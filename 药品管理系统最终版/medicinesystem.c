#include "medicinesystem.h"

int main()
{
    int logged_in = 0;
    while (!logged_in)
    {
        printf("*************************\n"); /*用户界面*/
        printf("*\t用户界面\t*\n");
        printf("*************************\n");
        printf("*      1.注册用户\t*\n");
        printf("*      2.登录账号\t*\n");
        printf("*      3.删除用户\t*\n");
        printf("*      4.修改密码\t*\n");
        printf("*      5.退出系统\t*\n");
        printf("*************************\n");
        printf("*    请输入您的选择     *\n");
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
                printf("登录失败，请重试。\n");
            }
            break;
        case 3:
            delate_user();
            break;
        case 4:
            modisy_password();
            break;
        case 5:
            printf("欢迎下次使用~");
            return;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }
    struct node *head = malloc(sizeof(struct node));
    head->next = NULL;
    loadmedicine(head); /*读取储存药品信息的文件*/
    while (1)
    {
        welcome(); /*功能界面*/
        int num;
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            inputmedicine(head);
            break; /*输入药品信息*/
        case 2:
            printmedicine(head);
            break; /*打印药品信息报表*/
        case 3:
            findmedicine(head);
            break; /*查询对应药品信息*/
        case 4:
            modisymedicine(head);
            break; /*修改药品信息*/
        case 5:
            delatemedicine(head);
            break; /*删除药品信息*/
        case 6:
            sortmedicine(head);
            break; /*给药品排序*/
        case 7:
            insertmedicine(head);
            break; /*在随意位置插入药品信息*/
        case 8:
            countmedicine(head);
            break; /*简单统计药品数量*/
        case 9:
            statisticsmedicine(head);
            break; /*药品数据综合统计*/
        case 10:
            printf("欢迎下次使用~\n");
            return;
        default:
            printf("请重新输入数字\n");
            break;
        }
    }
    return 0;
}

