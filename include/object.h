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
typedef struct object_t* VALUE;

typedef VALUE (*unaryfunc)(VALUE);
typedef VALUE (*binaryfunc)(VALUE, VALUE);
typedef VALUE (*ternaryfunc)(VALUE, VALUE, VALUE);
typedef int (*inquiry)(VALUE);
typedef size_t (*lenfunc)(VALUE);
typedef VALUE (*ssizeargfunc)(VALUE, size_t);
typedef VALUE (*ssizessizeargfunc)(VALUE, size_t, size_t);
typedef int (*ssizeobjargproc)(VALUE, size_t, VALUE);
typedef int (*ssizessizeobjargproc)(VALUE, size_t, size_t, VALUE);
typedef int (*objobjargproc)(VALUE, VALUE, VALUE);

typedef int (*objobjproc)(VALUE, VALUE);
typedef int (*visitproc)(VALUE, void *);
typedef int (*traverseproc)(VALUE, visitproc, void *);

typedef void (*freefunc)(void *);
typedef void (*destructor)(VALUE);
typedef VALUE (*getattrfunc)(VALUE, char *);
typedef VALUE (*getattrofunc)(VALUE, VALUE);
typedef int (*setattrfunc)(VALUE, char *, VALUE);
typedef int (*setattrofunc)(VALUE, VALUE, VALUE);

typedef unaryfunc reprfunc;
typedef size_t (*hashfunc)(VALUE);
typedef VALUE (*richcmpfunc)(VALUE, VALUE, int);
typedef VALUE (*getiterfunc)(VALUE);
typedef VALUE (*iternextfunc)(VALUE);
typedef VALUE (*descrgetfunc)(VALUE, VALUE, VALUE);
typedef int (*descrsetfunc)(VALUE, VALUE, VALUE);
typedef int (*initproc)(VALUE, VALUE, VALUE);
typedef VALUE (*newfunc)(FTypeObject *, VALUE, VALUE);
typedef VALUE (*allocfunc)(FTypeObject *, size_t);

struct type_object_t {
    FObject_Base;

    const char *tp_name;
    size_t tp_size;

    destructor tp_dealloc;
    unaryfunc tp_unary_op;
    binaryfunc tp_binary_op;
    reprfunc tp_repr;
};

#define INCREF(ob) (++(ob)->refcount)
#define DECREF(ob) (--(ob)->refcount)

#endif //CPEG_OBJECT_H
