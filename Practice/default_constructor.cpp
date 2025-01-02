#include<iostream>
#include<string>

class A {
public:
	A(): a(0), b(0) {}
	friend std::ostream& operator<<(std::ostream&, A&);
private:
	int a;
	int* b;
};

std::ostream& operator<<(std::ostream& os, A& a)
{
	os << a.a << " " << a.b << std::endl;
	os << &a.a << " " << &a.b << std::endl;
	return os;
}

// typedef vector<int> IntVec;
// using IntVec = vector<int>;

// nullptr cannot be cast as integer, it can be cast only as a pointer
//unsigned int ptr = nullptr; //error

//public members are the interface of the class
//private members are the implementation of the class

//"this" is a pointer to the object passed into the implementation of the
//member function

//assignment operator returns non-const reference Test& operator=(const Test& other)

//multiplication is much faster than pointer deref

//ANSI escape codes are used to manipulate outptut of the terminal
// 0x1b[ ==> 0x1 ==> escape b[ ==> command
// 0x1b[n;mH ==> move cursro to nth row and mth colum and display char
// -x1b[2J ==> clear the screen and return cursor to home

//cstdint ==> used to include int32_t, int16_t etc.. 
//sizeof returns size in bytes
//base 16 0x2a (hex)
//base 8 052 (octal)
//c++ 14 onwards 0b0001 (binary)
//float = 6 digits precision, double = 15 digts, long double = 20
//c++ 14 allows digit seperator 1'000'000
//floating point literals are double by default
//add suffix 1234LL for long long, c++11 allows custom suffix which allow to return custom types
//string suffix in c++ 14 "hello"s using namespace std::literals;
//Raw string R"(delim_char)(<a href="file">C:\Program Files\</a>\n)(delimchar)";

//casting means converting an expression from one type to other (in C) => (char)c
//in c++11 static_cast<char>(c)
//const_cast<char*>(msg) makes msg a non const variable
//reinterpret_cast convert data in a buffer to untyped binary data(used for low level)
//dynamic_cast  used to convert a pointer to base class object to pointer to a derived class, also applicable on refrences

//std::class_name::iterator
// const_iterator cbegin, cend => read only access to element, const container can only be accessed using const iterator
// reverse_iterator => backwards rbegin(), rend() crbegin(), crend()
// begin(container) end(container)
// range for loops for(auto el : vec) //copy of the element is returned
// end() - begin() gives number of elements
// adding i to begin() gives ith element
// last = end() - 1
// distance(begin(), end()) ==> gives number of elements
// mid = begin(), advance(mid, distance(begin(), end())/2) => advance iterator by 2nd arg
// iterator range is half-open [ begin(), end() )

//auto keyword ignores const and refrence(&)

//c++17 allows if(auto iter = begin(vec); iter != end(vec)) to check if empty 
//c++17 switch (const char c=arr[i]; c)
//attribute in c++ is just an instruction to the compiler, it can't change the meaning of the code
//[[fallthrough]] attribute after switch statement tells compiler delibrately no break

//g++ -Wall -Werror (all warnings are treated as errors)

//templates allows generic programming in c++
//c++ is strongly typed language
//translation unit is a source code file passed to the compiler
//declaration and definition must be in the same file
//CTAD : constructor template argument detection is available in c++17

//namespaces are used to group together logically related symbols
//using declaration using xyz::Test brings Test into global namespace
//using directive using namespace std;

//function pointer ==> void (*func_pointer)(int, int) = &func; or auto func_ptr = &func
//using pfunc = void(*)(int, int);
//function pointer is callable object => (*func_ptr)(1,2);

struct test {
	double x;
	double y;
	unsigned int h;
	unsigned int age;
};

class URL {
public:
	URL() :protocol{ "" }, resource{ "" } {}
	URL(const char* pr, const char* res):protocol{pr} , resource {res} {}
	URL(const std::string& pr, const std::string& res):protocol{pr}, resource{res} {}

	std::string Print()
	{
		return std::string(protocol + "://" + resource);
	}
private:
	std::string protocol;
	std::string resource;
};

int main_2()
{

	URL url{ "http", "www.example.com" };
	std::cout << url.Print() << std::endl;

	A obj1;
	A obj2(obj1);

	std::cout << obj1;
	std::cout << obj2;

	test arr[4]{1,2,3,4};
	int* arr2 = new int[4] {1, 2, 3, 4};
	char str[] = "hello what are you doing? kamehahme haldhfalkdjshiaotyeoayhta ";
	std::string str2{ str };

	std::cout << "size of " << str << " is " << sizeof(str) << std::endl;
	std::cout << "size of " << str << " is " << sizeof(str2) << std::endl;
	std::cout << "size of test = " << sizeof(arr[0]) << std::endl;
	std::cout << sizeof(arr) << std::endl;
	std::cout << sizeof(*arr2) << std::endl;

	delete[] arr2;

	int i = 7.7;
	//int j{ 7.7 }; //narrowing conversion not allowed compiler error

	//std::cout << i << j << std::endl;

	return 0;
}