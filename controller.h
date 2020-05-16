//
// 该文件用于控制主要的业务流程
// Created by 陈志林 & 任昊青 on 2020/3/13.
//

#ifndef MARKETING4C_CONTROLLER_H
#define MARKETING4C_CONTROLLER_H

#include "definition/login.h"
#include "definition/category.h"
#include "definition/goods.h"
#include "definition/order.h"


/**
 * 打印帮助信息
 */
void help();

/**
 * 处理命令，仅处理一条
 */
bool command();

/**
 * 按商品销售量排序
 */
void commandPrintGoodsInSalesOrder();

/**
 * 输出所有商品
 */
void commandPrintAllGoods();

/**
 * 按照类别输出订单信息
 */
void commandPrintOrderInCategory();

#endif //MARKETING4C_CONTROLLER_H
