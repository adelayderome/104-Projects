struct Node {
    int value;
    Node *next;
};


Node* iterate(Node* curr){ //edit if statemnt parameters ??
	if(curr->next == nullptr) return nullptr;
//need to account for vals at end 

	else if(curr->value < curr->next->value //iterate(curr->next);
		&& curr->next->value < curr->next->next->value) iterate(curr->next);
	
	//if smallest value out of place
	else if(curr->next->value > curr->next->next->value 
		&& curr->next->value < curr->next->next->next->value){
		return curr->next;
	}

	//if largest value out of place
	else if((curr->next->value > curr->next->next->value) && 
		((curr->next->value > curr->next->next->value) || (curr->next == nullptr))){
		return curr;
	}

	return nullptr;
}

Node* fullsort (Node* in){

	Node* before = iterate(in);

	if(before == nullptr) return in;

	Node* move = before->next;
	
	//std::cout << move->value << " " << before->value << std::endl;

	//smallest value out of place
	if(move->value < before->value){
		Node* temp = move->next;
		move->next = in;
		before->next = temp;
		in->next = before;
		in = move;
		
		return in;
	}

	//largest value out of place
	if(before->value < move->value){
		Node* temp = move;
		before->next = move->next;
		temp->next = move->next->next;
		move->next->next = temp;
		iterate(in);

		temp->next = nullptr;
		return in;
	}

	return in; //maybe take out
}

