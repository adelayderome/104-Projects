#include "splayTree.h"
#include <stdexcept>

//templated cache class that stores key/value pairs in splay tree
template <typename Key, typename Value>
class cacheLRU : public SplayTree<Key, Value>
{
public:
	cacheLRU(int capacity);
	~cacheLRU();
	void put(const std::pair<const Key, Value>& keyValuePair);
	std::pair<const Key, Value> get(const Key& key);
	int misses;
private:
	void getSize(Node<Key, Value>* node);
	int cap;
	int size;
	
};

template <typename Key, typename Value>
cacheLRU<Key, Value>::cacheLRU(int capacity){
	cap = capacity;
	size = 0;
	misses = 0;
}

template <typename Key, typename Value>
cacheLRU<Key, Value>::~cacheLRU(){

}

template <typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair){
	typename cacheLRU<Key, Value>::iterator it = SplayTree<Key, Value>::find(keyValuePair.first);
	//if key not already in tree
	if(it == NULL){
		//key not in tree and not yet at capacity
		if(size < cap){
			SplayTree<Key, Value>::insert(keyValuePair);
			size++;
		}
		//key not in tree and at capacity
		else{
			misses++;
			this->deleteMinLeaf(); //delete leaf, size decrements
			//insert new node, size incrementss
			SplayTree<Key, Value>::insert(keyValuePair); 
		}
	}
}

//find node with key, return keyvalpair
//if key not found, throw exception
template <typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key){
	typename cacheLRU<Key, Value>::iterator it = SplayTree<Key, Value>::find(key);

	if(it == NULL) throw std::logic_error("key not in cacheLRU");
	
	Node<Key, Value>* node = this->internalFind(key);
	Value value = node->getValue();
	std::pair<const Key, Value> kvpair = std::make_pair(key, value);
	return kvpair;
}
