#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include "bitheader/bitstream.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
namespace ca {
	class Node {
	public:
		int frequency;
		char data;
		std::shared_ptr<Node> left, right;
		Node(char, int);
		Node(int, std::shared_ptr<Node>, std::shared_ptr<Node>);
	};

	class Huffman {
	public:
		void compress(std::istream&, bit::obstream&);
		void expand(bit::ibstream&, std::ostream&);
	private:
		std::map<char, int> getfrequency(std::istream&);
		std::shared_ptr<Node> buildtree(const std::map<char, int>&);
		void writetree(bit::obstream&, std::shared_ptr<Node>);
		void buildtable(std::shared_ptr<Node>, std::map<char, std::vector<bool>>&,
			std::vector<bool>&);
		void encode(std::istream&, bit::obstream&, std::map<char, std::vector<bool>>&);

		void readtree(bit::ibstream&, std::shared_ptr<Node>&);
		void decode(bit::ibstream&, std::ostream&, std::shared_ptr<Node>);
	};

	Huffman &Huffman_algs();
}
#endif