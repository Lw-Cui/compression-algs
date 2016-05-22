#ifndef _COMPRESSION_ALGS_
#define _COMPRESSION_ALGS_
#include <bitstream.hpp>
namespace ca {
	class CompressAlgs {
	public:
		virtual void compress(std::istream&, bit::obstream&) = 0;
		virtual void expand(bit::ibstream&, std::ostream&) = 0;
	};
	CompressAlgs &Huffman_algs();
	CompressAlgs &AdaptiveHuffman_algs();
}
#endif