#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include<stdio.h>
#include<stdlib.h>

enum dataTYPE {
    INT_t,
    ARRAY_t,
    CHAR_t,
    STRING_t,
    DOUBLE_t,
    FLOAT_t
};

union valptr {
    int* i;
    int** a;
    char* c;
    char** s;
    double *d;
    float* f;
};


struct varsym {
    union valptr addr;
    enum dataTYPE valTYPE;
    char* id_literal;
};

struct funcsym {
    enum dataTYPE valTYPE;
    char* id_literal;
    struct varsym *list;
};

struct scope {
    u_int16_t scopeDepth;
    u_int16_t funcCount;
    u_int16_t varCount;
    struct funcsym **funcList;
    struct varsym **varList;
    struct scope *next;
};

struct scope *curScope;

void initScope();

void pushScope();

void popScope();

void pushfucsym
(
    enum dataTYPE valTYPE,
    char* id_literal,
    struct varsym *list
);
void pushVarSym();


#endif