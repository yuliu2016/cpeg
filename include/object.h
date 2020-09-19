#ifndef CPEG_OBJECT_H
#define CPEG_OBJECT_H

#include "stddef.h"

typedef struct type_object_t FTypeObject;

typedef struct object_t {
    size_t refcount;
    FTypeObject *type;
} FObject;

typedef FObject *VALUE;

typedef FObject * (*unaryfunc)(FObject *);
typedef FObject * (*binaryfunc)(FObject *, FObject *);
typedef FObject * (*ternaryfunc)(FObject *, FObject *, FObject *);
typedef int (*inquiry)(FObject *);
typedef size_t (*lenfunc)(FObject *);
typedef FObject *(*ssizeargfunc)(FObject *, size_t);
typedef FObject *(*ssizessizeargfunc)(FObject *, size_t, size_t);
typedef int(*ssizeobjargproc)(FObject *, size_t, FObject *);
typedef int(*ssizessizeobjargproc)(FObject *, size_t, size_t, FObject *);
typedef int(*objobjargproc)(FObject *, FObject *, FObject *);

typedef int (*objobjproc)(FObject *, FObject *);
typedef int (*visitproc)(FObject *, void *);
typedef int (*traverseproc)(FObject *, visitproc, void *);

typedef void (*freefunc)(void *);
typedef void (*destructor)(FObject *);
typedef FObject *(*getattrfunc)(FObject *, char *);
typedef FObject *(*getattrofunc)(FObject *, FObject *);
typedef int (*setattrfunc)(FObject *, char *, FObject *);
typedef int (*setattrofunc)(FObject *, FObject *, FObject *);

typedef unaryfunc reprfunc;
typedef size_t (*hashfunc)(FObject *);
typedef FObject *(*richcmpfunc) (FObject *, FObject *, int);
typedef FObject *(*getiterfunc) (FObject *);
typedef FObject *(*iternextfunc) (FObject *);
typedef FObject *(*descrgetfunc) (FObject *, FObject *, FObject *);
typedef int (*descrsetfunc) (FObject *, FObject *, FObject *);
typedef int (*initproc)(FObject *, FObject *, FObject *);
typedef FObject *(*newfunc)(FTypeObject *, FObject *, FObject *);
typedef FObject *(*allocfunc)(FTypeObject *, size_t);

struct type_object_t {
    FObject base;
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
