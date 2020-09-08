#ifndef CPEG_TOKENIZER_H
#define CPEG_TOKENIZER_H

#include "peg.h"

FToken *FLexer_get_next_token(FLexerState *ls);

FLexerState *FLexer_analyze_all(char *src);

#endif //CPEG_TOKENIZER_H
