#ifndef CPEG_FLOAT_TYPE_H
#define CPEG_FLOAT_TYPE_H

#include "../object.h"

typedef struct float_t {
    FObject_Base;

    double float_val;
} FFloat;

#endif //CPEG_FLOAT_TYPE_H
