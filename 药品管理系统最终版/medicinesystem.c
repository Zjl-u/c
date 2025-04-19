#include "medicinesystem.h"

int main()
{
    int logged_in = 0;
    while (!logged_in)
    {
        printf("*************************\n"); /*�û�����*/
        printf("*\t�û�����\t*\n");
        printf("*************************\n");
        printf("*      1.ע���û�\t*\n");
        printf("*      2.��¼�˺�\t*\n");
        printf("*      3.ɾ���û�\t*\n");
        printf("*      4.�޸�����\t*\n");
        printf("*      5.�˳�ϵͳ\t*\n");
        printf("*************************\n");
        printf("*    ����������ѡ��     *\n");
        printf("*************************\n");

        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            register_user();
            break;
        case 2:
            logged_in = login_user();
            if (!logged_in)
            {
                printf("��¼ʧ�ܣ������ԡ�\n");
            }
            break;
        case 3:
            delate_user();
            break;
        case 4:
            modisy_password();
            break;
        case 5:
            printf("��ӭ�´�ʹ��~");
            return;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }
    }
    struct node *head = malloc(sizeof(struct node));
    head->next = NULL;
    loadmedicine(head); /*��ȡ����ҩƷ��Ϣ���ļ�*/
    while (1)
    {
        welcome(); /*���ܽ���*/
        int num;
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            inputmedicine(head);
            break; /*����ҩƷ��Ϣ*/
        case 2:
            printmedicine(head);
            break; /*��ӡҩƷ��Ϣ����*/
        case 3:
            findmedicine(head);
            break; /*��ѯ��ӦҩƷ��Ϣ*/
        case 4:
            modisymedicine(head);
            break; /*�޸�ҩƷ��Ϣ*/
        case 5:
            delatemedicine(head);
            break; /*ɾ��ҩƷ��Ϣ*/
        case 6:
            sortmedicine(head);
            break; /*��ҩƷ����*/
        case 7:
            insertmedicine(head);
            break; /*������λ�ò���ҩƷ��Ϣ*/
        case 8:
            countmedicine(head);
            break; /*��ͳ��ҩƷ����*/
        case 9:
            statisticsmedicine(head);
            break; /*ҩƷ�����ۺ�ͳ��*/
        case 10:
            printf("��ӭ�´�ʹ��~\n");
            return;
        default:
            printf("��������������\n");
            break;
        }
    }
    return 0;
}

/*ע���û�*/
void register_user()
{
    struct user new_user;
    printf("�������û���: ");
    scanf("%s", new_user.username);
    printf("����������: ");
    scanf("%s", new_user.password);
    encrypt_password(new_user.password); /*��������*/
    FILE *file = fopen("./users.txt", "a");
    if (file == NULL)
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    fprintf(file, "%s %s\n", new_user.username, new_user.password);
    fclose(file);
    printf("ע��ɹ���\n");
    system("pause"); /*��ͣ��������*/
    system("cls");   /*��������ֹ����̫��*/
}

/*��������*/
void encrypt_password(char *password)
{
    while (*password)
    {
        *password = *password + 3;
        password++;
    }
}

/*��������*/
void decrypt_password(char *password)
{
    while (*password)
    {
        *password = *password - 3;
        password++;
    }
}

