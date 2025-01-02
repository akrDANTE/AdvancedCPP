
#include<iostream>
#include<string>
#include<tuple>

//#define Max(x,y) ((x) > (y) ? (x) : (y))

// compile time programming
//  the compiler executes code at compile time
//  result of computation is available in the program
//  no run-time overhead
//  compile-time programming could be done in C
//   Uses pre-processor "macro functions"
//   copy and paste with substitution
//   no type info
//   does not understand c++ syntax
//   example : #define Max(x,y) ((x) > (y) ? (x) : (y))

// template programming features
//   support generic programming
//   turing complete programming language: means any problem can be solved using templates
//     template parameters can represent state variables
//     recursive instantiatin can simulate loops
//     template specializations to implement control flow
//     integer operations to calculate results
// Template Metaprogramming:
// making decisions at compile time for efficiency or portability
// domain specific programming(new programming language)
// complex software patterns and concepts
// mostly uses class templates rather than functions
// by convention:
//   members that represent numeric results or other values are named "value"
//   members that represent types are named "type"
// Makes heavy use of template specialization
// use of "type traits" to get information about the properties of types, e.g is_arithmetic<T>
// <type_traits> // is_same<std::string, T>::value
//  is_arithmetic<int>::value // true
//  is_floating_point<int>::value // false, is_class, is_pointer
// c++11 provides constexpr which is code written in c++ but is executed by compiler

// constant expressions
//  evaluated at compile time and cannot be changed
//  literals, value computed from literals, value computed from other const exprs
//  const variable cannot be modified after being initialized
//  constexpr indicates that a variable is constant expressions
//    means will be evaluated at compile time, cannot be modified
//    constexpr int i{3};
//    used for computing value of constants, for improving performance

// constexpr functions
//  args and return value are constexpr
//  executed at compile time
//  implemented using compile time interpreter which supports most of c++
//  must be pure, does not modify any variables or args
//  implicitly inline
//  constexpr double miles_to_km(double miles) { return miles*1.602;}
//  constexpr member variables must be delared static

// template classes
// member template : a templated member function
//  cannot be virtual
//  generic lamdas are implemented using member templates
// c++20 has concepts using which we can specify the type of template args 

// template specialization
//   sometimes we want to have different behaviour for differnt types
//     we want to handle some types differently, code doesnt behave correctly for sometypes
// template<typename T> 
//  class class_name<T> // generic template
// template <>
//  class class_name<bool> {} //specialized template
//  write specialization immediately after generic
// compiler chooses most specialized version of template according to template argument
// partial specialization
// template <typename T*> // specialized for pointers

// extern templates
//  helpful in dealing with template bloat issue
//  when multiple instantiations of same template, the compiler creates multiple files for same template
//  this causes to increase in object file size and compile time
//  manually instantiation of the template
//    template std::ostream& print(std::ostream& os, const std::string& str);
//  by writing above statement the template will be instantiated only once and will be used by all the statements
// extern keyword : defined somewhere else
// extern template void func(); tells compiler that there is instantiation of the template func somewhere in thr program
//   there must be exactly one file where the fuction is instantiated explicitly
//    template void func() {}

// variadic templates
// variadic functions can take any number of arguments
//   in the declaration of a variadic function the last parameter is ...
//   int printf(const char *fmt, ...); // only works properly with Ctypes
//   args are processed at runtime
// variadic template functions
//   list of parameters is written as typename... T
// compiler will deduce the number of arguments from the call
// parameter packs only available at compile time
// we can do three things with a parameter pack
// sizeof...() to get number of elements
// make_tuple() to store them in std::tuple
// iterate over the elements, using template recursion
// template recursion decreases arguments in subsequent argument calls
// pack processing
//  template<typename T, typename... Args>
//  void func(T t, Args... args) {
//     // process t;
//     func(args...); // recursive call, passing the remainder of the list
//   }
//   for this to work we need to have base case handler template<typename T> void func(T t) {} before variadic one

