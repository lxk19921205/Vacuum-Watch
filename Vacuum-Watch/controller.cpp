/************************************************************************/
/* 总控制器的实现，by Andriy                                            */
/************************************************************************/

#include <stdio.h>	//only for the definition of NULL
#include "controller.h"
#include "game_data.h"
#include "view_engine.h"


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
