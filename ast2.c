#include "include/ast2.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>


/*
sum[double] (left_recursive):
    | sum '+' term { "binop_add(p, %a, %b)" }
    | sum '-' term { "binop_sub(p, %a, %b)" }
    | term { a }
term[double] (left_recursive):
    | term '*' factor { "binop_mul(p, %a, %b)" }
    | term '/' factor { "binop_div(p, %a, %b)" }
    | term '%' factor { "binop_mod(p, %a, %b)" }
    | factor { a }
factor[double]:
    | '+' factor { "unary_plus(p, %a)" }
    | '-' factor { "unary_minus(p, %a)" }
    | '~' factor { "unary_not(p, %a)" }
    | power { a }
power[double]:
    | atom '**' factor { "binop_pow(p, %a, %b)" }
    | atom { a }
atom[double]:
    | '(' sum ')' { a }
    | NAME '(' [parameters] ')' { "call_func(p, %a, %b)" }
    | NAME { "load_const(p, %a)" }
    | NUMBER { "to_double(p, %a)" }
parameters[ast_list_t]:
    | ','.sum+ [','] { a }
    */

static double *doubleptr(parser_t *p, double v) {
    double *r = mballoc(p->region, sizeof(double));
    if (r) *r = v;
    return r;
}

double *binop_add(parser_t *p, double *a, double *b) {
    return doubleptr(p, *a + *b);
}

double *binop_sub(parser_t *p, double *a, double *b) {
    return doubleptr(p, *a - *b);
}


double *binop_mul(parser_t *p, double *a, double *b) {
    return doubleptr(p, *a * *b);
}


double *binop_div(parser_t *p, double *a, double *b) {
    if (*b == 0) {
        p->errorcode = -1;
        return 0;
    }
    return doubleptr(p, *a / *b);
}

double *binop_mod(parser_t *p, double *a, double *b) {
    if (*b == 0) {
        return 0;
    }
    return doubleptr(p, fmod(*a, *b));
}


double *binop_pow(parser_t *p, double *a, double *b) {
    return doubleptr(p, pow(*a, *b));
}

double *unary_plus(parser_t *p, double *a) {
    return a;
}

double *unary_minus(parser_t *p, double *a) {
    return doubleptr(p, -*a);
}

double *unary_not(parser_t *p, double *a) {
    p->errorcode = -1;
    return 0;
}


double *load_const(parser_t *p, token_t *token) {

    char *v = token_nullterm_view(token);
    double *r = 0;
    if (strncmp("pi", v, 3) == 0) {
        r = doubleptr(p, 3.141592653589793);
    } else if (strncmp("e", v, 2) == 0) {
        r = doubleptr(p, 2.718281828459045);
    } else if (strncmp("rand", v, 5) == 0) {
        r = doubleptr(p, rand() / (double) RAND_MAX);
    }
    token_nullterm_restore();
    return r;
}

static int first_param(ast_list_t *params, double *d) {
    if (params->len != 1) {
        return 0;
    }
    *d = *((double *) params->items[0]);
    return 1;
}


static int no_params(ast_list_t *params) {
    return !params || params->len == 0;
}


double *call_func(parser_t *p, token_t *name, ast_list_t *params) {

    double r = 0, first;
    char *func_name = token_nullterm_view(name);

    if (strcmp("sum", func_name) == 0) {

    } else if (strcmp("sum", func_name) == 0) {

    } else if (strcmp("max", func_name) == 0) {

    } else if (strcmp("min", func_name) == 0) {

    } else if (strcmp("hypot", func_name) == 0) {

    } else if (strcmp("average", func_name) == 0) {

    } else if (strcmp("mean", func_name) == 0) {

    } else if (strcmp("var", func_name) == 0) {

    } else if (strcmp("stddev", func_name) == 0) {

    } else if (strcmp("fib", func_name) == 0) {

    } else if (strcmp("sin", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = sin(first);
    } else if (strcmp("cos", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = cos(first);
    } else if (strcmp("tan", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = tan(first);
    } else if (strcmp("sinh", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = sinh(first);
    } else if (strcmp("cosh", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = cosh(first);
    } else if (strcmp("tanh", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = tanh(first);
    } else if (strcmp("asin", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = asin(first);
    } else if (strcmp("acos", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = acos(first);
    } else if (strcmp("atan", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = atan(first);
    } else if (strcmp("abs", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = fabs(first);
    } else if (strcmp("log", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = log10(first);
    } else if (strcmp("sqrt", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = sqrt(first);
    } else if (strcmp("degrees", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = first * 180 / 3.141592653589793;
    } else if (strcmp("radians", func_name) == 0) {
        if (!first_param(params, &first)) return 0;
        r = first * 3.141592653589793 / 180;
    } else if (strcmp("random", func_name) == 0) {
        if (!no_params(params)) return 0;
        r = rand() / (double) RAND_MAX;
    } else {
        return 0;
    }

    return doubleptr(p, r);
}

double *to_double(parser_t *p, token_t *tok) {
    char *v = token_nullterm_view(tok);
    double *r = doubleptr(p, strtod(v, NULL));
    token_nullterm_restore();
    return r;
}