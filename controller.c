#include "controller.h"

/*
 *  “按商品编号排序”：排序后结果显示项包含：商品编号、商品类别名称、商品名称、库存数量、单价、总金额，需要注意其中“商品类别名称”数据与商品信息不在同一文件中。
 *  “销售商品”：销售商品功能是指用户添加一条销售数据，销售单号自动生成，一般是上张单号加1。输入销售数量时，需要检查库存数是否满足，不满足则不能销售，销售完成后需要变更库存数。考虑方便用户操作，首先应显示商品类别编号和名称，用户选择编号后，显示该类别下所有商品供用户选择，之后再要求输入购买数量，该值不能超过库存量。以上工作可重复多次直到用户不再需要购买。此时，显示用户购买的所有商品，然后生成对应的订单号（一个订单由多个商品组成）。商品购买成功后要及时更新库存。
 *  “删除指定订单”：删除指定订单要求根据用户的订单号删除相应数据，同时需要更新库存。应先显示所有订单供用户选择，选择后，显示指定订单，要求用户确认。删除订单后，相应的商品库存要进行更新。
 *  “输出给定类别的商品销售明细”：先显示类别，供用户选择，然后显示商品销售情况：包含：订单号、商品编号、商品名称、销售数量、单价、总金额
 *  “所有商品销售情况明细”：首先按商品统计销售情况，然后显示，包含：商品编号、商品名称、销售数量、单价、总金额
 *  “按商品销售量排序”：显示信息包含：商品编号、商品名称、销售数量、单价、总金额
 *  “设置和修改系统登录密码”：设置系统的密码。密码在屏幕上以*显示，在系统中以密文保存，为了防止用户误操作，设置密码时要求输入两次，两次相同，方可设置成功。
 *  “输出指定商品信息”：显示所有商品编号和名称供用户选择，选择后显示如下信息：商品编号、商品名称、库存数量、销售数量、单价。
 */
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
    printf("☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱☱\n\n");
}

void command() {
    printf("↳ 请输入命令：");

    char input[1];
    scanf("%s", input);

    int id = input[0] - '0';

    printf("\n");

    if (id == 0) {
        printf("▧ 已退出 ➭ 感谢您使用 ➭ 商品销售系统 V1.0\n");
        exit(0);
    } else if (id == 1) {
        printAllGoodsInIDOrder();
    } else if (id == 2) {
        commandSell();
    } else if (id == 3) {
        commandDeleteOrder();
    } else if (id == 4) {
        commandPrintOrderInCategory();
    } else if (id == 5) {
        commandPrintGoodsInSalesOrder();
    } else if (id == 6) {
        commandPrintGoodsInSalesOrder();
    } else if (id == 7) {
        commandPrintGoods();
    } else if (id == 8) {
        commandResetPassword();
    } else help();
}


/**
 * 比较销量
 */
bool func_goods_inSalesOrder(Goods *a, Goods *b) {
    return a->sales >= b->sales;
}

void commandPrintGoodsInSalesOrder() {
    Linker *sortedHead = list_folkInOrder(GOODS_LIST, (int (*)(void *, void *)) func_goods_inSalesOrder);

    printf("\n◉\t%s\t%s\t%s\t%s\t%s\n", "商品编号", "商品名称", "销售数量", "单价", "总金额");
    while (sortedHead != NULL) {
        Goods *g = sortedHead->entry;

        // 商品编号、商品名称、销售数量、单价、总金额
        printf("↳\t%s\t%s\t%d\t%f\t%f\n", g->id, g->name, g->sales, g->price, g->price * ((float) g->sales));

        sortedHead = sortedHead->next;
    }

    printf("\n");

    list_free(sortedHead);
}

void commandPrintOrderInCategory() {
    printAllCategory();

    printf("↳ 请输入你要查询的类别：");

    int id;
    scanf("%d", &id);

    char *cgName = getCategoryDisplayNameByID(id);
    if (strcmp(cgName, CATEGORY_NOT_DEFINED_DISPLAY_NAME) == 0) {
        printf("× 抱歉，没有找到类别 %d！\n\n", id);
    }

    printf("\n◉ 正在输出类别 %s 的订单：", cgName);
    printf("◉ 订单号\t商品编号\t商品名称\t销售数量\t单价\t总金额\n");
    FOREACH(ORDER_LIST, Order*, order, {
        if (order->goods->category != id) continue;
        printf("| %04d\t%s\t%s\t%d\t%f\t%f\n", order->id, order->goods_id, order->goods->name, order->count, order->price, order->total);
    })

    printf("\n\n");
}