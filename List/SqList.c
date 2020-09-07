#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 0;
#define ERROR -1;

typedef struct {
    int *elem;
    int length;
    int listSize;
} SqList;

/**
 * 初始化，带头结点的顺序表
 * @param sqList
 * @return
 */
int ListInit_Sq(SqList *sqList) {
//     dynamic allocation
    sqList->elem = (int *) malloc(sizeof(int) * LIST_INIT_SIZE);
    if (!sqList->elem) {
        exit(-1);
    }
    sqList->length = 0;
    sqList->listSize = LIST_INIT_SIZE;
    return OK;
}

/**向指定位置i前插入元素e
 *
 * @param sqList
 * @param i
 * @param e
 * @return
 */
int ListInsert_Sq(SqList *sqList, int i, int e) {
//    1 <= i <= n+1
    if (i < 1 || i > sqList->length + 1 || sqList->length == 0) return ERROR;
//  increase  capacity
    if (sqList->length >= sqList->listSize) {
        int *newBase = (int *) realloc(sqList->elem, (sqList->listSize + LISTINCREMENT) * sizeof(int));
        if (!newBase)
            return ERROR;
        sqList->elem = newBase;
        sqList->listSize += LISTINCREMENT;
    }
//  elem of array[i-1~n-1] back；下标运算
    for (int j = sqList->length - 1; j >= i - 1; --j) {
        sqList->elem[j + 1] = sqList->elem[j];
    }
    sqList->elem[i - 1] = e;
    /* （指针）地址运算
     int *q = &(sqList->elem[i-1]);
     for (int * p =&(sqList->elem[sqList->length-1]) ; p >= q ; --p) {
         *(p+1) = *p;
     }
     *q = e;*/
    ++sqList->length;
    return OK;
}

/**
 * 删除指定位置 i 上的元素，并用e返回其值
 * @param sqList
 * @param i
 * @param e
 * @return
 */
int ListDelete_Sq(SqList *sqList, int i, int *e) {
//    1 <= i <= n
    if (i < 1 || i > sqList->length) {
        return ERROR;
    }
//    elem of array[i-1+1~n-1] forward
    int *start = &(sqList->elem[i - 1]);
    *e = *start;
    int *end = sqList->elem + sqList->length - 1;
    for (++start; start <= end; ++start) {
        *(start - 1) = *(start);
    }
    --sqList->length;
    return OK;
}

/**
 * 要求La,Lb均升序排列，合并后Lc也升序,
 * @param La
 * @param Lb
 * @param Lc
 */
void ListMerge_Sq(SqList *La, SqList *Lb, SqList *Lc) {
    int *pa = La->elem, *pb = Lb->elem, *pc;
//    init Lc
    Lc->length = La->length + Lb->length;
    Lc->listSize = Lc->length;
    Lc->elem = (int *) malloc(Lc->listSize * sizeof(int));
    pc = Lc->elem;

    int *pa_last = La->elem + La->length - 1;
    int *pb_last = Lb->elem + Lb->length - 1;
    while (pa <= pa_last && pb <= pb_last) {
        if (*pa <= *pb) {
            *pc++ = *pa++;
        } else {
            *pc++ = *pb++;
        }
    }
    while (pa <= pa_last) {
        *pc++ = *pa++;
    }
    while (pb <= pb_last) {
        *pc++ = *pb++;
    }

}

/**
 * 返回sqList中第一个与e相等的元素位置
 * 0代表未发现
 * @param sqList
 * @param e
 * @return
 */
int LocateElem_Sq(SqList *sqList, int e) {
    int i = 1;
    int *start = sqList->elem;
    while (i <= sqList->length && *start++ != e) {
        i++;
    }
    if (i <= sqList->length) {
        return i;
    } else {
        return 0;
    }

}

void ListDisplay_Sq(SqList *sqList) {
    for (int i = 0; i < sqList->length; ++i) {
        printf("%d ", sqList->elem[i]);
    }
    printf("\n");
}

int main() {
    SqList listA;
    ListInit_Sq(&listA);
    listA.elem[0] = -1;
    listA.length = 1;

//    Insert Test
    for (int i = 1; i <= 5; ++i) {
        ListInsert_Sq(&listA, i, i);
    }
    ListDisplay_Sq(&listA);
//    Delete Test
    int deleteElem = -1;
    ListDelete_Sq(&listA, 2, &deleteElem);
    printf("%d\n", deleteElem);
    ListDisplay_Sq(&listA);
//    Merge Test
    SqList Lc;
    ListMerge_Sq(&listA, &listA, &Lc);
    ListDisplay_Sq(&Lc);
//    LocateElem Test
    printf("%d\n", LocateElem_Sq(&Lc, 3));
    return 0;
}