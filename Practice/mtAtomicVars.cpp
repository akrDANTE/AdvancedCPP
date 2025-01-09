#include<iostream>
#include<thread>
#include<atomic>
#include<future>
#include<condition_variable>
#include<mutex>

// Integer ops and threads
//   usually single instruction (true on x64), provided data aligned correctly and fits single word
//   a thread can't be interrupted while performing integer operations
//   still we need to take locks on them as a thread could use a stale value in calculation and
//     thread could publish its result after a thread which ran later
//   atomic keyword:
//     the compiler will generate special instructions which disable prefetch for variable, flush the store buffer immediately after doing the increment
//     this also avoids some other problems, hw/compiler optims  which change instruction order
//     the result is that only one thread can access variable at a time
//     this prevents data race and makes operation take much longer
//     when we make a variable atomic, all ops are atomic, no threads will be able to interleave during ops
//     the object must be intialized for it to be atomic
//     the parameter must be trivially copyable: scalar type or class where all copy and move constructors are trivial
//     normally integers and pointers are used
//     for complex types locks may be added, which will make it even slower, to avoid use pointer
//     entire sequence of operations is not atomic, between threads may change the value
//     atomic types don't support . or -> operators, we must copy the value to non atomic and access using that
//   volatile keyword:
//     represents a variable which may change without explicit modification
//     prevents some compiler optimizations
//     typically used when accessing hardware
//     useful when we want to avoid compiler from optimizing code which may optimize away some function calls
// 
//   atomic member functions
//     store() : atomically replace the object's value with its arg
//     load() : atomically return the obj's value
//     operator=()
//     operator T()
//     exchange(): atomically replcae obj's value with arg and returns previous val
//     for atomic pointers fetch_add()(x++), fetch_sub()(x--), += and -= operators
//       integers also have these plus atomic bitwise logical ops &, | and ^
//     atomic_flag: boolean type atomic
//       clear(), test_and_set() sets flag to true and returns prev value, operator=()
//       must be initialized to false using ATOMIC_FLAG_INIT;
//       can be used to implement spin lock
//       spin lock:
//          alternative to using mutex or condition var
//          essentially an infinite loop
//          keeps spinning util a condition becomes true
//          std::atomic_flag to implement basic spin lock: loop condition is the value of the flag
//            each thread calls test_and_set() in a loop
//            if this returns true, some other thread has set the flag and is in critical section, iterate again
//            if returns false, this thread has the flag, exit the loop and proceed into the critical section
//            after critical section clear the flag
//            while(flag.test_and_set()){} /*critical section*/ flag.clear();
//          spinning thread remains active, a mutex block the thread
//          it can continue immediately when it gets the lock, with mutex thread may need to be reloaded or woken up
//          processor intensive: only suitable for protecting very short critical sections and very low contention
//          performance can be heavily impacted if spinning threads interrupt each other
//          usually used only in OS and libs
//          often used to implement std::mutex (hybrid mutex)


std::atomic<int> curr = -1;

void threadd()
{
	curr+=1;
}



int main()
{
	std::vector<std::thread> threads;
	for (int i = 0; i <= 10; i++)
		threads.push_back(std::thread(threadd));

	for (int i = 0; i <= 10; i++)
		threads[i].join();

	std::cout << curr << std::endl;
	return 0;
}
