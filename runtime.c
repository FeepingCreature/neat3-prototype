#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Value create_int(int64_t value) {
    Value v = {.type = TYPE_INT, .data.int_value = value};
    return v;
}

Value create_array(Value* elements, size_t length) {
    Value v = {.type = TYPE_ARRAY};
    v.data.array.elements = malloc(sizeof(Value) * length);
    if (elements) {
        memcpy(v.data.array.elements, elements, sizeof(Value) * length);
    }
    v.data.array.length = length;
    v.data.array.capacity = length;
    return v;
}

Value create_object(ClassType* class_type) {
    Value v = {.type = TYPE_OBJECT};
    v.data.object.class_type = class_type;
    v.data.object.fields = malloc(sizeof(Value) * class_type->field_count);
    memset(v.data.object.fields, 0, sizeof(Value) * class_type->field_count);
    return v;
}

Value create_null() {
    Value v = {.type = TYPE_NULL};
    return v;
}

Value array_get(Value array, size_t index) {
    if (array.type != TYPE_ARRAY || index >= array.data.array.length) {
        fprintf(stderr, "Array index out of bounds\n");
        exit(1);
    }
    return array.data.array.elements[index];
}

void array_set(Value array, size_t index, Value value) {
    if (array.type != TYPE_ARRAY || index >= array.data.array.length) {
        fprintf(stderr, "Array index out of bounds\n");
        exit(1);
    }
    array.data.array.elements[index] = value;
}

Value array_push(Value* array, Value element) {
    if (array->type != TYPE_ARRAY) {
        fprintf(stderr, "Cannot push to non-array\n");
        exit(1);
    }
    if (array->data.array.length == array->data.array.capacity) {
        size_t new_capacity = array->data.array.capacity * 2 + 1;
        Value* new_elements = malloc(sizeof(Value) * new_capacity);
        memcpy(new_elements, array->data.array.elements, sizeof(Value) * array->data.array.length);
        array->data.array.elements = new_elements;
        array->data.array.capacity = new_capacity;
    }
    array->data.array.elements[array->data.array.length++] = element;
    return *array;
}

Value array_slice(Value array, size_t start, size_t end) {
    if (array.type != TYPE_ARRAY || start > end || end > array.data.array.length) {
        fprintf(stderr, "Invalid array slice\n");
        exit(1);
    }
    return create_array(array.data.array.elements + start, end - start);
}

Value array_concat(Value array1, Value array2) {
    if (array1.type != TYPE_ARRAY || array2.type != TYPE_ARRAY) {
        fprintf(stderr, "Cannot concat non-arrays\n");
        exit(1);
    }
    size_t new_length = array1.data.array.length + array2.data.array.length;
    Value* new_elements = malloc(sizeof(Value) * new_length);
    memcpy(new_elements, array1.data.array.elements, sizeof(Value) * array1.data.array.length);
    memcpy(new_elements + array1.data.array.length, array2.data.array.elements, sizeof(Value) * array2.data.array.length);
    return create_array(new_elements, new_length);
}

Value array_length(Value array) {
    if (array.type != TYPE_ARRAY) {
        fprintf(stderr, "Cannot get length of non-array\n");
        exit(1);
    }
    return create_int(array.data.array.length);
}

Value array_join(Value array, Value separator) {
    if (array.type != TYPE_ARRAY || separator.type != TYPE_ARRAY) {
        fprintf(stderr, "array_join: Arguments must be arrays\n");
        exit(1);
    }

    size_t total_length = 0;
    for (size_t i = 0; i < array.data.array.length; i++) {
        if (array.data.array.elements[i].type != TYPE_ARRAY) {
            fprintf(stderr, "array_join: All elements must be arrays\n");
            exit(1);
        }
        total_length += array.data.array.elements[i].data.array.length;
        if (i < array.data.array.length - 1) {
            total_length += separator.data.array.length;
        }
    }

    Value* result_elements = malloc(sizeof(Value) * total_length);
    size_t result_index = 0;

    for (size_t i = 0; i < array.data.array.length; i++) {
        Value sub_array = array.data.array.elements[i];
        for (size_t j = 0; j < sub_array.data.array.length; j++) {
            result_elements[result_index++] = sub_array.data.array.elements[j];
        }

        if (i < array.data.array.length - 1) {
            for (size_t j = 0; j < separator.data.array.length; j++) {
                result_elements[result_index++] = separator.data.array.elements[j];
            }
        }
    }

    return create_array(result_elements, total_length);
}

