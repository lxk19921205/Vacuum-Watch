/************************************************************************/
/* 总控制器的实现，by Andriy                                            */
/************************************************************************/

#include <stdio.h>	//only for the definition of NULL
#include <string.h>
#include <gl/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

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

	srand(time(NULL));
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
			//移动X：最左 -2*DEF_SPEED, 最右 2*DEF_SPEED
			int speed = (int) (((double)to_x / g_window_width - 0.5) * 2 * VW_DEF_MOVE_SPEED);
			this->MovePlaneX(speed);

			//移动Y：最上 2*DEF_SPEED，最下 -2*DEF_SPEED
			speed = (int) (((double)to_y / g_window_height - 0.5) * (-2) * VW_DEF_MOVE_SPEED);
			this->MovePlaneY(speed);

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
	//Input模块会自动把信息发送到Controller的单例来，因此这样就好了
	CInput input;
	input.InitListener();
}

void CController::Init(int* pargc, char** argv)
{
	//注意先后顺序，先ViewEngine！
	m_pViewEngine->Init(pargc, argv);
	this->InitKeyboardMouseListening();
}

void CController::OnLeftClicked( int pos_x, int pos_y )
{
	m_pViewEngine->OnLeftClicked(pos_x, pos_y);
}

//返回true表示需要重绘
bool CController::OnTimerClick()
{
	// 该更新数据了，只更新就够了，不用调用重绘，其他地方会调的
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
				//还可以继续走
				int current_length = m_pGameData->GetCurrentLength();
				if (current_length % VW_DEF_WALL_DISTANCE == 0 && current_length != 0)
				{
					cout << "CHECK WALL NOW" << endl;
					//又碰到一个了!
					this->PopNextWallType();
					// TODO 判断有没有撞到
				}

				return true;
			}
			else
			{
				//到头了，不能再走了
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
	log->Info("ENTER GAME_START");
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
	log->Info("ENTER ABOUT");
}

void CController::OnQuitButton()
{
	ILog* log = CFactory::getLog();
	log->Info("QUIT GAME");

	exit(0);
}

void CController::OnLeftPushed()
{
	this->MovePlaneX(-VW_DEF_MOVE_SPEED);
}

void CController::OnRightPushed()
{
	this->MovePlaneX(VW_DEF_MOVE_SPEED);
}

void CController::OnUpPushed()
{
	this->MovePlaneY(VW_DEF_MOVE_SPEED);
}

void CController::OnDownPushed()
{
	this->MovePlaneY(-VW_DEF_MOVE_SPEED);
}

void CController::AdjustSpeed()
{
	if (m_pGameData->GetCurrentLength() < 500)
	{
		m_pGameData->SetStep(VW_DEF_VELOCITY_ONE);
	}
	else if (m_pGameData->GetCurrentLength() < 2000)
	{
		m_pGameData->SetStep(VW_DEF_VELOCITY_TWO);
	}
	else if (m_pGameData->GetCurrentLength() < 4000)
	{
		m_pGameData->SetStep(VW_DEF_VELOCITY_THREE);
	}
	else if (m_pGameData->GetCurrentLength() < VW_DEF_TUNNEL_LENGTH)
	{
		m_pGameData->SetStep(VW_DEF_VELOCITY_FOUR);
	}
	else
	{
		m_pGameData->SetStep(0);
		//TOO LONG should stop
	}
}

// @deprecated 下边的代码原本用来在鼠标移动的时候找到视图移动的方向，但代价太高了！
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

int CController::NextWallType()
{
	if (m_NextWallTypes.empty())
	{
		//随机生成几个，就3个吧，然后重调一次吧
		for (int i=0; i<3; i++)
		{
//			m_NextWallTypes.push_back(rand() % VW_WALL_COUNT);
			//m_NextWallTypes.push_back(VW_WALL_ONE);	//为了测试，全部生成第一种类型
			m_NextWallTypes.push_back(VW_WALL_TWO);	//为了测试，全部生成第二种类型
			//m_NextWallTypes.push_back(VW_WALL_THREE);	//为了测试，全部生成第三种类型
		}
		return this->NextWallType();
	}
	else
	{
		if (m_pGameData->GetCurrentLength() >= m_pGameData->GetTotalLength())
		{
			//如果跑完了，就给个NONE
			return VW_WALL_NONE;
		}
		else
		{
			//不然，给个front()
			return m_NextWallTypes.front();
		}
	}
}

void CController::PopNextWallType()
{
	if (!m_NextWallTypes.empty())
	{
		m_NextWallTypes.pop_front();
	}
}
