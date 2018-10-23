#include <vector>

// template <class T>
// struct LessComp {
// 	bool operator()(T val1, T val2){
// 		return val1 <= val2;
// 	}
// };

// template <class T>
// struct GreaterComp{
// 	bool operator()(T val1, T val2){
// 		return val1 >= val2;
// 	}
// };

template<class T>
int find_pivot(std::vector<T> &myArray, int a_start, int a_end){
	//take first, middle, and last element, find the median 
	T start = myArray[a_start];
	T end = myArray[a_end];
	T middle = myArray[(a_start+a_end)/2];
	if(start <= middle){
		if(start >= end) return a_start;
		else if(middle < end) return (a_start+a_end)/2;
		else if(end < middle) return a_end;
	}
	else{
		if(start < end)return a_start;
		else if(middle > end) return (a_start+a_end)/2;
		//else return a_end; check if this is okay
	}
	return a_end;
}

template<class T>
void swap(std::vector<T> &myArray, int index1, int index2){ 
	T temp = myArray[index1];
	myArray[index1] = myArray[index2];
	myArray[index2] = temp;
}

template<class T, class Comparator>
int partition(std::vector<T> &myArray, Comparator comp, int left, int right){
	int i = left;

	int pivot_index = find_pivot(myArray, left, right);
	T pivot = myArray[pivot_index];
	swap(myArray, pivot_index, right);

	for(int j = left; j < right; j++){
		if(comp(myArray[j], pivot)){
			swap(myArray, i, j);
			i++;
		}
	}
	swap(myArray, i, right);
	return i;
}

template <class T, class Comparator>
void qsHelper(std::vector<T> &myArray, Comparator comp, int start, int end){
	if(start == end){
		return; 
	}
	else if(start < end){
		int location = partition(myArray, comp, start, end);
		qsHelper(myArray, comp, start, location-1);
		qsHelper(myArray, comp, location+1, end);
	}
	
}

template <class T, class Comparator>
void QuickSort(std::vector<T> &myArray, Comparator comp){
	//check base case--if size 1 list (or size 2?)
	//unsigned-signed int issue maybe
	if(myArray.size() < 2) return;
	std::size_t end1 = myArray.size()-1;
	int end = static_cast<int>(end1);

	qsHelper(myArray, comp, 0, end);
}