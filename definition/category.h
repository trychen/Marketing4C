#ifndef MARKETING4C_CATEGORY_H
#define MARKETING4C_CATEGORY_H

#include "../core.h"

/**
 * 存储类别信息的默认路径
 */
#define CATEGORY_BIN_PATH "category.txt"

/**
 * 当找不到对应的类别时，返回的缺省类别名称
 */
#define CATEGORY_NOT_DEFINED_DISPLAY_NAME "未知类型"

typedef struct MarketCategory {
    int id; // 类别ID
    char name[20]; //列表名称
} Category;

/**
 * 存储类别信息的链表
 */
LIST CATEGORY_LIST;

/**
 * 从文件中读入类别信息到 {@see CATEGORY_LIST}
 */
void readAllCategoryFromFile();

/**
 * 获取类别ID对应的显示名称，找不到对应的类别时返回 {@see CATEGORY_NOT_DEFINED_DISPLAY_NAME}
 */
char* getCategoryDisplayNameByID(int);

/**
 * 输出所有的类别
 */
void printAllCategory();

#endif //MARKETING4C_CATEGORY_H
