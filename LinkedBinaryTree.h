#ifndef LINKED_BINARY_TREE
#define LINKED_BINARY_TREE

#include <cstdlib>
#include <list>
#include <ostream>

using std::ostream;

// class for a linked binary tree of integers
class LinkedBinaryTree {
private:
	// private, internal Node class 
	class Node {
	public:
		int e;			// node value
		Node* pParent;	// pointer to parent
		Node* pLeft;	// pointer to left child
		Node* pRight;	// pointer to right child

		// default constructor
		Node() : e(), pParent(NULL), pLeft(NULL), pRight(NULL) { }
	};

public:
	// public, internal Position class
	class Position {
	private:
		Node* pV;		// pointer to this position's Node

		// constructor is private so Positions can be managed
		// by the LinkedBinaryTree class
		Position(Node* pU = NULL) : pV(pU) { }


	public:

		// overload assignment operator to allow input into
		// Node's int
		void operator=(int i) { pV->e = i; }

		// overload dereferencing operator to allow access to 
		// Node's int
		int& operator*() { return pV->e; }

		// get Position to the left child
		Position left() const { return Position(pV->pLeft); }

		// get Position to the right child
		Position right() const { return Position(pV->pRight); }

		// get Position to the parent
		Position parent() const { return Position(pV->pParent); }

		// is this Position at the root?
		bool isRoot() const { return pV->pParent == NULL; }

		// is this Position at a leaf?
		bool isExternal() const { return pV->pLeft == NULL &&
			pV->pRight == NULL; }

		// friend the LinkedBinaryTree class, so it can access the
		// private constructor
		friend class LinkedBinaryTree;
	};

	///////////////////////////////////////////////////////////////
	// LinkedBinaryTree definitions follow
	///////////////////////////////////////////////////////////////

	// clean up the syntax a little by providing a new name for the
	// list of positions
	typedef std::list<Position> PositionList;

	// default constructor
	LinkedBinaryTree();

	// copy constructor
	LinkedBinaryTree(const LinkedBinaryTree& lbt);

	LinkedBinaryTree& copyTree(Node* pV, LinkedBinaryTree lbt);

	// destructor
	~LinkedBinaryTree();

	void deleteTree(Node* pV);

	// overloaded assignment operator 
	LinkedBinaryTree& operator=(const LinkedBinaryTree& lbt);

	// how many nodes in the tree?
	int size() const;

	// is the tree empty?
	bool empty() const;

	// get Position of the root node
	Position root() const;

	// get a list of all the nodes' positions, via a pre-order traversal
	PositionList positions() const;

	// add the root node to the tree
	void addRoot();

	// change an existing leaf into an internal node with two children
	void expandExternal(const Position& p);

	// remove leaf p and its parent
	Position removeAboveExternal(const Position& p);

	// overloaded stream insertion operator
	friend ostream& operator<<(ostream& out, const LinkedBinaryTree& lbt); 

private:
	// Pointer to the root node of the tree
	Node* pRoot;

	// number of nodes in the tree
	int n;

	// preorder traversal used to create the list returned by the 
	// positions() function
	void preorder(Node* pV, PositionList& list) const;
};

#endif