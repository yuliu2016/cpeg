#ifndef CPEG_OBJECT_H
#define CPEG_OBJECT_H

#include "stddef.h"

typedef struct object_t {
    size_t refcount;
} FObject;

#define INCREF(ob) (++(ob)->refcount)
#define DECREF(ob) (--(ob)->refcount)

#endif //CPEG_OBJECT_H
