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

// System Thread interface
//  std::thread uses system's thread implementation
//  thread priority/affinity(pin thread to specific core) not available
//  thr.native_handle() : used internally by system's thread implementation
//    needed when making calls into the implementation's api
//  std::thread id: guaranteed to be unique, if two thread ids are equal the related objs are identical
//    could be used to store std::thread objs in associative containers
//    new thread may get teh ID of an earlier thread which has completed
//    std::this_thread.get_id();
//    thr.get_id();
//    std::this_thread::sleep_for(std::chrono::seconds(2)); could sleep for more than 2secs

// std::thread class
//   implmented using RAII
//   std::thread object has ownership of execution thread(only one obj can be bound at a time to a thread)
//   move_only class : transfers ownership of execution thread
//   passing a thread object should be pass by move : using std::move(obj) or std::thread(...)
//   returning is straight forward, compiler automatically moves object
//   each thread has its own execution stack which is unwound when the thread throws an exception
//    if no handler is found program is terminated
//    other threads cannot catch the exception
// detaching thread
//   detach() will cause child thread to run until it completes or the program terminates
//   parent keeps on executing
//   when an execution thread is detached, thread object is no longer associated with it
//   destructor will not call std::terminate()
//   we must make sure that join or detach is called in every branch to avoid resource leak
//     because in case exception in calling thread may cause resource leak
//   RAII solution for managing thread:
//     wrap the std::thread object in a class
//     the class's destructor calls join() 
//     join() can only be called once
//     joinable() member function can be used to check if join/detach already been called
//  interruptible_thread can be created in c++ as killing is not available
//  native_handle can be used to make OS stop the execution thread
//  c++20 has jthrad join() call is optional, supports cooperative interruption

// data sharing between threads
//  global/static for global thread funcs
//  static clas member for class member threads
//  variable capture by lambda threads 
// data race occurs when:
//  two or more threads access the same memory location and atleast one modifies it
//  potentially conflicting access to same memory location
//  only safe if threads are synchronized
//    one thread accesses the memory location at a time, other wait until safe to access
//    in effect threads execute sequentially while they access it
//  data race causes undefined behaviour
// Race condition
//   the outcome is affected by timing changes
//   data race is special case of race condition
// memory location is a scalar object : a built in variable, pointer, element in container, a struct class member which is scalar
//    a series of contiguous bitfields within the same word unless they contain zero-length bitfield
//    compound objects like C++ STL containers are memory locations
//    for our own types classes can provide their own synchronization
//    calling a sequence of member funcs may be problematic, usually better to implement them as memory locations
//  consequences of data race can be : incorrect results, program flow, torn writes and reads, improper construction or destruction of objs
//  compilers can optimize switch case statements to jump tables instead of if else statements
// avoiding data races
//   avoid shared data between different threads
//   synchronize the threads, impose ordering on how threads access the shared data
//     increaseed execution time and program complexity



void hello(std::string& str) {
	std::cout << "hello from thread " << str << std::endl;
	str.assign("ghost of sparta");
	try {
		throw 10;
	}
	catch (...)
	{
		std::cout << "error : sleeping for 5 seconds" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	
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


int main_mth()
{
	std::string str("God hand!");
	std::cout << "current string value : " << str << std::endl;
	std::thread thr(hello, std::ref(str));

	std::cout << "Thread handle is : " << thr.native_handle() << std::endl;
	std::cout << "Thread id is : " << thr.get_id() << std::endl;
	//std::thread thr2(fizzbuzz);
	thr.detach();
	std::cout << "after thread string value : " << str << std::endl;
	std::cout << "Thread handle is : " << thr.native_handle() << std::endl;
	std::cout << "Thread id is : " << thr.get_id() << std::endl;
	//thr2.join();
	return 0;
}