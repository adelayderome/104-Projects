#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);
public:
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;
};
//write these first three functions earlier in the day

//perform a left rotation at the parameter node (constant runtime)
//if r has no right chils, this does nothing
template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){
	Node<Key, Value>* parent = r->getParent();
	Node<Key, Value>* rightc = r->getRight();
	bool is_left = false;
	if(parent != NULL){
		if(parent->getLeft() == r) is_left = true;
	} 
	rightc->setParent(parent); //will set to null if root node
	//parent->setRight(r->getRight());
	if(is_left && parent != NULL) parent->setLeft(r); 
	else if(parent != NULL) parent->setRight(r);
	r->setParent(rightc);
	rightc->setLeft(r);
	r->setRight(NULL);
	if(parent == NULL) this->mRoot = rightc;
}

//perform a right rotation at the parameter node (constant runtime)
//if r has no left child, this does nothing
template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
	//no rotate if root??
	Node<Key, Value>* parent = r->getParent();
	Node<Key, Value>* leftc = r->getLeft();
	bool is_left = false;
	if(parent != NULL){
		if(parent->getLeft() == r) is_left = true;
	} 
	leftc->setParent(parent); //will set to null if root node
	//parent->setRight(r->getRight());
	if(is_left && parent != NULL) parent->setLeft(r); 
	else if(parent != NULL) parent->setRight(r);
	r->setParent(leftc);
	leftc->setRight(r);
	r->setLeft(NULL);
	if(parent == NULL) this->mRoot = leftc;

}

//provides another BST, checks that the sets of keys in both trees are same
//runtime: O(n), with n being number of nodes
template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const{
	return false;
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{

}