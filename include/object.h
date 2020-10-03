#ifndef CPEG_OBJECT_H
#define CPEG_OBJECT_H

#include "stddef.h"

// pointer to an object
typedef struct object_t *VALUE;


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

typedef enum {
    FCompare_Equal,
    FCompare_NotEqual,
    FCompare_LessThan,
    FCompare_LessEqual,
    FCompare_GreaterThan,
    FCompare_GreaterEqual
} FCompareOp;

typedef enum {
    FBinop_Add,
    FBinop_Subtract,
    FBinop_Multiply,
    FBinop_Divide,
    FBinop_FloorDivide,
    FBinop_Modulus,
    FBinop_DivideModulus,
    FBinop_Power,
    FBinop_LeftShift,
    FBinop_RightShift,
    FBinop_And,
    FBinop_Or,
    FBinop_Xor,
    FBinop_MatrixMultiply,
} FBinaryOp;

typedef enum {
    FUnary_Negative,
    FUnary_Positive,
    FUnary_Absolue,
    FUnary_Invert,
    FUnary_AsInteger,
    FUnary_AsFloat,
    FUnary_Round,
    FUnary_Truncate,
    FUnary_Floor,
    FUnary_Ceil,
    FUnary_AsString,
    FUnary_AsRepr,
    FUnary_AsIterator,
    FUnary_Next
} FUnaryOp;

typedef struct object_t FBaseObject;

#define FObject_Base FBaseObject base

typedef struct type_object_t FTypeObject;

struct object_t {
    size_t refcount;
    FTypeObject *type;
};

struct type_object_t {
    FObject_Base;

    const char *type_name;
    size_t type_alloc_size;
    size_t type_flags;

    VALUE type_dict;

    int (*fast_bool)(VALUE a);
    int (*fast_compare)(VALUE a, VALUE b, FCompareOp compare_op);
    size_t (*fast_hash)(VALUE a);
    size_t (*fast_length)(VALUE a);

    VALUE (*fast_unary_op)(VALUE a, FUnaryOp unary_op);
    VALUE (*fast_binary_op)(VALUE a, VALUE b, FBinaryOp binary_op);

    VALUE (*fast_get_item)(VALUE a, size_t index);
    VALUE (*fast_set_item)(VALUE a, size_t index);
    VALUE (*fast_get_key)(VALUE a, VALUE key);
    VALUE (*fast_set_key)(VALUE a, VALUE key, VALUE value);
    VALUE (*fast_get_attr)(VALUE a, char *name);
    VALUE (*fast_set_attr)(VALUE a, char *name, VALUE value);

    FCallable fast_call;
};

#define INCREF(ob) (++(ob)->refcount)
#define DECREF(ob) (--(ob)->refcount)

#endif //CPEG_OBJECT_H
