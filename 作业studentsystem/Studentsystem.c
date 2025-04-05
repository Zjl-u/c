#include"Studentsystem.h"
int main() {
    Node* head = malloc(sizeof(Node));
    head->next = NULL;
    welcome();
    loadstudent(head);
    while(1)
    {
	    int b;
	    scanf("%d",&b);
	    switch (b)
	    {
	    case 1:inputstduent(head); break;
	    case 2:printstudent(head);break;
	    case 3:countstduent(head);break;
	    case 4:findstudent(head);break;
	    case 5:modistduent(head);break;
	    case 6:delatestudent(head);break;
	    case 7:sortstudent(head);break;
	    case 8:
			printf("再见，欢迎下次使用\n");
			return;
	    default:break;
	    }
	}
    return 0;
}
void welcome()
{
    printf("*************************\n");
    printf("*   学生成绩管理系统\t*\n");
    printf("*************************\n");
    printf("*   1录入学生信息\t*\n");
    printf("*   2打印学生信息\t*\n");
    printf("*   3统计学生信息\t*\n");
    printf("*   4查找学生信息\t*\n");
    printf("*   5修改学生信息\t*\n");
    printf("*   6删除学生信息\t*\n");
    printf("*   7按序号排序\t\t*\n");
    printf("*   8退出系统\t\t*\n");
    printf("*************************\n");
    printf("*   请输入您的选择\t*\n");
    printf("*************************\n");
}

void inputstduent(Node* head)
{
    Node* fresh = malloc(sizeof(Node));
    fresh->next = NULL;
    printf("请输入学生的序号，姓名，成绩:");
    scanf("%d %s %d", &fresh->student.serial,fresh->student.name,&fresh->student.score);

    Node* move = head;
    while (move->next != NULL)
    {
        move = move->next;
    }
    move->next = fresh;
    keepstudent(head);
}

void printstudent(Node* head)
{
    Node* move=head->next;
    while(move!=NULL)
    {
        printf("学号：%d,姓名:%s,成绩:%d\n",move->student.serial,move->student.name,move->student.score);
        move=move->next;
    }
    
}

void countstduent(Node* head)
{
    int count=0;
    Node* move=head->next;
    while(move!=NULL)
    {
    	count++;
    	move=move->next;
	}
	printf("学生总人数为%d\n",count);
}

void findstudent(Node* head)
{
	printf("请输入要查找学生的学号:");
	int stunum;
	scanf("%d",&stunum);
	Node* move=head->next;
	while(move!=NULL)
	{
		if(stunum==move->student.serial)
		{
			printf("学号：%d 姓名：%s 成绩：%d\n",move->student.serial,move->student.name,move->student.score);
			return;
		}
		move=move->next;
	 } 
	 printf("未找到学生信息");
}

void modistduent(Node* head)
{
	printf("请输入修改学生的学号:\n");
	int stunum;
	scanf("%d",&stunum);
	Node* move=head->next;
	while(move!=NULL)
	{
		if(move->student.serial==stunum)
		{
			printf("请输入修改后的学生姓名，成绩:\n");
			scanf("%s %d",move->student.name,&move->student.score);
			printf("学生信息修改成功\n");
			return; 
		}
		move=move->next;
	 } 
	 printf("未找到学生信息\n");
}

void delatestudent(Node* head)
{
	printf("输入要删除学生的学号:\n");
	int stunum;
	scanf("%d",&stunum);
	Node* move =head;
	while(move->next!=NULL)
	{
		if(move->next->student.serial==stunum)
		{
			Node* tmp=move->next;
			move->next=move->next->next;
			free(tmp);
			tmp=NULL;
			printf("删除成功\n");
			return;
		}
		move=move->next;
	}
	printf("未找到学生信息\n");
}

void sortstudent(Node* head)
{
	Node* turn;
	Node* move;
	for(turn=head->next;turn->next!=NULL;turn=turn->next)
	{
		for(move=head->next;move->next!=NULL;move=move->next)
		{
			if(move->student.serial>move->next->student.serial)
			{
				Student tmp=move->student;
				move->student=move->next->student;
				move->next->student=tmp;
			}
		}
	}
	printstudent(head);
}

void keepstudent(Node*head)
{
	FILE*file=fopen("./stu.info","w");
	if(file==NULL)
	{
		printf("打开文件失败\n");
		return;
	}
	struct node*move=head->next;
	while(move!=NULL)
	{
		if(fwrite(&move->Student,sizeof(Student),1,file!=1))
		{
			printf("保存出现错误\n");
		}
		move=move->next;
	}
	fclose(file);
}

void loadstudent(Node* head)
{
	FILE*file=fopen("./stu.info","r");
	if(!file)
	{
		printf("未找到学生信息，跳过读取\n");
		return;
	}
	Node*fresh=malloc(sizeof(Node));
	fresh->next=NULL;
	Node*move=head;
	while(fread(&fresh->stu,sizeof(Student),1,file)==1)
	{
		move->next=fresh;
		move=fresh;
		fresh=malloc(sizeof(Node));
		fresh->next=NULL;
	}
	free(fresh);
	fclose(file);
	printf("读取成功\n");
}
