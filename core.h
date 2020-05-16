//
// 通用的接口
// Created by 陈志林 on 2020/3/13.
//

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
int fixReturnNewline(char c[], int len);

/**
 * 单向链表
 */
typedef struct linker {
    void *entry;
    struct linker *next;
} Linker;

typedef Linker* LIST;

/**
 * 往链表尾部添加元素
 */
void list_add(LIST head, void *entry);

/**
 * 获取链表的长度
 */
int list_size(LIST head);

/**
 * 释放链表（不会释放里面的元素）
 */
void list_free(LIST head);

/**
 * 创建一个链表节点
 */
LIST list_create();

/**
 * 链表的插入排序
 *
 * @param order 用于对比的函数指针，返回 true 表示两个元素已按先后顺序排好
 */
LIST list_folkInOrder(Linker *head, bool (*order)(void*, void*));

/**
 * 用于链表的循环
 * @param TYPE 元素类型
 * @param VAR 变量名称
 * @param BODY 方法体
 */
#define FOREACH(LIST_HEAD, TYPE, VAR, BODY) {LIST __FOREACH__ELEMENT__ = LIST_HEAD; \
while(__FOREACH__ELEMENT__ != NULL) { \
__FOREACH__ELEMENT__ = __FOREACH__ELEMENT__->next; \
if (__FOREACH__ELEMENT__ == NULL) break; \
TYPE VAR = __FOREACH__ELEMENT__->entry; \
BODY; \
}}

/**
 * 删除链表中的数据
 *
 * @param TYPE 元素类型
 * @param VAR 变量名
 * @param COMPARE 对比表达式，REMOVE = true 既删除
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
