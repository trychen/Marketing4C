#include "goods.h"

LIST GOODS_LIST;
LIST GOODS_FILE_COMMENTS;

void readAllGoodsFromFile() {
    FILE *fp = fopen(GOODS_BIN_PATH, "r");

    // 文件存在与否
    if (fp == NULL) {
        printf("× 商品文件不存在！\n\n");
        return;
    }

    // 注释
    GOODS_FILE_COMMENTS = list_create();

    // 创建用于存储类别的链表
    Linker *head = list_create();

    // 最后一个节点，用于尾插法
    Linker *node = head;

    // 读取缓存
    char buf[128];
    // 逐行读入
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // 计算长度
        size_t len = strlen(buf);

        // s_01_002 1 苹果 974 8\r\n
        // 删除数据尾部的 \r\n
        len = fixReturnNewline(buf, len);

        // 判断空行
        if (len == 0) continue;

        // 判断是否为注释
        if (buf[0] == '#') {
            char *cpBuf = calloc(len + 1, sizeof(char));
            strcpy(cpBuf, buf);
            list_add(GOODS_FILE_COMMENTS, cpBuf);
            continue;
        }

        // 读取数据
        // s_02_002 2 饼干 987 18
        // 商品编号,所属类别编号,商品名称,库存量,单价
        Goods *p = malloc(sizeof(Goods));
        sscanf(buf, "%s %d %s %d %f", p->id, &p->category, p->name, &p->stock, &p->price);

        // 添加数据到链表
        Linker *next = list_create();
        next->entry = p;
        node->next = next;
        node = next;
    }

    fclose(fp);

    GOODS_LIST = head;
}

void writeAllGoodsToFile() {
    FILE *fp = fopen(GOODS_BIN_PATH, "w");

    FOREACH(GOODS_FILE_COMMENTS, char *, msg, {
        fputs(msg, fp);
        fputs("\n", fp);
    })

    // 商品编号,所属类别编号,商品名称,库存量,单价
    FOREACH(GOODS_LIST, Goods *, g, {
        fprintf(fp, "%s %d %s %d %f\n", g->id, g->category, g->name, g->stock, g->price);
    })
}

Goods *findGoodsByID(const char *id) {
    FOREACH(GOODS_LIST, Goods *, g, {
        if (strcmp(g->id, id) == 0) return g;
    })
    return NULL;
}

void printGoods(Goods *goods) {
    printf("| %s  %s  %s  %d  %d  %.2f\n", goods->id, goods->name, getCategoryDisplayNameByID(goods->category), goods->stock, goods->sales, goods->price);
//    printf("◉ 商品编号：\t%s\n", goods->id);
//    printf("| 商品名称：\t%s\n", goods->name);
//    printf("| 商品类型：\t%s\n", getCategoryDisplayNameByID(goods->category));
//    printf("| 库存数量：\t%d\n", goods->stock);
//    printf("| 销售数量：\t%d\n", goods->sales);
//    printf("| 单价：\t%.2f\n", goods->price);
}

/**
 * 判读两个商品是否已满足前后顺序
 */
bool compareGoodsID(Goods *a, Goods *b) {
    return strcmp(a->id, b->id) >= 0;
}

void printAllGoodsInIDOrder() {
    // 获取到这个列表的长度
    int size = list_size(GOODS_LIST);

    // 判空
    if (size == 0) {
        printf("× 当前没有任何商品，请先创建！\n");
        return;
    }

    // 排序
    LIST sorted = list_folkInOrder(GOODS_LIST, compareGoodsID);

    // 输出
    printf("◉ %s  %s  %s  %s  %s  %s\n", "商品编号", "商品名称", "商品类型", "库存数量", "销售数量", "单价");
    FOREACH(sorted, Goods *, g, printGoods(g))

    // 释放插入法排序的链表
    list_free(sorted);
}


void commandPrintGoods() {
    // 判空
    int size = list_size(GOODS_LIST);

    if (size == 0) {
        printf("× 当前没有任何商品，请先创建！\n");
        return;
    }

    // 输出所有商品简要信息
    printf("◉ 商品编号\t名称\n");
    FOREACH(GOODS_LIST, Goods*, g, {
        printf("| %s\t%s\n", g->id, g->name);
    })
    printf("\n");

    printf("▧ 查询商品信息\n");
    printf("↳ 请输入商品编号：");

    char id[30];
    scanf("%s", id);

    // 查找商品
    Goods *goods = findGoodsByID(id);

    printf("\n");

    // 检查商品是否存在
    if (goods == NULL) {
        printf("× 你所查找的商品 %s 不存在！\n", id);
        return;
    }

    // 输出商品信息
    printf("◉ %s  %s  %s  %s  %s  %s\n", "商品编号", "商品名称", "商品类型", "库存数量", "销售数量", "单价");
    printGoods(goods);
    printf("\n\n");
}