#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int ch;

	while (1) {
		ch = getopt(argc, argv, "-lahi:m::");
		if (-1 == ch)
			break;
		switch (ch) {
			case 'l':
				printf("get -l...\n");
				break;
			case 'a':
				printf("get -a...\n");
				break;
			case 'h':
				printf("get -h...\n");
				break;
			case 'i':
				printf("get -i...\n");
				if (optarg != NULL) {
					printf("arg:%s\n", optarg);	
				} else
					fprintf(stderr, "required arguments\n");
				break;
			case 'm':
				printf("get -m...\n");
				if (optarg != NULL)
					printf("arg:%s\n", optarg);
				break;
			case 1:
				printf("not option argument...\n");
				break;
			case '?':
				printf("i don't know\n");
				break;
			default:
				break;
		}
	}

	return 0;
}



#if 0
int main(int argc, char *argv[])
{
	int ch;

	while(1)
	{
		ch = getopt(argc, argv, "-ali:m::");
		if(ch == -1)
			break;
		switch(ch)
		{
			case 'a':
				printf("a...\n");
				break;
			case 'l':
				printf("l...\n");
				break;
			case 'i':
				printf("i...\n");
				if(optarg != NULL)
				{
					printf("%s\n", optarg);
				}
				else
				{
					fprintf(stderr,"error!\n");
				}
				break;
			case 'm':
				printf("m...\n");
				if(optarg != NULL)
					printf("%s\n", optarg);
			case 1:
				printf("This option parameter is not available\n");
				break;
			case '?':
				printf("That's not an option\n");
				break;
		}
	}

	return 0;
}

#endif
