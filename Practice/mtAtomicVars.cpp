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
