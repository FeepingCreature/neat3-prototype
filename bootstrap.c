#include "runtime.h"

/**
 * Known-good compiled version of main.n3 for bootstrapping.
 */

Value CodegenContext_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "init expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value parent = args[0];    object_set_field(&*this_ptr, "parent", parent);
Value v1 = create_int(0);
object_set_field(&*this_ptr, "variableCounter", v1);
Value v2 = create_array((Value[]){}, 0);
object_set_field(&*this_ptr, "code", v2);
    return create_null();
}

Value CodegenContext_newVariable(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "newVariable expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "parent"), "isNull", (Value[]){}, 0);
Value v2 = call_method(mod, &v1, "not", (Value[]){}, 0);
if (v2.data.int_value != 0) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "parent"), "newVariable", (Value[]){}, 0);
return v3;
}
Value v4 = create_int(1);
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "variableCounter"), "add", (Value[]){v4}, 1);
object_set_field(&*this_ptr, "variableCounter", v5);
Value v6 = create_array((Value[]){create_int(118)}, 1);
Value v7 = call_method(mod, &*object_get_field(*this_ptr, "variableCounter"), "toString", (Value[]){}, 0);
Value v8 = call_method(mod, &v6, "concat", (Value[]){v7}, 1);
return v8;
    return create_null();
}

Value CodegenContext_emitLine(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "emitLine expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value line = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "code"), "push", (Value[]){line}, 1);
object_set_field(&*this_ptr, "code", v1);
    return create_null();
}

Value CodegenContext_getCurrentCode(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "getCurrentCode expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){create_int(10)}, 1);
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "code"), "join", (Value[]){v1}, 1);
return v2;
    return create_null();
}

ClassType CodegenContext_type = {
    .base = {
        .methods = (MethodFunc[]){CodegenContext_init, CodegenContext_newVariable, CodegenContext_emitLine, CodegenContext_getCurrentCode},
        .method_names = (char*[]){"init", "newVariable", "emitLine", "getCurrentCode"},
        .method_count = 4
    },
    .name = "CodegenContext",
    .parent = NULL,
    .field_names = (char*[]){"parent", "variableCounter", "code"},
    .field_count = 3
};

Value TopLevelASTNode_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "init expects 2 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
    return create_null();
}

Value TopLevelASTNode_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value prog = args[0];    Value v1 = create_array((Value[]){}, 0);
return v1;
    return create_null();
}

ClassType TopLevelASTNode_type = {
    .base = {
        .methods = (MethodFunc[]){TopLevelASTNode_init, TopLevelASTNode_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "TopLevelASTNode",
    .parent = NULL,
    .field_names = (char*[]){"filename", "line"},
    .field_count = 2
};

Value ASTFunctionNode_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "init expects 2 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
    return create_null();
}

Value ASTFunctionNode_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = create_array((Value[]){}, 0);
return v1;
    return create_null();
}

ClassType ASTFunctionNode_type = {
    .base = {
        .methods = (MethodFunc[]){ASTFunctionNode_init, ASTFunctionNode_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "ASTFunctionNode",
    .parent = NULL,
    .field_names = (char*[]){"filename", "line"},
    .field_count = 2
};

Value Program_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value nodes = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "nodes", nodes);
    return create_null();
}

Value Program_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "compile expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){}, 0);
Value compiledNodes = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "nodes"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "nodes"), "get", (Value[]){i}, 1);
Value v6 = call_method(mod, &v5, "compile", (Value[]){*this_ptr}, 1);
Value v7 = call_method(mod, &compiledNodes, "push", (Value[]){v6}, 1);
compiledNodes = v7;
Value v8 = create_int(1);
Value v9 = call_method(mod, &i, "add", (Value[]){v8}, 1);
i = v9;
}
Value v10 = create_array((Value[]){create_int(10)}, 1);
Value v11 = call_method(mod, &compiledNodes, "join", (Value[]){v10}, 1);
return v11;
    return create_null();
}

Value Program_findClass(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "findClass expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value name = args[0];    Value v1 = create_int(0);
Value i = v1;
while (1) {
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "nodes"), "length", (Value[]){}, 0);
Value v3 = call_method(mod, &i, "smaller", (Value[]){v2}, 1);
if (v3.data.int_value == 0) break;
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "nodes"), "get", (Value[]){i}, 1);
Value v5 = instance_of(v4, "ClassDecl");
Value classDecl = v5;
Value v6 = call_method(mod, &classDecl, "isNull", (Value[]){}, 0);
Value v7 = call_method(mod, &v6, "not", (Value[]){}, 0);
Value v8 = create_int(0);
if (v7.data.int_value != 0) {
Value v9 = call_method(mod, &*object_get_field(classDecl, "name"), "equal", (Value[]){name}, 1);
    if (v9.data.int_value != 0) {
        v8 = create_int(1);
    }
}
if (v8.data.int_value != 0) {
return classDecl;
}
Value v10 = create_int(1);
Value v11 = call_method(mod, &i, "add", (Value[]){v10}, 1);
i = v11;
}
Value v12 = create_null();
return v12;
    return create_null();
}

ClassType Program_type = {
    .base = {
        .methods = (MethodFunc[]){Program_init, Program_compile, Program_findClass},
        .method_names = (char*[]){"init", "compile", "findClass"},
        .method_count = 3
    },
    .name = "Program",
    .parent = NULL,
    .field_names = (char*[]){"filename", "line", "nodes"},
    .field_count = 3
};

Value FunctionDecl_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 5) {
        fprintf(stderr, "init expects 5 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value name = args[2];
    Value params = args[3];
    Value body = args[4];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "name", name);
object_set_field(&*this_ptr, "params", params);
object_set_field(&*this_ptr, "body", body);
    return create_null();
}

Value FunctionDecl_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value prog = args[0];    Value v1 = create_null();
Value v2 = module_call(mod, "CodegenContext", (Value[]){v1}, 1);
Value bodyContext = v2;
Value v3 = create_array((Value[]){}, 0);
Value compiledBody = v3;
Value v4 = create_int(0);
Value i = v4;
while (1) {
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "body"), "length", (Value[]){}, 0);
Value v6 = call_method(mod, &i, "smaller", (Value[]){v5}, 1);
if (v6.data.int_value == 0) break;
Value v7 = call_method(mod, &*object_get_field(*this_ptr, "body"), "get", (Value[]){i}, 1);
Value v8 = call_method(mod, &v7, "compile", (Value[]){bodyContext}, 1);
Value v9 = call_method(mod, &compiledBody, "push", (Value[]){v8}, 1);
compiledBody = v9;
Value v10 = create_int(1);
Value v11 = call_method(mod, &i, "add", (Value[]){v10}, 1);
i = v11;
}
Value v12 = call_method(mod, &bodyContext, "getCurrentCode", (Value[]){}, 0);
Value functionBody = v12;
Value emittedName = *object_get_field(*this_ptr, "name");
Value v13 = create_array((Value[]){create_int(109), create_int(97), create_int(105), create_int(110)}, 4);
Value v14 = call_method(mod, &*object_get_field(*this_ptr, "name"), "equal", (Value[]){v13}, 1);
if (v14.data.int_value != 0) {
Value v15 = create_array((Value[]){create_int(109), create_int(97), create_int(105), create_int(110), create_int(50)}, 5);
emittedName = v15;
}
Value v16 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v17 = call_method(mod, &v16, "concat", (Value[]){emittedName}, 1);
Value v18 = create_array((Value[]){create_int(40), create_int(77), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(42), create_int(32), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(42), create_int(32), create_int(97), create_int(114), create_int(103), create_int(115), create_int(44), create_int(32), create_int(115), create_int(105), create_int(122), create_int(101), create_int(95), create_int(116), create_int(32), create_int(97), create_int(114), create_int(103), create_int(95), create_int(99), create_int(111), create_int(117), create_int(110), create_int(116), create_int(41), create_int(32), create_int(123), create_int(10)}, 47);
Value v19 = call_method(mod, &v17, "concat", (Value[]){v18}, 1);
Value v20 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(105), create_int(102), create_int(32), create_int(40), create_int(97), create_int(114), create_int(103), create_int(95), create_int(99), create_int(111), create_int(117), create_int(110), create_int(116), create_int(32), create_int(33), create_int(61), create_int(32)}, 21);
Value v21 = call_method(mod, &v19, "concat", (Value[]){v20}, 1);
Value v22 = call_method(mod, &*object_get_field(*this_ptr, "params"), "length", (Value[]){}, 0);
Value v23 = call_method(mod, &v22, "toString", (Value[]){}, 0);
Value v24 = call_method(mod, &v21, "concat", (Value[]){v23}, 1);
Value v25 = create_array((Value[]){create_int(41), create_int(32), create_int(123), create_int(10)}, 4);
Value v26 = call_method(mod, &v24, "concat", (Value[]){v25}, 1);
Value v27 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(102), create_int(112), create_int(114), create_int(105), create_int(110), create_int(116), create_int(102), create_int(40), create_int(115), create_int(116), create_int(100), create_int(101), create_int(114), create_int(114), create_int(44), create_int(32), create_int(34)}, 25);
Value v28 = call_method(mod, &v26, "concat", (Value[]){v27}, 1);
Value v29 = call_method(mod, &v28, "concat", (Value[]){*object_get_field(*this_ptr, "name")}, 1);
Value v30 = create_array((Value[]){create_int(32), create_int(101), create_int(120), create_int(112), create_int(101), create_int(99), create_int(116), create_int(115), create_int(32)}, 9);
Value v31 = call_method(mod, &v29, "concat", (Value[]){v30}, 1);
Value v32 = call_method(mod, &*object_get_field(*this_ptr, "params"), "length", (Value[]){}, 0);
Value v33 = call_method(mod, &v32, "toString", (Value[]){}, 0);
Value v34 = call_method(mod, &v31, "concat", (Value[]){v33}, 1);
Value v35 = create_array((Value[]){create_int(32), create_int(97), create_int(114), create_int(103), create_int(117), create_int(109), create_int(101), create_int(110), create_int(116), create_int(40), create_int(115), create_int(41), create_int(92), create_int(110), create_int(34), create_int(41), create_int(59), create_int(10)}, 18);
Value v36 = call_method(mod, &v34, "concat", (Value[]){v35}, 1);
Value v37 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(101), create_int(120), create_int(105), create_int(116), create_int(40), create_int(49), create_int(41), create_int(59), create_int(10)}, 17);
Value v38 = call_method(mod, &v36, "concat", (Value[]){v37}, 1);
Value v39 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(125), create_int(10)}, 6);
Value v40 = call_method(mod, &v38, "concat", (Value[]){v39}, 1);
Value v41 = call_method(mod, &*this_ptr, "compileParamAssignments", (Value[]){}, 0);
Value v42 = call_method(mod, &v40, "concat", (Value[]){v41}, 1);
Value v43 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32)}, 4);
Value v44 = call_method(mod, &v42, "concat", (Value[]){v43}, 1);
Value v45 = call_method(mod, &v44, "concat", (Value[]){functionBody}, 1);
Value v46 = create_array((Value[]){create_int(10)}, 1);
Value v47 = call_method(mod, &v45, "concat", (Value[]){v46}, 1);
Value v48 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(114), create_int(101), create_int(116), create_int(117), create_int(114), create_int(110), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(110), create_int(117), create_int(108), create_int(108), create_int(40), create_int(41), create_int(59), create_int(10)}, 26);
Value v49 = call_method(mod, &v47, "concat", (Value[]){v48}, 1);
Value v50 = create_array((Value[]){create_int(125), create_int(10)}, 2);
Value v51 = call_method(mod, &v49, "concat", (Value[]){v50}, 1);
return v51;
    return create_null();
}

Value FunctionDecl_compileParamAssignments(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "compileParamAssignments expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){}, 0);
Value assignments = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "params"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 10);
Value v6 = call_method(mod, &*object_get_field(*this_ptr, "params"), "get", (Value[]){i}, 1);
Value v7 = call_method(mod, &v5, "concat", (Value[]){v6}, 1);
Value v8 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(97), create_int(114), create_int(103), create_int(115), create_int(91)}, 8);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = call_method(mod, &i, "toString", (Value[]){}, 0);
Value v11 = call_method(mod, &v9, "concat", (Value[]){v10}, 1);
Value v12 = create_array((Value[]){create_int(93), create_int(59)}, 2);
Value v13 = call_method(mod, &v11, "concat", (Value[]){v12}, 1);
Value v14 = call_method(mod, &assignments, "push", (Value[]){v13}, 1);
assignments = v14;
Value v15 = create_int(1);
Value v16 = call_method(mod, &i, "add", (Value[]){v15}, 1);
i = v16;
}
Value v17 = create_array((Value[]){create_int(10)}, 1);
Value v18 = call_method(mod, &assignments, "join", (Value[]){v17}, 1);
return v18;
    return create_null();
}

ClassType FunctionDecl_type = {
    .base = {
        .methods = (MethodFunc[]){FunctionDecl_init, FunctionDecl_compile, FunctionDecl_compileParamAssignments},
        .method_names = (char*[]){"init", "compile", "compileParamAssignments"},
        .method_count = 3
    },
    .name = "FunctionDecl",
    .parent = &TopLevelASTNode_type,
    .field_names = (char*[]){"name", "params", "body", "filename", "line"},
    .field_count = 5
};

Value VTableEntry_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "init expects 2 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value name = args[0];
    Value function_ = args[1];    object_set_field(&*this_ptr, "name", name);
object_set_field(&*this_ptr, "function", function_);
    return create_null();
}

ClassType VTableEntry_type = {
    .base = {
        .methods = (MethodFunc[]){VTableEntry_init},
        .method_names = (char*[]){"init"},
        .method_count = 1
    },
    .name = "VTableEntry",
    .parent = NULL,
    .field_names = (char*[]){"name", "function"},
    .field_count = 2
};

Value VTable_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "init expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){}, 0);
object_set_field(&*this_ptr, "entries", v1);
    return create_null();
}

Value VTable_addEntry(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "addEntry expects 2 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value name = args[0];
    Value function_ = args[1];    Value v1 = create_int(0);
Value i = v1;
while (1) {
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "entries"), "length", (Value[]){}, 0);
Value v3 = call_method(mod, &i, "smaller", (Value[]){v2}, 1);
if (v3.data.int_value == 0) break;
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "entries"), "get", (Value[]){i}, 1);
Value v5 = call_method(mod, &*object_get_field(v4, "name"), "equal", (Value[]){name}, 1);
if (v5.data.int_value != 0) {
Value v6 = call_method(mod, &*object_get_field(*this_ptr, "entries"), "get", (Value[]){i}, 1);
object_set_field(&v6, "function", function_);
Value v7 = create_int(0);
return v7;
}
Value v8 = create_int(1);
Value v9 = call_method(mod, &i, "add", (Value[]){v8}, 1);
i = v9;
}
Value v10 = module_call(mod, "VTableEntry", (Value[]){name, function_}, 2);
Value v11 = call_method(mod, &*object_get_field(*this_ptr, "entries"), "push", (Value[]){v10}, 1);
object_set_field(&*this_ptr, "entries", v11);
Value v12 = create_int(0);
return v12;
    return create_null();
}

ClassType VTable_type = {
    .base = {
        .methods = (MethodFunc[]){VTable_init, VTable_addEntry},
        .method_names = (char*[]){"init", "addEntry"},
        .method_count = 2
    },
    .name = "VTable",
    .parent = NULL,
    .field_names = (char*[]){"entries"},
    .field_count = 1
};

Value ClassDecl_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 6) {
        fprintf(stderr, "init expects 6 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value name = args[2];
    Value parent = args[3];
    Value fields = args[4];
    Value methods = args[5];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "name", name);
object_set_field(&*this_ptr, "parent", parent);
object_set_field(&*this_ptr, "fields", fields);
object_set_field(&*this_ptr, "methods", methods);
    return create_null();
}

Value ClassDecl_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value prog = args[0];    Value v1 = create_array((Value[]){}, 0);
Value compiledMethods = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "methods"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "methods"), "get", (Value[]){i}, 1);
Value v6 = call_method(mod, &*this_ptr, "compileMethod", (Value[]){v5}, 1);
Value v7 = call_method(mod, &compiledMethods, "push", (Value[]){v6}, 1);
compiledMethods = v7;
Value v8 = create_int(1);
Value v9 = call_method(mod, &i, "add", (Value[]){v8}, 1);
i = v9;
}
Value v10 = create_array((Value[]){create_int(10)}, 1);
Value v11 = call_method(mod, &compiledMethods, "join", (Value[]){v10}, 1);
Value v12 = create_array((Value[]){create_int(10)}, 1);
Value v13 = call_method(mod, &v11, "concat", (Value[]){v12}, 1);
Value v14 = call_method(mod, &*this_ptr, "compileClassTypeInitializer", (Value[]){prog}, 1);
Value v15 = call_method(mod, &v13, "concat", (Value[]){v14}, 1);
return v15;
    return create_null();
}

