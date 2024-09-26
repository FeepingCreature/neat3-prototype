import std.algorithm;
import std.array;
import std.conv;
import std.exception;
import std.file;
import std.format;
import std.stdio;
import std.traits;

class Type {
    Value call(string name, Value thisptr, Value[] args) {
        throw new Exception("Method not implemented: " ~ name);
    }
}

class ClassType : Type {
    string name;
    ClassType parent;
    Value[string] fields;
    Value delegate(Value, Value[])[string] methods;

    this(string name, ClassType parent, Value[string] fields) {
        this.name = name;
        this.parent = parent;
        this.fields = fields;
        if (parent) {
            foreach (key, value; parent.fields) {
                if (key !in this.fields) {
                    this.fields[key] = value;
                }
            }
        }
    }

    override Value call(string name, Value thisptr, Value[] args) {
        if (name == "isNull") {
            return Value(0);
        }
        if (auto method = name in methods) {
            return (*method)(thisptr, args);
        }
        if (parent) {
            return parent.call(name, thisptr, args);
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
            case "and":
                enforce(args.length == 1, "and expects 1 argument");
                return Value((value && args[0].expect!int) ? 1 : 0);
            case "or":
                enforce(args.length == 1, "or expects 1 argument");
                return Value((value || args[0].expect!int) ? 1 : 0);
            case "notEqual":
                enforce(args.length == 1, "notEqual expects 1 argument");
                return Value(value != args[0].expect!int ? 1 : 0);
            case "smallerEqual":
                enforce(args.length == 1, "smallerEqual expects 1 argument");
                return Value(value <= args[0].expect!int ? 1 : 0);
            case "greaterEqual":
                enforce(args.length == 1, "greaterEqual expects 1 argument");
                return Value(value >= args[0].expect!int ? 1 : 0);
            case "not":
                enforce(args.length == 0, "not expects 0 arguments");
                return Value(value == 0 ? 1 : 0);
            case "negate":
                enforce(args.length == 0, "negate expects 0 arguments");
                return Value(-value);
            case "toString":
                return Value(value.text.map!(ch => Value(cast(int) ch)).array);
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
                enforce(args.length == 0, "length expects 0 arguments");
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
            case "get":
                enforce(args.length == 1, "get expects 1 argument");
                int index = args[0].expect!int;
                enforce(index >= 0 && index < arr.length, "Index out of bounds");
                return arr[index];
            case "set":
                enforce(args.length == 2, "set expects 2 arguments");
                int index = args[0].expect!int;
                enforce(index >= 0 && index < arr.length, "Index out of bounds");
                arr[index] = args[1];
                return Value(0);
            case "slice":
                enforce(args.length == 2, "slice expects 2 arguments");
                int start = args[0].expect!int;
                int end = args[1].expect!int;
                enforce(start >= 0 && end <= arr.length && start <= end,
                    format!"Invalid slice range: %s .. %s not in 0 .. %s"(start, end, arr.length));
                return Value(arr[start .. end]);
            case "concat":
                enforce(args.length == 1, "concat expects 1 argument");
                Value[] other = args[0].expect!(Value[]);
                return Value (arr ~ other);
            case "equal":
                import std.range : iota;
                enforce(args.length == 1, "equal expects 1 argument");
                Value[] other = args[0].expect!(Value[]);
                return Value(arr.length == other.length && arr.length.iota
                    .map!(i => arr[i].type.call("equal", arr[i], [other[i]]).expect!int)
                    .all ? 1 : 0);
            case "join":
                enforce(args.length == 1, "join expects 1 argument");
                return Value(arr.map!(a => a.expect!(Value[])).join(args[0].expect!(Value[])));
            case "toInt":
                enforce(args.length == 0, "toInt expects 0 arguments");
                auto str = arr.map!(v => cast(immutable char)v.expect!int).array;
                return Value(str.parse!int);
            default:
                throw new Exception("Unknown method: " ~ name);
        }
    }
}

class NullType : Type {
    static NullType instance;

    static this() {
        instance = new NullType();
    }

