import std.algorithm;
import std.array;
import std.stdio;
import std.conv;
import std.exception;
import std.traits;

class Type {
    Value call(string name, Value thisptr, Value[] args) {
        throw new Exception("Method not implemented: " ~ name);
    }
}

class ClassType : Type {
    Value[string] fields;
    Value delegate(Value, Value[])[string] methods;

    this(Value[string] fields) {
        this.fields = fields;
    }

    override Value call(string name, Value thisptr, Value[] args) {
        if (auto method = name in methods) {
            return (*method)(thisptr, args);
        }
        throw new Exception("Method not found: " ~ name);
    }
}

class IntType : Type {
    static IntType instance;

    static this() {
        instance = new IntType();
    }

    override Value call(string name, Value thisptr, Value[] args) {
        int value = thisptr.expect!int;
        switch (name) {
            case "add":
                enforce(args.length == 1, "add expects 1 argument");
                return Value(value + args[0].expect!int);
            case "sub":
                enforce(args.length == 1, "sub expects 1 argument");
                return Value(value - args[0].expect!int);
            case "mul":
                enforce(args.length == 1, "mul expects 1 argument");
                return Value(value * args[0].expect!int);
            case "div":
                enforce(args.length == 1, "div expects 1 argument");
                int divisor = args[0].expect!int;
                enforce(divisor != 0, "Division by zero");
                return Value(value / divisor);
            case "greater":
                enforce(args.length == 1, "greater expects 1 argument");
                return Value(value > args[0].expect!int ? 1 : 0);
            case "smaller":
                enforce(args.length == 1, "smaller expects 1 argument");
                return Value(value < args[0].expect!int ? 1 : 0);
            case "equal":
                enforce(args.length == 1, "equal expects 1 argument");
                return Value(value == args[0].expect!int ? 1 : 0);
            default:
                throw new Exception("Unknown method: " ~ name);
        }
    }
}

class ArrayType : Type {
    static ArrayType instance;

    static this() {
        instance = new ArrayType();
    }

    override Value call(string name, Value thisptr, Value[] args) {
        Value[] arr = thisptr.expect!(Value[]);
        switch (name) {
            case "length":
                return Value(cast(int)arr.length);
            case "push":
                enforce(args.length == 1, "push expects 1 argument");
                arr ~= args[0];
                return Value(cast(int)arr.length);
            case "pop":
                enforce(arr.length > 0, "Cannot pop from empty array");
                Value last = arr[$ - 1];
                arr = arr[0 .. $ - 1];
                return last;
            default:
                throw new Exception("Unknown method: " ~ name);
        }
    }
}

struct Value {
    private {
        Type _type;
        union {
            int _int;
            Value[] _arr;
            Value[string] _obj;
        }
    }

    this(int i) {
        _type = IntType.instance;
        _int = i;
    }

    this(Value[] arr) {
        _type = ArrayType.instance;
        _arr = arr;
    }

    this(ClassType type) {
        _type = type;
        _obj = type.fields.dup;
    }

    T expect(T)() {
        static if (is(T == int)) {
            enforce(_type == IntType.instance, "Expected int, got " ~ typeid(_type).toString());
            return _int;
        } else static if (is(T == Value[])) {
            enforce(_type == ArrayType.instance, "Expected array, got " ~ typeid(_type).toString());
            return _arr;
        } else static if (is(T == Value[string])) {
            enforce(cast(ClassType)_type !is null, "Expected object, got " ~ typeid(_type).toString());
            return _obj;
        } else {
            static assert(false, "Unsupported type: " ~ T.stringof);
        }
    }

    Value opCall(string name, Value[] args...) {
        enforce(_type !is null, "Cannot call method on null type");
        return _type.call(name, this, args);
    }

    string toString() const {
        if (_type is null) {
            return "null";
        } else if (_type == IntType.instance) {
            return to!string(_int);
        } else if (_type == ArrayType.instance) {
            return to!string(_arr);
        } else if (cast(ClassType)_type !is null) {
            return to!string(_obj);
        }
        return "Unknown";
    }
}

