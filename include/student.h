#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
	char name[20];
	char sex;
	int id;
}Student;

#define STU_MAX 1000

#define STU_SIZE sizeof(Student)

#endif//STUDENT_H
