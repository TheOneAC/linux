#include<pthread.h>
#include"errors.h"
typedef struct my_struct_tag
{
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	int 			value;
}my_struct_t;
//static init
//my_struct_t data ={PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,O};
int  main(int argc, char const *argv[])
{
	my_struct_t *data
	int status;
	data=malloc(sizeof(my_struct_t));     //allocate memory

	// dynamic init 
	if(data==NULL)errno_abort("Allocate structure");
	status=pthread_mutex_t(&data->mutex,NULL);
	if (status!=0)errno_abort(status,"init mutex");
	status=pthread_cond_t(&data->cond,NULL);
	if (status!=0)errno_abort(status,"cond mutex");
	status=pthread_cond_destroy(&data->cond);

	// dynamic init must be destroied and freed by youeself
	if (status!=0)errno_abort(status,"Destroy cond");
	status=pthread_mutex_destroy(&data->mutex);
	if (status!=0)errno_abort(status,"Destroy mutex");
	(void)free(data);
	
	return status;
}