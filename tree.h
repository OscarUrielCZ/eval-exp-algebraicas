/* Data */

typedef char *DataT;

void printDataT(DataT d) {
	printf("%s", d);
}

/* Tree */

typedef struct NodeT {
	DataT r;
	struct NodeT *left;
	struct NodeT *right;
} *Tree;

Tree emptyT() {
	return NULL;
}

int isEmptyT(Tree t) {
	return t == NULL;
}

Tree create(Tree l, DataT d, Tree r) {
	Tree temp = (Tree)malloc(sizeof(struct NodeT));

	temp->r = d;
	temp->left = l;
	temp->right = r;

	return temp;
}

DataT root(Tree t) {
	return t->r;
}

Tree rightBranch(Tree t) {
	return t->right;
}

Tree leftBranch(Tree t) {
	return t->left;
}

void inorder(Tree t) {
	if(!isEmptyT(t)) {
		inorder(leftBranch(t));
		printDataT(root(t));
		inorder(rightBranch(t));
	}
}