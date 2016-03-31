#include "bitheader/bitstream.hpp"
#include "huffmanHeader/Huffman.hpp"
#include "huffmanHeader/AdaptiveHuffman.hpp"
#include <fstream>
#include <cstring>
using namespace ca;
using namespace std;
using namespace bit;

int main(int argc, char *argv[]) {
	ifstream fin("test.txt", ios::in | ios::binary);
	fin.unsetf(ios_base::skipws);
	obstream bout("test.bin");
	AdaptiveHuffman().compress(fin, bout);
	fin.close();
	bout.close();
	ibstream bin("test.bin");
	ofstream fout("test.raw");
	AdaptiveHuffman().expand(bin, fout);
	bin.close();
	fout.close();
	/*
	if (argc == 4 && !strcmp(argv[1], "-")) {
		ifstream fin(argv[2], ios::in | ios::binary);
		fin.unsetf(ios_base::skipws);
		obstream bout(argv[3]);
		Huffman_algs().compress(fin, bout);
		fin.close();
		bout.close();
	} else if (argc == 4 && !strcmp(argv[1], "+")) {
		ibstream bin(argv[2]);
		ofstream fout(argv[3], ios::out);
		Huffman_algs().expand(bin, fout);
		bin.close();
		fout.close();
	}
	*/
	return 0;
}
