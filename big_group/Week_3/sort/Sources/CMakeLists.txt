
cmake_minimum_required(VERSION 3.0)
project(sort)
 
#等价于g++ main.cpp src/swap.cpp -Iinclude -o  main中的-Iinclude头文件搜索路径
include_directories(../Headers)
#等价于g++ main.cpp src/swap.cpp -Iinclude -o  main_cmake
add_executable(sort_cmake rand.c sort.c test.c)