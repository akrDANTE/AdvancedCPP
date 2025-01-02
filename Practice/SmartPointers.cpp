#include<iostream>
#include<memory>
#include<string>

// drawbacks of traditional pointers
//		no concept of ownership(anyone can assign, reassign, overwrite, invalidate it)
//      no destructor(allocated  memory can be released twice or not at all)

// in c++11 we can avoid traditional pointers
//     with stack memory we can use references instead of pointers
//	   we can use vector instead of variable sized arrays
//	   we can use smart pointers for working with heap memory
//     for dynamic binding, we can use smart_pointers or refrences

// smart pointers are classes which encapsulate allocated memory follow RAII
// pointer arithmetic not allowed, only accessed through public member functions
// unique_ptr (object cannot be copied or assigned to but can be moved using std::move)
// shared_ptr (can share allocated memory with other shared_ptr object), more overhead than unique_ptr

// unique_ptr: <memory> move only class
// best replacement to traditional pointers
// template class with a traditional pointer data member
// unique_ptr<int> p1 { new int(42) };
// unique_ptr<int []> p2 { new int[6] }; //use vector instead
// c++14 has  auto p1 { make_unique<int>(42) } // uses perfect forwarding
// does not automatically decay into array
// setting p1 = nullptr will release the memory and make pointer invalid
// we can pass unique_ptr objects by pass by move using std::move(ptr) as function arg;
// we can return unique_ptr
// polymorphism is when we use a base class object to represent a derived class obj, requiring pointers in c++
// unique_ptr<Base> pbase{ make_unique<Derived>() };
//    pbase cannot be aliased, cannot be accidentally reseated, overwritten, invalidated
//    delete called automatically, can't be used after deletion
// factory pattern : when a function creates the object and the type of the new object will depend upon arguments to function
//     useful when working with class hierarchies, create a child object and return it through pointer to base
//     all code to create objects in the hierarchy is in a single place
//     easy to extend if new child classes are added
//     can use args to choose which child class type to create
// if we want to handle delete ourselves we can provide a callble object as deleter
//   it will be invoked by the destructor instead of the delete
// auto custom_deleter = [](ptr_type* ptr) {do whatever required};
// deleter is part of the unique_ptr's type, we need to give it as optional template parameter
// we can use decltype(var_name) to automatically deduce the type of variable 

// handle-body pattern
// in OOP, we aim to seperate the interface from the implementation
//    clients do not need to know inner details of the class
//    clients do not need to modify their code if the implementation changes
// in c++ we use header file for interface and cpp file for implementation
// handle body pattern splits the class into two classes:
//    the handle is outer class that provides the interface to clients
//    the body is an inner class that provides the implementation
//    when client creates a handle object handle creates a body object
//    when client calls a member function on handle object, the call is forwarded to the body
// similar to adapter design pattern
// handle.h defines the handle class with public member functions only
// body.h defines teh body class teh full class definition
// client only include handle.h
// if implementation details change, this only affects body.h, clients do not need to be recompiled
// in dynamic linking we create portable dll/shared obj

// pimpl(pointer to implementation) idiiom " also known as compiler firewall
// handle.h declares body class but does not define it
// clients know only its name: class body;
// handle contains pointer to body: Body *body;
// handle follows RAII
// disadvantage : requires extra memory allocation for body obj, pointer deref required, loading shared lib increase progs start-up time
// used in large projects, heavily used in QT
// could be used to write standard container class

// refrence counting
// integer used to store the number of objects which are sharing the resource
// allocated on heap
// when new object created increment, when destroyed decrement, when become 0, destroy and free memory
// copy constructor, assignment operator needs to be handled properly with taking self assigment
// move operators are fine but may need to handle sometimes

// shared_ptr <memory>
// allows objects to share a memory allocation
// when shared_ptr is copied or assigned there are no memory allocations
// when the last shared_ptr object is destroyed the allocated memory is released
// share_ptr contains two private members allocated memory pointer and control block
// control block contains the refrence counter
// make_shared<int>(24) recommended; shared_ptr<int> p1{new int(42)} // less efficient
// all operations supported by unique_ptr
// refrence is atomic, shared_ptr is thread safe but very slow

// weak ptr
// it provides a safe way of aliasing a shared_ptr
// this avoids the problems with traditional pointers of dangling aptr = bptr; delete bptr; aptr is dangling
// weak_ptr cannot access the shared memory directly, it has to be onverted back to shared_ptr
// auto ptr{make_shared<int>(36)}; // ref count 1
// weak_ptr<int> wptr = ptr; // ref count still 1
// ptr = nullptr;
// to convert back to shared_ptr: shared_ptr<int> sp1 = wptr.lock();
// if(sp1) {} ==> to check if sp1 is not nullptr
// or we can copy like this : shared_ptr<int> sp2(wptr);
// this will throw std::bad_weak_ptr if invalid
// to prevent data race lock() is atomic operation
// we can use weak_ptr to check for validity of shared_ptr
// applications:
//   cache implementation: data stored in share_ptr objects, cache holds weak_ptr to data
//   use lock to retreive the data, original data returned if not expired
//   otherwise need to fetch again
// cyclic refrences: when object a has shared_ptr to object b, and object b has shared_ptr to object a
//    this makes it impossible to reference count to go to 0
// use weak_ptr to avoid cyclic refs

int main_smartptrs()
{
	std::cout << " main smart pointers: " << std::endl;
	int x{25};
	int* ptr = &x;
	auto custom_deleter = [](int* ptr) { std::cout << "custom deleter called" << std::endl; };
	std::unique_ptr<int, decltype(custom_deleter)> p1{&x, custom_deleter};
	return 0;
}