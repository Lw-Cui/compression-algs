#ifndef _BITSTREAM_H_
#define _BITSTREAM_H_
#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
namespace bit {
	static const int SIZE = 32;
	static const int CHAR_BIT = 8;

	class ibstream {
	public:
		ibstream(const std::string &f);
		~ibstream();
		operator bool();
		bool read_bit();
		ibstream &read_bit(bool &);
		char read_byte();
		ibstream & read_byte(char&);
		void open(const std::string &f);
		void close();
	private:
		void read_buffer();
		bool valid;
		unsigned long sum;
		unsigned long cnt;
		std::bitset<SIZE> buffer;
		std::ifstream fin;
	};

	class obstream {
	public:
		obstream(const std::string &f);
		~obstream();
		void open(const std::string &f);
		obstream &write_byte(char data);
		obstream &write_bit(bool data);
		void close();
	private:
		void write_buffer();
		unsigned long cnt;
		std::bitset<SIZE> buffer;
		std::ofstream fout;
	};

	ibstream& operator>> (ibstream&, char&);
	ibstream& operator>> (ibstream&, bool&);

	obstream& operator<< (obstream&, const char&);
	obstream& operator<< (obstream&, const bool&);
}

#endif