#include <stdio.h>

int main()
{
	int score, n;
	int i = 0;

	while(i < 10)
	{	
		printf("请输入第%d个成绩：", i+1);

		scanf("%d", &score);

		//	printf("%d\n", score++);

		if(score < 0 || score > 100)
		{
			printf("成绩无效！\n");
			continue;
		}
		/*
		   if(score >= 90 && score <= 100)
		   printf("A\n");
		   else if(score >= 80 && score < 90)
		   printf("B\n");
		   else if(score >= 70 && score < 80)
		   printf("C\n");
		   else if(score >= 60 && score < 70)
		   printf("D\n");
		   else if(score >= 0 && score < 60)
		   printf("E\n");
		   else
		   printf("没有这个成绩！\n");

		 */
		n = score / 10;

		switch(n)
		{
			case 10:
			case 9:
				printf("A\n");
				break;
			case 8:
				printf("B\n");
				break;
			case 7:
				printf("C\n");
				break;
			case 6:
				printf("D\n");
				break;
			default:
				printf("E\n");
				break;

		}
		i++;
	}

}


