#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <stdbool.h>
#include <tools.h>

void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清理输入缓冲区
}

char* get_str(char* str,size_t len)
{
	if(NULL == str)
	{
		puts("空指针异常！");
		return NULL;
	}

	char *in=fgets(str,len,stdin);
	
	size_t cnt = strlen(str);
	if('\n' == str[cnt-1])
	{
		str[cnt-1] = '\0';
	}
	
	clear_stdin();

	return str;
}

char get_sex(void)
{
	printf("（m男，w女）：");
	while(true)
	{
		char sex = getch();
		if('w' == sex || 'm' == sex)
		{
			printf("%s\n",'w'==sex?"女":"男");
			return sex;
		}
	}
}

char get_cmd(char start,char end)
{
	clear_stdin();

	printf("请输入指令:");
	while(true)
	{
		char val = getch();
		if(val >= start && val <= end)
		{
			printf("%c\n",val);
			return val;
		}
	}
}

char* get_pw(char* passwd,bool is_show,size_t size)
{
	if(NULL == passwd) return NULL;

	int count = 0;
	do{
		char val = getch();
		if(127 == val)
		{
			if(count > 0)
			{
				if(is_show)printf("\b \b");
				count--;
			}
			continue;
		}
		else if(10 == val)
		{
			break;
		}
		passwd[count++] = val;
		if(is_show) printf("*");
	}while(count < size -1);

	passwd[count] = '\0';
	return passwd;
}

int _binary_find(void* arr[],size_t l,size_t r,int key)
{
	int pi;
	while(l <= r)
	{
		pi = (l+r)/2;
		if(key > arr[pi])
			l = pi+1;
		else if(key < arr[pi])
			r = pi-1;
		else
			return pi;
	}
	return -1;
}

// 二分
int binary_find(void* arr[],size_t len,int key)
{
	return _binary_find(arr,0,len-1,key);
}

void _quick_sort(void* arr[],size_t left,size_t right,compar cmp)
{
	if(left >= right) return;

	// 计算标杆的下标
	int pi = (left+right)/2;
	// 备份标杆的值
	void* pv = arr[pi];
	// 备份左右下标
	int l = left , r = right;

	// 左右下标相遇时结束
	while(l < r)
	{
		// 在标杆的左边寻找比它大的数据
		while(l<pi && 1!=cmp(arr[l],pv)) l++;
		if(l<pi) // 如果没有超出范围，说明找到比标杆大的值
		{
			// 与标杆交换位置，并记录新的标杆下标
			arr[pi] = arr[l];
			pi = l;
		}
		// 在标杆的右边寻找比它小的数据
		while(pi<r && 1!=cmp(pv,arr[r])) r--;
		if(pi<r) // 如果没有走出范围，说明找到比标杆小的值
		{
			arr[pi] = arr[r];
			pi = r;
		}
	}
	// 还原标杆的值
	arr[pi] = pv;
	//show_arr(arr,10);
	if(pi-left > 1) _quick_sort(arr,left,pi-1,cmp);
	if(right-pi > 1) _quick_sort(arr,pi+1,right,cmp);
}

void quick_sort(void* arr[],size_t len,compar cmp)
{
	_quick_sort(arr,0,len-1,cmp);
}
