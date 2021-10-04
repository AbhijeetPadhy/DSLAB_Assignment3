class AVL_Node{
	private:
		int key;
		int bf; //balance factor bf = height(left subtree) - height(right subtree)
		AVL_Node *LChild, *RChild;
		int height;
	public:
		AVL_Node(int k);
	friend class AVL_Tree;
};

class Stack_Node{
	public:
		AVL_Node *node;
		int a;
		Stack_Node();
		Stack_Node(AVL_Node *P, int n);
};

class AVL_Tree{
	private:
		AVL_Node *root;
		void printTreeUtil(AVL_Node* node, FILE *fptr);
		bool AVL_Search_util(AVL_Node *node, int k);
		AVL_Node* AVL_Clone(AVL_Node *node);
		void AVL_ClearTree(AVL_Node *node);
		int count_of_nodes(AVL_Node*);
		int sum_of_height_of_nodes(AVL_Node*);
		int get_height(AVL_Node*);
	
	public:
		AVL_Tree();
		AVL_Tree(const AVL_Tree &T);
		AVL_Tree &operator=(const AVL_Tree &T);
		void AVL_Insert(int k);
		void AVL_Delete(int k);
		bool AVL_Search(int k);
		void AVL_Print(const char *filename);
		int get_height();
		double get_average_height();
		~AVL_Tree();
};

