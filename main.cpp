#include<iostream>
#include<climits>
#include<cstdlib>
#include<time.h>
#include<string.h>

using namespace std;
#include "treap.h"
#include "AVL_Tree.h"
#include "ThreadedBST.h"

const char TEST[] = "test_case.txt";
int NO_OF_OPERATIONS = 10000;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

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


int take_input_from_file(treap *treap_obj){
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
	treap_obj->print_treap("graph.gv");
	return 1;
}

int take_input_from_file(AVL_Tree *avl_tree_object){
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
			try{
				avl_tree_object->AVL_Insert(element);
			}catch(const char* msg){}
		else if(strcmp(operation,"DELETE") == 0)
			try{
				avl_tree_object->AVL_Delete(element);
			}catch(const char* msg){}
	}
	avl_tree_object->AVL_Print("graph.gv");
	return 1;
}

int take_input_from_file(TreeAPI *bst_object){
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
			bst_object->insert(element);
		else if(strcmp(operation,"DELETE") == 0)
			bst_object->deleteElement(element);
	}
	bst_object->printTree();
	return 1;
}

void treap_executor(){
	treap *treap_obj = new treap();
	treap *clone = NULL;
	
	int choice = -1;
	int element = -1, element2=-1;
	int priority = 0;
	char str[] = "graph.gv";
	int success = 0;

	do{
		cout<<"\nThis is an implementation of Treap"<<endl;
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
				clone = new treap(*treap_obj);
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
				treap_obj = new treap();
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
				treap_obj = new treap();
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
}

void performance_comparator(){
	treap *treap_obj;
	AVL_Tree *avl_tree_object;
	TreeAPI *bst_object;
	int element;
	int choice = -1;
	int success = 0;
	
	do{
		cout<<"\nThis is an implementation of Comparision operations"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Generate Test Case"<<endl;
		cout<<"2. Run Test case on Threaded Binary Search Tree"<<endl;
		cout<<"3. Run Test case on AVL Tree"<<endl;
		cout<<"4. Run Test case on Treap"<<endl;
		cout<<"5. Update the Number of operations that should be included in test case file."<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				break;
			case 1:
				generate_test_case();
				cout<<"Test case file named test_case.txt has been created"<<endl;
				break;
			case 2:
				bst_object = new TreeAPI();
				success = take_input_from_file(bst_object);
				if(success == 1){
					cout<<"BST has been loaded from file"<<endl;
					//cout<<"Number of rotations: "<<bst_object->get_no_of_rotations()<<endl;
					cout<<"The height of the BST is "<<bst_object->get_height()<<endl;
					cout<<"The average height of each node is "<<bst_object->get_average_height()<<endl;
					cout<<"The number of key comparisions done during insert and delete operations is "<<bst_object->get_no_of_comparisions()<<endl;
				}
				delete(bst_object);
				break;
			case 3:
				avl_tree_object = new AVL_Tree();
				success = take_input_from_file(avl_tree_object);
				if(success == 1){
					cout<<"AVL Tree has been loaded from file"<<endl;
					//cout<<"Number of rotations: "<<avl_tree_object->get_no_of_rotations()<<endl;
					cout<<"The height of the BST is "<<avl_tree_object->get_height()<<endl;
					cout<<"The average height of each node is "<<avl_tree_object->get_average_height()<<endl;
					//cout<<"The number of key comparisions done during insert and delete operations is "<<avl_tree_object->get_no_of_comparisions()<<endl;
				}
				delete(avl_tree_object);
				break;
			case 4:
				treap_obj = new treap();
				success = take_input_from_file(treap_obj);
				if(success == 1){
					cout<<"Treap has been loaded from file"<<endl;
					cout<<"Number of rotations: "<<treap_obj->get_no_of_rotations()<<endl;
					cout<<"The height of the treap is "<<treap_obj->get_height()<<endl;
					cout<<"The average height of each node is "<<treap_obj->average_height()<<endl;
					cout<<"The number of key comparisions done during insert and delete operations is "<<treap_obj->get_no_of_comparisions()<<endl;
				}
				delete(treap_obj);
				break;
			case 5:
				cout<<"Enter the number of operations: ";
				cin>>element;
				if(element>1){
					NO_OF_OPERATIONS = element;
					cout<<"The NO_OF_OPERATIONS has been updated to "<<NO_OF_OPERATIONS<<endl;
				}
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
			}
	}while(choice != 0);
	return;
}

int main(int argc, char** argv) {
	srand(time(0));
	int choice = -1;
	
	do{
		cout<<"\nThis is an implementation of Assignment 3 of DS LAB"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Go to Treap operations"<<endl;
		cout<<"2. Comparision operations"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				break;
			case 1:
				treap_executor();
				break;
			case 2:
				performance_comparator();
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
			}
	}while(choice != 0);
	
	return 0;
}

