#include<iostream>
#include<algorithm>
#include<chrono>
#include<functional>
#include<string>

// <chrono>
// handling times and dates
// <ctime> low-level and poorly designed
// clock() => returns number of clock ticks since the program started
//    stored in clock_t, precision usually in microsecond, can be used for intervals upto few minutes
// time() takes a variable of type time_t by address
//    sets the argument to number of seconds since 1970
//    can be used for longer intervals(upto several decades)
//    precision is 1 second
// std::chrono namespace:
//   clock => start date(epoch) and tick rate (C time, epoch (1970) tick rate (once per sec))
//   time point => number of clock ticks since the epoch, at a given point in time
//   duration => an interval between two time points, measured in clock ticks
// duration types in chrono namespace:
//    hours, minutes, seconds, milliseconds, microseconds, nanoseconds
//    default initialized as undefined
//    constructor takes single integer
//    c++14 provides std::literals for these as 5h, 10min, 2s, 20ms, 50us, 80ns 
//    cannot be printed directly
//    count() member function returns the numeric value of the duration
//      should only used for i/o and interfacing with legacy code
//    can perform addition and subtraction
//    construct and conversion operators are explicit
//    conversion between durations can be done implicitly done if there is no loss of data
//    duration_cast<seconds>(5043ms); can be used if we don't care about loss of data
// clocks in chrono:
//   system_clock : measures wall time using hardware system clock
//	     system_clock::now()
//       similar to C library clock
//       best for interactive use (relate to calendars, watches, phones etc)
//       matches user's view of time
//       not suited for measuring time intervals (can be corrected due to various reasons)
//   steady_clock : idealized clock which only goes forward one tick at a time, software
//       steady_clock::now()
//       best clock for measuring time interval
//   high_resolution_clock : clock with shortest tick period supported by the system
//      usually an alias for system_clock or stead_clock
// time_point:
//    represents a point in time
//    it's object is associated with particular clock
//    time_points can be subtracted result will be duration
// sleep_for(duration) defined in  <thread>
//     actual duration may be longer(depends on scheduling)

// std::bitset <bitset> for bitwise manipulation of objects
// bitset<num_bytes> b1{"01011000"}, b2{0xae}, b3{0b10101010}; // b3 allowed in c++14
// to_ulong, to_ullong, to_string
// size(), we can subscript to access individual bits
// index 0 is the least significant bits [rightmost]
// test() accesses a bit with bounds checking // throws out_of_range
// ~, &, | , ^, >>, << supported
// set(), reset(), flip() //given no arg will apply to all bits
// all(), any(), none(), count() //for set bits

// tuple <tuple>
// useful for returning multiple values from a function, handling variadic templates, lightweight storage of data points
// can have any number of elements but should be fixed
// elements are accessed by index not by member name
// tuple<double, int, string> numbers(1.0, 2,"three"s) or auto numbers {make_tuple(1.0,2,"three")} 
// to access tuple members we use templated std::get
// auto x = get<index>(numbers)
// get<1>(numbers) = 3 to set, we can use type(get<int>) if unique
// tie(d,i,str) = numbers // store all elements in variables
// we cannot use auto to deduce the return type
// c++17 allows compiler template  arg deduction tuple t{1,2.0,'c'}
// we can use structured bindings with c++17 auto [a,b,c] = t;
// c++17 has std::apply(func_name, tuple(arg1, arg2, arg3..)) calls func(arg1, arg2, arg3)
// c++17 allows pass tuple as constructor arguments like
//    auto test = make_from_tuple<Test>(tuple(1,2.0, "three"s));

// Unions
// union is compound data structure
// each member must have a distinct type
// all members are stored at the same address
// only one member can be in use at a time
// useful if we are processing raw data which could be one of several types
// all members are public by default
// can have member functions
// when we assign to a member that member becomes active
// unions can be made safer by adding a "tag" member which indicates member in use
// tagged union requires programmer to check before accessing a member
// always make computer work whenever possible
// to fix create wrapped tagged union : wrap the tagged union inside a class
// c++17 provides std::variant
// similar to wrapped tagged union but are type safe, can have different alternatives with same type,
//   automatically calls constructors and destructors when required, simpler to use
//   define in <variant>
// variant<char, int, double> v; v = 'z';
// to get an alternative from a variant we call std::get,
// get<char>(v) or get<0>(v) 
// holds_alternative<double>(v) to check if the given type is in use
// useful for parsing source code, ini file, language implimentation
// return values, error handling
// polymorphism // virtual function implementation

// Mathematical types
// std::valarray => fixed size, easier syntax for numerical ops
// better to use third-party libs (Eigen, Blaze, Armadillo)
// std::complex in <complex> complex number class, complex<double> q{3.0, 4.0}
// number literals ==> 2i complex object with real part 0 and imaginary part 2
// abs(q) magnitude
// arg(q) returns phase angle(in radians)
// conj(q) // invert imaginary part
// exp, log, pow, sqrt, sin, cos, tan, inverse, hyperbolic versions

// Bind
// std::bind() in <functional>
// bind() takes a callable obj as its first arg, and performs a partial function call
// it binds the remaining args to this object and returns a new callble
// auto match_cat = bind( match, std::placeholders::_1, "cat"); // bind "cat" to match and return match_cat
// useful when passing callable objects to std::lib which only take one argument
// use lambda when possible

