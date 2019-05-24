#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct
{
	int sleep;
	const char *exec;
} cronjob;

#include "config.h"

void *cj_runner(void *arg)
{
	cronjob *j = (cronjob *)arg;
	while(1)
	{
		system(j->exec);
		sleep(j->sleep);
	}
}

int main(int argc, char **argv)
{
	int sz = sizeof(jobs) / sizeof(cronjob);
	pthread_t t;
	for(int i = 0; i < sz; i++)
		pthread_create(&t, 0, cj_runner, &jobs[i]);
	while(1) sleep(0xffffffff);
}
