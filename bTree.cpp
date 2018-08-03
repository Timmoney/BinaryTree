/*
Binary Tree --> each node can have at most 2 children
linked list implementation
c --> malloc
c++ --> new
NULL is a macro for 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue> //for level order traversal
using namespace std;
//binary search node
struct BstNode{
	int data;
	BstNode* left;
	BstNode* right;
};
//prototyping
BstNode* GetNewNode(int data); //create bstNode
BstNode* Insert(BstNode* root, int data); //insert passing root
bool Search(BstNode* root, int data); //search for data in the tree
int FindMin(BstNode* root); //min int in the bst
int FindMax(BstNode* root); //max
int max(int a, int b); //return greater a or b
int Findheight(BstNode* root);
void LevelOrder(BstNode* root); //print out all the elements
void preOrder(BstNode* root);
void inOrder(BstNode* root);
void postOrder(BstNode* root);
bool isSubTLesser(BstNode* root, int value); //left subtree
bool isSubGreater(BstNode* root, int value); //right subtree
bool isBST(BstNode* root); //recursive O(n^2)
bool isBSTUtil(BstNode* root, int minValue, int maxValue);//using in isBST2
bool isBST2(BstNode* root); //O(n)
BstNode* FindMinAddress(BstNode* root);
BstNode* delNode(BstNode* root, int data);
BstNode* Find(BstNode* root, int data); //return address
BstNode* GetSuccessor(BstNode* root, int data); //get the successor, and return that node

int main(){
	//creating the original tree
	BstNode* root = NULL;
	root = Insert(root, 12);
	root = Insert(root, 5);
	root = Insert(root, 3);
	root = Insert(root, 7);
	root = Insert(root, 1);
	root = Insert(root, 9);
	root = Insert(root, 15);
	root = Insert(root, 13);
	root = Insert(root, 17);

	/*testing for search method*/
	if(Search(root, 17)){
		printf("17 is found in the tree.\n");
	}
	if(!Search(root, 20)){
		printf("20 is not found in the tree.\n" );
	}

	printf("\n");

	/*testing for FindMin*/
	printf("The min value in the tree is %d\n", FindMin(root));

	/*testing for FindMax*/
	printf("The max value in the tree is %d\n", FindMax(root));

	printf("\n");

	/*testing for FindHeight*/
	printf("The height of the tree is %d\n", Findheight(root));

	printf("\n");

	/*testing for level of order*/
	LevelOrder(root);  

	printf("\n\n");

	/*testing for pre-oreder*/
	preOrder(root);
	printf("\n\n");


	/*testing for pre-oreder*/
	inOrder(root);
	printf("\n\n");


	/*testing for pre-oreder*/
	postOrder(root);
	printf("\n\n");




	//LevelOrder(root); 
	// delNode(root, 15);
	// LevelOrder(root);

	// BstNode* p = Find(root, 5);
	// printf("%d\n", p->data);
	//BstNode* p = GetSuccessor(root, 5);
	//printf("%d\n", p->data);

	//cout << FindMin(root) <<endl;
	//cout << FindMax(root) <<endl;
	//cout << Findheight(root) <<endl;

	//preOrder(root);
	//inOrder(root);
	//postOrder(root);

	//LevelOrder(root);

	// int x;
	// cout << "Enter your number be search\n";
	// cin >> x;
	// if(Search(root,x)==true) cout <<"Found\n";
	// else cout<<"Not found\n";
}


bool Search(BstNode* root, int data){
	//recursive end condition
	if(root == NULL) return false;
	if(root->data == data) return true;

	else if(data<root->data) return Search(root->left,data);
	else return Search(root->right,data);
}

//find the address of the node
BstNode* Find(BstNode* root, int data){
	BstNode* ptr = root;
	if(ptr == NULL) return ptr;
	if(ptr->data == data) return ptr;
	else if(data<=ptr->data) return Find(ptr->left, data);
	else return Find(ptr->right, data);
}

