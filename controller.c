#include "controller.h"

void help() {
    printf("");
    printf("☴☴☴☴☴ 商品销售系统菜单 ☴☴☴☴☴\n");
    printf("   ◉ 1. 按商品编号排序\n");
    printf("   ◉ 2. 销售商品\n");
    printf("   ◉ 3. 删除指定订单\n");
    printf("   ◉ 4. 给定类别的商品销售明细\n");
    printf("   ◉ 5. 所有商品销售情况统计\n");
    printf("   ◉ 6. 按商品销售量排序\n");
    printf("   ◉ 7. 输出指定商品信息\n");
    printf("   ◉ 8. 修改密码\n");
    printf("   ◉ 0. 退出系统\n");
    printf("   ◉ *. 其他任意数字显示菜单\n");
    printf("☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱\n\n");
}

bool command() {
    printf("↳ 请输入命令：");

    char input[1];
    scanf("%s", input);

    int id = input[0] - '0';

    printf("\n");

    if (id == 0) {
        printf("▧ 已退出 ➭ 感谢您使用 ➭ 商品销售系统 V1.0\n");
        return false;
    } else if (id == 1) {
        printAllGoodsInIDOrder();
    } else if (id == 2) {
        commandSell();
    } else if (id == 3) {
        commandDeleteOrder();
    } else if (id == 4) {
        commandPrintOrderInCategory();
    } else if (id == 5) {
        commandPrintAllGoods();
    } else if (id == 6) {
        commandPrintGoodsInSalesOrder();
    } else if (id == 7) {
        commandPrintGoods();
    } else if (id == 8) {
        commandResetPassword();
    } else help();

    return true;
}

void commandPrintAllGoods() {
    printf("\n◉ %10s\t%8s\t%6s\t%6s\t%6s\n", "商品编号", "商品名称", "销售数量", "单价", "总金额");

    FOREACH(GOODS_LIST, Goods *, g,{
        printf("| %10s\t%8s\t%6d\t%6.2f\t%6.2f\n", g->id, g->name, g->sales, g->price, g->price * ((float) g->sales));
    })
}

/**
 * 比较销量
 */
bool func_goods_inSalesOrder(Goods *a, Goods *b) {
    return a->sales >= b->sales;
}

void commandPrintGoodsInSalesOrder() {
    // 插入排序
    Linker *sortedHead = list_folkInOrder(GOODS_LIST, func_goods_inSalesOrder);

    printf("\n◉ %10s\t%8s\t%8s\t%8s\t%8s\n", "商品编号", "商品名称", "销售数量", "单价", "总金额");

    FOREACH(sortedHead, Goods *, g, {
        // 商品编号、商品名称、销售数量、单价、总金额
        printf("| %10s\t%8s\t%8d\t%8.2f\t%8.2f\n", g->id, g->name, g->sales, g->price, g->price * ((float) g->sales));
    })

    printf("\n");

    list_free(sortedHead);
}

void commandPrintOrderInCategory() {
    printAllCategory();

    printf("↳ 请输入你要查询的类别：");

    int id;
    scanf("%d", &id);

    // 检查类别是否存在
    char *cgName = getCategoryDisplayNameByID(id);
    if (strcmp(cgName, CATEGORY_NOT_DEFINED_DISPLAY_NAME) == 0) {
        printf("× 抱歉，没有找到类别 %d！\n\n", id);
        return;
    }

    printf("\n◉ 正在输出类别 %s 的订单：\n", cgName);
    printf("| 订单号\t商品编号\t商品名称\t销售数量\t单价\t总金额\n");
    FOREACH(ORDER_LIST, Order*, order, {
        // 判读类别是否为用户输入的类别
        if (order->goods->category != id) continue;
        printf("| %04d\t%s\t%s\t%d\t%.2f\t%.2f\n", order->id, order->goods_id, order->goods->name, order->count, order->price, order->total);
    })
}