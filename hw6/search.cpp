#include "search.h"
#include "pagerank.h"
#include "setutility.h"
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void print(ifstream &webpage, ofstream &out){
	
	while(!webpage.eof()){
		char c;
		webpage >> noskipws >> c;
		if(c != '(' && !webpage.eof()){
			out << c;
		}
		else if(c == '('){
			while(c != ')'){
				webpage >> c;
			}
		}
	}
}
//add all words to map (make lowercase), with webpage as value
//add outgoing link names to outgoing set
//add current page name to all outgoing links incoming set 
void parsing(ifstream &webpage, string file_name, 
	map<string, set<string> > &words_map, 
	map<string, WebPage*> &full_page_map){
	char c;

	while(webpage >> noskipws >> c){
		string word;
		if(isalpha(c) || isdigit(c)){
			while((isalpha(c) || isdigit(c)) && !webpage.eof()){

				string add(1, tolower(c));
				word += add;
				webpage >> noskipws >> c;
				//if c equal to bracket, should then enter next loop
			}

			bool exists = (words_map.count(word) > 0);
			if(!exists){
				set<string> file1;
				file1.insert(file_name);
				words_map.insert(pair<string, set<string> >(word, file1));
			}
			else{
				//insert current file name to set of fnames for word in map
				words_map.at(word).insert(file_name);
			}
			word = "";
		}

		if(c == '['){
			while(c != ']'){
				webpage >> noskipws >> c;
				if(isalpha(c) || isdigit(c)){
					while(isalpha(c) || isdigit(c)){
						string add(1, tolower(c));
						word += add;
						webpage >> noskipws >> c;
					}
					bool exists = (words_map.count(word) > 0);

					if(!exists){
						set<string> f1;
						f1.insert(file_name);
						words_map.insert(pair<string, set<string> >(word, f1));
					}
					else{
						words_map.at(word).insert(file_name);
					}
					word = "";
				}
			}
			//one breaks out, assume next char is (
			webpage >> c;
			string link;
			webpage >> noskipws >> c;
			while(c != ')'){
				string add(1, c);
				link += add;
				webpage >> noskipws >> c;
			}
			full_page_map.at(file_name)->outgoing.insert(link);

			if(full_page_map.count(link) > 0){
				full_page_map.at(link)->incoming.insert(file_name);
			}
		}
	}
}

