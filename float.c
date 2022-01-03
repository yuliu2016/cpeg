#include "include/mem.h"
#include "include/float.h"
#include "include/internal/float_type.h"
#include "math.h"
#include "stdlib.h"

VALUE FFloat_from_double(double d) {
    FFloat *fobj = malloc(sizeof(FFloat));
    fobj->float_val = d;
    return (VALUE) fobj;
}

VALUE float_binop(VALUE a, VALUE b, FBinaryOp binop) {
    if (!OBJECT_IS_FLOAT(a)) {
        return NULL;
    }
    double d1 = ((FFloat *) a)->float_val;
    double d2;
    if (OBJECT_IS_FLOAT(a)) {
        d2 = ((FFloat *) b)->float_val;
    } else {
        return 0;
    }
    double r;
    switch (binop) {
        case FBinop_Add:
            r = d1 + d2;
            break;
        case FBinop_Subtract:
            r = d1 - d2;
            break;
        case FBinop_Multiply:
            r = d1 * d2;
            break;
        case FBinop_Divide:
            r = d1 / d2;
            break;
        case FBinop_FloorDivide:
            r = floor(d1 / d2);
            break;
        case FBinop_Modulus:
            r = fmod(d1, d2);
            break;
        case FBinop_DivideModulus:
            r = 0;
            break;
        case FBinop_Power:
            r = pow(d1, d2);
            break;
        case FBinop_LeftShift:
        case FBinop_RightShift:
        case FBinop_And:
        case FBinop_Or:
        case FBinop_Xor:
        case FBinop_MatrixMultiply:
        default:
            r = 0;
            break;
    }
    return FFloat_from_double(r);
}

VALUE float_as_string(double d1) {
    return 0;
}

VALUE float_unary(VALUE a, FUnaryOp unary) {
    if (!OBJECT_IS_FLOAT(a)) {
        return NULL;
    }
    double d1 = ((FFloat *) a)->float_val;
    double r;
    switch (unary) {
        case FUnary_Negative:
            r = -d1;
            break;
        case FUnary_Positive:
            r = d1;
            break;
        case FUnary_Absolue:
            r = fabs(d1);
            break;
        case FUnary_Invert:
            r = 0;
            break;
        case FUnary_AsInteger:
            r = floor(d1);
            break;
        case FUnary_AsFloat:
            r = d1;
            break;
        case FUnary_Round:
            r = floor(d1 + 0.5);
            break;
        case FUnary_Truncate:
        case FUnary_Floor:
            r = floor(d1);
            break;
        case FUnary_Ceil:
            r = ceil(d1);
            break;
        case FUnary_AsString:
        case FUnary_AsRepr:
            return float_as_string(d1);
        case FUnary_AsIterator:
        case FUnary_Next:
            r = d1;
            break;
        default:
            r = 0;
            break;
    }
    return FFloat_from_double(r);
}

static FTypeObject FFloatType = {
        0,
        0,
        "float",
        sizeof(FFloat),
        0,
        0,
        0,
        0,
        0,
        0,
        float_unary,
        float_binop,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
};