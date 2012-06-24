#include <gl/glut.h>
#include "constants.h"
#include "input.h"
#include "factory.h"
#include "button.h"

Button pBtn;

CInput::CInput()
{
}

CInput::~CInput()
{
}

static void ListenMouseClick(int button, int state, int x, int y)
{

	if(button==GLUT_LEFT_BUTTON)
		switch(state)
	{
		case GLUT_DOWN:
			//������£�
//			printf("Left Button ");
			if( pBtn.OnMouseDown(x, y) );
				break;

		case GLUT_UP:
			pBtn.OnMouseUp();
			break;
	}
	glutPostRedisplay();
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
