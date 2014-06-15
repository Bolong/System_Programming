#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void)
{
	char filename[256];
	FILE *fp;
	pid_t pids[10];
	int ids[10];
	int i = 0;
    char a[10][129];
    
	printf("Please Enter The File Name:\n");
	scanf("%s", filename);
	fp = fopen(filename, "r");
    
	if (fp!=NULL)
	{
 		char *line[128];
		while (fgets(line, sizeof line, fp) != NULL)
		{
            strcpy(a[i], line);
			ids[i]=(pids[i]=fork());
			if (ids[i]<0)
			{
				perror("fork");
				abort();
			}
			else if (pids[i]==0)
			{
                execvp(line, NULL);
				exit(0);
			}
            i++;
		}
		fclose(fp);
	}
	else
	{
		perror(filename);
	}
    
    int status;
    pid_t pid;
    while (i > 0) {
        --i;
        pid = wait(&status);
        time_t t = time(0);
        struct tm* lt = localtime(&t);
        printf("[%04d%02d%02d %02d:%02d:%02d] [%s] [code exit %d]\n", lt->tm_year + 1900, lt->tm_mon + 1,
               lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec, a[i], status);
    }
    
	return 0;
}
