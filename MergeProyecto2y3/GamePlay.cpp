#include <iostream>
#include <thread>
#include <array>
#include <conio.h>

#include "GamePlay.h"
#include "Structures.h"

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

void InitRoomList(std::vector<room*>& _RoomList, room*& _firstRoom, room*& _lastRoom, char& _difficulty)
{
	int numRooms = rand() % MAX_MAIN_PATH;
	if (numRooms < MIN_MAIN_PATH) numRooms = MIN_MAIN_PATH;
	_RoomList.resize(numRooms);

	for (size_t i = 0; i < numRooms; i++)
	{
		_RoomList[i] = new room();
		BasicInitRoom(_RoomList[i], _difficulty);
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
	else _RoomList[j]->north = _RoomList[j + 1];

	if (j == 0)	_RoomList[j]->south = nullptr;
	else _RoomList[j]->south = _RoomList[j - 1];
}

void BasicInitRoom(room*& _room, char& _difficulty)
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

int SetDifficulty(room*& _room, char& _difficulty)
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

void InitEnemyList(std::vector<Enemy>& _enemyList, int _enemyNum, int _size)
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


/*-----------------------------------------------------------------------------------------------------*/


double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}
//...

void enemyIntoMap(room*& _room)
{
	Enemy aux;
	short length = _room->enemyList.size();
	for (size_t i = 0; i < length; i++)
	{
		aux = _room->enemyList.at(i);
		_room->map[aux.pos.X][aux.pos.Y] = aux.skin;
	}
}

void drawMap(room*& _room)
{
	short int roomSize = _room->size;
	system("cls");
	std::cout << "\n";
	for (size_t i = 0; i < roomSize; i++)
	{
		for (size_t j = 0; j < roomSize; j++)
		{
			if (i == 0 && j + 1 == _room->size)
			{
				//	ultima casilla del tejado
				std::cout << "º\n";
			}
			//	TECHO
			else if ((i == 0 && j != roomSize / 2) && _room->east != nullptr)
			{
				//	PUERTA TECHO Y TECHO
				std::cout << 'º';
			}
			else if ((i == 0) && _room->east == nullptr)
			{
				//	TECHO
				std::cout << 'º';
			}
			// SUELO
			else if ((i == roomSize - 1 && j != roomSize / 2) && _room->west != nullptr)
			{
				//	PUERTA SUELO Y SUELO
				std::cout << 'º';
			}
			else if ((i == roomSize - 1) && _room->west == nullptr)
			{
				//	SUELO
				std::cout << 'º';
			}
			//	IZQUIERDA
			else if ((j == 0 && i != roomSize / 2) && _room->north != nullptr)
			{
				//	PARED Y PUERTA IZQUIERDA
				std::cout << '|';
			}
			else if ((j == 0) && _room->north == nullptr)
			{
				//	PARED IZQUIERDA
				std::cout << '|';
			}
			// DERECHA
			else if ((j == roomSize - 1 && i != roomSize / 2) && _room->south != nullptr)
			{
				//	PARED Y PUERTA DERECHA
				std::cout << "|";
			}
			else if ((j == roomSize - 1) && _room->south == nullptr)
			{
				//	PARED DERECHA
				std::cout << "|";
			}
			else
			{
				//	MAPA
				std::cout << _room->map[i][j];
			}
		}
		if (i == roomSize / 2)
		{
			//	PUERTA DERECHA
			std::cout << ' ' << "\n";
		}
		else if (i != roomSize / 2 && i != 0)
		{
			if (i + 1 == roomSize)
			{
				std::cout << "\n";
			}
			else
			{
				//	PARED FALSA DERECHA
				std::cout << " \n";
			}
			//	SIN PARED DERECHA
			//std::cout << "\n";
		}
	}
}

void checkMapBalls(room*& _room, int& playerhp)
{
	Enemy bAux;
	for (size_t i = 0; i < _room->enemyList.size(); i++)
	{
		bAux = _room->enemyList.at(i);
		if (_room->map[_room->player.pos.X][_room->player.pos.Y] != bAux.skin && (_room->player.pos.X == bAux.pos.X && _room->player.pos.Y == bAux.pos.Y))
		{
			_room->enemyList.erase(_room->enemyList.begin() + i);
			playerhp--;
			return;
		}
	}
}

