# The infamous Dining Philosophers problem
### How to test it?
Simply `git clone` the repository, go into the `philo` directory for implementation with threads and mutexes, and go into the `philo_bonus` directory for implementation with processes and semaphores. 

Use Makefile command `make` for both directory. Once the executable is compiled, simply run the program with the 4/5 arguments specified below (for example, `./philo 15 800 200 200 3`)

Enjoy :))

### What is the problem?
_**General rules**_

* One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table
* The philosophers alternatively eat, think, or sleep
* There are **as many forks as philosophers**. Because serving and eating spaghetti with only 1 fork is difficult, a philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation
* Every philosopher needs to eat and should never starve. Philosophers don’t speak with each other. Philosophers don’t know if another philosopher is about to die. Philosophers should avoid dying

My program takes in at least 4 arguments (in order), and an optional 5th one:
1. `no. of philosphers`
2. `time to die`: if a philosopher doesn't start eating this amount of time since the time they began their last meal or the beginning of the simulation, they die
3. `time to eat`: the amount of time taken for each philospher to eat (holding 2 forks!)
4. `time to sleep`: the amount of time a philosopher will sleep for after eating
5. `eat goal`: if every philosopher has eaten at least this number of times, then the simulation is completed. If not specified, the simulation stops when a philosopher dies or it simply never stops...

The program will print out any state change of a philospher in the following format:
> timestamp_in_ms X has taken a fork
> 
> timestamp_in_ms X is eating
> 
> timestamp_in_ms X is sleeping
> 
> timestamp_in_ms X is thinking
> 
> timestamp_in_ms X died
>
> Eat goal achieved! :)

### Now for the mandatory part
* Each philosopher should be a `thread`
* The philosophers are sitting at a round table, with 1 fork each on their right and left side (so they can only pick up the forks next to them)
* Use mutex to protect the fork state, so we do not accidentally duplicate forks.

Some rough notes for the key concepts:
* `Threads` - multiple threads of a given process may be executed concurrently.
  * The threads share resources such as **memory, code, data** etc..
  * Benefits include:
    * **_Responsiveness_**: allow a program to continue running even if part of it is blocked or is performing a lengthy operation
    * **_Resource sharing_**: allows an application to have several different threads of activity within the same address space. Making the system more efficient.
    * **_Economy_** - it is costly to allocate memory and resources for process creation.  
    * **_Multiprocessors_** - if we have a multiprocessor architecture, threads can be running in parallel on different processors. Whereas a single-threaded process can only run on one CPU, no matter how many are available
    * Use data type `pthread_t` for the thread variable
  * Use `pthread_create()` to initiate the thread.
  * Use `pthread_join()` to join the thread back to the main code. 
  * Both join and create **return 0** if success and error code if an error occurs.
* `Race conditions` - multiple tasks or threads access a shared resource without sufficient protection and lead to undefined or unpredictable behaviour. E.g. two threads are accessing the same memory and writing them, leading to one overwriting the other, leading to wrong output at the end.
* `Mutex` - Mutual exclusion. To ensure only one thread at a time can access a shared resource or section of code
  * `pthread_mutex_init (&mutex, NULL)` & `pthread_mutex_destroy(&mutex)`
  * `pthread_mutex_lock(&mutex)` (code) `pthread_mutex_unlock(&mutex)`

### Bonus!!
* Each philosopher should be a `process`, but the main process is not a philospher
* All the forks are put in the middle of the table.
* The number of available forks is represented by a `semaphore`

Notes for this section:
* `Processes`
  * Processing ID (`PID`) - a numerical ID assigned to each running process, normally a positive integer
  * `Parent process` - initiates the creation of other child processes.
  * `Child process` - shares a copy of the code, data, and environment, but capable of executing its own task independent of its parent process. And the termination does not affect the parent process.
  * `Fork()`. Can do pid_t pid = fork(). Used to initiate a child process.
    * Return value is 0 for child process, so pid will be 0, otherwise we are in the parent process. If -1, meaning forking has failed. 
* `Semaphore`
  * Data type `sem_t`
  * `sem_unlink(“”)` - removes a named semaphore from the system. Generally used before creating a new semaphore to ensure any previous instances with the same name are removed. 
  * `sem_open(“name”, O_CREAT, 0600, value)`
    * O_CREAT - used to create the semaphore if it doesn´t exist
    * 0600 - file permission (read and write)
  * `sem_wait(sem_t *sem)` - if the semaphore value is greater than 0, it is decremented, and the process proceeds. If the value is 0, the calling process is blocked until the semaphore becomes non-zero
  * `sem_post (sem_t *sem)` - increments the value of the semaphore pointed to by ‘sem’. If the value of sem was previously 0, sem_post will resume the processes that were blocked previously.
  * `sem_close(sem_t *sem)` - should be called when finished using a named semaphore, and to release system resources associated with it. However, it does not erase the semaphore itself, instead simply decrements the reference count of the semaphore. If the reference count drops to 0 as a result of sem_close, the system may release resources associated with the named semaphore. However, it is not immediately removed from the system, it may persist as long as it is still being used by other processes. 


