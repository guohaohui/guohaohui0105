
# 变量
LDFLAGS=-lmylist
LDPATH=-L/home/xiaohao/guohaohui/guohaohui0105/ds/doubleforlist/4
CFLAGS+=-I/home/xiaohao/guohaohui/guohaohui0105/ds/doubleforlist/4
#LDFLAGS 库名
#LDPATH 库路径
#CFLAGS 头文件路径
# 目标:依赖
lstack:main.o lstack.o
	gcc -o $@ $^ $(LDFLAGS) $(LDPATH)
#gcc -o lstack main.o lstack.o $(LDFLAGS) $(LDPATH)
# $@ 取目标文件 $^ 取所有依赖文件
# 规则

main.o:main.c
	gcc -c -o $@ $^ $(CFLAGS)
#gcc -c -o main.o main.c $(CFLAGS)

lstack.o:lstack.c
	gcc -c -o $@ $^ $(LDFLAGS) $(LDPATH) $(CFLAGS)
#gcc -c -o lstack.o lstack.c $(LDFLAGS) $(LDPATH) $(CFLAGS)

# 伪目标
clean:
	rm *.o

