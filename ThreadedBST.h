#ifndef THREADEDBST_H
#define THREADEDBST_H

#include <iostream>

// Class for implementation of a Threaded Binary Search Tree
class ThreadedBST{
		ThreadedBST *leftChild; // Stores pointer of left child. It can be NULL, or it can also point as a thread to its predecessor if there is no left child.
		bool leftThread;        // It is true when leftChild is NULL or is pointing as a thread to its predecessor. It is false when leftChild is pointing to its left child node
		int key;                // Data value of a tree node
		bool rightThread;       // It is true when rightChild is NULL or is pointing as a thread to its successor. It is false when rightChild is pointing to its right child node.
		ThreadedBST *rightChild;// Stores pointer of right child. It can be NULL, or it can also point as a thread to its successor if there is no right child.
		int rcount;             // Stores size of right subtree
		
		ThreadedBST *leftMost(ThreadedBST *root);                   //Returns the left most tree node
		ThreadedBST *rightMost(ThreadedBST *root);                  //Returns the right most tree node
		int printTreeUtil(FILE*);                                   // Utility helper function for printTree
		void printTree(char *);                                     // Creates a pictorial image of the tree but the gv file name has to be specified in arguement
		
	public:
		//constructor
		ThreadedBST(int val);                                       // Constructor to create a new tree node having key value val
		void insert(int val);                                       // Inserts a new tree node with value val
		int getKey();                                               // Returns the key value of the current node
		ThreadedBST *deleteElement(int val);                        // Delete a node of the tree with value equal to val
		ThreadedBST *successor(ThreadedBST *);                      // Returns pointer to the successor node of the node passed in arguement.
		void printTree();                                           // Creates a pictorial image of the tree
};

// An API which is provided to do operations on a tree for ease of access
class TreeAPI{
	ThreadedBST *root;
	public:
		TreeAPI(){
			root = NULL;
		}
		void insert(int val){
			if(root == NULL)
				root = new ThreadedBST(val);
			else{
				try{
					root->insert(val);
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at insert() method :: "<<msg<<endl;
				}
			}
		}
		ThreadedBST *deleteElement(int val){
			if(root != NULL){
				try{
					root = root->deleteElement(val);
					return root;
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at deleteElement() method :: "<<msg<<endl;
				}
			}	
			return NULL;
		}
		
		void printTree(){
			if(root == NULL)
				cout<<"The tree is empty now. Hence it cannot be printed!"<<endl;
			else
				root->printTree();
		}
};

#endif
