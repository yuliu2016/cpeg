#ifndef CPEG_CALL_H
#define CPEG_CALL_H

#include "object.h"


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

typedef void (*FCallable)(FCallState *cstate);

#define F_CALLABLE(name) void name(FCallState *cstate)

#endif //CPEG_CALL_H