void enemyMovement(room*& _room)
{
	Enemy aux;
	for (size_t i = 0; i < _room->enemyList.size(); i++)
	{

		aux = _room->enemyList.at(i);
		int x = aux.pos.X;
		int y = aux.pos.Y;
		if (_room->player.pos.X > aux.pos.X and _room->player.pos.Y > aux.pos.Y)
		{
			_room->map[x][y] = ' ';
			aux.pos.X++;
			aux.pos.Y++;
		}
		else if (_room->player.pos.X < aux.pos.X and _room->player.pos.Y < aux.pos.Y)
		{
			_room->map[x][y] = ' ';
			aux.pos.X--;
			aux.pos.Y--;
		}
		else if (_room->player.pos.Y > aux.pos.Y and _room->player.pos.X < aux.pos.X)
		{
			_room->map[x][y] = ' ';
			aux.pos.Y++;
			aux.pos.X--;
		}
		else if (_room->player.pos.Y < aux.pos.Y and _room->player.pos.X > aux.pos.X)
		{
			_room->map[x][y] = ' ';

			aux.pos.Y--;
			aux.pos.X++;
		}
		else if (_room->player.pos.Y == aux.pos.Y and _room->player.pos.X < aux.pos.X)
		{
			_room->map[x][y] = ' ';
			aux.pos.X--;
		}
		else if (_room->player.pos.Y == aux.pos.Y and _room->player.pos.X > aux.pos.X)
		{
			_room->map[x][y] = ' ';
			aux.pos.X++;
		}
		else if (_room->player.pos.Y < aux.pos.Y and _room->player.pos.X == aux.pos.X)
		{
			_room->map[x][y] = ' ';
			aux.pos.Y--;
		}
		else if (_room->player.pos.Y > aux.pos.Y and _room->player.pos.X == aux.pos.X)
		{
			_room->map[x][y] = ' ';
			aux.pos.Y++;
		}
		else { return; }
		_room->map[aux.pos.X][aux.pos.Y] = aux.skin;
		_room->enemyList.at(i) = aux;
	}
	return;
}

room* checkDoors(room* _room)
{
	room* AuxRoom = new room();
	//	COMPRUEBA LA PUERTA IZQUIERDA
	if (_room->player.pos.X == _room->size / 2 && _room->player.pos.Y == _room->size - _room->size)
	{
		std::cout << "\nPuerta izquierda\n";
		AuxRoom = _room->north;
		AuxRoom->player.pos.X = _room->size / 2;
		AuxRoom->player.pos.Y = _room->size - 2;
		return AuxRoom;
	}
	//	COMPRUEBA LA PUERTA DERECHA
	else if (_room->player.pos.X == _room->size / 2 && _room->player.pos.Y == _room->size - 1)
	{
		std::cout << "Puerta derecha";
		AuxRoom = _room->south;
		AuxRoom->player.pos.X = _room->size / 2;
		AuxRoom->player.pos.Y = _room->size - _room->size + 1;
		return AuxRoom;
	}
	//	COMPRUEBA LA PUERTA INFERIOR
	else if (_room->player.pos.X == _room->size - 1 && _room->player.pos.Y == _room->size / 2)
	{
		std::cout << "Puerta inferior";
		AuxRoom = _room->west;
		AuxRoom->player.pos.X = _room->size - _room->size + 1;
		AuxRoom->player.pos.Y = _room->size / 2;
		return AuxRoom;
	}
	//	COMPRUEBA LA PUERTA SUPERIOR
	else if (_room->player.pos.X == _room->size - _room->size && _room->player.pos.Y == _room->size / 2)
	{
		std::cout << "Puerta superior";
		AuxRoom = _room->east;
		AuxRoom->player.pos.X = _room->size - 2;
		AuxRoom->player.pos.Y = _room->size / 2;
		return AuxRoom;
	}
	else {
		AuxRoom = _room;
		return AuxRoom;
	}
	delete AuxRoom;
}

#include <fstream>
#include <sstream>

void menuPause()
{
	bool menuLoop = true;
	while (true)
	{
		int c;
		std::cout << "Menu de pausa: \n\n";
		std::cout << "1. Continuar.\n";
		std::cout << "2. Guardar partida.\n";
		std::cout << "3. Salir del juego.\n\n";
		std::cin >> c;
		switch (c)
		{
		case 1:
			menuLoop = false;
			return;
		case 2:
			int i;
			bool checked;
			for (i = 0; i < VectorDungeon.size(); i++)
			{
				if (roomList == VectorDungeon[i])
				{ 
					VectorDungeon[i] = roomList;
					checked = false;
					break;
				}
			}
			if (checked) {
				VectorDungeon.reserve(VectorDungeon.size() + 1);
				VectorDungeon.insert(VectorDungeon.begin() + i, roomList);
				VectorDungeon.shrink_to_fit();
			}
			saveGameState();
			break;
		case 3:
			frameRateLoop = false;
			menuLoop = false;
			return;
		}
	}
}

