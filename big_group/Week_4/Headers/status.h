#ifndef STATUS_H
#define STATUS_H



typedef unsigned long long size_t;
//定义状态枚举
typedef enum Status 
{
	_ERROR,
	_SUCCESS,
    _OVERFLOW,
    _EXIST,
    _NULLPOINTER
} Status;

//定义数据类型枚举
typedef enum Elemtype
{
    _INT=1,
    _DOUBLE=2,
    _STRING=3,
    _CHAR=4,
    _POINTER=5,
}Elemtype;

#endif