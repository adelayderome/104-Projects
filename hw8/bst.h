#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the clear() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 
	//call clear function here... or do nothing??
	//check valgrind if you decide to do nothing to make sure all 
	//dynamically allocated memory is freed
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;
	private:
		//helper functions
		bool balanced_helper(Node<Key, Value>* node);
		void remove_helper(Node<Key, Value>*, bool curr_is_left);
		Node<Key, Value>* find_successor(Node<Key, Value>* root);
		void clear_helper(Node<Key, Value>* curr_node);
		iterator end_c() const;
		void update_heights(Node<Key, Value>* node);

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	mRoot = NULL;
	// mRoot.setRight(NULL);
	// mRoot.setLeft(NULL);
	// mRoot.setValue(NULL);
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>:: iterator BinarySearchTree<Key, Value>::end_c() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}
/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	if(mRoot == NULL) return 0;
	return mRoot->getHeight();
}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	//Node<Key, Value>* curr_node = mRoot;
	return balanced_helper(mRoot);

}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanced_helper(Node<Key, Value>* curr_node){

	if(curr_node == NULL) return true;

	Node<Key, Value>* left = curr_node->getLeft();
	Node<Key, Value>* right = curr_node->getRight();
	int lefth, righth;
	if(left == NULL) lefth = 0;
	else lefth = left->getHeight();
	if(right == NULL) righth = 0;
	else righth = right->getHeight();

	if(abs(lefth - righth) <= 1 && balanced_helper(left) && balanced_helper(right)){
		return true;
	}

	return false;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	//if already in tree, do nothing 

	Key key = keyValuePair.first;
	Node<Key, Value>* curr_node = mRoot;
	//std::cout << key << std::endl;
	if(mRoot == NULL){
		mRoot = new typename Node<Key, Value>::Node(key, keyValuePair.second, NULL);
		//curr_node = mRoot;
	}
	else{
		if(this->find(key) != this->end_c()) return;

		Node<Key, Value>* currp = NULL;

		while(curr_node != NULL){
			if(curr_node->getKey() < key){
				currp = curr_node;
				//int h = curr_node->getHeight() + 1;
				//curr_node->setHeight(h);
				curr_node = curr_node->getRight();
			}
			else if(curr_node->getKey() > key){
				currp = curr_node;
				//int h = curr_node->getHeight() + 1;
				//curr_node->setHeight(h);
				curr_node = curr_node->getLeft();
			}
		}
		if(curr_node == NULL){ //kinda redundant but necessary?
			//need to create new node??
			//std::cout << currp->getKey() << std::endl;
			curr_node = new typename Node<Key, Value>::Node(key, keyValuePair.second, currp);
			if(curr_node->getKey() > currp->getKey()) currp->setRight(curr_node);
			if(curr_node->getKey() < currp->getKey()) currp->setLeft(curr_node);

			//do you need to update previos nodes heights??--yessss
			//curr_node->setParent(currp);
		}
	}
	update_heights(curr_node);
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	//if key not in tree/tree is empty will not remove 
	if(this->find(key) != this->end_c()){
		//if(mRoot->getKey() == key) clear();

		bool leftnode = false; //if node is to left
		Node<Key, Value>* curr_node = mRoot;
		Node<Key, Value>* parent;

		while(curr_node != NULL){
			if(curr_node->getKey() == key){
				parent = curr_node->getParent();
				remove_helper(curr_node, leftnode);
				break;
			}
			else if(curr_node->getKey() > key){
				curr_node = curr_node->getLeft();
				leftnode = true;
			}
			else{
				curr_node = curr_node->getRight();
				leftnode = false;
			}
		}

		update_heights(parent);
	}
	
}
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove_helper(Node<Key, Value>* curr, bool curr_is_left)
{
	Node<Key, Value>* parent = curr->getParent();
	Node<Key, Value>* rchild = curr->getRight(); 
	Node<Key, Value>* lchild = curr->getLeft(); 
	
	//leaf node to be removed
	if((lchild == NULL) && (rchild == NULL)){
		//root node and only root node
		if(parent == NULL){
			delete curr;
			mRoot = NULL;
		}
		else{
			if(curr_is_left) parent->setLeft(NULL);
			else parent->setRight(NULL);
			delete curr;
		}
	}
	//node to be removed has one child 
	//only child left
	else if(curr->getRight() == NULL){
		//root node 
		if(parent == NULL){
			mRoot = curr->getLeft();
			mRoot->setParent(NULL);
			delete curr;
		}
		else{
			if(curr_is_left){
				parent->setLeft(curr->getLeft());
				curr->getLeft()->setParent(parent);
			}
			else{
				parent->setRight(curr->getLeft());
				curr->getLeft()->setParent(parent);
			}
			update_heights(curr->getLeft());
			delete curr;
		}
	}
	//only child right
	else if(curr->getLeft() == NULL){
		if(parent == NULL){
			mRoot = curr->getRight();
			mRoot->setParent(NULL);
			delete curr;
		}
		else{
			if(curr_is_left){
				parent->setLeft(curr->getRight());
				curr->getRight()->setParent(parent);
			}
			else{
				parent->setRight(curr->getRight());
				curr->getRight()->setParent(parent);
			}
			update_heights(curr->getRight());
			delete curr;
		}
	}
	//node to be removed has two children
	else{
		Node<Key, Value>* pred_node = curr->getLeft();

		while(pred_node->getRight() != NULL){
			pred_node = pred_node->getRight();
		}
 		Node<Key, Value>* pred_par = pred_node->getParent();

		if(curr->getParent() == NULL){
			bool isadjacent = false, update = false;
			if(pred_node == curr->getLeft()){
				pred_node->setRight(curr->getRight());
				curr->getRight()->setParent(pred_node);
				isadjacent = true;
			}
			else{
				if(pred_node->getLeft() != NULL){
					pred_node->getLeft()->setParent(pred_node->getParent());	
				}
				pred_node->getParent()->setRight(pred_node->getLeft());
				pred_node->setRight(curr->getRight());
				curr->getRight()->setParent(pred_node);
				pred_node->setLeft(curr->getLeft());
				curr->getLeft()->setParent(pred_node);
				update = true;
				//update_heights(pred_node->getLeft());
			}
			pred_node->setParent(NULL);
			mRoot = pred_node;
			delete curr;

			if(isadjacent) update_heights(pred_node);
			if(update) update_heights(pred_par);
		}

		else if(pred_node == curr->getLeft()){
			pred_node->setRight(curr->getRight());
			curr->getRight()->setParent(pred_node);
			if(curr_is_left) parent->setLeft(pred_node);
			else parent->setRight(pred_node);
			pred_node->setParent(parent);
			delete curr;
			update_heights(pred_node);
		}

		else{
			if(pred_node->getLeft() != NULL){
				pred_node->getLeft()->setParent(pred_node->getParent());
			}
			pred_node->getParent()->setRight(pred_node->getLeft());
			pred_node->setParent(parent);
			if(curr_is_left) parent->setLeft(pred_node);
			else parent->setRight(pred_node);
			pred_node->setLeft(lchild);
			lchild->setParent(pred_node);
			pred_node->setRight(rchild);
			rchild->setParent(pred_node);
			delete curr;
			update_heights(pred_node->getLeft());
		}
		//delete temp_pred;
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::update_heights(Node<Key, Value>* node){
	if(node == NULL) return;
	else if((node->getLeft() == NULL) && (node->getRight() == NULL)){
		node->setHeight(1);
	}
	int lh =0, rh = 0;
	if(node->getLeft() != NULL) lh = node->getLeft()->getHeight();
	if(node->getRight() != NULL) rh = node->getRight()->getHeight();
	node->setHeight(std::max(lh, rh) + 1);
	update_heights(node->getParent());
}



template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::find_successor(Node<Key, Value>* node)
{
	while(node->getRight() != NULL){
		node = node->getRight();
	}
	return node;
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	clear_helper(mRoot);
	mRoot = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_helper(Node<Key, Value>* curr_node)
{
	if(curr_node == NULL) return; //do nothing??
	if(curr_node != NULL){
		clear_helper(curr_node->getRight());
		clear_helper(curr_node->getLeft());
		delete curr_node;

	}
}
/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	//just find leftmost node
	Node<Key, Value>* curr = mRoot;

	if(mRoot == NULL) return NULL;

	while(curr->getLeft() != NULL){
		curr = curr->getLeft();
	}
	return curr;
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	//if the key does not exist
	if(mRoot == NULL){
		return NULL;
	}

	Node<Key, Value>* curr_node = mRoot;
	while(curr_node != NULL){
		if(curr_node->getKey() == key) return curr_node;
		else if(curr_node->getKey() > key) curr_node = curr_node->getLeft();
		else if(curr_node->getKey() < key) curr_node = curr_node->getRight();
	}
	//should return NULL if curr node not found??
	return curr_node;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	// std::cout << "Here" << std::endl;
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}

		// std::cout << "HERE IN RIGHT"<<std::endl;
}

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
