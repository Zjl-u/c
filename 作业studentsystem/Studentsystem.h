#include <stdio.h>
#include<stdlib.h>

typedef struct _Student
{
    int serial;
    char name[20];
    int score;
} Student;

typedef struct _Node
{
    Student student;
    struct _Node* next;
} Node;

void welcome();

void inputstduent(Node* head);

void printstudent(Node* head);

void countstduent(Node* head);

void findstudent(Node* head);

void modistduent(Node* head);

void delatestudent(Node* head);

void sortstudent(Node* head);

void freeList(Node* head);

void keepstudent(Node* head);

void loadstudent(Node* head);
