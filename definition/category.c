#include "category.h"

char * getCategoryDisplayNameByID(int id) {
    Linker *current = CATEGORY_LIST;

    while (current != NULL) {
        Category *category = current->entry;

        if (category->id == id) {
            return category->name;
        }
    }

    return CATEGORY_NOT_DEFINED_DISPLAY_NAME;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"

void readAllCategoryFromFile() {
    FILE *fp = fopen(CATEGORY_BIN_PATH, "r");

    if (fp == NULL) {
        printf("× 商品分类文件不存在！\n\n");
        return;
    }

    CATEGORY_LIST = malloc(sizeof(Linker));
    memset(CATEGORY_LIST, 0, sizeof(Linker));

    char buf[128];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // 计算长度
        size_t len = strlen(buf);
        if (len == 0 || buf[0] == '#') continue;

        fixReturnNewline(buf, len);

        // 读取数据
        Category *cg = malloc(sizeof(Category));
        sscanf(buf, "%d %s", &cg->id, cg->name);

        // 添加数据到链表
        linkedlist_add(CATEGORY_LIST, cg);
    }

    fclose(fp);
}

#pragma clang diagnostic pop