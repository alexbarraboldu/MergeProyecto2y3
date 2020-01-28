#pragma once

#include "Structures.h"

extern bool menuLoop;
extern bool gameLoop;
extern 	int idUser;
extern int charIndex;


int aCharactersCount(std::array<Character, 5> _array);

void LoginMenu();

void LoginUser();

void RegisterUser();

void PlayerMenu(int& _countaUsers);

void AdminMenu(int& _countaUsers);

void Play();

void DeleteUserUser();

void DeleteUserAdmin();

void NewCharacter();

void ListCharcatersUser();

void ListCharactersAdmin();

void DeleteCharacterUser();

void DeleteCharacterAdmin();

void ListUsers();

int startGame();