#include "symbolTable.h"

void initScope(){
    curScope = (struct scope*)malloc(sizeof(struct scope));
    curScope->scopeDepth = 0;
    curScope->funcCount = 0;
    curScope->varCount = 0;
    curScope->next = NULL;
    curScope->varList = NULL;
    curScope->funcList = NULL;
}

void pushScope(){
    struct scope *temp = (struct scope*)malloc(sizeof(struct scope));
    temp->scopeDepth = (curScope->scopeDepth)+1;
    temp->funcCount = 0;
    temp->varCount = 0;
    temp->next = curScope;
    curScope = temp;
    temp->varList = NULL;
    temp->funcList = NULL;
}

void popScope(){
    curScope = curScope->next;
}

void pushfucsym
(
    enum dataTYPE valTYPE,
    char* id_literal,
    struct varsym *list
)
{
    curScope->funcCount += 1;
    struct funcsym** temp = (struct funcsym**)malloc((curScope->funcCount)*(sizeof(struct funcsym*)));
    if(curScope->funcList!=NULL){
        int i;
        for(i = 0; i<curScope->funcCount-1; i++)
        {
            temp[i] = (curScope->funcList)[i];
        }
        free(curScope->funcList);
        temp[i] = (struct funcsym*)malloc(sizeof(struct funcsym));
        temp[i]->id_literal = id_literal;
        temp[i]->list = list;
        temp[i]->valTYPE = valTYPE;
        curScope->funcList = temp;
    } else {
        curScope->funcList = temp;
    }
    
}
void pushVarSym(){
    curScope->varCount+=1;
}
