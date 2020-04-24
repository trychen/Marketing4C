#ifndef MARKETING4C_CORE_H
#define MARKETING4C_CORE_H

/* 自定义的 Boolean 实现，用于提高结构化 */
#define bool int
#define true 1
#define false 0

#define LOOP for(;;)

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

typedef Linker* LIST;

void list_add(LIST head, void *entry);
bool list_delete(LIST head, void *entry);
int list_size(LIST head);
void list_free(LIST head);
LIST list_create();

/**
 * 链表的插入排序
 */
LIST list_folkInOrder(Linker *head, bool (*order)(void*, void*));

/* 用于链表的循环 */
#define FOREACH(LIST_HEAD, TYPE, VAR, BODY) LIST __cfee__##VAR = LIST_HEAD->next; \
while(__cfee__##VAR != NULL) { \
TYPE VAR = __cfee__##VAR->entry; \
BODY; \
__cfee__##VAR = __cfee__##VAR->next; \
}


#define REMOVE_IF(LIST_HEAD, TYPE, VAR, COMPARE) LIST RI_##VAR = LIST_HEAD->next; \
LIST PREVIOUS_##VAR = LIST_HEAD; \
while(RI_##VAR != NULL) { \
    TYPE VAR = RI_##VAR->entry; \
    bool REMOVE = false;\
    COMPARE; \
    if (REMOVE) { \
        PREVIOUS_##VAR->next = RI_##VAR->next; \
        free(RI_##VAR); \
        RI_##VAR = PREVIOUS_##VAR->next; \
        continue; \
    } \
    PREVIOUS_##VAR = RI_##VAR; \
    RI_##VAR = RI_##VAR->next; \
}


#endif //MARKETING4C_CORE_H
