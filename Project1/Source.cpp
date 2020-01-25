#include <iostream>

#include "Declarations.h"

std::vector<room*> roomList;
room* firstRoom = new room();
room* lastRoom = new room();

void Init(std::vector<room*>& _RoomList)
{
	char difficulty = AskDifficulty();
	InitRoomList(_RoomList, firstRoom, lastRoom, difficulty);
}

void GameLoop()
{
	int playerhp = 100;
	FrameRate(firstRoom, playerhp, roomList.size());
}

int main()
{
	Init(roomList);
	GameLoop();
	Destroy(roomList);
	return 0;
}