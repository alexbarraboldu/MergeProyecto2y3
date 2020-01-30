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
			file.read((char*)&AuxCharacter.playerhp, sizeof(int));
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
			file.write((char*)&AuxCharacter.playerhp, sizeof(int));
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
	VectorDungeon.clear();
	int VectorDungeonSize;
	file.read((char*)&VectorDungeonSize, sizeof(int));
	for (size_t c = 0; c < VectorDungeonSize; c++)
	{
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
		VectorDungeon.reserve(c);
		VectorDungeon.push_back(AuxRoomList);
	}
	file.close();
}

void saveGameState()
{
	std::fstream file;
	file.open("dungeon.thc", std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.fail()) return;
	int VectorDungeonSize = VectorDungeon.size();
	file.write((char*)&VectorDungeonSize, sizeof(int));
	for (size_t c = 0; c < VectorDungeonSize; c++)
	{
		std::vector<room*> AuxRoomList;
		int AuxRoomListSize = VectorDungeon[c].size();
		AuxRoomList.reserve(AuxRoomListSize);
		AuxRoomList = VectorDungeon[c];
		file.write((char*)&AuxRoomListSize, sizeof(int));
		for (size_t i = 0; i < AuxRoomListSize; i++)
		{
			std::vector<infoVectorRoom> ArrayIVR;
			ArrayIVR.reserve(4);
			room* AuxRoom = AuxRoomList[i];
			for (size_t i = 0; i < AuxRoomListSize; i++)
			{
				if (AuxRoom->north == AuxRoomList[i] && AuxRoom != AuxRoomList[i]) { ArrayIVR.push_back(infoVectorRoom('n', i)); continue;}
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
	}
	file.close();
}


struct magString
{
	std::string type;
	std::string content;
};

void loadTextDungeon()
{
	std::fstream file;
	file.open("dungeon.txt", std::ios::in);

	std::vector<std::array<magString, 10>> VectorPAAMS;
	std::vector<std::string> Estrings;
	std::string line;
	while (!file.eof())
	{
		std::array<magString, 10> PlayerArrayAuxMagString;
		std::getline(file, line);
		for (size_t i = 0; i < line.size(); i++)
		{
			std::string AuxString = line;
			int PuntoComa = AuxString.find(';');
			Estrings.push_back(AuxString.substr(0, PuntoComa + 1));
			line = line.substr(PuntoComa + 1);
		}
		std::vector<magString> who;
		for (size_t i = 0; i < Estrings.size(); i++)
		{
			std::string AuxString = Estrings[i];
			int PuntoPunto = AuxString.find(':');
			magString AuxMagString;
			AuxMagString.type = AuxString.substr(0, PuntoPunto + 1);
			AuxMagString.content = AuxString.substr(PuntoPunto + 1);
			who.push_back(AuxMagString);

			std::string PlayerAuxString;
			int PlayerPuntoPunto;
			std::string PlayerAuxString2;
			int PlayerPosPuntoPunto;
			int PlayerPosComa;
			std::string PlayerAuxString3;
			std::string PlayerAuxString4;
			int PlayerPunto;
			int PlayerPunto2;
			int PlayerPuntoPunto2;

			int DoorsComa;
			int PuntoPartida;
			std::string DoorsAuxString;
			std::string ActualDoor;

			if (who.at(i).type[0] == ' ')
			{
				who.at(i).type = who.at(i).type.substr(1);
			}
			char c = who.at(i).type[0];

			switch (c)
			{
			case 'i':
				PlayerArrayAuxMagString[0].type = who.at(i).type;
				PlayerArrayAuxMagString[0].content = who.at(i).content;
				break;
			case 'p':
				PlayerAuxString = who.at(i).content;
				PlayerPuntoPunto = PlayerAuxString.find(':');
				PlayerPunto = PlayerAuxString.find('.');

				PlayerAuxString2 = PlayerAuxString.substr(PlayerPuntoPunto + 1, PlayerPunto - PlayerAuxString.substr(0, PlayerPuntoPunto).size());
				PlayerPosPuntoPunto = PlayerAuxString2.find(':');
				PlayerArrayAuxMagString[1].type = PlayerAuxString2.substr(0, PlayerPosPuntoPunto);
				PlayerArrayAuxMagString[1].content = PlayerAuxString2.substr(PlayerPosPuntoPunto + 1, PlayerAuxString2.find(',') - 1);
				// Check to get only 1 char in the type string
				for (size_t pt1 = 0; pt1 < PlayerArrayAuxMagString[1].type.size(); pt1++)
				{
					if (PlayerArrayAuxMagString[1].type[pt1] == 'x' || PlayerArrayAuxMagString[1].type[pt1] == 'X')
					{
						PlayerArrayAuxMagString[1].type = PlayerArrayAuxMagString[1].type.substr(pt1);
					}
				}
				// Check first char to delete it
				for (size_t pc1 = 0; pc1 < PlayerArrayAuxMagString[1].content.size(); pc1++)
				{
					if (PlayerArrayAuxMagString[1].content[pc1] == ',' || PlayerArrayAuxMagString[1].content[pc1] == '.' || PlayerArrayAuxMagString[1].content[pc1] == ' ' || PlayerArrayAuxMagString[1].content[pc1] == ':' || PlayerArrayAuxMagString[1].content[pc1] == ';')
					{
						continue;
					}
					PlayerArrayAuxMagString[1].content.resize(PlayerArrayAuxMagString[1].content[pc1]);
					PlayerArrayAuxMagString[1].content = PlayerArrayAuxMagString[1].content[pc1];
				}
				/*----------------------------------------------------------------------------------------------------------*/
				PlayerPosComa = PlayerAuxString2.find(',');
				PlayerAuxString3 = PlayerAuxString2.substr(PlayerPosComa, PlayerAuxString2.find('.') - 1);
				PlayerPosComa = PlayerAuxString3.find(',');
				PlayerArrayAuxMagString[2].type = PlayerAuxString3.substr(PlayerPosComa, PlayerAuxString3.find(':'));
				PlayerArrayAuxMagString[2].content = PlayerAuxString3.substr(PlayerAuxString3.find(':'), PlayerAuxString3.find('.') - 1);
				// Check to get only 1 char in the type string
				for (size_t pt2 = 0; pt2 < PlayerArrayAuxMagString[2].type.size(); pt2++)
				{
					if (PlayerArrayAuxMagString[2].type[pt2] == 'y' || PlayerArrayAuxMagString[2].type[pt2] == 'Y')
					{
						PlayerArrayAuxMagString[2].type = PlayerArrayAuxMagString[2].type.substr(pt2);
					}
				}
				// Check first char to delete it
				for (size_t pc2 = 0; pc2 < PlayerArrayAuxMagString[2].content.size(); pc2++)
				{
					if (PlayerArrayAuxMagString[2].content[pc2] == ',' || PlayerArrayAuxMagString[2].content[pc2] == '.' || PlayerArrayAuxMagString[2].content[pc2] == ' ' || PlayerArrayAuxMagString[2].content[pc2] == ':' || PlayerArrayAuxMagString[2].content[pc2] == ';')
					{
						continue;
					}
					PlayerArrayAuxMagString[2].content.resize(PlayerArrayAuxMagString[2].content[pc2]);
					PlayerArrayAuxMagString[2].content = PlayerArrayAuxMagString[2].content[pc2];
				}
				/*----------------------------------------------------------------------------------------------------------*/
				PlayerAuxString4 = PlayerAuxString.substr(PlayerPuntoPunto + 1);
				PlayerPunto2 = PlayerAuxString4.find('.');
				PlayerAuxString4 = PlayerAuxString4.substr(PlayerPunto2 + 1);
				PlayerPuntoPunto2 = PlayerAuxString4.find(':');
				PlayerArrayAuxMagString[3].type = PlayerAuxString4.substr(0, PlayerPuntoPunto2);
				PlayerArrayAuxMagString[3].content = PlayerAuxString4.substr(PlayerPuntoPunto2 + 1);
				// Check to get only 1 char in the type string
				for (size_t pt3 = 0; pt3 < PlayerArrayAuxMagString[3].type.size(); pt3++)
				{
					if (PlayerArrayAuxMagString[3].type[pt3] == 's' || PlayerArrayAuxMagString[3].type[pt3] == 'S')
					{
						PlayerArrayAuxMagString[3].type = PlayerArrayAuxMagString[3].type[pt3];
					}
				}
				// Check first char to delete it
				for (size_t pc3 = 0; pc3 < PlayerArrayAuxMagString[3].content.size(); pc3++)
				{
					if (PlayerArrayAuxMagString[3].content[pc3] == ',' || PlayerArrayAuxMagString[3].content[pc3] == '.' || PlayerArrayAuxMagString[3].content[pc3] == ' ' || PlayerArrayAuxMagString[3].content[pc3] == ':' || PlayerArrayAuxMagString[3].content[pc3] == ';')
					{
						continue;
					}
					PlayerArrayAuxMagString[3].content.resize(PlayerArrayAuxMagString[3].content[pc3]);
					PlayerArrayAuxMagString[3].content = PlayerArrayAuxMagString[3].content[pc3];
				}
				break;
			case 's':
				PlayerArrayAuxMagString[4].type = who.at(i).type[who.at(i).type.find('e')];
				PlayerArrayAuxMagString[4].content = who.at(i).content;
				break;
			case 'd':
				DoorsComa = 0;
				PuntoPartida = 0;
				for (size_t e = 0; e < 4; e++)
				{
					DoorsAuxString = who.at(i).content;
					DoorsComa = DoorsAuxString.find(',', DoorsComa + 1);
					ActualDoor = DoorsAuxString.substr(PuntoPartida, DoorsComa - PuntoPartida);
					PuntoPartida = DoorsComa;
					PlayerArrayAuxMagString[5 + e].type = who.at(i).type + ActualDoor.substr(1, ActualDoor.find(':'));
					PlayerArrayAuxMagString[5 + e].content = ActualDoor.substr(ActualDoor.find(':') + 1);
					for (size_t pc5 = 0; pc5 < PlayerArrayAuxMagString[5 + e].content.size(); pc5++)
					{
						if (PlayerArrayAuxMagString[5 + e].content[pc5] == ',' || PlayerArrayAuxMagString[5 + e].content[pc5] == '.' || PlayerArrayAuxMagString[5 + e].content[pc5] == ' ' || PlayerArrayAuxMagString[5 + e].content[pc5] == ':' || PlayerArrayAuxMagString[5 + e].content[pc5] == ';')
						{
							continue;
						}
						PlayerArrayAuxMagString[5 + e].content.resize(PlayerArrayAuxMagString[5 + e].content[pc5]);
						PlayerArrayAuxMagString[5 + e].content = PlayerArrayAuxMagString[5 + e].content[pc5];
					}
				}
				break;
			case 'm':
				PlayerArrayAuxMagString[9].type = who.at(i).type;
				PlayerArrayAuxMagString[9].content = who.at(i).content;
				for (size_t pc9 = 0; pc9 < PlayerArrayAuxMagString[3].content.size(); pc9++)
				{
					if (PlayerArrayAuxMagString[9].content[pc9] == ',' || PlayerArrayAuxMagString[9].content[pc9] == '.' || PlayerArrayAuxMagString[9].content[pc9] == ' ' || PlayerArrayAuxMagString[9].content[pc9] == ':' || PlayerArrayAuxMagString[9].content[pc9] == ';')
					{
						continue;
					}
					PlayerArrayAuxMagString[9].content.resize(PlayerArrayAuxMagString[9].content[pc9]);
					PlayerArrayAuxMagString[9].content = PlayerArrayAuxMagString[9].content[pc9];
				}
				break;
			default:
				break;
			}
		}
		VectorPAAMS.push_back(PlayerArrayAuxMagString);
	}
	// INTRODUCIR INFORMACIÓN EN STRUCT AUXILIAR DEL PROGRAMA
	int VectorPAAMSSize = VectorPAAMS.size();
	std::vector<room*> AuxVectorRoom;
	AuxVectorRoom.resize(VectorPAAMSSize);
	for (size_t v = 0; v < VectorPAAMSSize; v++)
	{
		room* AuxRoom = new room;
		int PAAMSSize = VectorPAAMS.at(v).size();
		for (size_t p = 0; p < PAAMSSize; p++)
		{
			char lastLetter;
			char firstLetter = VectorPAAMS.at(v).at(p).type[0];
			switch (firstLetter)
			{
			case 'X':
			case 'x':
				AuxRoom->player.pos.X = stoi(VectorPAAMS.at(v).at(p).content);
				break;
			case 'Y':
			case 'y':
				AuxRoom->player.pos.Y = stoi(VectorPAAMS.at(v).at(p).content);
				break;
			case 'S':
			case 's':
				AuxRoom->player.skin = (char)VectorPAAMS.at(v).at(p).content[0];
				break;
			case 'E':
			case 'e':
				AuxRoom->startEnemyNum = stoi(VectorPAAMS.at(v).at(p).content);
				break;
			case 'M':
			case 'm':
				AuxRoom->size = stoi(VectorPAAMS.at(v).at(p).content);
			default:
				break;
			}
		}

		InitEnemyList(AuxRoom->enemyList, AuxRoom->startEnemyNum, AuxRoom->size);

		AuxRoom->map.resize(AuxRoom->size);
		for (size_t map = 0; map < AuxRoom->size; map++)
		{
			AuxRoom->map.at(map).resize(AuxRoom->size);
		}
		AuxVectorRoom.at(v) = AuxRoom;
	}
	for (size_t v = 0; v < VectorPAAMSSize; v++)
	{
		if (VectorPAAMS.at(v).at(5).type == "doors:N:" && !(VectorPAAMS.at(v).at(5).content == "" || VectorPAAMS.at(v).at(5).content == ";"))
		{
			int Room = stoi(VectorPAAMS.at(v).at(5).content);
			AuxVectorRoom[v]->north = AuxVectorRoom[Room];
		}
		else if (VectorPAAMS.at(v).at(6).type == "doors:S:" && !(VectorPAAMS.at(v).at(6).content == "" || VectorPAAMS.at(v).at(6).content == ";"))
		{
			int Room = stoi(VectorPAAMS.at(v).at(6).content);
			AuxVectorRoom[v]->south = AuxVectorRoom[Room];
		}
		else if (VectorPAAMS.at(v).at(7).type == "doors:W:" && !(VectorPAAMS.at(v).at(7).content == "" || VectorPAAMS.at(v).at(7).content == ";"))
		{
			int Room = stoi(VectorPAAMS.at(v).at(7).content);
			AuxVectorRoom[v]->west = AuxVectorRoom[Room];
		}
		else if (VectorPAAMS.at(v).at(8).type == "doors:E:" && !(VectorPAAMS.at(v).at(8).content == "" || VectorPAAMS.at(v).at(8).content == ";"))
		{
			int Room = stoi(VectorPAAMS.at(v).at(8).content);
			AuxVectorRoom[v]->east = AuxVectorRoom[Room];
		}
	}
	VectorDungeon.push_back(AuxVectorRoom);
	file.close();
}