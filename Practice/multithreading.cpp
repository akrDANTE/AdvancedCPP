#include<iostream>
#include<thread>
#include<vector>
#include<string>
// concurrency
//  perform two or more activites at the same time
//  the task and feedback is performed at same time(download data and display %)
//  computers run many programs at the same time
// Hardware concurrency
//   multiple cpu chips
//   cpu chips with multiple processor cores
//   different processors can perform different activities at the same time
//   known as hardware threads: each processor follows its own thread of execution through the code
//   1 hardware thread == 1 cpu core
// software concurrency
//   managed by os
//   there are more software threads than hardware threads
//   some threads may have to stop and wait for something
//   while they are waiting another thread which is ready can run
// motivation
//   server throughput had to increase dramatically
//   responsiveness (seperation of concerns) GUI and background processes
//   fast numeric computation
//   effective use of hardware

// single threaded concurrency
//   each activity requires a seperate process: has one executin path or thread through program's code
//   may need "IPC" : message queue, pipe, semaphore, shared memory, network socket etc
//   example : program which displays a progress counter
//   each process has its own private memory space: cannot alter another's data accidentally
//   processes can run on different computer or over a network
//   creating a new process can be slow on some systems
//   IPC : adds complication, can be slow to setup, no direct support in c++

// multi threaded concurrency
//   a single process performs all activities
//   each activity has its own execution path or "thread"
//   concurrency is achieved by starting a new thread for each activity

// Threads
//   each thread is an independent execution environment
//   has its own execution stack, has its own processor state
//   threads are lightweight processes
//   less overhead to startup
//   smaller task switching overhead
//   easy to share data between threads
//   all teh threads in a process share its memory space
//   can access global data, pointers can be passed between threads
//   lack of data protection between threads
//   can cause data inconsistency and data corruption
//   requires careful programming
//   use only when the benefits outweigh the cost

// Single threaded c++ program structure
//   have single thread, when started executes code in main(entry point function for thread)
//   main() calls other functions which also run in main thread
//   when main() returns thread ends and so does the program

// multi Threaded program structure
//   have main thread that starts additional threads, which could start even more threads
//   each thread has its own entry point
//   when thread starts it executes the code in this function
//   when function returns the thread ends
//   the  main thread continues to execute its own code
//   it does not wait for other threads unless we explicitly tell it to

// pthreads library C interfaces, windows and unix api's
// C++ libs : ACE, Poco, Boost
// std::thread class is base level of concurrency
//    maps onto software thread managed by the OS
//    similar to boost threads, but with some important differences
//    no thread cancellation
//    different arg passing semantics
//    different behaviour on thread destruction
// c++14 read-write locks
// c++17 parallel algo
// c++20 joining threads, cancellation, coroutines, semaphores, latches and barriers
// c++23 improved support for coroutines 
// thread : a software thread, object of std::thread class
// task : higher level abstraction, some work that should be performed concurrently

// std::thread <thread>
// constructor starts a new execution thread, execution starts immediately
// parent thread will continue its own execution
// constructor takes a callable obj(entry point)
// execution thread will invoke this function
// entry point function (cannot be overloaded, any return value is ignored)

// thread termination
//   the parent thread completes its execution, the std::thread object goes out of scope, destructor is called
//   this can happen while the child is still running
//    this can create zombie threads
//   by default teh destructor calls std::terminate()
//   this terminates all threads, including  main
// join() member function is a blocking call
//   does not return until the thread has completed execution, parent waits for thread
// prevents std:thread's destructor calling std::terminate()
// this is known as joining: program can continue after thread obj is destroyed

// passing args to threads
// std::thread thr(func_name, args);
// std::thread object owns the arguments
// lvalue args are passed by value
// rvalue args are passed by move 
// it is safe to call str.empty() on str that has been moved using std::move
// use reference wrapper std::ref() for passing by reference, std::cref() for const ref
// beware of dangling refs make sure the ref is valid as long as thread is using it 
//   works similar to bind, it wraps around a reference 
// we can use member function as the entry point for the thread, requires an object of the class
//  class greeter{ public: void hello();} greeter greet; 
//  std::thread thr(&greeter::hello, &greet); // pass both member function pointer and obj
// we can use lambda with capture as well
//  std::thread thr( [&i]() {i *=2;} );

// multi threaded program on single processor is implemented by "time slicing"
// each thread runs on the CPU for a short time
// this switching between threads is done very quickly so threads appear to run concurrently
// done using thread scheduler of OS using pre-emptive task switching/ cooperative task switching
// requires context switch, save processor state(current processor registers, instruction pointer etc.) and loading
// processor cannot execute any instructions during a context switch

// single processor + cache
// to handle problem with memory latency(time taken between request and response) cache was used
// when first time data is requested it is copied to cache and then goes to cpu and next time it is accessed through cache
// the CPU writes to cache and then cache writes to memory, so cpu time is saved
// cache memory is close to cpu and uses static RAM so is fast
// cache hit:, cache miss
// cache controller manages cache 

// multiple processors
//  multiple sockets, multiple cores, 
//  hyperthreads: duplicate some of the circuitry within a processor core, enough to run a seperate thread with its own stack
//  additional caches and registers
// multi level cache
//  L1 cache : private to each processor, as close to core as possible(4 cycles)
//  L2 cache : usually private to each core(12 cycles)
//  L3 cache : shared by all the cores on the same socket(26-37) (mainmem ~300)
//  cache controller : coordinates the caches(cache coherency), monitors data changes
// Optimizations:
//  Pre-fetcher : looks at incoming instructions, fetches data before it is needed
//  store buffer : between core and L1 cache, modified data written to this buff
//  core can proceed to next instruction : does not need to wait for L1 cache

// Synchronization issues
//  different threads execute on different cores and may share data, can cause sync issues
//  each core that has access to data will have a seperate copy of data in cache, if one modifies the data then data will be different in every cache
//     can make data incosistent across cores
//  mutex and atomic variables can be used to sync data



void hello(std::string& str) {
	std::cout << "hello from thread " << str << std::endl;
	str.assign("ghost of sparta");
}

void fizzbuzz()
{
	std::string children[4]{ "Abdul", "Bart", "Claudia", "Divya" };
	int child_index = 0;
	int counter = 1;
	while (counter <= 50)
	{
		if (counter % 3 == 0 && counter % 5 == 0)
		{
			std::cout << children[child_index] << " says fizzbuzz" << std::endl;
		}
		else if (counter % 3 == 0)
		{
			std::cout << children[child_index] << " says fizz" << std::endl;
		}
		else if (counter % 5 == 0)
		{
			std::cout << children[child_index] << " says buzz" << std::endl;
		}
		else {
			std::cout << children[child_index] << " says " << counter << std::endl;
		}
		child_index = (child_index + 1) % 4;
		++counter;
	}
}


int main()
{
	std::string str("God hand!");
	std::cout << "current string value : " << str << std::endl;
	std::thread thr(hello, std::ref(str));
	//std::thread thr2(fizzbuzz);
	thr.join();
	std::cout << "after thread string value : " << str << std::endl;
	//thr2.join();
	return 0;
}