cmake_minimum_required(VERSION 3.17)
project(product_dao_iteration2 C)

set(CMAKE_C_STANDARD 11)

add_executable(product_dao_iteration2 main.c product.c product.h product_dao.c product_dao.h)