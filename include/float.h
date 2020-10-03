#ifndef CPEG_FLOAT_H
#define CPEG_FLOAT_H

#include "object.h"

static FTypeObject FFloatType;

#define OBJECT_IS_FLOAT(ob) ((ob)->type == &FFloatType)

#endif //CPEG_FLOAT_H
