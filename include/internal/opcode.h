#ifndef CPEG_OPCODE_H
#define CPEG_OPCODE_H

typedef enum opcode_t {

    // Stack Operations
    NOP,
    POP_TOP,
    ROT_TWO,
    ROT_THREE,
    ROT_FOUR,
    DUP_TOP,
    DUP_TOP_TWO,

    // Load/Store/Delete
    LOAD_CONST,
    LOAD_NAME,
    LOAD_INDEX,
    LOAD_ATTR,
    STORE_NAME,
    STORE_INDEX,
    STORE_ATTR,
    STORE_SUBSCR,
    DELETE_SUBSCR,
    DELETE_NAME,
    DELETE_ATTR,

    // Operators
    UNARY_OP,
    BINARY_OP,
    INPLACE_OP,
    COMPARE_OP,

    // Calling
    CALL_FUNCTION,
    RETURN_VALUE,

    // Control Flow
    JUMP_FORWARD,
    JUMP_ABSOLUTE,
    POP_JUMP_IF_TRUE,
    POP_JUMP_IF_FALSE,
    JUMP_IF_TRUE_OR_POP,
    JUMP_IF_FALSE_OR_POP,
    FOR_ITER,

} FOpcode;

#endif //CPEG_OPCODE_H
