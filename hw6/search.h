#include <string>
#include <set>
#include <map>

class WebPage{
public:
 	WebPage(std::string n) : name(n){}
 	std::string name; 
 	std::set<std::string> outgoing;
 	std::set<std::string> incoming;

}; 

class Search{
public:
	//is it also map<T??.. check how this will be graded && if need to return 
	//templated set for it to work
	Search(){};
	template<typename T>
	std::set<std::string> intersectString(std::set<T> targets, 
	std::map<T, std::set<std::string> > &targets_map);

	template<typename T>
	std::set<std::string> unionString(std::set<T> targets, 
	std::map<T, std::set<std::string> > &targets_map);
	// std::set<std::string> intersectString(std::set<std::string> words, 
	// 	std::map<std::string, std::set<std::string> > &words_map);
	// std::set<std::string> unionString(std::set<std::string> words, 
	// 	std::map<std::string, std::set<std::string> > &words_map);
};