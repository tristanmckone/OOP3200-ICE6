// OOP3200-ICE6.cpp : 
//Tristan Mckone
// 2021-10-21
#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

#include "GameObject.h"
#include "Vector3D.h"

void PrintGameObjects(const std::map<std::string, GameObject*>& game_objects)
{
	std::cout << "=================================" << std::endl;
	std::cout << " Output map of Game Objects      " << std::endl;
	std::cout << "=================================" << std::endl;

	// for every game_object in gameObjects...loop
	for (const auto& game_object : game_objects)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString();
		std::cout << "---------------------------------\n" << std::endl;
	}
}


int main()
{
	// map is made up of key-value pairs - in this case the key is a string
	// and the value is a GameObject
	std::map<std::string, GameObject*> gameObjects;

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);
	auto* space_station = new GameObject("SpaceStation", 2, 100.0f, 200.0f);

	gameObjects[ship->GetName()] = ship;
	gameObjects[enemy->GetName()] = enemy;
	gameObjects[space_station->GetName()] = space_station;

	PrintGameObjects(gameObjects);

	auto distance = Vector2D<float>::Distance(gameObjects["Ship"]->GetPosition(), gameObjects["Enemy"]->GetPosition());

	std::cout << "Distance between " << gameObjects["Ship"]->GetName()
		<< " and " << gameObjects["Enemy"]->GetName() << " is: " << std::to_string(distance) << "\n" << std::endl;


	// start output
	std::ofstream outfile("GameObject.txt", std::ios::out);
	outfile << gameObjects["Ship"]->ToFile() << std::endl;
	outfile << gameObjects["Enemy"]->ToFile() << std::endl;
	outfile << gameObjects["SpaceStation"]->ToFile() << std::endl;
	outfile.close();

	std::cout << "------------------------------------------------------------------------------------------------\n";
	std::cout << " END OF OUTPUT \n";
	std::cout << "------------------------------------------------------------------------------------------------\n\n";

	std::cout << "\n------------------------------------------------------------------------------------------------\n";
	std::cout << " STARTING INPUT \n";
	std::cout << "------------------------------------------------------------------------------------------------\n\n";


	std::ifstream infile;
	std::string fileName = "GameObject.txt";

	infile.open(fileName.c_str());

	if (infile.is_open())
	{
		int id;
		float x, y;
		std::string name;

		while (!infile.fail())
		{
			infile >> id >> name;
			infile.ignore(1, ' ');
			infile.ignore(1, '(');
			infile >> x;
			infile.ignore(1, ',');
			infile.ignore(1, ' ');
			infile >> y;
			infile.ignore(1, ')');

			auto* temp_object = new GameObject(name, id, x, y);

			gameObjects[name + " 1"] = temp_object;
		}
		infile.close();
	}


	PrintGameObjects(gameObjects);


	std::cout << "------------------------------------------------------------------------------------------------\n";
	std::cout << " END OF INPUT \n";
	std::cout << "------------------------------------------------------------------------------------------------\n\n";

}