Value ClassDecl_buildVTable(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "buildVTable expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value prog = args[0];    Value v1 = create_null();
Value vtable = v1;
Value v2 = create_array((Value[]){}, 0);
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "parent"), "equal", (Value[]){v2}, 1);
if (v3.data.int_value != 0) {
Value v4 = module_call(mod, "VTable", (Value[]){}, 0);
vtable = v4;
}
else {
Value v5 = call_method(mod, &prog, "findClass", (Value[]){*object_get_field(*this_ptr, "parent")}, 1);
Value parentClass = v5;
Value v6 = call_method(mod, &parentClass, "buildVTable", (Value[]){prog}, 1);
vtable = v6;
}
Value v7 = create_int(0);
Value i = v7;
while (1) {
Value v8 = call_method(mod, &*object_get_field(*this_ptr, "methods"), "length", (Value[]){}, 0);
Value v9 = call_method(mod, &i, "smaller", (Value[]){v8}, 1);
if (v9.data.int_value == 0) break;
Value v10 = call_method(mod, &*object_get_field(*this_ptr, "methods"), "get", (Value[]){i}, 1);
Value method = v10;
Value v11 = create_array((Value[]){create_int(95)}, 1);
Value v12 = call_method(mod, &*object_get_field(*this_ptr, "name"), "concat", (Value[]){v11}, 1);
Value v13 = call_method(mod, &v12, "concat", (Value[]){*object_get_field(method, "name")}, 1);
Value v14 = call_method(mod, &vtable, "addEntry", (Value[]){*object_get_field(method, "name"), v13}, 2);
v14;
Value v15 = create_int(1);
Value v16 = call_method(mod, &i, "add", (Value[]){v15}, 1);
i = v16;
}
return vtable;
    return create_null();
}

Value ClassDecl_compileMethod(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compileMethod expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value method = args[0];    Value v1 = create_null();
Value v2 = module_call(mod, "CodegenContext", (Value[]){v1}, 1);
Value context = v2;
Value v3 = create_array((Value[]){}, 0);
Value compiledBody = v3;
Value v4 = create_int(0);
Value i = v4;
while (1) {
Value v5 = call_method(mod, &*object_get_field(method, "body"), "length", (Value[]){}, 0);
Value v6 = call_method(mod, &i, "smaller", (Value[]){v5}, 1);
if (v6.data.int_value == 0) break;
Value v7 = call_method(mod, &*object_get_field(method, "body"), "get", (Value[]){i}, 1);
Value v8 = call_method(mod, &v7, "compile", (Value[]){context}, 1);
Value v9 = call_method(mod, &compiledBody, "push", (Value[]){v8}, 1);
compiledBody = v9;
Value v10 = create_int(1);
Value v11 = call_method(mod, &i, "add", (Value[]){v10}, 1);
i = v11;
}
Value v12 = call_method(mod, &context, "getCurrentCode", (Value[]){}, 0);
Value functionBody = v12;
Value v13 = call_method(mod, &*object_get_field(method, "params"), "length", (Value[]){}, 0);
Value argCount = v13;
Value v14 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v15 = call_method(mod, &v14, "concat", (Value[]){*object_get_field(*this_ptr, "name")}, 1);
Value v16 = create_array((Value[]){create_int(95)}, 1);
Value v17 = call_method(mod, &v15, "concat", (Value[]){v16}, 1);
Value v18 = call_method(mod, &v17, "concat", (Value[]){*object_get_field(method, "name")}, 1);
Value v19 = create_array((Value[]){create_int(40), create_int(77), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(42), create_int(32), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(42), create_int(32), create_int(116), create_int(104), create_int(105), create_int(115), create_int(95), create_int(112), create_int(116), create_int(114), create_int(44), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(42), create_int(32), create_int(97), create_int(114), create_int(103), create_int(115), create_int(44), create_int(32), create_int(115), create_int(105), create_int(122), create_int(101), create_int(95), create_int(116), create_int(32), create_int(97), create_int(114), create_int(103), create_int(95), create_int(99), create_int(111), create_int(117), create_int(110), create_int(116), create_int(41), create_int(32), create_int(123), create_int(10)}, 64);
Value v20 = call_method(mod, &v18, "concat", (Value[]){v19}, 1);
Value v21 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(105), create_int(102), create_int(32), create_int(40), create_int(97), create_int(114), create_int(103), create_int(95), create_int(99), create_int(111), create_int(117), create_int(110), create_int(116), create_int(32), create_int(33), create_int(61), create_int(32)}, 21);
Value v22 = call_method(mod, &v20, "concat", (Value[]){v21}, 1);
Value v23 = call_method(mod, &argCount, "toString", (Value[]){}, 0);
Value v24 = call_method(mod, &v22, "concat", (Value[]){v23}, 1);
Value v25 = create_array((Value[]){create_int(41), create_int(32), create_int(123), create_int(10)}, 4);
Value v26 = call_method(mod, &v24, "concat", (Value[]){v25}, 1);
Value v27 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(102), create_int(112), create_int(114), create_int(105), create_int(110), create_int(116), create_int(102), create_int(40), create_int(115), create_int(116), create_int(100), create_int(101), create_int(114), create_int(114), create_int(44), create_int(32), create_int(34)}, 25);
Value v28 = call_method(mod, &v26, "concat", (Value[]){v27}, 1);
Value v29 = call_method(mod, &v28, "concat", (Value[]){*object_get_field(method, "name")}, 1);
Value v30 = create_array((Value[]){create_int(32), create_int(101), create_int(120), create_int(112), create_int(101), create_int(99), create_int(116), create_int(115), create_int(32)}, 9);
Value v31 = call_method(mod, &v29, "concat", (Value[]){v30}, 1);
Value v32 = call_method(mod, &argCount, "toString", (Value[]){}, 0);
Value v33 = call_method(mod, &v31, "concat", (Value[]){v32}, 1);
Value v34 = create_array((Value[]){create_int(32), create_int(97), create_int(114), create_int(103), create_int(117), create_int(109), create_int(101), create_int(110), create_int(116), create_int(40), create_int(115), create_int(41), create_int(92), create_int(110), create_int(34), create_int(41), create_int(59), create_int(10)}, 18);
Value v35 = call_method(mod, &v33, "concat", (Value[]){v34}, 1);
Value v36 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(101), create_int(120), create_int(105), create_int(116), create_int(40), create_int(49), create_int(41), create_int(59), create_int(10)}, 17);
Value v37 = call_method(mod, &v35, "concat", (Value[]){v36}, 1);
Value v38 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(125), create_int(10)}, 6);
Value v39 = call_method(mod, &v37, "concat", (Value[]){v38}, 1);
Value v40 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(42), create_int(32), create_int(115), create_int(101), create_int(108), create_int(102), create_int(32), create_int(61), create_int(32), create_int(116), create_int(104), create_int(105), create_int(115), create_int(95), create_int(112), create_int(116), create_int(114), create_int(45), create_int(62), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(111), create_int(98), create_int(106), create_int(101), create_int(99), create_int(116), create_int(46), create_int(102), create_int(105), create_int(101), create_int(108), create_int(100), create_int(115), create_int(59), create_int(10)}, 48);
Value v41 = call_method(mod, &v39, "concat", (Value[]){v40}, 1);
Value v42 = call_method(mod, &*this_ptr, "compileMethodParamAssignments", (Value[]){method}, 1);
Value v43 = call_method(mod, &v41, "concat", (Value[]){v42}, 1);
Value v44 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32)}, 4);
Value v45 = call_method(mod, &v43, "concat", (Value[]){v44}, 1);
Value v46 = call_method(mod, &v45, "concat", (Value[]){functionBody}, 1);
Value v47 = create_array((Value[]){create_int(10)}, 1);
Value v48 = call_method(mod, &v46, "concat", (Value[]){v47}, 1);
Value v49 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(114), create_int(101), create_int(116), create_int(117), create_int(114), create_int(110), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(110), create_int(117), create_int(108), create_int(108), create_int(40), create_int(41), create_int(59), create_int(10)}, 26);
Value v50 = call_method(mod, &v48, "concat", (Value[]){v49}, 1);
Value v51 = create_array((Value[]){create_int(125), create_int(10)}, 2);
Value v52 = call_method(mod, &v50, "concat", (Value[]){v51}, 1);
return v52;
    return create_null();
}

Value ClassDecl_compileMethodParamAssignments(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compileMethodParamAssignments expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value method = args[0];    Value v1 = create_array((Value[]){}, 0);
Value assignments = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(method, "params"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 10);
Value v6 = call_method(mod, &*object_get_field(method, "params"), "get", (Value[]){i}, 1);
Value v7 = call_method(mod, &v5, "concat", (Value[]){v6}, 1);
Value v8 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(97), create_int(114), create_int(103), create_int(115), create_int(91)}, 8);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = call_method(mod, &i, "toString", (Value[]){}, 0);
Value v11 = call_method(mod, &v9, "concat", (Value[]){v10}, 1);
Value v12 = create_array((Value[]){create_int(93), create_int(59)}, 2);
Value v13 = call_method(mod, &v11, "concat", (Value[]){v12}, 1);
Value v14 = call_method(mod, &assignments, "push", (Value[]){v13}, 1);
assignments = v14;
Value v15 = create_int(1);
Value v16 = call_method(mod, &i, "add", (Value[]){v15}, 1);
i = v16;
}
Value v17 = create_array((Value[]){create_int(10)}, 1);
Value v18 = call_method(mod, &assignments, "join", (Value[]){v17}, 1);
return v18;
    return create_null();
}

Value ClassDecl_compileClassTypeInitializer(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compileClassTypeInitializer expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value prog = args[0];    Value v1 = create_array((Value[]){}, 0);
Value fieldNameInitializers = v1;
Value current = *this_ptr;
while (1) {
Value v2 = call_method(mod, &current, "isNull", (Value[]){}, 0);
Value v3 = call_method(mod, &v2, "not", (Value[]){}, 0);
if (v3.data.int_value == 0) break;
Value v4 = create_int(0);
Value i = v4;
while (1) {
Value v5 = call_method(mod, &*object_get_field(current, "fields"), "length", (Value[]){}, 0);
Value v6 = call_method(mod, &i, "smaller", (Value[]){v5}, 1);
if (v6.data.int_value == 0) break;
Value v7 = create_array((Value[]){create_int(34)}, 1);
Value v8 = call_method(mod, &*object_get_field(current, "fields"), "get", (Value[]){i}, 1);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = create_array((Value[]){create_int(34)}, 1);
Value v11 = call_method(mod, &v9, "concat", (Value[]){v10}, 1);
Value v12 = call_method(mod, &fieldNameInitializers, "push", (Value[]){v11}, 1);
fieldNameInitializers = v12;
Value v13 = create_int(1);
Value v14 = call_method(mod, &i, "add", (Value[]){v13}, 1);
i = v14;
}
Value v15 = create_array((Value[]){}, 0);
Value v16 = call_method(mod, &*object_get_field(current, "parent"), "equal", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = create_null();
current = v17;
}
else {
Value v18 = call_method(mod, &prog, "findClass", (Value[]){*object_get_field(current, "parent")}, 1);
current = v18;
}
}
Value v19 = call_method(mod, &*this_ptr, "buildVTable", (Value[]){prog}, 1);
Value vtable = v19;
Value v20 = create_array((Value[]){}, 0);
Value methodNameInitializers = v20;
Value v21 = create_array((Value[]){}, 0);
Value methodFuncInitializers = v21;
Value v22 = create_int(0);
Value i = v22;
while (1) {
Value v23 = call_method(mod, &*object_get_field(vtable, "entries"), "length", (Value[]){}, 0);
Value v24 = call_method(mod, &i, "smaller", (Value[]){v23}, 1);
if (v24.data.int_value == 0) break;
Value v25 = call_method(mod, &*object_get_field(vtable, "entries"), "get", (Value[]){i}, 1);
Value entry = v25;
Value v26 = create_array((Value[]){create_int(34)}, 1);
Value v27 = call_method(mod, &v26, "concat", (Value[]){*object_get_field(entry, "name")}, 1);
Value v28 = create_array((Value[]){create_int(34)}, 1);
Value v29 = call_method(mod, &v27, "concat", (Value[]){v28}, 1);
Value v30 = call_method(mod, &methodNameInitializers, "push", (Value[]){v29}, 1);
methodNameInitializers = v30;
Value v31 = call_method(mod, &methodFuncInitializers, "push", (Value[]){*object_get_field(entry, "function")}, 1);
methodFuncInitializers = v31;
Value v32 = create_int(1);
Value v33 = call_method(mod, &i, "add", (Value[]){v32}, 1);
i = v33;
}
Value v34 = create_array((Value[]){}, 0);
Value parentStr = v34;
Value v35 = create_array((Value[]){}, 0);
Value v36 = call_method(mod, &*object_get_field(*this_ptr, "parent"), "equal", (Value[]){v35}, 1);
if (v36.data.int_value != 0) {
Value v37 = create_array((Value[]){create_int(78), create_int(85), create_int(76), create_int(76)}, 4);
parentStr = v37;
}
else {
Value v38 = create_array((Value[]){create_int(38)}, 1);
Value v39 = call_method(mod, &v38, "concat", (Value[]){*object_get_field(*this_ptr, "parent")}, 1);
Value v40 = create_array((Value[]){create_int(95), create_int(116), create_int(121), create_int(112), create_int(101)}, 5);
Value v41 = call_method(mod, &v39, "concat", (Value[]){v40}, 1);
parentStr = v41;
}
Value v42 = create_array((Value[]){create_int(67), create_int(108), create_int(97), create_int(115), create_int(115), create_int(84), create_int(121), create_int(112), create_int(101), create_int(32)}, 10);
Value v43 = call_method(mod, &v42, "concat", (Value[]){*object_get_field(*this_ptr, "name")}, 1);
Value v44 = create_array((Value[]){create_int(95), create_int(116), create_int(121), create_int(112), create_int(101), create_int(32), create_int(61), create_int(32), create_int(123), create_int(10)}, 10);
Value v45 = call_method(mod, &v43, "concat", (Value[]){v44}, 1);
Value v46 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(98), create_int(97), create_int(115), create_int(101), create_int(32), create_int(61), create_int(32), create_int(123), create_int(10)}, 14);
Value v47 = call_method(mod, &v45, "concat", (Value[]){v46}, 1);
Value v48 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(109), create_int(101), create_int(116), create_int(104), create_int(111), create_int(100), create_int(115), create_int(32), create_int(61), create_int(32), create_int(40), create_int(77), create_int(101), create_int(116), create_int(104), create_int(111), create_int(100), create_int(70), create_int(117), create_int(110), create_int(99), create_int(91), create_int(93), create_int(41), create_int(123)}, 34);
Value v49 = call_method(mod, &v47, "concat", (Value[]){v48}, 1);
Value v50 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v51 = call_method(mod, &methodFuncInitializers, "join", (Value[]){v50}, 1);
Value v52 = call_method(mod, &v49, "concat", (Value[]){v51}, 1);
Value v53 = create_array((Value[]){create_int(125), create_int(44), create_int(10)}, 3);
Value v54 = call_method(mod, &v52, "concat", (Value[]){v53}, 1);
Value v55 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(109), create_int(101), create_int(116), create_int(104), create_int(111), create_int(100), create_int(95), create_int(110), create_int(97), create_int(109), create_int(101), create_int(115), create_int(32), create_int(61), create_int(32), create_int(40), create_int(99), create_int(104), create_int(97), create_int(114), create_int(42), create_int(91), create_int(93), create_int(41), create_int(123)}, 34);
Value v56 = call_method(mod, &v54, "concat", (Value[]){v55}, 1);
Value v57 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v58 = call_method(mod, &methodNameInitializers, "join", (Value[]){v57}, 1);
Value v59 = call_method(mod, &v56, "concat", (Value[]){v58}, 1);
Value v60 = create_array((Value[]){create_int(125), create_int(44), create_int(10)}, 3);
Value v61 = call_method(mod, &v59, "concat", (Value[]){v60}, 1);
Value v62 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(109), create_int(101), create_int(116), create_int(104), create_int(111), create_int(100), create_int(95), create_int(99), create_int(111), create_int(117), create_int(110), create_int(116), create_int(32), create_int(61), create_int(32)}, 24);
Value v63 = call_method(mod, &v61, "concat", (Value[]){v62}, 1);
Value v64 = call_method(mod, &*object_get_field(vtable, "entries"), "length", (Value[]){}, 0);
Value v65 = call_method(mod, &v64, "toString", (Value[]){}, 0);
Value v66 = call_method(mod, &v63, "concat", (Value[]){v65}, 1);
Value v67 = create_array((Value[]){create_int(10)}, 1);
Value v68 = call_method(mod, &v66, "concat", (Value[]){v67}, 1);
Value v69 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(125), create_int(44), create_int(10)}, 7);
Value v70 = call_method(mod, &v68, "concat", (Value[]){v69}, 1);
Value v71 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(110), create_int(97), create_int(109), create_int(101), create_int(32), create_int(61), create_int(32), create_int(34)}, 13);
Value v72 = call_method(mod, &v70, "concat", (Value[]){v71}, 1);
Value v73 = call_method(mod, &v72, "concat", (Value[]){*object_get_field(*this_ptr, "name")}, 1);
Value v74 = create_array((Value[]){create_int(34), create_int(44), create_int(10)}, 3);
Value v75 = call_method(mod, &v73, "concat", (Value[]){v74}, 1);
Value v76 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(112), create_int(97), create_int(114), create_int(101), create_int(110), create_int(116), create_int(32), create_int(61), create_int(32)}, 14);
Value v77 = call_method(mod, &v75, "concat", (Value[]){v76}, 1);
Value v78 = call_method(mod, &v77, "concat", (Value[]){parentStr}, 1);
Value v79 = create_array((Value[]){create_int(44), create_int(10)}, 2);
Value v80 = call_method(mod, &v78, "concat", (Value[]){v79}, 1);
Value v81 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(102), create_int(105), create_int(101), create_int(108), create_int(100), create_int(95), create_int(110), create_int(97), create_int(109), create_int(101), create_int(115), create_int(32), create_int(61), create_int(32), create_int(40), create_int(99), create_int(104), create_int(97), create_int(114), create_int(42), create_int(91), create_int(93), create_int(41), create_int(123)}, 29);
Value v82 = call_method(mod, &v80, "concat", (Value[]){v81}, 1);
Value v83 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v84 = call_method(mod, &fieldNameInitializers, "join", (Value[]){v83}, 1);
Value v85 = call_method(mod, &v82, "concat", (Value[]){v84}, 1);
Value v86 = create_array((Value[]){create_int(125), create_int(44), create_int(10)}, 3);
Value v87 = call_method(mod, &v85, "concat", (Value[]){v86}, 1);
Value v88 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(46), create_int(102), create_int(105), create_int(101), create_int(108), create_int(100), create_int(95), create_int(99), create_int(111), create_int(117), create_int(110), create_int(116), create_int(32), create_int(61), create_int(32)}, 19);
Value v89 = call_method(mod, &v87, "concat", (Value[]){v88}, 1);
Value v90 = call_method(mod, &fieldNameInitializers, "length", (Value[]){}, 0);
Value v91 = call_method(mod, &v90, "toString", (Value[]){}, 0);
Value v92 = call_method(mod, &v89, "concat", (Value[]){v91}, 1);
Value v93 = create_array((Value[]){create_int(10)}, 1);
Value v94 = call_method(mod, &v92, "concat", (Value[]){v93}, 1);
Value v95 = create_array((Value[]){create_int(125), create_int(59), create_int(10)}, 3);
Value v96 = call_method(mod, &v94, "concat", (Value[]){v95}, 1);
return v96;
    return create_null();
}

