#include "lliststr.h"

  LListStr::LListStr(){
  	head_ = NULL;
  	tail_ = NULL;

  	size_ = 0;
  }

  LListStr::~LListStr(){

  }

  int LListStr::size() const { 
  	return size_; 
  }

  bool LListStr::empty() const { 
  	if(size_ == 0){
  		return true;
  	}
  	else return false;
  } 


  void LListStr::insert(int pos, const std::string &val){
  	if(pos > size_ || pos < 0) return;

  	Item* new_val = new Item(val, NULL, NULL);

  	if(pos == 0){ 
  		if(head_ == NULL){
  			head_ = new_val;
  			tail_ = head_;
  		}

  		else{
  			Item* temp = head_;
  			head_ = new_val;
  			head_->next = temp;
  			temp->prev = head_;
  			head_->prev = tail_;

  		}

   		size_++;
  		return;
  	}

  	if(pos == size_){
  		if(tail_ == NULL){
  			tail_ = new_val;
  			tail_->next = head_;
  		}
  		else{
  			Item* temp = tail_;
  			tail_ = new_val;
  			temp->next = tail_;
  			tail_->next = head_;
  			tail_->prev = temp;

  		}
  		size_++;
  		return;
  	}

  	else{
	  	Item* prev_val; 
	  	Item* following_val;

	  	following_val = head_;

	  	while(pos > 0){
	  		prev_val = following_val;
	  		following_val = following_val->next;
	  		pos--;
	  	}
	  	prev_val->next = new_val;
	  	new_val->next = following_val;
	  	new_val->prev = prev_val;
	  	following_val->prev = new_val;

	  	size_++;
	  }
  }


  void LListStr::remove(int pos){


  	if(pos >= size_ || pos < 0) return;

  	if(pos == 0){
  		//remove head index
  		head_->next->prev = tail_;
  		tail_->next = head_->next;
  		head_ = head_->next;

  		size_--;
  	}

  	else if(pos == size_-1){
  		//remove tail index
  		tail_->prev->next = head_;
  		head_->prev = tail_->prev;
  		tail_ = tail_->prev;

  		size_--;
  	}

  	else{
  		Item* target_val;
  		target_val = head_;

  		while(pos > 0){
	  		target_val = target_val->next;
	  		pos--;
  		}
  		target_val->prev->next = target_val->next;
  		target_val->next->prev = target_val->prev;
  		//delete target_val; ???? need to delete?

  		size_--;
  	}


  }

  void LListStr::set(int pos, const std::string &val){
  	if(pos >= size_ || pos < 0) return;

  	Item* target_val;
  	target_val = head_;

  	while(pos > 0){
  		target_val = target_val->next;
  		pos--;
  	}
  	target_val->val = val;
  }


  std::string LListStr::get(int pos) const {
  	if(pos >= size_ || pos < 0) return "";

  	Item* target_val = head_;

  	while(pos > 0){
  		target_val = target_val->next;
  		pos--;
  	}

  	return target_val->val;

  }
