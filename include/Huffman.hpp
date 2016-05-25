#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include <Compression.hpp>
#include <bitstream.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
namespace ca {

	class Huffman: public CompressAlgs {
	public:
		void compress(std::istream&, bit::oBaseStream&) override;
		void expand(bit::iBaseStream&, std::ostream&) override;

		class Node {
		public:
			int frequency;
			char data;
			std::shared_ptr<Node> left, right;
			Node(char, int);
			Node(int, std::shared_ptr<Node>, std::shared_ptr<Node>);
		};
	private:
		std::map<char, int> getfrequency(std::istream&);
		std::shared_ptr<Node> buildtree(const std::map<char, int>&);
		void writetree(bit::oBaseStream&, std::shared_ptr<Node>);
		void buildtable(std::shared_ptr<Node>, std::map<char, std::vector<bool>>&,
			std::vector<bool>&);
		void encode(std::istream&, bit::oBaseStream&, std::map<char, std::vector<bool>>&);

		void readtree(bit::iBaseStream&, std::shared_ptr<Node>&);
		void decode(bit::iBaseStream&, std::ostream&, std::shared_ptr<Node>);
	};
}
#endif