/*��¼�û�*/
int login_user()
{
    char username[20];
    char password[20];
    printf("�������û���: ");
    scanf("%s", username);
    printf("����������: ");
    scanf("%s", password);
    system("pause"); /*��ͣ��������*/
    system("cls");   /*��������ֹ����̫��*/

    FILE *file = fopen("./users.txt", "r");
    if (file == NULL)
    {
        printf("δ�ҵ��û��ļ�\n");
        return 0;
    }

    struct user temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) == 2)
    {
        decrypt_password(temp.password);
        if (strcmp(username, temp.username) == 0 && strcmp(password, temp.password) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

/*ɾ���û�*/
void delate_user()
{
    char username[30], password[30];
    int found = 0;

    printf("�������û���: ");
    scanf("%s", username);
    printf("����������: ");
    scanf("%s", password);

    FILE *file = fopen(USER_FILE, "r");
    if (!file)
    {
        printf("�û��ļ������ڣ�\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file)
    {
        printf("�޷�������ʱ�ļ���\n");
        fclose(file);
        return;
    }

    struct user temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) == 2)
    {
        decrypt_password(temp.password);

        if (strcmp(username, temp.username) == 0 && strcmp(password, temp.password) == 0)
        {
            found = 1;
            printf("�û� %s �ѱ�ɾ����\n", username);
        }
        else
        {
            encrypt_password(temp.password);
            fprintf(temp_file, "%s %s\n", temp.username, temp.password);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(USER_FILE);
    rename("temp.txt", USER_FILE);

    if (!found)
    {
        printf("�û�������������޷�ɾ���û���\n");
    }
    system("pause");
    system("cls");
}

/*�޸�����*/
void modisy_password()
{
    char username[30], old_password[30], new_password[30];
    int found = 0;

    printf("�������û���: ");
    scanf("%s", username);
    printf("�����������: ");
    scanf("%s", old_password);

    FILE *file = fopen(USER_FILE, "r");
    if (!file)
    {
        printf("�û��ļ������ڣ�\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file)
    {
        printf("�޷�������ʱ�ļ���\n");
        fclose(file);
        return;
    }

    struct user temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) == 2)
    {
        decrypt_password(temp.password);

        if (strcmp(username, temp.username) == 0 && strcmp(old_password, temp.password) == 0)
        {
            found = 1;
            printf("������������: ");
            scanf("%s", new_password);
            strcpy(temp.password, new_password);
            encrypt_password(temp.password);
            fprintf(temp_file, "%s %s\n", temp.username, temp.password);
        }
        else
        {
            encrypt_password(temp.password);
            fprintf(temp_file, "%s %s\n", temp.username, temp.password);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(USER_FILE);
    rename("temp.txt", USER_FILE);

    if (found)
    {
        printf("�����޸ĳɹ���\n");
    }
    else
    {
        printf("�û�������������޷��޸����룡\n");
    }
    system("pause");
    system("cls");
}

/*���ܽ���*/
void welcome()
{
    printf("*************************\n");
    printf("*   ҩ��ҩƷ����ϵͳ\t*\n");
    printf("*************************\n");
    printf("*   1����ҩƷ��Ϣ\t*\n");
    printf("*   2��ӡҩƷ��Ϣ����\t*\n");
    printf("*   3���Ҷ�ӦҩƷ\t*\n");
    printf("*   4�޸�ҩƷ��Ϣ\t*\n");
    printf("*   5ɾ��ҩƷ��Ϣ\t*\n");
    printf("*   6��ҩƷ����\t\t*\n");
    printf("*   7ҩƷ���ݲ���\t*\n");
    printf("*   8��ͳ��ҩƷ����\t*\n");
    printf("*   9ҩƷ�����ۺ�ͳ��\t*\n");
    printf("*   10�رճ���\t\t*\n");
    printf("*************************\n");
    printf("*   ����������ѡ��\t*\n");
    printf("*************************\n");
}

/*����ҩƷ��Ϣ*/
void inputmedicine(struct node *head)
{
    struct node *fresh = malloc(sizeof(struct node));
    fresh->next = NULL;
    printf("������ҩƷ�����ƣ��۸�Ԫ��,�������У���\n");
    scanf("%s %d %d", fresh->mc.name, &fresh->mc.price, &fresh->mc.number);
    struct node *move = head;
    while (move->next != NULL)
    {
        move = move->next;
    }
    move->next = fresh;
    keepmedicine(head); /*����ҩƷ��Ϣ*/
    system("pause");    /*��ͣ��������*/
    system("cls");      /*������н��棬��ֹ����̫������*/
}

/*��ӡҩƷ��Ϣ����*/
void printmedicine(struct node *head)
{
    struct node *move = head->next;
    while (move != NULL)
    {
        printf("���ƣ�%s\t\t�۸�(Ԫ)��%d\t�������У���%d\n", move->mc.name, move->mc.price, move->mc.number);
        move = move->next;
    }
    system("pause"); /*��ͣ��������*/
    system("cls");   /*������н��棬��ֹ����̫������*/
}

/*��ͳ��ҩƷ����*/
void countmedicine(struct node *head)
{
    int num = 0; /*����ҩƷ����*/
    struct node *move = head->next;
    while (move != NULL)
    {
        num++;
        move = move->next;
    }
    printf("ҩƷ����%d��\n", num);
    system("pause"); /*��ͣ��������*/
    system("cls");   /*������н��棬��ֹ����̫������*/
}

/*��ѯҩƷ��Ϣ*/
void findmedicine(struct node *head)
{
    printf("����1�����Ʋ�ѯ\n����2��������ѯ\n����3������������ϲ�ѯ\n����4�����Ƽ۸���ϲ�ѯ\n");
    int b;
    scanf("%d", &b);
    struct node *move = head->next;
    int num;
    int pc;
    char name[20];
    switch (b)
    {
    case 1:
        printf("����������ҩƷ������\n"); /*ͨ�����ֲ���ҩƷ��Ϣ*/
        scanf("%s", name);
        while (move != NULL)
        {
            if (strcmp(name, move->mc.name) == 0)
            {
                printf("�۸�(Ԫ)��%d,����(��)��%d\n", move->mc.price, move->mc.number);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("δ�ҵ���ҩƷ\n");
        system("pause"); /*��ͣ��������*/
        system("cls");   /*������н��棬��ֹ����̫������*/
        break;
    case 2:
        printf("����������ҩƷ������(��)\n"); /*ͨ����������ҩƷ��Ϣ*/
        scanf("%d", &num);
        while (move != NULL)
        {
            if (num == move->mc.number)
            {
                printf("���ƣ�%s,�۸�(Ԫ)��%d\n", move->mc.name, move->mc.price);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("δ�ҵ���ҩƷ\n");
        system("pause"); /*��ͣ��������*/
        system("cls");   /*������н��棬��ֹ����̫������*/
        break;
    case 3:
        printf("����������ҩƷ�����ƺ�����(��)\n"); /*ͨ�����ƺ�������ϲ���ҩƷ��Ϣ*/
        scanf("%s %d", name, &num);
        while (move != NULL)
        {
            if (num == move->mc.number && strcmp(name, move->mc.name) == 0)
            {
                printf("�۸�(Ԫ)��%d\n", move->mc.price);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("δ�ҵ���ҩƷ\n");
        system("pause"); /*��ͣ��������*/
        system("cls");   /*������н��棬��ֹ����̫������*/
        break;
    case 4:
        printf("����������ҩƷ�����ƺͼ۸�(Ԫ)\n"); /*ͨ�����ƺͼ۸���ϲ���ҩƷ��Ϣ*/
        scanf("%s %d", name, &pc);
        while (move != NULL)
        {
            if (pc == move->mc.price && strcmp(name, move->mc.name) == 0)
            {
                printf("����(��)��%d\n", move->mc.number);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("δ�ҵ���ҩƷ\n");
        system("pause"); /*��ͣ��������*/
        system("cls");   /*������н��棬��ֹ����̫������*/
        break;
    default:
        printf("��Ч����");
        return;
    }
}

/*�޸�ҩƷ��Ϣ*/
void modisymedicine(struct node *head)
{
    printf("������Ҫ�޸�ҩƷ������\n");
    char name[20];
    scanf("%s", name);
    struct node *move = head->next;
    while (move != NULL)
    {
        if (strcmp(name, move->mc.name) == 0)
        {
            printf("������ҩƷ���ơ��۸��������");
            scanf("%s %d %d", move->mc.name, &move->mc.price, &move->mc.number);
            keepmedicine(head);
            system("pause"); /*��ͣ��������*/
            system("cls");   /*������н��棬��ֹ����̫������*/
            return;
        }
        move = move->next;
    }
    printf("δ�ҵ�ҩƷ��Ϣ\n");
    system("pause"); /*��ͣ��������*/
    system("cls");   /*������н��棬��ֹ����̫������*/
}

/*ɾ��ҩƷ��Ϣ*/
void delatemedicine(struct node *head)
{
    printf("������Ҫɾ��ҩƷ������\n");
    char name[20];
    scanf("%s", name);
    struct node *move = head;
    while (move->next != NULL)
    {
        if (strcmp(name, move->next->mc.name) == 0)
        {
            struct node *tmp = move->next;
            move->next = move->next->next;
            free(tmp);
            tmp = NULL;
            keepmedicine(head);
            printf("ɾ���ɹ�\n");
            system("pause"); /*��ͣ��������*/
            system("cls");   /*������н��棬��ֹ����̫������*/
            return;
        }
        move = move->next;
    }
    printf("δ�ҵ���ҩƷ\n");
    system("pause"); /*��ͣ��������*/
    system("cls");   /*������н��棬��ֹ����̫������*/
}

/*��ҩƷ����*/
void sortmedicine(struct node *head)
{
    printf("����1���۸���������2����������\n"); /*�۸��ɵ͵��ߣ������ɴ�С*/
    int b;
    scanf("%d", &b);
    struct node *turn;
    struct node *move;
    switch (b)
    {
    case 1:
        for (turn = head->next; turn->next != NULL; turn = turn->next) /*��ҩƷ���۸�����*/
        {
            for (move = head->next; move->next != NULL; move = move->next)
            {
                if (move->mc.price > move->next->mc.price)
                {
                    struct medicine tmp = move->mc;
                    move->mc = move->next->mc;
                    move->next->mc = tmp;
                }
            }
        }
        printmedicine(head);
        keepmedicine(head);
        break;
    case 2:
        for (turn = head->next; turn->next != NULL; turn = turn->next) /*��ҩƷ����������*/
        {
            for (move = head->next; move->next != NULL; move = move->next)
            {
                if (move->mc.number < move->next->mc.number)
                {
                    struct medicine tmp = move->mc;
                    move->mc = move->next->mc;
                    move->next->mc = tmp;
                }
            }
        }
        printmedicine(head);
        keepmedicine(head);
        break;
    default:
        printf("��Ч����");
        break;
    }
}

/*������λ�ò���ҩƷ��Ϣ*/
void insertmedicine(struct node *head)
{
    int position;
    struct node *fresh = malloc(sizeof(struct node));
    struct node *move = head;
    int i;
    printf("������Ҫ�����λ�ã���1��ʼ������: ");
    scanf("%d", &position);
    printf("������ҩƷ�����ƣ��۸�Ԫ��,�������У���\n");
    scanf("%s %d %d", fresh->mc.name, &fresh->mc.price, &fresh->mc.number);
    for (i = 1; i < position - 1 && move->next != NULL; i++)
    {
        move = move->next;
    }
    if (i != position - 1 || move->next == NULL && i < position - 1) /*���λ�ó��������ȣ����½ڵ���뵽����ĩβ*/
    {
        move->next = fresh;
        fresh->next = NULL;
    }
    else
    {
        fresh->next = move->next;
        move->next = fresh;
    }
    keepmedicine(head);
    printf("����ɹ�\n");
    system("pause");
    system("cls");
}

/* �ۺ�����ͳ�ƺ��� */
void statisticsmedicine(struct node *head)
{
    struct node *move = head->next;
    int totalNumber = 0; /*����ͳ��ҩƷ������*/
    int totalPrice = 0;  /*����ͳ��ҩƷ�ܼ۸�*/
    while (move != NULL)
    {
        totalNumber += move->mc.number;
        totalPrice += move->mc.price * move->mc.number;
        move = move->next;
    }
    printf("ҩƷ������: %d ��\n", totalNumber);
    printf("ҩƷ�ܼ۸�: %d Ԫ\n", totalPrice);
    system("pause");
    system("cls");
}

/*����ҩƷ��Ϣ*/
void keepmedicine(struct node *head)
{
    FILE *file = fopen("./gs.txt", "w");
    if (file == NULL)
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    struct node *move = head->next;
    while (move != NULL)
    {
        // ���ı���ʽд��ҩƷ��Ϣ
        fprintf(file, "%s %d %d\n", move->mc.name, move->mc.price, move->mc.number);
        move = move->next;
    }
    fclose(file); /*�ر��ļ�*/
}

/*��ȡ����ҩƷ��Ϣ���ļ�*/
void loadmedicine(struct node *head)
{
    FILE *file = fopen("./gs.txt", "r"); /*����Ӧ�ļ�*/
    if (!file)
    {
        printf("û��ҩƷ�ļ�,�޷���ȡ\n");
        return;
    }
    struct node *move = head;
    struct medicine temp;
    // ���ı���ʽ��ȡҩƷ��Ϣ
    while (fprintf(file, "%s %d %d", temp.name, &temp.price, &temp.number) != EOF)
    {
        struct node *fresh = malloc(sizeof(struct node));
        fresh->mc = temp;
        fresh->next = NULL;
        move->next = fresh;
        move = fresh;
    }
    fclose(file);
    printf("��ȡ�ɹ�\n");
}
