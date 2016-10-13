-------
**thread**
> pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
> pthread\_mutex\_init (pthread_mutex *mutex,pthread_mutexattr_t *attr) :new a mutex
  pthread\_mutex\_lock  :lock a lock
  pthread\_mutex\_unlock  :unlock
  pthread\_mutex\_trylock 
  pthread\_mutex\_destroy (pthread_mutex *mutex)

> pthread\_cond\_init
  pthread\_cond\_destroy
  pthread\_cond\_wait      :bolck and wait
  pthread\_cond\_signal    :signal to wake up another thread
  pthread\_cond\_broadcast :signal to wake up some threads
  **when in doubt use broadcast **

* int pthread\_create(  pthread\_t \*thread,
			pthread\_attr\_t \*attr, 
			void\*(\*start_routine)(void\*)),
			void(*arg);
> thread：返回创建的线程的ID
  attr：线程属性，调度策略、优先级等都在这里设置，如果为NULL则表示用默认属性
  start\_routine：线程入口函数，可以返回一个void*类型的返回值，该返回值可由pthread\_join()捕获
  arg：传给start_routine的参数， 可以为NULL
  返回值：成功返回0

**thread attribute**
* pthread\_attr\_get***()
  pthread\_attr\_set***()
  pthread\_get***()
  pthread\_set***()
* pthread_mutexattr_t attr;
  int pthread_mutexattr_init(pthread_mutexattr_t *attr);
  int pthread_mutexattr_destroy(pthread_mutexaatr_t *attr);

**Cancel**
* int pthread_cancel(pthread_t thread);
  int pthread_setcancelstat(int state,int *oldstate);
  int pthread_setcanceltype(int type,int*oldtype);
  void pthread_testcancel(void);
  void pthread_cleanup_push(void(*routine)(void* ),void*arg);
  void pthread_clean_pop(int * execute);
  state :enabled / disabled
  type  :deferred/ asynchronous
  To cancell a thread need the thread`s identifer
  : the pthread_t value returned to the creater by `pthread_create`
  : returned  itself by pthread_self
  the thread will not be cancelled imdietly  because of pending, i
  if you need know when thr thread actually terminated ,youn must `join` with it by `pthread_join` after cancelling it


**Schedual design**
* SCHED_OTHER : nonreal-time,normal
  SCHED_RR    : real-time,rotate to run
  SCHED_FIFO  : real-time,FIFO
```
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setschedpolicy(&attr, SCHED_FIFO);\/\/sched\_policy
```
**private data**
* pthread_key_t key;
  int pthread_key_create(pthread_key *key ,void(*destroy)(void*));
  int pthread_key_delete(pthread_key_t key);
* int pthread_setspecific(pthread_ket_t,const void *value);
  void *pthread_getspecific(pthread_key_t key);




**Priority**
* static-set:  pthread_attr_setchedparam(&attr,new_priority);
* dynamic_set:
  ```
   pthread_attr_setschedparam(&attr, &task->prv_priority);
   pthread_attr_getschedparam(&attr, &schedparam);
   schedparam.sched_priority = new_priority;
   pthread_attr_setschedparam(&attr, &schedparam);
   pthread_setschedparam(pthrid, sched_policy, &schedparam);
  ```

**Synchronization**
* pthreadjoin()   :keep the syn between parent and child pthreads
  default stat is PHREAD_CREATE_JOINABLE, onece set PTHREAD\_CREATE_DETACH, it can never coma back to joinable.
  `pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);`

**schedual inheritence**
* defaultly, the child thread have the same schedual ptiority with the parent. but if`pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);`, the child\`s priority is rely on the `attr`
  



















