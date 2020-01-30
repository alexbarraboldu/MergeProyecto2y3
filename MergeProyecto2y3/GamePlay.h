#pragma once
#include <vector>
#include <ctime>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_w 119
#define KEY_W 87
#define KEY_a 97
#define KEY_A 65
#define KEY_D 68
#define KEY_d 100
#define KEY_S 83
#define KEY_s 115
#define KEY_F5 63
#define KEY_ENTER 13

typedef std::vector<std::vector<char>> charbivector;

const short MIN_MAIN_PATH = 5;
const short MAX_MAIN_PATH = 10;

const short MIN_RAMIFICATION_LENGTH = 2;
const short MAX_RAMIFICATION_LENGTH = 5;

const short MIN_RAMIFICATIONS = 0;
const short MAX__RAMIFICATIONS = 1;

const short NUM_CONNECTIONS = 4;

extern bool frameRateLoop;

/*-------------------------------------------------------------------------------------*/

struct Position2D
{
	int X, Y;
};

struct Player
{
	char skin = 'O';
	Position2D pos;
};

struct Enemy
{
	char skin = 'X';
	Position2D pos;
};

struct room
{
	room* north = nullptr;
	room* south = nullptr;
	room* east = nullptr;
	room* west = nullptr;
	std::vector<Enemy> enemyList;
	Player player;
	charbivector map;
	int size;
	int startEnemyNum;
};

/*-------------------------------------------------------------------------------------*/

void Init(std::vector<room*>& _RoomList);

char AskDifficulty();

void InitRoomList(std::vector<room*>& _RoomList, room*& _firstRoom, room*& _lastRoom, char& _difficulty);

void GenerateNewConnection(std::vector<room*>& _RoomList, int _j);

void BasicInitRoom(room*& _room, char& _difficulty);

int SetDifficulty(room*& _room, char& _difficulty);

void InitEnemyList(std::vector<Enemy>& _enemyList, int _enemyNum, int _size);


void GameLoop();

double clockToMilliseconds(clock_t ticks);

void enemyIntoMap(room*& _room);

void drawMap(room*& _room);

void checkMapBalls(room*& _room, int& playerhp);

void enemyMovement(room*& _room);

room* checkDoors(room* _room);

void FrameRate(room*& _room, int& _playerhp, int _listRoomLength);


void Destroy(std::vector<room*>& _roomList, room*& _firstRoom, room*& _lastRoom);

void menuPause();

void loadGameState();

void saveGameState();

void drawDungeon(std::vector<room*>& _roomList);

extern std::vector<room*> roomList;

extern std::vector<std::vector<room*>> VectorDungeon;