// callable objects
// supports () operator
// sometimes we want to work with different callable objects which have the same signature
// c++11 provides std::function in <functional>
// function<signature> func_obj_name; ==> example function<bool(const string&)> match;
// implemented using inheritance
// std::function performs type erasure: objects original type cannot be recovered
// we can decalre a function arg as type std::function
// we can create a container whose elements are of type std::function
// has runtiime overhead
// only use for polymorphic function object

// member function pointers
// may need to provide the this pointer
// member function pointers cannot be called directly, must be explicitly dereferenced
// void (ClassName::*pointer_name)(int, const string&) = &ClassName::memberFunc;
// to call a member function pointer we nned an object, then we access the pointer as a member of the object then we deref it
// Test test; (test.*pfunc) (24, "hello"s);, for pointer (test->*pfunc)(24, "hel"s);
// use auto pfunc = &Test::do_something; or using PfuncType = void(Test::*)(int, const string&);
// c++11 has std::mem_fn() in functional which takes member function pointer object as arg and returns a callable obj
//    auto f = mem_fn(pfunc); f(obj_name, 42, "hello"s);
// we can use member function pointer and bind to generate callable object
// only used in concurrency (need to run member functions in their own thread)
// runtime decision making
// choose which object is used
//    use bind() to bind the args to a member function call
//    use a placeholder for the caller to provide the object
// choose which member function is called
// use switch or if/else to make the decision
// state machines and callbacks

// Interfacing to c
// OS API, DB API, 3rd party libraries and frameworks, languages with foreign function interfaces
// simplest solution compile everything with c++ compiler
// C and C++ compiler used must be compatible
//  same obj file format, same function call conventions, same word size(32 or 64)
// if c++ lib features are used, then c++ compiler needs to be used for linking
// take care of name mangling, name mangling is done to give different names to different func overloads
// to make c++ binaries compatible with C, we use extern "C" directive
// this tells compiler not to mangle the function name
//    extern "C" {int func(int x)// #include "header.h"};
// conditional compilation
//   the interface header will be processed as both c and C++
//   it may contain things which are not valid C
//   we use #ifdef __cplusplus for conditional compilation to hide things from C compiler
// c++ -c add.cc // -c gives object file only not full binary

// runtime type information
// typeid() returns information about dynamic type of its arg defined in <typinfo>
// mainly used in comparisons circle d; shape *pShape = &d;
//    if (typeif(*pshape) == typeid(circle))
// type_info is is a class defined, typeid() returns a type_info object which contains info about the dynamic type of the object
// type_info::name() returns C-style string returns compiler specific name for the type
// type_info::hash_code() returns a unique number for each dynamic type
// dynamic_cast convert pointer to base to a pointer to derived
//   if cast fails then returns nullptr
// one legitimate use of dynamic_cast is for calling a member function that only exists in child class
//   throws bad_cast 

// multiple inheritance
// adds complexity, some languages do not support it
// can be useful for writing "mix-in" classes
// class Mouse : pulic HardwareDevice, public TouchResponder {} 
// a derived class object in memory is stored as the base class objects followed by the derived class part
// the base class constructor is called in order they were listed, destructors in reverse order
// if two base classes have function with same name, then ambiguos call error may occur which can be avoid by writing same function in derived

// virtual inheritance
// in multiple inheritance it is possible for a class to inherit from a base class twice
// we can use static_cast<BaseClass *>(&derived) to get a pointer to base part of the class
// virtual inheritance can be used to fix above issue like
//   class BaseChild : public virtual Base{}; class BaseChild2 : public virtual Base{};
//   class derived: public BaseChild, public BaseChild2 {};
//   now there will be only single Base object part in derived class

// inline namespaces
//  these namespaces are defined as inline namespace B {}
//  these make it so that the symbols inside inline namespace appear to be part of outer namespace, so they can be used directly using outer::
//  useful for working with different version of code

// attributes
// these are c++ implementation dependent keywords which are directions to compiler to behave in certain ways
//   #pragma, __attribute, __declspec
// give extra information to the compiler, they should not be used to extend the language or change the meaning of the program
// [[ noreturn ]] void func_name(); // function does not return
// [[ gnu::always_inline ]] // namespaces can be used
// [[ deprecated("Use version 2.0") ]] void func();// can take args
// alignas(16) used for memory alignment
// c++14 added deprecated
// c++17 provides [[fallthrough]]
// c++17 [[nodiscard]] // function whose return value should not be ignored
// struct [[nodiscard]] test{}; // functions which return test will be nodiscard
// c++17 [[maybe_unused]] char data[128];// remove unused variables warning


using namespace std::literals;

bool match(const std::string& s1, const std::string& s2)
{
	std::cout << s1 << "  " << s2 << std::endl;
	return true;
}

int main_misc()
{
	auto match_cat = std::bind(match, std::placeholders::_1, "world"s);
	match_cat("hello"s);


	/*enum class TokenType {CHAR, INT, DOUBLE, FLOAT};
	union Toe {
		char c;
		int x;
		float y;
		double d;
		TokenType type;
	};


	Toe t;
	t.c = 'Z' ;

	std::cout << t.c << std::endl;
	t.x = 5;
	std::cout << t.x << std::endl;*/
	
	return 0;
}