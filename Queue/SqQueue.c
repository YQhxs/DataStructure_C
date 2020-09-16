#include <stdio.h>
#include <stdlib.h>

#define OK 0;
#define ERROR -1;
#define MAXQSIZE 100
/**
 * 循环队列。约定少用一个元素空间。队头指针在队尾指针的下一位置作为队满标志
 * 不能再次realloc，必须设置一个最大长度
 * 无法预估长度时，宜采用链队列
 */
typedef struct {
    int *base;
    int front;/*头指针，队不空，指向头元素*/
    int rear;/*尾指针，队不空，指向队尾的下一位置*/
    //二者范围[0,MAXQSIZE-1]
} SqQueue;

int QueueInit_Sq(SqQueue *sqQueue) {
    sqQueue->base = (int *) malloc(sizeof(int) * MAXQSIZE);
    if (!sqQueue->base) return ERROR;
    sqQueue->rear = sqQueue->front = 0;
    return OK;
}

/**
 * 差值代表元素个数，要保证非负
 * @param sqQueue
 * @return
 */
int QueueLength(SqQueue sqQueue) {
    return (sqQueue.front - sqQueue.rear + MAXQSIZE) % MAXQSIZE;
}

int EnQueue(SqQueue *sqQueue, int e) {
    if ((sqQueue->rear + 1) % MAXQSIZE == sqQueue->front) return ERROR;/*Full*/
    sqQueue->base[sqQueue->rear] = e;
    sqQueue->rear = (sqQueue->rear + 1) % MAXQSIZE;/*When the element is inserted again at the 0 position.*/
    return OK;
}

int DeQueue(SqQueue *sqQueue, int *e) {
    if (sqQueue->front == sqQueue->rear) return ERROR;
    *e = sqQueue->base[sqQueue->front];
    sqQueue->front = (sqQueue->front + 1) % MAXQSIZE;/*same as above*/
    return OK;
}

void Display(SqQueue sqQueue) {
    int ptr = sqQueue.front;
    while (ptr != sqQueue.rear) {
        printf("%d ", sqQueue.base[ptr++]);
    }
    printf("\n");
}

int main() {
    SqQueue sqQueue;
    QueueInit_Sq(&sqQueue);
//    EnQueue Test
    EnQueue(&sqQueue, 0);
    EnQueue(&sqQueue, 1);
    EnQueue(&sqQueue, 2);
    EnQueue(&sqQueue, 3);
    Display(sqQueue);
//    DeQueue Test
    int e;
    DeQueue(&sqQueue, &e);
    Display(sqQueue);
    printf("%d", e);
    return 0;
}