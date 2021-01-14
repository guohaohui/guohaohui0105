#include<stdio.h>
//要将5张100元的大钞票，换成等值的50元，20元，10元，5元一张的小钞票，每种面值至少1张，编程求需要多少张纸币。
int main()
{
    int rmb50, rmb20, rmb10, rmb5;
    int money = 500-35;
    int num = 0;
	int max = money / 50 +3, min = money / 5 + 3;
    for(rmb50 = 1; rmb50 <= money / 50; rmb50++)
        for(rmb20 = 1; rmb20 <= money / 20; rmb20++)
            for(rmb10 = 1; rmb10 <= money / 10; rmb10++)
                for(rmb5 = 1; rmb5 <= money / 5; rmb5++)
                    if(50 * rmb50 + 20 * rmb20 + 10 * rmb10 + 5 * rmb5 == 500)
                    {
                        num ++;
                        printf("%-3d%-3d%-3d%-3d%-3d\n",rmb50,rmb20,rmb10,rmb5,\
                        50 * rmb50 + 20 * rmb20 + 10 * rmb10 + 5 * rmb5);

						min = (min < (rmb50 + rmb20 + rmb10 + rmb5)) ? min : (rmb50 + rmb20 + rmb10 + rmb5);
						max = (max > (rmb50 + rmb20 + rmb10 + rmb5)) ? max : (rmb50 + rmb20 + rmb10 + rmb5);
                    }

    printf("一共%d种换法\n",num);
	printf("min = %d\nmax = %d\n", min, max);
    return 0;

}


