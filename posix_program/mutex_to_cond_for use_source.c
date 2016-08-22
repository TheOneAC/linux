/* $ waiting on a conditon variable atomatically release 
     the associated mutex and waits untill another thread signals
 * there some question in how the wait and mian interact totally!!!!
 */

#include<pthread.h>
#include<time.h>
#include"errors.h"
typedef struct my_struct_tag
{
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	int 		value;
}my_struct_t;
my_struct_t data ={PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,0};// static init

int hibernation=1;  //sleep time for wait_thread to  signal
/* if hibernation > timeout limit  timeout
 * if hibernation < timeout limit never timeout
 * if hibernation == timeout limit ,maybe time out
 */
void* wait_thread(void *arg)
{
	int status;
	sleep(hibernation);
	status=pthread_mutex_lock(&data.mutex);        //lock 
	if(status!=0)err_abort(status,"Lock mutex");
	data.value=1;
	status =pthread_cond_signal(&data.cond);       // signal
	if(status!=0)err_abort(status,"Signal conditon");
	status=pthread_mutex_unlock(&data.mutex);      // unlock
	if(status!=0)err_abort(status,"Unlock");
	//visit shared source
	return NULL;
}
int  main(int argc, char const *argv[])
{
	pthread_t wait_thread_id;
	int status;
	struct timespec timeout;
	if(argc>1)hibernation= atoi(argv[1]);          //control the wait time for wait_thread to signal
	status=pthread_create(&wait_thread_id,NULL,wait_thread,NULL);
	if(status!=0)err_abort(status,"Create wait thread");
	timeout.tv_sec=time(NULL)+2;                   //timeout limit
	timeout.tv_nsec=0;
	status=pthread_mutex_lock(&data.mutex);        //lock
	if(status!=0)err_abort(status,"Lock mutex");	
	while(data.value==0)                           
  	// test timeout if timeout ,not wait , else continue  waitting for signal
	{
		status=pthread_cond_timedwait(&data.cond,&data.mutex,&timeout);
		//pthread_cond_timedwait()   cause a wait to end with an ETIMEDOUT status  after a certian time is reached
		if(status==ETIMEDOUT)
		{
			printf("Condition wait timed out.\n");
			break;
		}else if(status!=0)err_abort(status,"wait on condition");
	}
	if(data.value!=0)printf("condition was signaled.\n");
	//get signal and operate, after operation unlock
	status=pthread_mutex_unlock(&data.mutex);         
	if(status!=0)err_abort(status, "unlock mutex");
	return 0;
}
