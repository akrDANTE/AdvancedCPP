#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include<cctype>
// file is just a sequence of bytes identified by a file name
// fstream objects to interact with files
// fstream object always access files sequentially
// fstream does not understand file formats
// open, read, write, close are calls to operating system API
// OS limits allocating memory and files opened by the program
// data is temporarily saved in memory buffer till it reaches a sufficient size then data 
//   is transferred to file
// ofstream --> file stream for writing
// ifstream --> file stream for reading
// ifstream ifile{"text.txt"} ==> this represents communication chanel which is used to receive
//    data from the file
// if(ifile) to check if file opened correctly
// before c++11 can't pass std::string as constructor argument to ifstream
// while(ifile >> text) cout << text << ","; reads one word at a time
// while(getline(ifile, text) ==> reads line by line removes newline char
// ofstream ofile{"text_out.txt"}
// for(auto word : words) ofile << word << ","; 
// destructor automatically calls close function.
// C++ streams use buffering to minimize calls to os, size of the buffer is max amount of
//    data that OS will accepting
// Flushing of output buffer: when buffer is full , the stream will remove the data from the buffer and send it to the OS
// ofstream is only flusehd when the buffer is full
// std::flush allows us to control when the stream's buffer is flushed,
// cout << i << flush; output the data immediately to stream
// only use flush if data really needs to be up to data

//lower level operations on streams are useful in network apps and when directly
//    communication directly with hardware
//single char in out, cin.get fetches next character from the input stream, reads until we get end-of-input
// cout.put sents its argument to an output stream
// ^Z is windows endofinput character
// for reading and writing many characters read and write functions
// for read and write we need to provide our own buffers
//    ifile.read(buf, bufsize); cout.write(buf, bufsize)
// gcount() function return the number of characters that were actually received

// by default files are opened in "text mode", i.e. characters are interpreted as ASCII
// output files are opened in truncate mode by default,
// to open in append_mode ofile.open("important.txt", fstream::app/ ios::app);
// binary mode, 
// trunc, in, out, ate(similar to append but output can be written anywhere in the file)
// fstream::out | fstream::app (for writing in append mode)

// is_open() member function
// state member functions : good() ==> returns true if input was read success
//    fail() ==> return true if input was not read correctly/recoverable error
//    bad() ==> return true if unrecoverable error like disk failure
// clear() restores the stream's state to valid
// eof() returns true after the end of file has been reached
// ifile >> x returns the state of the file stream
// cin.ignore(20, '\n') ==> ignores next 20 input characters or if /n comes stop
// to calculate the size of the buffer: cin.ignore(numberic_limits<streamsize>::max(), '\n') in limits header

// manipulator is an object that is pushed on to stream to affect the stream's behavior
// std::flush and std::endl are manipulators
// iomanip contains manipulators which take args
// cout << boolalpha << var_name << endl; // prints true or false for boolean
// boolalpha has sticky behavior, to turn off this push noboolalpha
// setw() manipulator takes width of the field, only affects the next data item, only non sticky manipulator
// setw by default right justifies the output, use left(sticky) to left justify, right to reset
// setfill('#') ==> change padding character

// by default 6 significant figures are displayed for small numbers
// when number increase certain threshold then scientific notation is displayed
// 2.997923+008 reps 2.99792 * 10^8, use scientific manipulator, uppercase as well
// fixed point notation ==> use fixed manipulator
// to reset use defaultfloat manipulator
// setprecision(num_of_digits_after_decimal) 

// stringstream for string operations <sstream> ==> wrapper around std::string class
// ostringstream has empty std::string object: use str() member function
// using ostringstream we can create our own to_string function:
// To_string(const T& i) { os << i; return os.str(); } 
// ostr << setw(8) << text; 
// istrinstream{existing_str}; => breaking up a line into words or numbers, processing parsing input
// while(istr >> num) { // do something with num }

// resources : heap memory, files, database connections , GUI windows
// need to think about allocate, release, copy, error handling
// Resource Acquisition is initialization(RAII)
//    resource is stored ad a private member of the class
//    class constructor acquires the resource
//    class's public member functions control access to the resource
//    class' destructor releases the resource
// when an object is copied or assigned to the target object acquires its own version of the resource

// random access to streams using stream position marker
// stream position marker keeps track of where the next read or write operation will be performed
// just after the last read for read operations, end of stream for write positions
// seek member function changes the position of the marker, seekg for input stream, seekp for output stream
// tell returns the marker's current position, tellg for input and tellp for output
// not defined for iostreams and for append mode always points to end of the file
// tell returns a pos_type object, this reps position in the stream can be converted to int
// if stream is invalid state, then tell will fail and return -1
// std::ios_base provides three base positions: beg, end, cur
// seekp(-10, std::ios_base::end);
// tell operations are useful for saving the current marker position, so we can retreive later
// marker = ofile.tellp();
// tellp will be useful when very big file is input

// stream iterators: the must all have the same type
// defined in <iterator> : istream_iterator, ostream_iterator
// ostream_iterator<int> oi(cout, "\n"); ==> whenver data is assigned to operator it will be pushed to the stream
// *oi = 7 will cause 7 to be displayed to output, calls << of the stream
// ++ and * also defined for iterators
// istream_iterator<int> ii(cin) will read ints from the cin stream, *ii will deref it
// empty iterator: istream_iterator<string> eof; // not bound to any input stream
// while(ii != eof) { vs.push_back(*ii); ++ii;} ctrlZ is end of input
// useful with containers

// binary file: ofile.open("image.bmp", fstream::binary);
// can't use shift operators with binary file, always use read and write
// create a struct which reps the file fields of the file format
// use fixed size ints to make sure of same results on all systems.
// first arg of read and write will be address of the object, reinterpret_cast<char *>(&obj)
// second argument will be the number of bytes in the object: sizeof(obj)
// calls example: ofile.write(reinterpret_cast<char *>(&obj), sizeof(obj));
// need to handle memory alignment and padding
// modern hardware is optimized for accessing data which is "word aligned"
// every object of data is at a multiple of wordsize: for 32 bit system 4 is word size
// if object is not word aligned, compiler adds extra bytes to make it so, this is called padding
// example: struct point{ char c //1 byte; char pad[3]; //compiler added 3 bytes
//                        int32_t x, int32_t y; // 4 bytes each}
// compiler provide non-standard #pragma pack(push, 1) to change alignment, after done
//    use #pragma pack(pop) works with clang, gcc, vc++
// c++11 has alignas(wordsizemultiple)  

// pixel == picture element

int fh_main()
{
	/*char c;
	while (std::cin.get(c))
	{
		std::cout.put(c);
	}*/

	struct language {
		std::string lang;
		std::string designer;
		int date;
	};

	std::vector<language> langs;

	std::ifstream ifile{ "languages2.txt"};
	if (ifile.is_open())
	{
		std::string line;
		
		while (std::getline(ifile, line))
		{
			std::istringstream istream{ line };
			std::string lang, designer, date;
			istream >> lang;
			char c;
			while (istream.get(c))
			{
				if (isdigit(c))
					date += c;
				else
					designer += c;
			}

			langs.push_back({ lang, designer, std::stoi(date) });
		}

		for (const auto &l : langs)
		{
			std::cout << std::setw(4) << std::left << l.lang << ", " << std::setw(14) << l.designer << ", " << l.date << std::endl;
		}

		std::cout << std::right;
		ifile.close();
	}
	else {
		std::cout << "Error in opening the file" << std::endl;
	}
	return 0;
}

