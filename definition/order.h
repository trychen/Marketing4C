
#ifndef MARKETING4C_ORDER_H
#define MARKETING4C_ORDER_H

#include "../core.h"

#define ORDER_BIN_PATH "order.txt"

typedef struct MarketOrder
{
    char* id; // 订单编号
    char* goods_id; // 商品编号
    int count; // 销售量
    float price; // 单价
    float total; // 总金额
} Order;

/**
 * 商品列表
 */
Linker * ORDER_LIST;

/**
 * 从文件中读入订单，并存储到 {@var ALL_ORDERS}
 */
void readAllOrdersFromFile();

/**
 * 写入 {@see ALL_ORDERS} 中所有订单到文件
 */
void writeAllOrdersToFile();

#endif //MARKETING4C_ORDER_H
