
#include "order.h"

LIST ORDER_LIST;
int NEXT_ORDER_ID = 1;
LIST ORDER_FILE_COMMENTS;

void readAllOrdersFromFile() {
    FILE *fp = fopen(ORDER_BIN_PATH, "r");

    if (fp == NULL) {
        printf("× 订单文件不存在！\n\n");
        return;
    }

    ORDER_FILE_COMMENTS = list_create();

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
            list_add(ORDER_FILE_COMMENTS, cpBuf);
            continue;
        }

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

void writeAllOrdersToFile() {
    FILE *fp = fopen(ORDER_BIN_PATH, "w");

    FOREACH(ORDER_FILE_COMMENTS, char *, msg, {
        fputs(msg, fp);
        fputs("\n", fp);
    })

    FOREACH(ORDER_LIST, Order *, order, {
        fprintf(fp, "%04d %s %d %f %f\n", order->id, order->goods_id, order->count, order->price, order->total);
    })
}

void printOrder(Order *order) {
    printf("| %04d\t%s\t%d\t%.2f\n", order->id, order->goods->name, order->count, order->total);
}

void commandDeleteOrder() {
    printf("◉ 订单编号\t商品\t数量\t总价\n");
    FOREACH(ORDER_LIST, Order *, o, {
        printOrder(o);
    })
    printf("↳ 请输入你要删除的订单编号：");

    int id;
    scanf("%d", &id);

    bool deleted = false;

    REMOVE_IF(ORDER_LIST, Order *, order, {
        if (order->id == id) {
            deleted = true;
            free(order);
            REMOVE = true;
        }
    })

    if (deleted) {
        printf("\n◉ 删除成功！\n\n");
    } else {
        printf("× 抱歉，没有找到编号为 %d 的订单！\n\n", id);
    }
}


void commandSell() {
    // 创建订单
    LIST orders = list_create();

    // 循环
    LOOP {
        printAllCategory();
        printf("↳ 请输入你要购买的商品类别：");

        int category_id;
        scanf("%d", &category_id);

        printf("\n");

        // 输入 -1 结束
        if (category_id == -1) {
            printf("\n");
            return;
        }

        printf("◉ 该类别下所有商品如下:\n\n");

        // 输出所有商品信息
        FOREACH(GOODS_LIST, Goods *, g, {
            if (g->category == category_id) printf("  %s\t%s\n", g->id, g->name);
        })

        char goods_id[20];
        printf("↳ 请输入购买的商品（输入 -1 重新选择类别）：");
        scanf("%s", goods_id);

        if (strcmp(goods_id, "-1") == 0) {
            continue;
        }

        Goods *goods = findGoodsByID(goods_id);
        if (goods == NULL) {
            printf("× 商品不存在！\n\n");
            continue;
        }

        printf("↳ 请输入购买的数量：");

        int count;
        scanf("%d", &count);
        if (goods->stock < count) {  //goods[i].many表示为商品库存量
            printf("× 抱歉，目前商品供货不足，仅有 %d 件,购买失败！\n\n", goods->stock);
            continue;
        }

        goods->stock -= count; //更新库存量
        goods->sales += count; //更新销售量

        Order *order = malloc(sizeof(Order));
        order->id = NEXT_ORDER_ID++;
        order->count = count; //记录下购买的数量
        order->price = goods->price; //记录下所购买商品的单价
        order->total = goods->price * count; //记录下购买该商品所花费的总额

        //记录下所购买的商品
        strcpy(order->goods_id, goods->id);
        strcpy(order->goods->name, goods->name);

        list_add(orders, order);

        printf("\n◉ 购买 %s 成功！\n", goods->name);

        printf("↳ 输入 1 以继续购买，输入 -1 结束购买:");

        int x;
        scanf("%d", &x);

        if (x == -1) break;
    }

    if (list_size(orders) != 0) {
        printf("\n您成功购买的商品如下:\n");//
        printf("商品名称\t购买数量\t商品单价\t所花费金额\n"); //输出所购买的商品的信息
        printf("-------------------------------------------------------------------\n");

        FOREACH(orders, Order *, order, {
            printf("%s\t\t%d\t\t%.2f\t\t%.2f\n", order->goods->name, order->count, order->price, order->total);
            orders = orders->next;
        })

        printf("-------------------------------------------------------------------\n\n");
    }

    list_free(orders);
}