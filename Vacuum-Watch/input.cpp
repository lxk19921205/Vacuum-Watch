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
		//TODO 收到了fire的信号，告诉controller！
		break;

	default:
		break;
	}
}


static void ListenMouseMove(int x, int y)
{
	static int prev_x = 0;
	static int prev_y = 0;

	//TODO 根据之前的点和现在的点，算出该做什么变化
//	cout << "from (" << prev_x << ", " << prev_y << ") to (" << x << ", " << y << ")" << endl;

	prev_x = x;
	prev_y = y;
}


void CInput::InitListener()
{
	glutKeyboardFunc(ListenKeyboard);		//监听键盘
	glutMotionFunc(ListenMouseMove);		//监听鼠标按下时的移动
	glutPassiveMotionFunc(ListenMouseMove);	//监听鼠标未按下时的移动
}
