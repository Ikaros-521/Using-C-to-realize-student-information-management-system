#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <student.h>
#include <user.h>

List* stu_list = NULL;
List* user_list = NULL;

static const Student* stu_arr[STU_MAX];

int lock = 0;

static void user_add(void)
{
	Student* stu = malloc(sizeof(Student));
	pf("添加学生\n");
	pf("请输入学生姓名：");
	get_str(stu->name,20);
	pf("请输入学生性别：");
	stu->sex = get_sex();
	pf("请输入学生工号：");
	sf("%d",&stu->id);
	add_tail_list(stu_list,stu);
	stu_arr[0] = NULL;
}

static void user_del(void)
{
	pf("删除学生\n");
	pf("请输入要删除的学生学号:");
	int stu_id = 0;	
	sf("%d",&stu_id);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const Student* stu = ptr1;
		const int* id = ptr2;
		if(stu->id > *id)
			return 1;
		else if(stu->id < *id)
			return -1;
		else 
			return 0;
	}
	if(del_value_list(stu_list,&stu_id,cmp))
	{
		pf("学号：%d,删除成功\n",stu_id);
		stu_arr[0] = NULL;
	}
	else
	{
		pf("无此学号，删除失败\n");
	}
}

static void user_chg(void)
{
	pf("请输入学生学号：");
	int Cstudent_id;
	sf("%d",&Cstudent_id);
	getch();
	int cmp(const void* ptr1,const void* ptr2)
	{
		const Student* stu = ptr1;
		const int* id = ptr2;
		if(stu->id > *id)
			return 1;
		else if(stu->id < *id)
			return -1;
		else 
			return 0;
	}
	int index = find_list(stu_list,&Cstudent_id,cmp);
	if(index == -1)
	{
		pf("无此学号。\n");
	}
	else
	{
		Student* stu = malloc(sizeof(Student));
		stu = access_list(stu_list,index);
		pf("请输入新的学生姓名：");
		get_str(stu->name,20);
		pf("请输入新的学生性别：");
		stu->sex = get_sex();
		pf("修改成功\n");
		getch();
/*		
		pf("请输入新的学生工号：");
		sf("%d",&stu->id);
		if(del_index_list(stu_list,index))
		{
			if(index == stu_list->size)
			{
				add_tail_list(stu_list,stu);
				pf("修改成功\n");
			}
			else
			{
				if(insert_list(stu_list,index,stu))
				{
					pf("修改成功\n");
				}
				else
				{
					pf("修改失败\n");
				}
			}
		}
		else
		{
			pf("修改失败\n");
		}
*/
	}
}

static void user_find(void)
{
	user_sort();
	pf("请输入学生学号：");
	int stu_id;	
	sf("%d",&stu_id);
	int cmp(const void* ptr1,const void* ptr2)
	{
		const Student* stu = ptr1;
		const int* id = ptr2;
		if(stu->id > *id)
			return 1;
		else if(stu->id < *id)
			return -1;
		else 
			return 0;
	}
	int index = binary_find((void**)stu_arr,stu_list->size,stu_id);
	if(index == -1)
	{
		pf("没有此学生\n");
	}
	else
	{
		void show(const void* ptr)
		{
			const Student* stu = ptr;
			printf("姓名：%s 性别：%c 学号：%d\n",stu->name,stu->sex,stu->id);
		}
		show_index(stu_list,index,show);
	}

/*	
	int index = find_list(stu_list,&Cstudent_id,cmp);
	if(index == -1)
	{
		pf("无此学号。\n");
	}
	else
	{
		void show(const void* ptr)
		{
			const Student* stu = ptr;
			printf("姓名：%s 性别：%c 学号：%d\n",stu->name,stu->sex,stu->id);
		}
		show_index(stu_list,index,show);
	}
*/
	getch();
}

// 排序
void user_sort(void)
{
	if(stu_arr[0] != NULL) return;
	//const Student* arr[stu_list->size];
	size_t index = 0;
	void get_stu(const void* ptr)
	{
		stu_arr[index++] = ptr;
	}
	show_list(stu_list,get_stu);
	
	int cmp(const void* ptr1,const void* ptr2)
	{
		const Student* s1 = ptr1, * s2 = ptr2;
		if(s1->id > s2->id)
			return 1;
		else if(s1->id < s2->id)
			return -1;
		else
			return 0;
	}
	
	quick_sort((void**)stu_arr,index,cmp);
	
	for(int i=0; i<index; i++)
	{
		pf("姓名：%s 性别：%c 学号：%d\n",stu_arr[i]->name,stu_arr[i]->sex,stu_arr[i]->id);
	}
}

void user_show(void)
{
	pf("显示在校学生\n");
	void show(const void* ptr)
	{
		const Student* stu = ptr;
		printf("%s %c %d\n",stu->name,stu->sex,stu->id);
	}
	show_list(stu_list,show);
	getch();
}

static void user_menu(void)
{
	for(;;)
	{
		system("clear");
		pf("******学生信息管理******\n");
		pf("1、增\n");
		pf("2、删\n");
		pf("3、改\n");
		pf("4、查\n");
		pf("5、排\n");
		pf("6、显\n");
		pf("7、撤\n");
		
		switch(getch())
		{
			case '1': user_add(); break;
			case '2': user_del(); break;
			case '3': user_chg(); break;
			case '4': user_find(); break;
			case '5': user_sort(); break;
			case '6': user_show(); break;
			case '7': return;
		}
	}
}

void user_start(void)
{

	char user[20] = {};
	char pass[20] = {};
	pf("请输入帐号:");
	get_str(user,20);
	pf("请输入密码:");
	get_str(pass,20);
	if(user_login(user,pass) == LoginOk)
	{
		user_menu();
	}
	else if(user_login(user,pass) == NameError)
	{
		lock++;
		pf("用户名或密码错误，请重新输入！\n");
	}
	else if(user_login(user,pass) == PassError)
	{
		lock++;
		pf("密码错误，请重新输入！\n");
	}
	else if(user_login(user,pass) == IsLock)
	{
		pf("系统已经被锁定，禁止登陆\n");
	}
	else
	{
		pf("异常错误\n");
	}
	getch();

	

}

// 登录
State user_login(const char* user,const char* pass)
{	
	if(lock >= 3)
	{
		return IsLock;
	}

	char cuser[20] = {};
	char cpass[20] = {};
	strcpy(cuser,user);
	strcpy(cpass,pass);

	if(user == NULL)
	{
		pf("用户名为空，请重新输入！\n");
		return Error;
	}	
	if(pass == NULL)
	{
		pf("密码为空，请重新输入！\n");
		return Error;
	}
	int cmp1(const void* ptr1,const void* ptr2)
	{
		const User* user = ptr1;
		const char* name = ptr2;
		return strcmp(user->name,name);	
	}
	int cmp2(const void* ptr1,const void* ptr2)
	{
		const User* user = ptr1;
		const char* passwd = ptr2;
		return strcmp(user->passwd,passwd);	
	}
	int index1 = find_list(user_list,cuser,cmp1);
	int index2 = find_list(user_list,cpass,cmp2);
	if(index1 == -1)
		return NameError;
	else
	{
		if(index2 == -1)
			return PassError;
		else
		{
			return LoginOk;
		}
	}

	

}
