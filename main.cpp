/*
 * TODO
 * 1. Exception Handling
 */

#include<iostream>
#include<climits>
#include<cstdlib>
#include<time.h>
#include<string.h>

using namespace std;

const char TEST[] = "test_case.txt";
int NO_OF_OPERATIONS = 10000;

class TreapNode{
	int key;
	int priority;
	int height;
	TreapNode *LChild;
	TreapNode *RChild;
	
	public:
		TreapNode();
		TreapNode(int k, int p);
		void rectify_height();
	friend class Treap;
};

TreapNode::TreapNode(){
	key = 0;
	priority = 0;
	height = 0;
	LChild = NULL;
	RChild = NULL;
}

TreapNode::TreapNode(int k, int p){
	key = k;
	priority = p;
	height = 0;
	LChild = NULL;
	RChild = NULL;
}

void TreapNode::rectify_height(){
	int left_height = 0;
	int right_height = 0;
	if(LChild != NULL) left_height = LChild->height;
	if(RChild != NULL) right_height = RChild->height;
	height = 1 + ((left_height > right_height)? left_height : right_height);  
}

class Treap{
	TreapNode *root;
	long long int no_of_rotations;
	long long int no_of_comparisions;
	void printTreapUtil(TreapNode* node, FILE *fptr);
	TreapNode *delete_key(TreapNode *, int);
	TreapNode *handle_priority_downwards(TreapNode *);
	bool search_key(TreapNode *, int);
	TreapNode * insert(TreapNode *, int, int);
	int get_count(TreapNode *);
	long long int get_sum_of_heights(TreapNode *);
	
	public:
		Treap();
		void insert(int);
		void insert(int k, int p);
		TreapNode * delete_key(int);
		bool search_key(int);
		void print_treap(const char *filename);
		long long int get_no_of_rotations();
		long long int get_no_of_comparisions();
		int get_height();
		long double average_height();
		
};

long long int Treap::get_no_of_comparisions(){
	return no_of_comparisions;
}

long double Treap::average_height(){
	int count = get_count(root);
	if(count != 0)
		return (1.0*get_sum_of_heights(root))/count;
	return 0;
}

int Treap::get_count(TreapNode *node){
	int LCount = 0;
	int RCount = 0;
	if(node == NULL)
		return 0;
	if(node->LChild != NULL) LCount = get_count(node->LChild);
	if(node->RChild != NULL) RCount = get_count(node->RChild);
	return (1 + LCount + RCount);
}

long long int Treap::get_sum_of_heights(TreapNode *node){
	int lheight = 0;
	int rheight = 0;
	if(node == NULL)
		return 0;
	if(node->LChild != NULL) lheight = get_sum_of_heights(node->LChild);
	if(node->RChild != NULL) rheight = get_sum_of_heights(node->RChild);
	return (node->height + lheight + rheight);
}

Treap::Treap(){
	root = NULL;
	no_of_rotations = 0;
	no_of_comparisions = 0;
}

int Treap::get_height(){
	if(root != NULL)
		return root->height;
	return 0;
}

long long int Treap::get_no_of_rotations(){
	return no_of_rotations;
}

bool Treap::search_key(int k){
	return search_key(root,k);
}

bool Treap::search_key(TreapNode *root, int k){
	if(root == NULL)
		return false;
	if(k < root->key)
		return search_key(root->LChild,k);
	if(k > root->key)
		return search_key(root->RChild,k);
	return true;
}

void Treap::insert(int k){
	int prio = rand()%100;
	root = insert(root, k, prio);
}

void Treap::insert(int k, int p){
	root = insert(root, k, p);
}

