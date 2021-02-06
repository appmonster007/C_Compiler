#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
// #include "symQueue.h"


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
    u_int16_t scopeCount;
    char* id_literal;
    struct funcsym **funcList;
    struct varsym **varList;
    struct scope **scopeList;
    struct scope *parent;
};

struct scope *curScope;
struct scope *rootScope;

void initScope();

void pushScope(char* id_literal);

void popScope();

void pushfucsym
(
    enum dataTYPE valTYPE,
    char* id_literal,
    struct varsym *list
);
void pushVarSym();

void dumpSymTab();


struct scopeLIST {
    struct scope* thisScope;
    struct scopeLIST* next;
    
};


struct scopeQueue {
    struct scopeLIST* top;
    struct scopeLIST* bottom;
};

struct scopeQueue *ScopeQue;


struct scope* popScopeQueue();

void pushScopeQueue(struct scope* thisSope);

#endif