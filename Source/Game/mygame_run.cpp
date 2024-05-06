#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "sstream"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{

}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	if (this->page_phase == 6){
		fireman.IsMoving(this->map, this->mapPole);
		watergirl.IsMoving(this->map, this->mapPole);
		if (!fireman.IsUpButtonClick) 
			this->fireman.isDropDown(this->map, this->mapPole, this->mapBox, page_phase - 5);
		if (!watergirl.IsWButtonClick) 
			this->watergirl.isDropDown(this->map, this->mapPole, this->mapBox, page_phase - 5);
		this->runOverlap(this->page_phase - 5);
		
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	/*
	background[3]: home, menu, map
	window[4]: setting, paused, die, pass
	*/
	scene.loadScene();

	/*
	home: (0)play  (1)setting
	menu: (2)stage1, 2, 3, 4 (3)back
	map: (4)paused
	window-
	settig: (5)muic (6)effect (7)end
	paused: (8)end (9)resume (10)retry
	die: (11)menu (12)retry (13)skip
	pass: (14)continue
	*/
	button.loadButton();


	fireman.character.LoadBitmapByString({ "Resources/characters/fireman_front_1.bmp" }, RGB(0, 255, 0));
	fireman.character.SetTopLeft(38, 877);
	watergirl.character.LoadBitmapByString({ "Resources/characters/watergirl_front_1.bmp" }, RGB(0, 255, 0));
	watergirl.character.SetTopLeft(38, 737);

	map.generateMap();
	mapButton.generateObject();
	mapController.generateObject();
	mapPole.generateObject();
	mapBox.generateObject();
	mapDoor.generateObject();
	mapDiamond.generateObject();
	mapPool.generateObject();
	mapFan.generateObject();

	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	fireman.IsButtonDown(nChar);
	watergirl.IsButtonDown(nChar);

	//test for passWindow
	const int VK_P = 0x50;
	if (nChar == VK_P) {
		page_phase = 5;
		scene.showScene(page_phase);
	}
	//test for dieWindow
	const int VK_O = 0x4F;
	if (nChar == VK_O) {
		page_phase = 4;
		scene.showScene(page_phase);
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	fireman.IsButtonUp(nChar);
	watergirl.IsButtonUp(nChar);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	if (nFlags == VK_LBUTTON) {
		IsMouseOverlap(point.x, point.y);
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//const auto audio = CAudio::Instance();

	

}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{

}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	
	

	scene.showScene(page_phase);

	

	if (page_phase >= 6) {	//Map
		last_stage = page_phase;	//�����Ҧb���d �Ω󭫻s&�~��
		map.showMap(page_phase - 5);
		mapButton.showObject(page_phase - 5);
		mapController.showObject(page_phase - 5);
		mapPole.showObject(page_phase - 5);
		mapBox.showObject(page_phase - 5);
		mapDoor.showObject(page_phase - 5);
		mapDiamond.showObject(page_phase - 5);
		mapPool.showObject(page_phase - 5);
		mapFan.showObject(page_phase - 5);

		fireman.character.ShowBitmap();		//(38, 877)
		watergirl.character.ShowBitmap();	//(38, 737)
	}

	button.showButton(page_phase);
	ShowWindowCoordinate();


}


void CGameStateRun::ShowWindowCoordinate() {
	// �y���ন�r��
	string text;
	stringstream ss;
	// �ŧi��ܤ�r�u��
	CDC* pDC = CDDraw::GetBackCDC();
	// Window ���U��API
	POINT pt;							// �y��
	HWND hWnd = GetForegroundWindow();	// �ŧi�è��o��e�������y�`
	BOOL bReturn = GetCursorPos(&pt);	// ���o��e���ЦbScreen�W���y��(�Y�Lreturn false)
	ScreenToClient(hWnd, &pt);			// �N���oScreen���y���ন��e�����y�`���y��
	if (bReturn != 0) {
		ss << pt.x << ", " << pt.y;
		text = ss.str();
		CTextDraw::Print(pDC, 5, 5, text);
	}
	CDDraw::ReleaseBackCDC();
}



void CGameStateRun::IsMouseOverlap(int mouse_x, int mouse_y) {
	const auto audio = CAudio::Instance();
	bool buttonClick = false;
	
	//playButton at Home
	if (button.ifOverlap(0, CPoint(mouse_x, mouse_y)) && page_phase == 0) {
		page_phase = 6;
		if (musicPlay) {
			audio->Stop(0);
			audio->Stop(1);
			audio->Play(2, true);
		}
		buttonClick = true;
	}
	//settingButton at Home
	if (button.ifOverlap(1, CPoint(mouse_x, mouse_y)) && page_phase == 0) {
		page_phase = 2;
		if (musicPlay) {
			audio->Stop(0);
			audio->Stop(1);
			audio->Play(2, true);
		}
		buttonClick = true;
	}

	//stageButton at Menu
	for (int i = 2; i < 7; i++) {
		if (button.ifOverlap(i, CPoint(mouse_x, mouse_y)) && page_phase == 1) {
			page_phase = i + 4;
			if (musicPlay) {
				audio->Stop(0);
				audio->Stop(1);
				audio->Play(2, true);
			}
			buttonClick = true;
		}
	}
	//backButton at Menu
	if (button.ifOverlap(7, CPoint(mouse_x, mouse_y)) && page_phase == 1) {
		page_phase = 0;
		if (musicPlay) {
			audio->Stop(1);
			audio->Stop(2);
			audio->Play(0, true);
		}
		buttonClick = true;
	}
	//pausedButton at Map
	if (button.ifOverlap(8, CPoint(mouse_x, mouse_y)) && page_phase >= 6) {
		page_phase = 3;
		buttonClick = true;
	}

	if (button.ifOverlap(9, CPoint(mouse_x, mouse_y)) && page_phase == 2) {
		//music on/off
		buttonClick = true;
		if (musicPlay) {
			button.isClick(9);
			audio->Pause();
			musicPlay = false;
		}
		else {
			button.isClick(9);
			musicPlay = true;
		}
	}
	if (button.ifOverlap(10, CPoint(mouse_x, mouse_y)) && page_phase == 2) {
		//effect on/of
		buttonClick = true;
		if (effectPlay) {
			button.isClick(10);
			effectPlay = false;
		}
		else {
			button.isClick(10);
			effectPlay = true;
		}
	}
	//backButton at setting
	if (button.ifOverlap(11, CPoint(mouse_x, mouse_y)) && page_phase == 2) {
		page_phase = 0;
		if (musicPlay) {
			audio->Stop(1);
			audio->Stop(2);
			audio->Play(0, true);
		}
	
		buttonClick = true;
		
	}
	//at paused
	if (button.ifOverlap(12, CPoint(mouse_x, mouse_y)) && page_phase == 3) {
		//end
		page_phase = 1;
		if (musicPlay) {
			audio->Stop(0);
			audio->Stop(2);
			audio->Play(1, true);
		}
		buttonClick = true;
	}
	if (button.ifOverlap(13, CPoint(mouse_x, mouse_y)) && page_phase == 3) {
		//resume unwork
		this->page_phase = last_stage;
		buttonClick = true;
	}
	if (button.ifOverlap(14, CPoint(mouse_x, mouse_y)) && page_phase == 3) {
		//retry unwork
		buttonClick = true;
		this->resetLevel(last_stage - 5);
		this->page_phase = last_stage;
	}
	//at die
	if (button.ifOverlap(15, CPoint(mouse_x, mouse_y)) && page_phase == 4) {
		//menu
		page_phase = 1;
		if (musicPlay) {
			audio->Stop(0);
			audio->Stop(2);
			audio->Play(1, true);
		}
		this->resetLevel(last_stage - 5);
		buttonClick = true;
	}
	if (button.ifOverlap(16, CPoint(mouse_x, mouse_y)) && page_phase == 4) {
		//retry unwork
		buttonClick = true;
		this->resetLevel(last_stage - 5);
		this->page_phase = last_stage;
	}
	if (button.ifOverlap(17, CPoint(mouse_x, mouse_y)) && page_phase == 4) {
		//skip
		page_phase = 1;
		buttonClick = true;
	}
	//continueButton at pass
	if (button.ifOverlap(18, CPoint(mouse_x, mouse_y)) && page_phase == 5) {
		page_phase = 1;
		if (musicPlay) {
			audio->Stop(0);
			audio->Stop(2);
			audio->Play(1, true);
		}
		buttonClick = true;
	}


	//Music & Effec
	if (buttonClick && effectPlay) {
		audio->Play(5, false);
		buttonClick = false;
	}


	
}

// reset level's everything when clicks the button of retry
void CGameStateRun::resetLevel(int page) {
	this->fireman.resetMap(page);
	this->watergirl.resetMap(page);
	this->mapBox.resetMap(page);
	this->mapButton.resetMap(page);
	this->mapController.resetMap(page);
	this->mapDiamond.resetMap(page);
	this->mapDoor.resetMap(page);
	this->mapPole.resetMap(page);
}

void CGameStateRun::isControllerOverlap(int page, CMovingBitmap& character) {
	if (page == 1) {
		// overlap from right side (opening controller)
		if (CMovingBitmap::IsOverlap(character, this->mapController.mapController[0])
			&& character.GetLeft() < this->mapController.mapController[0].GetLeft()){
			this->mapController.mapController[0].SetFrameIndexOfBitmap(1);
			this->mapController.controllerState[0] = true;
			this->controllerMode = 1;
		}
		// overlap from left side (closing controller)
		else if (CMovingBitmap::IsOverlap(character, this->mapController.mapController[0])
			&& character.GetLeft() + 20 > this->mapController.mapController[0].GetLeft() + 38){
			this->mapController.mapController[0].SetFrameIndexOfBitmap(0);
			this->mapController.controllerState[0] = true;
			this->controllerMode = 2;
		}

		if (this->mapController.controllerState[0]) {
			this->movingPole(1, 0);
		}

	}
	
}

void CGameStateRun::movingPole(int page, int index) {
	int current_Height = this->mapPole.mapPole[index].GetTop();
	
	if (current_Height < 635 && this->controllerMode == 1) {
		this->mapPole.mapPole[index].SetTopLeft(this->mapPole.mapPole[index].GetLeft(), current_Height + 10);
	}
	else if (current_Height > 525 && this->controllerMode == 2) {
		this->mapPole.mapPole[index].SetTopLeft(this->mapPole.mapPole[index].GetLeft(), current_Height - 10);
	}
	else { 
		this->mapController.controllerState[0] = false; 
		this->controllerMode = 0;
	}

	if (CMovingBitmap::IsOverlap(this->fireman.character, this->mapPole.mapPole[index]))
		this->fireman.character.SetTopLeft(this->fireman.character.GetLeft(), this->mapPole.mapPole[index].GetTop() - 100);
	if (CMovingBitmap::IsOverlap(this->watergirl.character, this->mapPole.mapPole[index]))
		this->watergirl.character.SetTopLeft(this->watergirl.character.GetLeft(), this->mapPole.mapPole[index].GetTop() - 100);
}

void CGameStateRun::isButtonOverlap(int page, CMovingBitmap& character) {
	if (page == 1) {
		// Button Up
		if (CMovingBitmap::IsOverlap(character, this->mapButton.mapButton[0])) {
			this->mapButton.mapButton[0].SetFrameIndexOfBitmap(1);
			this->mapButton.buttonState[0] = true;
			this->buttonMode[0] = 1;
		}
		else if (CMovingBitmap::IsOverlap(character, this->mapButton.mapButton[1])) {
			this->mapButton.mapButton[1].SetFrameIndexOfBitmap(1);
			this->mapButton.buttonState[1] = true;
			this->buttonMode[1] = 1;
		}
		else {
			this->mapButton.mapButton[0].SetFrameIndexOfBitmap(0);
			this->mapButton.buttonState[0] = false;
			this->buttonMode[0] = 2;
			this->mapButton.mapButton[1].SetFrameIndexOfBitmap(0);
			this->mapButton.buttonState[1] = false;
			this->buttonMode[1] = 2;
		}
		this->movingPolefromButton(1, this->mapPole.mapPole[1]);
	}
}

void CGameStateRun::movingPolefromButton(int page, CMovingBitmap &pole) {
	int current_Height = pole.GetTop();

	if (current_Height < 525 && (this->buttonMode[0] == 1 || this->buttonMode[1] == 1)) {
		pole.SetTopLeft(pole.GetLeft(), current_Height + 10);
	}
	else if (current_Height > 425 && (this->buttonMode[0] == 2 || this->buttonMode[1] == 2)) {
		pole.SetTopLeft(pole.GetLeft(), current_Height - 10);
	}
	else {
		this->buttonMode[0] = 0;
		this->buttonMode[1] = 0;
	}
	if (CMovingBitmap::IsOverlap(this->fireman.character, pole))
		this->fireman.character.SetTopLeft(this->fireman.character.GetLeft(), pole.GetTop() - 100);
	if (CMovingBitmap::IsOverlap(this->watergirl.character, pole))
		this->watergirl.character.SetTopLeft(this->watergirl.character.GetLeft(), pole.GetTop() - 100);
}

void CGameStateRun::isPoolOverlap(int page, CMovingBitmap& character, CMovingBitmap& pool) {
	if (page == 1) {
		if (CMovingBitmap::IsOverlap(character, pool)) 
			this->page_phase = 4;
	}
}

void CGameStateRun::isDoorOverlap(int page) {
	// Red Door
	if (CMovingBitmap::IsOverlap(this->fireman.character, this->mapDoor.mapDoor[0])) {
		this->mapDoor.mapDoor[0].SetFrameIndexOfBitmap(1);
		this->mapDoor.doorState[0] = true;
	}
	else {
		this->mapDoor.mapDoor[0].SetFrameIndexOfBitmap(0);
		this->mapDoor.doorState[0] = false;
	}
	// Blue Door
	if (CMovingBitmap::IsOverlap(this->watergirl.character, this->mapDoor.mapDoor[1])) {
		this->mapDoor.mapDoor[1].SetFrameIndexOfBitmap(1);
		this->mapDoor.doorState[1] = true;
	}
	else {
		this->mapDoor.mapDoor[1].SetFrameIndexOfBitmap(0);
		this->mapDoor.doorState[1] = false;
	}
	// Is Game Clear
	if (this->mapDoor.doorState[0] && this->mapDoor.doorState[1]) {
		this->page_phase = 5;
	}

}

void CGameStateRun::isBoxOverlap(int page, CMovingBitmap& character) {
	// pushing Box from right side
	if (CMovingBitmap::IsOverlap(character, this->mapBox.mapBox)
		&& character.GetLeft() > this->mapBox.mapBox.GetLeft() + 25) {
		this->mapBox.push = true;
		this->mapBox.movingBox(1);
	}
	// pusing Box from left side
	else if (CMovingBitmap::IsOverlap(character, this->mapBox.mapBox)
		&& character.GetLeft() < this->mapBox.mapBox.GetLeft() - 25){
		this->mapBox.push = true;
		this->mapBox.movingBox(2);
	}
	if (this->mapBox.push)
		this->mapBox.dropDown(this->map);
}

void CGameStateRun::isDiamondOverlap(int page) {
	if (page == 1) {
		// red
		for (int i = 0; i < 3; i++) {
			if (CMovingBitmap::IsOverlap(this->fireman.character, this->mapDiamond.redDiamond[i]))
				this->mapDiamond.redState[i] = false;
		}

		for (int i = 0; i < 4; i++) {
			if (CMovingBitmap::IsOverlap(this->watergirl.character, this->mapDiamond.blueDiamond[i]))
				this->mapDiamond.blueState[i] = false;
		}
	}
}

void CGameStateRun::runOverlap(int page) {
	if (page == 1){
		this->isControllerOverlap(this->page_phase - 5, this->fireman.character);
		this->isControllerOverlap(this->page_phase - 5, this->watergirl.character);
		//this->isButtonOverlap(this->page_phase - 5, this->fireman.character);
		this->isButtonOverlap(this->page_phase - 5, this->watergirl.character);
		this->isDoorOverlap(this->page_phase - 5);
		this->isDiamondOverlap(this->page_phase - 5);
		this->isBoxOverlap(this->page_phase - 5, this->fireman.character);
		this->isBoxOverlap(this->page_phase - 5, this->watergirl.character);
		this->isPoolOverlap(this->page_phase - 5, this->fireman.character, this->mapPool.greenPool);
		this->isPoolOverlap(this->page_phase - 5, this->fireman.character, this->mapPool.bluePool[0]);
		this->isPoolOverlap(this->page_phase - 5, this->watergirl.character, this->mapPool.redPool[0]);
		this->isPoolOverlap(this->page_phase - 5, this->watergirl.character, this->mapPool.greenPool);
		
	}
}