#include<thread>
#include<mutex>
#include<future>
#include<condition_variable>
#include<algorithm>
#include<queue>
#include<functional>

// Data structures for concurrent programming
//   stl containers are memory objects
//   coarse grained locking:
//      locks the entire object
//      in effect all code that accesses the object will be single-threaded
//   fine grained locking
//      we choose which parts of the object to lock
//      allows concurrent access, requires writing extra code, requires careful design
//      increases the cost of creating an object (mutex initialization)

// shared_ptr
//    ref count is atomic : internal synchronization
//    shared data is the responsibility of programmer, externally synchronize threads


// monitor class
//   internally synchronized class : Java Synchronized object
//   transaction model : ACID 
//   can be implemented using mutexes
//     member functions may need to call other member  funcs : can cause deadlocks
//     results in many locking and unlocking operations can cause data races/race conditions
//     existing classes need to be modified
//   write a wrapper class with core class as data member and mutex as data member
//   
//   templated monitor class
//   template <typename T>
//   class Monitor {
//      T data; // object to be monitored
//      std::mutex mut; // mutex to protect it
//      public:
//       Monitor<T>(T data=T{}) : data(data) {}
//       
//       template<typename Func> // arg is callable obj, which takes an arg of type t
//       auto operator() (Func func) {
//         std::lock_guard<std::mutex> lck_guard(mut);
//         return func(data);
//       }
//   }

// Semaphore
//    has a counter (non-negative integer)
//    acquire() : decrements the counter
//    release() : increments the counter
//    if counter is 0: acquire will block, until the counter becomes positive again
//    use mutex and condition variable for synchronization
//    binary semaphore when counter can only be 0 or 1
//      can be used as a mutex, by callin acquire() and release() on same thread
//      if calls are in multiple threads we can use it as condition variable
//    higher level than mutex and condition variables
//    more flexible, simplere code better performance, more versatile
//    little book of semaphores : https://greenteapress.com/wp/semaphores

// Concurrent Data queue
//   std::queue : FIFO data structure
//     calling pop() on empty container is undefined behaviour
//     pop() does not return anything, front() returns first element at the front
//     race condition between front() and pop() in threaded code, so not safe for multithreaded code
//   simplest implementation is to write a wrapper around std::queue
//     pop() does something sensible if called on empty queue
//     push() can cause exception because of copy constructor call
//     instead of throwing when queue is empty in pop(), we can wait for another thread to add an element
//       we can do this by condition variable, the thread thta calls pop() calls wait() on the condition variable
//       the thread that calls push() notifies the condition variable
//       to avoid spurious and lost wakeups, we can add a predicate to wait() call
//       if queue is empty we continue waiting, if it is not empty then it is safe to continue and pop from the queue

template<typename T>
class Concurrent_Queue {
	std::queue<T> q;
	std::mutex mut;
	std::condition_variable cv;

public:
	Concurrent_Queue() = default;
	void push(T t) {
		std::lock_guard<std::mutex> lck_guard(mut);
		q.push(t);
		cv.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lck;
		cv.wait(lck, [this]() { return !q.empty(); });
		auto ret = q.front();
		q.pop();
		return ret;
	}
};

// thread pools
//    motivations
//      creating a thread involves a lot of overhead
//        create an execution stack for thread, call a system API, OS must create the internal data to manage the thread
//        scheduler must execute the thread
//        a context switch occurs to run the thread
//      creating a thread can take 10000 times as long as calling a function directly
//    a fixed size container of thread objects
//      usually equal to the number of cores on the machine
//      this can be found by calling std::thread::hardware_concurrency()
//    a queue of task function objects
//      a thread object takes a task off the queue
//      it calls the task function, when finished, it takes the next task from the queue
//    easy scalable
//    makes efficient use of resources
//       threads are never idle
//    works best for short, simple "one-shot" tasks where
//      the overhead of creating a thread object is comparable to task execution
//      the task does not block
//    overhead : adding and removeing tasks from the queue must be done in a thread-safe way
//    thread_pool class will contain
//       vector of threads objects
//       concurrent queue to incoming tasks
//       user of the class will call its submit() with task function as argument
//       each thread runs in an infinite loop which calls pop() on the queue
//         when pop() call completes, it will return a task function
//         the thread will then execute the returned task function

using Func = std::function<void()>;

class thread_pool {
	Concurrent_Queue<Func> work_queue;
	std::vector<std::thread> threads;
	void worker()
	{
		while (true)
		{
			Func task;
			task = work_queue.pop();
			task();
		}
	}
public:
	thread_pool()
	{
		const unsigned thread_count = std::thread::hardware_concurrency();
		for (unsigned i = 0; i < thread_count; i++)
		{
			threads.push_back(std::thread{ &thread_pool::worker, this });
		}
	}
	~thread_pool()
	{
		for (auto& t : threads)
		{
			t.join();
		}
	}
	void submit(Func f)
	{

	}
};

int main()
{
	return 0;
}