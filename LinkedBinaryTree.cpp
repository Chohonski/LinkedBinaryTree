#include <iostream>
#include "LinkedBinaryTree.h"

using std::ostream;

// function implementations for the LinkedBinaryTree class

// default constructor, makes an empty tree
LinkedBinaryTree::LinkedBinaryTree(): pRoot(NULL), n(0) { }

// copy constructor: YOU WRITE THIS!
LinkedBinaryTree::LinkedBinaryTree(const LinkedBinaryTree& lbt) {
	Node* pV = lbt.pRoot;
	copyTree(pV, lbt);
}

LinkedBinaryTree& LinkedBinaryTree::copyTree(Node* pV, LinkedBinaryTree lbt) {
	Node* pU;
	Node* pW;
	if(pV != NULL) {
		pU = pV->pLeft;
		pW = pV->pRight;
		pU->pParent = pV;
		pW->pParent = pV;

        copyTree(pV->pLeft, lbt);
        copyTree(pV->pRight, lbt);
	}

	return *this;
}

// destructor: YOU WRITE THIS!
LinkedBinaryTree::~LinkedBinaryTree() {
	deleteTree(this->pRoot);
}

void LinkedBinaryTree::deleteTree(Node* pV) {
    if(pV != NULL) {
        deleteTree(pV->pLeft);
        deleteTree(pV->pRight);
        delete pV;
	}
}

// overloaded assignment operator: YOU WRITE THIS
LinkedBinaryTree& LinkedBinaryTree::operator=(const LinkedBinaryTree& lbt) {
	Node* pV = lbt.pRoot;
	copyTree(pV, lbt);
	// the return statement stays as the last line of your function
	return *this;
}

// get the number of nodes in the tree
int LinkedBinaryTree::size() const {
	return n;
}

// is the tree empty?
bool LinkedBinaryTree::empty() const {
	return n == 0;
}

// get Position of the tree's root
LinkedBinaryTree::Position LinkedBinaryTree::root() const {
	return LinkedBinaryTree::Position(pRoot);
}

// get a list of all the nodes' positions, via a pre-order traversal
LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const {
	LinkedBinaryTree::PositionList list;

	// build the list
	preorder(pRoot, list);

	// send back a new copy of the resulting list
	return PositionList(list);
}

// add a root to the tree
void LinkedBinaryTree::addRoot() {
	pRoot = new Node();
	n = 1;
}

// turn a leaf into an internal node with two children
void LinkedBinaryTree::expandExternal(const LinkedBinaryTree::Position& p) {
	LinkedBinaryTree::Node* pV = p.pV;

	pV->pLeft = new Node();
	pV->pLeft->pParent = pV;

	pV->pRight = new Node();
	pV->pRight->pParent = pV;

	n += 2;
}

// remove a leaf node and its parent; return position of node's sibling
LinkedBinaryTree::Position 
	LinkedBinaryTree::removeAboveExternal(const LinkedBinaryTree::Position& p) {

		LinkedBinaryTree::Node* pW = p.pV;
		LinkedBinaryTree::Node* pV = pW->pParent;
		LinkedBinaryTree::Node* pSibling = (pW == pV->pLeft ? pV->pRight : pV->pLeft);

		if (pV == pRoot) {
			pRoot = pSibling;
			pSibling->pParent = NULL;
		} else {
			LinkedBinaryTree::Node* pGPa = pV->pParent;
			if (pV == pGPa->pLeft) {
				pGPa->pLeft = pSibling;
			} else {
				pGPa->pRight = pSibling;
			}
			pSibling->pParent = pGPa;
		}

		delete pW;
		delete pV;

		n -= 2;

		return LinkedBinaryTree::Position(pSibling);
}

// private helper method to build list of all the positions in
// the tree, using a pre-order traversal
void LinkedBinaryTree::preorder(LinkedBinaryTree::Node* pV, LinkedBinaryTree::PositionList& list) const {
	list.push_back(LinkedBinaryTree::Position(pV));

	if (pV->pLeft != NULL) {
		preorder(pV->pLeft, list);
	}
	if (pV->pRight != NULL) {
		preorder(pV->pRight, list);
	}
}

// overloaded stream insertion operator -- get the position list for
// the tree, then iterate through that list, putting each element out
ostream& operator<<(ostream& out, const LinkedBinaryTree& lbt) {
	LinkedBinaryTree::PositionList list = lbt.positions();

	out << "[";

	LinkedBinaryTree::PositionList::iterator i = list.begin(), j = list.end();
	while (i != j) {
		out << **i; // dereference iterator to get position, then
		// dereference position to get value

		out << " ";
		++i;
	}

	out << "]";

	return out;
}	
