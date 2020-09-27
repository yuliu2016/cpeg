#ifndef CPEG_OBJECT_H
#define CPEG_OBJECT_H

#include "stddef.h"

// pointer to an object
typedef struct object_t *VALUE;

typedef struct object_t FBaseObject;
typedef struct type_object_t FTypeObject;

// Calling state - use a struct to include both args and return values
typedef struct call_state_t {

    enum {
        FArgsType_FastArgs,
        FArgsType_Sequence,
        FArgsType_WithKwargs
    } args_type;

    size_t nargs;

    union {
        VALUE fastargs[4]; // used when # of args < 4
        VALUE args_as_sequence; // args if it's a list/tuple object
        VALUE kwargs_as_dict;  // dictionary of keyword arguments
    };

    enum {
        FResult_Pending,         // No result is set
        FResult_Ok,              // successfully returns (no further calls)
        FResult_Exception,       // error/exception raised
        FResult_Suspend,         // suspends the current coroutine object
        FResult_Resume,          // resumes a certain coroutine object
        FResult_ResumeError,     // resumes a certain coroutine object
        FResult_InvokeCompiled   // A new block of code is called
    } result;

    // result values
    union {
        VALUE fastreturns[4]; // used when # of return values < 4
        VALUE exception; // used when call returns an exception
        VALUE invocation; // used when call returns a compiled function
        VALUE suspension; // the value to suspend the coroutine with
        struct {
            VALUE coroutine_to_resume; // the coroutine object to be resumed
            union {
                VALUE resume_with; // resume with a normal value
                VALUE resume_with_exception; // resume with an exception
            };
        } resumption; // used to resume a coroutine
    };
} FCallState;

typedef void (*FCallable)(struct call_state_t *cstate);

#define F_CALLABLE(name) void name(FCallState *cstate)

struct object_t {
    size_t refcount;
    FTypeObject *type;
};

#define FObject_Base FBaseObject base

struct type_object_t {
    FObject_Base;

    const char *type_name;
    size_t type_alloc_size;

    VALUE dict;

    int (*obj_fast_compare)(VALUE a, VALUE b, int compare_t);
    size_t (*obj_fast_hash)(VALUE a);
    size_t (*obj_fast_length)(VALUE a);
    VALUE (*obj_fast_str)(VALUE a);
    VALUE (*obj_fast_repr)(VALUE a);
    VALUE (*obj_fast_binary_op)(VALUE a, VALUE b, int binary_op);
    VALUE (*obj_fast_unary_op)(VALUE a, int unary_op);
    VALUE (*obj_fast_item)(VALUE a, size_t index);
    VALUE (*obj_fast_set_item)(VALUE a, size_t index);
    VALUE (*obj_fast_key)(VALUE a, VALUE key);
    VALUE (*obj_fast_set_key)(VALUE a, VALUE key, VALUE value);
    VALUE (*obj_fast_attr)(VALUE a, char *name);
    VALUE (*obj_fast_set_attr)(VALUE a, char *name, VALUE value);
};

#define INCREF(ob) (++(ob)->refcount)
#define DECREF(ob) (--(ob)->refcount)

#endif //CPEG_OBJECT_H