// misc template funcs
// assert <cassert> : checks its args at runtime, if arg is zero, it calls std::abort other normal execution
//   useful for checking invariants : assert(x == 42)
//   can be disabled by #define NDEBUG, disable in production code
// static_assert() : takes const bool expr and a string literal
//    bool is checked during compilation, if false compilation stops and error message is the arg
//    static_assert(sizeof(int*) == 8, "this program requires 64 bit compiler");
//    mainly used in template metaprogramming
//      static_assert(std::is_copy_constructor<T>::value, "argument must be copyable")
// default template parameters
//    template<typename T = int> class class_name{}
//    class_name<> will give default type 

// library defined operators
// <functional> example less<Type> operator calls '<' operator of type
// arithmetic operators : plus, minus, multiply, divide, modulus, negate
// relational operators : equal_to, not_equal_to, greater, greater_equal, less, less_equal
// logical : logicaland or, not
// bitwise : bit and , or, xor, not(14)
// these are functors to call : less() (a, b);
// we can use these operators to write generic functions with default comparisons
// we can write template function which takes two template args and callable object
// we can set template arg = less<T> as default template parameter
// template<typename T, typename Func = less<T>> bool compare(const T& t1, const T& t2, Func func=Func()){ return func(t1, t2);}

// constexpr if // c++17
// allows conditional to be evaluated at compile-time
// if constexpr(a<b)
// ... // compiler will compile this code
// else
// ... // 
// only true branch is included into the program, false branch is ignored
// useful for optimizing away the unused branches in code

// decltype
//  can only be used at compile time
//  gives the type of its argument
//  argument must be an expression or an object
//  compiler replaces decltype with the type that the argument will return
//   decltype(1+2) y; // declare y with same type as (1+2)
//  for named type, decltype will give the type it was declared as
//  decltype retains const, refrence etc
//  with lvalue expression result is an lvalue refrence to the expressions deduced type
//    decltype(x+y) // gives int& if x and y are int
//    decltype((x)) // gives int& writing variable inside pair of brackets it becomes an expression
//  with xrvalue, result is rvalue refrence to the argument's deduced type
//    decltype(Test()) // gives "Test&&"
//  useful in compile time programming
//  can be used for automatic deduction of return type of template functions
//  template<typename T, typename U>
//  auto add(T t, U u) -> decltype(t+u) { return t+u; }
//  can be used in c++14 generic lambdas
//  auto make_vector = [] (auto x, size_t n) { return vector<decltype(x)> (n,x);}

// Entity Component System Architecture : used in game frameworks
 
template<typename T>
void func(T t)
{
	std::cout << t << std::endl;
}

template <typename T, typename... Args> // template parameter pack
void func(T t,Args... args)//function arg pack //...lists are called parameter packs
{
	std::cout << t << " ";
	func(args...);
	/*std::cout << std::endl;*/
	/*auto arg_count = sizeof...(args);
	auto arg_tuple = std::make_tuple(args...);*/
	/*for (int i = 0; i < arg_count; i++)
	{
		auto ar = std::get<i>(arg_tuple);
		std::cout << "arg " << i << " : " << ar << std::endl;
	}*/
}

constexpr double miles_to_km(double miles) { return miles * 1.062; }

const double dist1 = miles_to_km(20);

double d = 40;
double dist2 = miles_to_km(d);

//constexpr double dis4 = miles_to_km(d);
template<typename T>
class comparer {
public:
	comparer(const T& t1, const T& t2) : t1{ t1 }, t2{ t2 } {}

	template<typename func>
	bool compare(func f)
	{
		return f(t1, t2);
	}
private:
	T t1;
	T t2;
};



int main_comptime()
{
	func(1);
	func(1, "2da", 3.0);
	/*int x{ 2 }, y{ 3 };
	comparer<int> comp(x, y);
	std::cout << comp.compare([](int a, int b) {return a > b; }) << std::endl;*/
	return 0;
}