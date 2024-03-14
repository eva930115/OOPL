#pragma once

#ifndef myCharacter_h
#define myCharacter_h
#include "../Library/gameutil.h"

class Character {
public:
	game_framework::CMovingBitmap character;
	int jumpHeight = 0;
	bool IsRightButtonClick = false;
	bool IsLeftButtonClick = false;
	bool IsUpButtonClick = false;

	void moveRight();
	void moveLeft();
	void moveRightJumpUp();
	void moveRightJumpDown();
	void moveLeftJumpUp();
	void moveLeftJumpDown();
};

#endif // !"myCharacter.h"
