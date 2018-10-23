#include "lliststr.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
	LListStr* game = new LListStr();

	ifstream input(argv[1]);

	string command, name;
	int pos;

	while(!input.eof()){

		input >> command >> pos;
		//cout << command;

		if(command == "ADD"){
			input >> name;

			game->insert(pos, name);
		}

		else if(command == "REPLACE"){
			input >> name;
			game->set(pos, name);
		}

		else if(command == "ACT" && game->size() > 1 && pos < game->size()-1){

			if(pos == game->size()-1) pos = -1;

			string assassinated = game->get(pos+1);
			//std::cout << assassinated << std::endl;
			//cout << 
			game->remove(pos+1);

			cout << "Assassinated: " << assassinated << endl;
		}
	}

	if(game->size() == 1){
		cout << "Winner: " << game->get(0) << endl;
	}
	else{
		cout << "Remaining Players: " << endl;
		
		int i = 0;
		while(i < game->size()){ //while loop parameter change
			cout << game->get(i) << endl;
			i++;
		}
	}
}