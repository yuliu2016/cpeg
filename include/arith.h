#ifndef CPEG_ARITH_H
#define CPEG_ARITH_H

#include "object.h"

static FTypeObject FFloatType;

#define OBJECT_IS_FLOAT(ob) ((ob)->type == &FFloatType)

#endif //CPEG_ARITH_H
