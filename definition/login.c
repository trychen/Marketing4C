#include "login.h"

char * CURRENT_PASSWORD;

bool initPassword() {
    // 创建密码读入缓冲区
    char buf[MAX_LENGTH_PASSWORD];
    FILE *fp = fopen(PASSWORD_BIN_PATH,"r");

    // 文件为空，密码未初始化
    if(fp == NULL) {
        return true;
    }

    // 读取数据
    if (fgets(buf, MAX_LENGTH_PASSWORD, fp) != NULL) {
        size_t length = strlen(buf);

        // 解密
        for (int i = 0; i < length; ++i) {
            buf[i] = buf[i] + i + 3;
        }

        // 拷贝密码到新的内存空间
        char *loadedPassword = calloc(length, sizeof(char));
        strcpy(loadedPassword, buf);

        // 存储密码变量
        CURRENT_PASSWORD = loadedPassword;

        fclose(fp);
        return true;
    }

    // 读取失败
    fclose(fp);
    perror("加载校验文件失败，将重置密码");
    return false;
}

void setPassword(const char *input) {
    // 拷贝密码到新的内存空间
    char *new = calloc(MAX_LENGTH_PASSWORD, sizeof(char));
    strcpy(new, input);

    // 加密
    int len = strlen(input);
    for (int i = 0; i < len; ++i) {
        *(new + i) = *(new + i) - i - 3;
    }

    // 写入文件
    FILE *fp = fopen(PASSWORD_BIN_PATH,"w");

    fputs(new, fp);

    fclose(fp);

    // 释放已有的密码
    if (CURRENT_PASSWORD != NULL) {
        free(CURRENT_PASSWORD);
    }

    CURRENT_PASSWORD = new;
}


void commandResetPassword() {
    printf("▧ 修改密码\n");
    printf("↳ 请输入原密码：");
    char password[20];
    scanf("%s", password);

    if (strcmp(password, CURRENT_PASSWORD) != 0) {
        printf("× 原密码不匹配，设置失败！\n");
        return;
    }

    printf("↳ 请输入新的密码：");
    scanf("%s", password);

    char confirmPassword[20];
    printf("↳ 再次输入新的密码：");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("× 两次输入的密码不一致，设置失败！\n");
        return;
    }

    setPassword(password);

    printf("\n◉ 修改密码成功！\n\n");
}

void login() {
    if (CURRENT_PASSWORD == NULL) {
        // 未设置密码

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