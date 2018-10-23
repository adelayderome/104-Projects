#include "functor.h"
#include <ctype.h>
#include <stdio.h>
#include <string>

using namespace std;

int NumStrComp::sum(const string& str){
	int len = 0;
	for(size_t i = 0; i < str.length(); i++){
		if(isdigit(str[i])) len += ((int)str[i] - 48);
		if(isalpha(str[i])){
			len += ((int)(toupper(str[i])) - 55);
		}
	}
	return len;
}

bool NumStrComp::operator()(const string& s1, const string& s2){
	int len1 = sum(s1);
	int len2 = sum(s2);
	if(len1 == len2){
		return s1 < s2;
	}
	else{
		return len1 < len2;
	}
}

