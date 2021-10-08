#include "treap.h"

// Name of the file where test case will be stored
const char TEST[] = "test_case.txt";

// constructor
treap_node::treap_node(){
	key = 0;
	priority = 0;
	height = 0;
	LChild = NULL;
	RChild = NULL;
}

// constructor
treap_node::treap_node(int k, int p){
	key = k;
	priority = p;
	height = 0;
	LChild = NULL;
	RChild = NULL;
}

// function to correct heights of required nodes during insert or delete
void treap_node::rectify_height(){
	int left_height = 0;
	int right_height = 0;
	if(LChild != NULL) left_height = LChild->height;
	if(RChild != NULL) right_height = RChild->height;
	height = 1 + ((left_height > right_height)? left_height : right_height);  
}

// function to return number of comparisons
long long int treap::get_no_of_comparisions(){
	return no_of_comparisions;
}

// function to return average height of all the nodes of the tree
long double treap::average_height(){
	int count = get_count(root);
	if(count != 0)
		return (1.0*get_sum_of_heights(root))/count;
	return 0;
}

// function to return number of nodes present in the treap
int treap::get_count(treap_node *node){
	int LCount = 0;
	int RCount = 0;
	if(node == NULL)
		return 0;
	if(node->LChild != NULL) LCount = get_count(node->LChild);
	if(node->RChild != NULL) RCount = get_count(node->RChild);
	return (1 + LCount + RCount);
}

// function to return the sum of heights of all nodes
long long int treap::get_sum_of_heights(treap_node *node){
	int lheight = 0;
	int rheight = 0;
	if(node == NULL)
		return 0;
	if(node->LChild != NULL) lheight = get_sum_of_heights(node->LChild);
	if(node->RChild != NULL) rheight = get_sum_of_heights(node->RChild);
	return (node->height + lheight + rheight);
}

// constructor
treap::treap(){
	root = NULL;
	no_of_rotations = 0;
	no_of_comparisions = 0;
}

// function to return height of tree
int treap::get_height(){
	if(root != NULL)
		return root->height;
	return 0;
}

//Function to return number of rotations
long long int treap::get_no_of_rotations(){
	return no_of_rotations;
}

//Function to search key
bool treap::search_key(int k){
	return search_key(root,k);
}

//Function to search key
bool treap::search_key(treap_node *root, int k){
	if(root == NULL)
		return false;
	if(k < root->key)
		return search_key(root->LChild,k);
	if(k > root->key)
		return search_key(root->RChild,k);
	return true;
}

// Function to insert an element
void treap::insert(int k){
	int prio = rand()%100;
	root = insert(root, k, prio);
}

// Function to insert an element
void treap::insert(int k, int p){
	root = insert(root, k, p);
}

// Function to insert an element
treap_node * treap::insert(treap_node *root, int k, int p){
	treap_node *node = NULL;
	if(root == NULL){
		node = new treap_node(k,p);
		node->rectify_height();
		return node;
	}
	no_of_comparisions++;
	if(k < root->key){
		root->LChild = insert(root->LChild,k,p);
		if(root->priority > root->LChild->priority){
			//Right rotation
			treap_node *left = root->LChild;
			treap_node *right_of_left = left->RChild;
			left->RChild = root;
			root->LChild = right_of_left;
			no_of_rotations++;
			
			//update heights
			root->rectify_height();
			left->rectify_height();
			
			return left;
		}else{
			root->rectify_height();
		}
		return root;
	}	
	else if(k > root->key){
		root->RChild = insert(root->RChild,k,p);
		if(root->priority > root->RChild->priority){
			//Left rotation
			treap_node *right = root->RChild;
			treap_node *left_of_right = right->LChild;
			right->LChild = root;
			root->RChild = left_of_right;
			no_of_rotations++;
			
			//manage height of right
			root->rectify_height();
			right->rectify_height();
			return right;
		}else{
			root->rectify_height();
		}
		return root;
	}	
	return root; 
}

//function to delete an element
void treap::delete_key(int k){
	root = delete_key(root, k);
}

//function to move the element found to be deleted downwards till it becomes a leaf using 
//left or right rotations
treap_node * treap::handle_priority_downwards(treap_node *root){
	if(root == NULL)
		return NULL;
	no_of_comparisions++;
	int left_child_priority = INT_MAX;
	int right_child_priority = INT_MAX;
	// root is a leaf node
	if(root->LChild == NULL && root->RChild == NULL){
		return NULL; // we need to return NULL as its parent will no longer point to this element after deletetion
	}
	// if LChild is not NULL
	if(root->LChild != NULL)
		left_child_priority = root->LChild->priority;
	// if RChild is not NULL
	if(root->RChild != NULL)
		right_child_priority = root->RChild->priority;
		
	//right rotation
	if(left_child_priority < right_child_priority){
		treap_node *left = root->LChild;
		treap_node *right_of_left = left->RChild;
		left->RChild = root;
		root->LChild = right_of_left;
		left->RChild = handle_priority_downwards(left->RChild);
		no_of_rotations++;
		// rectify height
		left->rectify_height();
		return left;
	}
	//left rotation
	else{
		treap_node *right = root->RChild;
		treap_node *left_of_right = right->LChild;
		right->LChild = root;
		root->RChild = left_of_right;
		right->LChild = handle_priority_downwards(right->LChild);
		no_of_rotations++;
		// rectify height
		right->rectify_height();
		return right;
	}
	
}

//function to delete an element
treap_node * treap::delete_key(treap_node *root, int k){
	treap_node *new_root = NULL;
	if(root == NULL)
		return NULL;
	no_of_comparisions++;
	if(k < root->key){
		root->LChild = delete_key(root->LChild, k);
		root->rectify_height();
	}else if(k > root->key){
		root->RChild = delete_key(root->RChild, k);
		root->rectify_height();
	}else{
		root->priority = INT_MAX;
		new_root = handle_priority_downwards(root);
		delete(root);
		root = new_root;
	}
	return root;
}

// Utility Function to print tree
void treap::printTreapUtil(treap_node* node, FILE *fptr){
	if(node == NULL)
		return;
	fprintf(fptr,"%d [label = \"<f0> | <f1> %d / %d | <f2>\"];\n",node->key,node->key, node->priority);
	if(node->LChild != NULL){
		printTreapUtil(node->LChild, fptr);
		fprintf(fptr,"\"%d\":f0 -> \"%d\":f1;\n",node->key,node->LChild->key);
	}
		
	if(node->RChild != NULL){
		printTreapUtil(node->RChild, fptr);
		fprintf(fptr,"\"%d\":f2 -> \"%d\":f1;\n",node->key,node->RChild->key);
	}
	
	return;
}

// Function to print tree
void treap::print_treap(const char *filename){
	FILE *fptr;
	fptr = fopen(filename,"w");
	fprintf(fptr,"digraph G {\n");
	fprintf(fptr,"node [shape = record,height=.1];\n");
	printTreapUtil(root, fptr);
	fprintf(fptr,"}");
	fclose(fptr);
}

// Function to recursively delete nodes of a tree
void treap::clear_tree(treap_node *node){
	if(node == NULL)
		return;
	clear_tree(node->LChild);
	clear_tree(node->RChild);
	delete(node);
	return;
}

// Destructor
treap::~treap(){
	clear_tree(root);
	root = NULL;
}
