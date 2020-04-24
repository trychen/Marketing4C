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
 * @param order 用于对比的函数指针，返回 true 表示两个元素已按先后顺序排好
 */
LIST list_folkInOrder(Linker *head, bool (*order)(void*, void*));

/* 用于链表的循环 */
#define FOREACH(LIST_HEAD, TYPE, VAR, BODY) {LIST __FOREACH__ELEMENT__ = LIST_HEAD->next; \
while(__FOREACH__ELEMENT__ != NULL) { \
TYPE VAR = __FOREACH__ELEMENT__->entry; \
BODY; \
__FOREACH__ELEMENT__ = __FOREACH__ELEMENT__->next; \
}}

/**
 * 删除链表中的数据
 * @param TYPE 元素类型
 * @param VAR 变量名
 * @param COMPARE 对比表达式，返回 true 既删除
 */
#define REMOVE_IF(LIST_HEAD, TYPE, VAR, COMPARE) {LIST __REMOVEIF__ELEMENT__ = LIST_HEAD->next; \
LIST __REMOVEIF__PREVIOUS__ = LIST_HEAD; \
while(__REMOVEIF__ELEMENT__ != NULL) { \
    TYPE VAR = __REMOVEIF__ELEMENT__->entry; \
    bool REMOVE = false;\
    COMPARE; \
    if (REMOVE) { \
        __REMOVEIF__PREVIOUS__->next = __REMOVEIF__ELEMENT__->next; \
        free(__REMOVEIF__ELEMENT__); \
        __REMOVEIF__ELEMENT__ = __REMOVEIF__PREVIOUS__->next; \
        continue; \
    } \
    __REMOVEIF__PREVIOUS__ = __REMOVEIF__ELEMENT__; \
    __REMOVEIF__ELEMENT__ = __REMOVEIF__ELEMENT__->next; \
}}


#endif //MARKETING4C_CORE_H
