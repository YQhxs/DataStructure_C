#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 0;

typedef struct {
    int *elem;
    int length;
    int listSize;
}SqList;

int InitListSq(SqList *sqList){
//     dynamic allocation
    sqList->elem  = (int *)malloc(sizeof(int)*LIST_INIT_SIZE);
    if(!sqList->elem){
        exit(-1);
    }
    sqList->length=0;
    sqList->listSize=LIST_INIT_SIZE;
    return OK;
}

int main() {
    SqList listA;
    InitListSq(&listA);
    return 0;
}