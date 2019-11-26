#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <mutex>
#include <time.h>

#include "node.hpp"
#include "car.hpp"
#define THREAD 3
#define CARS 3

// PROTO
void commounLink_adding(uint, uint);
void graph_init();
void car_init();
void car_moving(uint);
void change_availability(uint, uint);
void treading();

// GLOBAL
std::vector<node> root;
std::vector<car> vehicules;
std::mutex global_mutex;


void commounLink_adding(uint a, uint b){
 if((a < root.size()) && ( b < root.size()))
	root[a].add_link(&root[b]);
	root[b].add_link(&root[a]);
}

void change_availability(uint oldLocation, uint newLocation){

	root[newLocation].set_availability(false);
	root[oldLocation].set_availability(true);
}

void graph_init(){
	std::vector<std::string> list{"lyon", "paris", "bordeaux", "marseille", "lille", "reims"};
	//cree node
	int i = 0;
	for (auto it = list.cbegin(); it != list.cend(); it++, ++i)
				root.push_back(node(*it, i));

	//cree lien
	for(int villeA = 0; villeA < root.size(); ++villeA){
		for(int villeB = 0; villeB< root.size(); ++villeB){
			root[villeA].add_link(&root[villeB]);
		}
	}		
	
	root[0].get_node();
	root[1].get_node();
	root[2].get_node();
}

void car_init(){
	for(int i = 0 ; i < CARS; i++){
		uint newLocation;
		do{
			newLocation = (rand() % root.size()) ;
		}while(root[newLocation].isAvailable() == false);
		
		vehicules.push_back(car(newLocation, "Volvo"));
		root[newLocation].set_availability(false);
		std::cout << "Voiture [" << i << "] " << root[newLocation].get_cityName() << std::endl;

	}

}

void car_moving(uint id_car){

	uint newLocation;
	uint oldLocation = vehicules[id_car].get_location();
	
	newLocation = root[oldLocation].get_nodeVectorId(rand() % root[oldLocation].get_nodeVectorSize()); //on choisis un route random parmis depuis la ville
	
	if(root[newLocation].isAvailable()){	
		change_availability(oldLocation, newLocation);
		vehicules[id_car].move(newLocation);
		global_mutex.lock();
			std::cout << "[SUCCESS]la voiture " << id_car << " passe de " << root[oldLocation].get_cityName() << " à " << root[newLocation].get_cityName() << std::endl;
		global_mutex.unlock();
	}else{
		global_mutex.lock();
			std::cout << "[FAIL]la voiture " << id_car << " ne peut pas passer de " << root[oldLocation].get_cityName() << " à " << root[newLocation].get_cityName() << std::endl;
		global_mutex.unlock();
		sleep(rand() % 5);
		car_moving(id_car);
	}
 	
}

void treading(){
	std::vector<std::thread> liste; 
  // Create Thread  
	for(int nbThread = 0; nbThread < THREAD; liste.emplace_back(car_moving, nbThread++));

  // Join Thread        
	for(int nbThread = 0; nbThread < THREAD; liste[nbThread++].join());
}

int main()
{
  	srand (time(NULL));
	graph_init();
	car_init();
	for(int i = 0; i < 5; i++){
		treading();
		std::cout << "\n";
	}

	//to do
	return 0;
}