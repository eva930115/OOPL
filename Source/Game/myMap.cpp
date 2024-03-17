#include "stdafx.h"
#include "../Game/myMap.h"
#include <fstream>

void Map::generateMap1() {
	std::ifstream map("Resources/mapContent/map1Basic.txt");

	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			map >> this->map1[i][j];
			if (this->map1[i][j] == 0)
				this->mapResource[i][j].LoadBitmapByString({ "Resources/block/block_0.bmp" });
			else
				this->mapResource[i][j].LoadBitmapByString({ "Resources/block/block_1.bmp" });
			this->mapResource[i][j].SetTopLeft(j * 35, i * 35);
		}
	}
	
	map.close();
}

void Map::showMap1() {
	for (int i = 0; i < 29; i++) {
		for (int j = 0; j < 40; j++) {
			this->mapResource[i][j].ShowBitmap();
		}
	}
}