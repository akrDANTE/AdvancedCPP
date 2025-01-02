#include<vector>
#include<list>
#include<deque>
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<map>

template<typename T>
void print_vec(const std::vector<T>& vec, std::ostream& os = std::cout)
{
	std::copy(std::cbegin(vec), std::cend(vec), std::ostream_iterator<T>(os, ","));
	std::cout << std::endl;
}

// sequential : string vector
// associative: sets maps
// container adapters: stack and queues

// std::array
// does not automatically decay to pointer
// retains info about its size
// supports iterators
// only stack

//forward list: singly linked list
// std::forward_list 
// insert and erase add or remove element before given iterator
// insert_after, erase_after after given iterator
// splice_after

// std::list doubly linked list
// push_back, push_front
// no random access
// to sort call list.sort()
// merge, remove, remove_if, unique member funcs
// splice moves elements from another list into a list
// list.splice(iterator, list2) ==> insert all elements of list2 before iterator

// deque: double ended queue
// implemented as 2d array: multiple memory blocks which each store several elements
// push_front
// 

// tree balancing: too many elements in one branch of the tree
// choose different root, move elements around till the tree is balanced again
// red-black AVL tree

// set: collection of elements without any structure
// std::set
// no duplicates allowed, uses < operator and is sorted (usually red-black tree)
// insert fails if element is already in the set
// insert, erase
// insert() returns pair <element_iterator, success_status>
// find(k) == returns iterator to element
// count(k) returns 1 or 0
// works with algorithms which only iterate over elements and don't modify/reorder them
//    like find_if

// std::map : each element is pair<key, value> sorted 
// key acts like an index should be unique
// insert(make_pair(k,v)); insert({k,v}); fails if element is already in map
// with [] operator new element will be created if does not exist 
// erase(k)
// works with algorithms simliar to the set
// useful for indexed data(contact list/employee data) , useful for storing data which is in form of keyvalue pairs(json/xml)
// res = map[key] = val; // res contains the reference to the value element of the element
// use insert to insert
// c++ 17 provides insert_or_assign()

// c++17 introduces structured binding
// easy way to access data structures
// in single statement, we declare local vars, bind them to members of a compound DS,
//   the types are deduced by the compiler
// auto [i,d] = p where pair p(1, 20.22)

// multiset and multimap <set><map>
// duplicate keys are allowed
// multimap does not support subscripting
// erase deletes all elements with given key
// we can erase single element by finding iterator to required element
// find() for multimap will return iterator for the first element which has the given key
// count(k) will return number of elements in container with k
// upper_bound(k) returns an iterator to the first element whose key is greater than k
// lower_bound(k) returns an iterator to the first element whose key is greater than or equal to k
// [lower_bound(k), upper_bound(k)) defines a half-open range of iteratos to all elements with key k
// upper and lower bound use < operator.
// equal_range ==> combines(lower_bound and upper_bound) ==> returns pair or iterators
// use find_if over equal range to find an element

// unordered associative containers
// hash table : array of buckets
// reverse iterators not allowed, ++ is allowed -- not allowed for forward iterators
// equal_range available
// inserter(map, end(map))

// custom types with containers
// identity : objects occupy same memory but have are accessed by different refs
// equality : objects occupy different memory but have same value
// equivalence : values are same, but unimportant values may differ,  will sort as if they are equal
// custom < operator(): bool operator < (const class_name& other) const { 
//      if(data == other.data)) return data2 < other.data2;
//      return data < other.data; }

// queue is implemented as deque as it is efficient for front operations
// stacks for undo , storing history for back forward button, parsing expessions

// Emplacement : another way to insert elements into containers
// with emplacement the container creates teh object in the new element, instead of copying it(avoid copy constructor call)
// container.emplace(iterator, constructor_arg1, constructor_arg2...)
// emplace_back() ==> creates object at the end
// c++17 provides try_emplace() for associative containers, it creates object only if key does not exist
// emplacement is the only way to insert objects which cannot be copied


void assignment_11()
{
	std::vector<std::pair<std::string, int>> data;
	std::map<std::string, int> data_map;
	for (std::string word; std::cin >> word; )
	{
		data.push_back({ word, word.length() });
		data_map.insert({ word, word.length() });
	}
	for (auto& el : data)
	{
		std::cout << el.first << ":" << el.second << std::endl;
	}
	for (auto& el : data_map)
	{
		std::cout << el.first << ":" << el.second << std::endl;
	}
}

class URL {
public:
	URL() :protocol{ "" }, resource{ "" } {}
	URL(const char* pr, const char* res) :protocol{ pr }, resource{ res } {}
	URL(const std::string& pr, const std::string& res) :protocol{ pr }, resource{ res } {}

	std::string Print() const
	{
		return std::string(protocol + "://" + resource);
	}
private:
	std::string protocol;
	std::string resource;
};

class History {
public:
	History(): url_list{} {}
	void insert(URL url)
	{
		auto el = std::begin(url_list);
		while (el != std::end(url_list))
		{
			if (el->Print() == url.Print())
				break;
			++el;
		}

		if (el == url_list.end())
		{
			url_list.push_front(url);
		}
		else {
			url_list.push_front(url);
			url_list.erase(el);
		}
	}
	void show() {
		std::cout << "Browser History : " << std::endl;
		for (const auto& u : url_list)
		{
			std::cout << u.Print() << std::endl;
		}
	}
private:
	std::list<URL> url_list;
};

void assignment_10()
{
	auto protocol = "http";
	URL url1(protocol, "harekrishna.com"),
		url2(protocol, "fast.com"),
		url3(protocol, "dbz.com"),
		url4(protocol, "goodle.com");
	History hi;
	hi.insert(url1);
	hi.insert(url2);
	hi.show();
	hi.insert(url3);
	hi.insert(url4);
	hi.show();
	hi.insert(url3);
	hi.show();
}

void assignment_9() {
	std::list<std::string> li;
	std::deque<std::string> dq;

	for (std::string word; std::cin >> word;)
	{
		std::cout << word << std::endl;
	}

	std::istream_iterator<std::string> ist(std::cin), end;
	std::vector<std::string> vec{ ist, end };
	//std::cout << s << std::endl;
	/*std::istringstream iss{ s };
	std::istream_iterator<std::string> ssit(iss);

	std::copy(ssit, end, std::back_inserter(vec));*/
	print_vec<std::string>(vec);

	for (auto el : vec)
	{
		li.push_front(el);
		dq.push_front(el);
	}

	for (auto& el : li)
		std::cout << el << " ";
	std::cout << std::endl;

	for (auto& el : dq)
	{
		std::cout << el << " ";
	}
	std::cout << std::endl;

}

int main_container()
{
	assignment_11();
	return 0;
}