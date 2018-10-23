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
	int leftr_count = 0;
	int rightr_count = 0;
};

//perform a left rotation at the parameter node (constant runtime)
//if r has no right chils, this does nothing
template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){
	leftr_count++;
	if(r->getRight() != NULL){
		
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* rightc = r->getRight();
		Node<Key, Value>* rc_lc = NULL;
		if(rightc != NULL) rc_lc = rightc->getLeft();
		
		bool is_left = false;
		if(parent != NULL){
			if(parent->getLeft() == r) is_left = true;
		} 
		if(rightc != NULL) rightc->setParent(parent); //will set to null if root node
		if(is_left && parent != NULL) parent->setLeft(rightc); 
		else if(parent != NULL) parent->setRight(rightc); //maybs
		
		r->setParent(rightc);
		if(rightc != NULL) rightc->setLeft(r);

		if(rc_lc != NULL){
			r->setRight(rc_lc);
			rc_lc->setParent(r);
		}
		else r->setRight(NULL);
		if(parent == NULL) this->mRoot = rightc; //check this
	}
	//if(r->getParent() == NULL) this->mRoot = r;
}

//perform a right rotation at the parameter node (constant runtime)
//if r has no left child, this does nothing
template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
	rightr_count++;
	if(r->getLeft() != NULL){
		
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* leftc = r->getLeft();
		Node<Key, Value>* lc_rc = NULL;
		if(leftc != NULL) lc_rc = leftc->getRight();

		bool is_left = false;
		if(parent != NULL){
			if(parent->getLeft() == r) is_left = true;
		} 
		//will set to null if root node
		if(leftc != NULL) leftc->setParent(parent); 

		//parent->setRight(r->getRight());
		if(is_left && parent != NULL) parent->setLeft(leftc); 
		else if(parent != NULL) parent->setRight(leftc);
		r->setParent(leftc);

		if(leftc != NULL) leftc->setRight(r);
		if(lc_rc != NULL){
			r->setLeft(lc_rc);
			lc_rc->setParent(r);
		}
		else r->setLeft(NULL);
		if(parent == NULL) this->mRoot = leftc;
	}
	//if(r->getParent() == NULL) this->mRoot = r;
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