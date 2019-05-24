#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "config.h"

typedef struct
{
	int sleep;
	char exec[MAX_EXEC_LENGTH];
} cron_job;

void *cj_runner(void *arg)
{
	cron_job *j = (cron_job *)arg;
	while(1)
	{
		system(j->exec);
		sleep(j->sleep);
	}
}

int main(int argc, char **argv)
{
	FILE *f = fopen(CRON_LIST, "r");
	int i;
	char bfr[MAX_EXEC_LENGTH];
	char *b = bfr;
	cron_job jobs[MAX_JOBS];
	cron_job *j = jobs;
	memset(jobs, 0, sizeof(cron_job) * MAX_JOBS);
	while((i = fgetc(f)) != EOF)
	{
		cron_job cj;
		*b++ = i;
		while((i = fgetc(f)) != ' ' && i != EOF) *b++ = i;
		*b = '\0';
		cj.sleep = strtol(bfr, 0, 10);
		b = bfr;
		while((i = fgetc(f)) != '\n' && i != EOF) *b++ = i;
		*b = '\0';
		strcpy(cj.exec, bfr);
		*j++ = cj;
	}
	pthread_t t;
	for(cron_job *cj = jobs; cj < j; cj++)
		pthread_create(&t, 0, cj_runner, cj);
	while(1) sleep(0xffffffff);
}