void drawDungeon(std::vector<room*>& _roomList) {
	size_t RoomListSize = _roomList.size();
	for (size_t r = 0; r < RoomListSize; r++)
	{
		room* auxroom = _roomList[r];
		size_t EnemyListSize = auxroom->enemyList.size();
		std::vector<Enemy> auxEnemyList = auxroom->enemyList;
		Enemy auxEnemy;
		short int mapSize = auxroom->size;
		std::cout << "\n";
		for (size_t e = 0; e < auxroom->enemyList.size(); e++)
		{
			auxroom->map.at(auxroom->enemyList.at(e).pos.X).at(auxroom->enemyList.at(e).pos.Y) = auxroom->enemyList.at(e).skin;
		}
		for (size_t i = 0; i < mapSize; i++)
		{
			for (size_t j = 0; j < mapSize; j++)
			{
				if (i == 0 && j + 1 == mapSize)
				{
					//	ultima casilla del tejado
					std::cout << "º\n";
				}
				//	TECHO
				else if ((i == 0 && j != mapSize / 2) && auxroom->east != nullptr)
				{
					//	PUERTA TECHO Y TECHO
					std::cout << 'º';
				}
				else if ((i == 0) && auxroom->east == nullptr)
				{
					//	TECHO
					std::cout << 'º';
				}
				// SUELO
				else if ((i == mapSize - 1 && j != mapSize / 2) && auxroom->west != nullptr)
				{
					//	PUERTA SUELO Y SUELO
					std::cout << 'º';
				}
				else if ((i == mapSize - 1) && auxroom->west == NULL)
				{
					//	SUELO
					std::cout << 'º';
				}
				//	IZQUIERDA
				else if ((j == 0 && i != mapSize / 2) && auxroom->north != nullptr)
				{
					//	PARED Y PUERTA IZQUIERDA
					std::cout << '|';
				}
				else if ((j == 0) && auxroom->north == nullptr)
				{
					//	PARED IZQUIERDA
					std::cout << '|';
				}
				// DERECHA
				else if ((j == mapSize - 1 && i != mapSize / 2) && auxroom->south != nullptr)
				{
					//	PARED Y PUERTA DERECHA
					std::cout << "|";
				}
				else if ((j == mapSize - 1) && auxroom->south == nullptr)
				{
					//	PARED DERECHA
					std::cout << "|";
				}
				else if (auxEnemy.pos.X != i && auxEnemy.pos.Y != j)
				{
					//	MAPA
					std::cout << auxroom->map[i][j];
				}

			}
			if (i == mapSize / 2)
			{
				//	PUERTA DERECHA
				std::cout << ' ' << "\n";
			}
			else if (i != mapSize / 2 && i != 0)
			{
				if (i + 1 == mapSize)
				{
					std::cout << "\n";
				}
				else
				{
					//	PARED FALSA DERECHA
					std::cout << " \n";
				}
				//	SIN PARED DERECHA
				//std::cout << "\n";
			}
		}
	}
}

bool frameRateLoop;

