import std.stdio;
import std.file;
import std.range;
import std.ascii;
import std.array;
import std.string;
import std.conv;
import std.algorithm;

/**

Simplifications for the bootstrap, 0.1 version of the language:

- D bootstrap implementation language, D compile target
  (this lets us use arrays and hashmaps in the runtime, saving a lot of effort)
- untyped runtime only, no types, no constraints
- classes, fields and methods (for the AST), hence object method calls
- global functions and function calls
- arrays (can be typeless)
- no modules, single file only
- no structs, classes can handle it
- enough runtime to do basic I/O: read file to char[], write char[] to file, print to console.
- mutable variables, everything is mutable
- no typechecks, all done as asserts in the runtime
- runtime types: class, array, int.
- blocks, if statements, while statements (maybe array-element loops, as a treat)
- no GC/RC, leak everything
- no error propagation, every error kills the program right there (assert runtime function)
- no operands at all, builtin type functions only (.add, .sub, .concat etc.), this also handles string ops
  (.slice, .concat), and conversions (.toInt, .toString).
- basic inheritance
**/

class ASTNode {
    string filename;
    int line;

    this(string filename, int line) {
        this.filename = filename;
        this.line = line;
    }

    string compile() {
        return "";
    }
}

class Program : ASTNode {
    ASTNode[] nodes;

    this(string filename, int line, ASTNode[] nodes) {
        super(filename, line);
        this.nodes = nodes;
    }

    override string compile() {
        string[] compiledNodes;
        foreach (node; nodes) {
            compiledNodes ~= node.compile();
        }
        return "import std.stdio;
import std.algorithm;
import std.array;
import std.exception;
import runtime;

void main(string[] args) {
    auto mod = new Module();
" ~ compiledNodes.join("\n") ~ "
    mod.call(\"main\", [Value(args.map!(a => Value(a.map!(c => Value(cast(int)c)).array)).array)]);
}";
    }
}

class FunctionDecl : ASTNode {
    string name;
    string[] params;
    ASTNode[] body;

    this(string filename, int line, string name, string[] params, ASTNode[] body) {
        super(filename, line);
        this.name = name;
        this.params = params;
        this.body = body;
    }

    override string compile() {
        string[] compiledBody;
        foreach (stmt; body) {
            compiledBody ~= stmt.compile();
        }

        string paramList = params.map!(p => "Value " ~ p).join(", ");
        string functionBody = compiledBody.join("\n    ");

        return "mod.add(new FunctionEntry(\"" ~ name ~ "\", delegate Value(Value[] args) {\n" ~
               "    enforce(args.length == " ~ to!string(params.length) ~ ", \"" ~ name ~ " expects " ~ to!string(params.length) ~ " argument(s)\");\n" ~
               params.enumerate.map!(t => "    Value " ~ t.value ~ " = args[" ~ to!string(t.index) ~ "];").join("\n") ~ "\n" ~
               "    " ~ functionBody ~ "\n" ~
               "}));\n";
    }
}

class ClassDecl : ASTNode {
    string name;
    string parent;
    string[] fields;
    FunctionDecl[] methods;

    this(string filename, int line, string name, string parent, string[] fields, FunctionDecl[] methods) {
        super(filename, line);
        this.name = name;
        this.parent = parent;
        this.fields = fields;
        this.methods = methods;
    }

    override string compile() {
        string[] compiledMethods;
        foreach (method; methods) {
            compiledMethods ~= compileMethod(method);
        }

        string fieldDeclarations = fields.map!(f => "\"" ~ f ~ "\": Value(0)").join(", ");
        string parentDeclaration = parent ? "mod.get!ClassEntry(\"" ~ parent ~ "\").classType" : "null";

        return "auto " ~ name ~ "Type = new ClassType(" ~ parentDeclaration ~ ", [" ~ fieldDeclarations ~ "]);\n" ~
               compiledMethods.join("\n") ~
               "mod.add(new ClassEntry(\"" ~ name ~ "\", " ~ name ~ "Type));\n";
    }

