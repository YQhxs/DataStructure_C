//
// Created by HXS on 2020/9/7.
//
/**
 * 静态单链表，适合没有指针类型的高级语言Java、FORTRAN
 *
 */
#define MAXSIZE 1000
typedef struct {
    int data;
    int cur;
} Component, SLinkList[MAXSIZE];
//TODO