TreapNode * Treap::insert(TreapNode *root, int k, int p){
	TreapNode *node = NULL;
	if(root == NULL){
		node = new TreapNode(k,p);
		node->rectify_height();
		return node;
	}
	if(k < root->key){
		no_of_comparisions++;
		root->LChild = insert(root->LChild,k,p);
		if(root->priority > root->LChild->priority){
			//Right rotation
			TreapNode *left = root->LChild;
			TreapNode *right_of_left = left->RChild;
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
		no_of_comparisions++;
		root->RChild = insert(root->RChild,k,p);
		if(root->priority > root->RChild->priority){
			//Left rotation
			TreapNode *right = root->RChild;
			TreapNode *left_of_right = right->LChild;
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
		left->RChild = handle_priority_downwards(left->RChild);
		no_of_rotations++;
		// rectify height
		left->rectify_height();
		return left;
	}
	//left rotation
	else{
		TreapNode *right = root->RChild;
		TreapNode *left_of_right = right->LChild;
		right->LChild = root;
		root->RChild = left_of_right;
		right->LChild = handle_priority_downwards(right->LChild);
		no_of_rotations++;
		// rectify height
		right->rectify_height();
		return right;
	}
	
}

TreapNode * Treap::delete_key(TreapNode *root, int k){
	TreapNode *new_root = NULL;
	if(root == NULL)
		return NULL;
	if(k < root->key){
		no_of_comparisions++;
		root->LChild = delete_key(root->LChild, k);
		root->rectify_height();
	}else if(k > root->key){
		no_of_comparisions++;
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
	int insert[NO_OF_OPERATIONS];
	int insert_count = 0;
	int operation = 0;
	int element = 0;
	
	if ((fptr = fopen(TEST,"w")) == NULL){
		printf("Error! opening file");
		return;
	}
	fprintf(fptr, "%d\n", NO_OF_OPERATIONS);
	
	//First operation must always be insert
	element = rand()%NO_OF_OPERATIONS;
	insert[insert_count] = element;
	fprintf(fptr, "INSERT %d\n", element);
			insert_count++;
	
	// Generate random cases for next cases
	for(int i=1;i<NO_OF_OPERATIONS;i++){
		operation = rand()%2;
		if(operation == 0){
			element = rand()%NO_OF_OPERATIONS;
			insert[insert_count] = element;
			fprintf(fptr, "INSERT %d\n", element);
			insert_count++;
		}else{
			int index = rand()%insert_count;
			element = insert[index];
			fprintf(fptr, "DELETE %d\n", element);
		}
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
		cout<<"12.Print height of the treap"<<endl;
		cout<<"13.Display average height of each node"<<endl;
		cout<<"14.Update the Number of operations that should be included in test case file."<<endl;
		cout<<"15.Display number of key comparisions"<<endl;
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
				cout<<"Test case file named test_case.txt has been created"<<endl;
				break;
			case 8:
				delete(treap_obj);
				treap_obj = new Treap();
				success = take_input_from_file(treap_obj);
				if(success == 1){
					cout<<"Treap has been loaded from file"<<endl;
					cout<<"Number of rotations: "<<treap_obj->get_no_of_rotations()<<endl;
					cout<<"The height of the treap is "<<treap_obj->get_height()<<endl;
					cout<<"The average height of each node is "<<treap_obj->average_height()<<endl;
					cout<<"The number of key comparisions done during insert and delete operations is "<<treap_obj->get_no_of_comparisions()<<endl;
				}
					
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
			case 12:
				cout<<"The height of the treap is "<<treap_obj->get_height()<<endl;
				break;
			case 13:
				cout<<"The average height of each node is "<<treap_obj->average_height()<<endl;
				break;
			case 14:
				cout<<"Enter the number of operations: ";
				cin>>element;
				if(element>1){
					NO_OF_OPERATIONS = element;
					cout<<"The NO_OF_OPERATIONS has been updated to "<<NO_OF_OPERATIONS<<endl;
				}
				break;
			case 15:
				cout<<"The number of key comparisions done during insert and delete operations is "<<treap_obj->get_no_of_comparisions()<<endl;
				break;	
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
	}while(choice != 0);
	
	delete(treap_obj);
	
	return 0;
}
