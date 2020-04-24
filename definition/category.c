#include "category.h"

char * getCategoryDisplayNameByID(int id) {
    FOREACH(CATEGORY_LIST, Category*, cg, {
        if (cg->id == id) return cg->name;
    })

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

    Linker *head = list_create();
    Linker *node = head;

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
        Linker *next = list_create();
        next->entry = cg;
        node->next = next;
        node = next;
    }

    CATEGORY_LIST = head;
    fclose(fp);
}

void printAllCategory() {
    printf("◉ 类别编号\t名称\n");

    FOREACH(CATEGORY_LIST, Category *, c, {
        printf("| %d\t%s\n", c->id, c->name);
    })
}

#pragma clang diagnostic pop