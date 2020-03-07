#include <cstring>
#include <cstdlib>


#include "EStore.h"
#include "TaskQueue.h"
#include "sthread.h"
#include "RequestGenerator.h"

class Simulation
{
    public:
    TaskQueue supplierTasks;
    TaskQueue customerTasks;
    EStore store;

    int maxTasks;
    int numSuppliers;
    int numCustomers;

    explicit Simulation(bool useFineMode) : store(useFineMode) { }
};

/*
 * ------------------------------------------------------------------
 * supplierGenerator --
 *
 *      The supplier generator thread. The argument is a pointer to
 *      the shared Simulation object.
 *
 *      Enqueue arg->maxTasks requests to the supplier queue, then
 *      stop all supplier threads by enqueuing arg->numSuppliers
 *      stop requests.
 *
 *      Use a SupplierRequestGenerator to generate and enqueue
 *      requests.
 *
 *      This thread should exit when done.
 *
 * Results:
 *      Does not return. Exit instead.
 *
 * ------------------------------------------------------------------
 */
static void*
supplierGenerator(void* arg)
{
    // TODO: Your code here
    Simulation* sim=(Simulation*)arg;
    SupplierRequestGenerator gen1{&sim->supplierTasks};
    int max=sim->maxTasks;
    for(int i=0;i<max;i++) {
	    gen1.enqueueTasks(max,&sim->store); 
    }

    gen1.enqueueStops(sim->numSuppliers);
    exit(0); // Keep compiler happy.
}

/*
 * ------------------------------------------------------------------
 * customerGenerator --

 *      The customer generator thread. The argument is a pointer to
 *      the shared Simulation object.
 *
 *      Enqueue arg->maxTasks requests to the customer queue, then
 *      stop all customer threads by enqueuing arg->numCustomers
 *      stop requests.
 *
 *      Use a CustomerRequestGenerator to generate and enqueue
 *      requests.  For the fineMode argument to the constructor
 *      of CustomerRequestGenerator, use the output of
 *      store.fineModeEnabled() method, where store is a field
 *      in the Simulation class.
 *
 *      This thread should exit when done.
 *
 * Results:
 *      Does not return. Exit instead.
 *
 * ------------------------------------------------------------------
 */
static void*
customerGenerator(void* arg)
{
    // TODO: Your code here
    Simulation* sim=(Simulation*)arg;
    bool res=(sim->store).fineModeEnabled();
    CustomerRequestGenerator gen1{&sim->supplierTasks,res};
    int max=sim->maxTasks;
     for(int i=0;i<max;i++){
	      gen1.enqueueTasks(max,&sim->store);
      }

   gen1.enqueueStops(sim->numSuppliers);

    exit(0);
     // Keep compiler happy.

}

/*
 * ------------------------------------------------------------------
 * supplier --
 *
 *      The main supplier thread. The argument is a pointer to the
 *      shared Simulation object.
 *
 *      Dequeue Tasks from the supplier queue and execute them.
 *
 * Results:
 *      Does not return.
 *
 * ------------------------------------------------------------------
 */
static void*
supplier(void* arg)
{
    // TODO: Your code here. 
    Simulation* sim=(Simulation*)arg;
    int numSupply=sim->numSuppliers;
    for(int i=0;i<numSupply;i++){
	    Task t= (sim->supplierTasks).dequeue();
	    t.handler(t.arg);
	     
    }
    return NULL;
    // Keep compiler happy.
}
/*
 * ------------------------------------------------------------------
 * customer --
 *
 *      The main customer thread. The argument is a pointer to the
 *      shared Simulation object.
 *
 *      Dequeue Tasks from the customer queue and execute them.
 *
 * Results:
 *      Does not return.
 *
 * ------------------------------------------------------------------
 */
static void*
customer(void* arg)
{
    // TODO: Your code here.
     Simulation* sim=(Simulation*)arg;
     int numCust = sim->numCustomers;
     for(int i=0;i<numCust;i++){
	      Task t = (sim->customerTasks).dequeue();
	      t.handler(t.arg);
     }
   return NULL;// Keep compiler happy.
}

/*
 * ------------------------------------------------------------------
 * startSimulation --
 *      Create a new Simulation object. This object will serve as
 *      the shared state for the simulation. 
 *
 *      Create the following threads:
 *          - 1 supplier generator thread.
 *          - 1 customer generator thread.
 *          - numSuppliers supplier threads.
 *          - numCustomers customer threads.
 *
 *      After creating the worker threads, the main thread
 *      should wait until all of them exit, at which point it
 *      should return.
 *
 *      Hint: Use sthread_join.
 *
 * Results:
 *      None.
 *
 * ------------------------------------------------------------------
 */
static void
startSimulation(int numSuppliers, int numCustomers, int maxTasks, bool useFineMode)
{
    // TODO: Your code here.

     bool fineMode=useFineMode;

     Simulation sim(fineMode);
     sim.maxTasks=maxTasks; 
     sim.numSuppliers=numSuppliers;
     sim.numCustomers=numCustomers;
    
     sthread_t sG,cG;
     sthread_t * customers = new sthread_t[numCustomers];
     sthread_t * suppliers = new sthread_t[numSuppliers];  

     //Simulation * sim_on_heap = new Simulation(fineMode);

     sthread_create (&sG,supplierGenerator,&sim);
     sthread_create (&cG,customerGenerator,&sim);
    //create two arrays of numS and numC supplier and customer threads 
     for(int i=0;i<numSuppliers;i++)
	     sthread_create (&customers[i],customer,&sim);
     for(int i=0;i<numCustomers;i++)
	     sthread_create (&suppliers[i],supplier,&sim);

     sthread_join(sG);
     sthread_join(cG);

    for(int i=0;i<numSuppliers;i++)
     sthread_join(suppliers[i]);
    for(int i=0;i<numCustomers;i++)
     sthread_join(customers[i]);

	    
}
int main(int argc, char **argv)
{
    bool useFineMode = false;

    // Seed the random number generator.
    // You can remove this line or set it to some constant to get deterministic
    // results, but make sure you put it back before turning in.
    srand(time(NULL));

    if (argc > 1)
        useFineMode = strcmp(argv[1], "--fine") == 0;
    startSimulation(10, 10, 100, useFineMode);
    return 0;
}

