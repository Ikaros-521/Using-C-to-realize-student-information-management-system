#include <stdlib.h>
#include <list.h>

// 创建结点
Node* creat_node(void* ptr)
{
	Node* node = malloc(sizeof(Node));
	node->ptr = ptr;
	node->next = NULL;
	return node;
}

// 创建链表
List* creat_list(void)
{
	List* list = malloc(sizeof(List));
	list->head = NULL;
	list->size = 0;
	return list;
}

// 销毁链表
void destory_list(List* list);
// 清空链表
void clear_list(List* list);
// 头部添加元素
void add_head_list(List* list,void* ptr)
{
	Node* node = creat_node(ptr);
	node->next = list->head;
	list->head = node;
	list->size++;
}

// 尾部添加元素
void add_tail_list(List* list,void* ptr)
{
	Node* node = creat_node(ptr);
	if(0 == list->size)
	{
		list->head = node;
	}
	else
	{
		Node* tail = list->head;
		while(NULL != tail->next) 
			tail = tail->next;
		tail->next = node;
	}
	list->size++;
}

// 头部删除元素
bool del_head_list(List* list)
{
	if(list->size <= 0) return false;
	Node* node = list->head;
	list->head = node->next;
	free(node);
	list->size--;
	return true;
}

// 尾部删除元素
bool del_tail_list(List* list)
{
	if(list->size <= 0) return false;
	if(1 == list->size)
	{
		free(list->head);
		list->head = NULL;
		list->size = 0;
		return true;
	}
	
	Node* prev = list->head;
	while(NULL!=prev->next->next)
	{
		prev = prev->next;
	}
	
	Node* tail = prev->next;
	prev->next = NULL;
	free(tail);
	list->size--;
	return true;
}

// 获取链表长度
size_t size_list(List* list);

// 从index位置前插入元素
bool insert_list(List* list,int index,void* ptr)
{
	if(index < 0 || index >= list->size) return false;
	if(0 == index)
	{
		add_head_list(list,ptr);
		return true;
	}
	
	Node* prev = list->head;
	for(int i=0; i<index-1; i++)
	{
		prev = prev->next;
	}
	
	Node* node = creat_node(ptr);
	node->next = prev->next;
	prev->next = node;
	list->size++;
	return true;
}

// 访问index元素
void* access_list(List* list,int index)
{
	Node* node = list->head;
	for(int i=0; i<index; i++)
	{
		node = node->next;
	}
	return node->ptr;
}


// 按位置删除元素
bool del_index_list(List* list,int index)
{
	if(index < 0 || index >= list->size) return false;
	if(0 == index) return del_head_list(list);
	if(list->size-1 == index) return del_tail_list(list);
	
	Node* prev = list->head;
	for(int i=0; i<index-1; i++)
	{
		prev = prev->next;
	}
	Node* node = prev->next;
	prev->next = node->next;
	free(node);
	list->size--;
	return true;	
}

// 按值删除元素
bool del_value_list(List* list,void* ptr,compar cmp)
{
	if(list->size <= 0) return false;
	if(0 == cmp(list->head->ptr,ptr)) 
		return del_head_list(list);

	Node* prev = list->head;
	while(NULL != prev->next)
	{
		if(0 == cmp(prev->next->ptr,ptr))
		{
			Node* node = prev->next;
			prev->next = node->next;
			free(node);
			list->size--;
			return true;
		}
		prev = prev->next;
	}

	return false;
}

// 查找值为value的元素
int find_list(List* list,void* ptr,compar cmp)
{
	int index=0;
	for(Node* i=list->head; NULL!=i; i=i->next)
	{
		if(0 == cmp(i->ptr,ptr))
		{
			return index;
		}
		index++;
	}
	
	return -1;
}

// 排序
void sort_list(List* list,compar cmp)
{
	for(Node* i=list->head; NULL!=i->next; i=i->next)
	{
		for(Node* j=i->next; NULL!=j; j=j->next)
		{
			if(1 == cmp(i->ptr,j->ptr))
			{
				void* temp = i->ptr;
				i->ptr = j->ptr;
				j->ptr = temp;
			}
		}
	}
}

// 遍历
void show_list(List* list,void (*show)(const void* ptr))
{
	for(Node* i=list->head; NULL!=i; i=i->next)
	{
		show(i->ptr);
	}
}

void show_index(List* list,int index,void (*show)(const void* ptr))
{
	Node* node=list->head;
	for(int i=0; i<index; i++)
	{
		node = node->next;
	}
	show(node->ptr);
}

/***********以下是调用者所写代码*********************/


int cmp(const void* ptr1,const void* ptr2)
{
	const double *p1 = ptr1 , *p2 = ptr2;
	if(*p1 > *p2)
		return 1;
	else if(*p1 < *p2)
		return -1;
	else
		return 0;
}
