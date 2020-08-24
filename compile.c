#include "astgen.h"

FTokenStr *test_compile(FAstNode *node) {
    FAstNode *n = ASC(node)->as_name.name;
    FToken *aux = AST_GET_TOKEN(n);
    return aux->str;
}