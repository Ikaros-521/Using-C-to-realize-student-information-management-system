#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include "getch.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <list.h>

#define pf printf
#define sf scanf

typedef enum {
	Error=-1,
	NameError,
	PassError,
	IsLock,
	LoginOk
}State;

void clear_stdin(void);

char* get_str(char* str,size_t len);

char get_sex(void);

char get_cmd(char start,char end);

char* get_pw(char* passwd,bool is_show,size_t size);

int binary_find(void* arr[],size_t len,int key);

int _binary_find(void* arr[],size_t l,size_t r,int key);

void quick_sort(void* arr[],size_t len,compar cmp);

#endif//TOOLS_H
