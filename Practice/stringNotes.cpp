#include<iostream>
#include<string>
#include<cctype>

//string.substr(start_pos, length_of_substring)
//constructor substring argument syntax : str(ref_string, index, length)
//str.find('c' or "str") => returns string::npos is not found else returns first matching char
//str.rfind() reverse find
//str.find_first_of("aeiou"), str.find_last_of("aeiou"), str.find_first_not_of
//append(ref_str, substr_index, substr_len), += (useful for adding single character)
//insert(index,frequency, string)  iterators also work
//when memory buffer of the container changes due to new allocation or deletion, the
//    iterators used before this become invalid and can cause undefined behavior
//    so reset iterators after the operation
//str.erase(index, num_chars), erase(itr, itr_last) [itr, itr_last) are deleted
//str.replace(index, num_characters_to_be_replaced, "ref_string"), replace(itr_start, itr_end, "ref_string")
//assign ==> replace all characters with argument
//atoi, atod convert numbers to str, sprintf to convert string to nums
//in c++11 to_string(numeric)
//stoi convert string to int. stoi ignores whitespace chars
//stoi(str2, &n_processed) ==> throws exception if not convertable str2
// stoi(str, &n_processed, 16) ==> base 16
// stod, stoll, stof are also available
// data() member function returns address of the internal memory bufer
// cctype header, isdigit, islower, isupper, isspace, ispunct
//      toupper, and tolower(char)

// reading all content of file into the vector of strings
// std::ifstream wif{"words.txt"};
// if (wif) {
//	 istream_iterator<string> iit{ wif };
//	 istream_iterator<string> eof;
//	 vector<string> in_words{ iit, eof }; // string in_words{iit, eof}; // all content
//  }


std::string exclaim(const std::string& str)
{
	std::string ret;
	for (char c : str)
	{
		if (ispunct(c))
			ret += '!';
		else ret += c;
	}
	return ret;
}

void test()
{
	std::string ans { "To be! or not to be! that is the question!" };
	std::string str{ "To be, or not to be, that is the question:" };
	
	std::string ret = exclaim(str);
	std::cout << ret << std::endl;
	if (!(ans == ret))
		std::cout << "Incorrect answer!" << std::endl;
	else std::cout << "Correct!" << std::endl;
}

int main_str()
{
	//std::string str{ "To be, or not to be, that is the question:" };
	//std::cout << exclaim(str) << std::endl;
	test();

	return 0;
}