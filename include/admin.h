#ifndef ADM_H
#define ADM_H

#include <list.h>
#include <tools.h>

extern List* user_list;

void admin_start(void);
// 登录
State admin_login(const char* admin,const char* pass);

#endif//ADM_H
