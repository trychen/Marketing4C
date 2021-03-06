//
// 商品的定义、加载、存储、排序、输出
// Created by 任昊青 on 2020/4/12.
//

#ifndef MARKETING4C_GOODS_H
#define MARKETING4C_GOODS_H

#include "../core.h"

#include "category.h"

/**
 * 存储商品信息的默认路径
 */
#define GOODS_BIN_PATH "goods.txt"

/**
 * 商品的结构体
 */
typedef struct MarketGoods
{
    char id[30]; // 商品编号
    int category; // 所属类别编号
    char name[30]; // 商品名称
    float price; // 库存量
    int stock; //单价

    int sales; // 销量
} Goods;

/**
 * 存储商品信息的链表
 */
extern LIST GOODS_LIST;
extern LIST GOODS_FILE_COMMENTS;

/**
 * 从文件中读取商品，并存入 {@see ALL_GOODS}
 */
void readAllGoodsFromFile();

/**
 * 写入 {@see ALL_GOODS} 中所有商品到文件
 */
void writeAllGoodsToFile();

/**
 * 根据 ID 找对应商品
 * @return 对应的 Goods 的指针，不存在则为 NULL
 */
Goods* findGoodsByID(const char*);

/**
 * 输出商品信息
 */
void printGoods(Goods *);

/**
 * 按商品编号排序
 */
void printAllGoodsInIDOrder();

/**
 * 输出指定商品的信息
 */
void commandPrintGoods();

#endif //MARKETING4C_GOODS_H
