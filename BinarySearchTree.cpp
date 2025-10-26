//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Antonio Colantuono
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

// Internal structure for tree node
struct Node {
	Bid bid;
	Node* left;
	Node* right;

	// default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with a bid
	Node(Bid aBid) :
		Node() {
		bid = aBid;
	}
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Bid bid);
	void inOrder(Node* node);
	void postOrder(Node* node);
	void preOrder(Node* node);
	Node* removeNode(Node* node, string bidId);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void PostOrder();
	void PreOrder();
	void Insert(Bid bid);
	void Remove(string bidId);
	Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	root = nullptr; //starting the root is equal to nullptr function call 
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
	while (root != nullptr) { //while the root does not equal null ptr remove the node 
		removeNode(root, root->bid.bidId); //removes the node with the matching bidId
	}
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	inOrder(root); //calling the inorder function while passing the root
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
	postOrder(root); //calling upon the postorder function while passing the root
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
	preOrder(root); //calling upon the preorder function while passing the root
}



/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
	if (root == nullptr) { //need a function where if the root is equal to nullptr then we want to make the root the new node bid
		root = new Node(bid);
	}
	else {
		addNode(root, bid); //if the current pointer is pointing to something then we add the node in the order of root and then bid
	}
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
	root = removeNode(root, bidId); //remove bid function calling upon the order of root, bid id
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
	Node* current = root; //current node equals root
	while (current != nullptr) { //loop function for until the bottom is reached or matching bidid
		if (current->bid.bidId == bidId) { //if the current bidId is equal to the bid id we are looking for
			return current->bid; //return that bid
		}
		else if (bidId < current->bid.bidId) {
			current = current->left; //if not move left
		}
		else {
			current = current->right; //if not move right 
		}
	}
	Bid bid;
	return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
	if (bid.bidId < node->bid.bidId) { //if the bid Id is less than the nodes bid Id
		if (node->left == nullptr) {//if the left node is equal to nullptr
			node->left = new Node(bid); //make the left node a new node 
		}
		else {
			addNode(node->left, bid); //otherwise move down the left tree 
		}
	}
	else {
		if (node->right == nullptr) { //if right node is empty
			node->right = new Node(bid); //make the right node a new node
		}
		else {
			addNode(node->right, bid); //continue searching down the right tree
			//this line of code was causing a memory leak because directions say recurse down the left node so i had it said to addNode left and then
			//when i changed it to right it fixed my memory leakage
		}
	}
}
void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) { //if node does not have an empty pointer
		inOrder(node->left); //call upon the in order left function and traverse recursvely on the subtree

		cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
			<< node->bid.fund << endl; //process the current list

		inOrder(node->right); //call upon the inorder right function and traverse recursvely on the subtree
	}
}
void BinarySearchTree::postOrder(Node* node) {
	if (node != nullptr) { //if node does not have an empty pointer 
		postOrder(node->left); //traverse the left subtree recursevely 

		postOrder(node->right); //traverse the right subtree recursevely 

		cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
			<< node->bid.fund << endl; //process the current list after both subtrees have been processed 
	}

}

void BinarySearchTree::preOrder(Node* node) {
	if (node != nullptr) { //if the node does not have an empty pointer

		cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
			<< node->bid.fund << endl; //process the current list since we are using preordered travel 

		preOrder(node->left); //traverse the left subtree recursvely 

		preOrder(node->right); //traverse the right subtree recursevely


	}

}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
	if (node == nullptr) { //if node pointer is empty
		return node; //return that node
	}
	else if (bidId < node->bid.bidId) { //if our target bid id is less than the current nodes bid id
		node->left = removeNode(node->left, bidId); //remove the left node
	}
	else if (bidId > node->bid.bidId) { //if our current bid id is greater than the current nodes bidid
		node->right = removeNode(node->right, bidId); //remove the right node 
	}
	else {
		if (node->left == nullptr && node->right == nullptr) { //if the node is a leaf aka the endpoint node 
			delete node; //delete the node
			return nullptr; //return a null pointer 
		}
		else if (node->left == nullptr) { //if the left part of the tree has a null pointer
			Node* temp = node->right; //set a temporary node equal to the right
			delete node; //delete the node
			return temp; //return the temporary node
		}

		else if (node->right == nullptr) { //if the right part of the tree has a null pointer
			Node* temp = node->left; //set the temporary node equal to the left node
			delete node;// delete the node
			return temp; //return the temporary
		}
		else {
			Node* temp = node->right; //set the temp node equal to the right node
			while (temp->left != nullptr) { //loop while the left is not a null pointer
				temp = temp->left; //keep setting the temp node to the left node
			}
			node->bid = temp->bid; //when found set the node bid to a temporary bid variable

			node->right = removeNode(node->right, temp->bid.bidId); //remove the temporary bid
			return node; //forgot to return here and had a memory leak
		}
	} 
	return node; //also forgot to return here and had a memory leak issue
	
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << endl;
	return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	// read and display header row - optional
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;

	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bst->Insert(bid);
		}
	}
	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath, bidKey;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		bidKey = "98223";
		break;
	case 3:
		csvPath = argv[1];
		bidKey = argv[2];
		break;
	default:
		csvPath = "eBid_Monthly_Sales.csv";
		bidKey = "98223";
	}

	// Define a timer variable
	clock_t ticks;

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  4. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			loadBids(csvPath, bst);

			//cout << bst->size() << " bids read" << endl;

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 2:
			bst->InOrder();
			break;

		case 3:
			ticks = clock();

			bid = bst->Search(bidKey);

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) {
				displayBid(bid);
			}
			else {
				cout << "Bid Id " << bidKey << " not found." << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 4:
			bst->Remove(bidKey);
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
