#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm> //can use algorithm here ??
#include <iostream>

void parse_config(std::ifstream &config_file, std::string &index, 
	std::string &output){
	std::string full_line;
	std::string parameter;
	while(getline(config_file, full_line)){
		if(full_line[0] == '#'); //skip this line

		else{ 
			std::stringstream line(full_line);
			line >> parameter;
			char equals;
			if(parameter == "INDEX_FILE"){
				line >> equals;
				if(equals == '='){ //make sure 
					line >> index;
				}
			}
			else if(parameter == "OUTPUT_FILE"){
				line >> equals;
				if(equals == '='){
					line >> output;
				}
			}
		}
	}
}

std::vector<std::string> find_links(std::ifstream &file){
	char c;
	
	std::vector<std::string> links;
	while(file >> c){
		if(c == '('){
			file >> c;
			std::string link_name;
			while(c != ')'){
				std::string add(1, c);
				link_name += add;
				file >> c;
			}
			links.push_back(link_name);
		}
	}
	return links;
}

void DFS(std::string fname, std::vector<std::string> &filenames){
	std::vector<std::string> links;
	std::ifstream curr_file(fname);
	std::vector<std::string>::iterator found = 
		find(filenames.begin(), filenames.end(), fname);
	//check for valid filename 
	if(curr_file){
		if(found == filenames.end()) filenames.push_back(fname);
		links = find_links(curr_file);
	}

	for(std::vector<std::string>::iterator it = links.begin(); 
		it != links.end(); it++){
		std::vector<std::string>::iterator visited = 
			find(filenames.begin(), filenames.end(), *it);
		if(visited == filenames.end()){
			std::ifstream file_exists;
			file_exists.open(*it);
			if(file_exists){
				file_exists.close();
				filenames.push_back(*it);
				DFS(*it, filenames);
			}
		}
	}
}

std::vector<std::string> parse_files(std::string index){
	std::ifstream seed_file(index);
	std::string fname;
	std::vector<std::string> filenames;

	while(seed_file >> fname){
		DFS(fname, filenames);
	}
	return filenames;
}

int main(int argc, char* argv[]){
	std::string index_name; 
	std::string output_name;
	if(argc > 1){
		std::ifstream config(argv[1]);
		parse_config(config, index_name, output_name);
	}
	else{
		std::ifstream config("config.txt");
		parse_config(config, index_name, output_name);
	}

	std::vector<std::string> result = parse_files(index_name);
	std::ofstream ofile(output_name);

	for(std::vector<std::string>::iterator it = result.begin(); 
		it != result.end(); it++){
		ofile << *it << std::endl;
	}
}