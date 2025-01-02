#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<random>
#include<numeric>
#include<fstream>
#include<sstream>

using namespace std::string_literals;



template<typename T>
void print_vec(const std::vector<T>& vec, std::ostream& os=std::cout)
{
	std::copy(std::cbegin(vec), std::cend(vec), std::ostream_iterator<T>(os, ","));
	std::cout << std::endl;
}

void print_random_vector()
{
	std::mt19937 md(std::random_device{}());
	std::vector<int> ans(10);
	std::uniform_int_distribution<int> dist(0, 1000);

	std::generate(std::begin(ans), std::end(ans), [&dist, &md]() { return dist(md); });
	
	print_vec<int>(ans);

	auto max_el = std::max_element(std::begin(ans), std::end(ans));
	
	std::cout << "max element : " << *max_el << std::endl;
	
	std::cout << "Index of max element " << std::distance(std::begin(ans), max_el) << std::endl;

	int sum = std::accumulate(std::begin(ans), std::end(ans), 0);
	std::cout << "sum of the elements : " << sum << std::endl;

	auto odds = std::count_if(std::begin(ans), std::end(ans),
		[](int i) { return i % 2 == 1; }
	);
	std::cout << "number of odd elements : " << odds << std::endl;

	std::vector<double> normalized_vec;
	std::transform(std::begin(ans), std::end(ans), std::back_inserter(normalized_vec),
		[&max_el](int i) {
			return 1.0 * i / *(max_el);
		}
	);

	print_vec<double>(normalized_vec);

	std::vector<int> ans_copy{ans};
	std::sort(std::begin(ans_copy), std::end(ans_copy));

	auto el = std::upper_bound(std::begin(ans_copy), std::end(ans_copy), 455);
	print_vec<int>(ans_copy);
	if (el != ans_copy.end())
	{
		std::cout << "First element greater than 455: " << * el << std::endl;
		std::cout << "Index for above element is : " << std::distance(std::begin(ans_copy), el) << std::endl;
		std::cout << "Number of elements greater than 455 : " << std::distance(el, std::end(ans_copy)) << std::endl;
	}
	else {
		std::cout << "No element greater than 455" << std::endl;
	}

	std::vector<double> odd_vec;
	std::copy_if(std::begin(ans), std::end(ans), std::back_inserter(odd_vec),
		[](int i) { return i % 2 == 1; }
	);
	std::cout << "odd vector" << std::endl;
	print_vec<double>(odd_vec);

	sort(std::begin(odd_vec), std::end(odd_vec), std::greater<double>());
	std::cout << "odd vector sorted in descending order" << std::endl;
	print_vec<double>(odd_vec);

	std::shuffle(std::next(std::begin(odd_vec)), std::prev(std::end(odd_vec)), md);
	std::cout << "shuffled odd vector " << std::endl;
	print_vec<double>(odd_vec);

	auto removed_els = std::remove_if(std::begin(ans_copy), std::end(ans_copy),
		[](int i) { return i % 2 == 1; }
	);
	ans_copy.erase(removed_els);
	std::cout << "Removed odd elements from ans copy : " << std::endl;
	print_vec<int>(ans_copy);

	std::ofstream outfile{ ".\\output.txt", std::ios::trunc };
	print_vec<int>(ans_copy, outfile);
	outfile.close();
}

void read_words(std::ifstream& ifile, std::vector<std::string>& word_vec)
{
	if (ifile.is_open())
	{
		std::istreambuf_iterator<char> ibit{ ifile }, ibend;
		std::string input_text;

		int num_lines = 0;
		int num_chars = 0;
		if (ibit != ibend)
			num_lines += 1;

		std::copy_if(ibit, ibend, std::back_inserter(input_text),
			[&num_lines, &num_chars](char c) {
				num_chars++;
				if (c == '\n') num_lines++;
				return ispunct(c) == false && !(c == '\n');
			});
		std::transform(std::begin(input_text), std::end(input_text), std::begin(input_text),
			[](char c) {return tolower(c); });
		std::istringstream iss{ input_text };
		std::istream_iterator<std::string> iss_it{ iss }, end;
		std::copy(iss_it, end, std::back_inserter(word_vec));

		std::sort(std::begin(word_vec), std::end(word_vec));
		auto removed_els = std::unique(std::begin(word_vec), std::end(word_vec));
		word_vec.erase(removed_els);
		print_vec<std::string>(word_vec);
		std::cout << "Number of words in the file : " << word_vec.size() << std::endl;
		std::cout << "Number of lines in the file : " << num_lines << std::endl;
		std::cout << "Number of characters in the file : " << num_chars << std::endl;
	}
	else {
		std::cout << "failed to open the file " << std::endl;
	}
}

int main_algoass()
{
	//std::cout << "Current working dir " << ExePath() << std::endl;
	//print_random_vector();

	std::vector<std::string> word_vec, word_vec2, common_words;
	std::ifstream ifile{ "words.txt" };
	std::ifstream ifile2{ "words2.txt" };

	read_words(ifile, word_vec);
	read_words(ifile2, word_vec2);


	std::set_intersection(std::cbegin(word_vec), std::cend(word_vec),
		std::cbegin(word_vec2), std::cend(word_vec2),
		std::back_inserter(common_words)
	);

	print_vec<std::string>(common_words);

	std::cout << std::endl;
	int fact = 1;
	int n = 6;
	std::vector<int> nums(n);
	std::iota(std::begin(nums), std::end(nums), 1);
	print_vec<int>(nums);
	auto ans = std::accumulate(std::begin(nums), std::end(nums), 1,
		[](int x, int y) {
			return 	x * y;
		});
	std::cout << "Factorial of " << n << " " << ans << std::endl;

	// typical use case: an input stream represented as a pair of iterators
	//std::istringstream in{ "Hello, world"s };
	//std::istreambuf_iterator<char> it{ in }, end;
	//std::string ss{ it, end };
	//std::cout << "ss has " << ss.size() << " bytes; "
	//	"it holds \"" << ss << "\"\n";

	//// demonstration of the single-pass nature
	//std::istringstream s{ "abc" };
	//std::istreambuf_iterator<char> i1{ s }, i2{ s };
	//std::cout << "i1 returns '" << *i1 << "'\n"
	//	"i2 returns '" << *i2 << "'\n";

	//++i1;
	//std::cout << "after incrementing i1, but not i2:\n"
	//	"i1 returns '" << *i1 << "'\n"
	//	"i2 returns '" << *i2 << "'\n";

	//++i2;
	//std::cout << "after incrementing i2, but not i1:\n"
	//	"i1 returns '" << *i1 << "'\n"
	//	"i2 returns '" << *i2 << "'\n";
	return 0;
}