#include "symbolTable.h"

void initScope(){
    curScope = (struct scope*)malloc(sizeof(struct scope));
    curScope->scopeDepth = 0;
    curScope->funcCount = 0;
    curScope->varCount = 0;
    curScope->scopeCount = 0;
    curScope->id_literal = "root";
    curScope->scopeList = NULL;
    curScope->varList = NULL;
    curScope->funcList = NULL;
    curScope->parent = NULL;
    rootScope = curScope;
}

void pushScope(char* id_literal){
    struct scope *temp = (struct scope*)malloc(sizeof(struct scope));
    temp->scopeDepth = (curScope->scopeDepth)+1;
    temp->funcCount = 0;
    temp->varCount = 0;
    temp->scopeCount = 0;
    temp->scopeList = NULL;
    temp->varList = NULL;
    temp->funcList = NULL;
    temp->parent = curScope;
    temp->id_literal = strdup(id_literal);
    curScope->scopeCount += 1;

    struct scope **List = (struct scope**)malloc((temp->scopeCount)*sizeof(struct scope*));
    if(curScope->scopeList != NULL){
        int i;
        for(i = 0; i<curScope->scopeCount-1; i++)
        {
            List[i] = (curScope->scopeList)[i];
        }
        free(curScope->scopeList);
        curScope->scopeList = List;
        List[i] = temp;

    } else {
        List[0] = temp;
        curScope->scopeList = List;
    }
    curScope = temp;   
        // printf("++++++++++++++++++++++++\n");

}

void popScope(){
    curScope = curScope->parent;
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
        temp[i]->id_literal = strdup(id_literal);
        temp[i]->list = list;
        temp[i]->valTYPE = valTYPE;
        curScope->funcList = temp;
    } else {
        temp[0] = (struct funcsym*)malloc(sizeof(struct funcsym));
        temp[0]->id_literal = strdup(id_literal);
        temp[0]->list = list;
        temp[0]->valTYPE = valTYPE;
        curScope->funcList = temp;
    }
    
}
void pushVarSym(){
    curScope->varCount+=1;
}



void dumpSymTab(){
    ScopeQue = (struct scopeQueue*)malloc(sizeof(struct scopeQueue));
    ScopeQue->top = ScopeQue->bottom = NULL;
    if(rootScope!=NULL){
        struct scope* temp = rootScope;
        pushScopeQueue(temp);
        
        while(NULL!=(temp = popScopeQueue())){
            printf("\n%s:: scope count : %d, var count : %d\n", 
                temp->id_literal, 
                temp->scopeCount,
                temp->varCount
            );
            for(int i=0; i<temp->scopeCount; i++){
                printf("->");
                printf("\t%s:\n",((temp->scopeList)[i])->id_literal);
                pushScopeQueue((temp->scopeList)[i]);
            }
            printf("-------------------------------------\n");
        }
    }
}


void pushScopeQueue(struct scope* thisSope){
    if(thisSope!=NULL){
        struct scopeLIST* temp = (struct scopeLIST*)malloc(sizeof(struct scopeLIST));
        temp->thisScope = thisSope;
        temp->next = NULL;
        if(ScopeQue->top==NULL && ScopeQue->bottom==NULL){
            ScopeQue->bottom = ScopeQue->top = temp;
        } else {
            (ScopeQue->bottom)->next = temp;
            (ScopeQue->bottom) = temp;
        }
    }
}

struct scope* popScopeQueue(){
    struct scopeLIST* thisNode;
    struct scope* thisScope = NULL;
    if(ScopeQue->top==NULL && ScopeQue->bottom==NULL){
        ;
    } else if(ScopeQue->top==ScopeQue->bottom){
        thisScope = (ScopeQue->top)->thisScope;
        thisNode = (ScopeQue->top);
        (ScopeQue->top) = NULL;
        (ScopeQue->bottom) = NULL;
        free(thisNode);
    }
    else{
        thisScope = (ScopeQue->top)->thisScope;
        thisNode = (ScopeQue->top);
        (ScopeQue->top) = (ScopeQue->top)->next;
        free(thisNode);
    }
    return thisScope;
}