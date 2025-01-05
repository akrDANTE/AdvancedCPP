#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<chrono>
#include<mutex>

// critial sections
// must only be executed by one thread at a time, usually accessing a shared resource

// Locking protocol: one thread can enter the critical section all other threads are locked out

// Mutex
//  Mutual Exclusion Object
//  two states: locked/unlocked
//  used to exclude threads from entering the critical section
//  if the mutex is unlocked, a thread can enter the critical section else wait till unlocked
//  lock mutex when entering critical section, unlock when leaving
//  mutex can only be locked once
//  unlocking a mutex publishes any changes(shared data is updated everywhere)
//  acquire - release of mutex makes sure there is no data race
//  std::mutex : <mutex>
//    must be visible to all task functions which uses it
//    must be defined outside task functions
//    global/static for global task functions, class data member with member func, refrence capture with lambda
//    lock() : tries to lock the mutex, waits until it locks the mutex
//    try_lock() : tries to lock the mutex, returns immediately
//       returns true if locked the mutex succesfully, else returns false
//       used for loops
//    unlock() : unlock the mutex
//    all paths should unlock the mutex even the exception ones

// internally synchronized classes
//   std containers need to be externally synchronized
//   our own types can provide internal sync
//     using std::mutex as a data member
//     member funcs lock the mutex before accessing class data and unlock when done
//   both read and write sections must be synchronized

// Lock guard
//    exception thrown in critical section can cause infinite lock on mutex object
//    causing all the waiting threads to be blocked
//    wrapper class over mutex uses RAII constructor acquires mutex, destructor releases mutex
//    std::lock_guard very basic class has constructor and destructor only
//    constructor takes mutex as argument and locks it, destructor releases it
//    template class
//    std::lock_guard<std::mutex> lck_guard(mutex);
//    keeps the mutex locked until the end of scope, which may cause other threads to be blocked

// unique lock
//    std::unique_lock<std::mutex> => lock gaurd with unlock function
//    constructor options: default calls mutex lock function
//       try to get lock : do not wait if unsuccessful: std::try_to_lock
//           wait with a time-out if unsuccessful for timed mutex 
//       do not lock : will be locked later or mutex is already locked : std::defer_lock
//       std::adopt_lock : takes a mutex that is already locked, does not lock twice
//    owns_lock() member checks if the mutex is locked, also has lock, unlock funcs
//    move-only class
//    we can write a function that creates a lock object and return it
//      function could lock different types of mutex, depending on the args
//    requires more storage and is slower than lock_guard
//    use lock_guard to lock a mutex for an entire scope
//    use unique_lock if you need to unlock within the scope and if extra features required

// Timeouts and mutex
// std::recursive_mutex : can call lock() member function repeatedly without calling unlock
//    for each lock call there must eventually be an unlock call, bad design(avoid using it)
// std::timed_mutex : similar to std::mutex with more functions
//    bool try_lock_for(duration) : keep trying to lock for certain duration
//    bool try_lock_until(timepoint) : keep trying to lock the mutex until a specified time
//		returns true if mutex was locked else false
//      timepoint = std::chrono::system_clock::now() + 900ms;
//      may return later then reuested
// unique_lock has above member functions and are fowarded to wrapped mutex

// multiple readers, single writer
//   stock market data, audio/video buffers streaming, shared data
//   selective locking: read-write lock

// std::share_mutex : <shared_mutex>
//   exclusive lock : no other thread can acquire lock
//      lock_guard<std::shared_mutex> , unique_lock<std::shared_lock>
//      can only acquire if mutex is unlocked
//	    lock, try_lock, unlock
//   shared lock : other threads may acquire a shared lock
//      std::shared_lock<std::shared_mutex>
//      can only acquire if any thread has exclusive lock
//      lock_shared(), try_lock_shared, unlock_shared

// shared data initialization
//   in c++11 only one thread can initialize the local static variable, after that the declaration is blocked
// singleton class : private constructor, copy move operators are deleted, a static member function that returns the unique instance
//   in c++11 create get_singleton function (with singleton static variable) outside the class to avoid constructor datarace  

// thread local variables
//   same as static and global however seperate object for each thread
//   with static single object shared by all threads
//   use thread_local to declare them
//   destroyed when thread is completed

// lazy initialization
//    we only initialize a variable the first time we use it, useful when construction is expensive
//    double checked locking to avoid data race: still may cause data race
//    std::call_once() : given function is only called once
//      it is done in one thread, the thread cannot be interrupted until the func completes
//      we use it with a global instance of std::once_flag, we pass the instance and function to std::call_once
//    use meyer's singleton

// deadlock
//  a thread cannot run, as one thread is waiting for other thread and other thread is waiting for this thread
//  waiting for mutexes can cause deadlocks 
//   one way to avoid mutex deadlock : have order of mutex locks be same in all threads
//     may not be feasible in large programs
//  dining philosopher problem
//  another way to avoid deadlock: lock all mutexes at once and then proceed
//    c++17 way : std::scoped_lock lck(mut1, mut2...) mutexes taken in order provided to constructor, destructor releases mutexes in reverse order
//    c++11 way : std::lock(mut1, mut2); then unlock later ourselves or use wrappers, std::try_lock(mut1, mut2)
//       try_lock returns -1 on success else index of mutex which could not be taken
//    hierarchical mutex : impose an ordering on mutexes
//      a thread cannot lock a mutex unless it has already locked a mutex with a lower status(id/alpha)
//  general deadlock avoidance:
//     avoid waiting for a thread while holding a lock
//     try to avoid waiting for other threads
//     try to avoid nested locks
//     avoid calling functions within a critical section
//  try_lock with timeout may end up as livelock
//  livelock:
//     in deadlock threads are inactive, in livelock threads are active but are not doing anything useful
//     can result from badly done deadlock avoidance
//     set thread priority using os by passing native_handle() so high priority thread will run first/more often
//     resource starvation: a thread cannot get the resources it needs to run
//       deadlock/livelock
//       lack of system resources
//       low priority threads may get starved
//     at randomness to avoid livelock
//     provide central arbitrator to coordinate threads : reduces parallelism

// mutex guidelines
//    always hold a lock for the shortest possible time
//    avoid locking lengthy operations if possible
// Reading
//    Lock
//    Make copy of shared data
//    unlock and process copy
// writing
//    Lock
//    make a copy
//    unlock and process copy
//    lock again
//    update the shared data from the copy
//    unlock
// for thread safe data structures
//   do not lock any more elements than necessary
//   do not make locking too fine-grained
//      do not lock individual elements
//      need to lock neighbouring elements in a single operation

// 

std::mutex mtx;
std::string glob("what");
std::vector<std::string> vec;
auto i = std::back_inserter(vec);

void hello(std::string arg) {
	std::cout << "Started " << std::this_thread::get_id() << std::endl;
	std::lock_guard<std::mutex> lck(mtx);
	*i = arg;
}

int main()
{
	std::cout << "hello " << std::endl;
	std::thread thr1(hello, "is");
	std::thread thr2(hello, "going");
	std::thread thr3(hello, "on?");

	thr1.join();
	thr2.join();
	thr3.join();


	for (auto& s : vec)
		std::cout << s << " ";
	return 0;
}