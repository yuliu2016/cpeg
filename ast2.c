#include "include/ast2.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>


/*
csum[double] (left_recursive):
    | csum '+' cterm { "binop_add(p, %a, %b)" }
    | csum '-' cterm { "binop_sub(p, %a, %b)" }
    | cterm { a }
cterm[double] (left_recursive):
    | cterm '*' cfactor { "binop_mul(p, %a, %b)" }
    | cterm '/' cfactor { "binop_div(p, %a, %b)" }
    | cterm '%' cfactor { "binop_mod(p, %a, %b)" }
    | cfactor { a }
cfactor[double]:
    | '+' cfactor { "unary_plus(p, %a)" }
    | '-' cfactor { "unary_minus(p, %a)" }
    | '~' cfactor { "unary_not(p, %a)" }
    | cpower { a }
cpower[double]:
    | catom '**' cfactor { "binop_pow(p, %a, %b)" }
    | catom { a }
catom[double]:
    | '(' csum ')' { a }
    | NAME '(' [cparameters] ')' { "call_func(p, %a)" }
    | NAME { "load_const(p, %a)" }
    | NUMBER { "to_double(p, %a)" }
cparameters[ast_list_t]:
    | ','.csum+ [','] { a }
    */

double *binop_add(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}

double *binop_sub(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a - *b;
    return r;
}


double *binop_mul(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a * *b;
    return r;
}


double *binop_div(parser_t *p, double *a, double *b) {
    if (*b == 0) {
        p->error = "Division by zero";
        return 0;
    }
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a / *b;
    return r;
}

double *binop_mod(parser_t *p, double *a, double *b) {
    if (*b == 0) {
        return 0;
    }
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = fmod(*a, *b);
    return r;
}


double *binop_pow(parser_t *p, double *a, double *b) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = *a + *b;
    return r;
}

double *unary_plus(parser_t *p, double *a) {
    return a;
}

double *unary_minus(parser_t *p, double *a) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    *r = -*a;
    return r;
}

double *unary_not(parser_t *p, double *a) {
    p->error = "~ operator not allowed";
    return 0;
}


double *load_const(parser_t *p, token_t *token) {

    char *v = token_nullterm_view(token);
    double *r = 0;
    if (strncmp("pi", v, 3) == 0) {
        r = PARSER_ALLOC(p, sizeof(double));
        *r = 3.141592653589793; 
    } else if (strncmp("e", v, 2) == 0) {
        r = PARSER_ALLOC(p, sizeof(double));
        *r = 2.718281828459045; 
    } else if (strncmp("rand", v, 5) == 0) {
         r = PARSER_ALLOC(p, sizeof(double));
         *r = rand() / (double) RAND_MAX;
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

    double *res = PARSER_ALLOC(p, sizeof(double));
    *res = r;
    return res;
}

double *to_double(parser_t *p, token_t *tok) {
    double *r = PARSER_ALLOC(p, sizeof(double));
    char *v = token_nullterm_view(tok);
    *r = strtod(v, NULL);
    token_nullterm_restore();
    return r;
}