class  car{
	private:
		std::string _name;
		int _location;

	public:
		car(int initLocation, std::string initName){
			_location = initLocation;
			_name = initName;
		}

	//setter
		void move(int moveLocation){
			if(_location != moveLocation)
				_location = moveLocation;
		}

	//getter
 		int get_location(){
 			return _location;
 		}
};
