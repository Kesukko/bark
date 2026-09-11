#include <stdio.h>

/*int main(int argc, char *argv[]){
	for (int i = 0; i < argc; i++)
	{
		printf("arg %d: %s\n", i, argv[i]);
	}
}*/
//show information about file
//printf("\x1b[34m #### FILE NAME: %s #### FILE SIZE: %ld bytes\n \x1b[0m",argv[i], length);

int main(int argc, char *argv[])
{
	for(int i = 1; i<argc; i++)
	{
		FILE *file;
		file = fopen(argv[i], "r");
		if(file == NULL)
		{
			printf("couldn't open file\n");
			return 1;
		}

		fseek(file, 0L, SEEK_END); //go to EOF
		long length = ftell(file);
		fseek(file, 0L, SEEK_SET); //go to top

		char contents[length];
		while(fgets(contents, length, file))
		{
			printf("%s", contents);
		}
		fclose(file);
	}
	return 0;
}
