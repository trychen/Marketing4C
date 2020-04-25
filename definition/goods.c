#include "goods.h"

LIST GOODS_LIST;
LIST GOODS_FILE_COMMENTS;

void readAllGoodsFromFile() {
    FILE *fp = fopen(GOODS_BIN_PATH, "r");

    if (fp == NULL) {
        printf("× 商品文件不存在！\n\n");
        return;
    }
    GOODS_FILE_COMMENTS = list_create();

    Linker *head = list_create();
    Linker *node = head;

    char buf[128];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        // 计算长度
        size_t len = strlen(buf);
        if (len == 0) continue;
        fixReturnNewline(buf, len);

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

    GOODS_LIST = head;

    fclose(fp);
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

Goods* findGoodsByID(const char* id) {
    FOREACH(GOODS_LIST, Goods *, g, {
        if (strcmp(g->id, id) == 0) return g;
    })
    return NULL;
}

void printGoods(Goods *goods) {
    printf("◉ 商品编号：\t%s\n", goods->id);
    printf("| 商品名称：\t%s\n", goods->name);
    printf("| 商品类型：\t%s\n", getCategoryDisplayNameByID(goods->category));
    printf("| 库存数量：\t%d\n", goods->stock);
    printf("| 销售数量：\t%d\n", goods->sales);
    printf("| 单价：\t%.2f\n", goods->price);
}

bool compareGoodsID(Goods *a, Goods *b) {
    return strcmp(a->id, b->id) >= 0;
}

void printAllGoodsInIDOrder() {
    // 获取到这个列表的长度
    int size = list_size(GOODS_LIST);

    if (size == 0) {
        printf("× 当前没有任何商品，请先创建！\n");
        return;
    }

    LIST sorted = list_folkInOrder(GOODS_LIST, compareGoodsID);

    FOREACH(sorted, Goods *, g, printGoods(g))

    list_free(sorted);
}


void commandPrintGoods() {
    int size = list_size(GOODS_LIST);

    if (size == 0) {
        printf("× 当前没有任何商品，请先创建！\n");
        return;
    }

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

    if (goods == NULL) {
        printf("× 你所查找的商品 %s 不存在！\n", id);
        return;
    }

    // 输出商品信息
    printGoods(goods);
    printf("\n\n");
}