class  car{
	private:
		std::string _name;
		int _location;
		int _gaz ;

	public:
		car(int initLocation, std::string initName) : _name(initName), _location(initLocation), _gaz(10){}


	//setter
		void move(int moveLocation){
			if(_location != moveLocation){
				_location = moveLocation;
				_gaz -= 1;
			}
		}

	//getter
 		int get_location(){
 			return _location;
 		}

 		int get_gaz(){
 			return _gaz;
 		}
};
