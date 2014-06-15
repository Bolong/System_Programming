#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	char filename[256];
	FILE *fp;
	int i;
	int n=10;

	printf("Please Enter The File Name:\n");
	scanf("%s", filename);
	fp = fopen(filename, "r");

	if (fp!=NULL)
	{
		char *line[128];
		while (fgets(line,sizeof line, fp) != NULL)
		{
			time_t rawtime;
			struct tm * timeinfo;

			time (&rawtime);
			timeinfo = localtime (&rawtime);
			printf("time:%s", asctime(timeinfo));
		}
		fclose(fp);
	}
	else
	{
		perror(filename);
	}

	return 0;
}
