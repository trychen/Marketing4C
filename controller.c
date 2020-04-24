#include "controller.h"

void login() {
    if (CURRENT_PASSWORD == NULL) {
        char password[20];
        for (;;) {
            printf("↳ 初次使用请先设置密码：");
            scanf("%s", password);
            char confirmPassword[20];
            printf("↳ 再次输入密码以确认：");
            scanf("%s", confirmPassword);

            if (strcmp(password, confirmPassword) == 0) {
                printf("\n◉ 设置成功，已为你自动登录！\n");
                break;
            }

            printf("× 两次输入的密码不一致，请重新输入！\n\n");
        }

        setPassword(password);
    } else {
        char password[20];
        for (;;) {
            printf("↳ 请输入密码登录：");
            scanf("%s", password);

            if (strcmp(password, CURRENT_PASSWORD) == 0) {
                printf("\n◉ 登录成功！\n\n");
                break;
            }
            printf("× 密码错误，请重新输入\n\n");
        }
    }
}

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

    } else if (id == 6) {
        commandPrintGoodsInSalesOrder();
    } else if (id == 7) {
        commandPrintGoods();
    } else if (id == 8) {
        commandResetPassword();
    } else help();
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

bool func_goods_inSalesOrder(Goods *a, Goods *b) {
    return a->sales >= b->sales;
}

void commandPrintGoodsInSalesOrder() {
    printf("\n");

    Linker *sortedHead = list_folkInOrder(GOODS_LIST, (int (*)(void *, void *)) func_goods_inSalesOrder);

    printf("◉\t%s\t%s\t%s\t%s\t%s\n", "商品编号", "商品名称", "销售数量", "单价", "总金额");
    while (sortedHead != NULL) {
        Goods *g = sortedHead->entry;

        // 商品编号、商品名称、销售数量、单价、总金额
        printf("↳\t%s\t%s\t%d\t%f\t%f\n", g->id, g->name, g->sales, g->price, g->price * ((float) g->sales));

        sortedHead = sortedHead->next;
    }

    printf("\n");

    list_free(sortedHead);
}

void commandSell() {
    LIST orders = list_create();

    LOOP {
        printAllCategory();
        printf("↳ 请输入你要购买的商品类别：");

        int category_id;
        scanf("%d", &category_id);

        printf("\n");

        if (category_id == -1) {
            printf("\n");
            return;
        }

        printf("◉ 该类别下所有商品如下:\n\n");

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