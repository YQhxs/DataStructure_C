#include <stdio.h>
#include <stdlib.h>
/**
 * 双向循环链表，带头结点。
 * 除插入删除操作外，其他方法(ListLength、GetElem、LocateElem等)与单链表相同
 * */
#define OK 0;
#define ERROR -1;
typedef struct DuLNode {
    int data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;

int ListInit_DuL(DuLinkList *L) {
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    if (!(*L))
        return ERROR;
    (*L)->prior = (*L)->next = *L;
    return OK;
}

/**
 * 返回指定位置的节点
 * @param L
 * @param i
 * @return
 */
DuLinkList GetElemP_DuL(DuLinkList L, int i) {
    DuLinkList ptr = L->next;
    int j = 1;
    while (ptr != L && j < i) {/*loop i-1 times*/
        ptr = ptr->next;
        ++j;
    }
/*
 * Satisfied situation
 * 1<= i <= n+1 j=i
 * Unsatisfied situation
 * condition (i > j):due to i > n+1
 * condition (j > i):due to i < 1
 * i=0 j=1
 * i>n+1 j=n+1
 */
    if (j != i) {
        return NULL;
    }
    return ptr;
}

/**
 * 1<= i <= n+1，确定插入位置的结点p
 * @param duLinkList
 * @param i
 * @param e
 * @return
 */
int ListInsert_DuL(DuLinkList *duLinkList, int i, int e) {
    DuLinkList ptr = GetElemP_DuL(*duLinkList, i);
    if (!ptr) {
        return ERROR;
    }
    DuLinkList newNode = (DuLinkList) malloc(sizeof(DuLNode));
    if (!newNode) return ERROR;
    newNode->data = e;
    newNode->prior = ptr->prior;
    ptr->prior->next = newNode;
    newNode->next = ptr;
    ptr->prior = newNode;
    return OK;
}

/**
 * 1<=i<=n,Modify the pointer of the previous node first
 * @param duLinkList
 * @param i
 * @param e
 * @return
 */
int ListDelete_DuL(DuLinkList *duLinkList, int i, int *e) {
    DuLinkList ptr = GetElemP_DuL(*duLinkList, i);
    if (!ptr) {
        return ERROR;
    }
    *e = ptr->data;
    ptr->prior->next = ptr->next;
    ptr->next->prior = ptr->prior;
    free(ptr);
    return OK;
}

void DisplayList_DuL(DuLinkList linkList) {
    DuLinkList ptr = linkList->next;
    while (ptr != linkList) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main() {
    DuLinkList duLinkList;
//    Init Test
    ListInit_DuL(&duLinkList);
    DisplayList_DuL(duLinkList);
//    Insert Test
    ListInsert_DuL(&duLinkList, 1, 1);
    DisplayList_DuL(duLinkList);

    ListInsert_DuL(&duLinkList, 1, 2);
    DisplayList_DuL(duLinkList);
    ListInsert_DuL(&duLinkList, 3, 3);
    DisplayList_DuL(duLinkList);
//    Delete Test
    int e;
    ListDelete_DuL(&duLinkList, 2, &e);
    DisplayList_DuL(duLinkList);
    printf("%d", e);
    return 0;
}