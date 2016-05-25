#include <iostream>
#include <thread>
#include <netstream.hpp>
#include <Compression.hpp>
#include <Compression.hpp>
using namespace ca;
using namespace bit;
using namespace std;

void startServe(short connfd) {
	instream nin(connfd);
	ofstream fout("Recv", ios::out);
	Huffman_algs().expand(nin, fout);
	fout.close();
}

int main(int argc, char *argv[]) {
	unsigned short port = 2000;
	if (argc == 2) sscanf(argv[1], "%hu", &port);
	try {
		while(true) 
			std::thread(startServe, Server::getConnfd(port)).detach();
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}