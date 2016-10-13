#include<limits.h>
#include<pthread.h>
#include"errors.h"

void *thread_routine(void *arg)
{
	printf("this ia deatched thread\n");
	return NULL:
}
int main(int argc ,char * argv[])
{
	pthread_t thread_id;
	pthread_attr_t thread_attr;
	struct sched_papram thread_param;  //schedualling
	size_t stack_size;    //maybe  explained in more deep understand
	int status;
	status=pthread_attr_init(&thread_attr);
	if(status!=0)err_abort(status, "Create attr");
	status=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
	if(status!=0)err_abort(status,"set detach");
	status=pthrea_create(&thread_id,&pthread_attr,thread_routine,NULL);
	if(status!=0)err_abort("create thread");
	pritnf("main exiting\n");
	pthread_exit(NULL);
	return 0;
}