Value array_to_int(Value array) {
    if (array.type != TYPE_ARRAY) {
        fprintf(stderr, "array_to_int: Argument must be an array\n");
        exit(1);
    }

    char* str = malloc(array.data.array.length + 1);
    for (size_t i = 0; i < array.data.array.length; i++) {
        if (array.data.array.elements[i].type != TYPE_INT) {
            fprintf(stderr, "array_to_int: All elements must be integers\n");
            exit(1);
        }
        str[i] = (char)array.data.array.elements[i].data.int_value;
    }
    str[array.data.array.length] = '\0';

    int result = atoi(str);
    free(str);

    return create_int(result);
}

Value* object_get_field(Value object, const char* field_name) {
    if (object.type != TYPE_OBJECT) {
        fprintf(stderr, "Cannot get field from non-object\n");
        exit(1);
    }
    for (size_t i = 0; i < object.data.object.class_type->field_count; i++) {
        if (strcmp(object.data.object.class_type->field_names[i], field_name) == 0) {
            return &object.data.object.fields[i];
        }
    }
    fprintf(stderr, "Field not found: %s\n", field_name);
    exit(1);
}

void object_set_field(Value* object, const char* field_name, Value value) {
    if (object->type != TYPE_OBJECT) {
        fprintf(stderr, "Cannot set field on non-object\n");
        exit(1);
    }
    for (size_t i = 0; i < object->data.object.class_type->field_count; i++) {
        if (strcmp(object->data.object.class_type->field_names[i], field_name) == 0) {
            object->data.object.fields[i] = value;
            return;
        }
    }
    fprintf(stderr, "Field not found: %s\n", field_name);
    exit(1);
}

Value call_method(Module* mod, Value* value, const char* method_name, Value* args, size_t arg_count) {
    switch (value->type) {
        case TYPE_INT:
            if (strcmp(method_name, "add") == 0) {
                return value_add(*value, args[0]);
            } else if (strcmp(method_name, "sub") == 0) {
                return value_subtract(*value, args[0]);
            } else if (strcmp(method_name, "mul") == 0) {
                return value_multiply(*value, args[0]);
            } else if (strcmp(method_name, "div") == 0) {
                return value_divide(*value, args[0]);
            } else if (strcmp(method_name, "equal") == 0) {
                return value_equal(*value, args[0]);
            } else if (strcmp(method_name, "notEqual") == 0) {
                return value_not_equal(*value, args[0]);
            } else if (strcmp(method_name, "greater") == 0) {
                return value_greater(*value, args[0]);
            } else if (strcmp(method_name, "smaller") == 0) {
                return value_less(*value, args[0]);
            } else if (strcmp(method_name, "greaterEqual") == 0) {
                return value_greater_equal(*value, args[0]);
            } else if (strcmp(method_name, "smallerEqual") == 0) {
                return value_less_equal(*value, args[0]);
            } else if (strcmp(method_name, "not") == 0) {
                return value_not(*value);
            } else if (strcmp(method_name, "negate") == 0) {
                return value_negate(*value);
            } else if (strcmp(method_name, "toString") == 0) {
                return value_to_string(*value);
            }
            break;
        case TYPE_ARRAY:
            if (strcmp(method_name, "get") == 0) {
                return array_get(*value, args[0].data.int_value);
            } else if (strcmp(method_name, "set") == 0) {
                array_set(*value, args[0].data.int_value, args[1]);
                return create_null();
            } else if (strcmp(method_name, "push") == 0) {
                return array_push(value, args[0]);
            } else if (strcmp(method_name, "slice") == 0) {
                return array_slice(*value, args[0].data.int_value, args[1].data.int_value);
            } else if (strcmp(method_name, "concat") == 0) {
                return array_concat(*value, args[0]);
            } else if (strcmp(method_name, "length") == 0) {
                return array_length(*value);
            } else if (strcmp(method_name, "join") == 0) {
                return array_join(*value, args[0]);
            } else if (strcmp(method_name, "toInt") == 0) {
                return array_to_int(*value);
            } else if (strcmp(method_name, "equal") == 0) {
                return value_equal(*value, args[0]);
            }
            break;
        case TYPE_OBJECT:
            if (strcmp(method_name, "isNull") == 0) {
                return create_int(0);
            }
            for (size_t i = 0; i < value->data.object.class_type->base.method_count; i++) {
                if (strcmp(value->data.object.class_type->base.method_names[i], method_name) == 0) {
                    return value->data.object.class_type->base.methods[i](mod, value, args, arg_count);
                }
            }
            fprintf(stderr, "Class method not found on %s: %s\n", value->data.object.class_type->name, method_name);
            exit(1);
        case TYPE_NULL:
            if (strcmp(method_name, "isNull") == 0) {
                return create_int(1);
            }
            break;
    }
    fprintf(stderr, "Method not found: %s\n", method_name);
    exit(1);
}


