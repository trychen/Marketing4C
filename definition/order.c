
#include "order.h"

LIST ORDER_LIST;
int NEXT_ORDER_ID = 1;

void readAllOrdersFromFile() {
    FILE *fp = fopen(ORDER_BIN_PATH, "r");

    if (fp == NULL) {
        printf("× 订单文件不存在！\n\n");
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
        Order *p = malloc(sizeof(Order));
        sscanf(buf, "%d %s %d %f %f", &p->id, p->goods_id, &p->count, &p->price, &p->total);

        Goods *goods = findGoodsByID(p->goods_id);
        if (goods == NULL) continue;
        p->goods = goods;
        p->goods->sales += p->count;

        if (p->id > NEXT_ORDER_ID) {
            NEXT_ORDER_ID = p->id + 1;
        }

        // 添加数据到链表
        Linker *next = list_create();
        next->entry = p;
        node->next = next;
        node = next;
    }

    ORDER_LIST = head;

    fclose(fp);
}

void printOrder(Order *order) {
    printf("| %04d\t%s\t%d\t%.2f\n", order->id, order->goods->name, order->count, order->total);
}