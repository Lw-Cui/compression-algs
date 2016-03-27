#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include "bitheader/bitstream.hpp"
#include <fstream>
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
		void compress(std::ifstream&, bit::obstream&);
		void expand(bit::ibstream&, std::ofstream&);
	private:
		std::map<char, int> getfrequency(std::ifstream&);
		std::shared_ptr<Node> buildtree(const std::map<char, int>&);
		void writetree(bit::obstream&, std::shared_ptr<Node>);
		void buildtable(std::shared_ptr<Node>, std::map<char, std::vector<bool>>&,
			std::vector<bool>&);
		void encode(std::ifstream&, bit::obstream&, std::map<char, std::vector<bool>>&);

		void readtree(bit::ibstream&, std::shared_ptr<Node>&);
		void decode(bit::ibstream&, std::ofstream&, std::shared_ptr<Node>);
	};

	Huffman &Huffman_algs();
}
#endif