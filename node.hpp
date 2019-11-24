
class  node{
	private:
		std::string _ville;
		std::vector<node *> _V;
		bool _availability;
		int _id;


	public:
		node(std::string newVille, int id){
			_ville = newVille;
			_availability = true;
			_id = id;

		}

	//setter
		void add_link(node *newVille){
			if(this != newVille)
				_V.push_back(newVille);
		}

		void rename(std::string newName){
			_ville = newName;
		}

		void set_availability(bool newState){
			_availability = newState;
		}

	//getter
 		void get_node(){
 			std::cout << '[' << _ville << ']' << std::endl;
 			for (auto it = _V.cbegin(); it != _V.cend(); it++)
				std::cout << "->" << (*it)->_ville << std::endl;
 		}

 		int get_nodeVectorSize(){
 			return _V.size();
 		}

 		int get_nodeVectorId(int index){
 			return _V[index]->_id;
 		}
 			
 		std::string get_cityName(){
 			return _ville;
 		}

 		bool isAvailable(){
 			return _availability;
 		}
};
