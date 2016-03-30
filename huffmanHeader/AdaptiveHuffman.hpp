#ifndef _ADAPTIVEHUFFMAN_H_
#define _ADAPTIVEHUFFMAN_H_
#include "bitheader/bitstream.hpp"
#include "huffmanHeader/Compression.hpp"
#include <iostream>
#include <stack>
#include <vector>
namespace ca {
	class AdaptiveHuffman: public CompressAlgs {
	public:
		class Node {
		public:
			int parent;
			int weight;
			char value;
			int left, right;
			Node();
			void set(int, int);
		};
		AdaptiveHuffman();
		void compress(std::istream&, bit::obstream&) override;
		void expand(bit::ibstream&, std::ostream&) override;
	private:
		int findPos(int);
		void update(int);
		void insertNew(char);
		bit::obstream& encode(int, bit::obstream&);
		bool decode(bit::ibstream&, int&);
		static const int Alphabet = 512;
		std::vector<Node> tree;
		std::vector<int> leaf;
		int NYT;
	};

	AdaptiveHuffman &AdaptiveHuffman_algs();
}
#endif