void module_add_default_entries(Module* module) {
    ModuleEntry print_entry = {
        .name = "print",
        .type = ENTRY_FUNCTION,
        .data = { .function_call = print_value }
    };
    module_add_entry(module, print_entry);

    ModuleEntry read_file_entry = {
        .name = "readFile",
        .type = ENTRY_FUNCTION,
        .data = { .function_call = read_file }
    };
    module_add_entry(module, read_file_entry);

    ModuleEntry write_file_entry = {
        .name = "writeFile",
        .type = ENTRY_FUNCTION,
        .data = { .function_call = write_file }
    };
    module_add_entry(module, write_file_entry);

    ModuleEntry assert_entry = {
        .name = "assert",
        .type = ENTRY_FUNCTION,
        .data = { .function_call = assert_value }
    };
    module_add_entry(module, assert_entry);
}

static void print_helper(Value value);

Value print_value(Module* mod, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "print expects 1 argument\n");
        exit(1);
    }
    print_helper(args[0]);
    printf("\n");
    return create_int(0);
}

static void print_helper(Value value) {
    switch (value.type) {
        case TYPE_INT:
            printf("%ld", value.data.int_value);
            break;
        case TYPE_ARRAY:
            char* buffer = malloc(value.data.array.length);
            for (size_t i = 0; i < value.data.array.length; i++) {
                buffer[i] = (char) value.data.array.elements[i].data.int_value;
            }
            printf("%.*s", (int) value.data.array.length, buffer);
            free(buffer);
            break;
        case TYPE_OBJECT:
            printf("<%s object>", value.data.object.class_type->name);
            break;
        case TYPE_NULL:
            printf("null");
            break;
    }
}

Value read_file(Module* mod, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "readFile expects 1 argument\n");
        exit(1);
    }
    if (args[0].type != TYPE_ARRAY) {
        fprintf(stderr, "readFile expects a string (array of integers)\n");
        exit(1);
    }

    size_t filename_length = args[0].data.array.length;
    char* filename = malloc(filename_length + 1);
    for (size_t i = 0; i < filename_length; i++) {
        filename[i] = (char)args[0].data.array.elements[i].data.int_value;
    }
    filename[filename_length] = '\0';

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    Value* chars = malloc(sizeof(Value) * file_size);
    for (long i = 0; i < file_size; i++) {
        chars[i] = create_int(fgetc(file));
    }
    fclose(file);

    Value content = create_array(chars, file_size);
    free(filename);
    return content;
}

Value write_file(Module* mod, Value* args, size_t arg_count) {
    if (arg_count != 2) {
        fprintf(stderr, "writeFile expects 2 arguments\n");
        exit(1);
    }
    if (args[0].type != TYPE_ARRAY || args[1].type != TYPE_ARRAY) {
        fprintf(stderr, "writeFile expects two strings (arrays of integers)\n");
        exit(1);
    }

    size_t filename_length = args[0].data.array.length;
    char* filename = malloc(filename_length + 1);
    for (size_t i = 0; i < filename_length; i++) {
        filename[i] = (char)args[0].data.array.elements[i].data.int_value;
    }
    filename[filename_length] = '\0';

    if (args[1].type != TYPE_ARRAY) {
        fprintf(stderr, "Cannot write non-array to file\n");
        exit(1);
    }
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file for writing: %s\n", filename);
        exit(1);
    }
    for (size_t i = 0; i < args[1].data.array.length; i++) {
        Value char_value = args[1].data.array.elements[i];
        if (char_value.type != TYPE_INT) {
            fprintf(stderr, "Array contains non-integer value\n");
            exit(1);
        }
        fputc((int)char_value.data.int_value, file);
    }
    fclose(file);
    free(filename);
    return create_int(0);
}

Value assert_value(Module* mod, Value* args, size_t arg_count) {
    if (arg_count != 1) {
        fprintf(stderr, "assert expects 1 argument\n");
        exit(1);
    }
    if (args[0].type != TYPE_INT || args[0].data.int_value == 0) {
        fprintf(stderr, "Assertion failed\n");
        exit(1);
    }
    return create_int(0);
}

// Modify the create_module function to add default entries
Module* create_module() {
    Module* module = malloc(sizeof(Module));
    module->entries = NULL;
    module->entry_count = 0;
    module_add_default_entries(module);
    return module;
}

void module_add_entry(Module* module, ModuleEntry entry) {
    module->entries = realloc(module->entries, sizeof(ModuleEntry) * (module->entry_count + 1));
    module->entries[module->entry_count++] = entry;
}

