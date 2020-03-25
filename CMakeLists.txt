cmake_minimum_required(VERSION 3.16)
project(Marketing4C C)

set(CMAKE_C_STANDARD 99)

add_executable(Marketing4C main.c core.h components/login.c components/login.h definition/goods.c definition/goods.h definition/order.c definition/order.h definition/category.c definition/category.h controller.c controller.h core.c)