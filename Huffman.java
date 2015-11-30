import edu.princeton.cs.algs4.*;
import java.util.Arrays;

public class Huffman {
	private static final boolean DEBUG = false;
	private static int R = 256;

	private static class Node implements Comparable<Node> {
		private char ch;
		private int freq;
		private final Node left, right;

		Node(char ch, int freq, Node left, Node right) {
			this.ch = ch;
			this.freq = freq;
			this.left = left;
			this.right = right;
		}

		public boolean isLeaf() {
			return left == null && right == null;
		}

		public int compareTo(Node that) {
			return this.freq - that.freq;
		}
	}

	private static Node buildTrie(int[] freq) {
		MinPQ<Node> pq = new MinPQ<Node>();
		for (char c = 0; c < freq.length; c++)
			if (freq[c] > 0)
				pq.insert(new Node(c, freq[c], null, null));

		while (pq.size() > 1) {
			Node x = pq.delMin();
			Node y = pq.delMin();
			Node parent = new Node('\0', x.freq + y.freq, x, y);
			pq.insert(parent);
		}

		return pq.delMin();
	}

	private static String[] buildCode(Node root) {
		String[] code = new String[R];
		buildCode(root, "", code);

		if (DEBUG) {
			for (int i = 0; i < R; i++)
				System.out.println((char)i + " " + code[i]);
		}
		return code;
	}

	private static void buildCode(Node root, String s, String[] code) {
		if (root.ch != '\0') {
			code[root.ch] = s;
			return;
		}
		buildCode(root.left, s + '0', code);
		buildCode(root.right, s + '1', code);
	}

	private static int[] getFreq(char[] input) {
		int[] freq = new int[R];
		for (int i = 0; i < input.length; i++)
			freq[input[i]]++;

		if (DEBUG) {
			for (int i = 0; i < freq.length; i++)
				System.out.println((char)i + " " + freq[i]);
		}
		return freq;
	}

	private static void writeTrie(Node root) {
		if (root.isLeaf()) {
			BinaryStdOut.write(true);
			BinaryStdOut.write(root.ch);
			return;
		}
		BinaryStdOut.write(false);
		writeTrie(root.left);
		writeTrie(root.right);
	}

	private static void writeCode(String[] code, char[] input) {
		BinaryStdOut.write(input.length);

		for (int i = 0; i < input.length; i++) {
			String coding = code[input[i]];
			for (int j = 0; j < coding.length(); j++)
				if (coding.charAt(j) == '1')
					BinaryStdOut.write(true);
				else
					BinaryStdOut.write(false);
		}
	}
	
	public static void compress() {
		String s = BinaryStdIn.readString();
		char[] input = s.toCharArray();

		int[] freq = getFreq(input);
		Node trie = buildTrie(freq);
		String[] code = buildCode(trie);

		writeTrie(trie);
		writeCode(code, input);

		BinaryStdOut.close();
	}

	public static void expand() {

	}

	public static void main(String[] args) {
		if (args[0].equals("-")) compress();
		if (args[0].equals("+")) expand();

	}
}
