#include<iostream>


// with move semantics we can save time by moving data in and out of function calls
// if the source object is an rvalue, its data can be moved into the target instead of being copied
// this makes source object empty

// lvalue is something which can appear on the left side of assignment ()
// rvalue is something which can only appear on the right side of assignment (2, func_return_value)
// in c++ lvalue represents a named memory location, we should be able to take its address using &
// anything else is rvalue 
// lvalues can be passed by value, address, refrence
// rvalues can be passed by value, const refrence
// pass by move : the argument can be moved if obj is rvalue and is movable else copied
// lvalue reference is pointer to the object
// int&& x; (this helps compiler to check if x is movable rvalue) rvalue refrence
// std::move(y) // y is cast to an rvalue, should be done when we don't care about the value of y after this statement
// std::move(y) will move y's data into the function argument
// should be done if y's data is expendable: y's data may be empty or unusable
// if we want to use y again we must reassign some data to it.
// string&& r{string{"Temp"}};
// argtype: 
//	lvalue : pass an lvalue allowed ,  function has copy of the passed arg, passing moveable rvalue, function owns the passed object data
//  lvalue ref: can pass lvalue, but not rvalue, function can modify passed object through ref
//  const lvalue ref : we can pass lvalue or rvalue, function cannot modify passed arg
//  rvalue ref : we can pass moveable rvalue, but not lvalue, function owns the passed arg
 
// characteristics of lvalues:
//		lvalues represent persistent objects
//		these occupy memory which is accessible to the programmer(either stack or heap)
//		these remain valid until they go out of scope or are deleted
//			local , global, static variables, function args

// characteristics of rvalues:
//		rvalues are stored in locations which are not accessible to programmer, such as processor registers
//		literls like 2 or 'c',  temporary objects (destroyed in same statement in which they are created)

// c++17 has 3 value categories
// literals are called pure rvalues prvalues, these have no name and cannot be referred to again
// temp objects represent an object and their data can be moved, known as xvalues
// lvalues
// every expression has a type and a value category
// lvalues and xvalues are objects, thier dynamic type can be different from their static type
// collectively(lvalues and xvalues) are called glvalues(generalized)

// Move operators
// we can overload function so that it behaves differently depeneding on whether its argument is moved
// func(const myclass& obj); // called when lvalue is passed
//  func(myclass&& obj); // called when rvalue is passed
// two of the most useful function to ovrload this way are the copy constructor and assignment operator
//   moving instead of copying is very efficient
// move constructor and move assignmnent operator // automatically called if movable rvalue
// stl containers will only call an element's move operator if it is noexcept 
// derived operators must call corresponding versions of the base class
// for built in types moving is equivalent to copy
// when using move with heap data, make arguments pointer to nullptr to avoid crash to invalidate the argument object
// move and swap: temp(std::move(arg)), swap(*this, temp), return *this;

// move-only objects are which can only be moved and not copied
// to create such objects delete copy opertors and constructors and only implement move operators
// fstream and iostream, smartpointer classes, some multithreading classes are moveonly
// c++14 allows capture by move in lambdas [vs = std::move(strings)]

// if class needs a destructor, then copy /move operators also needed
// to make class immovable delete copy operators

// forwarding refrences
// refrence to refrence to int collapses into refrence to int
// template<typename T> func(T&& x) ==> x is now a forwarding reference/ universal ref
// x can be bound to rvalue or lvalue
// if argument is lvalue type of x will be lvalue refrence
// if rvalue is passed then x will be a rvalue refrence
// write a forwarding reference constructor instead of two copy and nmove consttructors

// perfect forwarding
// when a function passes some or all of its arguments, it's said to forward them
// perfect forwarding means the properties of passed object are preserved
// make_pair()
// perfect forwarding is used to write functions which call constructors
// if a passed object is an rvalue the more efficient move constructor is called
// std::forward<T> casts its argument to rvalue reference, if arg is not lvalue ref

class animal {
public:
	animal() = default;
	animal(const animal& a): c(a.c) {
		std::cout << "Animal copy constructor called" << std::endl;
	}
	animal(animal&& a) noexcept: c(a.c) {
		std::cout << "Animal move constructor called" << std::endl;
	}
	animal& operator=(const animal &a) {
		std::cout << "Animal copy assignment operator called" << std::endl;
		this->c = a.c;
		return *this;
	}
	animal& operator=(animal&& a) noexcept{
		std::cout << "Animal move assignment operator called" << std::endl;
		if (this != &a)
		{
			this->c = a.c;
		}
		return *this;
	}
private:
	char c{ 'a' };
};

class Test {
public:
	Test():i(2), a() {
		std::cout << "Test constructor called" << std::endl;
	}
	~Test() {
		std::cout << "test Destructor called" << std::endl;
	}
	Test(const Test& other):i(other.i), a(other.a) {
		std::cout << "copy constructor called" << std::endl;
	}
	Test(Test&& other) noexcept :i(other.i), a(std::move(other.a))
	{
		std::cout << "move constructor called" << std::endl;
	}
	Test& operator=(const Test& other)
	{
		this->i = other.i;
		std::cout << "copy assignment operator called " << std::endl;
		return *this;
	}
	Test& operator=(Test&& other) noexcept
	{
		std::cout << "move assignment operator called " << std::endl;
		if (this != &other)
		{
			this->i = other.i;
			this->a = std::move(other.a);
		}
		return *this;
	}
	void print() const {
		std::cout << "test " << i << std::endl;
	}
private:
	int i;
	animal a;
};



void func2(Test t)
{
	Test tcopy;
	tcopy = std::move(t);
	tcopy.print();
}


void func(int&& y)
{
	std::cout << y << std::endl;
	return;
}






int main_move()
{
	std::cout << " move semantics main : " << std::endl;
	Test t;

	std::cout << "Entering func2" << std::endl;
	func2(t);
	std::cout << "returned from func2" << std::endl;
	t.print(); // this should not be done
	/*int x = 3;
	int* y = nullptr;
	func(2);
	func(std::move(x));
	std::cout << x << std::endl;*/
	return 0;
}