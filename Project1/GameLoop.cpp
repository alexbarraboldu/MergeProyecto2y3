#include <ctime>
#include <iostream>
#include <thread>
#include <array>
#include <conio.h>

#include "Declarations.h"

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
			if (i == 0 && j + 1 == _room->size )
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
			else if ((i == roomSize - 1) && _room->west == NULL)
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

void checkMapBalls(room*& _room, int &playerhp)
{
	Enemy bAux;
	for (size_t i = 0; i < _room->enemyList.size(); i++)
	{
		bAux = _room->enemyList.at(i);
		if (_room->map[_room->player.pos.X][_room->player.pos.Y] != bAux.skin && (_room->player.pos.X == bAux.pos.X && _room->player.pos.Y == bAux.pos.Y))
		{
			_room->enemyList.erase(_room->enemyList.begin()+i);
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
		else { return;}
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

void FrameRate(room*& _room, int &_playerhp, int _listRoomLength)
{
	int inputCount = 0;

	room* nextRoom = new room();
	clock_t timer = 0;
	clock_t time = 0;
	clock_t deltaTime;
	unsigned int frames = 0;
	double frameRate = 120;

	while (true) {

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
				else if ((_room->player.pos.Y < _room->size - 1&& _room->player.pos.X == _room->size / 2) && _room->south != nullptr)
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
		/*std::cout << "\nDelta Time: " << deltaTime / 1000.0f;
		std::cout << "\nTiempo: " << time / 1000.0f;
		std::cout << "\nX: " << _room->player.pos.X << " Y: " << _room->player.pos.Y;
		std::cout << "\nRoom Size: " << _room->size;
		std::cout << "\nEnemy List Length: " << _room->enemyList.size();
		std::cout << "\nRoom List Length: " << _listRoomLength;
		std::cout << "\nPuerta WEST: " << _room->west << " | Puerta EAST: " << _room->east << "\nPuerta NORTH: " << _room->north << " | Puerta SOUTH: " << _room->south;
		std::cout << "\nVidas: " << _playerhp << std::endl;*/

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
}