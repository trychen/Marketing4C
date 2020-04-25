#include <stdio.h>

#include "controller.h"

/**
 * 程序入口方法
 */
int main() {
    // 初始化

    printf("欢迎使用 ➭ 商品销售系统 V1.0\n\n");
    printf("▧ 系统正在初始化...\n");
    // 初始化密码
    if (!initPassword()) {
        printf("× 加载密码失败！\n\n");
        return 1;
    }
    // 读取数据文件
    readAllCategoryFromFile();
    readAllGoodsFromFile();
    readAllOrdersFromFile();

    // 业务开始
    // 进行登录
    login();

    // 打印一次帮助信息
    help();

    // 开始执行命令循环
    LOOP {
        if (!command()) break;
    }

    writeAllGoodsToFile();
    writeAllOrdersToFile();

    return 0;
}