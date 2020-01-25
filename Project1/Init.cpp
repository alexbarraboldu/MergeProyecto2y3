#include <iostream>

#include "Declarations.h"

char AskDifficulty()
{
	setlocale(LC_ALL, "");
	//FASE 1
	char difficulty;
	bool temporal = true;
	std::cout << "¿Vas a jugar en modo fácil o difícil? (f/m/d)\n Respuesta: ";
	while (temporal)
	{
		std::cin >> difficulty;
		if (difficulty != 'f' && difficulty != 'F' && difficulty != 'd' && difficulty != 'D' && difficulty != 'm' && difficulty != 'M')
		{
			system("CLS");
			std::cout << "Por favor, introduzca una respuesta válida (f/m/d)\n Respuesta: ";
		}
		else
		{
			temporal = false;
		}
	}
	return difficulty;
}

void InitRoomList(std::vector<room*>& _RoomList, room*& _firstRoom, room*& _lastRoom, char &_difficulty)
{
	int numRooms = rand() % MAX_MAIN_PATH;
	if (numRooms < MIN_MAIN_PATH) numRooms = MIN_MAIN_PATH;
	_RoomList.resize(numRooms);

	for (size_t i = 0; i < numRooms; i++)
	{
		_RoomList[i] = new room();
		BasicInitRoom(_RoomList[i],_difficulty);
	}
	for (size_t j = 0; j < numRooms; j++)
	{
		GenerateNewConnection(_RoomList, j);
	}
	_firstRoom = _RoomList[0];
	_lastRoom = _RoomList[numRooms - 1];
}

void GenerateNewConnection(std::vector<room*>& _RoomList, int j)
{
	if (j == _RoomList.size() - 1)_RoomList[j]->north = nullptr;
	else _RoomList[j]->north = _RoomList[j+1];

	if (j == 0)	_RoomList[j]->south = nullptr;
	else _RoomList[j]->south = _RoomList[j-1];
}

void BasicInitRoom(room*& _room, char &_difficulty)
{
	//_room = new room();
	SetDifficulty(_room, _difficulty);

	InitEnemyList(_room->enemyList, _room->startEnemyNum, _room->size);

	_room->map.resize(_room->size);
	for (size_t i = 0; i < _room->size; i++)
	{
		_room->map[i].resize(_room->size);
		for (size_t j = 0; j < _room->size; j++)
		{
				_room->map[i][j] = ' ';
		}
	}
	_room->player.pos.X = _room->size / 2;
	_room->player.pos.Y = _room->size / 2;
}

int SetDifficulty(room*& _room, char &_difficulty)
{
	_room = new room();
	srand(time(NULL));
	_room->size = rand() % 10 + 20;

	switch (_difficulty)
	{
	case 'f':
	case 'F':
		_room->startEnemyNum = rand() % 3 + 1;
		break;
	case 'm':
	case 'M':
		_room->startEnemyNum = rand() % 6 + 3;
		break;
	case 'd':
	case 'D':
		_room->startEnemyNum = rand() % 8 + 6;
		break;
	default:
		break;
	}
	return _room->startEnemyNum;
}

void InitEnemyList(std::vector<Enemy> &_enemyList, int _enemyNum, int _size)
{
	Enemy p;
	_enemyList.reserve(_enemyNum);
	for (int i = 0; i < _enemyNum; i++)
	{
		p.pos.X = rand() % (_size - 2) + 1;

		p.pos.Y = rand() % (_size - 2) + 1;

		_enemyList.push_back(p);
	}
	for (int i = 0; i < _enemyNum; i++)
	{
		Enemy Aux1 = _enemyList.at(i);
		for (int j = i + 1; j < _enemyNum; j++)
		{
			Enemy Aux2 = _enemyList.at(j);
			if (Aux1.pos.X == Aux2.pos.X && Aux1.pos.Y == Aux2.pos.Y)
			{
				Aux1.pos.X = rand() % (_size - 2) + 1;
				Aux1.pos.Y = rand() % (_size - 2) + 1;
			}
		}
	}
};