ClassType ClassDecl_type = {
    .base = {
        .methods = (MethodFunc[]){ClassDecl_init, ClassDecl_compile, ClassDecl_buildVTable, ClassDecl_compileMethod, ClassDecl_compileMethodParamAssignments, ClassDecl_compileClassTypeInitializer},
        .method_names = (char*[]){"init", "compile", "buildVTable", "compileMethod", "compileMethodParamAssignments", "compileClassTypeInitializer"},
        .method_count = 6
    },
    .name = "ClassDecl",
    .parent = &TopLevelASTNode_type,
    .field_names = (char*[]){"name", "parent", "fields", "methods", "filename", "line"},
    .field_count = 6
};

Value VariableDecl_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value name = args[2];
    Value initializer = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "name", name);
object_set_field(&*this_ptr, "initializer", initializer);
    return create_null();
}

Value VariableDecl_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "initializer"), "compile", (Value[]){context}, 1);
Value initVar = v1;
Value v2 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v3 = call_method(mod, &v2, "concat", (Value[]){*object_get_field(*this_ptr, "name")}, 1);
Value v4 = create_array((Value[]){create_int(32), create_int(61), create_int(32)}, 3);
Value v5 = call_method(mod, &v3, "concat", (Value[]){v4}, 1);
Value v6 = call_method(mod, &v5, "concat", (Value[]){initVar}, 1);
Value v7 = create_array((Value[]){create_int(59)}, 1);
Value v8 = call_method(mod, &v6, "concat", (Value[]){v7}, 1);
Value v9 = call_method(mod, &context, "emitLine", (Value[]){v8}, 1);
v9;
Value v10 = create_array((Value[]){}, 0);
return v10;
    return create_null();
}

ClassType VariableDecl_type = {
    .base = {
        .methods = (MethodFunc[]){VariableDecl_init, VariableDecl_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "VariableDecl",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"name", "initializer", "filename", "line"},
    .field_count = 4
};

Value MethodCall_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 5) {
        fprintf(stderr, "init expects 5 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value object = args[2];
    Value method = args[3];
    Value args_ = args[4];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "object", object);
object_set_field(&*this_ptr, "method", method);
object_set_field(&*this_ptr, "args", args_);
    return create_null();
}

Value MethodCall_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "object"), "compile", (Value[]){context}, 1);
Value objectVar = v1;
Value v2 = create_array((Value[]){}, 0);
Value compiledArgs = v2;
Value v3 = create_int(0);
Value i = v3;
while (1) {
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "args"), "length", (Value[]){}, 0);
Value v5 = call_method(mod, &i, "smaller", (Value[]){v4}, 1);
if (v5.data.int_value == 0) break;
Value v6 = call_method(mod, &*object_get_field(*this_ptr, "args"), "get", (Value[]){i}, 1);
Value v7 = call_method(mod, &v6, "compile", (Value[]){context}, 1);
Value v8 = call_method(mod, &compiledArgs, "push", (Value[]){v7}, 1);
compiledArgs = v8;
Value v9 = create_int(1);
Value v10 = call_method(mod, &i, "add", (Value[]){v9}, 1);
i = v10;
}
Value v11 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v11;
Value v12 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v13 = call_method(mod, &v12, "concat", (Value[]){resultVar}, 1);
Value v14 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(97), create_int(108), create_int(108), create_int(95), create_int(109), create_int(101), create_int(116), create_int(104), create_int(111), create_int(100), create_int(40), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(38)}, 21);
Value v15 = call_method(mod, &v13, "concat", (Value[]){v14}, 1);
Value v16 = call_method(mod, &v15, "concat", (Value[]){objectVar}, 1);
Value v17 = create_array((Value[]){create_int(44), create_int(32), create_int(34)}, 3);
Value v18 = call_method(mod, &v16, "concat", (Value[]){v17}, 1);
Value v19 = call_method(mod, &v18, "concat", (Value[]){*object_get_field(*this_ptr, "method")}, 1);
Value v20 = create_array((Value[]){create_int(34), create_int(44), create_int(32), create_int(40), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(91), create_int(93), create_int(41), create_int(123)}, 13);
Value v21 = call_method(mod, &v19, "concat", (Value[]){v20}, 1);
Value v22 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v23 = call_method(mod, &compiledArgs, "join", (Value[]){v22}, 1);
Value v24 = call_method(mod, &v21, "concat", (Value[]){v23}, 1);
Value v25 = create_array((Value[]){create_int(125), create_int(44), create_int(32)}, 3);
Value v26 = call_method(mod, &v24, "concat", (Value[]){v25}, 1);
Value v27 = call_method(mod, &*object_get_field(*this_ptr, "args"), "length", (Value[]){}, 0);
Value v28 = call_method(mod, &v27, "toString", (Value[]){}, 0);
Value v29 = call_method(mod, &v26, "concat", (Value[]){v28}, 1);
Value v30 = create_array((Value[]){create_int(41), create_int(59)}, 2);
Value v31 = call_method(mod, &v29, "concat", (Value[]){v30}, 1);
Value v32 = call_method(mod, &context, "emitLine", (Value[]){v31}, 1);
v32;
return resultVar;
    return create_null();
}

ClassType MethodCall_type = {
    .base = {
        .methods = (MethodFunc[]){MethodCall_init, MethodCall_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "MethodCall",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"object", "method", "args", "filename", "line"},
    .field_count = 5
};

Value FunctionCall_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value name = args[2];
    Value args_ = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "name", name);
object_set_field(&*this_ptr, "args", args_);
    return create_null();
}

Value FunctionCall_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = create_array((Value[]){}, 0);
Value compiledArgs = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "args"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "args"), "get", (Value[]){i}, 1);
Value v6 = call_method(mod, &v5, "compile", (Value[]){context}, 1);
Value v7 = call_method(mod, &compiledArgs, "push", (Value[]){v6}, 1);
compiledArgs = v7;
Value v8 = create_int(1);
Value v9 = call_method(mod, &i, "add", (Value[]){v8}, 1);
i = v9;
}
Value v10 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v10;
Value v11 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v12 = call_method(mod, &v11, "concat", (Value[]){resultVar}, 1);
Value v13 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(109), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(95), create_int(99), create_int(97), create_int(108), create_int(108), create_int(40), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(34)}, 21);
Value v14 = call_method(mod, &v12, "concat", (Value[]){v13}, 1);
Value v15 = call_method(mod, &v14, "concat", (Value[]){*object_get_field(*this_ptr, "name")}, 1);
Value v16 = create_array((Value[]){create_int(34), create_int(44), create_int(32), create_int(40), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(91), create_int(93), create_int(41), create_int(123)}, 13);
Value v17 = call_method(mod, &v15, "concat", (Value[]){v16}, 1);
Value v18 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v19 = call_method(mod, &compiledArgs, "join", (Value[]){v18}, 1);
Value v20 = call_method(mod, &v17, "concat", (Value[]){v19}, 1);
Value v21 = create_array((Value[]){create_int(125), create_int(44), create_int(32)}, 3);
Value v22 = call_method(mod, &v20, "concat", (Value[]){v21}, 1);
Value v23 = call_method(mod, &*object_get_field(*this_ptr, "args"), "length", (Value[]){}, 0);
Value v24 = call_method(mod, &v23, "toString", (Value[]){}, 0);
Value v25 = call_method(mod, &v22, "concat", (Value[]){v24}, 1);
Value v26 = create_array((Value[]){create_int(41), create_int(59)}, 2);
Value v27 = call_method(mod, &v25, "concat", (Value[]){v26}, 1);
Value v28 = call_method(mod, &context, "emitLine", (Value[]){v27}, 1);
v28;
return resultVar;
    return create_null();
}

ClassType FunctionCall_type = {
    .base = {
        .methods = (MethodFunc[]){FunctionCall_init, FunctionCall_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "FunctionCall",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"name", "args", "filename", "line"},
    .field_count = 4
};

Value IfStatement_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 5) {
        fprintf(stderr, "init expects 5 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value condition = args[2];
    Value thenBody = args[3];
    Value elseBody = args[4];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "condition", condition);
object_set_field(&*this_ptr, "thenBody", thenBody);
object_set_field(&*this_ptr, "elseBody", elseBody);
    return create_null();
}

Value IfStatement_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "condition"), "compile", (Value[]){context}, 1);
Value condVar = v1;
Value v2 = create_array((Value[]){create_int(105), create_int(102), create_int(32), create_int(40)}, 4);
Value v3 = call_method(mod, &v2, "concat", (Value[]){condVar}, 1);
Value v4 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(105), create_int(110), create_int(116), create_int(95), create_int(118), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(33), create_int(61), create_int(32), create_int(48), create_int(41), create_int(32), create_int(123)}, 23);
Value v5 = call_method(mod, &v3, "concat", (Value[]){v4}, 1);
Value v6 = call_method(mod, &context, "emitLine", (Value[]){v5}, 1);
v6;
Value v7 = module_call(mod, "CodegenContext", (Value[]){context}, 1);
Value thenContext = v7;
Value v8 = create_int(0);
Value i = v8;
while (1) {
Value v9 = call_method(mod, &*object_get_field(*this_ptr, "thenBody"), "length", (Value[]){}, 0);
Value v10 = call_method(mod, &i, "smaller", (Value[]){v9}, 1);
if (v10.data.int_value == 0) break;
Value v11 = call_method(mod, &*object_get_field(*this_ptr, "thenBody"), "get", (Value[]){i}, 1);
Value v12 = call_method(mod, &v11, "compile", (Value[]){thenContext}, 1);
v12;
Value v13 = create_int(1);
Value v14 = call_method(mod, &i, "add", (Value[]){v13}, 1);
i = v14;
}
Value v15 = call_method(mod, &thenContext, "getCurrentCode", (Value[]){}, 0);
Value v16 = call_method(mod, &context, "emitLine", (Value[]){v15}, 1);
v16;
Value v17 = create_array((Value[]){create_int(125)}, 1);
Value v18 = call_method(mod, &context, "emitLine", (Value[]){v17}, 1);
v18;
Value v19 = call_method(mod, &*object_get_field(*this_ptr, "elseBody"), "length", (Value[]){}, 0);
Value v20 = create_int(0);
Value v21 = call_method(mod, &v19, "greater", (Value[]){v20}, 1);
if (v21.data.int_value != 0) {
Value v22 = create_array((Value[]){create_int(101), create_int(108), create_int(115), create_int(101), create_int(32), create_int(123)}, 6);
Value v23 = call_method(mod, &context, "emitLine", (Value[]){v22}, 1);
v23;
Value v24 = module_call(mod, "CodegenContext", (Value[]){context}, 1);
Value elseContext = v24;
Value v25 = create_int(0);
i = v25;
while (1) {
Value v26 = call_method(mod, &*object_get_field(*this_ptr, "elseBody"), "length", (Value[]){}, 0);
Value v27 = call_method(mod, &i, "smaller", (Value[]){v26}, 1);
if (v27.data.int_value == 0) break;
Value v28 = call_method(mod, &*object_get_field(*this_ptr, "elseBody"), "get", (Value[]){i}, 1);
Value v29 = call_method(mod, &v28, "compile", (Value[]){elseContext}, 1);
v29;
Value v30 = create_int(1);
Value v31 = call_method(mod, &i, "add", (Value[]){v30}, 1);
i = v31;
}
Value v32 = call_method(mod, &elseContext, "getCurrentCode", (Value[]){}, 0);
Value v33 = call_method(mod, &context, "emitLine", (Value[]){v32}, 1);
v33;
Value v34 = create_array((Value[]){create_int(125)}, 1);
Value v35 = call_method(mod, &context, "emitLine", (Value[]){v34}, 1);
v35;
}
Value v36 = create_array((Value[]){}, 0);
return v36;
    return create_null();
}

ClassType IfStatement_type = {
    .base = {
        .methods = (MethodFunc[]){IfStatement_init, IfStatement_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "IfStatement",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"condition", "thenBody", "elseBody", "filename", "line"},
    .field_count = 5
};

Value WhileStatement_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value condition = args[2];
    Value body = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "condition", condition);
object_set_field(&*this_ptr, "body", body);
    return create_null();
}

Value WhileStatement_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = create_array((Value[]){create_int(119), create_int(104), create_int(105), create_int(108), create_int(101), create_int(32), create_int(40), create_int(49), create_int(41), create_int(32), create_int(123)}, 11);
Value v2 = call_method(mod, &context, "emitLine", (Value[]){v1}, 1);
v2;
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "condition"), "compile", (Value[]){context}, 1);
Value condVar = v3;
Value v4 = create_array((Value[]){create_int(105), create_int(102), create_int(32), create_int(40)}, 4);
Value v5 = call_method(mod, &v4, "concat", (Value[]){condVar}, 1);
Value v6 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(105), create_int(110), create_int(116), create_int(95), create_int(118), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(61), create_int(61), create_int(32), create_int(48), create_int(41), create_int(32), create_int(98), create_int(114), create_int(101), create_int(97), create_int(107), create_int(59)}, 28);
Value v7 = call_method(mod, &v5, "concat", (Value[]){v6}, 1);
Value v8 = call_method(mod, &context, "emitLine", (Value[]){v7}, 1);
v8;
Value v9 = module_call(mod, "CodegenContext", (Value[]){context}, 1);
Value bodyContext = v9;
Value v10 = create_int(0);
Value i = v10;
while (1) {
Value v11 = call_method(mod, &*object_get_field(*this_ptr, "body"), "length", (Value[]){}, 0);
Value v12 = call_method(mod, &i, "smaller", (Value[]){v11}, 1);
if (v12.data.int_value == 0) break;
Value v13 = call_method(mod, &*object_get_field(*this_ptr, "body"), "get", (Value[]){i}, 1);
Value v14 = call_method(mod, &v13, "compile", (Value[]){bodyContext}, 1);
v14;
Value v15 = create_int(1);
Value v16 = call_method(mod, &i, "add", (Value[]){v15}, 1);
i = v16;
}
Value v17 = call_method(mod, &bodyContext, "getCurrentCode", (Value[]){}, 0);
Value v18 = call_method(mod, &context, "emitLine", (Value[]){v17}, 1);
v18;
Value v19 = create_array((Value[]){create_int(125)}, 1);
Value v20 = call_method(mod, &context, "emitLine", (Value[]){v19}, 1);
v20;
Value v21 = create_array((Value[]){}, 0);
return v21;
    return create_null();
}

ClassType WhileStatement_type = {
    .base = {
        .methods = (MethodFunc[]){WhileStatement_init, WhileStatement_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "WhileStatement",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"condition", "body", "filename", "line"},
    .field_count = 4
};

Value AssignmentStatement_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value lhs = args[2];
    Value rhs = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "lhs", lhs);
object_set_field(&*this_ptr, "rhs", rhs);
    return create_null();
}

