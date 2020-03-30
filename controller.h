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
void printGoodsInSalesOrder();

#endif //MARKETING4C_CONTROLLER_H
