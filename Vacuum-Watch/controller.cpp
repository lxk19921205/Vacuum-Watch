/************************************************************************/
/* �ܿ�������ʵ�֣�by Andriy                                            */
/************************************************************************/

#include <stdio.h>	//only for the definition of NULL
#include <string.h>
#include <gl/freeglut.h>
#include <math.h>
#include "controller.h"
#include "constants.h"
#include "game_data.h"
#include "view_engine.h"
#include "factory.h"
#include "input.h"

#include <iostream>
using std::cout;
using std::endl;

extern GLfloat g_window_height;
extern GLfloat g_window_width;

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
	cout << "FIRE (spacebar) clicked" << endl;
}

void CController::OnMouseMoved( int from_x, int from_y, int to_x, int to_y )
{
	switch (m_state)
	{
	case VW_STATE_MENU:
	case VW_STATE_SETTING:
	case VW_STATE_ABOUT:
	case VW_STATE_PAUSED:
		break;

	case VW_STATE_ONGOING:
		{
			//�ƶ�X
			if (to_x < 1.0/5.0 * g_window_width)
			{
				//����Ļ�����1/5��������������
				this->MovePlaneX(-2 * VW_DATA_DEF_MOVE_SPEED);
			}
			if (to_x < 2.0/5.0 * g_window_width)
			{
				//����Ļ������м䴦��һ��������
				this->MovePlaneX(-VW_DATA_DEF_MOVE_SPEED);
			}
			else if (to_x < 3.0/5.0 * g_window_width)
			{
				//����Ļ���м䣬���ö�
			}
			else if (to_x < 4.0/5.0 * g_window_width)
			{
				//����Ļ���ұ��м䴦��һ��������
				this->MovePlaneX(VW_DATA_DEF_MOVE_SPEED);
			}
			else
			{
				//����Ļ���ұ�1/5��������������
				this->MovePlaneX(2 * VW_DATA_DEF_MOVE_SPEED);
			}

			//�ƶ�Y
			if (to_y < 1.0/5.0 * g_window_height)
			{
				//����Ļ���ϱ�1/5��������������
				this->MovePlaneY(2 * VW_DATA_DEF_MOVE_SPEED);
			}
			else if (to_y < 2.0/5.0 * g_window_height)
			{
				//����Ļ���ϱ��м䴦��һ��������
				this->MovePlaneY(VW_DATA_DEF_MOVE_SPEED);
			}
			else if (to_y < 3.0/5.0 * g_window_height)
			{
				//����Ļ���м䣬���ö�
			}
			else if (to_y < 4.0/5.0 * g_window_height)
			{
				//����Ļ���±��м䴦��һ��������
				this->MovePlaneY(-VW_DATA_DEF_MOVE_SPEED);
			}
			else
			{
				//����Ļ���±�1/5��������������
				this->MovePlaneY(-2 * VW_DATA_DEF_MOVE_SPEED);
			}

			break;
		}

	default:
		break;
	}
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

void CController::Init(int* pargc, char** argv)
{
	//ע���Ⱥ�˳����ViewEngine��
	m_pViewEngine->Init(pargc, argv);
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
			this->AdjustSpeed();
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
	m_pViewEngine->SetupRCOngoing();
	this->m_state = VW_STATE_ONGOING;

	ILog* log = CFactory::getLog();
	log->Info("GAME START");
}

void CController::OnSettingButton()
{
	m_pViewEngine->SetupRCSetting();
	this->m_state = VW_STATE_SETTING;

	ILog* log = CFactory::getLog();
	log->Info("ENTER SETTINGS");
}

void CController::OnAboutButton()
{
	m_pViewEngine->SetupRCAbout();
	this->m_state = VW_STATE_ABOUT;

	ILog* log = CFactory::getLog();
	log->Info("READ ABOUT");
}

void CController::OnQuitButton()
{
	cout << "QUIT clicked" << endl;

	ILog* log = CFactory::getLog();
	log->Info("QUIT GAME");

	exit(0);
}

void CController::OnLeftPushed()
{
	this->MovePlaneX(-VW_DATA_DEF_MOVE_SPEED);
}

void CController::OnRightPushed()
{
	this->MovePlaneX(VW_DATA_DEF_MOVE_SPEED);
}

void CController::OnUpPushed()
{
	this->MovePlaneY(VW_DATA_DEF_MOVE_SPEED);
}

void CController::OnDownPushed()
{
	this->MovePlaneY(-VW_DATA_DEF_MOVE_SPEED);
}

void CController::AdjustSpeed()
{
	if (m_pGameData->GetCurrentLength() < 500)
	{
		m_pGameData->SetStep(1);
	}
	else if (m_pGameData->GetCurrentLength() < 2000)
	{
		m_pGameData->SetStep(2);
	}
	else if (m_pGameData->GetCurrentLength() < 4000)
	{
		m_pGameData->SetStep(4);
	}
	else if (m_pGameData->GetCurrentLength() < VW_DATA_DEF_TUNNEL_LENGTH)
	{
		m_pGameData->SetStep(8);
	}
	else
	{
		m_pGameData->SetStep(0);
		//TOO LONG should stop

	}
}

//�±ߵĴ������̫���ˣ����ʺ�������ƶ���ô������
void CController::Unproject( int window_x, int window_y, GLdouble* pworld_x, GLdouble* pworld_y, GLdouble* pworld_z)
{
	GLdouble model_view[16];
	GLdouble projection[16];
	GLint viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble x = window_x;
	GLdouble y = (GLdouble)viewport[3] - (GLdouble)window_y;
	GLfloat window_z;
	glReadPixels(window_x, window_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &window_z);

	gluUnProject(window_x, window_y, window_z, model_view, projection, viewport, pworld_x, pworld_y, pworld_z);
}

bool CController::MovePlaneX( int offset )
{
	GLfloat current_x = m_pGameData->GetPositionX();
	m_pGameData->SetPositionX(current_x + offset);
	if (!m_pGameData->IsPlaneInside())
	{
		m_pGameData->SetPositionX(current_x);
		return false;
	}
	return true;
}

bool CController::MovePlaneY( int offset )
{
	GLfloat current_y = m_pGameData->GetPositionY();
	m_pGameData->SetPositionY(current_y + offset);
	if (!m_pGameData->IsPlaneInside())
	{
		m_pGameData->SetPositionY(current_y);
		return false;
	}
	return true;
}
