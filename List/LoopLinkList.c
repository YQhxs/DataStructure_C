//
// Created by HXS on 2020/9/7.
//
/**
 * 单向循环链表，带头结点
 * 操作与单链表基本一致，差别在于循环条件不是
 * p或p->next是否为空，而是他们是否是头结点
 */
#include <stdio.h>
#include <stdlib.h>

#define OK 0;
#define ERROR -1;
typedef struct LoopNode {
    int data;
    struct LoopNode *next;
} LoopNode, *LLinkList;

/**
 * 要求带头结点
 * @param linkList
 * @return
 */
int InitLinkList_L(LLinkList *linkList) {/*C只有值传递，模拟引用调用*/
    *linkList = (LLinkList) malloc(sizeof(LoopNode));
    if (!*linkList)
        return ERROR;
    (*linkList)->next = *linkList;
    return OK;
}

/**
 * 尾插法建立单链表,正序输入->正序输出
 * @param linkList
 * @param n
 * @return
 */
int CreateLinkList_T(LLinkList *linkList, int n) {
    InitLinkList_L(linkList);
    LLinkList tail = *linkList;
    for (int i = 0; i < n; ++i) {
        LLinkList newLNode = (LLinkList) malloc(sizeof(LoopNode));
        scanf("%d", &newLNode->data);
        newLNode->next = *linkList;
//        two step：modify the ‘next’ domain of tail pointer and update the tail node
        tail->next = newLNode;
        tail = newLNode;
    }
    return OK;
}

/**
 * 头插法,正序输入->逆序输出
 * @param linkList
 * @param n
 * @return
 */
int CreateLinkList_H(LLinkList *linkList, int n) {
    InitLinkList_L(linkList);
    for (int i = 0; i < n; ++i) {
        LLinkList newLNode = (LLinkList) malloc(sizeof(LoopNode));
        scanf("%d", &newLNode->data);
//      two step：modify the 'next' domain of newNode and head point
        newLNode->next = (*linkList)->next;
        (*linkList)->next = newLNode;
    }
    return OK;
}

/**
 * 第i个位置前插入e，1<=i<=n+1.
 * n+1的情况可理解为：插入i位置必须找到i-1节点，可找到n节点
 * @param linkList
 * @param i
 * @param e
 * @return
 */
int InsertLinkList(LLinkList *linkList, int i, int e) {
    LLinkList ptr = (*linkList)->next;
    int j = 1;/*counter*/
/*
 * find the node of index of i-1.
 * the role of ptr is to judge whether the headNode exists
 * and the loop ends normally(ptr!=*linkList).
 */
    while (j < i - 1 && ptr != *linkList) {
        ptr = ptr->next;
        j++;
    }
/*
 * Satisfied situation
 * 1< i <= n+1 j=i-1
 * i=1 j=1
 *Unsatisfied situation
 * i = 0 j=1
 * i > n+1 j=n
 */
    if (i == j || j == i - 1) {
        LLinkList newNode = (LLinkList) malloc(sizeof(LoopNode));
        newNode->data = e;
        newNode->next = ptr->next;
        ptr->next = newNode;
    } else {
        return ERROR;
    }

    return OK;
}

/**
 * 删除第i个位置，1<=i<=n
 * @param linkList
 * @param i
 * @param e
 * @return
 */
int DeleteLinkList(LLinkList *linkList, int i, int *e) {
    LLinkList ptr = (*linkList)->next;
    int j = 1;/*counter*/
/*
 * find the node of index of i-1.
*/
    while (ptr != (*linkList) && j < i - 1) {
        ptr = ptr->next;
        ++j;
    }

    if (i == j || j == i - 1) {
        LLinkList deletedNode = ptr->next;
        *e = deletedNode->data;
        ptr->next = deletedNode->next;
        free(deletedNode);
    } else {
        return ERROR;
    }
    return OK;
}

/**
 * 前提都是升序，归并链表。pa、pb、pc指针需要移动。
 * @param La
 * @param Lb
 */
void MergeLinkList(LLinkList *La, LLinkList *Lb) {
    LLinkList pa = (*La)->next, pb = (*Lb)->next;/*same as SqList , compare from the first Element*/
    LLinkList Lc = *La, pc = Lc;/*no extra space*/
    while (pa != (*La) && pb != (*Lb)) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(*Lb);
}

/**
 * 取出指定位置的元素。j计数器从第一个数据节点开始
 *
 * @param linkList
 * @param i
 * @param e
 * @return
 */
int GetElemLinkList(LLinkList linkList, int i, int *e) {
    LLinkList ptr = linkList->next;
    int j = 1;/*counter*/
    while (ptr != linkList && j < i) {/*loop i-1 times*/
        ptr = ptr->next;
        ++j;
    }
    if (j != i) {
        return ERROR
    }

    *e = ptr->data;
    return OK;
}

void DisplayLinkList(LLinkList linkList) {
    LLinkList ptr = linkList->next;
    while (ptr != linkList) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main() {
    LLinkList La;
// Init Test
    InitLinkList_L(&La);
//    Create Test
    LLinkList Lb;
    CreateLinkList_T(&Lb, 3);
    DisplayLinkList(Lb);
    LLinkList Lc;
    CreateLinkList_H(&Lc, 3);
    DisplayLinkList(Lc);
//  Insert Test
    InsertLinkList(&Lb, 4, 4);
    DisplayLinkList(Lb);
//    Delete Test
    int elem;
    DeleteLinkList(&Lb, 2, &elem);
    DisplayLinkList(Lb);
//    Merge Test
    MergeLinkList(&Lb, &Lc);
    DisplayLinkList(Lb);
    return 0;
};
