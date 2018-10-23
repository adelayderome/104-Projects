#include <iostream>
#include <fstream> 
#include <string> 
#include <sstream> 


using namespace std;

void output(ifstream &words, int count){
	string word;

	if(count == 0){

		words >> word;
		cout << word << " ";
		return;
	} 

	else{

		words >> word;
		output(words, count-1);
		cout << word << " ";
	}
}

int main (int argc, char* argv[]){
	ifstream txt_file;
	txt_file.open(argv[1]);


	int word_count;
	string line;
	getline(txt_file, line);
	word_count = stoi(line);

	stringstream all_words;

	output(txt_file, word_count-1);

	txt_file.close();

}

