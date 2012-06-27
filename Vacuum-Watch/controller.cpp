/************************************************************************/
/* �ܿ�������ʵ�֣�by Andriy                                            */
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
	//Inputģ����Զ�����Ϣ���͵�Controller�ĵ���������������ͺ���
	CInput input;
	input.InitListener();
}

void CController::Init()
{
	//ע���Ⱥ�˳����ViewEngine��
	m_pViewEngine->Init();
	this->InitKeyboardMouseListening();
}

void CController::OnLeftClicked( int pos_x, int pos_y )
{
	m_pViewEngine->OnLeftClicked(pos_x, pos_y);
}

//����true��ʾ��Ҫ�ػ�
bool CController::OnTimerClick()
{
	//TODO �ø��������ˣ�ֻ���¾͹��ˣ����õ����ػ棬�����ط������
	switch (m_state)
	{
	case VW_STATE_MENU:
		{
			return true;
		}
	case VW_STATE_SETTING:
		{
			return true;
		}
	case VW_STATE_ABOUT:
		{
			return true;
		}
	case VW_STATE_ONGOING:
		{
			if (m_pGameData->Step())
			{
				//�����Լ�����
				//�ж���û��ײ��
				return true;
			}
			else
			{
				//��ͷ�ˣ�����������
				return false;
			}
		}
	case VW_STATE_PAUSED:
		{
			return false;
		}

	default:
		return false;
	}
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

	this->m_state = VW_STATE_ONGOING;
}

void CController::OnSettingButton()
{
	//TODO setting
	cout << "setting" << endl;

	this->m_state = VW_STATE_SETTING;
}

void CController::OnAboutButton()
{
	//TODO about
	cout << "about" << endl;

	this->m_state = VW_STATE_ABOUT;
}

void CController::OnQuitButton()
{
	cout << "QUIT clicked" << endl;
	exit(0);
}
