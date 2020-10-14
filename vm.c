#include "include/vm.h"
#include "include/mem.h"
#include "include/internal/opcode.h"


FOpcode get_op() {
    return 0;
}

void FCoroutine_run() {
    FOpcode opcode = get_op();
    int opcode_arg = 0;
    VALUE dummy;

#define POP() 0
#define PUSH(ob) dummy = ob

switch_opcode:
    VALUE a, b, c, d; /* Stack values; a=TOS, b=TOS~1, etc. */
    switch (opcode) {
        case NOP:
            break;
        case POP_TOP:
            POP();
            break;
        case ROT_TWO:
            a = POP();
            b = POP();
            PUSH(b);
            PUSH(a);
            break;
        case ROT_THREE:
            a = POP();
            b = POP();
            c = POP();
            PUSH(b);
            PUSH(c);
            PUSH(a);
            break;
        case ROT_FOUR:
            a = POP();
            b = POP();
            c = POP();
            d = POP();
            PUSH(b);
            PUSH(c);
            PUSH(d);
            PUSH(a);
            break;
        case DUP_TOP:
            a = POP();
            PUSH(a);
            PUSH(a);
            break;
        case DUP_TOP_TWO:
            a = POP();
            b = POP();
            PUSH(b);
            PUSH(b);
            PUSH(a);
            PUSH(a);
            break;
        case LOAD_CONST:
            a = 0;
            PUSH(a);
            break;
        case LOAD_NAME:
            a = 0;
            PUSH(a);
            break;
        case LOAD_INDEX:
            break;
        case LOAD_ATTR:
            break;
        case STORE_NAME:
            break;
        case STORE_INDEX:
            break;
        case STORE_ATTR:
            break;
        case STORE_SUBSCR:
            break;
        case DELETE_SUBSCR:
            break;
        case DELETE_NAME:
            break;
        case DELETE_ATTR:
            break;
        case UNARY_OP:
            a = POP();
            if (a->type->fast_unary_op) {
                PUSH(a->type->fast_unary_op(a, (FUnaryOp) opcode_arg));
            }
            break;
        case BINARY_OP:
            break;
        case INPLACE_OP:
            break;
        case COMPARE_OP:
            break;
        case CALL_FUNCTION:
            break;
        case RETURN_VALUE:
            break;
        case JUMP_FORWARD:
            break;
        case JUMP_ABSOLUTE:
            break;
        case POP_JUMP_IF_TRUE:
            break;
        case POP_JUMP_IF_FALSE:
            break;
        case JUMP_IF_TRUE_OR_POP:
            break;
        case JUMP_IF_FALSE_OR_POP:
            break;
        case FOR_ITER:
            break;
        default:
            break;
    };

process_result:
    FCallState *call = 0;
    switch (call->result) {
        case FResult_Pending:
            break;
        case FResult_Ok:
            break;
        case FResult_Exception:
            break;
        case FResult_Suspend:
            break;
        case FResult_Resume:
            break;
        case FResult_ResumeError:
            break;
        case FResult_InvokeCompiled:
            break;
    }
}