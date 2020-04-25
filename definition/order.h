
#ifndef MARKETING4C_ORDER_H
#define MARKETING4C_ORDER_H

#include "../core.h"
#include "goods.h"

#define ORDER_BIN_PATH "order.txt"

typedef struct MarketOrder
{
    int id; // 订单编号
    char goods_id[30]; // 商品编号
    int count; // 销售量
    float price; // 单价
    float total; // 总金额

    Goods* goods; // 临时存储的商品名称，用于特点情况下使用
} Order;

/**
 * 商品列表
 */
extern LIST ORDER_LIST;

/**
 * 下一个订单 ID
 */
extern int NEXT_ORDER_ID;

extern LIST ORDER_FILE_COMMENTS;

/**
 * 从文件中读入订单，并存储到 {@var ALL_ORDERS}
 */
void readAllOrdersFromFile();

/**
 * 写入 {@see ALL_ORDERS} 中所有订单到文件
 */
void writeAllOrdersToFile();

/**
 * 输出订单信息
 */
void printOrder(Order *order);

/**
 * 销售商品
 */
void commandSell();

/**
 * 删除订单
 */
void commandDeleteOrder();

#endif //MARKETING4C_ORDER_H
