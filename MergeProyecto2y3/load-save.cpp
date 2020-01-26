#pragma once

#include <fstream>
#include <sstream>

#include "Structures.h"

void loadGame()
{
	std::fstream file;
	file.open("save.thc", std::ios::in | std::ios::binary);
	int UsersSize = 0;
	file.read((char*)&UsersSize, sizeof(int));
	users.resize(UsersSize);
	for (size_t i = 0; i < UsersSize; i++)
	{
		User AuxUser = users[i];
		std::string userName;
		int userNameSize = 0;
		file.read((char*)&userNameSize, sizeof(int));
		userName.resize(userNameSize);
		for (size_t n = 0; n < userNameSize; n++)
		{
			char AuxChar = ' ';
			file.read((char*)&AuxChar, sizeof(char));
			userName[n] = AuxChar;
		}
		AuxUser.name = userName;

		std::string userPsswrd;
		int userPsswrdSize = 0;
		file.read((char*)&userPsswrdSize, sizeof(int));
		userPsswrd.resize(userPsswrdSize);
		for (size_t c = 0; c < userPsswrdSize; c++)
		{
			char AuxChar = ' ';
			file.read((char*)&AuxChar, sizeof(char));
			userPsswrd[c] = AuxChar;
		}
		AuxUser.password = userPsswrd;
		file.read((char*)&AuxUser.admin, sizeof(bool));
		int userCharactersSize = 0;
		file.read((char*)&userCharactersSize, sizeof(int));
		for (size_t p = 0; p < userCharactersSize; p++)
		{
			Character AuxCharacter = AuxUser.characters[p];
			std::string characterName;
			int characterNameSize = 0;
			file.read((char*)&characterNameSize, sizeof(int));
			characterName.resize(characterNameSize);
			for (size_t cn = 0; cn < characterNameSize; cn++)
			{
				char AuxChar = ' ';
				file.read((char*)&AuxChar, sizeof(char));
				characterName[cn] = AuxChar;
			}
			AuxCharacter.name = characterName;
			file.read((char*)&AuxCharacter.race, sizeof(Race));
			file.read((char*)&AuxCharacter.level, sizeof(int));
			int characterAttackSize = 0;
			file.read((char*)&characterAttackSize, sizeof(int));
			for (size_t a = 0; a < characterAttackSize; a++)
			{
				AttackIDs attackId = NON;
				file.read((char*)&attackId, sizeof(AttackIDs));
				AuxCharacter.attackVector[a] = attackId;
			}
			file.read((char*)&AuxCharacter.item, sizeof(ItemIDs));
			AuxUser.characters[p] = AuxCharacter;
		}
		users[i] = AuxUser;
	}
	file.close();
}

void saveGame()
{
	std::fstream file;
	file.open("save.thc", std::ios::out | std::ios::binary | std::ios::trunc);
	int UsersSize = users.size();
	file.write((char*)&UsersSize, sizeof( int));
	for (size_t i = 0; i < UsersSize; i++)
	{
		User AuxUser = users[i];
		std::string userName = AuxUser.name;
		int userNameSize = userName.size();
		file.write((char*)&userNameSize, sizeof(int));
		for (size_t n = 0; n < userNameSize; n++)
		{
			char AuxChar = userName[n];
			file.write((char*)&AuxChar,sizeof(char));
		}
		std::string userPsswrd = AuxUser.password;
		int userPsswrdSize = userPsswrd.size();
		file.write((char*)&userPsswrdSize, sizeof(int));
		for (size_t c = 0; c < userPsswrdSize; c++)
		{
			char AuxChar = userPsswrd[c];
			file.write((char*)&AuxChar, sizeof(char));
		}
		file.write((char*)&AuxUser.admin, sizeof(bool));
		int userCharactersSize = AuxUser.characters.size();
		file.write((char*)&userCharactersSize,sizeof(int));
		for (size_t p = 0; p < userCharactersSize; p++)
		{
			Character AuxCharacter = AuxUser.characters[p];
			std::string CharacterName = AuxCharacter.name;
			int CharacterNameSize = AuxCharacter.name.size();
			file.write((char*)&CharacterNameSize, sizeof(int));
			for (size_t cn = 0; cn < CharacterNameSize; cn++)
			{
				char AuxChar = CharacterName[cn];
				file.write((char*)&AuxChar, sizeof(char));
			}
			file.write((char*)&AuxCharacter.race, sizeof(Race));
			file.write((char*)&AuxCharacter.level, sizeof(int));
			int CharacterAttacksSize = AuxCharacter.attackVector.size();
			file.write((char*)&CharacterAttacksSize, sizeof(int));
			for (size_t a = 0; a < CharacterAttacksSize; a++)
			{
				AttackIDs attackId = AuxCharacter.attackVector[a];
				file.write((char*)&attackId, sizeof(AttackIDs));
			}
			file.write((char*)&AuxCharacter.item, sizeof(ItemIDs));
		}
	}
	file.close();
}