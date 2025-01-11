#include<thread>
#include<iostream>
#include<future>
#include<chrono>

// Synchronous vs asynchronous programming:
//   sync : a task starts, current task blocked, wait for each task to complete
//      normal function calls
//      reduces throughput and user satisfaction
//      blocking operations
//      uses mutex and atomic variables for synchronization between threads
//   async : continue without waiting for tasks to complete
//     a task starts another task, current task continue, new task runs in background and receive data later
//     non blocking operations
//     synchronized using message queues
//       a threads pushes a message onto a concurrent queue
//       another thread takes the message off the queue and processes it
//       first thread continues to running without waiting
//       messages often consists of callable objets
//       cpp does not have standard concurrent queue(use Boost, ms PPl, intel TBB)
//     can be used to perform parallel operations
//       start new threads which all perform the same task
//       collect the result from each thread as it completes its task
//       combine the results into the final answer
//       can also be used in single-threaded programs using OS features

// Packaged Task : <future>
//   encapsulates a callable object for task's code and promise for the result of the task
//   provides a higher level abstraction
//   std::packaged_task<return_type(arg1_type, arg2_type)> ptask(callable_obj);
//   functor class overloaded operator() => invokes callable object, stores return val in promise
//   get_future() : returns future object
//   move only class
//   call get() on returned future object or wait() or timed waits
//   avoids boilerplate code : no need to create promise
//   applications:
//     create a container of packaged_task objects
//       threads do not start up until we are ready for them
//     useful for managing threads
//       each task can be run on a specified thread
//       custom thread scheduler runs threads in a certain order
//       custom thread pool consists of threads waiting for work to arrive

// std::async() <future>
//  std::async(function_name, args...)
//  returns future object
//  while(fut.wait_for(1s) != std::future_status::ready) for timed wait
//  to control running of task as seperate thread or synchronously, use launch flag as option argument to std::async()
//    std::launch::async => new thread for the task
//    std::launch::deferred => nothing happens until get() is called on returned future
//    if both flags are set then implementation decides which policy to use
//      problems : lack of certainity, thread local storage
//  return values of wait_for() and wait_until()
//    std::future_status::ready  result is available
//    std::future_status::timeout  timeout has expired
//    std::future_status::deferred  being lazily evaluated

// choosing thread object std::thread, std::packaged_task, std::async
// async : 
//   simplest way to execute a task, easy to obtain return value, choice of running task sync or async
//   higher level abstraction than std::thread 
//   cannot detach() tasks, std::launch::async is implicitly joined
// packaged_task
//   best choice if want to represent tasks as objects
//   can control when a task is executed, can control on which thread it is executed
// thread
//   allows access to underlying software thread
//   useful for features not supported by standard c++, like pinning a task to a core 
//   can be detached

// c++ async limitations
//   continuations : do this then do that task
//   only supports waiting on one future at a time
//   waiting on multiple threads has to be done sequentially
//   concurrent queue
//   cannot start multiple tasks at once, one task at a time



int calculate(int a, int b)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));

	return a + b;
}

void get_result(std::future<int> fut)
{
	std::cout << "waiting for the ans in thread" << std::endl;
	auto ans = fut.get();
	std::cout << ans << std::endl;
}



int main_asyncprog()
{


	auto fut2 = std::async(calculate, 6, 7);
	std::thread thr2(get_result, std::move(fut2));
	
	thr2.join();

	std::packaged_task<int(int, int)> ptask([](int a, int b) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return a + b; 
		});

	auto fut = ptask.get_future();
	//ptask(6, 7); // will run synchronously
	std::thread thr(std::move(ptask), 6, 7); // will run async
	std::cout << "waiting for the result..." << std::endl;
	auto ans = fut.get();
	std::cout << "ans : " << ans << std::endl;
	thr.join();
	return 0;
}