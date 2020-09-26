#ifndef CPEG_OBJECT_H
#define CPEG_OBJECT_H

#include "stddef.h"

typedef struct object_t FBaseObject;
typedef struct type_object_t FTypeObject;

struct object_t {
    size_t refcount;
    FTypeObject *type;
};

#define FObject_Base FBaseObject base

// pointer to an object
typedef struct object_t *VALUE;


struct type_object_t {
    FObject_Base;

    const char *tp_name;
    size_t tp_size;
};

#define INCREF(ob) (++(ob)->refcount)
#define DECREF(ob) (--(ob)->refcount)

#endif //CPEG_OBJECT_H
