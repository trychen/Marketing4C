#ifndef MARKETING4C_CORE_H
#define MARKETING4C_CORE_H

/* 自定义的 Boolean 实现，用于提高结构化 */
#define bool int
#define true 1
#define false 0

/* 引入常用的头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 删除使用 fgets 函数时，字符串尾部存在。
 * 例如："hello/r/n" => "hello"
 *      "123/n" => "123"
 *      "123/r" => "123"
 *      "123/n/r" => "123"
 * @param c 要处理的字符串
 * @param len 字符串长度
 */
void fixReturnNewline(char c[], int len);

/**
 * 单向链表
 */
typedef struct linker {
    void *entry;
    struct linker *next;
} Linker;

void linkedlist_add(Linker *head, void *entry);
void linkedlist_foreach(Linker *head, void (*each)(void *));
bool linkedlist_delete(Linker *head, void *entry);
int linkedlist_size(Linker *head);

/**
 * 链表的插入排序
 */
Linker * linkedlist_folkInOrder(Linker *head, bool (*order)(void*, void*));

#endif //MARKETING4C_CORE_H
