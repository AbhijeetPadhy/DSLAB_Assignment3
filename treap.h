#ifndef TREAP_H
#define TREAP_H

#include<iostream>
#include<climits>
#include<cstdlib>
#include<time.h>
#include<string.h>

class treap_node{
	private:
		int key;
		int priority;
		int height;
		treap_node *LChild;
		treap_node *RChild;
	
	public:
		treap_node();
		treap_node(int k, int p);
		void rectify_height();
	friend class treap;
};

class treap{
	private:
		treap_node *root;
		long long int no_of_rotations;
		long long int no_of_comparisions;
		void printTreapUtil(treap_node* node, FILE *fptr);
		treap_node *delete_key(treap_node *, int);
		treap_node *handle_priority_downwards(treap_node *);
		bool search_key(treap_node *, int);
		treap_node * insert(treap_node *, int, int);
		int get_count(treap_node *);
		long long int get_sum_of_heights(treap_node *);
		void clear_tree(treap_node *node);
	
	public:
		treap();
		void insert(int);
		void insert(int k, int p);
		void delete_key(int);
		bool search_key(int);
		void print_treap(const char *filename);
		long long int get_no_of_rotations();
		long long int get_no_of_comparisions();
		int get_height();
		long double average_height();
		~treap();
};

#endif
