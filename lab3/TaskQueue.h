#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include "sthread.h"

typedef void (*handler_t) (void *); 

struct Task {
    handler_t handler;
    void* arg;
};

/*
 * ------------------------------------------------------------------
 * TaskQueue --
 * 
 *      A thread-safe task queue. This queue should be implemented
 *      as a monitor.
 *
 * ------------------------------------------------------------------
 */
class TaskQueue {
    private:
    std::queue<Task> q;
    smutex_t m;
    scond_t c;
     
 
    public:
    TaskQueue();
  	    
    ~TaskQueue();
   
    void enqueue(Task task);
    Task dequeue();

    int size();
    bool empty();
};

