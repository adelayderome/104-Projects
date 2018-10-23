#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

void checkValue(LListStr *list, int pos, const string &str) {
	string val = list->get(pos);
	bool correct = false;
	if(str == val) correct = true;

	if(correct){
		cout << "SUCCESS: string at index " << pos << " is: " << str << endl;
	}
}

void checkRemove(LListStr *list, int exp_size){
	int size = list->size();
	if(size == exp_size){
		cout << "SUCCESS: item removed. List has size: " << size << endl;
	}
	else{
		cout << "FAIL: item not correctly removed. List has size " << size;
		cout << " but expected size " << exp_size << endl;
	}
}

int main() {
	LListStr* list = new LListStr();

	//insert multiple values
	list->insert(0, "abc");
	list->insert(1, "bcd");
	list->insert(1, "cde");

	checkValue(list, 0, "abc");
	checkValue(list, 2, "bcd");
	checkValue(list, 1, "cde");
	checkSize(list, 3);

	//check get function 
	checkGet(list, 1, "bcd");

	//check remove function
	list->remove(0);
	checkRemove(list, 2);
	list->remove(1);
	checkRemove(list, 1);

	// Verify the list is not empty
	checkEmpty(list, false);
	checkSize(list, 1);

	// Clean up memory.
	delete list;
}
