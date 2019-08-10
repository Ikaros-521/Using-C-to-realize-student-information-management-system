#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

// 设计链表节点
typedef struct Node
{
	void* ptr;	// 指向数据的首地址
	struct Node* next;	// 元素的下一个位置
}Node;

// 设计链表结构
typedef struct List
{
	Node* head;
	size_t size;
}List;

// 定义函数指针类型
typedef int (*compar)(const void* ptr1,const void* ptr2);

// 创建结点
Node* creat_node(void* ptr);
// 创建链表
List* creat_list(void);
// 销毁链表
void destory_list(List* list);
// 清空链表
void clear_list(List* list);
// 头部添加元素
void add_head_list(List* list,void* ptr);
// 尾部添加元素
void add_tail_list(List* list,void* ptr);
// 头部删除元素
bool del_head_list(List* list);
// 尾部删除元素
bool del_tail_list(List* list);
// 获取链表长度
size_t size_list(List* list);
// 从index位置前插入元素
bool insert_list(List* list,int index,void* ptr);
// 访问index元素
void* access_list(List* list,int index);
// 按位置删除元素
bool del_index_list(List* list,int index);
// 按值删除元素
bool del_value_list(List* list,void* ptr,compar cmp);
// 查找值为value的元素
int find_list(List* list,void* ptr,compar cmp);
// 排序
void sort_list(List* list,compar cmp);
// 遍历
void show_list(List* list,void (*show)(const void* ptr));
void show_index(List* list,int index,void (*show)(const void* ptr));

#endif//LIST_H