    string compileMethod(FunctionDecl method) {
        string[] compiledBody;
        foreach (stmt; method.body) {
            compiledBody ~= stmt.compile();
        }

        string paramList = method.params.map!(p => "Value " ~ p).join(", ");
        string functionBody = compiledBody.join("\n    ");

        return name ~ "Type.methods[\"" ~ method.name ~ "\"] = (Value thisptr, Value[] args) {\n" ~
               "    enforce(args.length == " ~ to!string(method.params.length) ~ ", \"" ~ method.name ~ " expects " ~ to!string(method.params.length) ~ " argument(s)\");\n" ~
               method.params.enumerate.map!(t => "    Value " ~ t.value ~ " = args[" ~ to!string(t.index) ~ "];").join("\n") ~ "\n" ~
               "    " ~ functionBody ~ "\n" ~
               "    return Value(0);\n" ~ // Default return value if none specified
               "};\n";
    }
}

class VariableDecl : ASTNode {
    string name;
    ASTNode initializer;

    this(string filename, int line, string name, ASTNode initializer) {
        super(filename, line);
        this.name = name;
        this.initializer = initializer;
    }

    override string compile() {
        return "Value " ~ name ~ " = " ~ initializer.compile() ~ ";";
    }
}

class MethodCall : ASTNode {
    ASTNode object;
    string method;
    ASTNode[] args;

    this(string filename, int line, ASTNode object, string method, ASTNode[] args) {
        super(filename, line);
        this.object = object;
        this.method = method;
        this.args = args;
    }

    override string compile() {
        string[] compiledArgs = args.map!(a => a.compile()).array;
        string objectCode = (cast(Identifier)object !is null && (cast(Identifier)object).name == "this")
            ? "thisptr"
            : object.compile();
        return "(" ~ objectCode ~ ").call(\"" ~ method ~ "\", [" ~ compiledArgs.join(", ") ~ "])";
    }
}

class FunctionCall : ASTNode {
    string name;
    ASTNode[] args;

    this(string filename, int line, string name, ASTNode[] args) {
        super(filename, line);
        this.name = name;
        this.args = args;
    }

    override string compile() {
        string[] compiledArgs = args.map!(a => a.compile()).array;
        return "mod.call(\"" ~ name ~ "\", [" ~ compiledArgs.join(", ") ~ "])";
    }
}

class IfStatement : ASTNode {
    ASTNode condition;
    ASTNode[] thenBody;
    ASTNode[] elseBody;

    this(string filename, int line, ASTNode condition, ASTNode[] thenBody, ASTNode[] elseBody) {
        super(filename, line);
        this.condition = condition;
        this.thenBody = thenBody;
        this.elseBody = elseBody;
    }

    override string compile() {
        string compiledCondition = condition.compile();
        string[] compiledThenBody = thenBody.map!(s => s.compile()).array;
        string[] compiledElseBody = elseBody.map!(s => s.compile()).array;

        string result = "if (" ~ compiledCondition ~ ".expect!int != 0) {\n";
        result ~= "    " ~ compiledThenBody.join("\n    ") ~ "\n";
        result ~= "}";

        if (elseBody.length > 0) {
            result ~= " else {\n";
            result ~= "    " ~ compiledElseBody.join("\n    ") ~ "\n";
            result ~= "}";
        }

        return result;
    }
}

class WhileStatement : ASTNode {
    ASTNode condition;
    ASTNode[] body;

    this(string filename, int line, ASTNode condition, ASTNode[] body) {
        super(filename, line);
        this.condition = condition;
        this.body = body;
    }

    override string compile() {
        string compiledCondition = condition.compile();
        string[] compiledBody = body.map!(s => s.compile()).array;

        return "while (" ~ compiledCondition ~ ".expect!int != 0) {\n" ~
            "    " ~ compiledBody.join("\n    ") ~ "\n" ~
            "}";
    }
}

class AssignmentStatement : ASTNode {
    ASTNode lhs;
    ASTNode rhs;

    this(string filename, int line, ASTNode lhs, ASTNode rhs) {
        super(filename, line);
        this.lhs = lhs;
        this.rhs = rhs;
    }

    override string compile() {
        if (auto fa = cast(FieldAccess)lhs) {
            return "(" ~ fa.object.compile() ~ ").setField(\"" ~ fa.field ~ "\", " ~ rhs.compile() ~ ");";
        } else {
            return lhs.compile() ~ " = " ~ rhs.compile() ~ ";";
        }
    }
}

class ReturnStatement : ASTNode {
    ASTNode expression;

