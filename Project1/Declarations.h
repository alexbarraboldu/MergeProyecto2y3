#pragma once
#include <ctime>
#include "Structures.h"

void Init(std::vector<room*>& _RoomList);

char AskDifficulty();

void InitRoomList(std::vector<room*>& _RoomList, room*& _firstRoom, room*& _lastRoom, char &_difficulty);

void GenerateNewConnection(std::vector<room*>& _RoomList, int _j);

void BasicInitRoom(room*& _room, char &_difficulty);

int SetDifficulty(room*& _room, char &_difficulty);

void InitEnemyList(std::vector<Enemy> &_enemyList, int _enemyNum, int _size);


void GameLoop();

double clockToMilliseconds(clock_t ticks);

void enemyIntoMap(room*& _room);

void drawMap(room*& _room);

void checkMapBalls(room*& _room, int &playerhp);

void enemyMovement(room*& _room);

room* checkDoors(room* _room);

void FrameRate(room*& _room, int &_playerhp, int _listRoomLength);


void Destroy(std::vector<room*>& _roomList);
