/*
 * TODO
 * 1. Exception Handling
 * 2. Check number of rotations during delete also when using the handle_priority_downwards method
 */

#include<iostream>
#include<climits>
#include<cstdlib>
#include<time.h>
#include<string.h>

using namespace std;

const char TEST[] = "test_case.txt";
const int NO_OF_OPERATIONS = 10;

class TreapNode{
	int key;
	int priority;
	TreapNode *LChild;
	TreapNode *RChild;
	
	public:
		TreapNode();
		TreapNode(int k, int p);
	friend class Treap;
};

TreapNode::TreapNode(){
	key = 0;
	priority = 0;
	LChild = NULL;
	RChild = NULL;
}

TreapNode::TreapNode(int k, int p){
	key = k;
	priority = p;
	LChild = NULL;
	RChild = NULL;
}

class Treap{
	TreapNode *root;
	long long int no_of_rotations;
	void printTreapUtil(TreapNode* node, FILE *fptr);
	TreapNode *delete_key(TreapNode *, int);
	TreapNode *handle_priority_downwards(TreapNode *);

	
	public:
		Treap(){
			root = NULL;
			no_of_rotations = 0;
		}
		void insert(int);
		void insert(int k, int p);
		TreapNode * insert(TreapNode *, int, int);
		TreapNode * delete_key(int);
		bool search_key(int);
		void print_treap(const char *filename);
		long long int get_no_of_rotations();
};

long long int Treap::get_no_of_rotations(){
	return no_of_rotations;
}

bool Treap::search_key(int k){
	return false;
}

void Treap::insert(int k){
	int prio = rand()%100;
	root = insert(root, k, prio);
}

void Treap::insert(int k, int p){
	root = insert(root, k, p);
}

TreapNode * Treap::insert(TreapNode *root, int k, int p){
	if(root == NULL)
		return new TreapNode(k,p);
	if(k < root->key){
		root->LChild = insert(root->LChild,k,p);
		if(root->priority > root->LChild->priority){
			//Right rotation
			TreapNode *left = root->LChild;
			TreapNode *right_of_left = left->RChild;
			left->RChild = root;
			root->LChild = right_of_left;
			no_of_rotations++;
			return left;
		}
		return root;
	}	
	else if(k > root->key){
		root->RChild = insert(root->RChild,k,p);
		if(root->priority > root->RChild->priority){
			//Left rotation
			TreapNode *right = root->RChild;
			TreapNode *left_of_right = right->LChild;
			right->LChild = root;
			root->RChild = left_of_right;
			no_of_rotations++;
			return right;
		}
		return root;
	}	
	return root; 
}

TreapNode * Treap::delete_key(int k){
	root = delete_key(root, k);
}

TreapNode * Treap::handle_priority_downwards(TreapNode *root){
	if(root == NULL)
		return NULL;
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
		TreapNode *left = root->LChild;
		TreapNode *right_of_left = left->RChild;
		left->RChild = root;
		root->LChild = right_of_left;
		no_of_rotations++;
		left->RChild = handle_priority_downwards(left->RChild);
		no_of_rotations++;
		return left;
	}
	//left rotation
	else{
		TreapNode *right = root->RChild;
		TreapNode *left_of_right = right->LChild;
		right->LChild = root;
		root->RChild = left_of_right;
		no_of_rotations++;
		right->LChild = handle_priority_downwards(right->LChild);
		no_of_rotations++;
		return right;
	}
	
}

TreapNode * Treap::delete_key(TreapNode *root, int k){
	TreapNode *new_root = NULL;
	if(root == NULL)
		return NULL;
	if(k < root->key){
		root->LChild = delete_key(root->LChild, k);
	}else if(k > root->key){
		root->RChild = delete_key(root->RChild, k);
	}else{
		root->priority = INT_MAX;
		new_root = handle_priority_downwards(root);
		delete(root);
		root = new_root;
	}
	return root;
}

