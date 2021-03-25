#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	struct option opts[] = {
		{"help", no_argument, NULL, 'p'},
		{"test", optional_argument, NULL, 's'},
		{0,0,0,0}
	};

	int c;

	while(1)
	{
		c = getopt_long(argc, argv, "hl", opts, NULL);
		if(c == -1)
			break;
		switch(c)
		{
			case 'h':
				printf("get -h...\n");
				break;
			case 'l':
				printf("get -l...\n");
				break;
			case 'p':
				printf("get --help\n");
				break;
			case 's':
				printf("get --tast\n");
				if(optarg != NULL)
					printf("%s\n", optarg);
				break;
			case '?':
				printf("I don't konw\n");
				break;
			default:
				break;
		}
	}


	return 0;
}
