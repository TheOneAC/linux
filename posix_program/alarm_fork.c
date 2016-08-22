#include"errors.h"

#include<sys/types.h>
#include<wait.h>


int main()
{
	int status;
	int seconds;
	char line[129];
	char message[64];
	pid_t pid;
	while(1)
	{
		printf("Alarm > ");
		if(fgets(line,sizeof(char)*128,stdin)==NULL)exit(0);  //read in the command buffered in line
		if(strlen(line)<=1)continue;			      // read in blank
		if(sscanf(line,"%d %64[^\n]",&seconds,message)<2)     //read in error format command
		{
			fprintf(stderr,"Bad command\n");
		}
		else
		{
			pid=fork();
			if(pid==(pid_t)-1)errno_abort("fork");
			if(pid==(pid_t)0)
			{
				sleep(seconds);
				printf("(%d)seconds later,it`s time to : %s.\n",seconds,message);
				exit(0);
			}
			else
			{
				do
				{
					pid=waitpid((pid_t)-1,NULL,WNOHANG);
					if(pid==(pid_t)-1)errno_abort("wait for child");
				}while(pid!=(pid_t)0);
			}
                                                                      // printf message for alarm
		}
	}
}
