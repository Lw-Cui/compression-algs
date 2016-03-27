#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include "bitheader/bitstream.hpp"
#include <fstream>
#include <memory>
namespace ca {
	class Node {
	public:
		int frequency;
		char data;
		std::shared_ptr<Node> left, right;
		bool operator<(const Node&);
		Node(char c, int frequency);
		Node(std::shared_ptr<Node>, std::shared_ptr<Node>);
	};

	class Huffman {
	public:
		void compress(std::ifstream&, bit::obstream&);
		void expand(bit::ibstream&, std::ofstream&);
	private:
		Node buildtree(std::ifstream&);
		void writetree(bit::ibstream&, const Node&);
		void encode(std::ifstream&, bit::obstream&);

		Node readtree(bit::ibstream&);
		void decode(bit::ibstream&, std::ofstream&, const Node&);
	};
}
#endif