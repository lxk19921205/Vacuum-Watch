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
				//左键按下，记录坐标
				down_x = x;
				down_y = y;
				break;
			}

		case GLUT_UP:
			{
				//左键弹起，对照坐标，若相等，则表示clicked，最后清楚按下的坐标
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
			//收到了fire的信号，告诉controller
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

	//根据之前的点和现在的点，告诉controller，让它去算该做什么变化
	IController* controller = CFactory::getController();
	controller->OnMouseMoved(prev_x, prev_y, x, y);

	prev_x = x;
	prev_y = y;
}


void CInput::InitListener()
{
	//在ViewEngine的Init之后再调用这里，应该是如果没有先CreateWindow，会崩
	glutKeyboardFunc(ListenKeyboard);		//监听键盘
	glutMouseFunc(ListenMouseClick);		//监听鼠标点击
	glutMotionFunc(ListenMouseMove);		//监听鼠标按下时的移动
	glutPassiveMotionFunc(ListenMouseMove);	//监听鼠标未按下时的移动
}
