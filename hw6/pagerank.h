//all new functions for search.cpp for hw6 are here 
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>

std::set<std::string> find_cs(std::set<std::string> pages, std::map<std::string, WebPage*> page_map){
	std::set<std::string> candidate_set;
	for(std::set<std::string>::iterator it = pages.begin(); it != pages.end(); it++){
		candidate_set.insert(*it);
		candidate_set.insert(page_map.at(*it)->outgoing.begin(), 
			page_map.at(*it)->outgoing.end());
		candidate_set.insert(page_map.at(*it)->incoming.begin(), 
			page_map.at(*it)->incoming.end());
	}
	return candidate_set;
}

std::set<std::string> pagerank_incoming(std::string page_name, std::set<std::string> candidates, 
	std::map<std::string, WebPage*> page_map){
	//include own page for self loop
	std::set<std::string> new_incoming;
	std::set<std::string> all_in = page_map.at(page_name)->incoming;
	for(std::set<std::string>::iterator it = all_in.begin(); it != all_in.end(); it++){
		if(candidates.find(*it) != candidates.end()){
			new_incoming.insert(*it);
		}
	}
	new_incoming.insert(page_name);
	return new_incoming;
}

std::map<std::string, int> find_out_degrees(std::set<std::string> candidates, 
	std::map<std::string, WebPage*> page_map){
	std::map<std::string, int> outdegs;
	for(std::set<std::string>::iterator it = candidates.begin(); it != candidates.end();
		it++){
		int degree = 0;
		std::set<std::string> all_out = page_map.at(*it)->outgoing;
		for(std::set<std::string>::iterator it2 = all_out.begin(); it2 != all_out.end();
			it2++){
			if(candidates.find(*it2) != candidates.end()){
				degree++;
			}
		}
		degree++; //add one for self loop
		outdegs.insert(std::pair<std::string, int>(*it, degree));
	}
	return outdegs;
}

std::map<std::string, double> pagerank(std::set<std::string> candidate_set, 
	std::map<std::string, WebPage*> page_map, int t, double e){

	std::map<std::string, double> ranks;
	double first_rank = (double)1/candidate_set.size();
	int n = candidate_set.size();
	for(std::set<std::string>::iterator it = candidate_set.begin(); 
		it != candidate_set.end(); it++){
		ranks.insert(std::pair<std::string, double>(*it, first_rank));
	}
	//need to find new out degree for each page 
	//add one to out degree for each for self loop
	std::map<std::string, int> out_degrees = find_out_degrees(candidate_set, page_map);
	//need to find list of incoming links to each node 
	std::map<std::string, std::set<std::string> > incoming_links;
	for(std::set<std::string>::iterator it = candidate_set.begin();
		it != candidate_set.end(); it++){
		std::set<std::string> new_incoming = pagerank_incoming(*it, candidate_set,
			page_map);
		incoming_links.insert(std::pair<std::string, std::set<std::string> >(*it, new_incoming));
	}
	for(int i = 0; i < t; i++){
	//do equation t times 
		std::map<std::string, double> temp_ranks;
		//keep temp std::set here?--push the values to the actual std::set once done loops
		for(std::set<std::string>::iterator it = candidate_set.begin();
			it != candidate_set.end(); it++){
		//for each node get pagerank value during each t iteration
			double sum = 0;
			for(std::set<std::string>::iterator it2 = incoming_links.at(*it).begin(); 
				it2 != incoming_links.at(*it).end(); it2++){
			//summation of the pagerank equation
			//goes through all incoming nodes to the current node/page
			//does operation 
				double out = (double)out_degrees.at(*it2); //make sure all doubles
				sum += (ranks.at(*it2))*(1/out);
			}
			double new_rank = ((1-e)*sum)+(e/n);
			temp_ranks.insert(std::pair<std::string, double>(*it, new_rank));
		}
		for(std::map<std::string, double>::iterator it3 = temp_ranks.begin();
			it3 != temp_ranks.end(); it3++){
			ranks.at(it3->first) = it3->second;
		}
	}
	return ranks;
}
std::map<double, std::string> sort_map(std::map<std::string, double> first_map){
	std::map<double, std::string> sorted_map;
	for(std::map<std::string, double>::iterator it = first_map.begin(); 
		it != first_map.end(); it++){
		sorted_map.insert(std::pair<double, std::string>(it->second, it->first));
	}
	return sorted_map;
}
void parse_config(std::string &index, std::ifstream &config_file, std::string &query, 
	std::string &output, double &e, int &t){
	std::string full_line;
	std::string parameter;
	while(getline(config_file, full_line)){
		if(full_line[0] == '#'); //skip this line
		else{
			std::stringstream line(full_line);
			line >> parameter;
			char equals;
			if(parameter == "QUERY_FILE"){
				line >> equals;
				if(equals == '='){ //make sure 
					line >> query;
				}
			}
			else if(parameter == "INDEX_FILE"){
				line >> equals;
				if(equals == '='){
					line >> index;
				}
			}
			else if(parameter == "OUTPUT_FILE"){
				line >> equals;
				if(equals == '='){
					line >> output;
				}
			}
			else if(parameter == "RESTART_PROBABILITY"){
				line >> equals;
				if(equals == '='){
					line >> e;
				}
			}
			else if(parameter == "STEP_NUMBER"){
				line >> equals;
				if(equals == '='){
					line >> t;
				}
			}
		}
	}
}