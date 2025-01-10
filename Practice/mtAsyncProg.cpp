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




int calculate(int a, int b, std::promise<int> prom)
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	prom.set_value(a + b);
	return a + b;
}

void get_result(std::future<int> fut)
{
	std::cout << "waiting for the ans in thread" << std::endl;
	auto ans = fut.get();
	std::cout << ans << std::endl;
}



int main()
{
	std::promise<int> prom;
	auto fut2 = prom.get_future();

	std::thread thr1(calculate, 6, 7, std::move(prom));
	std::thread thr2(get_result, std::move(fut2));
	
	thr1.join();
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