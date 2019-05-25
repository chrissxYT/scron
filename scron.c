#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct job
{
	int sleep;
	const char *exec;
};

void *runner(void *arg)
{
	struct job *j = (struct job *)arg;
	while(1) system(j->exec), sleep(j->sleep);
}

int main(int argc, char **argv)
{
	struct job jobs[] = {
		#include "jobs.h"
	};
	pthread_t t;
	for(int i = 0; i < sizeof(jobs) / sizeof(struct job); i++)
		pthread_create(&t, 0, runner, &jobs[i]);
	while(1) sleep(0xffffffff);
}