// Utility Function to print tree
void Treap::printTreapUtil(TreapNode* node, FILE *fptr){
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
void Treap::print_treap(const char *filename){
	FILE *fptr;
	fptr = fopen(filename,"w");
	fprintf(fptr,"digraph G {\n");
	fprintf(fptr,"node [shape = record,height=.1];\n");
	printTreapUtil(root, fptr);
	fprintf(fptr,"}");
	fclose(fptr);
}

void generate_test_case(){
	FILE *fptr;
	int operation = 0;
	int element = 0;
	
	if ((fptr = fopen(TEST,"w")) == NULL){
		printf("Error! opening file");
		return;
	}
	fprintf(fptr, "%d\n", NO_OF_OPERATIONS);
	for(int i=0;i<NO_OF_OPERATIONS;i++){
		operation = rand()%2;
		element = rand()%99999;
		if(operation == 0)
			fprintf(fptr, "INSERT %d\n", element);
		else
			fprintf(fptr, "DELETE %d\n", element);
	}
	fclose(fptr);
}

int take_input_from_file(Treap *treap_obj){
	FILE *fptr;
	char operation[7];
	int element = 0;
	if ((fptr = fopen(TEST,"r")) == NULL){
		printf("Error! opening file\n");
		return 0;
	}
	int no_of_operations = 0;
	fscanf(fptr, "%d", &no_of_operations);
	for(int i=0;i<no_of_operations;i++){
		fscanf(fptr, "%s", &operation);
		fscanf(fptr, "%d", &element);
		if(strcmp(operation,"INSERT") == 0)
			treap_obj->insert(element);
		else if(strcmp(operation,"DELETE") == 0)
			treap_obj->delete_key(element);
	}
	return 1;
}

int main(){
	srand(time(0));
	Treap *treap_obj = new Treap();
	Treap *clone = NULL;
	generate_test_case();
	
	int choice = -1;
	int element = -1, element2=-1;
	int priority = 0;
	char str[] = "graph.gv";
	int success = 0;

	do{
		cout<<"\nThis is an implementation of AVL Tree"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Insert an element"<<endl;
		cout<<"2. Delete an element"<<endl;
		cout<<"3. Search for an element"<<endl;
		cout<<"4. Print an image of the tree"<<endl;
		cout<<"5. Insert a series of elements"<<endl;
		cout<<"6. Clone a tree and print it."<<endl;
		cout<<"7. Generate test cases"<<endl;
		cout<<"8. Take input from file"<<endl;
		cout<<"9. Check number of rotations"<<endl;
		cout<<"10.Clear Treap"<<endl;
		cout<<"11.Insert with priority"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				break;
			case 1:
				cout<<"Please enter the element you want to insert: ";
				cin>>element;
				try{
					treap_obj->insert(element);
					cout<<"Element "<<element<<" has been successfully inserted!"<<endl;
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at insert() method :: "<<msg<<endl;
				}
				break;
			case 2:
				cout<<"Please enter the element you want to delete: ";
				cin>>element;
				try{
					treap_obj->delete_key(element);
					cout<<"Element "<<element<<" has been successfully deleted!"<<endl;
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at delete_key() method :: "<<msg<<endl;
				}
				
				break;
			case 3:
				cout<<"Please enter the element you want to search: ";
				cin>>element;
				if(treap_obj->search_key(element))
					cout<<"The searched element is found!"<<endl;
				else
					cout<<"The searched element is not found!"<<endl;
				break;
			case 4: 
				cout<<"An image of the tree can be produced by using the following command: "<<endl;
				cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
				cout<<"The image will be named graph.png and will be present in the same path"<<endl;
				treap_obj->print_treap(str);
				break;
			case 5:
				cout<<"Enter the number of elements you want to insert: ";
				cin>>element;
				cout<<"Insert all the elements:"<<endl;
				for(int i=0;i<element;i++){
					cin>>element2;
					treap_obj->insert(element2);
				}
				break;
			case 6:
				cout<<"Cloning the tree..."<<endl;
				clone = new Treap(*treap_obj);
				cout<<"Printing the tree. Check the filename cloned_graph.gv"<<endl;
				clone->print_treap("cloned_graph.gv");
				cout<<"Operation Successful. Please check the file cloned_graph.gv"<<endl;
				break;
			case 7:
				generate_test_case();
				cout<<"Test case file named test.txt has been created"<<endl;
				break;
			case 8:
				delete(treap_obj);
				treap_obj = new Treap();
				success = take_input_from_file(treap_obj);
				if(success == 1)
					cout<<"Treap has been loaded from file"<<endl;
				else
					cout<<"Encountered error loading Treap from file"<<endl;
				break;
			case 9:
				cout<<"Number of rotations: "<<treap_obj->get_no_of_rotations()<<endl;
				break;
			case 10:
				delete(treap_obj);
				treap_obj = new Treap();
				cout<<"The Treap has been cleared!"<<endl;
				break;
			case 11:
				cout<<"Please enter the element you want to insert: ";
				cin>>element;
				cout<<"Please enter the priority of the element: ";
				cin>>priority;
				try{
					treap_obj->insert(element,priority);
					cout<<"Element "<<element<<" has been successfully inserted!"<<endl;
				}catch(const char* msg){
					cerr<<"\n---------WARNING----------"<<endl;
					cerr<<"Exception caught at insert() method :: "<<msg<<endl;
				}
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
	}while(choice != 0);
	
	delete(treap_obj);
	
	return 0;
}
