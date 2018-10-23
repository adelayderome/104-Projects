#include "bst.h"
#include "rotateBST.h"

template <typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();
protected:
	void splay(Node<Key, Value> *r);
private:
	Node<Key, Value>* find_helper(const Key& key) const; 
};

//constructor...
template <typename Key, typename Value>
SplayTree<Key, Value>::SplayTree(){

}

template <typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair){
	//insert to tree, does nothing if already in tree
	BinarySearchTree<Key, Value>::insert(keyValuePair);
	//splay inserted node to top
	Node<Key, Value>* inserted_node = this->internalFind(keyValuePair.first);
	
	splay(inserted_node);
}

//if key not in tree, dont remove, but splay last visited to root
template <typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key){
	Node<Key, Value>* remove_node = this->internalFind(key);

	if(remove_node == NULL){
		//find the last visited node is remove node not found and splay it
		Node<Key, Value>* remove = find_helper(key);
		splay(remove);
		return;
	}
	//depending on child situation, will splay different nodes 
	if((remove_node->getLeft() == NULL) && (remove_node->getRight() == NULL)){
		Node<Key, Value>* parent = remove_node->getParent();
		BinarySearchTree<Key, Value>::remove(key);
		splay(parent);
		return;
	}
	else if((remove_node->getLeft() != NULL)&& (remove_node->getRight() == NULL)){
		Node<Key, Value>* left = remove_node->getLeft();
		BinarySearchTree<Key, Value>::remove(key);
		splay(left);
		return;
	}
	else if((remove_node->getLeft() == NULL)&& (remove_node->getRight() != NULL)){
		Node<Key, Value>* right = remove_node->getRight();
		BinarySearchTree<Key, Value>::remove(key);
		splay(right);
		return;
	}
	//will splay the parent of the predecessor
	//unless predecessor is the direct left child, then splay pred
	else if((remove_node->getLeft() != NULL) && (remove_node->getRight() != NULL)){
		Node<Key, Value>* pred_node = remove_node->getLeft();
		bool left = true; //splay node is direct left node of removed node
		if(pred_node != NULL){
			while(pred_node->getRight() != NULL){
				pred_node = pred_node->getRight();
				left = false; //not direct left node
			}
			Node<Key, Value>* pred_parent = pred_node->getParent();

			BinarySearchTree<Key, Value>::remove(key);
			if(left) splay(pred_node);
			else splay(pred_parent); 	
		}
	}
}


template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key){
	Node<Key, Value>* node = find_helper(key);
	splay(node);

	typename SplayTree<Key, Value>::iterator it = BinarySearchTree<Key, Value>::find(key);
	return it;
}

//find helper function
//finds the node with the key and returns
//if doesnt find the key, returns the last visitied node 
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::find_helper(const Key& key) const 
{
	//if empty?
	if(this->mRoot == NULL){
		return NULL;
	}

	Node<Key, Value>* curr_node = this->mRoot;
	Node<Key, Value>* prev_node = NULL;
	while(curr_node != NULL){
		if(curr_node->getKey() == key) return curr_node;
		else if(curr_node->getKey() > key){
			prev_node = curr_node;
			curr_node = curr_node->getLeft();
		}
		else if(curr_node->getKey() < key){
			prev_node = curr_node;
			curr_node = curr_node->getRight();
		}
	}
	
	return prev_node;
}


template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin(){
	Node<Key, Value>* min_node = this->getSmallestNode();
	if(min_node == NULL) return NULL;
	splay(min_node);
	//begin returns iterator to the smallest node 
	typename SplayTree<Key, Value>::iterator it = this->begin();
	return it;
}

template <typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax(){
	//find max node
	Node<Key, Value>* max_node = this->mRoot;
	//if called on empty tree
	if(max_node == NULL) return NULL;
	while(max_node->getRight() != NULL){
		max_node = max_node->getRight();
	}
	splay(max_node);
	typename SplayTree<Key, Value>::iterator it = this->find(max_node->getKey());
	return it;
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf(){
	Node<Key, Value>* minleaf = this->getSmallestNode();
	while(minleaf->getRight() != NULL){
		minleaf = minleaf->getRight();
		while(minleaf->getLeft() != NULL){
			minleaf = minleaf->getLeft();
		}
	}
	this->remove(minleaf->getKey());
}

template <typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf(){
	Node<Key, Value>* maxleaf = this->mRoot;
	while(maxleaf->getRight() != NULL){
		maxleaf = maxleaf->getRight();
	}
	while(maxleaf->getLeft() != NULL){
		maxleaf = maxleaf->getLeft();
		while(maxleaf->getRight() != NULL){
			maxleaf = maxleaf->getRight();
		}
	}
	this->remove(maxleaf->getKey());
}
//splays node to root 
template <typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r){

	while(r != this->mRoot){
		Node<Key, Value>* parent = r->getParent();

		bool isleft = false, pisleft = false;
		if(parent->getLeft() == r) isleft = true;

		//single rotation, one from root
		if(parent->getParent() == NULL){
			if(isleft) this->rightRotate(parent);
			else this->leftRotate(parent);
			return; //now should be at root, dont need to continue
		}

		Node<Key, Value>* gparent = parent->getParent();
		if(gparent->getLeft() == parent) pisleft = true;
		//zig-zig situation (left child of left child)
		if(isleft && pisleft){
			this->rightRotate(gparent);
			this->rightRotate(parent);
		}
		//zig-zig all right
		else if(!isleft && !pisleft){
			this->leftRotate(gparent);
			this->leftRotate(parent);
		}
		//zig-zag, node left but parent right
		else if(isleft && !pisleft){
			this->rightRotate(parent);
			this->leftRotate(gparent);

		}
		//zig-zag, node right but parent left
		else if(!isleft && pisleft){
			this->leftRotate(parent);
			this->rightRotate(gparent);
		}



	} 

}