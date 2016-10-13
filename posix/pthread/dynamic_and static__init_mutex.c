/*    it`s a good idea to associate a mutex with the data it protect! haha...
 *    if SUCESS return 0 : 'init' and 'destroy'
 * $  dynamic init mutex must be destroyed by mutex_desroy,
 * $  while static init not which inited by PTHREAD_MUTEX_INITIALIZER macro.
 */
#include<pthread.h>
#include "errors.h"
typedef struct my_struct_tag
{
	pthread_mutex_t mutex;
	int  		value;
}my_struct_t;
int main()
{
	//my_struct_t data ={PTHREAD_INITIALIZER,0};  //static init
	my_struct_t *data;
	int status;
	data=malloc(sizeof(my_struct_t));
	if(data==NULL) errno_abort("Allocate struture");
	status=pthread_mutex_init(&data->mutex,NULL);  // dynamic init
	if(status!=0) err_abort(status,"Init mutex");
	status= pthread_mutex_destroy(&data->mutex);
	if(status!=0)err_abort(status,"Destroy mutex");
	// before free the memory allocated to mutex, destroy it first
	(void) free(data);
	return status;
}