    this(string filename, int line, ASTNode expression) {
        super(filename, line);
        this.expression = expression;
    }

    override string compile() {
        return "return " ~ expression.compile() ~ ";";
    }
}

class ExpressionStatement : ASTNode {
    ASTNode expression;

    this(string filename, int line, ASTNode expression) {
        super(filename, line);
        this.expression = expression;
    }

    override string compile() {
        return expression.compile() ~ ";";
    }
}

class Identifier : ASTNode {
    string name;

    this(string filename, int line, string name) {
        super(filename, line);
        this.name = name;
    }

    override string compile() {
        if (name == "this") {
            return "thisptr";
        }
        return name;
    }
}

class IntegerLiteral : ASTNode {
    int value;

    this(string filename, int line, int value) {
        super(filename, line);
        this.value = value;
    }

    override string compile() {
        return "Value(" ~ to!string(value) ~ ")";
    }
}

class StringLiteral : ASTNode {
    string value;

    this(string filename, int line, string value) {
        super(filename, line);
        this.value = value;
    }

    override string compile() {
        return "Value(" ~ value.map!(c => to!string(cast(int)c)).join(", ") ~ ")";
    }
}

class NullLiteral : ASTNode {
    this(string filename, int line) {
        super(filename, line);
    }

    override string compile() {
        return "Value.nullValue";
    }
}

class FieldAccess : ASTNode {
    ASTNode object;
    string field;

    this(string filename, int line, ASTNode object, string field) {
        super(filename, line);
        this.object = object;
        this.field = field;
    }

    override string compile() {
        return "(" ~ object.compile() ~ ").getField(\"" ~ field ~ "\")";
    }
}

class Parser {
    string input;
    string filename;
    int position;
    int line;

    this(string input, string filename) {
        this.input = input;
        this.filename = filename;
        this.position = 0;
        this.line = 1;
    }

    bool accept(string s) {
        skipWhitespace();
        if (input[position .. $].startsWith(s)) {
            position += s.length;
            return true;
        }
        return false;
    }

    void expect(string s) {
        if (!accept(s)) {
            throw new Exception(format("Expected '%s' at %s:%d", s, filename, line));
        }
    }

    void skipWhitespace() {
        while (position < input.length && (input[position] == ' ' || input[position] == '\t' || input[position] == '\n' || input[position] == '\r')) {
            if (input[position] == '\n') line++;
            position++;
        }
    }

    void skipComments() {
        while (true) {
            skipWhitespace();
            if (accept("//")) {
                while (position < input.length && input[position] != '\n') {
                    position++;
                }
            } else if (accept("/*")) {
                while (position < input.length && !accept("*/")) {
                    if (input[position] == '\n') line++;
                    position++;
                }
            } else {
                break;
            }
        }
    }

    string parseIdentifier() {
        skipWhitespace();
        skipComments();
        int start = position;
        while (position < input.length && (input[position].isAlpha || input[position] == '_' || (position > start && input[position].isDigit))) {
            position++;
        }
        if (start == position) {
            throw new Exception(format("Expected identifier at %s:%d", filename, line));
        }
        return input[start .. position];
    }

    Program parse() {
        ASTNode[] nodes;
        while (position < input.length) {
            skipWhitespace();
            skipComments();
            if (accept("function")) {
                nodes ~= parseFunctionDecl();
            } else if (accept("class")) {
                nodes ~= parseClassDecl();
            } else {
                break;
            }
        }
        return new Program(filename, 1, nodes);
    }

    FunctionDecl parseFunctionDecl() {
        string name = parseIdentifier();
        string[] params;

        expect("(");
        if (!accept(")")) {
            do {
                params ~= parseIdentifier();
            } while (accept(","));
            expect(")");
        }

        ASTNode[] body;
        expect("{");
        while (!accept("}")) {
            body ~= parseStatement();
        }

        return new FunctionDecl(filename, line, name, params, body);
    }

