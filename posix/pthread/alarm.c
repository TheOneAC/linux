#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<wait.h>

int main()
{
	int seconds;
	char line[129];
	char message[64];

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
			sleep(seconds);				      // include in unistd.h
			printf("(%d)seconds later,it`s time to : %s.\n",seconds,message);
                                                                      // printf message for alarm
		}
	}
}
