#include <bitstream.hpp>
#include <netstream.hpp>
#include <Compression.hpp>
#include <cxxopts.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace ca;
using namespace std;
using namespace bit;
using namespace cxxopts;

int main(int argc, char *argv[]) {
	try {
		bool compress = true;
		bool adaptive = true;
		Options options(argv[0], " - command line options");
		options.add_options() 
		("c,compress", "Compress file")
		("e,expand", "Expand compressed file")
		("s,static", "Use static huffman coding")
		("a,adaptive", "Use adaptive huffman coding")
		("i,input", "Input file", value<string>())
		("o,output", "Output file", value<string>()->default_value("Processed.out"))
		("n,hostname", "hostname", value<string>())
		("h,help", "Print help")
		; 
		options.parse(argc, argv); 
		if (options.count("h")) {
			cout << options.help({""}) << endl; 
			exit(0);
		}
		if (!(options.count("c") ^ options.count("e")))
			throw OptionException(
				" You must specify one of the '--compress' or '--expand' options");
		if (!(options.count("s") ^ options.count("a")))
			throw OptionException(
				" You must specify one of the '--static' or '--adaptive' options");
		if (options.count("i")) { 
			if (options.count("c")) {
				ifstream fin(options["input"].as<string>(), ios::in | ios::binary);
				fin.unsetf(ios_base::skipws);
				if (options.count("n")) {
					onstream nout(options["hostname"].as<string>(), 2000);
					AdaptiveHuffman_algs().compress(fin, nout);
				} else {
					obstream bout(options["output"].as<string>());
					if (options.count("s")) Huffman_algs().compress(fin, bout);
					else AdaptiveHuffman_algs().compress(fin, bout);
					bout.close();
				}
				fin.close();
			} else {
				ibstream bin(options["input"].as<string>());
				ofstream fout(options["output"].as<string>(), ios::out);
				if (options.count("s")) Huffman_algs().expand(bin, fout);
				else AdaptiveHuffman_algs().expand(bin, fout);
				bin.close();
				fout.close();
			}
		} else {
			throw OptionException(" You must specify input file");
		}
	} catch (const OptionException &e) {
		cout << "error parsing options: " << e.what() << endl;
		cout << "Try \'huffman --help\' for more information." << endl;
		exit(1);
	}
	return 0;
}