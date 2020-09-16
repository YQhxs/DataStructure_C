#include <stdio.h>
#include <stdlib.h>


#define OK 0;
#define ERROR -1;
/**
 * 链栈也无容量限制
 * 不设头结点
 * 由栈顶指针惟一确定
 */

typedef struct SNode {
    int data;
    struct SNode *next;
} SNode, *LinkStack;

/**
 * 无头结点
 * @param linkStack
 * @return
 */
int StackInit_L(LinkStack *linkStack) {
    (*linkStack) = NULL;
    return OK;
}

/**
 * 新结点next域指向栈顶，然后原栈顶位置更新（指向新结点）
 * @param linkStack
 * @param elem
 * @return
 */
int StackPush_L(LinkStack *linkStack, int elem) {
    LinkStack newNode = (LinkStack) malloc(sizeof(SNode));
    if (!newNode) return ERROR;
    newNode->data = elem;
    newNode->next = (*linkStack);/*①*/
    (*linkStack) = newNode;/*②*/
    return OK;
}

int StackPop_L(LinkStack *linkStack, int *elem) {
    if (*linkStack) {
        LinkStack ptr = (*linkStack);/*①*/
        (*elem) = ptr->data;
        (*linkStack) = ptr->next;/*②*/
        free(ptr);
        return OK;
    }
    return ERROR;
}

/**
 * 从栈顶到栈底的输出顺序
 * @param linkStack
 */
void Display_L(LinkStack linkStack) {
    LinkStack ptr = linkStack;
    while (ptr) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

void main() {
//    Init Test
    LinkStack stack;
    StackInit_L(&stack);
//    Push Test
    StackPush_L(&stack, 0);
    StackPush_L(&stack, 1);
    StackPush_L(&stack, 2);
    Display_L(stack);
//    Pop Test
    int e;
    StackPop_L(&stack, &e);
    Display_L(stack);
    printf("%d", e);
}