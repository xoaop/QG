
cmake_minimum_required(VERSION 3.0)
project(Calculator)
 
#等价于g++ main.cpp src/swap.cpp -Iinclude -o  main中的-Iinclude头文件搜索路径
include_directories(../Headers)
#等价于g++ main.cpp src/swap.cpp -Iinclude -o  main_cmake
add_executable(calculator_cmake calculator.c queue.c stack.c)