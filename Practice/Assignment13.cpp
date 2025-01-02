#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<numeric>

extern "C" {
#include "assignment13.h"
}

int main_ass13()
{
	std::set<int> s;
	for (int i = 0; i < 10; i++)
	{
		s.insert(i + 1);
	}
	
	std::vector<int> sv;
	std::copy(std::begin(s), std::end(s), std::back_inserter(sv));
	print_array(sv.data(), sv.size());
	
	return 0;
}