ModuleEntry* module_get_entry(Module* module, const char* name) {
    for (size_t i = 0; i < module->entry_count; i++) {
        if (strcmp(module->entries[i].name, name) == 0) {
            return &module->entries[i];
        }
    }
    return NULL;
}

Value module_call(Module* module, const char* name, Value* args, size_t arg_count) {
    ModuleEntry* entry = module_get_entry(module, name);
    if (entry == NULL) {
        fprintf(stderr, "Module entry not found: %s\n", name);
        exit(1);
    }

    if (entry->type == ENTRY_FUNCTION) {
        return entry->data.function_call(module, args, arg_count);
    } else if (entry->type == ENTRY_CLASS) {
        // Create a new instance of the class
        Value instance = create_object(entry->data.class_type);

        // Call the constructor (init method) if it exists
        for (size_t i = 0; i < entry->data.class_type->base.method_count; i++) {
            if (strcmp(entry->data.class_type->base.method_names[i], "init") == 0) {
                entry->data.class_type->base.methods[i](module, &instance, args, arg_count);
                return instance;
            }
        }

        // If no init method and args were provided, throw an error
        if (arg_count > 0) {
            fprintf(stderr, "Constructor called with arguments, but no init method defined for class %s\n", name);
            exit(1);
        }

        return instance;
    }

    fprintf(stderr, "Invalid module entry type\n");
    exit(1);
}

Value value_equal(Value left, Value right) {
    if (left.type != right.type) return create_int(0);
    switch (left.type) {
        case TYPE_INT:
            return create_int(left.data.int_value == right.data.int_value);
        case TYPE_ARRAY:
            if (left.data.array.length != right.data.array.length) return create_int(0);
            for (size_t i = 0; i < left.data.array.length; i++) {
                if (!value_equal(left.data.array.elements[i], right.data.array.elements[i]).data.int_value) {
                    return create_int(0);
                }
            }
            return create_int(1);
        case TYPE_OBJECT:
            return create_int(left.data.object.class_type == right.data.object.class_type);
        case TYPE_NULL:
            return create_int(1);
    }
    return create_int(0);
}

Value value_not_equal(Value left, Value right) {
    return create_int(!value_equal(left, right).data.int_value);
}

Value value_greater(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot compare non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value > right.data.int_value);
}

Value value_less(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot compare non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value < right.data.int_value);
}

Value value_greater_equal(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot compare non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value >= right.data.int_value);
}

Value value_less_equal(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot compare non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value <= right.data.int_value);
}

Value value_add(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot add non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value + right.data.int_value);
}

Value value_subtract(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot subtract non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value - right.data.int_value);
}

Value value_multiply(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot multiply non-integer values\n");
        exit(1);
    }
    return create_int(left.data.int_value * right.data.int_value);
}

Value value_divide(Value left, Value right) {
    if (left.type != TYPE_INT || right.type != TYPE_INT) {
        fprintf(stderr, "Cannot divide non-integer values\n");
        exit(1);
    }
    if (right.data.int_value == 0) {
        fprintf(stderr, "Division by zero\n");
        exit(1);
    }
    return create_int(left.data.int_value / right.data.int_value);
}

Value value_negate(Value v) {
    if (v.type != TYPE_INT) {
        fprintf(stderr, "Cannot negate non-integer value\n");
        exit(1);
    }
    return create_int(-v.data.int_value);
}

Value value_not(Value v) {
    if (v.type != TYPE_INT) {
        fprintf(stderr, "Cannot apply logical not to non-integer value\n");
        exit(1);
    }
    return create_int(!v.data.int_value);
}

Value value_to_string(Value v) {
    if (v.type != TYPE_INT) {
        fprintf(stderr, "TODO: toString non-integer value\n");
        exit(1);
    }
    int i = v.data.int_value;
    char* buf = malloc(16);
    int length = snprintf(buf, 16, "%d", i);
    Value* elements = malloc(sizeof(Value) * length);
    for (int j = 0; j < length; j++) {
        elements[j] = create_int(buf[j]);
    }
    return create_array(elements, length);
}

Value instance_of(Value obj, const char* type_name) {
    if (obj.type != TYPE_OBJECT) {
        fprintf(stderr, "Cannot call instanceOf() on non-object\n");
        exit(1);
    }
    ClassType* current_type = obj.data.object.class_type;
    while (current_type != NULL) {
        if (strcmp(current_type->name, type_name) == 0) {
            return obj;
        }
        current_type = current_type->parent;
    }
    return create_null();
}
