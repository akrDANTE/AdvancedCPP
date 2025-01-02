#include<iostream>

// constructor
// can initialize data members within definition like
// class ref { int temp{2}; bool door_open{false};}
// delegating costructor can call other constructor of the class
// delegating constructor exapmle: constructor(argset1): constructor(argset2) {}

//copy constructor
// takes one argument an object of the same class
// Test(const Test& other);
// called when passed to argument by value/ may not always be called due to compiler optimizations
// default copy constructor is good enough usually, but need to write custom when some resource is managed by the object
// std::literals ==> used for "world"s string literal 

// assignment operator ==> return the reference to the current object
// correct signature : Test& Test::operator =(const Test&);
// called when an existing object is assigned(not initialized)
// x = y = z; x and y will have same value as z
// write when the class manages a resource
// same effect as calling destructor and then copy constructor

// synthesized member functions : compiler generated member functions
// constructors, copy constructor, assignment operators, destructor, move constructors
// always write own member functions when pointers/resource management are involved

// copy elision
// this is the form of optimization in which compiler misses out the call to copy constructor
// int x{7}; int y{x}; if x is not use after y then compiler can rewrite int y{7}; directly
// occurs during temporary variables copying
// to turn off copy-elision use -fno-elide-constructors
// in visual c++ disable all /Od optimizations 
// return value optimizations, name return value optimization

// conversion operators
// converts object of a class to another type/ kind of custom casts for classes
// syntax : operator int() const {return i_data_member;}
// useful when we want to write code like : Test test; int y = test + 5;
// implicit conversion : compiler does conversions automatically
// to make conversion explicit : explicit operator int() const {return data;}
//    then static_cast<int>test to convert
// conversion to bool is bypassed i.e. explicit will not stop compilation
// constructor with single arg works as implicit conversion operator
//     allowing Test test = 4;
// make constructor explicit to avoid implicit conversion

// force default constructor: Test() = default;
// to make uncopyable object make copy constructor and assignment operator private
// in c++11 delete copy constructor and assignment operator using Test(const Test&) = delete;

// unary operators are usually member funcs, binary ones are usually non member funcs
// overloading means giving different meaning to already existing symbols
// assignment operator, equality ==, inequality operator != , less than < , function call operator ()
// cannot overload && and ||, and &  and , operator, :: and . operator, .*operator, ternary as well

// avoid using friend keyword as it decreases encapsulation and can be unsafe

// binary operator works better with non member function as external function can call constructor and operator
// if operator changes the state of the obj, implement as member function
// if operator is tightly bound to type like * then also implement as member func
// members : = [] () ->
// if binary operator might require type conversion then use non member
// input/output << and >> operators should be non member

// + operator
// T operator +(const T& lhs, const T& rhs) non member
// += operator: T& operator +=(const T& rhs); member
// bool operator !=(const T& lhs, const T& rhs)
// bool operator <(const T& lhs, const T& rhs) ==> std lib uses < operator for sorting and ordering in containers
// make sure < operator is consistent with equality and inequality operator
// sort(std::begin(names), std::end(names))
// ++p ==> p += 1; p;
// p++ ==> temp = p; p += 1; temp;
// better to use prefix version for loop counters

// functional programming involves a tree of function calls which transform data
// callable objects are used to implement functional programming in c++
// function call operator makes a class functor(callable object)
// some_type operator() (...); 
// can be used to create generators in c++

// ostream& operator <<(ostream& os, const Test& t) const { t.print(os); return os;}

// operator precedence order in c++

// std::complex is part of C++11

// if we define a custom constructor then compiler does no synthesize default construct
// we need to explicitly tell compiler by writing Test() = default