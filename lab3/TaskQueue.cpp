#include <mutex>
#include <condition_variable>
#include <queue>
#include "TaskQueue.h"
#include "sthread.h"
//int s=q.size();

TaskQueue::
TaskQueue()
{
    // TODO: Your code here.
  
 smutex_init(&mut);
 scond_init(&cond);

 
}

TaskQueue::
~TaskQueue()
{

 smutex_destroy(&mut);
 scond_destroy(&cond);
 
       
	// TODO: Your code here.
   // ~TaskQueue()=default;
}

/*
 * ------------------------------------------------------------------
 * size --
 *
 *      Return the current size of the queue.
 *
 * Results:
 *      The size of the queue.
 *
 * ------------------------------------------------------------------
 */
int TaskQueue::
size()
{
    // TODO: Your code here.
    //
   int length=q.size();
   return length;
    //return -999; // Keep compiler happy until routine done.
}

/*
 * ------------------------------------------------------------------
 * empty --
 *
 *      Return whether or not the queue is empty.
 *
 * Results:
 *      The true if the queue is empty and false otherwise.
 *
 * ------------------------------------------------------------------
 */
bool TaskQueue::
empty()
{
    // TODO: Your code here.
    //
//	std::mutex::pthread_mutex_lock(mutex);
	if( q.empty()==true)
		return true;
	else
		return false;
	return false;

	
    //return false; // Keep compiler happy until routine done.
}

/*
 * ------------------------------------------------------------------
 * enqueue --
 *
 *      Insert the task at the back of the queue.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
void TaskQueue::
enqueue(Task task)
{
    smutex_lock(&mut);
      q.push(task);
    scond_signal(&cond,&mut);  
    smutex_unlock(&mut);
}
    

/*
 * ------------------------------------------------------------------
 * dequeue --
 *
 *      Remove the Task at the front of the queue and return it.
 *      If the queue is empty, block until a Task is inserted.
 *
 * Results:
 *      The Task at the front of the queue.
 *
 * ------------------------------------------------------------------
 */
Task TaskQueue::
dequeue(void)
{
    // TODO: Your code here.
    smutex_lock(&mut);
    while(q.empty())
    {
           scond_wait(&cond,&mut);
    }
    Task temp = q.front();
    q.pop(); 
   smutex_unlock(&mut);
   return temp; // Keep compiler happy until routine done.
}

