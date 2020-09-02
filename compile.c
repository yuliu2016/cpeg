#include "include/astgen.h"

#define UNPACK_AS_NAME(node) \
    ASSERT_AST_T(node, R_AS_NAME); \
    FAstNode *name = (node)->ast_v.fields[0];