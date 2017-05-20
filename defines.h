//defines.h is part of TetrixSTATIC
//Содержит основные определения макросов

#pragma once

//Размер доски
#define XSIZE				20
#define YSIZE				24

//Работа с игроками
#define FIRST_PLAYER		1
#define SECOND_PLAYER		2

//Команды для передачи по сети
#define MOVELEFT			1
#define MOVERIGHT			2
#define MOVEDOWN			3
#define ROTATE				4
#define FULLMOVEDOWN		5
#define QUIT				6
#define BOARD				7