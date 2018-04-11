cmake_minimum_required(VERSION 3.9)
project(nf16-tp3 C)

set(CMAKE_C_STANDARD 99)

add_executable(nf16-tp3 main.c interface.h interface.c blockchain.h blockchain.c)