#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	Sleep(1000);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//

	
	CAudio* audio = CAudio::Instance();
	audio->Load(0, R"(Resources/audio/HomeMusic.wav)");		//Home
	audio->Load(1, R"(Resources/audio/MenuMusic.wav)");		//Menu
	audio->Load(2, R"(Resources/audio/MapMusic1.wav)");		//Map
	audio->Load(3, R"(Resources/audio/EndWindow.wav)");		//EndWindow
	audio->Load(4, R"(Resources/audio/PassWindow.wav)");	//PassWindow
	audio->Load(5, R"(Resources/audio/ButtonClick.wav)");
	audio->Load(6, R"(Resources/audio/Diamond.wav)");
	audio->Load(7, R"(Resources/audio/Door.wav)");
	audio->Play(0, true);
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CAudio* audio = CAudio::Instance();
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//CAudio* audio = CAudio::Instance();
	
}
