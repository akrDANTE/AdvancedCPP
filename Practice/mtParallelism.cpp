#include<thread>
#include<future>
#include<mutex>
#include<iostream>
#include<algorithm>
#include<numeric>

// Parallelism
//   concurrency is when tasks are conceptually distinct, seperation of concerns, can run on single core
//     these tasks often overlap in time, concurrency is future of program structure
//   parallelism is when tasks are identical, they run all at the same time, on multiple cores
//     tasks run independently of each other, parallelism is a feature of the algo being run
//   programmer specifies how to parallelize the work, divide the data into four parts, then start four threads to process each part
//   can produce better performance, not scalable
//   mainly useful when writing for specific hardware e.g. a game console
//   or if the work naturally divides into a fixed number of tasks
//   implicit parallelism : left to the implementation, usually the best option
//   
//   Task parallelism: aka Thread-level Parallelism(TLP)
//     split a large task into smaller tasks
//     subtasks are run concurrently on seperate threads
//     example : DB server runs many threads to reduce latency
//      a thread is waiting to access data on disk, other threads can do useful work
//     fork and join paradigm

//   Data parallelism: aka vectorization/vector processing
//      distributed data: data set is divided up into several subsets
//      process all subsets concurrently
//      each thread works on one of the subsets
//      a final reduce step which collects result for each subset
//      vectorization paradigm
//      very common in numerical processing
//      used internally in GPU
//      single instruction/Multiple Data architecture "SIMD"
//      can improve performance by increasing data locality(data is stored where it is processed)
//        all the data each core needs is in the cache
  
//   Pipelining
//      dependent tasks
//      if A,B and C are processing a stream of data
//         a processes first item in stream
//         B starts which A's output
//         A starts processing the next item
//      perform dependent tasks sequentially
//      process data concurrently
//
//   Graph parallelism
//     similar to pipelining, but with an arbitrary graph of dependencies

// Execution policies
//   sequential : single instruction processes one data item
//     all operations are performed on single thread which calls the algo
//     operations will not be interleaved, may not necessarily be executed in specific order
// 
//  vectorized : a single instruction processes several data items, requires suitable data structure and HW support
//     unsequenced execution : operations are performed on a single thread(C++20)
//     guarnatees operations will not be interleaved
//     cautions : operations may not necessarily be executed in specific order
//       programmer must avoid any modifications of shared state between elements or between threads
//       memory allocation and deallocation
//       mutexs, locks and other forms of synchronizations
// 
//  parallellized : several instructions each process one data item, at the same time, requires suitable algo
//     operations performed in parallel across a number of threads
//     may include the thread which calls the algo
//     guarantees an operation will run on the same thread for its entire duration
//        operations performed on the same thread will not be interleaved
//        may not necessarily be executed in specific order
//     cautions operations performed on different threads may interleave
//        programmer must prevent data races
// 
//   parallelized + vectorized : several instructions each process several data items, at the same time 
//                  requires suitable algo, DS and HW support
//      operations performed on in parallel across a number of threads
//      cautions:
//        no specific order, ops performed on same thread may be interleaved
//        an operation may be migrated from one thread to another
//        programmer must avoid data races and modifications of shared state between elements/thread
// 
//   c++17 allows choice of execution policy for an algorithm call(not all compilers support it)
//      execution policy is just a request, may be ignored
//   <execution> std::execution namespace
//     std::sort(std::execution::seq, vec.begin(), vec.end());
//     std::execution::par, std::execution::par_unseq(parallel+vec), std::execution::unseq(vec)

// Algos and Execution policy
//   c++14 -> c++17(parllelized support policies)
//   accumulate -> reduce
//     reduce will not give correct answer if : reordering/regrouping the operations change result
//        operators must be cummutative, associative
// 
//   partial_sum -> inclusive_scan, exclusive_scan
//     inclusive_scan == same as partial sum with execution policy support
//     exclusive_scan == ignores first element and uses the arg instead of first element
// 
//   transform + inner_product -> transform_reduce : {1,2,3} transform_reduce {1,2,3} = 1*1 + 2*2 + 3*3
//      transform_reduce overload : we can replace * operator by transform function and we can replace + operator by reduce function
//      transform_reduce(se::par, begin(v1), end(v1), begin(v2), 0, reduce, transform)
//   in c++17 if exception is thrown, std::terminate() is called and program is terminated
//   extra overhead for execution policy as threads may start and needs to be managed



int main()
{
	
	
	return 0;
}