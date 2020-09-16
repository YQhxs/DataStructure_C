#include <stdio.h>
#include <stdlib.h>

#define OK 0;
#define ERROR -1;
/**
 * 带头结点的链队列
 */

/*结点及结点指针*/
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode, *QueuePtr;
/*链队列*/
typedef struct {
    QueuePtr front;/*Point to head node*/
    QueuePtr rear;/*Point to the tail*/
} LinkQueue;

/**
 * 初始化：front与rear指向头结点
 * @param linkQueue 
 * @return 
 */
int QueueInit_L(LinkQueue *linkQueue) {
    QueuePtr head = (QueuePtr) malloc(sizeof(QNode));
    if (!head)
        return ERROR;
    head->next = NULL;
    linkQueue->front = linkQueue->rear = head;
    return OK;
}

int EnQueue(LinkQueue *linkQueue, int e) {
    QueuePtr newNode = (QueuePtr) malloc(sizeof(QNode));
    if (!newNode) return ERROR;
    newNode->data = e;
    newNode->next = NULL;
    (*linkQueue).rear->next = newNode;/*①*/
    (*linkQueue).rear = newNode;/*②*/
    return OK;
}

/**
 * 注意只有一个元素的情况：尾指针会丢失
 * @param linkQueue
 * @param e
 * @return
 */
int DeQueue(LinkQueue *linkQueue, int *e) {
    if ((*linkQueue).front == (*linkQueue).rear)
        return ERROR;
    QueuePtr ptr;
    ptr = (*linkQueue).front->next;
    *e = ptr->data;
    (*linkQueue).front->next = ptr->next;/*①*/
    if ((*linkQueue).rear == ptr) {
        (*linkQueue).rear = (*linkQueue).front;/*②*/
    }
    free(ptr);
    return OK;
}

/**
 * 从头结点开始销毁，之后头指针会丢失，用尾指针指示被销毁的下一位置
 * @param linkQueue
 * @return
 */
int DestroyQueue(LinkQueue *linkQueue) {
    while ((*linkQueue).front) {
        (*linkQueue).rear = (*linkQueue).front->next;/*①*/
        free((*linkQueue).front);/*②*/
        (*linkQueue).front = (*linkQueue).rear;/*③*/
    }
    return OK;
}

void Display(LinkQueue linkQueue) {
    QueuePtr ptr;
    ptr = linkQueue.front->next;
    while (ptr) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void main() {
    LinkQueue linkQueue;
    QueueInit_L(&linkQueue);
//    EnQueue Test
    EnQueue(&linkQueue, 0);
    EnQueue(&linkQueue, 1);
    EnQueue(&linkQueue, 2);
    EnQueue(&linkQueue, 3);
    Display(linkQueue);
//    DeQueue Test
    int e;
    DeQueue(&linkQueue, &e);
    Display(linkQueue);
    printf("%d", e);
// DestroyQueue Test
    DestroyQueue(&linkQueue);
}