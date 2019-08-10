#include <stdlib.h>
#include <string.h>
#include <list.h>
#include <dao.h>
#include <user.h>
#include <student.h>
#include <admin.h>
#include <sims.h>

int main()
{

	//  初始化链表、加载数据
	init_sims();
	
	// 进入学生信息管理系统
	start_sims();
	
	// 保存数据、
	exit_sims();

	return 0;
}
