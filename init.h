//init.h is part of TetrixSTATIC
//Загружает все ресурсы в оперативную память компьютера

#pragma once
#include "stdinclude.h"
#include "mbox.h"

bool init() {
	if (!font.loadFromFile("redist/fonts/Arista.ttf")) {
		return false;
	}
	if (!LightBlue_t.loadFromFile("redist/blocks/LightBlue.png")) {
		return false;
	}
	if (!Blue_t.loadFromFile("redist/blocks/Blue.png")) {
		return false;
	}
	if (!Orange_t.loadFromFile("redist/blocks/Orange.png")) {
		return false;
	}
	if (!Yellow_t.loadFromFile("redist/blocks/Yellow.png")) {
		return false;
	}
	if (!Green_t.loadFromFile("redist/blocks/Green.png")) {
		return false;
	}
	if (!Magenta_t.loadFromFile("redist/blocks/Magenta.png")) {
		return false;
	}
	if (!Red_t.loadFromFile("redist/blocks/Red.png")) {
		return false;
	}

	if (!icon.loadFromFile("redist/blocks/Blue.png")) {
		return false;
	}

	if (!scorebg_t.loadFromFile("redist/backgrounds/scoreboardbg.png")) {
		return false;
	}
	if (!gamebg_t.loadFromFile("redist/backgrounds/gamebg.png")) {
		return false;
	}
	if (!mboxbg_t.loadFromFile("redist/backgrounds/messageboxbg.png")) {
		return false;
	}
	if (!menubg_t.loadFromFile("redist/backgrounds/menubg.png")) {
		return false;
	}
	return true;
}