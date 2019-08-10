#ifndef DAO_H
#define DAO_H

#include "list.h"

#define STU_PATH 	"./data/stu.dat"
#define USER_PATH	"./data/user.dat"
#define TEMP_PATH	"./data/temp.dat"
#define PASSWORD	"--zzxx--"

// 加载数据到链表
size_t load(List* list,const char* path,size_t size);

// 从链读取数据保存到文件中
size_t save(List* list,const char* path,size_t size);

#endif//DAO_H
