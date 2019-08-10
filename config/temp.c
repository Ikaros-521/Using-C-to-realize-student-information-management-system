	List* list = creat_list();
	for(int i=0; i<5; i++)
	{
		Student* stu = malloc(STU_SIZE);
		strcpy(stu->name,"haha");
		stu->sex = 'a'+rand()%26;
		stu->id = 10010+rand()%1000;
		add_tail_list(list,stu);
	}
	save(list,STU_PATH,STU_SIZE);
