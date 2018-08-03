A complete binary tree with most operations

Function details:
1.BstNode* GetNewNode(int data)
        creating a new node and return that node's address
        
2.BstNode* Insert(BstNode* root, int data)
        inserting a new node with int data
        
3.Bool Search(BstNode* root, int data)
        searching data return booleanBool
    
4.FindMin/FindMax
        find the minimum and maximum value in the treeand
    
5.FindHeight(BstNode* root)
        return heigh of the tree

6.LevelOrder(BstNode* root)
        print out the tree in level order
        
7.preOrder(BstNode* root)
        root, left, right

8.inOrder(BstNode* root)
        left, root, right

9.postOrder(BstNode* root)
        left, right, root
        
10.isSubTLesser(BstNode* root, int value)
        check if sub tree is lesser than the value
        
11.isSubTGreater(BstNode* root, int value)
        check if sub tree is greater than the value
        
12.isBST(BstNode* root)
        check if tree is a binary search tree
    
13.isBSTUtil(BstNode* root, int minValue, int maxValue)
        compare min and max in the tree
        
14.isBST2(BstNode* root)
        check if the tree is binary search tree using min and max

