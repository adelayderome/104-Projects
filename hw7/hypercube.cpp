#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <set>


using namespace std;

struct Node{
	Node(string val, int h, int g);
	string value;
	int hVal;
	int gVal;
	int fVal;
	Node* predecessor;

};

Node::Node(string val, int h, int g){
	value = val;
	hVal = h;
	gVal = h;
}

struct Comparator{
public:
	bool operator()(const Node* lhs, const Node* rhs){
		if((lhs->fVal == rhs->fVal) && (lhs->hVal == rhs->hVal)){
			for(size_t i = 0; i < lhs->value.size(); i++){
				if((lhs->value[i] == '0') && rhs->value[i] == '1') return false;
				else if((rhs->value[i] == '0') && (lhs->value[i] == '1')) return true;
			}
		}
		else if(lhs->fVal == rhs->fVal){
			return lhs->hVal > rhs->hVal;
		}
		return lhs->fVal > rhs->fVal;
	}
};

set<string> parse_strings(ifstream &ifile){
	string curr;
	set<string> nodes;
	while(!ifile.eof()){
		ifile >> curr;
		//Node* new_node = new Node(curr);
		nodes.insert(curr);
	}
	return nodes;
}

int hval(string bits, int size){
	int h = 0;
	for(int i = 0; i < size; i++){
		if(bits[i] == '0') h++;
	}
	return h;
}
string find_end(int size){
	string end = "1";
	for(int i = 0; i < size-1; i++){
		end+='1';
	}
	return end;
}

set<string> find_neighbors(string bits, int size, set<string> vals){

	set<string> neighbors;

	for(int i = 0; i < size; i++){
		string neighbor = bits;
		if(bits[i] == '0'){
			neighbor[i] = '1';
		}
		else if(bits[i] == '1'){
			neighbor[i] = '0';
		}
		if(vals.find(neighbor) != vals.end()) neighbors.insert(neighbor);
	}
	return neighbors;
}

void print_nodes(Node* curr){
	if(curr->predecessor == NULL){
		cout << curr->value << endl;
		return;
	}
	print_nodes(curr->predecessor);
	cout << curr->value << endl;
}

void print(Node* end_node, int expansions){
	print_nodes(end_node);
	cout << "expansions = " << expansions << endl;

}

int main(int argc, char* argv[]){
	string node1 = argv[1];
	ifstream ifile(argv[2]);
	int ncount;
	ifile >> ncount;
	int size = node1.length();
	string end_node = find_end(size);

	set<string> nodes = parse_strings(ifile);

	typedef priority_queue<Node*, vector<Node*>, Comparator> my_pq;
	my_pq pq;

	int g = 0;
	Node* end = new Node(end_node, 0, 0);
	Node* start = new Node(node1, hval(node1, size), g);
	start->predecessor = NULL;
	start->fVal = start->hVal;

	set<string> visited;
	pq.push(start);
	int expansions = 0;
	bool complete = false;
	while(!pq.empty()){
		Node* top = pq.top();
		//cout << top->value << endl;
		pq.pop();
		if(top->value == end_node){
			end = top;
			complete = true;
		 	break; //maybe edit this, or return if put in function
		}
		else if(visited.find(top->value) == visited.end()){
			visited.insert(top->value);
			expansions++;
			g = top->gVal+1;

			set<string> neighbors = find_neighbors(top->value, size, nodes);
			for(set<string>::iterator it = neighbors.begin();
			  it != neighbors.end(); it++){
				//expansions++;
				Node* new_node = new Node(*it, hval(*it, size), g);
				new_node->predecessor = top;
				new_node->fVal = new_node->hVal + new_node->gVal;
				pq.push(new_node);
			}
		}

	}
	
	if(complete){
		print(end, expansions);
	}
	else{
		cout << "No transformation" << endl << "expansions = " << expansions;
		cout << endl;
	}

}
	// --keep a closed list of visited--add the top here
	// 	--if top has already been visited, dont explore the neighbors
	//...just ignore here
	// 	--add to expnasions if not already visited 
	// 	--if top equals end value then stop 
	// 	add valid neighbors of top to pq
	// 		top.g+1 --for each of the nodes
	// 		the g for the neighbors is one more than the g for the top 

	// if exits while loop, w/o finding 11111 path not found6