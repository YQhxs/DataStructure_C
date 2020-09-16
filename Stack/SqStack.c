#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
#define OK 0;
#define ERROR -1;
/*
 * 栈的顺序实现，栈顶指针指向尾部元素的下一位置
 * ,top指针可以使用int类型(初始化时top = 0)，也可以使用int* 类型（top = base）
 * */
typedef struct {
    int *base;/*It also represents the first address of the array.*/
    int top;/*top pointer equal length*/
    int StackSize;
} SqStack;

/**
 * 初始化：分配空间
 * @param sqStack
 * @return
 */
int StackInit_Sq(SqStack *sqStack) {
    sqStack->base = (int *) malloc(sizeof(int) * STACK_INIT_SIZE);
    if (!sqStack->base) {
        return ERROR;
    }
    sqStack->top = 0;
    sqStack->StackSize = STACK_INIT_SIZE;
    return OK;
}

/**
 * 注意int*与int类型的top时，增加容量的区别
 * @param sqStack
 * @param base
 * @return
 */
int StackPush_Sq(SqStack *sqStack, int e) {
    if (sqStack->top >= sqStack->StackSize) {/*In judgment conditions, top is only a number, don`t  access array.*/
        sqStack->base = (int *) realloc(sqStack->base, (sqStack->StackSize + STACK_INCREMENT) * sizeof(int));
        if (!sqStack->base) {
            return ERROR;
        }
        //if top is type of int* ,it needs to reassign.such as:sqStack->top = sqStack->base+sqStack->StackSize;
        sqStack->StackSize += STACK_INCREMENT;
    }
    sqStack->base[sqStack->top++] = e;
    return OK;
}

/**
 * 先top-1
 * @param sqStack
 * @param e
 * @return
 */
int StackPop_Sq(SqStack *sqStack, int *e) {
    if (sqStack->top > 0) {
        *e = sqStack->base[--sqStack->top];
        return OK;
    }
    return ERROR;
}

void StackDisplay_Sq(SqStack sqStack) {
    int *p = sqStack.base;
    int *q = sqStack.base + sqStack.top - 1;
    while (p <= q) {
        printf("%d ", *p);
        p++;
    }
    printf("\n");
}

int main() {
//    Init Test
    SqStack stack;
    StackInit_Sq(&stack);
    StackDisplay_Sq(stack);
//    Push Test
    StackPush_Sq(&stack, 0);
    StackPush_Sq(&stack, 1);
    StackDisplay_Sq(stack);
//    Pop Test
    int e;
    StackPop_Sq(&stack, &e);
    printf("%d\n", e);
    StackPop_Sq(&stack, &e);
    printf("%d\n", e);
    StackDisplay_Sq(stack);
    return 0;
}