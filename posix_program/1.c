#include<pthread.h>
#include"errors.h"
 typedef struct stage_tag
{
	pthread_mutex_t mutex;   // lock the stage
	pthread_cond_t  avail;   //stag itself is readty for process data
	pthread_cond_t  ready;   //data is ready for the stage to process.
	int 		data_ready;
	long 		data;
	pthread_t 	thread;  // thread operating on this stage
	struct stage_tag *next;  // point to next stage.
}stage_t;
typedef struct pipe_tag
{
	pthread_mutex_t   mutex;	//lock pipe
	stage_t		  *head;	//queue head
	stage_t		  *tail;
	int 		  stages;	//stages number
	int 		  active;	//active data elment
}pipe_t;

int pipe_send(stage_t *stage, long data)
{
	int status;
	status=pthread_mutex_lock(&stage->mutex);
	if(status!=0)return status;
	while(stage->data_ready)
	{
		status=pthread_cond_wait(&stage->ready,&stage->mutex);
		if(status!=0)
		{
			pthread_mutex_unlock(&stage->mutex);
			return status;
		}
	}
	stage->data=data;
	stage->data_ready=1;
	status=pthread_cond_signal(&stage->avail);
	if(status!=0)
	{
		pthread_mutex_unlock(&stage->mutex);
		return status;
	}
	status=pthread_mutex_unlock(&stage->mutex);
		return status;
}

void* pipe_stage(void *arg)
{
	stage_t *stage=(stage_t*)arg;
	stage_t *next_stage=stage->next;
	int status;
	status=pthread_mutex_lock(&stage->mutex);
	if(status!=0)err_abort(status,"lock pipe stage");
	while(1)
	{
		while(stage->data_ready!=1)
		{
			status=pthread_cond_wait(&stage->avail,&stage->mutex);
			if(status!=0)err_abort(status,"lwait for prevois stage");
		}
		pipe_send(next_stage,stage->data+1);
		stage->data_ready=0;
		status=pthread_cond_signal(&stage->ready);
		if(status!=0)err_abort(status,"wake next stage");
	}
}

void* pipe_create(pipe_t *pipe,int stages)
{

	int pipe_index;
	stage_t **link=&pipe->head,*new_stage, *stage;
	int status;
	status=pthread_mutex_init(&pipe->mutex,NULL);
	if(status!=0)err_abort(status,"init pipe stage");
	pipe->stages=stages;
	pipe->active=0;
	for(pipe_index=0;pipe_index<=stages;pipe_index++)
	{
		new_stage=(stage_t *)malloc(sizeof(stage_t));
		if(new_stage==NULL)err_abort(status,"Allocate stage");
		status=pthread_mutex_init(&new_stage->mutex,NULL);
		if(status!=0)err_abort(status,"init stage mutex");
		status=pthread_cond_init(&new_stage->avail,NULL);
		if(status!=0)err_abort(status,"init avali condition");
		status=pthread_cond_init(&new_stage->ready,NULL);
		if(status!=0)err_abort(status,"init ready condition");
		new_stage->data=0;
		*link=new_stage;
		link=&new_stage->next;
	}
	*link=(stage_t*)NULL;
	pipe->tail=new_stage;
	for(stage=pipe->head;stage->next!=NULL;stage=stage->next);
	{
		status=pthread_create(&stage->thread,NULL,pipe_stage,(void*)stage);
		if(status!=0)err_abort(status,"create pipe stage");
	}

	return 0;
}
int pipe_start(pipe_t *pipe,long value)
{
	int status;
	status=pthread_mutex_lock(&pipe->mutex);
	if(status!=0)err_abort(status,"lock pipe mutex");
	pipe->active++;
	status=pthread_mutex_unlock(&pipe->mutex);
	if(status!=0)err_abort(status,"unlock pipe mutex");
	pipe_send(pipe->head,value);
	return 0;
}
int pipe_result(pipe_t *pipe,long *result)
{
	stage_t *tail=pipe->tail;
	long value;
	int empty=0;
	int status;
	status=pthread_mutex_lock(&pipe->mutex);
	if(status!=0)err_abort(status,"lock pipe mutex");
	if(pipe->active<=0)empty=1;
	else pipe->active--;
	status=pthread_mutex_unlock(&pipe->mutex);
	if(status!=0)err_abort(status,"unlock pipe mutex");
	if(empty)return 0;
	pthread_mutex_lock(&tail->mutex);
	while(!tail->data_ready)
		pthread_cond_wait(&tail->avail,&tail->mutex);
	*result=tail->data;
	tail->data_ready=0;
	pthread_cond_signal(&tail->ready);
	pthread_mutex_unlock(&tail->mutex);
	return 1;
}
 int main()
{
	pipe_t my_pipe;
	long value,result;
	int status;
	char line[128];
	pipe_create(&my_pipe,10);								//create main thread
	printf("Enter inter values,or\"=\" for next result \n");
	while(1)
	{
#ifndef DEBUG
			printf("#1\n" );
#endif
		printf("data > ");
		if(fgets(line,sizeof(line),stdin)==NULL)exit(0);

		if(strlen(line)<=1)continue;

		if(strlen(line)<=2&&line[0]=='=')
		{
#ifndef DEBUG
			printf("#2\n" );
#endif
			if(pipe_result(&my_pipe,&result))printf("result is%ld\n",result);
			else printf("pipe is empty\n");
		}else 
		{
			if(sscanf(line,"%ld",&value)<1)fprintf(stderr,"enter an integer value\n");
			else pipe_start(&my_pipe,value);
		}
	}
}



















