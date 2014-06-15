#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define PROJID	888

int lock(int semid)
{
	struct sembuf sop;

	sop.sem_num = 0;
	sop.sem_op = -1;
	sop.sem_flg = 0;

	return semop(semid, &sop, 1);
}

int unlock(int semid)
{
	struct sembuf sop;

	sop.sem_num = 0;
	sop.sem_op = 1;
	sop.sem_flg = 0;

	return semop(semid, &sop, 1);
}

// we have $1000 at the beginning
int balance = 1000;

/* saving thread every time we save $1, in 1000 times */
void *thr_deposit(void *data)
{
	int i;

	for (i = 0; i < 1000; i++)
	{
		lock(*(int *)data);
		balance++;
		// printf("--- deposit --- balance = %d\n", balance);
		unlock(*(int *)data);
	}
}

/* getting thread every time we get $1, in 1000 times */
void *thr_withdraw(void *data)
{
	int i;

	for (i = 0; i < 1000; i++)
	{
		lock(*(int *)data);
		balance--;
		// printf("--- withdraw--- balance = %d\n", balance);
		unlock(*(int *)data);
	}
}

int main(void)
{
	key_t key;
	int semid, fd;
	pthread_t tid_deposit, tid_withdraw;

	// open a file to create key
	fd = creat("./key_file", 0666);

	// create key
	if (-1 == (key = ftok("key_file", PROJID)))
	{
		perror("ftok");
		return 0;
	}

	// create signals based on the key
	// 1: how many signals we need
	if (-1 == (semid = semget(key, 1, IPC_CREAT)))
	{
		perror("semget");
		return 0;
	}

	// 0: setting the signal which with the lower mark.
	// 1: how many shared resources most used simultaneously for execution flow. 1 means mutex.
	semctl(semid, 0, SETVAL, 1);

	printf("semid = %d\n", semid);
	printf("create deposit thread and withdraw thread.\n");
	printf("--- start, the balance = %d\n", balance);
	pthread_create(&tid_deposit, NULL, thr_deposit, &semid);
	pthread_create(&tid_withdraw, NULL, thr_withdraw, &semid);

	pthread_join(tid_deposit, NULL);
	pthread_join(tid_withdraw, NULL);

	semctl(semid, 0, IPC_RMID);

	printf("--- ending ...\n");
	printf("Now the balance = %d\n", balance);

	close(fd);

	return 0;
}
