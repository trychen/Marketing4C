#include "login.h"

bool initPassword() {
    char buf[MAX_LENGTH_PASSWORD];
    FILE *fp = fopen(PASSWORD_BIN_PATH,"r");

    if(fp == NULL) {
        return false;
    }

    if (fgets(buf, MAX_LENGTH_PASSWORD, fp) != NULL) {
        size_t length = strlen(buf);
        char *loadedPassword = calloc(length, sizeof(char));
        strcpy(loadedPassword, buf);
        CURRENT_PASSWORD = loadedPassword;
        fclose(fp);
        return true;
    }

    fclose(fp);
    perror("加载校验文件失败，将重置密码");
    return false;
}

/**
 * 是否为合法的密码
 * @param password 密码
 * @return 合法返回 true
 */
bool isValidPassword(const char *password) {
    size_t len = strlen(password);
    return len > 6 && len < 20;
}

void setPassword(const char *input) {
    char *new = calloc(20, sizeof(char));
    strcpy(new, input);

    FILE *fp = fopen(PASSWORD_BIN_PATH,"w");

    fputs(new, fp);

    fclose(fp);

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

    printf("\n◉ 修改密码成功！\n\n");

    setPassword(password);
}