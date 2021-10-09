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

// ratio is a number such that we will have INSERT:DELETE = ratio:(10-ratio)
void generate_test_case(int ratio){
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
	fprintf(fptr, "Insert %d\n", element);
			insert_count++;
	
	// Generate random cases for next cases
	for(int i=1;i<NO_OF_OPERATIONS;i++){
		operation = rand()%10;
		if(operation < ratio){
			element = rand()%NO_OF_OPERATIONS;
			insert[insert_count] = element;
			fprintf(fptr, "Insert %d\n", element);
			insert_count++;
		}else{
			int index = rand()%insert_count;
			element = insert[index];
			fprintf(fptr, "Delete %d\n", element);
		}
	}
	fclose(fptr);
}

void generate_test_case(){
	int choice = 0, ratio=5;
	do{
		cout<<"\nGeneration of Test Case"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Generate an equally likely test case(Insert:Delete = 5:5)"<<endl;
		cout<<"2. Generate a test case with a specific ratio for Insert:Delete"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		switch(choice){
			case 1:
				cout<<"\nA test case file will be generated having Insert:Delete in the ratio 5:5"<<endl;
				generate_test_case(5);
				break;
			case 2:
				cout<<"\nChoose a number between 1 and 9 inclusive."<<endl;
				cout<<"If you choose 3, a test case file having Insert:Delete in ration 3:7 will be created"<<endl;
				cout<<"Enter a number between 1 and 9 inclusive: ";
				
				cin>>ratio;
				cout<<"\nA test case file will be generated having Insert:Delete in the ratio "<< ratio << ":"<< (10-ratio)<<endl;
				generate_test_case(ratio);
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
	}while(choice != 0 && choice != 1 && choice != 2);
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
		if(strcmp(operation,"Insert") == 0)
			try{
				treap_obj->insert(element);
			}catch(const char* msg){}
		else if(strcmp(operation,"Delete") == 0)
			try{
				treap_obj->delete_key(element);
			}catch(const char* msg){}	
	}
	treap_obj->print_treap("graph.gv");
	fclose(fptr);
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
		if(strcmp(operation,"Insert") == 0)
			try{
				avl_tree_object->AVL_Insert(element);
			}catch(const char* msg){}
		else if(strcmp(operation,"Delete") == 0)
			try{
				avl_tree_object->AVL_Delete(element);
			}catch(const char* msg){}
	}
	avl_tree_object->AVL_Print("graph.gv");
	fclose(fptr);
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
		if(strcmp(operation,"Insert") == 0)
			bst_object->insert(element);
		else if(strcmp(operation,"Delete") == 0)
			bst_object->deleteElement(element);
	}
	bst_object->printTree();
	fclose(fptr);
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
		cout<<"2. Insert a series of elements"<<endl;
		cout<<"3. Insert with priority"<<endl;
		cout<<"4. Delete an element"<<endl;
		cout<<"5. Search for an element"<<endl;
		cout<<"6. Print an image of the tree"<<endl;
		cout<<"7. Update the Number of operations that \n   should be included in test case file."<<endl;
		cout<<"8. Generate test cases"<<endl;
		cout<<"9. Take input from file"<<endl;
		cout<<"10.Print height of the treap"<<endl;
		cout<<"11.Display average height of each node"<<endl;
		cout<<"12.Display number of key comparisions"<<endl;
		cout<<"13.Check number of rotations"<<endl;
		cout<<"14.Clear Treap"<<endl;
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
					cerr<<"Element "<<element2<<" could not be inserted!"<<endl;
					cerr<<"Exception caught at insert() method :: "<<msg<<endl;
				}
				break;
			case 2:
				cout<<"Enter the number of elements you want to insert: ";
				cin>>element;
				cout<<"Insert all the elements:"<<endl;
				for(int i=0;i<element;i++){
					cin>>element2;
					try{
						treap_obj->insert(element2);
						cout<<"Element "<<element2<<" has been successfully inserted!"<<endl;
					}catch(const char* msg){
						cerr<<"Element "<<element2<<" could not be inserted!"<<endl;
						cerr<<"Exception caught at insert() method :: "<<msg<<endl;
					}
				}
				break;
			case 3:
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
			case 4:
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
			case 5:
				cout<<"Please enter the element you want to search: ";
				cin>>element;
				if(treap_obj->search_key(element))
					cout<<"The searched element is found!"<<endl;
				else
					cout<<"The searched element is not found!"<<endl;
				break;
			case 6: 
				cout<<"An image of the tree can be produced by using the following command: "<<endl;
				cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
				cout<<"The image will be named graph.png and will be present in the same path"<<endl;
				treap_obj->print_treap(str);
				break;
			case 7:
				cout<<"Enter the number of operations: ";
				cin>>element;
				if(element>1){
					NO_OF_OPERATIONS = element;
					cout<<"The NO_OF_OPERATIONS has been updated to "<<NO_OF_OPERATIONS<<endl;
				}
				break;
			case 8:
				generate_test_case();
				cout<<"Test case file named test_case.txt has been created"<<endl;
				break;
			case 9:
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
			case 10:
				cout<<"The height of the treap is "<<treap_obj->get_height()<<endl;
				break;
			case 11:
				cout<<"The average height of each node is "<<treap_obj->average_height()<<endl;
				break;
			
			case 12:
				cout<<"The number of key comparisions done during insert and delete operations is "<<treap_obj->get_no_of_comparisions()<<endl;
				break;	
			case 13:
				cout<<"Number of rotations: "<<treap_obj->get_no_of_rotations()<<endl;
				break;
			case 14:
				delete(treap_obj);
				treap_obj = new treap();
				cout<<"The Treap has been cleared!"<<endl;
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
					cout<<"\nThe height of the BST: "<<bst_object->get_height()<<endl;
					cout<<"The average height of each node: "<<bst_object->get_average_height()<<endl;
					cout<<"The number of key comparisions[insert & delete]: "<<bst_object->get_no_of_comparisions()<<endl;
					cout<<"\nAn image of the tree can be produced by using the following command: "<<endl;
					cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
					cout<<"The image will be named graph.png and will be present in the same path"<<endl;
				}
				delete(bst_object);
				break;
			case 3:
				avl_tree_object = new AVL_Tree();
				success = take_input_from_file(avl_tree_object);
				if(success == 1){
					cout<<"AVL Tree has been loaded from file"<<endl;
					cout<<"Number of rotations: "<<avl_tree_object->get_no_of_rotations()<<endl;
					cout<<"\nThe height of the BST: "<<avl_tree_object->get_height()<<endl;
					cout<<"The average height of each node: "<<avl_tree_object->get_average_height()<<endl;
					cout<<"The number of key comparisions[insert & delete]: "<<avl_tree_object->get_no_of_comparisions()<<endl;
					cout<<"Number of rotations: "<<avl_tree_object->get_no_of_rotations()<<endl;
					cout<<"\nAn image of the tree can be produced by using the following command: "<<endl;
					cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
					cout<<"The image will be named graph.png and will be present in the same path"<<endl;
				}
				delete(avl_tree_object);
				break;
			case 4:
				treap_obj = new treap();
				success = take_input_from_file(treap_obj);
				if(success == 1){
					cout<<"Treap has been loaded from file"<<endl;
					cout<<"Number of rotations: "<<treap_obj->get_no_of_rotations()<<endl;
					cout<<"\nThe height of the treap: "<<treap_obj->get_height()<<endl;
					cout<<"The average height of each node: "<<treap_obj->average_height()<<endl;
					cout<<"The number of key comparisions[insert & delete]: "<<treap_obj->get_no_of_comparisions()<<endl;
					cout<<"Number of rotations: "<<treap_obj->get_no_of_rotations()<<endl;
					cout<<"\nAn image of the tree can be produced by using the following command: "<<endl;
					cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
					cout<<"The image will be named graph.png and will be present in the same path"<<endl;
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

void performance_comparision_automator(int ratio){
	int arr[] = {10,50,100,300,500,1000,1500,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000,8500,9000,9500,10000};
	int N = sizeof(arr)/sizeof(int);
	treap *treap_obj;
	AVL_Tree *avl_tree_object;
	TreeAPI *bst_object;
	int element;
	int choice = -1;
	int success1 = 0, success2 = 0, success3 = 0;
	
	cout<<"\nN1\tN2\tN3\tN4\tN5\tN6\tN7\tN8\tN9\tN10\tN11\tN12"<<endl; 
	//N1 = No of operations
	//N2 = BST_height\t 
	//N3 = AVL_height\t 
	//N4 = Treap_height\t 
	//N5 = BST_avg_ht\t 
	//N6 = AVL_avg_ht\t 
	//N7 = Treap_avg_ht\t"
	//N8 = BST_Comp
	//N9 = AVL_Comp
	//N10 = Treap_comp
	//N11 = AVL_rot
	//N12 = Treap_rot
	for(int i=0;i<N;i++){
		NO_OF_OPERATIONS = arr[i];
		generate_test_case(ratio);
		
		bst_object = new TreeAPI();
		success1 = take_input_from_file(bst_object);
		
		avl_tree_object = new AVL_Tree();
		success2 = take_input_from_file(avl_tree_object);
		
		treap_obj = new treap();
		success3 = take_input_from_file(treap_obj);
		
		if(success1 == 1 && success2 == 1 && success3 == 1){
			cout<<arr[i]<<'\t';
		
			cout<<bst_object->get_height()<<'\t';
			cout<<avl_tree_object->get_height()<<'\t';
			cout<<treap_obj->get_height()<<'\t';
			
			cout<<bst_object->get_average_height()<<'\t';
			cout<<avl_tree_object->get_average_height()<<'\t';
			cout<<treap_obj->average_height()<<'\t';
			
			cout<<bst_object->get_no_of_comparisions()<<'\t';
			cout<<avl_tree_object->get_no_of_comparisions()<<'\t';
			cout<<treap_obj->get_no_of_comparisions()<<'\t';
			
			cout<<avl_tree_object->get_no_of_rotations()<<'\t';
			cout<<treap_obj->get_no_of_rotations()<<'\t';
			
			cout<<endl;
		}
		
		delete(bst_object);
		delete(avl_tree_object);
		delete(treap_obj);
	}
}

int main(int argc, char** argv) {
	srand(time(0));
	int choice = -1;
	int ratios[] = {4,5,6,7,8,9};
	int N = sizeof(ratios)/sizeof(int);
	
	do{
		cout<<"\nThis is an implementation of Assignment 3 of DS LAB"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Go to Treap operations"<<endl;
		cout<<"2. Comparision operations"<<endl;
		cout<<"3. Comparision operations automator"<<endl;
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
			case 3:
				for(int i=0;i<N;i++){
					cout<<"---------RATIO : "<< ratios[i] << ":" << (10-ratios[i])<<" ---------"<<endl;
					performance_comparision_automator(ratios[i]);
					cout<<endl;
				}	
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
			}
	}while(choice != 0);
	
	return 0;
}

