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
		//TODO �յ���fire���źţ�����controller��
		break;

	default:
		break;
	}
}


static void ListenMouseMove(int x, int y)
{
	static int prev_x = 0;
	static int prev_y = 0;

	//TODO ����֮ǰ�ĵ�����ڵĵ㣬�������ʲô�仯
//	cout << "from (" << prev_x << ", " << prev_y << ") to (" << x << ", " << y << ")" << endl;

	prev_x = x;
	prev_y = y;
}


void CInput::InitListener()
{
	glutKeyboardFunc(ListenKeyboard);		//��������
	glutMotionFunc(ListenMouseMove);		//������갴��ʱ���ƶ�
	glutPassiveMotionFunc(ListenMouseMove);	//�������δ����ʱ���ƶ�
}
