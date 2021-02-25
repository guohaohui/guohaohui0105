#include <stdio.h>
#include <string.h>

#define NAMESIZE 32

struct stu_st
{
    int age;
    char name[NAMESIZE];
    float score;
};

int main()
{
    struct stu_st stu;
    struct stu_st stu2 = {20,  "guohaohui", 99.9};
    struct stu_st stu3[3];
    struct stu_st *p;

    p = stu3;

    for(int i = 0; i < 3; i++)
    {
        stu3[i].age = i + 20;
        //strcpy(stu3[i].name, "guo");
        snprintf(stu3[i].name, NAMESIZE, "hello%d", i+1);
        stu3[i].score = i + 66.6;
    }
    for(int i = 0; i < 3; i++)
    {
        //printf("%d %s %4f\n",stu3[i].age, stu3[i].name, stu3[i].score);
        printf("%d %s %f\n", (p+i)->age, (p+i)->name, (p+i)->score);
    }
    printf("\n");
/*
    for(int i = 0; i < 3; i++)
    {
        scanf("%d%s%f", &stu3[i].age, stu3[i].name, &stu3[i].score);
    }
    printf("\n");
    for(int i = 0; i < 3; i++)
    {
        printf("%d %s %4f\n",stu3[i].age, stu3[i].name, stu3[i].score);
    }

    printf("\n");

    printf("%d %s %f\n", stu2.age, stu2.name, stu2.score);
   
    printf("\n");
    stu.age = 21;
    strcpy(stu.name, "guohaomeng");
    stu.score = 100;

    printf("%d %s %f\n", stu.age, stu.name, stu.score);
*/
    return 0;
}