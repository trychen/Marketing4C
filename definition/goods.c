#include "goods.h"

void commandPrintGoods() {
    int size = linkedlist_size(GOODS_LIST);

    if (size == 0) {
        printf("× 当前没有任何商品，请先创建！\n");
        return;
    }

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
}

Goods* findGoodsByID(const char* id) {
    Linker *current = GOODS_LIST;
    while (current != NULL) {
        Goods *goods = current->entry;
        if (strcmp(goods->id, id) == 0) {
            return goods;
        }
    }
    return NULL;
}

bool deleteGoodsByID(const char* id) {
    return false;
}

void printGoods(Goods *goods) {
    printf("◉ 商品编号：\t%s\n", goods->id);
    printf("  商品名称：\t%s\n", goods->name);
    printf("  商品类型：\t%s\n", getCategoryDisplayNameByID(goods->category));
    printf("  库存数量：\t%d\n", goods->stock);
    printf("  销售数量：\t%d\n", goods->sales);
    printf("  单价：\t%.2f\n", goods->price);
    printf("\n");
}

bool func_goods_inIDOrder(Goods *a, Goods *b) {
    return strcmp(a->id, b->id) >= 0;
}

void printAllGoodsInIDOrder() {
    // 获取到这个列表的长度
    int size = linkedlist_size(GOODS_LIST);

    if (size == 0) {
        printf("× 当前没有任何商品，请先创建！\n");
        return;
    }

    Linker * sortedList = linkedlist_folkInOrder(GOODS_LIST, (bool (*)(void *, void *)) func_goods_inIDOrder);

    linkedlist_foreach(sortedList, (void (*)(void *)) printGoods);
}