int main(int argc, char* argv[]){
	map<string, WebPage*> page_map;
	//map with individual words as keys and sets of webpages that contain 
	//the word (key) as values
	map<string, set<string> > contains_map;
	ifstream config(argv[1]);
	string query_file, index_file, output_file;
	double e;
	int t;
	//get all info from config file
	parse_config(index_file, config, query_file, output_file, e, t);
	ifstream index(index_file);
	ifstream query(query_file);
	//take in all file names from index, create webpage classes
	string page_name;
	set<string> page_name_set;

	while(!index.eof()){
		getline(index, page_name);

		page_map.insert(pair<string, WebPage*>(page_name, 
			new WebPage(page_name)));

		page_name_set.insert(page_name);
	}
	//iterate through set of names, parse through each file
	for(set<string>::iterator it = page_name_set.begin(); 
		it != page_name_set.end(); it++){

		string fname = *it;
		ifstream in_page(*it);
		parsing(in_page, fname, contains_map, page_map); 
	}

	ofstream output(output_file);
	//go through each query in file, print to output
	//make separate function for this 
	string command;
	while(!query.eof()){
		query >> command;
		string fname;
		Search search;

		if(command == "AND"){
			set<string> and_words;
			set<string> result;
			string words;
			getline(query, words);
			bool is_word = false;
			if(words.size() > 0){
				for(size_t i = 0; i < words.size()-1; i++){
					if(words[i] != ' ') is_word = true;
				}
			}

			if(!is_word && contains_map.count("and") > 0){
				result = contains_map.at("and");
			}
			else if(is_word){
				stringstream ss(words);
				string single_word;
				while(ss >> single_word){
					for(size_t i = 0; i < single_word.size(); i++){ 
						single_word[i] = tolower(single_word[i]);
					}
					and_words.insert(single_word);
				}
				result = search.intersectString(and_words, contains_map);
			}
			//new code for pagerank
			set<string> candidate_set = find_cs(result, page_map);
			map<string, double> rank = pagerank(candidate_set, page_map, t, e);
			map<double, string> sorted_rank = sort_map(rank);

			output << sorted_rank.size() << endl;
			for(map<double, string>::reverse_iterator rit = sorted_rank.rbegin();
				rit != sorted_rank.rend(); rit++){
				output << rit->second << endl;
			}
		}
		else if(command == "OR"){
			set<string> or_words;
			set<string> result; 
			string words;
			getline(query, words);
			bool is_word = false;
			if(words.size() > 0){
				for(size_t i = 0; i < words.size()-1; i++){
					if(words[i] != ' ') is_word = true;
				}
			}

			if(!is_word && contains_map.count("or") > 0){
				result = contains_map.at("or");
			}
			else if(is_word){
				stringstream ss(words);
				string single_word;
				while(ss >> single_word){
					for(size_t i = 0; i < single_word.size(); i++){ 
						single_word[i] = tolower(single_word[i]);
					}
					or_words.insert(single_word);
				}
				result = search.unionString(or_words, contains_map);
			}
			//add to the result set here
			set<string> candidate_set = find_cs(result, page_map);
			map<string, double> rank = pagerank(candidate_set, page_map, t, e);
			map<double, string> sorted_rank = sort_map(rank);
			//output the pagerank of each file below 
			 // for(map<double, string>::iterator it = sorted_rank.begin();
			 // 	it != sorted_rank.end(); it++){
			 // 	output << it->first << ": " << it->second << endl;
			 // }
			output << sorted_rank.size() << endl;
			for(map<double, string>::reverse_iterator rit = sorted_rank.rbegin();
				rit != sorted_rank.rend(); rit++){
				output << rit->second << endl;
			}

		}
		else if(command == "INCOMING"){
			getline(query, fname);
			set<string> in;
			bool is_file = false;

			if(fname.size() > 0){
				for(size_t i = 0; i < fname.size()-1; i++){
					if(fname[i] != ' ') is_file = true;
				}
			}
			string removing_spaces = fname;
			stringstream ss(removing_spaces);
			ss >> fname;
			if(!is_file){
				if(contains_map.count("incoming") > 0){
					in = contains_map.at("incoming");
				}
				set<string> candidate_set = find_cs(in, page_map);
				map<string, double> rank = pagerank(candidate_set, page_map, t, e);
				map<double, string> sorted_rank = sort_map(rank);

				output << sorted_rank.size() << endl;
				for(map<double, string>::reverse_iterator rit = sorted_rank.rbegin();
					rit != sorted_rank.rend(); rit++){
					output << rit->second << endl;
				}
			}
			else if(page_name_set.count(fname) > 0){
				in = page_map.at(fname)->incoming;
				output << in.size() << endl;
			}
			else output << "Invalid query" << endl;
			if(is_file){
				for(set<string>::iterator it = in.begin(); it != in.end(); it++){
					output << *it << endl;
				}
			}	
		}
		else if(command == "OUTGOING"){
			getline(query, fname);
			set<string> out;
			bool is_file = false;
			if(fname.size() > 0){
				for(size_t i = 0; i < fname.length()-1; i++){
					if(fname[i] != ' ') is_file = true;
				}
			}
			string removing_spaces = fname;
			stringstream ss(removing_spaces);
			ss >> fname;

			if(!is_file){
				if(contains_map.count("outgoing") > 0){
					out = contains_map.at("outgoing");
				}
				set<string> candidate_set = find_cs(out, page_map);
				map<string, double> rank = pagerank(candidate_set, page_map, t, e);
				map<double, string> sorted_rank = sort_map(rank);

				output << sorted_rank.size() << endl;
				for(map<double, string>::reverse_iterator rit = sorted_rank.rbegin();
					rit != sorted_rank.rend(); rit++){
					output << rit->second << endl;
				}
			}

			else if(page_name_set.count(fname) > 0){
				out = page_map.at(fname)->outgoing;
				output << out.size() << endl;
			}
			else output << "Invalid query" << endl;
			if(is_file){
				for(set<string>::iterator it = out.begin(); it != out.end(); it++){
					output << *it << endl;
				}
			}
		}
		else if(command == "PRINT"){
			getline(query, fname);
			bool is_file = false;
			if(fname.size() > 0){
				for(size_t i = 0; i < fname.length()-1; i++){
					if(fname[i] != ' ') is_file = true;
				}
			}
			string removing_spaces = fname;
			stringstream ss(removing_spaces);
			ss >> fname;
			if(!is_file){
				set<string> print_search;
				if(contains_map.count("print") > 0){
					print_search = contains_map.at("print");
				}
				set<string> candidate_set = find_cs(print_search, page_map);
				map<string, double> rank = pagerank(candidate_set, page_map, t, e);
				map<double, string> sorted_rank = sort_map(rank);

				output << sorted_rank.size() << endl;
				for(map<double, string>::reverse_iterator rit = sorted_rank.rbegin();
					rit != sorted_rank.rend(); rit++){
					output << rit->second << endl;
				}
			}
			else{
				ifstream in_file(fname);
				if(page_name_set.count(fname) > 0){
					output << fname << endl;
					print(in_file, output);
				}
				else output << "Invalid query";
				output << endl;
			}
		}
		else{
			for(size_t i = 0; i < command.size(); i++){ 
				command[i] = tolower(command[i]);
			}
			string line;
			getline(query, line);
			line.erase(0, 1);
			if(line.size() > 0) output << "Invalid query" << endl;
			else{
				set<string> result;
				if(contains_map.count(command) > 0){
					result = contains_map.at(command);
				}
				set<string> candidate_set = find_cs(result, page_map);
				map<string, double> rank = pagerank(candidate_set, page_map, t, e);
				map<double, string> sorted_rank = sort_map(rank);

				output << sorted_rank.size() << endl;
				for(map<double, string>::reverse_iterator rit = sorted_rank.rbegin();
					rit != sorted_rank.rend(); rit++){
					output << rit->second << endl;
				}
			}
		}
	}

	map<string, WebPage*>::iterator it;
	for (it = page_map.begin(); it != page_map.end(); it++) {
		delete (*it).second;
	}
}