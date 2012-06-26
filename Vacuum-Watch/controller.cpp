/************************************************************************/
/* 总控制器的实现，by Andriy                                            */
/************************************************************************/

#include <stdio.h>	//only for the definition of NULL
#include <string.h>
#include "controller.h"
#include "constants.h"
#include "game_data.h"
#include "view_engine.h"
#include "factory.h"
#include "input.h"

#include <iostream>
using std::cout;
using std::endl;

CController::CController()
	:m_state(VW_STATE_MENU)
{
	m_pGameData = new CGameData();
	m_pViewEngine = new CViewEngine();
};

CController::~CController()
{
	if (m_pGameData != NULL)
	{
		delete m_pGameData;
	}
	if (m_pViewEngine != NULL)
	{
		delete m_pViewEngine;
	}
}

void CController::OnFireKeyClicked()
{
	//TODO
	ILog* log = CFactory::getLog();
	log->Info("FIRE_KEY CLICKED, handled by CController");
}

void CController::OnMouseMoved( int from_x, int from_y, int to_x, int to_y )
{
	//TODO
	static char buffer[100];
	memset(buffer, 0, 100*sizeof(char));
	sprintf_s(buffer, "Mouse moved from (%d, %d) to (%d, %d), handled by CController", from_x, from_y, to_x, to_y);

	ILog* log = CFactory::getLog();
//	log->Info(buffer);
}

void CController::StartGame()
{
	m_pViewEngine->StartDisplaying();
	//TODO
}

void CController::InitKeyboardMouseListening()
{
	//Input模块会自动把信息发送到Controller的单例来，因此这样就好了
	CInput input;
	input.InitListener();
}

void CController::Init()
{
	//注意先后顺序，先ViewEngine！
	m_pViewEngine->Init();
	this->InitKeyboardMouseListening();
}

void CController::OnLeftClicked( int pos_x, int pos_y )
{
	m_pViewEngine->OnLeftClicked(pos_x, pos_y);
}

void CController::OnTimerClick()
{
	//TODO 该更新数据了

	//更新之后，调用viewengine里让刷新重绘
	m_pViewEngine->Redraw();
}

IGameData* CController::GetGameData()
{
	return this->m_pGameData;
}

int CController::GetState()
{
	return this->m_state;
}

void CController::OnStartButton()
{
	//TODO start
	cout << "start" << endl;
}

void CController::OnSettingButton()
{
	//TODO setting
	cout << "setting" << endl;
}

void CController::OnAboutButton()
{
	//TODO about
	cout << "about" << endl;
}

void CController::OnQuitButton()
{
	//TODO quit
	cout << "quit" << endl;
}
