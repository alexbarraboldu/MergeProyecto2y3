#pragma once

#include <fstream>
#include <sstream>

#include "Structures.h"
#include "Gameplay.h"

void loadGame()
{
	std::fstream file;
	file.open("save.thc", std::ios::in | std::ios::binary);
	if (file.fail()) return;
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
	if (file.fail()) return;
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

struct infoVectorRoom
{
	char direction;
	int indexVector;
	infoVectorRoom() {};
	infoVectorRoom(char _direction, int _indexVector)
	{
		direction = _direction;
		indexVector = _indexVector;
	};
};

void loadGameState()
{
	std::fstream file;
	file.open("dungeon.thc", std::ios::in | std::ios::binary);
	if (file.fail()) return;
	std::vector<room*> AuxRoomList;
	int roomListSize;
	file.read((char*)&roomListSize, sizeof(int));
	std::vector<std::vector<infoVectorRoom>> VectorArrayIVR;
	VectorArrayIVR.resize(roomListSize);
	AuxRoomList.resize(roomListSize);
	for (size_t r = 0; r < roomListSize; r++)
	{
		room* AuxRoom = new room;
		std::vector<infoVectorRoom> ArrayIVR;
		int ArrayIVRSize;
		file.read((char*)&ArrayIVRSize, sizeof(int));
		ArrayIVR.resize(ArrayIVRSize);
		for (size_t v = 0; v < ArrayIVRSize; v++)
		{
			file.read((char*)&ArrayIVR[v].direction, sizeof(char));
			file.read((char*)&ArrayIVR[v].indexVector, sizeof(int));
			/*infoVectorRoom AuxInfoVectorRoom;
			file.read((char*)&AuxInfoVectorRoom.direction, sizeof(char));
			file.read((char*)&AuxInfoVectorRoom.indexVector, sizeof(int));
			ArrayIVR.push_back(AuxInfoVectorRoom);*/
		}
		VectorArrayIVR.at(r) = ArrayIVR;
		std::vector<Enemy> AuxEnemyList;
		int enemyListSize;
		file.read((char*)&enemyListSize, sizeof(int));
		AuxRoom->startEnemyNum = enemyListSize;
		AuxEnemyList.resize(enemyListSize);
		for (size_t e = 0; e < enemyListSize; e++)
		{
			file.read((char*)&AuxEnemyList[e].skin, sizeof(char));
			file.read((char*)&AuxEnemyList[e].pos.X, sizeof(int));
			file.read((char*)&AuxEnemyList[e].pos.Y, sizeof(int));
		}
		AuxRoom->enemyList = AuxEnemyList;
		file.read((char*)&AuxRoom->player.skin, sizeof(char));
		file.read((char*)&AuxRoom->player.pos.X, sizeof(int));
		file.read((char*)&AuxRoom->player.pos.Y, sizeof(int));
		charbivector AuxMap;
		int AuxMapSizeFirstVector, AuxMapSizeSecondVector;
		file.read((char*)&AuxMapSizeFirstVector, sizeof(int));
		file.read((char*)&AuxMapSizeSecondVector, sizeof(int));
		AuxMap.resize(AuxMapSizeFirstVector);
		for (size_t i = 0; i < AuxMapSizeFirstVector; i++)
		{
			for (size_t j = 0; j < AuxMapSizeSecondVector; j++)
			{
				AuxMap[i].resize(AuxMapSizeSecondVector);
				file.read((char*)&AuxMap[i][j], sizeof(char));
			}
		}
		AuxRoom->map = AuxMap;
		file.read((char*)&AuxRoom->size, sizeof(int));
		AuxRoomList[r] = AuxRoom;
	}
	int AuxRoomListSize = AuxRoomList.size();
	for (size_t i = 0; i < AuxRoomListSize; i++)
	{
		int ArrayIVRSize = VectorArrayIVR[i].size();
		for (size_t l = 0; l < ArrayIVRSize; l++)
		{
			if (VectorArrayIVR[i][l].direction == 'n') AuxRoomList[i]->north = AuxRoomList[VectorArrayIVR[i][l].indexVector];
			if (VectorArrayIVR[i][l].direction == 's') AuxRoomList[i]->south = AuxRoomList[VectorArrayIVR[i][l].indexVector];
			if (VectorArrayIVR[i][l].direction == 'e') AuxRoomList[i]->east = AuxRoomList[VectorArrayIVR[i][l].indexVector];
			if (VectorArrayIVR[i][l].direction == 'w') AuxRoomList[i]->west = AuxRoomList[VectorArrayIVR[i][l].indexVector];
		}
	}
	roomList = AuxRoomList;
	file.close();
}

void saveGameState()
{
	std::fstream file;
	file.open("dungeon.thc", std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.fail()) return;
	std::vector<room*> AuxRoomList;
	AuxRoomList.reserve(roomList.size());
	int AuxRoomListSize = roomList.size();
	AuxRoomList = roomList;
	file.write((char*)&AuxRoomListSize, sizeof(int));
	for (size_t i = 0; i < AuxRoomListSize; i++)
	{
		std::vector<infoVectorRoom> ArrayIVR;
		ArrayIVR.reserve(4);
		room* AuxRoom = AuxRoomList[i];
		for (size_t i = 0; i < AuxRoomListSize; i++)
		{
			if (AuxRoom->north == AuxRoomList[i] && AuxRoom != AuxRoomList[i]) { 
				ArrayIVR.push_back(infoVectorRoom('n', i)); continue; }
			else if (AuxRoom->south == AuxRoomList[i] && AuxRoom != AuxRoomList[i]) { ArrayIVR.push_back(infoVectorRoom('s', i)); continue; }
			else if (AuxRoom->east == AuxRoomList[i] && AuxRoom != AuxRoomList[i]) { ArrayIVR.push_back(infoVectorRoom('e', i)); continue; }
			else if (AuxRoom->west == AuxRoomList[i] && AuxRoom != AuxRoomList[i]) { ArrayIVR.push_back(infoVectorRoom('w', i)); continue; }
		}
		ArrayIVR.shrink_to_fit();
		int ArrayIVRSize = ArrayIVR.size();
		file.write((char*)&ArrayIVRSize, sizeof(int));
		for (size_t i = 0; i < ArrayIVRSize; i++)
		{
			file.write((char*)&ArrayIVR[i].direction, sizeof(char));
			file.write((char*)&ArrayIVR[i].indexVector, sizeof(int));
		}
		std::vector<Enemy> AuxEnemyList = AuxRoom->enemyList;
		int enemyListSize = AuxEnemyList.size();
		file.write((char*)&enemyListSize, sizeof(int));
		for (size_t i = 0; i < enemyListSize; i++)
		{
			file.write((char*)&AuxEnemyList[i].skin, sizeof(char));
			file.write((char*)&AuxEnemyList[i].pos.X, sizeof(int));
			file.write((char*)&AuxEnemyList[i].pos.Y, sizeof(int));
		}
		Player AuxPlayer = AuxRoom->player;
		file.write((char*)&AuxPlayer.skin, sizeof(char));
		file.write((char*)&AuxPlayer.pos.X, sizeof(int));
		file.write((char*)&AuxPlayer.pos.Y, sizeof(int));
		charbivector AuxMap = AuxRoom->map;
		int AuxMapSizeFirstVector = AuxMap.size();
		int AuxMapSizeSecondVector = AuxMap[0].size();
		file.write((char*)&AuxMapSizeFirstVector, sizeof(int));
		file.write((char*)&AuxMapSizeSecondVector, sizeof(int));
		for (size_t i = 0; i < AuxMapSizeFirstVector; i++)
		{
			for (size_t j = 0; j < AuxMapSizeSecondVector; j++)
			{
				char casilla = AuxMap[i][j];
				file.write((char*)&casilla, sizeof(char));
			}
		}
		file.write((char*)&AuxRoom->size, sizeof(int));
	}
	file.close();
}