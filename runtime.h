#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_ARRAY,
    TYPE_OBJECT,
    TYPE_NULL
} ValueType;

typedef struct Value Value;
typedef struct Type Type;
typedef struct ClassType ClassType;
typedef struct Module Module;

struct Value {
    ValueType type;
    union {
        int64_t int_value;
        struct {
            Value* elements;
            size_t length;
            size_t capacity;
        } array;
        struct {
            ClassType* class_type;
            Value* fields;
        } object;
    } data;
};

typedef Value (*MethodFunc)(Module* mod, Value* this_ptr, Value* args, size_t arg_count);

struct Type {
    MethodFunc* methods;
    char** method_names;
    size_t method_count;
};

struct ClassType {
    Type base;
    char* name;
    ClassType* parent;
    char** field_names;
    size_t field_count;
};

typedef enum {
    ENTRY_FUNCTION,
    ENTRY_CLASS
} EntryType;

typedef struct {
    char* name;
    EntryType type;
    union {
        Value (*function_call)(Module* mod, Value* args, size_t arg_count);
        ClassType* class_type;
    } data;
} ModuleEntry;

struct Module {
    ModuleEntry* entries;
    size_t entry_count;
};

// Value creation functions
Value create_int(int64_t value);
Value create_array(Value* elements, size_t length);
Value create_object(ClassType* class_type);
Value create_null();

// Array operations
Value array_get(Value array, size_t index);
void array_set(Value array, size_t index, Value value);
Value array_push(Value* array, Value element);
Value array_slice(Value array, size_t start, size_t end);
Value array_concat(Value array1, Value array2);
Value array_length(Value array);
Value array_join(Value array, Value separator);
Value array_to_int(Value array);

// Object operations
Value* object_get_field(Value object, const char* field_name);
void object_set_field(Value* object, const char* field_name, Value value);

// Method calling
Value call_method(Module* mod, Value* value, const char* method_name, Value* args, size_t arg_count);

// Module operations
Module* create_module();
void module_add_entry(Module* module, ModuleEntry entry);
ModuleEntry* module_get_entry(Module* module, const char* name);
Value module_call(Module* module, const char* name, Value* args, size_t arg_count);

// Utility functions
Value print_value(Module* mod, Value* args, size_t arg_count);
Value read_file(Module* mod, Value* args, size_t arg_count);
Value write_file(Module* mod, Value* args, size_t arg_count);
Value assert_value(Module* mod, Value* args, size_t arg_count);
Value value_to_string(Value v);

// Comparison operations
Value value_equal(Value left, Value right);
Value value_not_equal(Value left, Value right);
Value value_greater(Value left, Value right);
Value value_less(Value left, Value right);
Value value_greater_equal(Value left, Value right);
Value value_less_equal(Value left, Value right);

// Arithmetic operations
Value value_add(Value left, Value right);
Value value_subtract(Value left, Value right);
Value value_multiply(Value left, Value right);
Value value_divide(Value left, Value right);
Value value_negate(Value v);
Value value_not(Value v);

// Type checking
Value instance_of(Value obj, const char* type_name);

#endif // RUNTIME_H
