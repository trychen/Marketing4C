#include "category.h"

LIST CATEGORY_LIST;

char * getCategoryDisplayNameByID(int id) {
    FOREACH(CATEGORY_LIST, Category*, cg, {
        // 判断当前循环的类别 ID 是否为参数传入的 ID
        if (cg->id == id)
            return cg->name;
    })

    return CATEGORY_NOT_DEFINED_DISPLAY_NAME;
}

void readAllCategoryFromFile() {
    FILE *fp = fopen(CATEGORY_BIN_PATH, "r");

    if (fp == NULL) {
        printf("× 商品分类文件不存在！\n\n");
        return;
    }

    // 创建用于存储类别的链表
    Linker *head = list_create();

    // 最后一个节点，用于尾插法
    Linker *node = head;

    char buf[128];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // 计算长度
        size_t len = strlen(buf);

        // 空行和注释行
        if (len == 0 || buf[0] == '#') continue;

        // 删除数据尾部的 \r\n
        fixReturnNewline(buf, len);

        // 读取数据
        Category *cg = malloc(sizeof(Category));
        sscanf(buf, "%d %s", &cg->id, cg->name);

        // 添加数据到链表
        Linker *next = list_create();
        next->entry = cg;
        node->next = next;
        // 尾插法 替换尾节点
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