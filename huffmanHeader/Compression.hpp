#ifndef _COMPRESSION_ALGS_
#define _COMPRESSION_ALGS_
#include "bitheader/bitstream.hpp"
#include <iostream>
namespace ca {
	class CompressAlgs {
	public:
		virtual void compress(std::istream&, bit::obstream&) = 0;
		virtual void expand(bit::ibstream&, std::ostream&) = 0;
	};
	class Huffman;
	Huffman &Huffman_algs();
	class AdaptiveHuffman;
	AdaptiveHuffman &AdaptiveHuffman_algs();
}
#endif