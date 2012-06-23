/************************************************************************/
/* 总控制器的实现，by Andriy                                            */
/************************************************************************/

#include <stdio.h>	//only for the definition of NULL
#include <string.h>
#include "controller.h"
#include "game_data.h"
#include "view_engine.h"
#include "factory.h"
#include "input.h"


CController::CController()
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
	log->Info(buffer);
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

void CController::InitViewEngine()
{
	m_pViewEngine->Init();
}
