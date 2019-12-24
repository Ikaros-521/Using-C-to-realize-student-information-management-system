#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <user.h>
#include <admin.h>

static void admin_add(void)
{
	User* user = malloc(sizeof(User));
	pf("添加用户\n");
	pf("请输入用户姓名：");
	get_str(user->name,20);
	pf("请输入用户性别：");
	user->sex = get_sex();
	pf("请输入用户密码：");
	get_pw(user->passwd,true,20);
	pf("\n");
	pf("请输入用户编号：");
	sf("%d",&user->id);
	getch();
	add_tail_list(user_list,user);
}

static void admin_del(void)
{
	pf("删除用户\n");
	pf("请输入用户编号:");
	char Cuser_name[20] = {};	
	get_str(Cuser_name,20);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const User* user = ptr1;
		const char* name = ptr2;
		return strcmp(user->name,name);
	}
	printf("删除%s\n",del_value_list(user_list,Cuser_name,cmp)?" 成功":" 失败");
}

static void admin_chg(void)
{
	pf("请输入用户编号：");
	char Cuser_name[20] = {};	
	get_str(Cuser_name,20);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const User* user = ptr1;
		const char* name = ptr2;
		return strcmp(user->name,name);
	}
	int index = find_list(user_list,Cuser_name,cmp);
	if(index == -1)
	{
		pf("无此编号。\n");
	}
	else
	{
		User* user = malloc(sizeof(User));
		pf("请输入新的用户姓名：");
		get_str(user->name,20);
		pf("请输入新的用户性别：");
		user->sex = get_sex();
		pf("请输入新的用户编号：");
		sf("%d",&user->id);
		if(del_index_list(user_list,index))
		{
			if(insert_list(user_list,index,user))
			{
				pf("修改成功\n");
			}
			else
			{
				pf("修改失败\n");
			}
		}
		else
		{
			pf("修改失败\n");
		}
	}
}

static void admin_find(void)
{
	pf("请输入用户编号：");
	char Cuser_name[20] = {};	
	get_str(Cuser_name,20);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const User* user = ptr1;
		const char* name = ptr2;
		return strcmp(user->name,name);
	}
	int index = find_list(user_list,Cuser_name,cmp);
	if(index == -1)
	{
		pf("无此编号。\n");
	}
	else
	{
		void show(const void* ptr)
		{
			const User* user = ptr;
			printf("姓名：%s 性别：%c 编号：%d\n",user->name,user->sex,user->id);
		}
		show_index(user_list,index,show);
	}
	getch();
}

static void admin_sort(void)
{
	const User* arr[user_list->size];
	size_t index = 0;
	void get_user(const void* ptr)
	{
		arr[index++] = ptr;
	}
	show_list(user_list,get_user);
	
	int cmp(const void* ptr1,const void* ptr2)
	{
		const User* s1 = ptr1, * s2 = ptr2;
		if(s1->id > s2->id)
			return 1;
		else if(s1->id < s2->id)
			return -1;
		else
			return 0;
	}
	
	quick_sort((void**)arr,index,cmp);
	
	for(int i=0; i<index; i++)
	{
		pf("姓名：%s 性别：%c 编号：%d\n",arr[i]->name,arr[i]->sex,arr[i]->id);
	}
}

void admin_show(void)
{
	pf("显示用户\n");
	void show(const void* ptr)
	{
		const User* user = ptr;
		printf("姓名：%s 性别：%c 编号：%d\n",user->name,user->sex,user->id);
	}
	show_list(user_list,show);
	getch();
}

static void admin_menu(void)
{
	for(;;)
	{
		system("clear");
		pf("******用户信息管理******\n");
		pf("      1、增加用户\n");
		pf("      2、删除用户\n");
		pf("      3、修改用户\n");
		pf("      4、查询用户\n");
		pf("      5、排序用户\n");
		pf("      6、显示用户\n");
		pf("      7、撤回上级\n");
		pf("**********************\n");
		
		switch(get_cmd('1','7'))
		{
			case '1': admin_add(); break;
			case '2': admin_del(); break;
			case '3': admin_chg(); break;
			case '4': admin_find(); break;
			case '5': admin_sort(); break;
			case '6': admin_show(); break;
			case '7': return;
		}
	}
}

void admin_start(void)
{
	char admin[20]={};
	char pass[20]={};
	pf("请输入编号:");
	get_str(admin,20);
	pf("请输入密码:");
	get_pw(pass,true,20);
	if(admin_login(admin,pass) == LoginOk)
	{
		admin_menu();
	}
	else if(admin_login(admin,pass) == NameError)
	{
		pf("用户名或密码错误，请重新输入！\n");
	}
	else if(admin_login(admin,pass) == PassError)
	{
		pf("密码错误，请重新输入！\n");
	}
	else
	{
		pf("异常错误\n");
	}

}

// 登录
State admin_login(const char* admin,const char* pass)
{	
	char* Admin = "admin";
	char* Pass = "admin";
	if(admin == NULL)
	{
		pf("用户名为空，请重新输入！\n");
		return Error;
	}	
	if(pass == NULL)
	{
		pf("密码为空，请重新输入！\n");
		return Error;
	}
	if(strcmp(Admin,admin)==0)
	{
		if(strcmp(Pass,pass)==0)
			return LoginOk;
		else
			return PassError;
	}
	else
		return NameError;
}
