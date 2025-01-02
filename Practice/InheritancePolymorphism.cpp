#include<iostream>


// derived classes(triangle) are specialised version of the base class(shape)
// relationship between classes at different levels in teh hierarchy is called inheritance
// class Aeroplane: public Vehicle // here aeroplane can access any public members of vehicle
// an object of a derived class is stored in memory as a base class object followed by derived class
// when a derived class object is created the base constructor is called first then derived constructor
// when it is destroyed derived constructor is called first then base
// Aeroplane() : Vehicle() {} // initialize the base
// in case of args, each class should initialize its own members

// we can call parent's member function in our own functions
// protected access specifier allows member access only to derived class, not elsewhere
// only overloaded function in a derived class is callable, not the inherited one
// one solution to above issue is to define other overloads manually
// other solution is to use == using Vehicle::original_function; // compiler generates for us

// pointers/ references
// base pointer/ref can have pointer of derived but not other way around
// static type is the type used in the variable declaration 
// dynamic type is the type of the variable in memory
// dynamic type is only used in case of pointer for base class in c++
// compiler does not decide it during compile time which function to call,
// it is decided during runtime, to allow this we need to declare the member function as virtual
// when object is passed by value static type is always used

// static binding : when compiler decides at compile time which function to call 
// dynamic binding : when compile puts some extra code to decide at runtime which function to call
// if a child class reimplements a virtual function is said to "override" it
// dynamic binding does work in case of function overload
// override keyword ==> explicitly write to make sure override not overload
// final keyword: final class cannot be derived from class circle final : public shape 
// a final member function cannot be overridden in derived class

// if destructor is not virtual, static binding will be used, so only base destructor will be called
// make destructor virtual if calling destructor for derived class when using pointer
// for base make virtual ~Base = default or ~Base() {}
// making virtual destructor will allow to call destructors in order using dynamic binding
// whenever there is virtual function always make destructor virtual as well

// base class is the interface which contains all the common functionality
// derived class implements / overrides the functions in base in concrete way specific to each class
// to make interface use : virtual void func() = 0; pure virtual func
// this makes a class abstract and it's objects cannot be created 
// when the compiler encounters a class which has virtual member it creates vtable virtual member function table
// and also generates some extra code which at runtime checks the dynamic type of the object
// and uses the vtable to call the correct version of the function
// only use virtual member function only when absolutely necessary

// parametric polymorphism : vector<int> int is a parameter
// subtype polymorphism : Shape : circle, triangle using virtual functions
//     an object of a type can be replaced by an object of its subtype
// we can add new types without having to write extra code to handle it
// many problems are better solved by composition: to use a class's interface make it a data member
// only use inheritance if you need "is-a" relationship


class Vehicle {
public:
	Vehicle():speed(0) {}
	Vehicle(int speed):speed(speed) {}

	virtual void accelerate()
	{
		std::cout << "Accelerate default " << std::endl;
	}

	virtual void accelerate(int al)
	{
		std::cout << "acclerate alpha " << al << std::endl;
	}

private:
	int speed;
};

class Aeroplane : public Vehicle {
public:
	Aeroplane(): Vehicle(), height(0) {}
	Aeroplane(int speed, int height): Vehicle(speed), height(height) {}
	using Vehicle::accelerate;
	void accelerate(std::string beta)
	{
		std::cout << "accelrate beta " << beta << std::endl;
	}
	void accelerate()
	{
		std::cout << "kamehamehaa" << std::endl;
	}
private:
	int height;
};

class Car : public Vehicle {

};

class Base {
	int m;
public:
	Base(int m): m(m) {}
	virtual void print() {
		std::cout << "hello base" << std::endl;
	}
};

class Child : public Base {
public:
	Child(int m) : Base(m) {}
	void print() {
		std::cout << "hello child" << std::endl;
	}
};

class GrandChild : public Child {
public:
	GrandChild(int m):Child(m) {}
	void print() {
		std::cout << "hello grandchild" << std::endl;
	}
};

void print_class(Base& b)
{
	b.print();
}

int main_ip()
{
	Base b(3);
	Child c(4);
	GrandChild gc(5);

	print_class(b);
	print_class(c);
	print_class(gc);
	/*Aeroplane a1;
	Vehicle* v = &a1;
	a1.accelerate();
	static_cast<Aeroplane*>(v)->accelerate("hahah");
	if (dynamic_cast<Aeroplane*>(v))
	{
		dynamic_cast<Aeroplane*>(v)->accelerate("hahaha");
	}
	v->accelerate();*/

	return 0;
}