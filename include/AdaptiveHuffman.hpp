#ifndef _ADAPTIVEHUFFMAN_H_
#define _ADAPTIVEHUFFMAN_H_
#include <bitstream.hpp>
#include <Compression.hpp>
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
		void compress(std::istream&, bit::oBaseStream&) override;
		void expand(bit::iBaseStream&, std::ostream&) override;
	private:
		int findPos(int);
		void update(int);
		void insertNew(char);
		bit::oBaseStream& encode(int, bit::oBaseStream&);
		bool decode(bit::iBaseStream&, int&);
		static const int Alphabet = 512;
		std::vector<Node> tree;
		std::vector<int> leaf;
		int NYT;
	};
}
#endif