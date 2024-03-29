#ifndef CPEG_TOKENMAP_H
#define CPEG_TOKENMAP_H


#define T_ENDMARKER 1  // ENDMARKER
#define T_NEWLINE 2  // NEWLINE
#define T_NAME 3  // NAME
#define T_NUMBER 4  // NUMBER
#define T_STRING 5  // STRING
#define T_DOT 6  // .
#define T_COMMA 7  // ,
#define T_ASSIGN 8  // =
#define T_COLON 9  // :
#define T_TERNERY 10  // ?
#define T_EXCLAIM 11  // !
#define T_SEMICOLON 12  // ;
#define T_LPAR 13  // (
#define T_RPAR 14  // )
#define T_LBRACE 15  // {
#define T_RBRACE 16  // }
#define T_LSQB 17  // [
#define T_RSQB 18  // ]
#define T_LESS 19  // <
#define T_GREATER 20  // >
#define T_PLUS 21  // +
#define T_MINUS 22  // -
#define T_TIMES 23  // *
#define T_DIV 24  // /
#define T_MODULUS 25  // %
#define T_MATRIX_TIMES 26  // @
#define T_BIT_OR 27  // |
#define T_BIT_AND 28  // &
#define T_BIT_NOT 29  // ~
#define T_BIT_XOR 30  // ^
#define T_EQUAL 31  // ==
#define T_NEQUAL 32  // !=
#define T_LESS_EQUAL 33  // <=
#define T_MORE_EQUAL 34  // >=
#define T_PIPE 35  // ->
#define T_ASGN_EXPR 36  // :=
#define T_FLOOR_DIV 37  // //
#define T_POWER 38  // **
#define T_PLUS_ASSIGN 39  // +=
#define T_MINUS_ASSIGN 40  // -=
#define T_TIMES_ASSIGN 41  // *=
#define T_DIV_ASSIGN 42  // /=
#define T_MODULUS_ASSIGN 43  // %=
#define T_MATRIX_TIMES_ASSIGN 44  // @=
#define T_BIT_OR_ASSIGN 45  // |=
#define T_BIT_AND_ASSIGN 46  // &=
#define T_BIT_XOR_ASSIGN 47  // ^=
#define T_LSHIFT 48  // <<
#define T_RSHIFT 49  // >>
#define T_FLOOR_DIV_ASSIGN 50  // //=
#define T_POWER_ASSIGN 51  // **=
#define T_LSHIFT_ASSIGN 52  // <<=
#define T_RSHIFT_ASSIGN 53  // >>=
#define T_RETURN 54  // return
#define T_NONLOCAL 55  // nonlocal
#define T_IF 56  // if
#define T_ELIF 57  // elif
#define T_ELSE 58  // else
#define T_AND 59  // and
#define T_OR 60  // or
#define T_NOT 61  // not
#define T_IS 62  // is
#define T_IN 63  // in
#define T_PASS 64  // pass
#define T_AS 65  // as
#define T_FROM 66  // from
#define T_IMPORT 67  // import
#define T_WITH 68  // with
#define T_ASYNC 69  // async
#define T_AWAIT 70  // await
#define T_WHILE 71  // while
#define T_FOR 72  // for
#define T_CONTINUE 73  // continue
#define T_BREAK 74  // break
#define T_TRY 75  // try
#define T_EXCEPT 76  // except
#define T_FINALLY 77  // finally
#define T_RAISE 78  // raise
#define T_DEL 79  // del
#define T_ASSERT 80  // assert
#define T_NONE 81  // None
#define T_TRUE 82  // True
#define T_FALSE 83  // False


