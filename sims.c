#include <sims.h>
#include <signal.h>
#include <user.h>
#include <dao.h>
#include <admin.h>
#include <student.h>
#include <list.h>
#include <unistd.h>
#include <signal.h>

void menu_sims(void)
{
	for(;;)
	{	
		system("clear");
		pf("***欢迎使用学生信息管理系统***\n");
		pf("1、用户管理\n");
		pf("2、学生信息管理\n");
		pf("3、退出系统\n");
		pf("--------------------------\n");
		switch(get_cmd('1','3'))
		{
			case '1': admin_start(); break;
			case '2': user_start(); break;
			case '3': return;
		}
	}
}

void sigint(int sig)
{
	printf("你按了ctrl+c\n");
	//signal(SIGINT,SIG_DFL);
}

//  初始化链表、加载数据
void init_sims(void)
{
	signal(SIGINT,sigint);

	sigset_t set,oldset;
	sigemptyset(&set);
	sigemptyset(&oldset);
	sigaddset(&set,2);
	sigaddset(&set,3);
	sigprocmask(SIG_BLOCK,&set,&oldset);
	// 创建存储学生信息的链表
	stu_list = creat_list();
	user_list = creat_list();
	// 加载学生信息到链表中
	load(stu_list,STU_PATH,STU_SIZE);
	load(user_list,USER_PATH,USER_SIZE);

	// 恢复被屏蔽的信号
	sigprocmask(SIG_SETMASK,&oldset,NULL);
}
	
// 进入学生信息管理系统
void start_sims(void)
{
	menu_sims();
}
	
// 保存数据、
void exit_sims(void)
{
	save(stu_list,STU_PATH,STU_SIZE);
	save(user_list,USER_PATH,USER_SIZE);
}
