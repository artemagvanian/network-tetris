//stdinclude.h is part of TetrixSTATIC
//Содержит в себе заголовки основных подключаемых файлов

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <array>
#include <thread>
#include "defines.h"

static bool dropThread = false;

sf::Font font;

sf::Texture LightBlue_t, Blue_t, Orange_t, Yellow_t, Green_t, Magenta_t, Red_t;

sf::Texture gamebg_t, scorebg_t, mboxbg_t, menubg_t;

sf::Image icon;