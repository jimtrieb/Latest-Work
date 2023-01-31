
#ifndef H_BINARYTREE
#define H_BINARYTREE
#include "node.h"

typedef enum {left_side, right_side } SIDE; //rand function to choose which node data will go to

SIDE rnd(){ 
    return rand()%2 ? right_side : left_side;
}// End of rnd()

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

template <typename T> BinaryTree<T>::BinaryTree(){} //constructor

//name:getSize
//use:calls private _getSize passed parameter root to get size of tree
//parameters:none
//retuns: unsigned const
template <typename T> unsigned BinaryTree<T>::getSize() const
{
	return _getSize(root); //retuns _getSize function value with root as parameter
}

//name:getHeight
//use: calls private _getHeight passed parameter root to get height of tree
//parameters:none
//returns: unsigned const
template <typename T> unsigned BinaryTree<T>::getHeight() const
{
	return _getHeight(root); //returns _getHeight function value with root as a parameter
}

//name:Insert
//use: to insert a node into binary tree
//parameters: node of type T
//retuns: none
template <typename T> void BinaryTree<T>::Insert(const T& data)
{
			_Insert(root, data); //returns _Insert function value with root and data as parameters. Data is value of node 
}	

//name: Inorder
//use:Traverse the binary tree in inorder
//parameters: function pointer used in tree operations
//retuns: none
template <typename T> void BinaryTree<T>::Inorder(void (*node_operation)(const T&))
{
	_Inorder(root,node_operation); //returns _Inorder value with root and node operation as parameters
}

//name:_getSize
//use: to get size of binary tree
//parameters: const node pointer of type T
//returns: unsigned const which is size
template <typename T> unsigned BinaryTree<T>::_getSize(Node<T> *node) const
{
	if (!node) //if statement for when the node is null
	{
		return 0;
	}

	unsigned int left_size = _getSize(node->left); //finds size of left subtrees
	unsigned int right_size = _getSize(node->right); //finds size of right subtrees
	return left_size + right_size + 1; //retuns both sizes plus 1
}

//name: _getHeight
//use: to get height of binary tree
//parameters: const node pointer of type T
//returns: unsigned const which is height
template <typename T> unsigned BinaryTree<T>::_getHeight(Node<T> *node) const
{
	if(!node) //if statement for when the node is null
	{
		return 0;
	}

	unsigned int left_height = _getHeight(node->left); //find max depth of left subtrees
	unsigned int right_height = _getHeight(node->right); //finds max depth of right subtrees

	if (left_height > right_height) //if statement to determine which subtree has a greater height
	{
		return (left_height + 1);
	}
	else 
	{
		return (right_height + 1);
	}
}

//name: _Insert
//use: to insert a node into the binary tree
//parameters: a node or insert point and the value it holds (data)
//returns:none
template <typename T> void BinaryTree<T>::_Insert(Node<T> *&insert_point, const T&data)
{

	
	if (!insert_point) //if statement to for creating a new node 
	{
		insert_point = new Node<T>(data);
	}

	else //else statemnt for when a node is thier insert the data and which node is belongs to
	{
		if (rnd() == right_side)
		{
			_Insert(insert_point->right,data);
		}

		else
		{
			_Insert(insert_point->left,data);
		}

	}
}

//name:_Inorder
//use: to traverse the binary tree inorderly
//parameters: const node pointer of type T and function pointer that does the operation
//returns: none
template <typename T> void BinaryTree<T>::_Inorder(Node<T> *node, void (*node_operation)(const T&))
{
	if(!node) //if statement for when node is null
	{
		return;
	}	

	_Inorder(node->left,node_operation); // when node is not null traverse down left

	node_operation(node->data);
	
	_Inorder(node->right,node_operation); // when node is not null traverse down right

}






#endif // End of H_BINARYTREE
