=== Concept Summary ===

neat3 is a C-like language that eliminates tradeoffs between dynamic and static languages, and between small generic binaries and large specialized ones. It uses a three-layer architecture:

1. Runtime Layer: Dynamic interpreter with capabilities defining value types.
2. Language Layer: Strict constraint-based typing system, central to enabling AOT compilation. Relative constraints ensure precise type control in data structures.
3. Optimizer Layer: AOT compilation with value type specialization, eliminating all runtime typechecks along any call boundary.

neat3 aims to provide the flexibility of dynamic languages with the performance of static compilation, making optimization an compiler concern rather than a programmer responsibility.

The core idea is to blur the line between static and dynamic typing in a way that allows the compiler to make intelligent decisions about optimization without sacrificing compilation speed.

When you write a function in Neat3, you're not saying "this takes an int and returns a string." You're saying "this takes something I can add to, and returns something I can concatenate." The compiler then has the freedom to decide how to implement this based on the context: dynamic lookup or specialization.

This approach creates a continuum between fully dynamic and fully static code. At one extreme, the compiler could treat everything as generic variants, compiling quickly but with potential runtime overhead. At the other extreme, it could fully specialize every function call, achieving C++-like performance but with longer compile times.

The key insight is that this decision doesn't have to be made upfront by the programmer. The same source code can be compiled different ways depending on the needs of the moment. Need a quick debug build? Lean towards the dynamic end. Preparing for release? Crank up the specialization.

Concretely, in the base runtime layer, Neat3 treats all parameters and variables as inherently untyped, similar to dynamically typed languages, making types a property of the value. However, the capability/constraint system at compiletime is exactly strong enough to ensure that no type errors can occur in the dynamic typed language, which is why the optimizer can reliably specialize dynamic functions for actual types without running into semantic errors.

This unified view of typing also simplifies the language itself. There's no need for separate concepts of templates, generics, or runtime polymorphism. It's all just functions with constraints and typechecks, and the compiler decides how to implement them.

The result is a language that can feel as flexible as Python when you're writing it, but can potentially perform like C++ when you need it to. And crucially, you don't have to change your code to move between these extremes.

Example: `T inc(T value : Number) type(T) { return value + 1; }`.

Here, `value` has the *type* `T` (a variable), and the *capability* `Number`. The function
also imposes the *constraint* that the returned value must be of the same type as the parameter - this must be
guaranteed by the definition of `Number.+`. If the definition of `+` does not allow this, the function immediately
fails to compile, rather than during what would be instantiation in a C++-like language.

This lowers into the runtime as `Value inc(Value value) { return value["_builtin_Number"]["+"](Value(1)); }`.
The constraints guarantee that the capability is available, and the implementation guarantees that the return value
is "int for int", "float for float", etc.

If the function is specialized for, say, int, it lowers to `int inc(int value) { return value + 1; }`.
If specialized for float, it lowers to `float inc(float value) { return value + 1; }`. And so on.

=== End of Summary ===
