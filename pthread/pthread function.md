-------
**thread**
> pthread\_mutex\_init  :new a mutex
  pthread\_mutex\_lock  :lock a lock
  pthread\_mutex\_unlock  :unlock
  pthread\_mutex\_trylock 
  pthread\_mutex\_destroy

> pthread\_cond\_init
  pthread\_cond\_destroy
  pthread\_cond\_wait      :bolck and wait
  pthread\_cond\_signal    :signal to wake up another thread
  pthread\_cond\_broadcast :signal to wake up some threads

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

**Schedual design**
* SCHED_OTHER : nonreal-time,normal
  SCHED_RR    : real-time,rotate to run
  SCHED_FIFO  : real-time,fifo
```
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setschedpolicy(&attr, SCHED_FIFO);\/\/sched\_policy
```
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
  



















