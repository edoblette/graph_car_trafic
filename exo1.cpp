#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;


class  node{
	private:
		int _id;
		std::vector<node> _V;


	public:
		node(int id){
			_id = id;
		}
	//operator
		node &operator[] (int index){
			return _V[index];
		}
	//setter
		void add_node(int id){
			node new_node(id);
			_V.push_back(new_node);
		}
	//getter
 		void get_node(){
 			std::cout << this->_id << std::endl;
 			for (auto it = this->_V.cbegin(); it != this->_V.cend(); it++){
				std::cout << "->" << it->_id << std::endl;
			}

 		}
};

int main()
{
	node root(1);
	root.add_node(2);
	root[1].add_node(3);
	root.get_node();

	//to do
	return 0;
}