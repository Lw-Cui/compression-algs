#define DEBUG
#include "huffmanHeader/Huffman.hpp"
#include <iostream>
#include <queue>
using namespace ca;
using namespace std;
using namespace bit;

Huffman& ca::Huffman_algs() {
	static Huffman huf;
	return huf;
}

Node::Node(char c, int fre):data(c), frequency(fre) {
}

Node::Node(int fre, std::shared_ptr<Node> l, std::shared_ptr<Node> n)
	:frequency(fre), left(l), right(n) {
}


void Huffman::compress(std::ifstream &fin, bit::obstream &bout) {
	shared_ptr<Node> root = buildtree(getfrequency(fin));
	std::map<char, std::vector<bool>> coding;
	std::vector<bool> v;
	buildtable(root, coding, v);
	writetree(bout, root);
	encode(fin, bout, coding);
}

std::map<char, int> Huffman::getfrequency(std::ifstream &fin) {
	map<char, int> freq;
	char c;
	while (fin >> c) freq[c]++;
	return freq;
}

shared_ptr<Node> Huffman::buildtree(const map<char, int>& freq) {
	auto cmp = [](const shared_ptr<Node> &n1, const shared_ptr<Node>& n2) {
		return n1->frequency > n2->frequency;
	};
	priority_queue<shared_ptr<Node>, 
		std::vector<shared_ptr<Node>>, decltype(cmp)> que(cmp);
	for (auto &p: freq)
		que.push(make_shared<Node>(p.first, p.second));
	while (que.size() != 1) {
		auto n1 = que.top(); que.pop();
		auto n2 = que.top(); que.pop();
		que.push(make_shared<Node>(n1->frequency + n2->frequency, n1, n2));
	}
	return que.top();
}

void Huffman::writetree(bit::obstream&bout, shared_ptr<Node>root) {
	if (root->left == nullptr && root->right == nullptr) {
		bout << true << root->data;
	} else {
		bout << false;
		writetree(bout, root->left);
		writetree(bout, root->right);
	}
}

void Huffman::buildtable(shared_ptr<Node> root, 
	std::map<char, std::vector<bool>>& coding, std::vector<bool> &v) {
	if (root->left == nullptr && root->right == nullptr) {
		coding[root->data] = v;
#ifdef DEBUG
		cout << root->data << " ";
		for (auto p: v)
			if (p) cout << "1"; else cout << "0";
		cout << endl;
#endif
	} else {
		v.push_back(false); buildtable(root->left, coding, v); v.pop_back();
		v.push_back(true); buildtable(root->right, coding, v); v.pop_back();
	}
}

void Huffman::encode(std::ifstream &fin, bit::obstream &bout, 
	std::map<char, std::vector<bool>>& coding) {
	fin.clear();
	fin.seekg(0, fin.beg);
	char c;
	while (fin >> c)
		for (auto b: coding[c])
			bout << b;
}

void Huffman::expand(bit::ibstream& bin, std::ofstream& fout) {
	shared_ptr<Node> root;
	readtree(bin, root);
#ifdef DEBUG
	std::map<char, std::vector<bool>> coding;
	std::vector<bool> v;
	buildtable(root, coding, v);
#endif
	while (bin)
		decode(bin, fout, root);
}

void Huffman::readtree(bit::ibstream& bin, shared_ptr<Node> &root) {
	bool flag; bin >> flag;
	if (flag) {
		char c; bin >> c; 
		root = make_shared<Node>(c, 0);
	} else {
		root = make_shared<Node>(0, nullptr, nullptr);
		readtree(bin, root->left);
		readtree(bin, root->right);
	}
}

void Huffman::decode(bit::ibstream &bin, std::ofstream &fout,
	std::shared_ptr<Node>root) {
	if (root->left == nullptr && root->right == nullptr) {
		fout << root->data;
	} else {
		bool flag; if (!(bin >> flag)) return;
		if (flag) decode(bin, fout, root->right);
		else decode(bin, fout, root->left);
	}
}