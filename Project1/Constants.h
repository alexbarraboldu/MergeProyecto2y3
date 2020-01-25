#pragma once
#include <vector>

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

typedef std::vector<std::vector<char>> charbivector;

const short MIN_MAIN_PATH = 5;
const short MAX_MAIN_PATH = 10;

const short MIN_RAMIFICATION_LENGTH = 2;
const short MAX_RAMIFICATION_LENGTH = 5;

const short MIN_RAMIFICATIONS = 0;
const short MAX__RAMIFICATIONS = 1;

const short NUM_CONNECTIONS = 4;
//int minSize = 20;