class ModuleEntry {
    string name;

    this(string name) {
        this.name = name;
    }

    Value call(Value[] args) {
        throw new Exception("Cannot call " ~ name);
    }
}

class ClassEntry : ModuleEntry {
    ClassType classType;

    this(string name, ClassType classType) {
        super(name);
        this.classType = classType;
    }

    override Value call(Value[] args) {
        assert(args.length == 0);
        // Create a new instance of the class
        return Value(classType);
    }
}

class FunctionEntry : ModuleEntry {
    Value delegate(Value[]) func;

    this(string name, Value delegate(Value[]) func) {
        super(name);
        this.func = func;
    }

    override Value call(Value[] args) {
        return func(args);
    }
}

class Module {
    ModuleEntry[string] entries;
    Value delegate(Value[])[string] methods;

    this() {
        addDefaultMethods();
    }

    void addDefaultMethods() {
        methods["print"] = (Value[] args) {
            enforce(args.length == 1, "print expects 1 argument");
            writeln(args[0].toString());
            return Value(0); // Return 0 as a convention
        };
    }

    void add(ModuleEntry entry) {
        entries[entry.name] = entry;
    }

    ModuleEntry get(string name) {
        enforce(name in entries, "Entry not found: " ~ name);
        return entries[name];
    }

    Value call(string name, Value[] args) {
        if (name in methods) {
            return methods[name](args);
        }
        return get(name).call(args);
    }
}

unittest {
    // Create a new module
    auto mod = new Module();

    // Define the fibonacci function
    auto fibFunc = delegate Value(Value[] args) {
        enforce(args.length == 1, "fibonacci expects 1 argument");
        int n = args[0].expect!int;
        if (n <= 1) return Value(n);

        Value fib1 = Value(0);
        Value fib2 = Value(1);
        for (int i = 2; i <= n; i++) {
            Value temp = fib2;
            fib2 = fib2("add", fib1);
            fib1 = temp;
        }
        return fib2;
    };

    // Add the function to the module
    mod.add(new FunctionEntry("fibonacci", fibFunc));

    // Test the fibonacci function
    assert(mod.call("fibonacci", [Value(0)]).expect!int == 0);
    assert(mod.call("fibonacci", [Value(1)]).expect!int == 1);
    assert(mod.call("fibonacci", [Value(2)]).expect!int == 1);
    assert(mod.call("fibonacci", [Value(3)]).expect!int == 2);
    assert(mod.call("fibonacci", [Value(4)]).expect!int == 3);
    assert(mod.call("fibonacci", [Value(5)]).expect!int == 5);
    assert(mod.call("fibonacci", [Value(10)]).expect!int == 55);

    // Test type checking
    try {
        mod.call("fibonacci", [Value([Value(1)])]);
        assert(false, "Should have thrown an exception");
    } catch (Exception e) {
        assert(e.msg == "Expected int, got runtime.ArrayType");
    }

    // Define a simple class
    auto personType = new ClassType([
        "name": Value(Value[].init),
        "age": Value(0)
    ]);
    personType.methods["sayHello"] = (Value thisptr, Value[] args) {
        auto name = thisptr.expect!(Value[string])["name"].expect!(Value[]);
        return Value((name ~ [Value(32)] ~ "says hello!".map!(c => Value(cast(int)c)).array));
    };

    // Add the class to the module
    mod.add(new ClassEntry("Person", personType));

    // Create an instance of the class and call a method
    auto person = mod.call("Person", []);
    person.expect!(Value[string])["name"] = Value("Alice".map!(c => Value(cast(int)c)).array);
    person.expect!(Value[string])["age"] = Value(30);
    auto greeting = person("sayHello", []);

    assert(greeting.expect!(Value[]).map!(v => cast(char)v.expect!int).array == "Alice says hello!");

    writeln("All tests passed!");
}