Value AssignmentStatement_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "rhs"), "compile", (Value[]){context}, 1);
Value rhsVar = v1;
Value v2 = instance_of(*object_get_field(*this_ptr, "lhs"), "FieldAccess");
Value v3 = call_method(mod, &v2, "isNull", (Value[]){}, 0);
if (v3.data.int_value != 0) {
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "lhs"), "compile", (Value[]){context}, 1);
Value lhsVar = v4;
Value v5 = create_array((Value[]){create_int(32), create_int(61), create_int(32)}, 3);
Value v6 = call_method(mod, &lhsVar, "concat", (Value[]){v5}, 1);
Value v7 = call_method(mod, &v6, "concat", (Value[]){rhsVar}, 1);
Value v8 = create_array((Value[]){create_int(59)}, 1);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = call_method(mod, &context, "emitLine", (Value[]){v9}, 1);
v10;
}
else {
Value v11 = call_method(mod, &*object_get_field(*object_get_field(*this_ptr, "lhs"), "object"), "compile", (Value[]){context}, 1);
Value objVar = v11;
Value v12 = create_array((Value[]){create_int(111), create_int(98), create_int(106), create_int(101), create_int(99), create_int(116), create_int(95), create_int(115), create_int(101), create_int(116), create_int(95), create_int(102), create_int(105), create_int(101), create_int(108), create_int(100), create_int(40), create_int(38)}, 18);
Value v13 = call_method(mod, &v12, "concat", (Value[]){objVar}, 1);
Value v14 = create_array((Value[]){create_int(44), create_int(32), create_int(34)}, 3);
Value v15 = call_method(mod, &v13, "concat", (Value[]){v14}, 1);
Value v16 = call_method(mod, &v15, "concat", (Value[]){*object_get_field(*object_get_field(*this_ptr, "lhs"), "field")}, 1);
Value v17 = create_array((Value[]){create_int(34), create_int(44), create_int(32)}, 3);
Value v18 = call_method(mod, &v16, "concat", (Value[]){v17}, 1);
Value v19 = call_method(mod, &v18, "concat", (Value[]){rhsVar}, 1);
Value v20 = create_array((Value[]){create_int(41), create_int(59)}, 2);
Value v21 = call_method(mod, &v19, "concat", (Value[]){v20}, 1);
Value v22 = call_method(mod, &context, "emitLine", (Value[]){v21}, 1);
v22;
}
Value v23 = create_array((Value[]){}, 0);
return v23;
    return create_null();
}

ClassType AssignmentStatement_type = {
    .base = {
        .methods = (MethodFunc[]){AssignmentStatement_init, AssignmentStatement_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "AssignmentStatement",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"lhs", "rhs", "filename", "line"},
    .field_count = 4
};

Value ReturnStatement_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value expression = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "expression", expression);
    return create_null();
}

Value ReturnStatement_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "expression"), "compile", (Value[]){context}, 1);
Value exprVar = v1;
Value v2 = create_array((Value[]){create_int(114), create_int(101), create_int(116), create_int(117), create_int(114), create_int(110), create_int(32)}, 7);
Value v3 = call_method(mod, &v2, "concat", (Value[]){exprVar}, 1);
Value v4 = create_array((Value[]){create_int(59)}, 1);
Value v5 = call_method(mod, &v3, "concat", (Value[]){v4}, 1);
Value v6 = call_method(mod, &context, "emitLine", (Value[]){v5}, 1);
v6;
Value v7 = create_array((Value[]){}, 0);
return v7;
    return create_null();
}

ClassType ReturnStatement_type = {
    .base = {
        .methods = (MethodFunc[]){ReturnStatement_init, ReturnStatement_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "ReturnStatement",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"expression", "filename", "line"},
    .field_count = 3
};

Value ExpressionStatement_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value expression = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "expression", expression);
    return create_null();
}

Value ExpressionStatement_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "expression"), "compile", (Value[]){context}, 1);
Value var = v1;
Value v2 = create_array((Value[]){create_int(59)}, 1);
Value v3 = call_method(mod, &var, "concat", (Value[]){v2}, 1);
Value v4 = call_method(mod, &context, "emitLine", (Value[]){v3}, 1);
v4;
Value v5 = create_array((Value[]){}, 0);
return v5;
    return create_null();
}

ClassType ExpressionStatement_type = {
    .base = {
        .methods = (MethodFunc[]){ExpressionStatement_init, ExpressionStatement_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "ExpressionStatement",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"expression", "filename", "line"},
    .field_count = 3
};

Value Identifier_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value name = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "name", name);
    return create_null();
}

Value Identifier_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = create_array((Value[]){create_int(116), create_int(104), create_int(105), create_int(115)}, 4);
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "name"), "equal", (Value[]){v1}, 1);
if (v2.data.int_value != 0) {
Value v3 = create_array((Value[]){create_int(42), create_int(116), create_int(104), create_int(105), create_int(115), create_int(95), create_int(112), create_int(116), create_int(114)}, 9);
return v3;
}
return *object_get_field(*this_ptr, "name");
    return create_null();
}

ClassType Identifier_type = {
    .base = {
        .methods = (MethodFunc[]){Identifier_init, Identifier_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "Identifier",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"name", "filename", "line"},
    .field_count = 3
};

Value IntegerLiteral_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value value = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "value", value);
    return create_null();
}

Value IntegerLiteral_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v1;
Value v2 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v3 = call_method(mod, &v2, "concat", (Value[]){resultVar}, 1);
Value v4 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40)}, 14);
Value v5 = call_method(mod, &v3, "concat", (Value[]){v4}, 1);
Value v6 = call_method(mod, &*object_get_field(*this_ptr, "value"), "toString", (Value[]){}, 0);
Value v7 = call_method(mod, &v5, "concat", (Value[]){v6}, 1);
Value v8 = create_array((Value[]){create_int(41), create_int(59)}, 2);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = call_method(mod, &context, "emitLine", (Value[]){v9}, 1);
v10;
return resultVar;
    return create_null();
}

ClassType IntegerLiteral_type = {
    .base = {
        .methods = (MethodFunc[]){IntegerLiteral_init, IntegerLiteral_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "IntegerLiteral",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"value", "filename", "line"},
    .field_count = 3
};

Value StringLiteral_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value value = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "value", value);
    return create_null();
}

Value StringLiteral_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = create_array((Value[]){}, 0);
Value values = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "value"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = create_array((Value[]){create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40)}, 11);
Value v6 = call_method(mod, &*object_get_field(*this_ptr, "value"), "get", (Value[]){i}, 1);
Value v7 = call_method(mod, &v6, "toString", (Value[]){}, 0);
Value v8 = call_method(mod, &v5, "concat", (Value[]){v7}, 1);
Value v9 = create_array((Value[]){create_int(41)}, 1);
Value v10 = call_method(mod, &v8, "concat", (Value[]){v9}, 1);
Value v11 = call_method(mod, &values, "push", (Value[]){v10}, 1);
values = v11;
Value v12 = create_int(1);
Value v13 = call_method(mod, &i, "add", (Value[]){v12}, 1);
i = v13;
}
Value v14 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v14;
Value v15 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v16 = call_method(mod, &v15, "concat", (Value[]){resultVar}, 1);
Value v17 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(97), create_int(114), create_int(114), create_int(97), create_int(121), create_int(40), create_int(40), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(91), create_int(93), create_int(41), create_int(123)}, 26);
Value v18 = call_method(mod, &v16, "concat", (Value[]){v17}, 1);
Value v19 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v20 = call_method(mod, &values, "join", (Value[]){v19}, 1);
Value v21 = call_method(mod, &v18, "concat", (Value[]){v20}, 1);
Value v22 = create_array((Value[]){create_int(125), create_int(44), create_int(32)}, 3);
Value v23 = call_method(mod, &v21, "concat", (Value[]){v22}, 1);
Value v24 = call_method(mod, &*object_get_field(*this_ptr, "value"), "length", (Value[]){}, 0);
Value v25 = call_method(mod, &v24, "toString", (Value[]){}, 0);
Value v26 = call_method(mod, &v23, "concat", (Value[]){v25}, 1);
Value v27 = create_array((Value[]){create_int(41), create_int(59)}, 2);
Value v28 = call_method(mod, &v26, "concat", (Value[]){v27}, 1);
Value v29 = call_method(mod, &context, "emitLine", (Value[]){v28}, 1);
v29;
return resultVar;
    return create_null();
}

ClassType StringLiteral_type = {
    .base = {
        .methods = (MethodFunc[]){StringLiteral_init, StringLiteral_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "StringLiteral",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"value", "filename", "line"},
    .field_count = 3
};

Value NullLiteral_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "init expects 2 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
    return create_null();
}

Value NullLiteral_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v1;
Value v2 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v3 = call_method(mod, &v2, "concat", (Value[]){resultVar}, 1);
Value v4 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(110), create_int(117), create_int(108), create_int(108), create_int(40), create_int(41), create_int(59)}, 17);
Value v5 = call_method(mod, &v3, "concat", (Value[]){v4}, 1);
Value v6 = call_method(mod, &context, "emitLine", (Value[]){v5}, 1);
v6;
return resultVar;
    return create_null();
}

ClassType NullLiteral_type = {
    .base = {
        .methods = (MethodFunc[]){NullLiteral_init, NullLiteral_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "NullLiteral",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"filename", "line"},
    .field_count = 2
};

Value ArrayLiteral_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 3) {
        fprintf(stderr, "init expects 3 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value elements = args[2];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "elements", elements);
    return create_null();
}

Value ArrayLiteral_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = create_array((Value[]){}, 0);
Value compiledElements = v1;
Value v2 = create_int(0);
Value i = v2;
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "elements"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &i, "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "elements"), "get", (Value[]){i}, 1);
Value v6 = call_method(mod, &v5, "compile", (Value[]){context}, 1);
Value v7 = call_method(mod, &compiledElements, "push", (Value[]){v6}, 1);
compiledElements = v7;
Value v8 = create_int(1);
Value v9 = call_method(mod, &i, "add", (Value[]){v8}, 1);
i = v9;
}
Value v10 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v10;
Value v11 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v12 = call_method(mod, &v11, "concat", (Value[]){resultVar}, 1);
Value v13 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(97), create_int(114), create_int(114), create_int(97), create_int(121), create_int(40), create_int(40), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(91), create_int(93), create_int(41), create_int(123)}, 26);
Value v14 = call_method(mod, &v12, "concat", (Value[]){v13}, 1);
Value v15 = create_array((Value[]){create_int(44), create_int(32)}, 2);
Value v16 = call_method(mod, &compiledElements, "join", (Value[]){v15}, 1);
Value v17 = call_method(mod, &v14, "concat", (Value[]){v16}, 1);
Value v18 = create_array((Value[]){create_int(125), create_int(44), create_int(32)}, 3);
Value v19 = call_method(mod, &v17, "concat", (Value[]){v18}, 1);
Value v20 = call_method(mod, &*object_get_field(*this_ptr, "elements"), "length", (Value[]){}, 0);
Value v21 = call_method(mod, &v20, "toString", (Value[]){}, 0);
Value v22 = call_method(mod, &v19, "concat", (Value[]){v21}, 1);
Value v23 = create_array((Value[]){create_int(41), create_int(59)}, 2);
Value v24 = call_method(mod, &v22, "concat", (Value[]){v23}, 1);
Value v25 = call_method(mod, &context, "emitLine", (Value[]){v24}, 1);
v25;
return resultVar;
    return create_null();
}

ClassType ArrayLiteral_type = {
    .base = {
        .methods = (MethodFunc[]){ArrayLiteral_init, ArrayLiteral_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "ArrayLiteral",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"elements", "filename", "line"},
    .field_count = 3
};

Value InstanceOfExpression_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value object = args[2];
    Value typeName = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "object", object);
object_set_field(&*this_ptr, "typeName", typeName);
    return create_null();
}

Value InstanceOfExpression_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "object"), "compile", (Value[]){context}, 1);
Value objVar = v1;
Value v2 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v2;
Value v3 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v4 = call_method(mod, &v3, "concat", (Value[]){resultVar}, 1);
Value v5 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(105), create_int(110), create_int(115), create_int(116), create_int(97), create_int(110), create_int(99), create_int(101), create_int(95), create_int(111), create_int(102), create_int(40)}, 15);
Value v6 = call_method(mod, &v4, "concat", (Value[]){v5}, 1);
Value v7 = call_method(mod, &v6, "concat", (Value[]){objVar}, 1);
Value v8 = create_array((Value[]){create_int(44), create_int(32), create_int(34)}, 3);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = call_method(mod, &v9, "concat", (Value[]){*object_get_field(*this_ptr, "typeName")}, 1);
Value v11 = create_array((Value[]){create_int(34), create_int(41), create_int(59)}, 3);
Value v12 = call_method(mod, &v10, "concat", (Value[]){v11}, 1);
Value v13 = call_method(mod, &context, "emitLine", (Value[]){v12}, 1);
v13;
return resultVar;
    return create_null();
}

ClassType InstanceOfExpression_type = {
    .base = {
        .methods = (MethodFunc[]){InstanceOfExpression_init, InstanceOfExpression_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "InstanceOfExpression",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"object", "typeName", "filename", "line"},
    .field_count = 4
};

Value FieldAccess_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value object = args[2];
    Value field = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "object", object);
object_set_field(&*this_ptr, "field", field);
    return create_null();
}

Value FieldAccess_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "object"), "compile", (Value[]){context}, 1);
Value objVar = v1;
Value v2 = create_array((Value[]){create_int(42), create_int(111), create_int(98), create_int(106), create_int(101), create_int(99), create_int(116), create_int(95), create_int(103), create_int(101), create_int(116), create_int(95), create_int(102), create_int(105), create_int(101), create_int(108), create_int(100), create_int(40)}, 18);
Value v3 = call_method(mod, &v2, "concat", (Value[]){objVar}, 1);
Value v4 = create_array((Value[]){create_int(44), create_int(32), create_int(34)}, 3);
Value v5 = call_method(mod, &v3, "concat", (Value[]){v4}, 1);
Value v6 = call_method(mod, &v5, "concat", (Value[]){*object_get_field(*this_ptr, "field")}, 1);
Value v7 = create_array((Value[]){create_int(34), create_int(41)}, 2);
Value v8 = call_method(mod, &v6, "concat", (Value[]){v7}, 1);
return v8;
    return create_null();
}

ClassType FieldAccess_type = {
    .base = {
        .methods = (MethodFunc[]){FieldAccess_init, FieldAccess_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "FieldAccess",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"object", "field", "filename", "line"},
    .field_count = 4
};

Value LogicalAndExpression_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value left = args[2];
    Value right = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "left", left);
object_set_field(&*this_ptr, "right", right);
    return create_null();
}

Value LogicalAndExpression_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "left"), "compile", (Value[]){context}, 1);
Value leftVar = v1;
Value v2 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v2;
Value v3 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v4 = call_method(mod, &v3, "concat", (Value[]){resultVar}, 1);
Value v5 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40), create_int(48), create_int(41), create_int(59)}, 17);
Value v6 = call_method(mod, &v4, "concat", (Value[]){v5}, 1);
Value v7 = call_method(mod, &context, "emitLine", (Value[]){v6}, 1);
v7;
Value v8 = create_array((Value[]){create_int(105), create_int(102), create_int(32), create_int(40)}, 4);
Value v9 = call_method(mod, &v8, "concat", (Value[]){leftVar}, 1);
Value v10 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(105), create_int(110), create_int(116), create_int(95), create_int(118), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(33), create_int(61), create_int(32), create_int(48), create_int(41), create_int(32), create_int(123)}, 23);
Value v11 = call_method(mod, &v9, "concat", (Value[]){v10}, 1);
Value v12 = call_method(mod, &context, "emitLine", (Value[]){v11}, 1);
v12;
Value v13 = call_method(mod, &*object_get_field(*this_ptr, "right"), "compile", (Value[]){context}, 1);
Value rightVar = v13;
Value v14 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(105), create_int(102), create_int(32), create_int(40)}, 8);
Value v15 = call_method(mod, &v14, "concat", (Value[]){rightVar}, 1);
Value v16 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(105), create_int(110), create_int(116), create_int(95), create_int(118), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(33), create_int(61), create_int(32), create_int(48), create_int(41), create_int(32), create_int(123)}, 23);
Value v17 = call_method(mod, &v15, "concat", (Value[]){v16}, 1);
Value v18 = call_method(mod, &context, "emitLine", (Value[]){v17}, 1);
v18;
Value v19 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32)}, 8);
Value v20 = call_method(mod, &v19, "concat", (Value[]){resultVar}, 1);
Value v21 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40), create_int(49), create_int(41), create_int(59)}, 17);
Value v22 = call_method(mod, &v20, "concat", (Value[]){v21}, 1);
Value v23 = call_method(mod, &context, "emitLine", (Value[]){v22}, 1);
v23;
Value v24 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(125)}, 5);
Value v25 = call_method(mod, &context, "emitLine", (Value[]){v24}, 1);
v25;
Value v26 = create_array((Value[]){create_int(125)}, 1);
Value v27 = call_method(mod, &context, "emitLine", (Value[]){v26}, 1);
v27;
return resultVar;
    return create_null();
}

