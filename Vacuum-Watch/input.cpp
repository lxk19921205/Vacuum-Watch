#include <gl/freeglut.h>
#include "constants.h"
#include "input.h"
#include "factory.h"
#include "button.h"

#include <iostream>

using std::cout;
using std::endl;


CInput::CInput()
{
}

CInput::~CInput()
{
}


static void ListenMouseClick(int button, int state, int x, int y)
{
	static int down_x = -1;
	static int down_y = -1;

	if(button == GLUT_LEFT_BUTTON)
	{
		switch(state)
		{
		case GLUT_DOWN:
			{
				//������£���¼����
				down_x = x;
				down_y = y;
				break;
			}

		case GLUT_UP:
			{
				//������𣬶������꣬����ȣ����ʾclicked�����������µ�����
				if (down_x == x && down_y == y)
				{
					IController* controller = CFactory::getController();
					controller->OnLeftClicked(x, y);
					cout << "clicked" << x << ", " << y << endl;
				}
				down_x = -1;
				down_y = -1;
				break;
			}

		default:
			break;
		}
	}
}


static void ListenKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case VW_OPTION_DEF_FIRE_KEY:
		{
			//�յ���fire���źţ�����controller
			IController* controller = CFactory::getController();
			controller->OnFireKeyClicked();
			break;
		}

	default:
		break;
	}
}


static void ListenMouseMove(int x, int y)
{
	static int prev_x = 0;
	static int prev_y = 0;

	//����֮ǰ�ĵ�����ڵĵ㣬����controller������ȥ�����ʲô�仯
	IController* controller = CFactory::getController();
	controller->OnMouseMoved(prev_x, prev_y, x, y);

	prev_x = x;
	prev_y = y;
}


void CInput::InitListener()
{
	//��ViewEngine��Init֮���ٵ������Ӧ�������û����CreateWindow�����
	glutKeyboardFunc(ListenKeyboard);		//��������
	glutMouseFunc(ListenMouseClick);		//���������
	glutMotionFunc(ListenMouseMove);		//������갴��ʱ���ƶ�
	glutPassiveMotionFunc(ListenMouseMove);	//�������δ����ʱ���ƶ�
}
