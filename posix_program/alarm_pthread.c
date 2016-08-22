//$ time.h library function nee to learn and understand 
#include<time.h>
#include<pthread.h>
#include"errors.h"
//#define DEBUG

//define struct alarm_t
typedef struct alarm_tag
{
	struct alarm_tag *link;
	int 		  seconds;
	time_t 		  time;
	char   		  message[64];
}alarm_t;

//initializa mutex and alarm_list
pthread_mutex_t alarm_mutex =PTHREAD_MUTEX_INITIALIZER ;
alarm_t *alarm_list =NULL;

void * alarm_thread(void*arg)
{
	alarm_t *alarm;
	int sleep_time;
	time_t now;
	int status;
	while(1)
	{
		status=pthread_mutex_lock(&alarm_mutex);
		if(status!=0)err_abort(status,"lock mutex");
		alarm= alarm_list;
		if(alarm==NULL) sleep_time=1;
		else
		{
			alarm_list=alarm->link;   //surprisely assign
			now=time(NULL);
			if(alarm->time<=now)sleep_time=0;
			else sleep_time=alarm->time - now;
#ifdef DEBUG
	printf("[waiting: %s(%d)\"%s\"]\n",ctime(&(alarm->time)), sleep_time,alarm->message);
#endif
		}
		status=pthread_mutex_unlock(&alarm_mutex);
		if(status!=0)err_abort(status,"unlock mutex");
		if(sleep_time>0)sleep(sleep_time);
		else sched_yield();    
		//library function to call prossor to athread which is ready
		if(alarm!=NULL)
		{
			printf("%d seconds later:  %s\n",alarm->seconds,alarm->message);
			free(alarm);
			//free a alarm node i the alarm_list which is a simple linklist.
		}
	}
}

int main(int argc, char *argv[])
{
	char line[128];
	int status;
	alarm_t *alarm,**last,*next;
	pthread_t thread;
	status=pthread_create(&thread,NULL,alarm_thread,NULL);
	if(status != 0)
		err_abort(status,"Create alarm thread");
	while(1)
	{
		printf("Alarm > ");
		if(fgets(line,sizeof(char)*128,stdin)==NULL) exit(0);
		if(strlen(line)<=1)continue;
		alarm=(alarm_t *)malloc(sizeof(alarm_t));
		if(alarm==NULL)errno_abort("Allocate alarm");
		if(sscanf(line,"%d %64[^\n]",&alarm->seconds,alarm->message)<2)
		{
			fprintf(stderr,"Bad command\n");
			free(alarm);
		}else{
			status=pthread_mutex_lock(&alarm_mutex);
			if(status!=0)err_abort(status,"Lock mutex");
			alarm->time=time(NULL)+alarm->seconds;
			last=&alarm_list;// prevois node
			next=*last;      // traverse and compare node
			//find the first node whose time larger or equal than the cur alarm_node
			while(next!=NULL)
			{
				if(next->time>=alarm->time)
				{
					alarm->link=next; //insert the current alarm, link to the next
					*last=alarm;      // link to the prevois
					break;
				}
				last =&next->link;
				next= next->link;
			}
			if(next==NULL)            // not find larger and equal, so inset in the end
			{
				*last=alarm;
				alarm->link=NULL;
			}
#ifdef DEBUG
	printf("[list: ");
	for(next=alarm_list;next!=NULL;next=next->link)
		printf("%s(%d)[\"%s\"]",ctime(&(next->time)),(next->time -time(NULL)),next->message);
	printf("]\n");
#endif
			status=pthread_mutex_unlock(&alarm_mutex);
			if(status!=0)err_abort(status,"Unlock mutex");
		}
	}
}