ClassType LogicalAndExpression_type = {
    .base = {
        .methods = (MethodFunc[]){LogicalAndExpression_init, LogicalAndExpression_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "LogicalAndExpression",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"left", "right", "filename", "line"},
    .field_count = 4
};

Value LogicalOrExpression_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 4) {
        fprintf(stderr, "init expects 4 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value filename = args[0];
    Value line = args[1];
    Value left = args[2];
    Value right = args[3];    object_set_field(&*this_ptr, "filename", filename);
object_set_field(&*this_ptr, "line", line);
object_set_field(&*this_ptr, "left", left);
object_set_field(&*this_ptr, "right", right);
    return create_null();
}

Value LogicalOrExpression_compile(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "compile expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value context = args[0];    Value v1 = call_method(mod, &*object_get_field(*this_ptr, "left"), "compile", (Value[]){context}, 1);
Value leftVar = v1;
Value v2 = call_method(mod, &context, "newVariable", (Value[]){}, 0);
Value resultVar = v2;
Value v3 = create_array((Value[]){create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32)}, 6);
Value v4 = call_method(mod, &v3, "concat", (Value[]){resultVar}, 1);
Value v5 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40), create_int(48), create_int(41), create_int(59)}, 17);
Value v6 = call_method(mod, &v4, "concat", (Value[]){v5}, 1);
Value v7 = call_method(mod, &context, "emitLine", (Value[]){v6}, 1);
v7;
Value v8 = create_array((Value[]){create_int(105), create_int(102), create_int(32), create_int(40)}, 4);
Value v9 = call_method(mod, &v8, "concat", (Value[]){leftVar}, 1);
Value v10 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(105), create_int(110), create_int(116), create_int(95), create_int(118), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(33), create_int(61), create_int(32), create_int(48), create_int(41), create_int(32), create_int(123)}, 23);
Value v11 = call_method(mod, &v9, "concat", (Value[]){v10}, 1);
Value v12 = call_method(mod, &context, "emitLine", (Value[]){v11}, 1);
v12;
Value v13 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32)}, 4);
Value v14 = call_method(mod, &v13, "concat", (Value[]){resultVar}, 1);
Value v15 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40), create_int(49), create_int(41), create_int(59)}, 17);
Value v16 = call_method(mod, &v14, "concat", (Value[]){v15}, 1);
Value v17 = call_method(mod, &context, "emitLine", (Value[]){v16}, 1);
v17;
Value v18 = create_array((Value[]){create_int(125), create_int(32), create_int(101), create_int(108), create_int(115), create_int(101), create_int(32), create_int(123)}, 8);
Value v19 = call_method(mod, &context, "emitLine", (Value[]){v18}, 1);
v19;
Value v20 = call_method(mod, &*object_get_field(*this_ptr, "right"), "compile", (Value[]){context}, 1);
Value rightVar = v20;
Value v21 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(105), create_int(102), create_int(32), create_int(40)}, 8);
Value v22 = call_method(mod, &v21, "concat", (Value[]){rightVar}, 1);
Value v23 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(46), create_int(105), create_int(110), create_int(116), create_int(95), create_int(118), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(33), create_int(61), create_int(32), create_int(48), create_int(41), create_int(32), create_int(123)}, 23);
Value v24 = call_method(mod, &v22, "concat", (Value[]){v23}, 1);
Value v25 = call_method(mod, &context, "emitLine", (Value[]){v24}, 1);
v25;
Value v26 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32)}, 8);
Value v27 = call_method(mod, &v26, "concat", (Value[]){resultVar}, 1);
Value v28 = create_array((Value[]){create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40), create_int(49), create_int(41), create_int(59)}, 17);
Value v29 = call_method(mod, &v27, "concat", (Value[]){v28}, 1);
Value v30 = call_method(mod, &context, "emitLine", (Value[]){v29}, 1);
v30;
Value v31 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(125)}, 5);
Value v32 = call_method(mod, &context, "emitLine", (Value[]){v31}, 1);
v32;
Value v33 = create_array((Value[]){create_int(125)}, 1);
Value v34 = call_method(mod, &context, "emitLine", (Value[]){v33}, 1);
v34;
return resultVar;
    return create_null();
}

ClassType LogicalOrExpression_type = {
    .base = {
        .methods = (MethodFunc[]){LogicalOrExpression_init, LogicalOrExpression_compile},
        .method_names = (char*[]){"init", "compile"},
        .method_count = 2
    },
    .name = "LogicalOrExpression",
    .parent = &ASTFunctionNode_type,
    .field_names = (char*[]){"left", "right", "filename", "line"},
    .field_count = 4
};

Value Parser_init(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "init expects 2 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value input = args[0];
    Value filename = args[1];    object_set_field(&*this_ptr, "input", input);
object_set_field(&*this_ptr, "filename", filename);
Value v1 = create_int(0);
object_set_field(&*this_ptr, "position", v1);
Value v2 = create_int(1);
object_set_field(&*this_ptr, "line", v2);
    return create_null();
}

Value Parser_accept(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "accept expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value s = args[0];    Value v1 = call_method(mod, &*this_ptr, "skipWhitespace", (Value[]){}, 0);
v1;
Value v2 = call_method(mod, &s, "length", (Value[]){}, 0);
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v2}, 1);
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v5 = call_method(mod, &v3, "smallerEqual", (Value[]){v4}, 1);
Value v6 = create_int(0);
if (v5.data.int_value != 0) {
Value v7 = call_method(mod, &s, "length", (Value[]){}, 0);
Value v8 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v7}, 1);
Value v9 = call_method(mod, &*object_get_field(*this_ptr, "input"), "slice", (Value[]){*object_get_field(*this_ptr, "position"), v8}, 2);
Value v10 = call_method(mod, &v9, "equal", (Value[]){s}, 1);
    if (v10.data.int_value != 0) {
        v6 = create_int(1);
    }
}
if (v6.data.int_value != 0) {
Value v11 = call_method(mod, &s, "length", (Value[]){}, 0);
Value v12 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v11}, 1);
object_set_field(&*this_ptr, "position", v12);
Value v13 = create_int(1);
return v13;
}
Value v14 = create_int(0);
return v14;
    return create_null();
}

Value Parser_expect(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "expect expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value s = args[0];    Value v1 = call_method(mod, &*this_ptr, "accept", (Value[]){s}, 1);
Value v2 = call_method(mod, &v1, "not", (Value[]){}, 0);
if (v2.data.int_value != 0) {
Value v3 = create_array((Value[]){create_int(69), create_int(120), create_int(112), create_int(101), create_int(99), create_int(116), create_int(101), create_int(100), create_int(32), create_int(39)}, 10);
Value v4 = call_method(mod, &v3, "concat", (Value[]){s}, 1);
Value v5 = create_array((Value[]){create_int(39), create_int(32), create_int(97), create_int(116), create_int(32)}, 5);
Value v6 = call_method(mod, &v4, "concat", (Value[]){v5}, 1);
Value v7 = call_method(mod, &v6, "concat", (Value[]){*object_get_field(*this_ptr, "filename")}, 1);
Value v8 = create_array((Value[]){create_int(58)}, 1);
Value v9 = call_method(mod, &v7, "concat", (Value[]){v8}, 1);
Value v10 = call_method(mod, &*object_get_field(*this_ptr, "line"), "toString", (Value[]){}, 0);
Value v11 = call_method(mod, &v9, "concat", (Value[]){v10}, 1);
Value v12 = module_call(mod, "print", (Value[]){v11}, 1);
v12;
Value v13 = create_int(0);
Value v14 = module_call(mod, "assert", (Value[]){v13}, 1);
v14;
}
    return create_null();
}

Value Parser_skipWhitespace(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "skipWhitespace expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    while (1) {
Value v1 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v1}, 1);
if (v2.data.int_value == 0) break;
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value c = v3;
Value v4 = create_int(32);
Value v5 = call_method(mod, &c, "equal", (Value[]){v4}, 1);
Value v6 = create_int(0);
if (v5.data.int_value != 0) {
    v6 = create_int(1);
} else {
Value v7 = create_int(9);
Value v8 = call_method(mod, &c, "equal", (Value[]){v7}, 1);
    if (v8.data.int_value != 0) {
        v6 = create_int(1);
    }
}
Value v9 = create_int(0);
if (v6.data.int_value != 0) {
    v9 = create_int(1);
} else {
Value v10 = create_int(10);
Value v11 = call_method(mod, &c, "equal", (Value[]){v10}, 1);
    if (v11.data.int_value != 0) {
        v9 = create_int(1);
    }
}
Value v12 = create_int(0);
if (v9.data.int_value != 0) {
    v12 = create_int(1);
} else {
Value v13 = create_int(13);
Value v14 = call_method(mod, &c, "equal", (Value[]){v13}, 1);
    if (v14.data.int_value != 0) {
        v12 = create_int(1);
    }
}
if (v12.data.int_value != 0) {
Value v15 = create_int(10);
Value v16 = call_method(mod, &c, "equal", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = create_int(1);
Value v18 = call_method(mod, &*object_get_field(*this_ptr, "line"), "add", (Value[]){v17}, 1);
object_set_field(&*this_ptr, "line", v18);
}
Value v19 = create_int(1);
Value v20 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v19}, 1);
object_set_field(&*this_ptr, "position", v20);
}
else {
break;
}
}
    return create_null();
}

Value Parser_skipComments(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "skipComments expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    while (1) {
Value v1 = create_int(1);
if (v1.data.int_value == 0) break;
Value v2 = call_method(mod, &*this_ptr, "skipWhitespace", (Value[]){}, 0);
v2;
Value v3 = create_array((Value[]){create_int(47), create_int(47)}, 2);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
while (1) {
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v6 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v5}, 1);
Value v7 = create_int(0);
if (v6.data.int_value != 0) {
Value v8 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v9 = create_int(10);
Value v10 = call_method(mod, &v8, "notEqual", (Value[]){v9}, 1);
    if (v10.data.int_value != 0) {
        v7 = create_int(1);
    }
}
if (v7.data.int_value == 0) break;
Value v11 = create_int(1);
Value v12 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v11}, 1);
object_set_field(&*this_ptr, "position", v12);
}
}
else {
Value v13 = create_array((Value[]){create_int(47), create_int(42)}, 2);
Value v14 = call_method(mod, &*this_ptr, "accept", (Value[]){v13}, 1);
if (v14.data.int_value != 0) {
while (1) {
Value v15 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v16 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v15}, 1);
Value v17 = create_int(0);
if (v16.data.int_value != 0) {
Value v18 = create_array((Value[]){create_int(42), create_int(47)}, 2);
Value v19 = call_method(mod, &*this_ptr, "accept", (Value[]){v18}, 1);
Value v20 = call_method(mod, &v19, "not", (Value[]){}, 0);
    if (v20.data.int_value != 0) {
        v17 = create_int(1);
    }
}
if (v17.data.int_value == 0) break;
Value v21 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v22 = create_int(10);
Value v23 = call_method(mod, &v21, "equal", (Value[]){v22}, 1);
if (v23.data.int_value != 0) {
Value v24 = create_int(1);
Value v25 = call_method(mod, &*object_get_field(*this_ptr, "line"), "add", (Value[]){v24}, 1);
object_set_field(&*this_ptr, "line", v25);
}
Value v26 = create_int(1);
Value v27 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v26}, 1);
object_set_field(&*this_ptr, "position", v27);
}
}
else {
break;
}
}
}
    return create_null();
}

Value Parser_parseIdentifier(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseIdentifier expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "skipWhitespace", (Value[]){}, 0);
v1;
Value v2 = call_method(mod, &*this_ptr, "skipComments", (Value[]){}, 0);
v2;
Value start = *object_get_field(*this_ptr, "position");
while (1) {
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v3}, 1);
if (v4.data.int_value == 0) break;
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value c = v5;
Value v6 = create_int(97);
Value v7 = call_method(mod, &c, "greaterEqual", (Value[]){v6}, 1);
Value v8 = create_int(0);
if (v7.data.int_value != 0) {
Value v9 = create_int(122);
Value v10 = call_method(mod, &c, "smallerEqual", (Value[]){v9}, 1);
    if (v10.data.int_value != 0) {
        v8 = create_int(1);
    }
}
Value v11 = create_int(0);
if (v8.data.int_value != 0) {
    v11 = create_int(1);
} else {
Value v12 = create_int(65);
Value v13 = call_method(mod, &c, "greaterEqual", (Value[]){v12}, 1);
Value v14 = create_int(0);
if (v13.data.int_value != 0) {
Value v15 = create_int(90);
Value v16 = call_method(mod, &c, "smallerEqual", (Value[]){v15}, 1);
    if (v16.data.int_value != 0) {
        v14 = create_int(1);
    }
}
    if (v14.data.int_value != 0) {
        v11 = create_int(1);
    }
}
Value v17 = create_int(0);
if (v11.data.int_value != 0) {
    v17 = create_int(1);
} else {
Value v18 = create_int(95);
Value v19 = call_method(mod, &c, "equal", (Value[]){v18}, 1);
    if (v19.data.int_value != 0) {
        v17 = create_int(1);
    }
}
Value v20 = create_int(0);
if (v17.data.int_value != 0) {
    v20 = create_int(1);
} else {
Value v21 = call_method(mod, &*object_get_field(*this_ptr, "position"), "greater", (Value[]){start}, 1);
Value v22 = create_int(0);
if (v21.data.int_value != 0) {
Value v23 = create_int(48);
Value v24 = call_method(mod, &c, "greaterEqual", (Value[]){v23}, 1);
    if (v24.data.int_value != 0) {
        v22 = create_int(1);
    }
}
Value v25 = create_int(0);
if (v22.data.int_value != 0) {
Value v26 = create_int(57);
Value v27 = call_method(mod, &c, "smallerEqual", (Value[]){v26}, 1);
    if (v27.data.int_value != 0) {
        v25 = create_int(1);
    }
}
    if (v25.data.int_value != 0) {
        v20 = create_int(1);
    }
}
if (v20.data.int_value != 0) {
Value v28 = create_int(1);
Value v29 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v28}, 1);
object_set_field(&*this_ptr, "position", v29);
}
else {
break;
}
}
Value v30 = call_method(mod, &start, "equal", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
if (v30.data.int_value != 0) {
Value v31 = create_array((Value[]){create_int(69), create_int(120), create_int(112), create_int(101), create_int(99), create_int(116), create_int(101), create_int(100), create_int(32), create_int(105), create_int(100), create_int(101), create_int(110), create_int(116), create_int(105), create_int(102), create_int(105), create_int(101), create_int(114), create_int(32), create_int(97), create_int(116), create_int(32)}, 23);
Value v32 = call_method(mod, &v31, "concat", (Value[]){*object_get_field(*this_ptr, "filename")}, 1);
Value v33 = create_array((Value[]){create_int(58)}, 1);
Value v34 = call_method(mod, &v32, "concat", (Value[]){v33}, 1);
Value v35 = call_method(mod, &*object_get_field(*this_ptr, "line"), "toString", (Value[]){}, 0);
Value v36 = call_method(mod, &v34, "concat", (Value[]){v35}, 1);
Value v37 = module_call(mod, "print", (Value[]){v36}, 1);
v37;
Value v38 = create_int(0);
Value v39 = module_call(mod, "assert", (Value[]){v38}, 1);
v39;
}
Value v40 = call_method(mod, &*object_get_field(*this_ptr, "input"), "slice", (Value[]){start, *object_get_field(*this_ptr, "position")}, 2);
return v40;
    return create_null();
}

Value Parser_parse(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parse expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){}, 0);
Value nodes = v1;
while (1) {
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v2}, 1);
if (v3.data.int_value == 0) break;
Value v4 = call_method(mod, &*this_ptr, "skipWhitespace", (Value[]){}, 0);
v4;
Value v5 = call_method(mod, &*this_ptr, "skipComments", (Value[]){}, 0);
v5;
Value v6 = create_array((Value[]){create_int(102), create_int(117), create_int(110), create_int(99), create_int(116), create_int(105), create_int(111), create_int(110)}, 8);
Value v7 = call_method(mod, &*this_ptr, "accept", (Value[]){v6}, 1);
if (v7.data.int_value != 0) {
Value v8 = call_method(mod, &*this_ptr, "parseFunctionDecl", (Value[]){}, 0);
Value v9 = call_method(mod, &nodes, "push", (Value[]){v8}, 1);
nodes = v9;
}
else {
Value v10 = create_array((Value[]){create_int(99), create_int(108), create_int(97), create_int(115), create_int(115)}, 5);
Value v11 = call_method(mod, &*this_ptr, "accept", (Value[]){v10}, 1);
if (v11.data.int_value != 0) {
Value v12 = call_method(mod, &*this_ptr, "parseClassDecl", (Value[]){}, 0);
Value v13 = call_method(mod, &nodes, "push", (Value[]){v12}, 1);
nodes = v13;
}
else {
break;
}
}
}
Value v14 = create_int(1);
Value v15 = module_call(mod, "Program", (Value[]){*object_get_field(*this_ptr, "filename"), v14, nodes}, 3);
return v15;
    return create_null();
}

Value Parser_parseFunctionDecl(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseFunctionDecl expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value name = v1;
Value v2 = create_array((Value[]){}, 0);
Value params = v2;
Value v3 = create_array((Value[]){create_int(40)}, 1);
Value v4 = call_method(mod, &*this_ptr, "expect", (Value[]){v3}, 1);
v4;
Value v5 = create_array((Value[]){create_int(41)}, 1);
Value v6 = call_method(mod, &*this_ptr, "accept", (Value[]){v5}, 1);
Value v7 = call_method(mod, &v6, "not", (Value[]){}, 0);
if (v7.data.int_value != 0) {
while (1) {
Value v8 = create_int(1);
if (v8.data.int_value == 0) break;
Value v9 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value v10 = call_method(mod, &params, "push", (Value[]){v9}, 1);
params = v10;
Value v11 = create_array((Value[]){create_int(44)}, 1);
Value v12 = call_method(mod, &*this_ptr, "accept", (Value[]){v11}, 1);
Value v13 = call_method(mod, &v12, "not", (Value[]){}, 0);
if (v13.data.int_value != 0) {
break;
}
}
Value v14 = create_array((Value[]){create_int(41)}, 1);
Value v15 = call_method(mod, &*this_ptr, "expect", (Value[]){v14}, 1);
v15;
}
Value v16 = create_array((Value[]){}, 0);
Value body = v16;
Value v17 = create_array((Value[]){create_int(123)}, 1);
Value v18 = call_method(mod, &*this_ptr, "expect", (Value[]){v17}, 1);
v18;
while (1) {
Value v19 = create_array((Value[]){create_int(125)}, 1);
Value v20 = call_method(mod, &*this_ptr, "accept", (Value[]){v19}, 1);
Value v21 = call_method(mod, &v20, "not", (Value[]){}, 0);
if (v21.data.int_value == 0) break;
Value v22 = call_method(mod, &*this_ptr, "parseStatement", (Value[]){}, 0);
Value v23 = call_method(mod, &body, "push", (Value[]){v22}, 1);
body = v23;
}
Value v24 = module_call(mod, "FunctionDecl", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), name, params, body}, 5);
return v24;
    return create_null();
}

