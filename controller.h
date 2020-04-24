//
// Created by Trychen on 2020/3/13.
//

#ifndef MARKETING4C_CONTROLLER_H
#define MARKETING4C_CONTROLLER_H

#include "definition/login.h"
#include "definition/category.h"
#include "definition/goods.h"
#include "definition/order.h"

/**
 * 登录的业务逻辑
 */
void login();

/**
 * 打印帮助信息
 */
void help();

/**
 * 处理命令，仅处理一条
 */
void command();

/**
 * 按商品销售量排序
 */
void commandPrintGoodsInSalesOrder();

/**
 * 销售商品
 */
void commandSell();
/**
 * 输出指定商品信息
 */
void commandPrintGoods();

/**
 * 删除订单
 */
void commandDeleteOrder();

/**
 * 按照类别输出订单信息
 */
void commandPrintOrderInCategory();

#endif //MARKETING4C_CONTROLLER_H
