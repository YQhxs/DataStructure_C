#include <stdio.h>
#include <stdlib.h>

#define OK 0;
#define ERROR -1;
typedef struct LNode {
    int data;
    struct LNode *next;/* If the structure contains a pointer to itself, you have use the struct version to refer to it.can't use just "LNode *next" here */
} LNode, *LinkList;

/**
 * 要求带头结点
 * @param linkList
 * @return
 */
int InitLinkList(LinkList *linkList) {/*C只有值传递，模拟引用调用*/
    *linkList = (LinkList) malloc(sizeof(LNode));
    if (!*linkList)
        return ERROR;

    (*linkList)->next = NULL;
    return OK;
}

/**
 * 尾插法建立单链表,正序输入->正序输出
 * @param linkList
 * @param n
 * @return
 */
int CreateLinkList_T(LinkList *linkList, int n) {
    InitLinkList(linkList);
    LinkList tail = *linkList;
    for (int i = 0; i < n; ++i) {
        LinkList newLNode = (LinkList) malloc(sizeof(LNode));
        scanf("%d", &newLNode->data);
        newLNode->next = NULL;
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
int CreateLinkList_H(LinkList *linkList, int n) {
    InitLinkList(linkList);
    for (int i = 0; i < n; ++i) {
        LinkList newLNode = (LinkList) malloc(sizeof(LNode));
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
int InsertLinkList(LinkList *linkList, int i, int e) {
    LinkList ptr = *linkList;
    int j = 0;/*counter*/
/*
 * find the node of index of i-1.
 * the role of ptr is to judge whether the headNode exists
 * and the loop ends normally(ptr!=NULL).
 */
    while (ptr && j < i - 1) {
        ptr = ptr->next;
        j++;
    }
/*
 * condition (ptr == NULL):due to i > n+1
 * condition (j > i-1):due to i < 1
 *
 */
    if (!ptr || j > i - 1) {
        return ERROR;
    }
    LinkList newNode = (LinkList) malloc(sizeof(LNode));
    newNode->data = e;
    newNode->next = ptr->next;
    ptr->next = newNode;
    return OK;
}

/**
 * 删除第i个位置，1<=i<=n
 * @param linkList
 * @param i
 * @param e
 * @return
 */
int DeleteLinkList(LinkList *linkList, int i, int *e) {
    LinkList ptr = *linkList;
    int j = 0;/*counter*/
/*
 * find the node of index of i-1.
 * the role of ptr->next is to judge whether the firstElement exists
 * and the loop ends normally(ptr != NULL).
*/
    while (ptr->next && j < i - 1) {
        ptr = ptr->next;
        ++j;
    }
/*
 * condition (ptr == NULL):due to i > n
 * condition (j > i-1):due to i < 1
 * */
    if (!ptr || j > i - 1) {
        return ERROR;
    }
    LinkList deletedNode = ptr->next;
    *e = deletedNode->data;
    ptr->next = deletedNode->next;
    free(deletedNode);
    return OK;
}

/**
 * 前提都是升序，归并链表。pa、pb、pc指针需要移动。
 * @param La
 * @param Lb
 */
void MergeLinkList(LinkList *La, LinkList *Lb) {
    LinkList pa = (*La)->next, pb = (*Lb)->next;/*same as SqList , compare from the first Element*/
    LinkList Lc = *La, pc = Lc;/*no extra space*/
    while (pa && pb) {
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
int GetElemLinkList(LinkList linkList, int i, int *e) {
    LinkList ptr = linkList->next;
    int j = 1;/*counter*/
    while (ptr && j < i) {/*loop i-1 times*/
        ptr = ptr->next;
        ++j;
    }
/*
 * condition (ptr == NULL):due to i > n
 * condition (j > i-1):due to i < 1
 */
    if (!ptr || j > i) {
        return ERROR
    }
    *e = ptr->data;
    return OK;
}

void DisplayLinkList(LinkList linkList) {
    LinkList ptr = linkList->next;
    while (ptr) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int main() {
    LinkList La;
// Init Test
    InitLinkList(&La);
//    Create Test
    LinkList Lb;
    CreateLinkList_T(&Lb, 3);
    DisplayLinkList(Lb);
    LinkList Lc;
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
