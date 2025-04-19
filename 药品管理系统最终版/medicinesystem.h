#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USER_FILE "./users.txt"

/*�����û��ṹ��*/ 
struct user {
    char username[20];
    char password[20];
};

/*����һ���ṹ�崢����Ʒ��Ϣ*/ 
struct medicine
{
	char name[20];
	int price;
	int number;
};

struct node
{
	struct medicine mc;
	struct node*next;
};

/*ע���û��ĺ�������*/ 
void register_user();

/*��������ĺ�������*/
void encrypt_password(char*password);

/*��������ĺ�������*/ 
void decrypt_password(char*password);

/*��¼�û��ĺ�������*/ 
int login_user();

/*ɾ���û��ĺ�������*/ 
void delate_user();

/*�޸�����ĺ�������*/
void modisy_password(); 

/*��ӭ����ĺ�������*/ 
void welcome();

/*����ҩƷ��Ϣ�ĺ�������*/ 
void inputmedicine(struct node* head);

/*��ӡҩƷ��Ϣ����ĺ�������*/ 
void printmedicine(struct node*head);

/*����ҩƷ�������ĺ�������*/ 
void countmedicine(struct node*head);

/*Ѱ��ҩƷ��Ϣ�ĺ�������*/ 
void findmedicine(struct node*head);

/*�޸�ҩƷ��Ϣ�ĺ�������*/ 
void modisymedicine(struct node*head);

/*ɾ��ҩƷ��Ϣ�ĺ�������*/ 
void delatemedicine(struct node*head);

/*��ҩƷ����ĺ�������*/ 
void sortmedicine(struct node*head);

/*���ݲ���ĺ�������*/
void insertmedicine(struct node* head);

/*����ͳ�ƺ���*/
void statisticsmedicine(struct node* head);

/*����ҩƷ��Ϣ�ĺ�������*/ 
void keepmedicine(struct node*head);

/*��ȡ����ҩƷ��Ϣ���ļ��ĺ�������*/ 
void loadmedicine(struct node* head);