    override Value call(string name, Value thisptr, Value[] args) {
        if (name == "isNull") {
            return Value(1);
        }
        throw new Exception("Null object has no methods except isNull");
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

    this(typeof(null)) {
        _type = NullType.instance;
    }

    static Value nullValue;

    static this() {
        nullValue = Value(null);
    }

    @property Type type() { return _type; }

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

    void setField(string fieldName, Value value) {
        if (auto classType = cast(ClassType)_type) {
            _obj[fieldName] = value;
        } else {
            throw new Exception("Cannot set field on non-object type");
        }
    }

    Value getField(string fieldName) {
        if (auto classType = cast(ClassType)_type) {
            if (auto field = fieldName in _obj) {
                return *field;
            }
            throw new Exception("Field not found: " ~ fieldName);
        }
        throw new Exception("Cannot get field from non-object type");
    }

    Value call(string name, Value[] args) {
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

Value instanceOf(Value obj, string typeName) {
    if (auto classType = cast(ClassType)obj.type) {
        ClassType currentType = classType;
        while (currentType !is null) {
            if (currentType.name == typeName) {
                return obj;
            }
            currentType = currentType.parent;
        }
    }
    return Value.nullValue;
}

Value logicalAnd(Value left, Value delegate() rightThunk) {
    if (left.expect!int == 0) {
        return Value(0);
    }
    return rightThunk();
}

Value logicalOr(Value left, Value delegate() rightThunk) {
    if (left.expect!int != 0) {
        return Value(1);
    }
    return rightThunk();
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
        // Create a new instance of the class
        Value instance = Value(classType);

        // Call the constructor (init method) if it exists
        if ("init" in classType.methods) {
            classType.methods["init"](instance, args);
        } else if (args.length > 0) {
            throw new Exception("Constructor called with arguments, but no init method defined for class " ~ name);
        }

        return instance;
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
            if (cast(ArrayType) args[0].type) {
                auto str = args[0].expect!(Value[]).map!(v => cast(immutable char)v.expect!int).array;
                writeln(str);
            } else {
                writeln(args[0].toString());
            }
            return Value(0); // Return 0 as a convention
        };

        methods["readFile"] = (Value[] args) {
            enforce(args.length == 1, "readFile expects 1 argument");
            string filename = args[0].expect!(Value[]).map!(v => cast(immutable char)v.expect!int).array;
            string content = readText(filename);
            return Value(content.map!(c => Value(cast(int)c)).array);
        };

        methods["writeFile"] = (Value[] args) {
            enforce(args.length == 2, "writeFile expects 2 arguments");
            string filename = args[0].expect!(Value[]).map!(v => cast(immutable char)v.expect!int).array;
            string content = args[1].expect!(Value[]).map!(v => cast(immutable char)v.expect!int).array;
            std.file.write(filename, content);
            return Value(0);
        };

        methods["assert"] = (Value[] args) {
            enforce(args.length == 1, "assert expects 1 argument");
            int value = args[0].expect!int;
            assert(value);
            return Value(0); // Return 0 as a convention
        };
    }

    void add(ModuleEntry entry) {
        entries[entry.name] = entry;
    }

    ModuleEntry get(string name) {
        enforce(name in entries, format!"Entry not found: %s in %s"(name, entries.keys));
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
            fib2 = fib2.call("add", [fib1]);
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
    auto personType = new ClassType("Person", null, [
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
    person.setField("name", Value("Alice".map!(c => Value(cast(int)c)).array));
    person.setField("age", Value(30));
    auto greeting = person.call("sayHello", []);

    assert(greeting.expect!(Value[]).map!(v => cast(char)v.expect!int).array == "Alice says hello!");

    // Test logical AND
    assert(logicalAnd(Value(1), () => Value(1)).expect!int == 1);
    assert(logicalAnd(Value(0), () => Value(1)).expect!int == 0);
    assert(logicalAnd(Value(1), () => Value(0)).expect!int == 0);

    // Test logical OR
    assert(logicalOr(Value(1), () => Value(1)).expect!int == 1);
    assert(logicalOr(Value(0), () => Value(1)).expect!int == 1);
    assert(logicalOr(Value(1), () => Value(0)).expect!int == 1);
    assert(logicalOr(Value(0), () => Value(0)).expect!int == 0);

    writeln("All tests passed!");
}
