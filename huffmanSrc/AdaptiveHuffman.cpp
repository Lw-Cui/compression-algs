#include "huffmanHeader/AdaptiveHuffman.hpp"
#include "huffmanHeader/Compression.hpp"
#include <algorithm>
#include <queue>
using namespace ca;
using namespace std;
using namespace bit;

AdaptiveHuffman &AdaptiveHuffman_algs() {
	static AdaptiveHuffman algs;
	return algs;
}

void AdaptiveHuffman::compress(std::istream& fin, bit::obstream& bout) {
	char c;
	while (fin >> c) {
#ifdef DEBUG
	cout << "coding " << c << ":" << flush;
#endif
		if (leaf[c] == -1) {
			encode(NYT, bout) << c;
			insertNew(c);
		} else {
			encode(leaf[c], bout);
		}
		update(leaf[c]);
	}
}

void AdaptiveHuffman::expand(bit::ibstream& bin, std::ostream& fout) {
	char c; int pos = Alphabet;
	while (decode(bin, pos)) {
		if (pos == NYT) {
			bin >> c; insertNew(c);
		} else {
			c = tree[pos].value; 
		}
		fout << c << flush;
#ifdef DEBUG
		cout << c << flush;
#endif
		update(leaf[c]);
	}
}

void AdaptiveHuffman::insertNew(char c) {
	tree[NYT].right = leaf[c] = NYT - 1;
	tree[leaf[c]].set(c, NYT);

	tree[NYT].left = NYT - 2;
	tree[tree[NYT].left].set(0, NYT);
	NYT -= 2;
}

AdaptiveHuffman::AdaptiveHuffman()
	:NYT(Alphabet), 
	tree(Alphabet + 1),
	leaf(Alphabet + 1, -1) {
}

AdaptiveHuffman::Node::Node() 
	:parent(-1), left(-1), right(-1), weight(0), value(0) {
}

void AdaptiveHuffman::Node::set(int v, int p) {
	value = v; parent = p;
}

obstream& AdaptiveHuffman::encode(int pos, obstream &bout) {
	stack<bool> coding;
	int parent = tree[pos].parent;
	while (parent != -1) {
		if (tree[parent].left == pos) coding.push(0);
		else coding.push(1);
		pos = parent;
		parent = tree[pos].parent;
	}
	while (!coding.empty()) {
#ifdef DEBUG
		cout << coding.top() << flush;
#endif
		bout << coding.top();
		coding.pop();
	}
#ifdef DEBUG
	cout << endl;
#endif
	return bout;
}

int AdaptiveHuffman::findPos(int pos) {
	int i = pos;
	while (i < tree.size() && tree[pos].weight == tree[i].weight) i++;
	return i - 1;
}

void AdaptiveHuffman::update(int pos) {
	while (pos != -1) {
		int newpos = findPos(pos);
		if (newpos != pos && newpos != tree[pos].parent) {
			leaf[tree[newpos].value] = pos;
			leaf[tree[pos].value] = newpos;

			tree[tree[pos].left].parent = newpos;
			tree[tree[pos].right].parent = newpos;
			tree[tree[newpos].left].parent = pos;
			tree[tree[newpos].right].parent = pos;

			swap(tree[newpos], tree[pos]);
			swap(tree[newpos].parent, tree[pos].parent);
			pos = newpos;
		}
		tree[pos].weight++;
		pos = tree[pos].parent;
	}
}

bool AdaptiveHuffman::decode(ibstream &bin, int &pos) {
#ifdef DEBUG
	cout << endl;
#endif
	pos = Alphabet; bool flag;
	if (tree[pos].left == -1 && tree[pos].right == -1)
		return true;
	while (bin >> flag) {
		if (flag) pos = tree[pos].right;
		else pos = tree[pos].left;
#ifdef DEBUG
		cout << flag << flush;
#endif
		if (tree[pos].left == -1 && tree[pos].right == -1)
			return true;
	}
	return false;
}