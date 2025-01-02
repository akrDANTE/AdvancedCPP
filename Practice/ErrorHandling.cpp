#include<iostream>


// situations which arise at runtime when the environment does not behave as expected
// error communication : 
//    communicate with user, avoid information which is not helpful to user, only exit the program as last resort
// errors can be handled where they occur
// the error needs to be passed from the place where the error occured to the code that handles it

// in C we use error codes returned by functions which represent type of errors
// error codes make code more complicated and hard to maintain
// error codes do not work well with callbacks
// c++ constructors cannot return error codes
// c++ provides exceptions: code which could cause a run-time error is put inside its own scope
// if an error occurs, create an exception object and exit the current scope
// find a handler for the exception depending on excetion type, handler processes the exception object
// programmer specifies the type of object and provide handler
//     when to create exception object
// if there is no suitable handler, programmer terminates immediately
// constructors can throw exceptions

// std::exception is a base class of inheritance hierarchy
// it has number of sub-classes including std::out_of_range, std::bad_alloc
// it has what() virtual member function which returns cstring describing the error

// try { //runtime_error_prone_code } 
// catch (const exception& e) { e.what() } will handle all subclasses of the exception class
// in case of uncaught exceptions the program will try to find handler in caller's caller and keep going up the call stack till it finds one
// if not found program terminates
// if we want to handle exceptions with different static types, we add different catch blocks per exception
// exception will be handled by the first catch block that can handle it
// keep base class at the bottom
// in a catch block : avoid allocating memory, creating new variables, calling functions, only use built in types if possible
//     because program may not be stable or consistent state
// catch(...) ==> catch all exceptions without knowing it
// when an exception is thrown: 
//   thrown object is copied into special are of memory which is setu pby the compiler, it is accesible by any catch block which can handle the object
//   every local variable in scope is destroyed
//	 program leaves the current scope immediately and start looking for suitable catch block
//   if not found then again all local  variables are destroyed and current scope is left and so on.. this is called stack unwinding
//   handler can rethrow the exception using throw;
// exception -> bad_alloc, logic_error, runtime_error, bad_cast, bad_weak_ptr, 
// logic_error(can be prevented by programmer) -> future_error, out_of_range, domain_error, invalid_argument, length_error
// runtime_error -> overflow_error, underflow_error, range_error, system_error, ios_base::filure
// ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit to enable exceptions for streams
// destructors should never throw exceptions

// custom objects should be as minimal and light weight as possible
// const char* what() const noexcept override {}
// class custom_exception: public std::out_of_range {
//      default_constructor()
//		custom_exception(const char*)
//      custom_exception(const std::string&)
//      copy_constructor = default // if no data members in class
//      assignment_operator = default // if no data members
//      override what() if required;
// }
// 

// exception safety:
// basic : no resources leaked, no open file blocked, or memory leaks
// strong : if exception, program reverts to its previous state, as if no operation happened
// strong exception gaurantee has transactional semantics, all iterators or refs remain good
// no throw : no exception is thrown
// noexcept keyword : function will not throw/ helps more optimized code
// noexcept is inherited in derived class
// destructor is implicitly noexcept

// make things explicit whenever possible

// overload swap in case of custom objects

// alternative approach to writing an assignment operator
//    create local var which is copy of the arg
//    swap the contents of the local var with the this object
//    return this object which now contains the correct values
//    local var is then destroyed




int main_except() {


	return 0; 
}