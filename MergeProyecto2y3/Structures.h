#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <list>

enum Race {	NONE,BARBAR,ASSASSIN,ARCHER,NIGROMANT,MAGICIAN };
enum AttackIDs { NON, PUNCH, SWORD_THRUST, KNIFE_STAB, SHIELD };
enum ItemIDs { VOID, SCHANPPS, PIKE, BOW, LONG_BOW, KNIFE, CLUB };

struct Character {
	std::string name;
	Race race;
	int level;
	std::array<AttackIDs, 4> attackVector;
	ItemIDs item;

	Character() {};
	Character(std::string _name, Race _race, int _level)
	{
		name = _name;
		race = _race;
		level = _level;
	};
	Character(std::string _name, Race _race, int _level, std::array<AttackIDs, 4> _attackVector, ItemIDs _item)
	{
		name = _name;
		race = _race;
		level = _level;
		attackVector = _attackVector;
		item = _item;
	};
};

struct User {
	std::string name;
	std::string password;
	bool admin = false;
	std::array<Character, 5> characters;

	User() {};
	User(std::string _name, std::string _password)
	{
		name = _name;
		password = _password;
	};
	User(std::string _name, std::string _password, bool _admin, std::array<Character, 5> _characters)
	{
		name = _name;
		password = _password;
		admin = _admin;
		characters = _characters;
	};
};

extern std::vector<User> users;