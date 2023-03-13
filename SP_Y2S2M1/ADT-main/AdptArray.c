#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
    DEL_FUNC del_func;
    COPY_FUNC copy_func;
    PRINT_FUNC print_func;
}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df ,PRINT_FUNC pf){
    PAdptArray temp = (PAdptArray)malloc(sizeof(AdptArray));
    if(temp==NULL){
        printf("cant create !!");
        return NULL;
    }
    temp -> ArrSize = 0;
    temp -> pElemArr = NULL;
    temp -> del_func = df;
    temp -> copy_func = cf;
    temp-> print_func = pf;
    printf("create !!");
    return temp;
}

void DeleteAdptArray(PAdptArray p){
    if(p==NULL) return;
    for (int i = 0; i < p -> ArrSize; ++i) {
        p -> del_func(p -> pElemArr[i]);
    }
    free(p->ArrSize);
    free(p);
}
Result SetAdptArrayAt(PAdptArray p, int index, PElement pe){
    if(p==NULL) return FAIL;
    if(index >= p->ArrSize){
        PElement* tempArr = (PElement*)malloc((index+1) * sizeof(PElement));
        if(tempArr == NULL) return FAIL;
        memcpy(tempArr, p->pElemArr, (p->ArrSize) * sizeof(PElement));
        free(p->pElemArr);
        p->pElemArr = tempArr;
    }
    p -> del_func((p -> pElemArr)[index]);
    (p->pElemArr)[index] = p -> copy_func(pe);
    if(index>=p->ArrSize){
        p -> ArrSize = index+1;
    }
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray p, int index){
    if(p==NULL) return NULL;
    if(p->ArrSize<index) return NULL;
    return p->copy_func((p->pElemArr)[index]);
}
int GetAdptArraySize(PAdptArray p){
    if(p==NULL)return -1;
    if(p->pElemArr==NULL) return -1;
    return p->ArrSize;
}
void PrintDB(PAdptArray p){
    if(p==NULL) printf("The PAdptArray you entered is null!");
    if(p->pElemArr==NULL) printf("The pElemArr of the PAdptArray you entered is null!");
    for (int i = 0; i < p->ArrSize; ++i) {
        p->print_func((p->pElemArr)[i]);
    }
}



















