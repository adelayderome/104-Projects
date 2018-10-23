#include "stackstr.h"

//constructor and destructor????
StackStr::StackStr(){}

StackStr::~StackStr(){}

  /**
   * Returns true if the stack is empty, false otherwise
   */
bool StackStr::empty() const{

	bool emp = list_.empty();
	return emp;
}

	/**
   * Returns the number of elements in the stack.
   */
int StackStr::size() const{
	int size_ = list_.size();
	return size_;
}

  /**
   * Pushes a new value, str, onto the top of the stack
   */
void StackStr::push(const std::string &str){
	int pos = list_.size();
	list_.insert(pos, str);
}

  /**
   * Returns the top value on the stack.
   * If the stack is empty, return the empty string.
   */
std::string StackStr::top() const{
	if(list_.empty()) return "";
	
	int pos = list_.size() - 1;
	return list_.get(pos);
}

  /**
   * Removes the top element on the stack.
   * Should do nothing if the stack is empty.
   */
void StackStr::pop(){
	int pos = list_.size() - 1;
	list_.remove(pos);
}