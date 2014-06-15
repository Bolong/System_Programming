#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	char filename[256];
	FILE *fp;
	pid_t pids[10];
	int ids[10];
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
			ids[i]=(pids[i]=fork());
			if (ids[i]<0)
			{
				perror("fork");
				abort();
			}
			else if (pids[i]==0)
			{
				sleep(10);
				printf("child process exit.\n");
				exit(0);
			}
		}
		fclose(fp);
	}
	else
	{
		perror(filename);
	}

	int status;
	pid_t pid;
	while(n>0)
	{
		pid = wait(&status);
		printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
		--n;
	}

	return 0;
}
