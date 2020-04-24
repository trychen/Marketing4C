#ifndef MARKETING4C_LOGIN_H
#define MARKETING4C_LOGIN_H

#include "../core.h"

/**
 * 最大密码长度
 */
#define MAX_LENGTH_PASSWORD 128

/**
 * 存储密码的文件路径
 */
#define PASSWORD_BIN_PATH "password.txt"

/**
 * 当前缓存的密码
 */
extern char *CURRENT_PASSWORD;

/**
 * 读取密码
 * @return 是否成功
 */
bool initPassword();

/**
 * 重置密码
 * @param input 新密码
 */
void setPassword(const char *input);

/**
 * 开始登陆
 */
void login();

/**
 * 重置代码
 */
void commandResetPassword();

#endif //MARKETING4C_LOGIN_H
