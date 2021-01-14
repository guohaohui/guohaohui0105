#include <stdio.h>
#include <stdlib.h>
/*一辆卡车违反交通规则，撞人后逃跑。现场有三人目击事件，但都没有记住车号，只记下车号的一些特征
 甲说：牌照的前两位数字是相同的；乙说：牌照的后两位数字是相同的，但与前两位不同 ；
 丙是数学家，他说：四位的车号刚好是一个整数的平方。请根据以上线索找出车号。*/
int sign();
int main()
{
	sign();
	return 0;
}
int sign()
{
	int a, b, c, d, i;
	int num1, num2, num3, num4, num;
	for(i = 0 ;i < 100; i++)
	{
		for(a = 1; a < 10; a++)
		{
			for(b = 1; b < 10; b++)
			{
				for(c = 1; c < 10; c++)
				{
					for(d = 1; d < 10; d++)
					{
						if(a == b && c == d && a != c && b != d )
						{
							num1 = a * 1000;
							num2 = b * 100;
							num3 = c * 10;
							num4 = d;
							num = num1 + num2 + num3 + num4;
							if((i * i) == num)
							{
								printf(%d\n", num);
							}
						}
					}
				}
			}
		}
	}
}



