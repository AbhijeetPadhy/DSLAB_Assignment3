#include "ThreadedBST.h"

//constructor
ThreadedBST::ThreadedBST(int val){
	key = val;
	leftThread = true;
	rightThread = true;
	leftChild = NULL;
	rightChild = NULL;
	rcount = 0;
}

// Function to find out left most node in a tree
ThreadedBST *ThreadedBST::leftMost(ThreadedBST *root){
	ThreadedBST *cur = root;
	while(cur->leftThread == false)
		cur = cur->leftChild;
	return cur;
}

// Function to find out right most node in a tree
ThreadedBST *ThreadedBST::rightMost(ThreadedBST *root){
	ThreadedBST *cur = root;
	while(cur->rightThread == false)
		cur = cur->rightChild;
	return cur;
}

// Function to insert a new node with a key value of val in a tree
void ThreadedBST::insert(int val){
	// If val < key, recur for left sub tree
	if(val<key){
		if(leftThread == true){
			ThreadedBST *temp = new ThreadedBST(val);
			if(leftChild != NULL){
				temp->leftChild = leftChild;
				temp->leftThread = leftThread;
			}
			temp->rightChild = this;
			temp->rightThread = true;
			leftThread = false;
			leftChild = temp;
			
		}else
			leftChild->insert(val);
	}
	// If val > key, recur for right sub tree	
	else if(val > key){
		rcount++;
		if(rightThread == true){
			ThreadedBST *temp = new ThreadedBST(val);
			if(rightChild != NULL){
				temp->rightChild = rightChild;
				temp->rightThread = rightThread;
			}
			temp->leftChild = this;
			temp->leftThread = true;
			rightThread = false;
			rightChild = temp;
		}
		else
			rightChild->insert(val);
	}
	// If element already exists, return exception
	else 
		throw "Element already exists Exception!";
}


// Function to delete an element in a tree, Exception is thrown if element to be deleted is not found
ThreadedBST* ThreadedBST::deleteElement(int val){
	// If this is the node to be deleted
	if(key == val){
		//case1: leaf node
		if(leftThread == true && rightThread == true){
			delete(this);
			return NULL;
		}
		//case2: one child
		else if(leftThread || rightThread){
			if(leftThread == false){ //left child exists
				ThreadedBST *left = leftChild;
				//If left child does not have a right child, then it points to the current node. Hence we need to set rightChild pointer
				//of leftChild to point to rightChild pointer of current node.
				if(leftChild->rightThread == true){
					leftChild->rightChild = rightChild;
				}else{
					ThreadedBST *rightMostOfLeft = rightMost(leftChild);
					rightMostOfLeft->rightChild = rightChild;
				}	
				delete(this);
				return left;
			}else{//right child exists
				ThreadedBST *right = rightChild;
				//If right child does not have a left child, then it points to the current node. Hence we need to set leftChild pointer
				//of rightChild to point to leftChild pointer of current node.
				if(rightChild->leftThread == true ){
					rightChild->leftChild = leftChild;
				}else{
					ThreadedBST *leftMostOfRight = leftMost(rightChild);
					leftMostOfRight->leftChild = leftChild;
				}
				delete(this);
				return right;
			}
		}
		//case3: two children
		else{
			ThreadedBST *successor = leftMost(rightChild);
			
			key = successor->key;
			rightChild = rightChild->deleteElement(key);
			
			if(rightChild == NULL)
				rightThread = true;
			rcount--;
			return this;
		}
	// If val  <key recur for left sub tree
	}else if(val < key){
		if(leftThread == false){
			ThreadedBST *leftOfLeft = leftChild->leftChild;
			ThreadedBST *left = leftChild->deleteElement(val);
			
			if(left == NULL){
				leftChild = leftOfLeft;
				leftThread = true;
			}
			else
				leftChild = left;
		}
		else
			throw "Element not Found Exception!";
	// If val > key recur for right sub tree
	}else{
		if(rightThread == false){
			ThreadedBST *rightOfRight = rightChild->rightChild;
			ThreadedBST *right = rightChild->deleteElement(val);
			rcount--;
			if(right == NULL){
				rightChild = rightOfRight;
				rightThread = true;
			}	
			else
				rightChild = right;
		}
		else
			throw "Element not Found Exception!";
	}
	return this;
}

// Getter function to get the value of private member variable key
int ThreadedBST::getKey(){
	return key;
}

// Function to find successor of a node passed in argument
ThreadedBST *ThreadedBST::successor(ThreadedBST *root){
	if(root->rightThread == true){
		return root->rightChild;	
	}
	return leftMost(root->rightChild);
}

// Utility function which helps to print tree in a .gv file to be used by graphviz tool to produce an image
int ThreadedBST::printTreeUtil(FILE *fptr){
	fprintf(fptr,"node%d [label = \"<f0> | <f1> %d | <f2>\"];\n",key,key);
	if(leftThread == false){
		leftChild->printTreeUtil(fptr);
		fprintf(fptr,"\"node%d\":f0 -> \"node%d\":f1;\n",key,leftChild->key);
	}else if(leftChild != NULL)
		fprintf(fptr,"\"node%d\":f0 -> \"node%d\":f1 [style=dotted];\n",key,leftChild->key);
		
	if(rightThread == false){
		rightChild->printTreeUtil(fptr);
		fprintf(fptr,"\"node%d\":f2 -> \"node%d\":f1;\n",key,rightChild->key);
	}else if(rightChild != NULL)
		fprintf(fptr,"\"node%d\":f2 -> \"node%d\":f1 [style=dotted];\n",key,rightChild->key);
	
	return key;
}

// Function to print tree in a .gv file to be used by graphviz tool to produce an image 
void ThreadedBST::printTree(){
	char str[] = "graph.gv";
	printTree(str);
}

// Creates a pictorial image of the tree but the gv file name has to be specified in argument
void ThreadedBST::printTree(char *str){
	FILE *fptr;
	fptr = fopen(str,"w");
	fprintf(fptr,"digraph G {\n");
	fprintf(fptr,"node [shape = record,height=.1];\n");
	printTreeUtil(fptr);
	fprintf(fptr,"}");
	fclose(fptr);
}

TreeAPI::TreeAPI(){
	root = NULL;
}
void TreeAPI::insert(int val){
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
ThreadedBST* TreeAPI::deleteElement(int val){
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

void TreeAPI::printTree(){
	if(root == NULL)
		cout<<"The tree is empty now. Hence it cannot be printed!"<<endl;
	else
		root->printTree();
}
