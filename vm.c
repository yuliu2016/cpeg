#include "include/vm.h"
#include "mem.h"

void FCoroutine_suspend(RESULT r) {
    r->res_state = FResult_Suspend;
    r->res_coroutine = NULL;
    r->res_value = NULL;
}

void FCoroutine_resume(RESULT r, FObject *coroutine, FObject *value) {
    r->res_state = FResult_Resume;
    r->res_coroutine = coroutine;
    r->res_value = value;
}