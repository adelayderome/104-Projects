#include "qsort.h"
#include "LengthMismatch.h"
#include <vector>

template <class T>
struct LessComp {
	bool operator()(T val1, T val2){
		return val1 <= val2;
	}
};

template <class T>
struct GreaterComp{
	bool operator()(T val1, T val2){
		return val1 >= val2;
	}
};

std::vector<std::pair<int, int>> assignPlates(std::vector<int> turkeys,
 std::vector<int> potatoes) {
 	std::vector<std::pair<int, int>> result;
 	std::vector<std::pair<int, int>> empty;

 	size_t t_count = turkeys.size(); 
 	size_t p_count = potatoes.size(); 

	if(t_count != p_count){
		int p = static_cast<int>(p_count);
		int t = static_cast<int>(t_count);
		throw LengthMismatch(t, p);
	}

	LessComp<int> comp1; 
	GreaterComp<int> comp2;

	QuickSort(turkeys, comp1); //sorts turkey cal counts from small->large
	QuickSort(potatoes, comp2); //sorts pot cal count from large->small
	//switch to sort() algorithm ? make sure this works

	int total = turkeys[0] + potatoes[0];
	result.push_back(std::make_pair(turkeys[0], potatoes[0]));

	for(size_t i = 1; i < t_count; i++){
		int cals = turkeys[i] + potatoes[i];
		if(cals != total) return empty;

		result.push_back(std::make_pair(turkeys[i], potatoes[i]));
	}

	return result;
}
