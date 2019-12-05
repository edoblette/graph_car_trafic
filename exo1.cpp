/**
    * Exo voiture
    * Machine Parallele
    * @teacher Mehdi Boucheta <boucheta.mehdi@gmail.com>
    *
    * @autor Edgar Oblette <edwardoblette@gmail.com>
    *
    * 20/11/2019
    */
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <mutex>
#include <time.h>

#include "node.hpp"
#include "car.hpp"
#define THREAD 3
#define CARS THREAD

// PROTO
void graph_init();
void car_init();
void commounLink_adding(uint, uint);
void car_moving(uint);
void mutex_securing(uint, uint);
void treading();

// GLOBAL
std::vector<node> root;
std::vector<car> vehicules;
std::mutex global_mutex;


 /**
 	* @desc Initalise le graph avec des noeud
 */
void graph_init(){
	 // liste de ville 
	std::vector<std::string> list{"lyon", "paris", "bordeaux", "marseille", "lille", "reims", "grenoble"};  //"rouen", "annecy", "montpellier", "nantes", "montellimar"};
	
	 // cree noeud
	int i = 0;
	for (auto it = list.cbegin(); it != list.cend(); it++, ++i)
				root.push_back(node(*it, i));

	 // cree une "route" avec tout les autres villes
	for(int villeA = 0; villeA < root.size(); ++villeA){
		for(int villeB = 0; villeB< root.size(); ++villeB){
			root[villeA].add_link(&root[villeB]);
		}
	}		
	 
	 // affiche 3 noeud pour tester si tout s'est bien initialiser
	root[0].get_node();
	root[1].get_node();
	root[2].get_node();
}

 /**
 	* @desc Initalise les voitures
 */  
void car_init(){
	for(int i = 0 ; i < CARS; i++){

		 // place les voiture dans une ville
		uint newLocation;
		do{
			newLocation = (rand() % root.size()) ;
		}while(root[newLocation].isAvailable() == false);
		
		 // ajoute un objet voiture dans le vecteur 'vehicule'
		vehicules.push_back(car(newLocation, "Volvo"));

		 // met le status de la ville où la voiture est initialiser en 'indisponible'
		root[newLocation].set_availability(false);
		std::cout << "Voiture [" << i << "] " << root[newLocation].get_cityName() << std::endl;

	}

}

 /**
 	* @desc ajoute un lien entre une ville A et une ville B
 */  
void commounLink_adding(uint a, uint b){
 if((a < root.size()) && ( b < root.size()))
	root[a].add_link(&root[b]);
	root[b].add_link(&root[a]);
}

 /**
 	* @desc bloque le mutex de la prochaine ville et debloque le mutex de l'ancienne ville 
 */  
void mutex_securing(uint oldLocation, uint newLocation){
	root[newLocation].set_arriving();
	root[oldLocation].set_leaving();
}

 /**
 	* @desc bouge les voiture d'une ville A dans une ville B
 */  
void car_moving(uint id_car){

	 // tant que la voiture à de l'essence on deplace les voitures
	while(vehicules[id_car].get_gaz() > 0){
		uint newLocation;
		uint oldLocation = vehicules[id_car].get_location();

		 // cherche une nouvelle ville à visiter autre que celle actuelle 
		do{
			newLocation = root[oldLocation].get_nodeVectorId(rand() % root[oldLocation].get_nodeVectorSize()); //on choisis un route random parmis depuis la ville
		}while(newLocation == oldLocation);

		global_mutex.lock();
			std::cout << " [DEMAND]la voiture " << id_car << " veut passer a  " << root[oldLocation].get_cityName() << " à " << root[newLocation].get_cityName() << std::endl;
		global_mutex.unlock();

		 // on appele les mutex pour eviter de tout casser
		mutex_securing(oldLocation, newLocation);

		 // on deplace notre voiture
		vehicules[id_car].move(newLocation);

		global_mutex.lock();
			std::cout << "[SUCCESS]la voiture " << id_car << " passe de " << root[oldLocation].get_cityName() << " à " << root[newLocation].get_cityName() << std::endl;
		global_mutex.unlock();
		
		// on attend entre 0 et 3 secondes
		sleep(rand() % 3);
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
	treading();

	//to do
	return 0;
}