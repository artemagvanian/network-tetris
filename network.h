#pragma once
#include <SFML/Network.hpp>

using namespace sf;

#define MOVELEFT			1
#define MOVERIGHT			2
#define MOVEDOWN			3
#define ROTATE				4
#define GENERATEDFIGURE		5
#define CANSTART			6
#define QUIT				7
#define CANGENERATE			8
#define FULLMOVEDOWN		9

void LogCommand(string logstring) {
	cout << "#" << logstring << endl;
}