    ClassDecl parseClassDecl() {
        string name = parseIdentifier();
        string parent = null;
        if (accept(":")) {
            parent = parseIdentifier();
        }
        string[] fields;
        FunctionDecl[] methods;

        expect("{");
        while (!accept("}")) {
            if (accept("function")) {
                methods ~= parseFunctionDecl();
            } else {
                expect("auto");
                fields ~= parseIdentifier();
                expect(";");
            }
        }

        return new ClassDecl(filename, line, name, parent, fields, methods);
    }

    ASTNode parseStatement() {
        skipWhitespace();
        skipComments();

        if (accept("if")) {
            return parseIfStatement();
        } else if (accept("while")) {
            return parseWhileStatement();
        } else if (accept("return")) {
            ASTNode expr = parseExpression();
            expect(";");
            return new ReturnStatement(filename, line, expr);
        } else if (accept("auto")) {
            string name = parseIdentifier();
            expect("=");
            ASTNode initializer = parseExpression();
            expect(";");
            return new VariableDecl(filename, line, name, initializer);
        } else {
            ASTNode expr = parseExpression();
            if (accept("=")) {
                ASTNode rhs = parseExpression();
                expect(";");
                return new AssignmentStatement(filename, line, expr, rhs);
            } else {
                expect(";");
                return new ExpressionStatement(filename, line, expr);
            }
        }
    }

    IfStatement parseIfStatement() {
        expect("(");
        ASTNode condition = parseExpression();
        expect(")");

        ASTNode[] thenBody;
        expect("{");
        while (!accept("}")) {
            thenBody ~= parseStatement();
        }

        ASTNode[] elseBody;
        if (accept("else")) {
            expect("{");
            while (!accept("}")) {
                elseBody ~= parseStatement();
            }
        }

        return new IfStatement(filename, line, condition, thenBody, elseBody);
    }

    WhileStatement parseWhileStatement() {
        expect("(");
        ASTNode condition = parseExpression();
        expect(")");

        ASTNode[] body;
        expect("{");
        while (!accept("}")) {
            body ~= parseStatement();
        }

        return new WhileStatement(filename, line, condition, body);
    }

    ASTNode parseExpression() {
        ASTNode left = parsePrimary();

        while (true) {
            if (accept(".")) {
                string identifier = parseIdentifier();
                if (accept("(")) {
                    ASTNode[] args;
                    if (!accept(")")) {
                        do {
                            args ~= parseExpression();
                        } while (accept(","));
                        expect(")");
                    }
                    left = new MethodCall(filename, line, left, identifier, args);
                } else {
                    left = new FieldAccess(filename, line, left, identifier);
                }
            } else {
                break;
            }
        }

        return left;
    }

    ASTNode parsePrimary() {
        skipWhitespace();
        skipComments();

        if (position < input.length && input[position].isDigit) {
            return parseIntegerLiteral();
        } else if (accept("\"")) {
            return parseStringLiteral();
        } else if (accept("null")) {
            return new NullLiteral(filename, line);
        } else {
            string id = parseIdentifier();
            if (accept("(")) {
                ASTNode[] args;
                if (!accept(")")) {
                    do {
                        args ~= parseExpression();
                    } while (accept(","));
                    expect(")");
                }
                return new FunctionCall(filename, line, id, args);
            } else {
                return new Identifier(filename, line, id);
            }
        }
    }

    IntegerLiteral parseIntegerLiteral() {
        int start = position;
        while (position < input.length && input[position].isDigit) {
            position++;
        }
        int value = to!int(input[start .. position]);
        return new IntegerLiteral(filename, line, value);
    }

    StringLiteral parseStringLiteral() {
        int start = position;
        while (position < input.length && input[position] != '"') {
            if (input[position] == '\\') {
                position++;
            }
            position++;
        }
        expect("\"");
        string value = input[start .. position - 1];
        return new StringLiteral(filename, line, value);
    }
}

void main(string[] args) {
    if (args.length != 3) {
        writeln("Usage: neat3 <input_file> <output_file>");
        return;
    }

    string inputFile = args[1];
    string outputFile = args[2];

    string input = readText(inputFile);

    Parser parser = new Parser(input, inputFile);
    Program program = parser.parse();

    string output = program.compile();

    std.file.write(outputFile, output);
}
