#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int &reserves, ofstream &output){
    //returns true if the invaders breach the walls.

    if(skirmish_row >= columns || skirmish_row < 0){
        return false; 
    }

    //invader in row i (col 0) duels protector in col i (row 0)
    for(int i = 0; i < rows; i++){  

        if(invaders[skirmish_row][i]->power == -1){
            output << "No assault" << '\n';
        }
        else if(protectors[i][skirmish_row]->power == -1){
            //walls are breached
            return true;
        }

        if(invaders[skirmish_row][i]->weapon == "axe" 
            && protectors[i][skirmish_row]->weapon == "sword"){
            //invader wins
            bool openSpot = false;
            int open_r;
            int open_c;

            for(int a = 0; a < columns; a++){
                for(int n = 0; n < rows; n++){
                    if(invaders[a][n]->power == -1){
                        openSpot = true;
                        open_r = a;
                        open_c = n;
                    }
                }
            }

            if(openSpot){
                int p = protectors[i][skirmish_row]->power;
                invaders[open_r][open_c]->power = p;
                invaders[open_r][open_c]->weapon = 
                    protectors[i][skirmish_row]->weapon;
                protectors[i][skirmish_row]->power = -1;

                output << "Protector defected" << '\n';

                break; //exit for loop if protector defected
            }

            else if(reserves > 0){
                output << "Protector killed" << '\n';

                //reserve warrior moves to position
                protectors[i][skirmish_row]->power = 100;
                protectors[i][skirmish_row]->weapon = "axe";
                reserves--;
            }
            else{
                output << "Protector killed" << '\n';
                protectors[i][skirmish_row]->power = -1;
            }
        }

        else if(invaders[skirmish_row][i]->weapon == "sword" 
            && protectors[i][skirmish_row]->weapon == "axe"){
            //protector wins
            output << "Invader killed" << '\n';
            
            invaders[skirmish_row][i]->power = -1; //position empty
        }

        else if(invaders[skirmish_row][i]->power 
            > protectors[i][skirmish_row]->power){
            //invader wins
            bool openSpot = false;
            int open_r;
            int open_c;

            for(int a = 0; a < columns; a++){
                for(int n = 0; n < rows; n++){
                    if(invaders[a][n]->power == -1){
                        openSpot = true;
                        open_r = a;
                        open_c = n;
                    }
                }
            }

            if(openSpot){
                int p = protectors[i][skirmish_row]->power;
                invaders[open_r][open_c]->power = p;
                invaders[open_r][open_c]->weapon = 
                    protectors[i][skirmish_row]->weapon;
                protectors[i][skirmish_row]->power = -1;

                output << "Protector defected" << '\n';

                break; 
            }
            else if(reserves > 0){
                output << "Protector killed" << '\n';

                //reserve warrior moves to position
                protectors[i][skirmish_row]->power = 100;
                protectors[i][skirmish_row]->weapon = "axe";
                reserves--;
            }
            else{
                output << "Protector killed" << '\n';
                protectors[i][skirmish_row]->power = -1;
            }
        }

        else if(invaders[skirmish_row][i]->power 
            < protectors[i][skirmish_row]->power){
            //protector wins
            output << "Invader killed" << '\n';
            invaders[skirmish_row][i]->power = -1; 
        }

        else if(invaders[skirmish_row][i]->power 
            == protectors[i][skirmish_row]->power){
            //draw
            output << "Duel ends in draw" << '\n';
        }

    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.
    input >> rows >> cols >> reserve >> skirmishes;

    Warrior ***protectors;
    Warrior ***invaders;

    //initialize the protectors and invaders here.
    protectors = new Warrior**[rows];
    for(int i = 0; i < rows; i++){
        protectors[i] = new Warrior*[cols];

        for(int j = 0; j < cols; j++){
            protectors[i][j] = new Warrior; 

            protectors[i][j]->power = i*10+(j+1)*10; 
            
            if(i % 2 == 0){
                protectors[i][j]->weapon = "axe";
            }
            else protectors[i][j]->weapon = "sword";
        }
    }


    invaders = new Warrior**[cols];
    for(int i = 0; i < cols; i++){
        invaders[i] = new Warrior*[rows];

        for(int j = 0; j < rows; j++){
            invaders[i][j] = new Warrior;

            invaders[i][j]->power = i*10+(j+1)*10;

            if(i % 2 == 1) invaders[i][j]->weapon = "axe";
            else invaders[i][j]->weapon = "sword";
        }
    }
    bool p_win = true;

    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
        
        //read the input file to find the value for skirmish row
        input >> skirmish_row;
        
        //In general, it is bad style to throw everything into your main function
        bool end = skirmish(protectors, invaders, skirmish_row, 
            rows, cols, reserve, output);

        if(end == true){
            output << "Winner: invaders";
            p_win = false;
            break;
        }
    }

    //output the winner and deallocate your memory.
    if(p_win == true) output << "Winner: protectors";

    //deallocate memory 
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            delete protectors[i][j];
        }
        delete[] protectors[i];
    } 
    delete[] protectors;

    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            delete invaders[i][j];
        }
        delete[] invaders[i];
    } 
    delete[] invaders;
    
    return 0;
}
 