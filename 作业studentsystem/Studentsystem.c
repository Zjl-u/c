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
			printf("�ټ�����ӭ�´�ʹ��\n");
			return;
	    default:break;
	    }
	}
    return 0;
}
void welcome()
{
    printf("*************************\n");
    printf("*   ѧ���ɼ�����ϵͳ\t*\n");
    printf("*************************\n");
    printf("*   1¼��ѧ����Ϣ\t*\n");
    printf("*   2��ӡѧ����Ϣ\t*\n");
    printf("*   3ͳ��ѧ����Ϣ\t*\n");
    printf("*   4����ѧ����Ϣ\t*\n");
    printf("*   5�޸�ѧ����Ϣ\t*\n");
    printf("*   6ɾ��ѧ����Ϣ\t*\n");
    printf("*   7���������\t\t*\n");
    printf("*   8�˳�ϵͳ\t\t*\n");
    printf("*************************\n");
    printf("*   ����������ѡ��\t*\n");
    printf("*************************\n");
}

void inputstduent(Node* head)
{
    Node* fresh = malloc(sizeof(Node));
    fresh->next = NULL;
    printf("������ѧ������ţ��������ɼ�:");
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
        printf("ѧ�ţ�%d,����:%s,�ɼ�:%d\n",move->student.serial,move->student.name,move->student.score);
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
	printf("ѧ��������Ϊ%d\n",count);
}

void findstudent(Node* head)
{
	printf("������Ҫ����ѧ����ѧ��:");
	int stunum;
	scanf("%d",&stunum);
	Node* move=head->next;
	while(move!=NULL)
	{
		if(stunum==move->student.serial)
		{
			printf("ѧ�ţ�%d ������%s �ɼ���%d\n",move->student.serial,move->student.name,move->student.score);
			return;
		}
		move=move->next;
	 } 
	 printf("δ�ҵ�ѧ����Ϣ");
}

void modistduent(Node* head)
{
	printf("�������޸�ѧ����ѧ��:\n");
	int stunum;
	scanf("%d",&stunum);
	Node* move=head->next;
	while(move!=NULL)
	{
		if(move->student.serial==stunum)
		{
			printf("�������޸ĺ��ѧ���������ɼ�:\n");
			scanf("%s %d",move->student.name,&move->student.score);
			printf("ѧ����Ϣ�޸ĳɹ�\n");
			return; 
		}
		move=move->next;
	 } 
	 printf("δ�ҵ�ѧ����Ϣ\n");
}

void delatestudent(Node* head)
{
	printf("����Ҫɾ��ѧ����ѧ��:\n");
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
			printf("ɾ���ɹ�\n");
			return;
		}
		move=move->next;
	}
	printf("δ�ҵ�ѧ����Ϣ\n");
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
		printf("���ļ�ʧ��\n");
		return;
	}
	struct node*move=head->next;
	while(move!=NULL)
	{
		if(fwrite(&move->Student,sizeof(Student),1,file!=1))
		{
			printf("������ִ���\n");
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
		printf("δ�ҵ�ѧ����Ϣ��������ȡ\n");
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
	printf("��ȡ�ɹ�\n");
}
