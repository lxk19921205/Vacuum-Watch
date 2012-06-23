#include <gl/glut.h>
#include "constants.h"
#include "input.h"
#include "factory.h"


CInput::CInput()
{
}

CInput::~CInput()
{
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
	glutMotionFunc(ListenMouseMove);		//监听鼠标按下时的移动
	glutPassiveMotionFunc(ListenMouseMove);	//监听鼠标未按下时的移动
}
