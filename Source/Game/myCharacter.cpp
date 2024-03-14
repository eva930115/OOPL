#include "StdAfx.h"
#include "../Game/myCharacter.h"


void Character::moveRight() {
	character.SetTopLeft(character.GetLeft() + 5, character.GetTop());
}
void Character::moveLeft(){
	character.SetTopLeft(character.GetLeft() - 5, character.GetTop());
}

void Character::moveRightJumpUp() {
	character.SetTopLeft(character.GetLeft() + 5, character.GetTop() - 14);
}

void Character::moveRightJumpDown() {
	character.SetTopLeft(character.GetLeft() + 5, character.GetTop() + 14);
}

void Character::moveLeftJumpUp() {
	character.SetTopLeft(character.GetLeft() - 5, character.GetTop() - 14);
}
void Character::moveLeftJumpDown() {
	character.SetTopLeft(character.GetLeft() - 5, character.GetTop() + 14);
}