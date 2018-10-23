#include <string>
#include <set>
#include <map>

//just make templatred for this assignment reasons
//put these functions in search class ???
template<typename T>
std::set<std::string> Search::intersectString(std::set<T> targets, 
	std::map<T, std::set<std::string> > &targets_map){ //map<T ??
	//change initial map to be typename T? even though always string?
	std::set<std::string> files_result;
	std::set<std::string> empty;

	if(targets.size() == 1){
		std::set<std::string>::iterator it = targets.begin();
		if(targets_map.count(*it) > 0){
			return targets_map.at(*it);
		}
		else return empty;
	}
	std::set<std::string>::iterator it = targets.begin();
	if(targets_map.find(*it) == targets_map.end()){
		return empty;
	}
	std::set<std::string> set1 = targets_map.at(*it);
	std::set<std::string> files;

	it++;
	while(it != targets.end()){
		files.clear();

		if(targets_map.find(*it) == targets_map.end()){
			return empty;
		}
		std::set<std::string> set2 = targets_map.at(*it);

		for (std::set<std::string>::iterator it1 = set1.begin(); 
			it1 != set1.end(); it1++){
			for(std::set<std::string>::iterator it2 = set2.begin();
				it2 != set2.end(); it2++){
				if(*it1 == *it2){
					files.insert(*it1);
				}
			}
		}
		set1 = files;
		it++;
	}
	return files;
}

template<typename T>
std::set<std::string> Search::unionString(std::set<T> targets, 
	std::map<T, std::set<std::string> > &targets_map){

	std::set<std::string> files_result;
	std::set<std::string> empty;

	if(targets.size() == 1){
		typename std::set<T>::iterator it = targets.begin();
		if(targets_map.count(*it) > 0){
			return targets_map.at(*it);
		}
		else return empty;
	}

	typename std::set<T>::iterator it;
	for(it = targets.begin(); it != targets.end(); it++){
		if(targets_map.count(*it) > 0){
			std::set<std::string> single_set = targets_map.at(*it);
			files_result.insert(single_set.begin(), single_set.end());
		}
	}
	return files_result;
}