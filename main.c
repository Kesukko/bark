#include <stdio.h>
#include <string.h>


int printFile(int i, char *argv[], int options[])
{
	FILE *file;
	file = fopen(argv[i], "r");
	if(file == NULL)
	{
		printf("couldn't open file ' '%s '\n", argv[i]);
		return 1;
	}
	
	fseek(file, 0L, SEEK_END); //go to EOF
	long length = ftell(file);
	fseek(file, 0L, SEEK_SET); //go to top

	//print options
	int nums = options[0];
	int tabs = options[1];
	int ends = options[2];
	int info = options[3];
	
	if (info) {
		printf("\x1b[34m ## FILE NAME: %s ##\t## FILE SIZE: %ld bytes ##\n \x1b[0m",argv[i], length);
	}
	length += (ends) ? 3 : 0;
	char contents[length];
	int j = 1;
	while(fgets(contents, length, file))
	{
		if(nums) {
			printf("  %d | ", j);
		}
		if(ends) {
			int len = strlen(contents);
			if (len > 0 && contents[len - 1] == '\n') {
			    contents[len - 1] = '$';
			    contents[len] = '\n';
			    contents[len + 1] = '\0';
			} else if (len > 0)
			{
				contents[len] = '$';
				contents[len + 1 ] = '\n';
				contents[len + 2 ] = '\0';
			}
		}
		printf("%s", contents);
		j++;
	}
	fclose(file);
}

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("Please enter at least 1 argument!\n");
		return 1;
	}
	int options[4] = {0, 0, 0, 0};
	int count = strlen(argv[1]);
	int start = 1;
	if (argv[1][0] == '-'){
		start = 2;
		for(int j = 1; j<count; j++)
		{
			switch (argv[1][j]) {
				case 'n':
					options[0] += 1;
					break;
				case 't':
					options[1] += 1;
					break;
				case 'e':
					options[2] += 1;
					break;
				case 'i':
					options[3] += 1;
					break;
				default:
					printf("'%c' is not a valid argument!\n Please refer to the help section by writing --help\n", argv[1][j]);
					return 1;
					break;
			}
		}
	}
	for(int i = start; i<argc; i++)
	{
		int ret_value = printFile(i, argv, options);
		if (ret_value == 1)
		{
			return 1;
		}
	}
	return 0;
}