void FrameRate(room*& _room, int& _playerhp, int _listRoomLength)
{
	int inputCount = 0;

	room* nextRoom = new room();
	clock_t timer = 0;
	clock_t time = 0;
	clock_t deltaTime;
	unsigned int frames = 0;
	double frameRate = 120;
	frameRateLoop = true;
	while (frameRateLoop) {

		std::chrono::high_resolution_clock::time_point beginFrame = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int c = 0;
		enemyIntoMap(_room);
		if (_kbhit()) {
			switch ((c = _getch())) {

			case KEY_UP:
			case KEY_W:
			case KEY_w:
				inputCount++;
				if (_room->player.pos.X > _room->size - _room->size + 1)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.X--;
				}
				else if ((_room->player.pos.Y == _room->size / 2 && _room->player.pos.X == _room->size - _room->size + 1) && _room->east != nullptr)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.X--;
				}
				std::cout << std::endl << "Up" << std::endl; //key up
				if (inputCount >= 2)
				{
					enemyMovement(_room);
					inputCount = 0;
				}
				break;

			case KEY_DOWN:
			case KEY_S:
			case KEY_s:
				inputCount++;
				if (_room->player.pos.X < _room->size - 2)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.X++;
				}
				else if ((_room->player.pos.Y == _room->size / 2 && _room->player.pos.X < _room->size - 1) && _room->west != nullptr)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.X++;
				}
				std::cout << std::endl << "Down" << std::endl; // key down
				if (inputCount >= 2)
				{
					enemyMovement(_room);
					inputCount = 0;
				}
				break;

			case KEY_LEFT:
			case KEY_A:
			case KEY_a:
				inputCount++;
				if (_room->player.pos.Y > _room->size - _room->size + 1)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.Y--;
				}
				else if ((_room->player.pos.Y > _room->size - _room->size && _room->player.pos.X == _room->size / 2) && _room->north != nullptr)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.Y--;
				}
				std::cout << std::endl << "Left" << std::endl; // key left
				if (inputCount >= 2)
				{
					enemyMovement(_room);
					inputCount = 0;
				}
				break;

			case KEY_RIGHT:
			case KEY_D:
			case KEY_d:
				inputCount++;
				if (_room->player.pos.Y < _room->size - 2)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.Y++;
				}
				else if ((_room->player.pos.Y < _room->size - 1 && _room->player.pos.X == _room->size / 2) && _room->south != nullptr)
				{
					_room->map[_room->player.pos.X][_room->player.pos.Y] = ' ';
					_room->player.pos.Y++;
				}
				std::cout << std::endl << "Right" << std::endl; // key right
				if (inputCount >= 2)
				{
					enemyMovement(_room);
					inputCount = 0;
				}
				break;

			case KEY_ENTER:
				menuPause();
				break;
			default:

				std::cout << std::endl << c << "null" << std::endl; // not arrow

				break;
			}
		}
		_room->map[_room->player.pos.X][_room->player.pos.Y] = 'O';

		system("cls");
		checkMapBalls(_room, _playerhp);
		nextRoom = checkDoors(_room);
		if (nextRoom == _room->north || nextRoom == _room->east || nextRoom == _room->south || nextRoom == _room->west)
		{
			_room = nextRoom;
			drawMap(_room);
		}
		else drawMap(_room);

		std::chrono::high_resolution_clock::time_point endFrame = std::chrono::high_resolution_clock::now();

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - beginFrame).count();
		timer += deltaTime;
		time += deltaTime;
		frames++;

		//
		// SOME INFORMATION FOR TRUBLESHOOTING
		//
		std::cout << "\nDelta Time: " << deltaTime / 1000.0f;
		std::cout << "\nTiempo: " << time / 1000.0f;
		std::cout << "\nX: " << _room->player.pos.X << " Y: " << _room->player.pos.Y;
		std::cout << "\nRoom Size: " << _room->size;
		std::cout << "\nEnemy List Length: " << _room->enemyList.size();
		std::cout << "\nRoom List Length: " << _listRoomLength;
		std::cout << "\nPuerta WEST: " << _room->west << " | Puerta EAST: " << _room->east << "\nPuerta NORTH: " << _room->north << " | Puerta SOUTH: " << _room->south;
		std::cout << "\nVidas: " << _playerhp << std::endl;

		if (_playerhp <= 0)
		{
			system("cls");
			std::cout << "HAS PERDIDO TODAS LAS VIDAS QUE TENIAS!\n";
			system("pause");
			return;
		}

		//if you really want FPS
		if (timer >= 1000.0) { //every second
			//std::cout << "Frames:" << frames << std::endl;
			timer = 0.0f;
			frames = 60;
		}
		/*FrameRate Limit*/
		else if (frames >= frameRate)
		{
			//std::cout << "Wait" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000.0f - timer)));
			time += 1000.0f - timer;
			frames = 0;
			timer = 0.0f;
		}
	}
};


/*-----------------------------------------------------------------------------------------------------*/

void Destroy(std::vector<room*>& _roomList, room* &_firstRoom, room* &_lastRoom)
{
	//int length = _roomList.size();

	//for (size_t i = 0; i < length; i++)
	//{
	//	delete(_roomList[i]);
	//}
	//delete(_firstRoom);
	//delete(_lastRoom);
	_roomList.clear();
}


/*-----------------------------------------------------------------------------------------------------*/


std::vector<std::vector<room*>> VectorDungeon;
std::vector<room*> roomList;
room* firstRoom = new room();
room* lastRoom = new room();

void Init(std::vector<room*>& _RoomList)
{
	char difficulty = AskDifficulty();
	InitRoomList(_RoomList, firstRoom, lastRoom, difficulty);
}

void GameLoop(int& _playerhp)
{
	
	FrameRate(firstRoom, _playerhp, roomList.size());
}

int startGameProcedural(int& _playerhp)
{
	Init(roomList);
	bool menuloop = true;
	while (menuloop)
	{
		int R;
		system("cls");
		drawDungeon(roomList);
		std::cout << "1. Guardar.\n";
		std::cout << "2. No guardar.\n\n";
		std::cin >> R;
		std::string dungeonName;
		switch (R)
		{
		case 1:
			void saveTextDungeon(std::string& _dungeonName);
			std::cout << "\nIntroduce un nombre para el archivo:\n";
			std::cin >> dungeonName;
			saveTextDungeon(dungeonName);
			menuloop = false;
			GameLoop(_playerhp);			
			break;
		case 2:
			return 1;
			break;
		default:
			break;
		}
		
	}
	Destroy(roomList, firstRoom, lastRoom);
	return 0;
}

int startGameFichero(int& _playerhp)
{
	firstRoom = roomList[0];
	lastRoom = roomList[roomList.size() - 1];
	drawDungeon(roomList);
	system("pause");
	GameLoop(_playerhp);
	Destroy(roomList, firstRoom, lastRoom);
	return 0;
}