/*注册用户*/
void register_user()
{
    struct user new_user;
    printf("请输入用户名: ");
    scanf("%s", new_user.username);
    printf("请输入密码: ");
    scanf("%s", new_user.password);
    encrypt_password(new_user.password); /*加密密码*/
    FILE *file = fopen("./users.txt", "a");
    if (file == NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    fprintf(file, "%s %s\n", new_user.username, new_user.password);
    fclose(file);
    printf("注册成功！\n");
    system("pause"); /*暂停程序运行*/
    system("cls");   /*清屏，防止界面太乱*/
}

/*加密密码*/
void encrypt_password(char *password)
{
    while (*password)
    {
        *password = *password + 3;
        password++;
    }
}

/*解密密码*/
void decrypt_password(char *password)
{
    while (*password)
    {
        *password = *password - 3;
        password++;
    }
}

/*登录用户*/
int login_user()
{
    char username[20];
    char password[20];
    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);
    system("pause"); /*暂停程序运行*/
    system("cls");   /*清屏，防止界面太乱*/

    FILE *file = fopen("./users.txt", "r");
    if (file == NULL)
    {
        printf("未找到用户文件\n");
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

/*删除用户*/
void delate_user()
{
    char username[30], password[30];
    int found = 0;

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    FILE *file = fopen(USER_FILE, "r");
    if (!file)
    {
        printf("用户文件不存在！\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file)
    {
        printf("无法创建临时文件！\n");
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
            printf("用户 %s 已被删除。\n", username);
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
        printf("用户名或密码错误，无法删除用户！\n");
    }
    system("pause");
    system("cls");
}

/*修改密码*/
void modisy_password()
{
    char username[30], old_password[30], new_password[30];
    int found = 0;

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入旧密码: ");
    scanf("%s", old_password);

    FILE *file = fopen(USER_FILE, "r");
    if (!file)
    {
        printf("用户文件不存在！\n");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file)
    {
        printf("无法创建临时文件！\n");
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
            printf("请输入新密码: ");
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
        printf("密码修改成功！\n");
    }
    else
    {
        printf("用户名或密码错误，无法修改密码！\n");
    }
    system("pause");
    system("cls");
}

/*功能界面*/
void welcome()
{
    printf("*************************\n");
    printf("*   药店药品管理系统\t*\n");
    printf("*************************\n");
    printf("*   1输入药品信息\t*\n");
    printf("*   2打印药品信息报表\t*\n");
    printf("*   3查找对应药品\t*\n");
    printf("*   4修改药品信息\t*\n");
    printf("*   5删除药品信息\t*\n");
    printf("*   6给药品排序\t\t*\n");
    printf("*   7药品数据插入\t*\n");
    printf("*   8简单统计药品数量\t*\n");
    printf("*   9药品数据综合统计\t*\n");
    printf("*   10关闭程序\t\t*\n");
    printf("*************************\n");
    printf("*   请输入您的选择\t*\n");
    printf("*************************\n");
}

/*输入药品信息*/
void inputmedicine(struct node *head)
{
    struct node *fresh = malloc(sizeof(struct node));
    fresh->next = NULL;
    printf("请输入药品的名称，价格（元）,数量（盒）：\n");
    scanf("%s %d %d", fresh->mc.name, &fresh->mc.price, &fresh->mc.number);
    struct node *move = head;
    while (move->next != NULL)
    {
        move = move->next;
    }
    move->next = fresh;
    keepmedicine(head); /*保存药品信息*/
    system("pause");    /*暂停代码运行*/
    system("cls");      /*清空运行界面，防止内容太过杂乱*/
}

/*打印药品信息报表*/
void printmedicine(struct node *head)
{
    struct node *move = head->next;
    while (move != NULL)
    {
        printf("名称：%s\t\t价格(元)：%d\t数量（盒）：%d\n", move->mc.name, move->mc.price, move->mc.number);
        move = move->next;
    }
    system("pause"); /*暂停代码运行*/
    system("cls");   /*清空运行界面，防止内容太过杂乱*/
}

/*简单统计药品数量*/
void countmedicine(struct node *head)
{
    int num = 0; /*计数药品种数*/
    struct node *move = head->next;
    while (move != NULL)
    {
        num++;
        move = move->next;
    }
    printf("药品共有%d种\n", num);
    system("pause"); /*暂停代码运行*/
    system("cls");   /*清空运行界面，防止内容太过杂乱*/
}

/*查询药品信息*/
void findmedicine(struct node *head)
{
    printf("输入1按名称查询\n输入2按数量查询\n输入3按名称数量组合查询\n输入4按名称价格组合查询\n");
    int b;
    scanf("%d", &b);
    struct node *move = head->next;
    int num;
    int pc;
    char name[20];
    switch (b)
    {
    case 1:
        printf("请输入所找药品的名称\n"); /*通过名字查找药品信息*/
        scanf("%s", name);
        while (move != NULL)
        {
            if (strcmp(name, move->mc.name) == 0)
            {
                printf("价格(元)：%d,数量(盒)：%d\n", move->mc.price, move->mc.number);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("未找到该药品\n");
        system("pause"); /*暂停代码运行*/
        system("cls");   /*清空运行界面，防止内容太过杂乱*/
        break;
    case 2:
        printf("请输入所找药品的数量(盒)\n"); /*通过数量查找药品信息*/
        scanf("%d", &num);
        while (move != NULL)
        {
            if (num == move->mc.number)
            {
                printf("名称：%s,价格(元)：%d\n", move->mc.name, move->mc.price);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("未找到该药品\n");
        system("pause"); /*暂停代码运行*/
        system("cls");   /*清空运行界面，防止内容太过杂乱*/
        break;
    case 3:
        printf("请输入所找药品的名称和数量(盒)\n"); /*通过名称和数量组合查找药品信息*/
        scanf("%s %d", name, &num);
        while (move != NULL)
        {
            if (num == move->mc.number && strcmp(name, move->mc.name) == 0)
            {
                printf("价格(元)：%d\n", move->mc.price);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("未找到该药品\n");
        system("pause"); /*暂停代码运行*/
        system("cls");   /*清空运行界面，防止内容太过杂乱*/
        break;
    case 4:
        printf("请输入所找药品的名称和价格(元)\n"); /*通过名称和价格组合查找药品信息*/
        scanf("%s %d", name, &pc);
        while (move != NULL)
        {
            if (pc == move->mc.price && strcmp(name, move->mc.name) == 0)
            {
                printf("数量(盒)：%d\n", move->mc.number);
                system("pause");
                system("cls");
                return;
            }
            move = move->next;
        }
        printf("未找到该药品\n");
        system("pause"); /*暂停代码运行*/
        system("cls");   /*清空运行界面，防止内容太过杂乱*/
        break;
    default:
        printf("无效输入");
        return;
    }
}

/*修改药品信息*/
void modisymedicine(struct node *head)
{
    printf("请输入要修改药品的名称\n");
    char name[20];
    scanf("%s", name);
    struct node *move = head->next;
    while (move != NULL)
    {
        if (strcmp(name, move->mc.name) == 0)
        {
            printf("请输入药品名称、价格和数量：");
            scanf("%s %d %d", move->mc.name, &move->mc.price, &move->mc.number);
            keepmedicine(head);
            system("pause"); /*暂停代码运行*/
            system("cls");   /*清空运行界面，防止内容太过杂乱*/
            return;
        }
        move = move->next;
    }
    printf("未找到药品信息\n");
    system("pause"); /*暂停代码运行*/
    system("cls");   /*清空运行界面，防止内容太过杂乱*/
}

/*删除药品信息*/
void delatemedicine(struct node *head)
{
    printf("请输入要删除药品的名称\n");
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
            printf("删除成功\n");
            system("pause"); /*暂停代码运行*/
            system("cls");   /*清空运行界面，防止内容太过杂乱*/
            return;
        }
        move = move->next;
    }
    printf("未找到该药品\n");
    system("pause"); /*暂停代码运行*/
    system("cls");   /*清空运行界面，防止内容太过杂乱*/
}

/*给药品排序*/
void sortmedicine(struct node *head)
{
    printf("输入1按价格排序，输入2按数量排序\n"); /*价格由低到高，数量由大到小*/
    int b;
    scanf("%d", &b);
    struct node *turn;
    struct node *move;
    switch (b)
    {
    case 1:
        for (turn = head->next; turn->next != NULL; turn = turn->next) /*给药品按价格排序*/
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
        for (turn = head->next; turn->next != NULL; turn = turn->next) /*给药品按数量排序*/
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
        printf("无效输入");
        break;
    }
}

/*在随意位置插入药品信息*/
void insertmedicine(struct node *head)
{
    int position;
    struct node *fresh = malloc(sizeof(struct node));
    struct node *move = head;
    int i;
    printf("请输入要插入的位置（从1开始计数）: ");
    scanf("%d", &position);
    printf("请输入药品的名称，价格（元）,数量（盒）：\n");
    scanf("%s %d %d", fresh->mc.name, &fresh->mc.price, &fresh->mc.number);
    for (i = 1; i < position - 1 && move->next != NULL; i++)
    {
        move = move->next;
    }
    if (i != position - 1 || move->next == NULL && i < position - 1) /*如果位置超出链表长度，将新节点插入到链表末尾*/
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
    printf("插入成功\n");
    system("pause");
    system("cls");
}

/* 综合数据统计函数 */
void statisticsmedicine(struct node *head)
{
    struct node *move = head->next;
    int totalNumber = 0; /*用于统计药品总数量*/
    int totalPrice = 0;  /*用于统计药品总价格*/
    while (move != NULL)
    {
        totalNumber += move->mc.number;
        totalPrice += move->mc.price * move->mc.number;
        move = move->next;
    }
    printf("药品总数量: %d 盒\n", totalNumber);
    printf("药品总价格: %d 元\n", totalPrice);
    system("pause");
    system("cls");
}

/*保存药品信息*/
void keepmedicine(struct node *head)
{
    FILE *file = fopen("./gs.txt", "w");
    if (file == NULL)
    {
        printf("打开文件失败\n");
        return;
    }
    struct node *move = head->next;
    while (move != NULL)
    {
        // 以文本格式写入药品信息
        fprintf(file, "%s %d %d\n", move->mc.name, move->mc.price, move->mc.number);
        move = move->next;
    }
    fclose(file); /*关闭文件*/
}

/*读取储存药品信息的文件*/
void loadmedicine(struct node *head)
{
    FILE *file = fopen("./gs.txt", "r"); /*打开相应文件*/
    if (!file)
    {
        printf("没有药品文件,无法读取\n");
        return;
    }
    struct node *move = head;
    struct medicine temp;
    // 以文本格式读取药品信息
    while (fprintf(file, "%s %d %d", temp.name, &temp.price, &temp.number) != EOF)
    {
        struct node *fresh = malloc(sizeof(struct node));
        fresh->mc = temp;
        fresh->next = NULL;
        move->next = fresh;
        move = fresh;
    }
    fclose(file);
    printf("读取成功\n");
}