Value Parser_parseClassDecl(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseClassDecl expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value name = v1;
Value v2 = create_array((Value[]){}, 0);
Value parent = v2;
Value v3 = create_array((Value[]){create_int(58)}, 1);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
Value v5 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
parent = v5;
}
Value v6 = create_array((Value[]){}, 0);
Value fields = v6;
Value v7 = create_array((Value[]){}, 0);
Value methods = v7;
Value v8 = create_array((Value[]){create_int(123)}, 1);
Value v9 = call_method(mod, &*this_ptr, "expect", (Value[]){v8}, 1);
v9;
while (1) {
Value v10 = create_array((Value[]){create_int(125)}, 1);
Value v11 = call_method(mod, &*this_ptr, "accept", (Value[]){v10}, 1);
Value v12 = call_method(mod, &v11, "not", (Value[]){}, 0);
if (v12.data.int_value == 0) break;
Value v13 = create_array((Value[]){create_int(102), create_int(117), create_int(110), create_int(99), create_int(116), create_int(105), create_int(111), create_int(110)}, 8);
Value v14 = call_method(mod, &*this_ptr, "accept", (Value[]){v13}, 1);
if (v14.data.int_value != 0) {
Value v15 = call_method(mod, &*this_ptr, "parseFunctionDecl", (Value[]){}, 0);
Value v16 = call_method(mod, &methods, "push", (Value[]){v15}, 1);
methods = v16;
}
else {
Value v17 = create_array((Value[]){create_int(97), create_int(117), create_int(116), create_int(111)}, 4);
Value v18 = call_method(mod, &*this_ptr, "expect", (Value[]){v17}, 1);
v18;
Value v19 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value v20 = call_method(mod, &fields, "push", (Value[]){v19}, 1);
fields = v20;
Value v21 = create_array((Value[]){create_int(59)}, 1);
Value v22 = call_method(mod, &*this_ptr, "expect", (Value[]){v21}, 1);
v22;
}
}
Value v23 = module_call(mod, "ClassDecl", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), name, parent, fields, methods}, 6);
return v23;
    return create_null();
}

Value Parser_parseStatement(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseStatement expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "skipWhitespace", (Value[]){}, 0);
v1;
Value v2 = call_method(mod, &*this_ptr, "skipComments", (Value[]){}, 0);
v2;
Value v3 = create_array((Value[]){create_int(105), create_int(102)}, 2);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
Value v5 = call_method(mod, &*this_ptr, "parseIfStatement", (Value[]){}, 0);
return v5;
}
else {
Value v6 = create_array((Value[]){create_int(119), create_int(104), create_int(105), create_int(108), create_int(101)}, 5);
Value v7 = call_method(mod, &*this_ptr, "accept", (Value[]){v6}, 1);
if (v7.data.int_value != 0) {
Value v8 = call_method(mod, &*this_ptr, "parseWhileStatement", (Value[]){}, 0);
return v8;
}
else {
Value v9 = create_array((Value[]){create_int(114), create_int(101), create_int(116), create_int(117), create_int(114), create_int(110)}, 6);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
if (v10.data.int_value != 0) {
Value v11 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value expr = v11;
Value v12 = create_array((Value[]){create_int(59)}, 1);
Value v13 = call_method(mod, &*this_ptr, "expect", (Value[]){v12}, 1);
v13;
Value v14 = module_call(mod, "ReturnStatement", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), expr}, 3);
return v14;
}
else {
Value v15 = create_array((Value[]){create_int(97), create_int(117), create_int(116), create_int(111)}, 4);
Value v16 = call_method(mod, &*this_ptr, "accept", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value name = v17;
Value v18 = create_array((Value[]){create_int(61)}, 1);
Value v19 = call_method(mod, &*this_ptr, "expect", (Value[]){v18}, 1);
v19;
Value v20 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value initializer = v20;
Value v21 = create_array((Value[]){create_int(59)}, 1);
Value v22 = call_method(mod, &*this_ptr, "expect", (Value[]){v21}, 1);
v22;
Value v23 = module_call(mod, "VariableDecl", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), name, initializer}, 4);
return v23;
}
else {
Value v24 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value expr = v24;
Value v25 = create_array((Value[]){create_int(61)}, 1);
Value v26 = call_method(mod, &*this_ptr, "accept", (Value[]){v25}, 1);
if (v26.data.int_value != 0) {
Value v27 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value rhs = v27;
Value v28 = create_array((Value[]){create_int(59)}, 1);
Value v29 = call_method(mod, &*this_ptr, "expect", (Value[]){v28}, 1);
v29;
Value v30 = module_call(mod, "AssignmentStatement", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), expr, rhs}, 4);
return v30;
}
else {
Value v31 = create_array((Value[]){create_int(59)}, 1);
Value v32 = call_method(mod, &*this_ptr, "expect", (Value[]){v31}, 1);
v32;
Value v33 = module_call(mod, "ExpressionStatement", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), expr}, 3);
return v33;
}
}
}
}
}
    return create_null();
}

Value Parser_parseIfStatement(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseIfStatement expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){create_int(40)}, 1);
Value v2 = call_method(mod, &*this_ptr, "expect", (Value[]){v1}, 1);
v2;
Value v3 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value condition = v3;
Value v4 = create_array((Value[]){create_int(41)}, 1);
Value v5 = call_method(mod, &*this_ptr, "expect", (Value[]){v4}, 1);
v5;
Value v6 = create_array((Value[]){}, 0);
Value thenBody = v6;
Value v7 = create_array((Value[]){create_int(123)}, 1);
Value v8 = call_method(mod, &*this_ptr, "expect", (Value[]){v7}, 1);
v8;
while (1) {
Value v9 = create_array((Value[]){create_int(125)}, 1);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
Value v11 = call_method(mod, &v10, "not", (Value[]){}, 0);
if (v11.data.int_value == 0) break;
Value v12 = call_method(mod, &*this_ptr, "parseStatement", (Value[]){}, 0);
Value v13 = call_method(mod, &thenBody, "push", (Value[]){v12}, 1);
thenBody = v13;
}
Value v14 = create_array((Value[]){}, 0);
Value elseBody = v14;
Value v15 = create_array((Value[]){create_int(101), create_int(108), create_int(115), create_int(101)}, 4);
Value v16 = call_method(mod, &*this_ptr, "accept", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = create_array((Value[]){create_int(105), create_int(102)}, 2);
Value v18 = call_method(mod, &*this_ptr, "accept", (Value[]){v17}, 1);
if (v18.data.int_value != 0) {
Value v19 = call_method(mod, &*this_ptr, "parseIfStatement", (Value[]){}, 0);
Value v20 = call_method(mod, &elseBody, "push", (Value[]){v19}, 1);
elseBody = v20;
}
else {
Value v21 = create_array((Value[]){create_int(123)}, 1);
Value v22 = call_method(mod, &*this_ptr, "expect", (Value[]){v21}, 1);
v22;
while (1) {
Value v23 = create_array((Value[]){create_int(125)}, 1);
Value v24 = call_method(mod, &*this_ptr, "accept", (Value[]){v23}, 1);
Value v25 = call_method(mod, &v24, "not", (Value[]){}, 0);
if (v25.data.int_value == 0) break;
Value v26 = call_method(mod, &*this_ptr, "parseStatement", (Value[]){}, 0);
Value v27 = call_method(mod, &elseBody, "push", (Value[]){v26}, 1);
elseBody = v27;
}
}
}
Value v28 = module_call(mod, "IfStatement", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), condition, thenBody, elseBody}, 5);
return v28;
    return create_null();
}

Value Parser_parseWhileStatement(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseWhileStatement expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){create_int(40)}, 1);
Value v2 = call_method(mod, &*this_ptr, "expect", (Value[]){v1}, 1);
v2;
Value v3 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value condition = v3;
Value v4 = create_array((Value[]){create_int(41)}, 1);
Value v5 = call_method(mod, &*this_ptr, "expect", (Value[]){v4}, 1);
v5;
Value v6 = create_array((Value[]){}, 0);
Value body = v6;
Value v7 = create_array((Value[]){create_int(123)}, 1);
Value v8 = call_method(mod, &*this_ptr, "expect", (Value[]){v7}, 1);
v8;
while (1) {
Value v9 = create_array((Value[]){create_int(125)}, 1);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
Value v11 = call_method(mod, &v10, "not", (Value[]){}, 0);
if (v11.data.int_value == 0) break;
Value v12 = call_method(mod, &*this_ptr, "parseStatement", (Value[]){}, 0);
Value v13 = call_method(mod, &body, "push", (Value[]){v12}, 1);
body = v13;
}
Value v14 = module_call(mod, "WhileStatement", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), condition, body}, 4);
return v14;
    return create_null();
}

Value Parser_parseExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseLogicalOrExpression", (Value[]){}, 0);
return v1;
    return create_null();
}

Value Parser_parseLogicalOrExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseLogicalOrExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseLogicalAndExpression", (Value[]){}, 0);
Value left = v1;
while (1) {
Value v2 = create_array((Value[]){create_int(124), create_int(124)}, 2);
Value v3 = call_method(mod, &*this_ptr, "accept", (Value[]){v2}, 1);
if (v3.data.int_value == 0) break;
Value v4 = call_method(mod, &*this_ptr, "parseLogicalAndExpression", (Value[]){}, 0);
Value right = v4;
Value v5 = module_call(mod, "LogicalOrExpression", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, right}, 4);
left = v5;
}
return left;
    return create_null();
}

Value Parser_parseLogicalAndExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseLogicalAndExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseEqualityExpression", (Value[]){}, 0);
Value left = v1;
while (1) {
Value v2 = create_array((Value[]){create_int(38), create_int(38)}, 2);
Value v3 = call_method(mod, &*this_ptr, "accept", (Value[]){v2}, 1);
if (v3.data.int_value == 0) break;
Value v4 = call_method(mod, &*this_ptr, "parseEqualityExpression", (Value[]){}, 0);
Value right = v4;
Value v5 = module_call(mod, "LogicalAndExpression", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, right}, 4);
left = v5;
}
return left;
    return create_null();
}

Value Parser_parseEqualityExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseEqualityExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseRelationalExpression", (Value[]){}, 0);
Value left = v1;
while (1) {
Value v2 = create_int(1);
if (v2.data.int_value == 0) break;
Value v3 = create_array((Value[]){create_int(61), create_int(61)}, 2);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
Value v5 = call_method(mod, &*this_ptr, "parseRelationalExpression", (Value[]){}, 0);
Value right = v5;
Value v6 = create_array((Value[]){create_int(101), create_int(113), create_int(117), create_int(97), create_int(108)}, 5);
Value v7 = create_array((Value[]){right}, 1);
Value v8 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v6, v7}, 5);
left = v8;
}
else {
Value v9 = create_array((Value[]){create_int(33), create_int(61)}, 2);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
if (v10.data.int_value != 0) {
Value v11 = call_method(mod, &*this_ptr, "parseRelationalExpression", (Value[]){}, 0);
Value right = v11;
Value v12 = create_array((Value[]){create_int(110), create_int(111), create_int(116), create_int(69), create_int(113), create_int(117), create_int(97), create_int(108)}, 8);
Value v13 = create_array((Value[]){right}, 1);
Value v14 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v12, v13}, 5);
left = v14;
}
else {
break;
}
}
}
return left;
    return create_null();
}

Value Parser_parseRelationalExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseRelationalExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseAdditiveExpression", (Value[]){}, 0);
Value left = v1;
while (1) {
Value v2 = create_int(1);
if (v2.data.int_value == 0) break;
Value v3 = create_array((Value[]){create_int(60), create_int(61)}, 2);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
Value v5 = call_method(mod, &*this_ptr, "parseAdditiveExpression", (Value[]){}, 0);
Value right = v5;
Value v6 = create_array((Value[]){create_int(115), create_int(109), create_int(97), create_int(108), create_int(108), create_int(101), create_int(114), create_int(69), create_int(113), create_int(117), create_int(97), create_int(108)}, 12);
Value v7 = create_array((Value[]){right}, 1);
Value v8 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v6, v7}, 5);
left = v8;
}
else {
Value v9 = create_array((Value[]){create_int(62), create_int(61)}, 2);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
if (v10.data.int_value != 0) {
Value v11 = call_method(mod, &*this_ptr, "parseAdditiveExpression", (Value[]){}, 0);
Value right = v11;
Value v12 = create_array((Value[]){create_int(103), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(114), create_int(69), create_int(113), create_int(117), create_int(97), create_int(108)}, 12);
Value v13 = create_array((Value[]){right}, 1);
Value v14 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v12, v13}, 5);
left = v14;
}
else {
Value v15 = create_array((Value[]){create_int(60)}, 1);
Value v16 = call_method(mod, &*this_ptr, "accept", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = call_method(mod, &*this_ptr, "parseAdditiveExpression", (Value[]){}, 0);
Value right = v17;
Value v18 = create_array((Value[]){create_int(115), create_int(109), create_int(97), create_int(108), create_int(108), create_int(101), create_int(114)}, 7);
Value v19 = create_array((Value[]){right}, 1);
Value v20 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v18, v19}, 5);
left = v20;
}
else {
Value v21 = create_array((Value[]){create_int(62)}, 1);
Value v22 = call_method(mod, &*this_ptr, "accept", (Value[]){v21}, 1);
if (v22.data.int_value != 0) {
Value v23 = call_method(mod, &*this_ptr, "parseAdditiveExpression", (Value[]){}, 0);
Value right = v23;
Value v24 = create_array((Value[]){create_int(103), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(114)}, 7);
Value v25 = create_array((Value[]){right}, 1);
Value v26 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v24, v25}, 5);
left = v26;
}
else {
break;
}
}
}
}
}
return left;
    return create_null();
}

Value Parser_parseAdditiveExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseAdditiveExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseMultiplicativeExpression", (Value[]){}, 0);
Value left = v1;
while (1) {
Value v2 = create_int(1);
if (v2.data.int_value == 0) break;
Value v3 = create_array((Value[]){create_int(43)}, 1);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
Value v5 = call_method(mod, &*this_ptr, "parseMultiplicativeExpression", (Value[]){}, 0);
Value right = v5;
Value v6 = create_array((Value[]){create_int(97), create_int(100), create_int(100)}, 3);
Value v7 = create_array((Value[]){right}, 1);
Value v8 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v6, v7}, 5);
left = v8;
}
else {
Value v9 = create_array((Value[]){create_int(45)}, 1);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
if (v10.data.int_value != 0) {
Value v11 = call_method(mod, &*this_ptr, "parseMultiplicativeExpression", (Value[]){}, 0);
Value right = v11;
Value v12 = create_array((Value[]){create_int(115), create_int(117), create_int(98)}, 3);
Value v13 = create_array((Value[]){right}, 1);
Value v14 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v12, v13}, 5);
left = v14;
}
else {
Value v15 = create_array((Value[]){create_int(126)}, 1);
Value v16 = call_method(mod, &*this_ptr, "accept", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = call_method(mod, &*this_ptr, "parseMultiplicativeExpression", (Value[]){}, 0);
Value right = v17;
Value v18 = create_array((Value[]){create_int(99), create_int(111), create_int(110), create_int(99), create_int(97), create_int(116)}, 6);
Value v19 = create_array((Value[]){right}, 1);
Value v20 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v18, v19}, 5);
left = v20;
}
else {
break;
}
}
}
}
return left;
    return create_null();
}

Value Parser_parseMultiplicativeExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseMultiplicativeExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "parseUnaryExpression", (Value[]){}, 0);
Value left = v1;
while (1) {
Value v2 = create_int(1);
if (v2.data.int_value == 0) break;
Value v3 = create_array((Value[]){create_int(42)}, 1);
Value v4 = call_method(mod, &*this_ptr, "accept", (Value[]){v3}, 1);
if (v4.data.int_value != 0) {
Value v5 = call_method(mod, &*this_ptr, "parseUnaryExpression", (Value[]){}, 0);
Value right = v5;
Value v6 = create_array((Value[]){create_int(109), create_int(117), create_int(108)}, 3);
Value v7 = create_array((Value[]){right}, 1);
Value v8 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v6, v7}, 5);
left = v8;
}
else {
Value v9 = create_array((Value[]){create_int(47)}, 1);
Value v10 = call_method(mod, &*this_ptr, "accept", (Value[]){v9}, 1);
if (v10.data.int_value != 0) {
Value v11 = call_method(mod, &*this_ptr, "parseUnaryExpression", (Value[]){}, 0);
Value right = v11;
Value v12 = create_array((Value[]){create_int(100), create_int(105), create_int(118)}, 3);
Value v13 = create_array((Value[]){right}, 1);
Value v14 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, v12, v13}, 5);
left = v14;
}
else {
break;
}
}
}
return left;
    return create_null();
}

