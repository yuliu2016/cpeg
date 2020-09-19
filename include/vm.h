#ifndef CPEG_VM_H
#define CPEG_VM_H

#include "object.h"

typedef enum result_state_t {
    FResult_Ok,
    FResult_Error,
    FResult_Suspend,
    FResult_Resume,
    FResult_NewFrame
} FResultState;

typedef struct result_t {
    FResultState res_state;
    VALUE res_coroutine;
    VALUE res_args;
} FResult;

typedef FResult *RESULT;

#endif //CPEG_VM_H
