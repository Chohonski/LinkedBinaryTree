#include <cstdlib>
#include <iostream>
#include "LinkedBinaryTree.h"

using std::cin;
using std::cout;
using std::endl;

// test function for linked binary tree
int main () {
	LinkedBinaryTree lbt;

	lbt.addRoot();
	LinkedBinaryTree::Position p = lbt.root();
	*p = 65;

	cout << lbt << endl;

	lbt.expandExternal(p);
	LinkedBinaryTree::Position left = p.left();
	LinkedBinaryTree::Position right = p.right();
	*left = 32;
	*right = 128;

	cout << lbt << endl;

	lbt.expandExternal(left);
	p = left;
	left = p.left();
	right = p.right();
	*left = 16;
	*right = 48;

	cout << lbt << endl;

	p = lbt.root();
	p = p.right();
	lbt.expandExternal(p);
	left = p.left();
	right = p.right();
	*left = 96;
	*right = 164;

	cout << lbt << endl;

	p = left;
	lbt.removeAboveExternal(p);

	cout << lbt << endl;

	char c;
	cout << "Enter c to continue: ";
	cin >> c;

	return EXIT_SUCCESS;
}
