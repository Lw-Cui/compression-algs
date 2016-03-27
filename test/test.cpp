#include "bitheader/bitstream.hpp"
#include "huffmanHeader/Huffman.hpp"
#include <fstream>
using namespace ca;
using namespace std;
using namespace bit;

int main() {
	ifstream fin("g.txt", ios::in | ios::binary);
	fin.unsetf(ios_base::skipws);
	obstream bout("g.bin");
	Huffman_algs().compress(fin, bout);
	fin.close();
	bout.close();

	ibstream bin("g.bin");
	ofstream fout("g.raw", ios::out);
	Huffman_algs().expand(bin, fout);
	bin.close();
	fout.close();
	return 0;
}