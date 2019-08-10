#ifndef USER_H
#define USER_H

#include <list.h>
#include <tools.h>

extern List* user_list;
extern List* stu_list;

typedef struct User
{
	char name[20];
	char sex;
	char passwd[20];
	int id;
}User;

#define USER_SIZE sizeof(User)

void user_sort(void);
void user_start(void);
void user_show(void);
// 登录
State user_login(const char* user,const char* pass);

#endif//USER_H
