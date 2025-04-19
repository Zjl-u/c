#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USER_FILE "./users.txt"

/*定义用户结构体*/ 
struct user {
    char username[20];
    char password[20];
};

/*建立一个结构体储存商品信息*/ 
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

/*注册用户的函数声明*/ 
void register_user();

/*加密密码的函数声明*/
void encrypt_password(char*password);

/*解密密码的函数声明*/ 
void decrypt_password(char*password);

/*登录用户的函数声明*/ 
int login_user();

/*删除用户的函数声明*/ 
void delate_user();

/*修改密码的函数声明*/
void modisy_password(); 

/*欢迎界面的函数声明*/ 
void welcome();

/*输入药品信息的函数声明*/ 
void inputmedicine(struct node* head);

/*打印药品信息报表的函数声明*/ 
void printmedicine(struct node*head);

/*计数药品的种数的函数声明*/ 
void countmedicine(struct node*head);

/*寻找药品信息的函数声明*/ 
void findmedicine(struct node*head);

/*修改药品信息的函数声明*/ 
void modisymedicine(struct node*head);

/*删除药品信息的函数声明*/ 
void delatemedicine(struct node*head);

/*给药品排序的函数声明*/ 
void sortmedicine(struct node*head);

/*数据插入的函数声明*/
void insertmedicine(struct node* head);

/*数据统计函数*/
void statisticsmedicine(struct node* head);

/*保存药品信息的函数声明*/ 
void keepmedicine(struct node*head);

/*读取保存药品信息的文件的函数声明*/ 
void loadmedicine(struct node* head);

