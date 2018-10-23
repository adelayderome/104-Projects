#include <stack>
#include <stdio.h> 
#include <ctype.h>
#include <algorithm> 
#include <string>
#include <sstream>
#include <fstream>
//#include "stackstr.h"
//#include "lliststr.h"

using namespace std;

string remove_first(string s){
	if(s.size() > 1){
		s.erase(s.begin());
	}
	return s;
}
string remove_last(string s){
	if(s.size() > 1){
		s.erase(s.end()-1);
	}
	return s;
}

string evaluate(stringstream& expression){
	stack<string> s;
	//StackStr* s = new StackStr();
	string str, str1, str2;

	char c;
	size_t ss_size = expression.str().size();
	int ss_size1 = (int)ss_size;

	while(expression >> c){
		ss_size1--;
		if(!isalpha(c) && c != ')'){
			string a(1, c);
			s.push(a);
		}

		else if(isalpha(c)){
			while(isalpha(c) && ss_size1 > -1){
				string add(1, c);
				str += add;
				expression >> c;
				ss_size1--;

			}
			s.push(str);

			str = "";

			if(c == ')'){
				goto closeParen;
			}
			if(!isalpha(c)){
				string b(1, c);
				s.push(b);
			}
		} 

		closeParen:;
		if(c == ')'){
			string op;

			while(op != "("){
				if(isalpha(s.top()[0])){
					str1 = s.top();
					s.pop();
				}

				op = s.top();
				s.pop(); 

				if(op == "(") return "Malformed";

				if(op == ">"){
					str1 = remove_first(str1);
					op = s.top();

					if(op == "("){
						s.pop();
						s.push(str1);
					}
					if(isalpha(op[0])) return "Malformed";
				}

				else if(op == "<"){
					str1 = remove_last(str1);
					op = s.top();
					if(op == "("){
						s.pop();
						s.push(str1);
					}
					if(isalpha(op[0])) return "Malformed";
				} 

				else if(op == "+"){
					str2 = s.top();
					s.pop();

					if(!isalpha(str2[0])){
						return "Malformed";
					}

					op = s.top();

					if(op == ">" || op == "<"){
						while(op == ">" || op == "<"){

							if(op == ">") str2 = remove_first(str2);
							else if(op == "<") str2 = remove_last(str2);
							s.pop();
							op = s.top();
						}
						if(isalpha(op[0])) return "Malformed";
					}
					if(op == "+" || op == "("){ //else if??
						str2 += str1;
						if(op == "(") s.pop();
						s.push(str2);

						str1 = str2;
					}
					else if (op == "-"){
						return "Malformed";
					}
				}

				//write function to eliminate repeated code for -/+
				else if(op == "-"){
					str2 = s.top();
					s.pop();

					if(!isalpha(str2[0])){
						return "Malformed";
					}

					op = s.top();

					if(op == ">" || op == "<"){
						while(op == ">" || op == "<"){

							if(op == ">") str2 = remove_first(str2);
							else if(op == "<") str2 = remove_last(str2);
							s.pop();
							op = s.top();
						}
						if(isalpha(op[0])) return "Malformed";
					}
					if(op == "("){
						if(str2 == str1) return "Malformed";

						size_t pos = str2.find(str1);
						int pos1 = (int)pos;
						if(pos1 > -1){
							size_t length1 = str1.size();
							int length = (int)length1;
							
							str2.erase(pos, length);
							if(op == "(") s.pop();
							s.push(str2);
						}
						else{
							if(op == "(") s.pop();
							s.push(str2);
						} 
					}
					//cannot be multiple of these operations in one parentheses
					else if (op == "-" || op == "+"){
						return "Malformed";
					}
				}
			}
		}
	}
	if(s.size() > 1){
		str1 = s.top();
		s.pop();

		if(!isalpha(str1[0])){
			return "Malformed";
		}

		string op = s.top();
		if(op == ">" || op == "<"){
			while(op == ">" || op == "<"){

				if(op == ">") str1 = remove_first(str1);
				else if(op == "<") str1 = remove_last(str1);
				s.pop();
				if(s.size() > 0){
					op = s.top();
				}

				if(s.size() == 0) break;
			}
			s.push(str1);
			if(isalpha(op[0])) return "Malformed";
		}
	}
	//cerr << "s.top here is " << s.top() << endl;
	if(s.top() == "("){
		return "Malformed";
	}
	return s.top();
}


int main(int argc, char* argv[]){

	ifstream ifile(argv[1]);
	ofstream output(argv[2]);

	string expression;
	//ifile.open(argv[1]);
	bool skip_eval = false;

	while(getline(ifile, expression)){

		size_t len = expression.size();

		if(len == 0){
			output << "Malformed" << endl;
			skip_eval = true;
		}
		bool has_paren = false; 
		int open_paren = 0;
		int close_paren = 0;

		for(size_t i = 0; i < len; i++){
			char check = expression[i];
			if(isalpha(check) && !islower(check) && !skip_eval){
				output << "Malformed" << endl;
				skip_eval = true;
			}
			if(!isalpha(check) && check != '<' && check != '>' && check != '('
				&& check != ')' && check != '+' && check != '-' &&
				check != ' ' && !skip_eval){
				output << "Malformed " << endl;
				skip_eval = true;
			}
			if(check == '('){
				has_paren = true;
				open_paren++;
			} 
			else if(check == ')') close_paren++;

			if(!has_paren && (check == '+' || check == '-') && !skip_eval){
				output << "Malformed" << endl;
				skip_eval = true;
			}
		}
		if(!isalpha(expression[0]) && expression[0] != '(' 
			&& expression[0] != '<' && expression[0] != '>' && !skip_eval){
			output << "Malformed" << endl;
			skip_eval = true;
		}

		if((open_paren != close_paren) && !skip_eval){
			output << "Malformed" << endl;
			skip_eval = true;
		}

		for(size_t i = 0; i < len; i++){
			if(expression[i] == ' '){
				expression.erase(i, 1);
			}
		}
		stringstream eval(expression);

		string final;

		if(!skip_eval){
			final = evaluate(eval);
			output << final << endl;
		}
		skip_eval = false;
	}
}