Value Parser_parseUnaryExpression(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseUnaryExpression expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){create_int(33)}, 1);
Value v2 = call_method(mod, &*this_ptr, "accept", (Value[]){v1}, 1);
if (v2.data.int_value != 0) {
Value v3 = call_method(mod, &*this_ptr, "parseUnaryExpression", (Value[]){}, 0);
Value operand = v3;
Value v4 = create_array((Value[]){create_int(110), create_int(111), create_int(116)}, 3);
Value v5 = create_array((Value[]){}, 0);
Value v6 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), operand, v4, v5}, 5);
return v6;
}
else {
Value v7 = create_array((Value[]){create_int(45)}, 1);
Value v8 = call_method(mod, &*this_ptr, "accept", (Value[]){v7}, 1);
if (v8.data.int_value != 0) {
Value v9 = call_method(mod, &*this_ptr, "parseUnaryExpression", (Value[]){}, 0);
Value operand = v9;
Value v10 = create_array((Value[]){create_int(110), create_int(101), create_int(103), create_int(97), create_int(116), create_int(101)}, 6);
Value v11 = create_array((Value[]){}, 0);
Value v12 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), operand, v10, v11}, 5);
return v12;
}
else {
Value v13 = call_method(mod, &*this_ptr, "parsePrimary", (Value[]){}, 0);
return v13;
}
}
    return create_null();
}

Value Parser_parseInstanceOf(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "parseInstanceOf expects 1 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value left = args[0];    Value v1 = create_array((Value[]){create_int(40)}, 1);
Value v2 = call_method(mod, &*this_ptr, "expect", (Value[]){v1}, 1);
v2;
Value v3 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value typeName = v3;
Value v4 = create_array((Value[]){create_int(41)}, 1);
Value v5 = call_method(mod, &*this_ptr, "expect", (Value[]){v4}, 1);
v5;
Value v6 = module_call(mod, "InstanceOfExpression", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), left, typeName}, 4);
return v6;
    return create_null();
}

Value Parser_parsePrimary(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parsePrimary expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = call_method(mod, &*this_ptr, "skipWhitespace", (Value[]){}, 0);
v1;
Value v2 = call_method(mod, &*this_ptr, "skipComments", (Value[]){}, 0);
v2;
Value v3 = create_null();
Value expr = v3;
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v4}, 1);
Value v6 = create_int(0);
if (v5.data.int_value != 0) {
Value v7 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v8 = create_int(48);
Value v9 = call_method(mod, &v7, "greaterEqual", (Value[]){v8}, 1);
    if (v9.data.int_value != 0) {
        v6 = create_int(1);
    }
}
Value v10 = create_int(0);
if (v6.data.int_value != 0) {
Value v11 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v12 = create_int(57);
Value v13 = call_method(mod, &v11, "smallerEqual", (Value[]){v12}, 1);
    if (v13.data.int_value != 0) {
        v10 = create_int(1);
    }
}
if (v10.data.int_value != 0) {
Value v14 = call_method(mod, &*this_ptr, "parseIntegerLiteral", (Value[]){}, 0);
expr = v14;
}
else {
Value v15 = create_array((Value[]){create_int(34)}, 1);
Value v16 = call_method(mod, &*this_ptr, "accept", (Value[]){v15}, 1);
if (v16.data.int_value != 0) {
Value v17 = call_method(mod, &*this_ptr, "parseStringLiteral", (Value[]){}, 0);
expr = v17;
}
else {
Value v18 = create_array((Value[]){create_int(110), create_int(117), create_int(108), create_int(108)}, 4);
Value v19 = call_method(mod, &*this_ptr, "accept", (Value[]){v18}, 1);
if (v19.data.int_value != 0) {
Value v20 = module_call(mod, "NullLiteral", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line")}, 2);
expr = v20;
}
else {
Value v21 = create_array((Value[]){create_int(91)}, 1);
Value v22 = call_method(mod, &*this_ptr, "accept", (Value[]){v21}, 1);
if (v22.data.int_value != 0) {
Value v23 = call_method(mod, &*this_ptr, "parseArrayLiteral", (Value[]){}, 0);
expr = v23;
}
else {
Value v24 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value id = v24;
Value v25 = create_array((Value[]){create_int(40)}, 1);
Value v26 = call_method(mod, &*this_ptr, "accept", (Value[]){v25}, 1);
if (v26.data.int_value != 0) {
Value v27 = create_array((Value[]){}, 0);
Value args_ = v27;
Value v28 = create_array((Value[]){create_int(41)}, 1);
Value v29 = call_method(mod, &*this_ptr, "accept", (Value[]){v28}, 1);
Value v30 = call_method(mod, &v29, "not", (Value[]){}, 0);
if (v30.data.int_value != 0) {
while (1) {
Value v31 = create_int(1);
if (v31.data.int_value == 0) break;
Value v32 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value v33 = call_method(mod, &args_, "push", (Value[]){v32}, 1);
args_ = v33;
Value v34 = create_array((Value[]){create_int(44)}, 1);
Value v35 = call_method(mod, &*this_ptr, "accept", (Value[]){v34}, 1);
Value v36 = call_method(mod, &v35, "not", (Value[]){}, 0);
if (v36.data.int_value != 0) {
break;
}
}
Value v37 = create_array((Value[]){create_int(41)}, 1);
Value v38 = call_method(mod, &*this_ptr, "expect", (Value[]){v37}, 1);
v38;
}
Value v39 = module_call(mod, "FunctionCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), id, args_}, 4);
expr = v39;
}
else {
Value v40 = module_call(mod, "Identifier", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), id}, 3);
expr = v40;
}
}
}
}
}
while (1) {
Value v41 = create_int(1);
if (v41.data.int_value == 0) break;
Value v42 = create_array((Value[]){create_int(46), create_int(105), create_int(110), create_int(115), create_int(116), create_int(97), create_int(110), create_int(99), create_int(101), create_int(79), create_int(102)}, 11);
Value v43 = call_method(mod, &*this_ptr, "accept", (Value[]){v42}, 1);
if (v43.data.int_value != 0) {
Value v44 = call_method(mod, &*this_ptr, "parseInstanceOf", (Value[]){expr}, 1);
expr = v44;
}
else {
Value v45 = create_array((Value[]){create_int(46)}, 1);
Value v46 = call_method(mod, &*this_ptr, "accept", (Value[]){v45}, 1);
if (v46.data.int_value != 0) {
Value v47 = call_method(mod, &*this_ptr, "parseIdentifier", (Value[]){}, 0);
Value identifier = v47;
Value v48 = create_array((Value[]){create_int(40)}, 1);
Value v49 = call_method(mod, &*this_ptr, "accept", (Value[]){v48}, 1);
if (v49.data.int_value != 0) {
Value v50 = create_array((Value[]){}, 0);
Value args_ = v50;
Value v51 = create_array((Value[]){create_int(41)}, 1);
Value v52 = call_method(mod, &*this_ptr, "accept", (Value[]){v51}, 1);
Value v53 = call_method(mod, &v52, "not", (Value[]){}, 0);
if (v53.data.int_value != 0) {
while (1) {
Value v54 = create_int(1);
if (v54.data.int_value == 0) break;
Value v55 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value v56 = call_method(mod, &args_, "push", (Value[]){v55}, 1);
args_ = v56;
Value v57 = create_array((Value[]){create_int(44)}, 1);
Value v58 = call_method(mod, &*this_ptr, "accept", (Value[]){v57}, 1);
Value v59 = call_method(mod, &v58, "not", (Value[]){}, 0);
if (v59.data.int_value != 0) {
break;
}
}
Value v60 = create_array((Value[]){create_int(41)}, 1);
Value v61 = call_method(mod, &*this_ptr, "expect", (Value[]){v60}, 1);
v61;
}
Value v62 = module_call(mod, "MethodCall", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), expr, identifier, args_}, 5);
expr = v62;
}
else {
Value v63 = module_call(mod, "FieldAccess", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), expr, identifier}, 4);
expr = v63;
}
}
else {
break;
}
}
}
return expr;
    return create_null();
}

Value Parser_parseArrayLiteral(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseArrayLiteral expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){}, 0);
Value elements = v1;
Value v2 = create_array((Value[]){create_int(93)}, 1);
Value v3 = call_method(mod, &*this_ptr, "accept", (Value[]){v2}, 1);
Value v4 = call_method(mod, &v3, "not", (Value[]){}, 0);
if (v4.data.int_value != 0) {
while (1) {
Value v5 = create_int(1);
if (v5.data.int_value == 0) break;
Value v6 = call_method(mod, &*this_ptr, "parseExpression", (Value[]){}, 0);
Value v7 = call_method(mod, &elements, "push", (Value[]){v6}, 1);
elements = v7;
Value v8 = create_array((Value[]){create_int(44)}, 1);
Value v9 = call_method(mod, &*this_ptr, "accept", (Value[]){v8}, 1);
Value v10 = call_method(mod, &v9, "not", (Value[]){}, 0);
if (v10.data.int_value != 0) {
break;
}
}
Value v11 = create_array((Value[]){create_int(93)}, 1);
Value v12 = call_method(mod, &*this_ptr, "expect", (Value[]){v11}, 1);
v12;
}
Value v13 = module_call(mod, "ArrayLiteral", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), elements}, 3);
return v13;
    return create_null();
}

Value Parser_parseIntegerLiteral(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseIntegerLiteral expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value start = *object_get_field(*this_ptr, "position");
while (1) {
Value v1 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v1}, 1);
Value v3 = create_int(0);
if (v2.data.int_value != 0) {
Value v4 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v5 = create_int(48);
Value v6 = call_method(mod, &v4, "greaterEqual", (Value[]){v5}, 1);
    if (v6.data.int_value != 0) {
        v3 = create_int(1);
    }
}
Value v7 = create_int(0);
if (v3.data.int_value != 0) {
Value v8 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v9 = create_int(57);
Value v10 = call_method(mod, &v8, "smallerEqual", (Value[]){v9}, 1);
    if (v10.data.int_value != 0) {
        v7 = create_int(1);
    }
}
if (v7.data.int_value == 0) break;
Value v11 = create_int(1);
Value v12 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v11}, 1);
object_set_field(&*this_ptr, "position", v12);
}
Value v13 = call_method(mod, &*object_get_field(*this_ptr, "input"), "slice", (Value[]){start, *object_get_field(*this_ptr, "position")}, 2);
Value v14 = call_method(mod, &v13, "toInt", (Value[]){}, 0);
Value value = v14;
Value v15 = module_call(mod, "IntegerLiteral", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), value}, 3);
return v15;
    return create_null();
}

Value Parser_parseStringLiteral(Module* mod, Value* this_ptr, Value* args, size_t arg_count) {
    if (arg_count != 0) {
        fprintf(stderr, "parseStringLiteral expects 0 argument(s)\n");
        exit(1);
    }
    Value* self = this_ptr->data.object.fields;
    Value v1 = create_array((Value[]){}, 0);
Value literal = v1;
while (1) {
Value v2 = call_method(mod, &*object_get_field(*this_ptr, "input"), "length", (Value[]){}, 0);
Value v3 = call_method(mod, &*object_get_field(*this_ptr, "position"), "smaller", (Value[]){v2}, 1);
Value v4 = create_int(0);
if (v3.data.int_value != 0) {
Value v5 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v6 = create_int(34);
Value v7 = call_method(mod, &v5, "notEqual", (Value[]){v6}, 1);
    if (v7.data.int_value != 0) {
        v4 = create_int(1);
    }
}
if (v4.data.int_value == 0) break;
Value v8 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v9 = create_int(92);
Value v10 = call_method(mod, &v8, "equal", (Value[]){v9}, 1);
if (v10.data.int_value != 0) {
Value v11 = create_int(1);
Value v12 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v11}, 1);
object_set_field(&*this_ptr, "position", v12);
Value v13 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v14 = create_int(110);
Value v15 = call_method(mod, &v13, "equal", (Value[]){v14}, 1);
if (v15.data.int_value != 0) {
Value v16 = create_int(10);
Value v17 = call_method(mod, &literal, "push", (Value[]){v16}, 1);
literal = v17;
}
else {
Value v18 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v19 = call_method(mod, &literal, "push", (Value[]){v18}, 1);
literal = v19;
}
}
else {
Value v20 = call_method(mod, &*object_get_field(*this_ptr, "input"), "get", (Value[]){*object_get_field(*this_ptr, "position")}, 1);
Value v21 = call_method(mod, &literal, "push", (Value[]){v20}, 1);
literal = v21;
}
Value v22 = create_int(1);
Value v23 = call_method(mod, &*object_get_field(*this_ptr, "position"), "add", (Value[]){v22}, 1);
object_set_field(&*this_ptr, "position", v23);
}
Value v24 = create_array((Value[]){create_int(34)}, 1);
Value v25 = call_method(mod, &*this_ptr, "expect", (Value[]){v24}, 1);
v25;
Value v26 = module_call(mod, "StringLiteral", (Value[]){*object_get_field(*this_ptr, "filename"), *object_get_field(*this_ptr, "line"), literal}, 3);
return v26;
    return create_null();
}

ClassType Parser_type = {
    .base = {
        .methods = (MethodFunc[]){Parser_init, Parser_accept, Parser_expect, Parser_skipWhitespace, Parser_skipComments, Parser_parseIdentifier, Parser_parse, Parser_parseFunctionDecl, Parser_parseClassDecl, Parser_parseStatement, Parser_parseIfStatement, Parser_parseWhileStatement, Parser_parseExpression, Parser_parseLogicalOrExpression, Parser_parseLogicalAndExpression, Parser_parseEqualityExpression, Parser_parseRelationalExpression, Parser_parseAdditiveExpression, Parser_parseMultiplicativeExpression, Parser_parseUnaryExpression, Parser_parseInstanceOf, Parser_parsePrimary, Parser_parseArrayLiteral, Parser_parseIntegerLiteral, Parser_parseStringLiteral},
        .method_names = (char*[]){"init", "accept", "expect", "skipWhitespace", "skipComments", "parseIdentifier", "parse", "parseFunctionDecl", "parseClassDecl", "parseStatement", "parseIfStatement", "parseWhileStatement", "parseExpression", "parseLogicalOrExpression", "parseLogicalAndExpression", "parseEqualityExpression", "parseRelationalExpression", "parseAdditiveExpression", "parseMultiplicativeExpression", "parseUnaryExpression", "parseInstanceOf", "parsePrimary", "parseArrayLiteral", "parseIntegerLiteral", "parseStringLiteral"},
        .method_count = 25
    },
    .name = "Parser",
    .parent = NULL,
    .field_names = (char*[]){"input", "filename", "position", "line"},
    .field_count = 4
};

Value main2(Module* mod, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "main expects 1 argument(s)\n");
        exit(1);
    }
    Value args_ = args[0];    Value v1 = call_method(mod, &args_, "length", (Value[]){}, 0);
