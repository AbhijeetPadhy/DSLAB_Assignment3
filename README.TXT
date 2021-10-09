# DSLAB_Assignment3
Implement dictionary ADT (Abstract Data Type) using treap by taking random priority

System Requirements
======================
1. Windows(Using DEVCPP)
	i.	Install Dev CPP if not present.
	ii. Open DSLAB_Assignment3.dev file present in the project folder using DevCPP or simply double click the file to open the project.
	iii.The project opens in Dev CPP.
	iv. Compile and execute to run the project.

2. Windows(Without using DEVCPP)  
	i.	Install GNU make  
		https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download  
	ii. Install GNU GCC compiler  
	iii.Install Graphwiz  
		https://graphviz.org/download/
	Please remember to add path to environemt variable during installation for each of the above mentioned tools.
	
3. Linux  
	i. Install Graphwiz  
	https://graphviz.org/download/

Build Instructions  (Not Required if using Dev Cpp)
==================
In case you want to build the source code via terminal, use the following procedure:

run the following command in terminal in the same directory as source code:  
	make  

This is expected to produce the executable binary which goes by the name "dslab_assignment3.exe" in windows and "dslab_assignment3" in linux.

Execution instructions (Not Required if using Dev Cpp)
====================
1. Windows : In Command Prompt type
	dslab_assignment3.exe  
2. Linux  : In terminal type
	./dslab_assignment3  

/* If there us any problem in using above steps for compiling, use the following command to compile:
 *	g++ treap.cpp ThreadedBST.cpp AVL_Tree.cpp main.cpp
 *	This is supposed to create an executable which you must run to start the program.
 */

Program Instructions
====================
The program starts with the following menu:

** MENU 1 **
	This is an implementation of Assignment 3 of DS LAB
	--------------------------------------------------------
	1. Go to Treap operations
	2. Comparision operations
	3. Comparision operations automator

	Press 0 to quit.
	Enter Your Choice:

Option 1 is used to perform all kinds of operations on treap data structure which constitutes the first section of assignment.
Following menu is then disaplayed:

** MENU 2 **

	This is an implementation of Treap
	--------------------------------------------------------
	1. Insert an element
	2. Insert a series of elements
	3. Insert with priority
	4. Delete an element
	5. Search for an element
	6. Print an image of the tree
	7. Update the Number of operations that
	   should be included in test case file.
	8. Generate test cases
	9. Take input from file
	10.Print height of the treap
	11.Display average height of each node
	12.Display number of key comparisions
	13.Check number of rotations
	14.Clear Treap

	Press 0 to quit.
	Enter Your Choice:

+ To insert a single element, use option 1
+ To insert a series of elements use option 2
+ To insert an element with a specific priority use option 3
+ To delete an element use option 4
+ To search for an element use option 5

+ To print an image of the tree, use option 6. This creates a file called graph.gv.
  Use the following command to convert it into an image:
  dot -Tpng graph.gv -o graph.png
  
  Open the file graph.png to view the image of the tree.
+ Options 7, 8 and 9 allow us to create a test case file consisting of Insert and Delete 
  operations of random elements in an interleaved fashion. By default, the number of 
  operations is set at 10000. To update this, use option 7. Then use option 8 to create a
  test case file. This creates a file called test_case.txt. Then use option 9 to read 
  the file and perform operations on it. Note that when we use option 9, the previous tree
  is deleted and insertions or deletions are made on a freshly generated tree.
+ To use your own test case file, place the file inside the project folder and rename it to 
  "test_case.txt" and then use option 9 to load the tree from the file.
+ Option 10 is used to display height of the tree.
+ Option 11 is used to display average height of each node of the tree.
+ Option 12 is used to display number of key comparisions of the tree.
+ Option 13 is used to display number of rotations of the tree.

Had we chosen option 2 in MENU 1, we would get the following menu further. This menu is used to generate a test case file 
and use it to load the operations into a treap or an AVL Tree or a Threaded BST.

** MENU 3 **
This is an implementation of Comparision operations
--------------------------------------------------------
1. Generate Test Case
2. Run Test case on Threaded Binary Search Tree
3. Run Test case on AVL Tree
4. Run Test case on Treap
5. Update the Number of operations that should be included in test case file.

Press 0 to quit.
Enter Your Choice:

Use option 5 to update number of operations.
Use option 1 to generate test case file.
Use option 2,3 or 4 to load them into the respective data structures. You may also use your own test case file, provided 
it has the file name "test_case.txt" and follows the convention which is mentioned at the end of this file.

Had we chosen option 3 in MENU 1, automatically test cases are created and excuted whose data is used in the documentation 
to create the plots.

The meaning of the headings are as follows:

	//N1 = No of operations
	//N2 = BST_height 
	//N3 = AVL_height 
	//N4 = Treap_height 
	//N5 = BST_avg_ht 
	//N6 = AVL_avg_ht 
	//N7 = Treap_avg_ht
	//N8 = BST_Comp
	//N9 = AVL_Comp
	//N10 = Treap_comp
	//N11 = AVL_rot
	//N12 = Treap_rot


Convention used in Test Case File:
====================================

5
Insert 1
Delete 1
Insert 2
Insert 0
Delete 2


Flow of the Project
=======================================

	1. main.cpp : contains the code for Generating test cases, Treap implementation, Comparing three trees and automatically generating table for comparison.
	2. treap.cpp and treap.h : have definition and declaration for Treap.
	3. AVL_Tree.cpp and AVL_Tree.h : have definition and declaration for AVL Tree.
	4. ThreadedBST.cpp and ThreadedBST.h : have definition and declaration for BST.