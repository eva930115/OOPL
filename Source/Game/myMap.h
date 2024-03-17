#pragma once

#ifndef MYMAP_H

#define MYMAP_H
#include "../Library/gameutil.h"

class Map{
public:
	int map1[29][40];
	game_framework::CMovingBitmap mapResource[29][40];

	void generateMap1();
	void showMap1();

};
#endif // !MYMAP_H