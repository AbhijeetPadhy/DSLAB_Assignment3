#include<iostream>
#include<climits>
#include<cstdlib>
#include<time.h>

using namespace std;

const char TEST[] = "test_case.txt";
const int NO_OF_OPERATIONS = 10000;

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
	void printTreapUtil(TreapNode* node, FILE *fptr);
	
	public:
		Treap(){
			root = NULL;
		}
		void insert(int);
		TreapNode * insert(TreapNode *, int, int);
		TreapNode * delete_key(int);
		bool search_key(int);
		void print_treap(const char *filename);
};

bool Treap::search_key(int k){
	return false;
}

void Treap::insert(int k){
	int prio = rand()%100;
	root = insert(root, k, prio);
}

TreapNode * Treap::insert(TreapNode *root, int k, int p){
	if(root == NULL)
		return new TreapNode(k,p);
	if(k < root->key)
		root->LChild = insert(root->LChild,k,p);
	else if(k > root->key)
		root->RChild = insert(root->RChild,k,p);
	return root; 
}

TreapNode * Treap::delete_key(int k){
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

int main(){
	srand(time(0));
	Treap *treap_obj = new Treap();
	Treap *clone = NULL;
	generate_test_case();
	
	int choice = -1;
	int element = -1, element2=-1;
	char str[] = "graph.gv";

	do{
		cout<<"\nThis is an implementation of AVL Tree"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Insert an element"<<endl;
		cout<<"2. Delete an element"<<endl;
		cout<<"3. Search for an element"<<endl;
		cout<<"4. Print an image of the tree"<<endl;
		cout<<"5. Insert a series of elements"<<endl;
		cout<<"6. Clone a tree and print it."<<endl;
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
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
	}while(choice != 0);
	
	delete(treap_obj);
	
	return 0;
}
