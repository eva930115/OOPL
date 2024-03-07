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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{

}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({
		"Resources/home_page/background.bmp",
		"Resources/menu/background.bmp",
		"Resources/map/map1.bmp",
		"Resources/map/block1.bmp"
		});
	background.SetTopLeft(0, 0);

	button[0].LoadBitmapByString({ "Resources/home_page/button_play.bmp" });
	button[0].SetTopLeft(553, 530);
	button[1].LoadBitmapByString({ "Resources/home_page/button_setting.bmp" });
	button[1].SetTopLeft(100, 890);
	button[2].LoadBitmapByString({ "Resources/menu/button_back.bmp" });
	button[2].SetTopLeft(90, 800);

	window[0].LoadBitmapByString({ "Resources/window/setting/background.bmp" });
	window[0].SetTopLeft(80, 215);
	/*
	for (int i = 0; i < 4; i++) {
		window[i].SetTopLeft(182, 167);	//(0,0) ()
	}
	*/
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (nFlags == VK_LBUTTON) {
		IsMouseOverlap(point.x, point.y);
	}
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{		
	if (call_window) {
		show_window();
	}
	else {
		show_page();
	}
	ShowWindowCoordinate();
	
}

void CGameStateRun::show_page() {
	if (page_phase == 0) {	//home page
		background.SetFrameIndexOfBitmap(0);
		background.ShowBitmap();
		button[0].ShowBitmap();	//button_play
		button[1].ShowBitmap();	//button_setting
	}
	if (page_phase == 1) {	//menu
		background.SetFrameIndexOfBitmap(1);
		background.ShowBitmap();
		button[2].ShowBitmap();	//back
	}
	if (page_phase == 2) {	//map1
		// background.SetFrameIndexOfBitmap(2);
		background.ShowBitmap();
	}
}

void CGameStateRun::show_window() {
	if (window_phase == 0) {
		window[0].ShowBitmap();
		button[2].ShowBitmap();
	}
}

void CGameStateRun::ShowWindowCoordinate() {
	// 座標轉成字串
	string text;
	stringstream ss;
	// 宣告顯示文字工具
	CDC* pDC = CDDraw::GetBackCDC();
	// Window 底下的API
	POINT pt;							// 座標
	HWND hWnd = GetForegroundWindow();	// 宣告並取得當前視窗的句柄
	BOOL bReturn = GetCursorPos(&pt);	// 取得當前鼠標在Screen上的座標(若無return false)
	ScreenToClient(hWnd, &pt);			// 將取得Screen的座標轉成當前視窗句柄的座標
	if (bReturn != 0) {
		ss << pt.x << ", " << pt.y;
		text = ss.str();
		CTextDraw::Print(pDC, 5, 5, text);
	}
	CDDraw::ReleaseBackCDC();
}


void CGameStateRun::IsMouseOverlap(int mouse_x, int mouse_y) {
	// playButton
	if ((mouse_x >= button[0].GetLeft() && mouse_x <= button[0].GetLeft() + 300) && (mouse_y >= button[0].GetTop() && mouse_y <= button[0].GetTop() + 120) && page_phase == 0) {
		background.SetFrameIndexOfBitmap(2);
		page_phase = 2;
	}
	// settingButton
	if ((mouse_x >= button[1].GetLeft() && mouse_x <= button[1].GetLeft() + 110) && (mouse_y >= button[1].GetTop() && mouse_y <= button[1].GetTop() + 110) && page_phase == 0) {
		button[2].SetTopLeft(560, 700);
		call_window = true;
	}
	// backButton at Setting Menu
	if ((mouse_x >= button[2].GetLeft() && mouse_x <= button[2].GetLeft() + 340) && (mouse_y >= button[2].GetTop() && mouse_y <= button[2].GetTop() + 150) && call_window == true) {
		call_window = false;
		page_phase = 0;
	}
}