BstNode* GetSuccessor(BstNode* root, int data){
	//search the node - O(h)
	BstNode* current = Find(root, data);
	if(current == NULL) return NULL;
	//case 1: node has right subtree, and find the min in the right subtree
	if(current->right != NULL){
		return FindMinAddress(current->right);
	}
	//case 2: node have no right subtree
	else{
		BstNode* successor = NULL;
		BstNode* ancestor = root;
		while(ancestor != current){
			if(current->data < ancestor->data){
				successor = ancestor;
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}

//find the node address
BstNode* FindMinAddress(BstNode* root){
	BstNode* ptr = root;
	if(ptr == NULL) return NULL;
	while(ptr->left!=NULL){
		ptr = ptr->left;
	}
	return ptr;	
}

//the root actually change every time you recurse it
BstNode* delNode(BstNode* root, int data){
	if(root == NULL) return root;
	//using recursion to find the location
	else if(data < root->data){
		root->left = delNode(root->left,data);
	}
	else if(data > root->data){
		root->right = delNode(root->right,data);
	}
	else{
		//case 1: no child
		if(root->left == NULL && root->right == NULL){
			delete root; //deallocate the memory in heap in c is "free"
			root = NULL;
		}
		//case 2: one child
		else if(root->left == NULL){
			BstNode* p = root;
			root = root->right;
			delete p;
		}
		else if(root->right == NULL){
			BstNode* p = root;
			root = root->left;
			delete p;
		}
		//case 3: two children
		else{
			BstNode* p = FindMinAddress(root->right);
			root->data = p->data; //replace data
			root->right = delNode(root->right,p->data);
		}	
	}
	return root;
}

BstNode* GetNewNode(int data){
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode; //address, whenever you create a node, you return that address
}

BstNode* Insert(BstNode* root, int data){
	//empty tree
	//recursive end condition
	if(root == NULL){
		root = GetNewNode(data);
	}
	else if(data <= root->data){
		root->left = Insert(root->left, data);
	}
	else{
		root->right = Insert(root->right, data);
	}
	return root;
}


int FindMin(BstNode* root){
	BstNode* ptr = root;
	while(ptr->left!=NULL){
		ptr = ptr->left;
	}
	if(ptr->right!=NULL){
		ptr = ptr->right;
		return ptr->data;
	} 
	else return ptr->data;	
}

int FindMax(BstNode* root){
	BstNode* ptr = root;
	while(ptr->right!=NULL){
		ptr = ptr->right;
	}
	if(ptr->left!=NULL){
		ptr = ptr->left;
		return ptr->data;
	} 
	else return ptr->data;	
}

int max(int a, int b){
	if(a==b) return a;
	else if(a>b) return a;
	else return b;
}

int Findheight(BstNode* root){
	int leftH;
	int rightH;

	//base case with the subtree is empty return -1 
	if(root == NULL) 
		return -1; //for balance out
	leftH = Findheight(root->left);
	rightH = Findheight(root->right);

	return max(leftH, rightH)+1;
}

//level order traversal
void LevelOrder(BstNode* root){
	if(root == NULL) return;
	queue<BstNode*> Q;
	Q.push(root); //set the address of the roots
	while(!Q.empty()){
		BstNode* current = Q.front();
		cout << current->data << " ";
		if(current->left!=NULL) Q.push(current->left);
		if(current->right!=NULL) Q.push(current->right);
		Q.pop();//removing the element at front
	}
}

//<root><left><right>
/*
The idea of recursive is that it will pause, then resume
that's why after resume from preOrder(root->left), 
then preOrder(root->right) will keep going
*/
void preOrder(BstNode* root){
	if(root==NULL) return;
	printf("%d ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}

//<left><root><right>
void inOrder(BstNode* root){
	if(root == NULL) return;
	inOrder(root->left);
	printf("%d ", root->data);
	inOrder(root->right);
}

//<left><right><root>
void postOrder(BstNode* root){
	if(root == NULL) return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->data);

}

//this is an expensive operation
bool isSubTLesser(BstNode* root, int value){
	if(root == NULL) return true;
	if(root->data <= value
		&& isSubTLesser(root->left, value)
		//this actually check the left sub tree compare with root
		&& isSubTLesser(root->right, value))
		return true;
	else
		return false;
}

//this is an expensive operation
bool isSubGreater(BstNode* root, int value){
	if(root == NULL) return true;
	if(root->data > value
		&& isSubGreater(root->left, value)
		//this actually check the right sub tree compare with root
		&& isSubGreater(root->right, value))
		return true;
	else
		return false;
}

//recursive one, time complexity O(n^2)
bool isBST(BstNode* root){

	if(root == NULL) return true; //base case

	if(isSubTLesser(root->left,root->data) 
		&& isSubGreater(root->right, root->data)
		&& isBST(root->left)
		&& isBST(root->right)){
		return true;
	}
	else return false;
}

//better one
bool isBSTUtil(BstNode* root, int minValue, int maxValue){
	if(root == NULL) return true; //base case

	if(root->data >= minValue 
		&& root->data < maxValue
		&& isBSTUtil(root->left, minValue, root->data)
		&& isBSTUtil(root->right, root->data, maxValue)){
		return true;
	}
	else return false;
}

//better one time complexity O(n)
bool isBST2(BstNode* root){
	//INT_MIN and INT_MAX are macro
	return isBSTUtil(root, INT_MIN, INT_MAX);
}




