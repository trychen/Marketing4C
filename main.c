#include <stdio.h>

#include "controller.h"
#include "components/login.h"

/**
 * 系统初始化
 */
void init() {
    printf("欢迎使用 ➭ 商品销售系统 V1.0\n\n");
    printf("▧ 系统正在初始化...\n");
    // 初始化密码
    initPassword();
    // 读取数据文件
    readAllCategoryFromFile();
}

/**
 * 处理业务流程
 */
_Noreturn void process() {
    // 进行登录
    login();

    // 打印一次帮助信息
    help();

    // 开始执行命令循环
    for(;;) {
        command();
    }
}

/**
 * 程序入口方法
 */
int main() {
    // 初始化
    init();

    // 业务开始
    process();
    return 0;
}