static char *indices[] = {
    "",
    "ENDMARKER",
    "NEWLINE",
    "NAME",
    "NUMBER",
    "STRING",
    ".", ",", "=", ":", "?", 
    "!", ";", "(", ")", "{", 
    "}", "[", "]", "<", ">", 
    "+", "-", "*", "/", "%", 
    "@", "|", "&", "~", "^", 
    "==", "!=", "<=", ">=", "->", 
    ":=", "//", "**", "+=", "-=", 
    "*=", "/=", "%=", "@=", "|=", 
    "&=", "^=", "<<", ">>", "//=", 
    "**=", "<<=", ">>=", "return", "nonlocal", 
    "if", "elif", "else", "and", "or", 
    "not", "is", "in", "pass", "as", 
    "from", "import", "with", "async", "await", 
    "while", "for", "continue", "break", "try", 
    "except", "finally", "raise", "del", "assert", 
    "None", "True", "False", ""
};


struct token_literal {
    const char *literal;
    size_t tkl_type;
};

static struct token_literal keywords[] = {
    {"return",   T_RETURN},
    {"nonlocal", T_NONLOCAL},
    {"if",       T_IF},
    {"elif",     T_ELIF},
    {"else",     T_ELSE},
    {"and",      T_AND},
    {"or",       T_OR},
    {"not",      T_NOT},
    {"is",       T_IS},
    {"in",       T_IN},
    {"pass",     T_PASS},
    {"as",       T_AS},
    {"from",     T_FROM},
    {"import",   T_IMPORT},
    {"with",     T_WITH},
    {"async",    T_ASYNC},
    {"await",    T_AWAIT},
    {"while",    T_WHILE},
    {"for",      T_FOR},
    {"continue", T_CONTINUE},
    {"break",    T_BREAK},
    {"try",      T_TRY},
    {"except",   T_EXCEPT},
    {"finally",  T_FINALLY},
    {"raise",    T_RAISE},
    {"del",      T_DEL},
    {"assert",   T_ASSERT},
    {"None",     T_NONE},
    {"True",     T_TRUE},
    {"False",    T_FALSE},
};

static struct token_literal operators[] = {
    {".",   T_DOT},
    {",",   T_COMMA},
    {"=",   T_ASSIGN},
    {":",   T_COLON},
    {"?",   T_TERNERY},
    {"!",   T_EXCLAIM},
    {";",   T_SEMICOLON},
    {"(",   T_LPAR},
    {")",   T_RPAR},
    {"{",   T_LBRACE},
    {"}",   T_RBRACE},
    {"[",   T_LSQB},
    {"]",   T_RSQB},
    {"<",   T_LESS},
    {">",   T_GREATER},
    {"+",   T_PLUS},
    {"-",   T_MINUS},
    {"*",   T_TIMES},
    {"/",   T_DIV},
    {"%",   T_MODULUS},
    {"@",   T_MATRIX_TIMES},
    {"|",   T_BIT_OR},
    {"&",   T_BIT_AND},
    {"~",   T_BIT_NOT},
    {"^",   T_BIT_XOR},
    {"==",  T_EQUAL},
    {"!=",  T_NEQUAL},
    {"<=",  T_LESS_EQUAL},
    {">=",  T_MORE_EQUAL},
    {"->",  T_PIPE},
    {":=",  T_ASGN_EXPR},
    {"//",  T_FLOOR_DIV},
    {"**",  T_POWER},
    {"+=",  T_PLUS_ASSIGN},
    {"-=",  T_MINUS_ASSIGN},
    {"*=",  T_TIMES_ASSIGN},
    {"/=",  T_DIV_ASSIGN},
    {"%=",  T_MODULUS_ASSIGN},
    {"@=",  T_MATRIX_TIMES_ASSIGN},
    {"|=",  T_BIT_OR_ASSIGN},
    {"&=",  T_BIT_AND_ASSIGN},
    {"^=",  T_BIT_XOR_ASSIGN},
    {"<<",  T_LSHIFT},
    {">>",  T_RSHIFT},
    {"//=", T_FLOOR_DIV_ASSIGN},
    {"**=", T_POWER_ASSIGN},
    {"<<=", T_LSHIFT_ASSIGN},
    {">>=", T_RSHIFT_ASSIGN},
};


#endif // CPEG_TOKENMAP_H