Value v2 = create_int(3);
Value v3 = call_method(mod, &v1, "notEqual", (Value[]){v2}, 1);
if (v3.data.int_value != 0) {
Value v4 = create_array((Value[]){create_int(85), create_int(115), create_int(97), create_int(103), create_int(101), create_int(58), create_int(32), create_int(110), create_int(101), create_int(97), create_int(116), create_int(51), create_int(32), create_int(60), create_int(105), create_int(110), create_int(112), create_int(117), create_int(116), create_int(95), create_int(102), create_int(105), create_int(108), create_int(101), create_int(62), create_int(32), create_int(60), create_int(111), create_int(117), create_int(116), create_int(112), create_int(117), create_int(116), create_int(95), create_int(102), create_int(105), create_int(108), create_int(101), create_int(62)}, 39);
Value v5 = module_call(mod, "print", (Value[]){v4}, 1);
v5;
Value v6 = create_int(0);
return v6;
}
Value v7 = create_int(1);
Value v8 = call_method(mod, &args_, "get", (Value[]){v7}, 1);
Value inputFile = v8;
Value v9 = create_int(2);
Value v10 = call_method(mod, &args_, "get", (Value[]){v9}, 1);
Value outputFile = v10;
Value v11 = module_call(mod, "readFile", (Value[]){inputFile}, 1);
Value input = v11;
Value v12 = module_call(mod, "Parser", (Value[]){input, inputFile}, 2);
Value parser = v12;
Value v13 = call_method(mod, &parser, "parse", (Value[]){}, 0);
Value program = v13;
Value v14 = call_method(mod, &program, "compile", (Value[]){}, 0);
Value output = v14;
Value v15 = create_array((Value[]){create_int(77), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(42), create_int(32), create_int(109), create_int(111), create_int(100), create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(109), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(40), create_int(41), create_int(59), create_int(10)}, 31);
Value moduleSetup = v15;
Value v16 = create_int(0);
Value i = v16;
while (1) {
Value v17 = call_method(mod, &*object_get_field(program, "nodes"), "length", (Value[]){}, 0);
Value v18 = call_method(mod, &i, "smaller", (Value[]){v17}, 1);
if (v18.data.int_value == 0) break;
Value v19 = call_method(mod, &*object_get_field(program, "nodes"), "get", (Value[]){i}, 1);
Value node = v19;
Value v20 = instance_of(node, "FunctionDecl");
Value v21 = call_method(mod, &v20, "isNull", (Value[]){}, 0);
Value v22 = call_method(mod, &v21, "not", (Value[]){}, 0);
if (v22.data.int_value != 0) {
Value emittedName = *object_get_field(node, "name");
Value v23 = create_array((Value[]){create_int(109), create_int(97), create_int(105), create_int(110)}, 4);
Value v24 = call_method(mod, &*object_get_field(node, "name"), "equal", (Value[]){v23}, 1);
if (v24.data.int_value != 0) {
Value v25 = create_array((Value[]){create_int(109), create_int(97), create_int(105), create_int(110), create_int(50)}, 5);
emittedName = v25;
}
Value v26 = create_array((Value[]){create_int(109), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(95), create_int(97), create_int(100), create_int(100), create_int(95), create_int(101), create_int(110), create_int(116), create_int(114), create_int(121), create_int(40), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(40), create_int(77), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(69), create_int(110), create_int(116), create_int(114), create_int(121), create_int(41), create_int(123)}, 36);
Value v27 = call_method(mod, &moduleSetup, "concat", (Value[]){v26}, 1);
Value v28 = create_array((Value[]){create_int(46), create_int(110), create_int(97), create_int(109), create_int(101), create_int(32), create_int(61), create_int(32), create_int(34)}, 9);
Value v29 = call_method(mod, &v27, "concat", (Value[]){v28}, 1);
Value v30 = call_method(mod, &v29, "concat", (Value[]){*object_get_field(node, "name")}, 1);
Value v31 = create_array((Value[]){create_int(34), create_int(44), create_int(32)}, 3);
Value v32 = call_method(mod, &v30, "concat", (Value[]){v31}, 1);
Value v33 = create_array((Value[]){create_int(46), create_int(116), create_int(121), create_int(112), create_int(101), create_int(32), create_int(61), create_int(32), create_int(69), create_int(78), create_int(84), create_int(82), create_int(89), create_int(95), create_int(70), create_int(85), create_int(78), create_int(67), create_int(84), create_int(73), create_int(79), create_int(78), create_int(44), create_int(32)}, 24);
Value v34 = call_method(mod, &v32, "concat", (Value[]){v33}, 1);
Value v35 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(32), create_int(61), create_int(32), create_int(123), create_int(32), create_int(46), create_int(102), create_int(117), create_int(110), create_int(99), create_int(116), create_int(105), create_int(111), create_int(110), create_int(95), create_int(99), create_int(97), create_int(108), create_int(108), create_int(32), create_int(61), create_int(32)}, 27);
Value v36 = call_method(mod, &v34, "concat", (Value[]){v35}, 1);
Value v37 = call_method(mod, &v36, "concat", (Value[]){emittedName}, 1);
Value v38 = create_array((Value[]){create_int(32), create_int(125)}, 2);
Value v39 = call_method(mod, &v37, "concat", (Value[]){v38}, 1);
Value v40 = create_array((Value[]){create_int(125), create_int(41), create_int(59), create_int(10)}, 4);
Value v41 = call_method(mod, &v39, "concat", (Value[]){v40}, 1);
moduleSetup = v41;
}
else {
Value v42 = instance_of(node, "ClassDecl");
Value v43 = call_method(mod, &v42, "isNull", (Value[]){}, 0);
Value v44 = call_method(mod, &v43, "not", (Value[]){}, 0);
if (v44.data.int_value != 0) {
Value v45 = create_array((Value[]){create_int(109), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(95), create_int(97), create_int(100), create_int(100), create_int(95), create_int(101), create_int(110), create_int(116), create_int(114), create_int(121), create_int(40), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(40), create_int(77), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(69), create_int(110), create_int(116), create_int(114), create_int(121), create_int(41), create_int(123)}, 36);
Value v46 = call_method(mod, &moduleSetup, "concat", (Value[]){v45}, 1);
Value v47 = create_array((Value[]){create_int(46), create_int(110), create_int(97), create_int(109), create_int(101), create_int(32), create_int(61), create_int(32), create_int(34)}, 9);
Value v48 = call_method(mod, &v46, "concat", (Value[]){v47}, 1);
Value v49 = call_method(mod, &v48, "concat", (Value[]){*object_get_field(node, "name")}, 1);
Value v50 = create_array((Value[]){create_int(34), create_int(44)}, 2);
Value v51 = call_method(mod, &v49, "concat", (Value[]){v50}, 1);
Value v52 = create_array((Value[]){create_int(46), create_int(116), create_int(121), create_int(112), create_int(101), create_int(32), create_int(61), create_int(32), create_int(69), create_int(78), create_int(84), create_int(82), create_int(89), create_int(95), create_int(67), create_int(76), create_int(65), create_int(83), create_int(83), create_int(44), create_int(32)}, 21);
Value v53 = call_method(mod, &v51, "concat", (Value[]){v52}, 1);
Value v54 = create_array((Value[]){create_int(46), create_int(100), create_int(97), create_int(116), create_int(97), create_int(32), create_int(61), create_int(32), create_int(123), create_int(32), create_int(46), create_int(99), create_int(108), create_int(97), create_int(115), create_int(115), create_int(95), create_int(116), create_int(121), create_int(112), create_int(101), create_int(32), create_int(61), create_int(32), create_int(38)}, 25);
Value v55 = call_method(mod, &v53, "concat", (Value[]){v54}, 1);
Value v56 = call_method(mod, &v55, "concat", (Value[]){*object_get_field(node, "name")}, 1);
Value v57 = create_array((Value[]){create_int(95), create_int(116), create_int(121), create_int(112), create_int(101), create_int(32), create_int(125)}, 7);
Value v58 = call_method(mod, &v56, "concat", (Value[]){v57}, 1);
Value v59 = create_array((Value[]){create_int(125), create_int(41), create_int(59), create_int(10)}, 4);
Value v60 = call_method(mod, &v58, "concat", (Value[]){v59}, 1);
moduleSetup = v60;
}
}
Value v61 = create_int(1);
Value v62 = call_method(mod, &i, "add", (Value[]){v61}, 1);
i = v62;
}
Value v63 = create_array((Value[]){create_int(105), create_int(110), create_int(116), create_int(32), create_int(109), create_int(97), create_int(105), create_int(110), create_int(40), create_int(105), create_int(110), create_int(116), create_int(32), create_int(97), create_int(114), create_int(103), create_int(99), create_int(44), create_int(32), create_int(99), create_int(104), create_int(97), create_int(114), create_int(42), create_int(42), create_int(32), create_int(97), create_int(114), create_int(103), create_int(118), create_int(41), create_int(32), create_int(123), create_int(10)}, 34);
Value v64 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32)}, 4);
Value v65 = call_method(mod, &v63, "concat", (Value[]){v64}, 1);
Value v66 = call_method(mod, &v65, "concat", (Value[]){moduleSetup}, 1);
Value v67 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(97), create_int(114), create_int(103), create_int(115), create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(97), create_int(114), create_int(114), create_int(97), create_int(121), create_int(40), create_int(78), create_int(85), create_int(76), create_int(76), create_int(44), create_int(32), create_int(97), create_int(114), create_int(103), create_int(99), create_int(41), create_int(59), create_int(10)}, 43);
Value v68 = call_method(mod, &v66, "concat", (Value[]){v67}, 1);
Value v69 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(102), create_int(111), create_int(114), create_int(32), create_int(40), create_int(105), create_int(110), create_int(116), create_int(32), create_int(105), create_int(32), create_int(61), create_int(32), create_int(48), create_int(59), create_int(32), create_int(105), create_int(32), create_int(60), create_int(32), create_int(97), create_int(114), create_int(103), create_int(99), create_int(59), create_int(32), create_int(105), create_int(43), create_int(43), create_int(41), create_int(32), create_int(123), create_int(10)}, 37);
Value v70 = call_method(mod, &v68, "concat", (Value[]){v69}, 1);
Value v71 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(86), create_int(97), create_int(108), create_int(117), create_int(101), create_int(32), create_int(97), create_int(114), create_int(103), create_int(32), create_int(61), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(97), create_int(114), create_int(114), create_int(97), create_int(121), create_int(40), create_int(78), create_int(85), create_int(76), create_int(76), create_int(44), create_int(32), create_int(115), create_int(116), create_int(114), create_int(108), create_int(101), create_int(110), create_int(40), create_int(97), create_int(114), create_int(103), create_int(118), create_int(91), create_int(105), create_int(93), create_int(41), create_int(41), create_int(59), create_int(10)}, 57);
Value v72 = call_method(mod, &v70, "concat", (Value[]){v71}, 1);
Value v73 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(102), create_int(111), create_int(114), create_int(32), create_int(40), create_int(105), create_int(110), create_int(116), create_int(32), create_int(106), create_int(32), create_int(61), create_int(32), create_int(48), create_int(59), create_int(32), create_int(106), create_int(32), create_int(60), create_int(32), create_int(115), create_int(116), create_int(114), create_int(108), create_int(101), create_int(110), create_int(40), create_int(97), create_int(114), create_int(103), create_int(118), create_int(91), create_int(105), create_int(93), create_int(41), create_int(59), create_int(32), create_int(106), create_int(43), create_int(43), create_int(41), create_int(32), create_int(123), create_int(10)}, 52);
Value v74 = call_method(mod, &v72, "concat", (Value[]){v73}, 1);
Value v75 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(97), create_int(114), create_int(114), create_int(97), create_int(121), create_int(95), create_int(115), create_int(101), create_int(116), create_int(40), create_int(97), create_int(114), create_int(103), create_int(44), create_int(32), create_int(106), create_int(44), create_int(32), create_int(99), create_int(114), create_int(101), create_int(97), create_int(116), create_int(101), create_int(95), create_int(105), create_int(110), create_int(116), create_int(40), create_int(97), create_int(114), create_int(103), create_int(118), create_int(91), create_int(105), create_int(93), create_int(91), create_int(106), create_int(93), create_int(41), create_int(41), create_int(59), create_int(10)}, 55);
Value v76 = call_method(mod, &v74, "concat", (Value[]){v75}, 1);
Value v77 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(125), create_int(10)}, 10);
Value v78 = call_method(mod, &v76, "concat", (Value[]){v77}, 1);
Value v79 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(32), create_int(97), create_int(114), create_int(114), create_int(97), create_int(121), create_int(95), create_int(115), create_int(101), create_int(116), create_int(40), create_int(97), create_int(114), create_int(103), create_int(115), create_int(44), create_int(32), create_int(105), create_int(44), create_int(32), create_int(97), create_int(114), create_int(103), create_int(41), create_int(59), create_int(10)}, 33);
Value v80 = call_method(mod, &v78, "concat", (Value[]){v79}, 1);
Value v81 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(125), create_int(10)}, 6);
Value v82 = call_method(mod, &v80, "concat", (Value[]){v81}, 1);
Value v83 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(109), create_int(111), create_int(100), create_int(117), create_int(108), create_int(101), create_int(95), create_int(99), create_int(97), create_int(108), create_int(108), create_int(40), create_int(109), create_int(111), create_int(100), create_int(44), create_int(32), create_int(34), create_int(109), create_int(97), create_int(105), create_int(110), create_int(34), create_int(44), create_int(32), create_int(38), create_int(97), create_int(114), create_int(103), create_int(115), create_int(44), create_int(32), create_int(49), create_int(41), create_int(59), create_int(10)}, 40);
Value v84 = call_method(mod, &v82, "concat", (Value[]){v83}, 1);
Value v85 = create_array((Value[]){create_int(32), create_int(32), create_int(32), create_int(32), create_int(114), create_int(101), create_int(116), create_int(117), create_int(114), create_int(110), create_int(32), create_int(48), create_int(59), create_int(10)}, 14);
Value v86 = call_method(mod, &v84, "concat", (Value[]){v85}, 1);
Value v87 = create_array((Value[]){create_int(125)}, 1);
Value v88 = call_method(mod, &v86, "concat", (Value[]){v87}, 1);
Value mainFunction = v88;
Value v89 = create_array((Value[]){create_int(35), create_int(105), create_int(110), create_int(99), create_int(108), create_int(117), create_int(100), create_int(101), create_int(32), create_int(34), create_int(114), create_int(117), create_int(110), create_int(116), create_int(105), create_int(109), create_int(101), create_int(46), create_int(104), create_int(34), create_int(10), create_int(10)}, 22);
Value v90 = call_method(mod, &v89, "concat", (Value[]){output}, 1);
Value v91 = create_array((Value[]){create_int(10)}, 1);
Value v92 = call_method(mod, &v90, "concat", (Value[]){v91}, 1);
Value v93 = call_method(mod, &v92, "concat", (Value[]){mainFunction}, 1);
output = v93;
Value v94 = module_call(mod, "writeFile", (Value[]){outputFile, output}, 2);
v94;
Value v95 = create_int(0);
return v95;
    return create_null();
}

int main(int argc, char** argv) {
    Module* mod = create_module();
module_add_entry(mod, (ModuleEntry){.name = "CodegenContext",.type = ENTRY_CLASS, .data = { .class_type = &CodegenContext_type }});
module_add_entry(mod, (ModuleEntry){.name = "TopLevelASTNode",.type = ENTRY_CLASS, .data = { .class_type = &TopLevelASTNode_type }});
module_add_entry(mod, (ModuleEntry){.name = "ASTFunctionNode",.type = ENTRY_CLASS, .data = { .class_type = &ASTFunctionNode_type }});
module_add_entry(mod, (ModuleEntry){.name = "Program",.type = ENTRY_CLASS, .data = { .class_type = &Program_type }});
module_add_entry(mod, (ModuleEntry){.name = "FunctionDecl",.type = ENTRY_CLASS, .data = { .class_type = &FunctionDecl_type }});
module_add_entry(mod, (ModuleEntry){.name = "VTableEntry",.type = ENTRY_CLASS, .data = { .class_type = &VTableEntry_type }});
module_add_entry(mod, (ModuleEntry){.name = "VTable",.type = ENTRY_CLASS, .data = { .class_type = &VTable_type }});
module_add_entry(mod, (ModuleEntry){.name = "ClassDecl",.type = ENTRY_CLASS, .data = { .class_type = &ClassDecl_type }});
module_add_entry(mod, (ModuleEntry){.name = "VariableDecl",.type = ENTRY_CLASS, .data = { .class_type = &VariableDecl_type }});
module_add_entry(mod, (ModuleEntry){.name = "MethodCall",.type = ENTRY_CLASS, .data = { .class_type = &MethodCall_type }});
module_add_entry(mod, (ModuleEntry){.name = "FunctionCall",.type = ENTRY_CLASS, .data = { .class_type = &FunctionCall_type }});
module_add_entry(mod, (ModuleEntry){.name = "IfStatement",.type = ENTRY_CLASS, .data = { .class_type = &IfStatement_type }});
module_add_entry(mod, (ModuleEntry){.name = "WhileStatement",.type = ENTRY_CLASS, .data = { .class_type = &WhileStatement_type }});
module_add_entry(mod, (ModuleEntry){.name = "AssignmentStatement",.type = ENTRY_CLASS, .data = { .class_type = &AssignmentStatement_type }});
module_add_entry(mod, (ModuleEntry){.name = "ReturnStatement",.type = ENTRY_CLASS, .data = { .class_type = &ReturnStatement_type }});
module_add_entry(mod, (ModuleEntry){.name = "ExpressionStatement",.type = ENTRY_CLASS, .data = { .class_type = &ExpressionStatement_type }});
module_add_entry(mod, (ModuleEntry){.name = "Identifier",.type = ENTRY_CLASS, .data = { .class_type = &Identifier_type }});
module_add_entry(mod, (ModuleEntry){.name = "IntegerLiteral",.type = ENTRY_CLASS, .data = { .class_type = &IntegerLiteral_type }});
module_add_entry(mod, (ModuleEntry){.name = "StringLiteral",.type = ENTRY_CLASS, .data = { .class_type = &StringLiteral_type }});
module_add_entry(mod, (ModuleEntry){.name = "NullLiteral",.type = ENTRY_CLASS, .data = { .class_type = &NullLiteral_type }});
module_add_entry(mod, (ModuleEntry){.name = "ArrayLiteral",.type = ENTRY_CLASS, .data = { .class_type = &ArrayLiteral_type }});
module_add_entry(mod, (ModuleEntry){.name = "InstanceOfExpression",.type = ENTRY_CLASS, .data = { .class_type = &InstanceOfExpression_type }});
module_add_entry(mod, (ModuleEntry){.name = "FieldAccess",.type = ENTRY_CLASS, .data = { .class_type = &FieldAccess_type }});
module_add_entry(mod, (ModuleEntry){.name = "LogicalAndExpression",.type = ENTRY_CLASS, .data = { .class_type = &LogicalAndExpression_type }});
module_add_entry(mod, (ModuleEntry){.name = "LogicalOrExpression",.type = ENTRY_CLASS, .data = { .class_type = &LogicalOrExpression_type }});
module_add_entry(mod, (ModuleEntry){.name = "Parser",.type = ENTRY_CLASS, .data = { .class_type = &Parser_type }});
module_add_entry(mod, (ModuleEntry){.name = "main", .type = ENTRY_FUNCTION, .data = { .function_call = main2 }});
    Value args = create_array(NULL, argc);
    for (int i = 0; i < argc; i++) {
        Value arg = create_array(NULL, strlen(argv[i]));
        for (int j = 0; j < strlen(argv[i]); j++) {
            array_set(arg, j, create_int(argv[i][j]));
        }
        array_set(args, i, arg);
    }
    module_call(mod, "main", &args, 1);
    return 0;
}