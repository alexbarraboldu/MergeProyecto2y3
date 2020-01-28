#pragma once

#include "Structures.h"
#include "Functions.h"

void saveGame();
void loadGame();

bool gameLoop = true;

int countaUsers;

std::vector<User> users;

int main()
{ 
	loadGame();
	while (gameLoop == true)
	{
		LoginMenu();
		while (menuLoop == true)
		{
			bool userType = users.at(idUser).admin;
			switch (userType)
			{
			case false:
				PlayerMenu(countaUsers);
				break;
			case true:
				AdminMenu(countaUsers);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}


//Race raza = Race::ASSASSIN;
//std::array<AttackIDs, 4> ataques = { PUNCH, KNIFE_STAB, SHIELD, NON };
//ItemIDs item = ItemIDs::BOW;
//Character character("elyte", raza, 1, ataques, item);
//std::array<Character, 5> characters = { character, character, character, character, character};
//bool admin = true;
//User user1("enti", "enti", admin, characters);
//
//int main()
//{
//	users.resize(1);
//	users[0] = user1;
//
//	saveGame();
//	//loadGame();
//	std::cout << "\nname: " << users.at(0).name;
//	std::cout << "\npsswrd: " << users.at(0).password;
//	std::cout << "\nname character: " << users.at(0).characters[0].name;
//	std::cout << "\nattack SIZE: " << users.at(0).characters[0].attackVector.size();
//
//	return 0;
//}