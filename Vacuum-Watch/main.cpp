#include <iostream>
#include <gl/glut.h>

#include "constants.h"
#include "module_interfaces.h"
#include "factory.h"
#include "testing.h"
#include "input.h"

using std::cout;
using std::endl;


void RenderScene()
{
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT);
	//ˢ�»�ͼ����
	glFlush();
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void DoTest()
{
	CTesting test;

//	test.TestOptions();
//	test.TestLog();
//	test.TestGameData();
}

void ListenKeyboard(unsigned char key, int x, int y)
{
	CInput keyboard;

	switch (key)
	{
	case VW_OPTION_DEF_FIRE_KEY:
		keyboard.OnFireKeyClicked();
//		cout<<"Press space"<<endl;
		break;
	default:
		break;
	}
}

void ListenMouseMove(int x, int y)
{
//	cout<<x<<' '<<y<<endl;
}

int main(int argc, char** argv)
{
//	DoTest();
//	return 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);

	SetupRC();

//	glutKeyboardFunc(ListenKeyboard);//��������
//	glutMotionFunc(ListenMouseMove);//������갴��ʱ���ƶ�
//	glutPassiveMotionFunc(ListenMouseMove);//�������δ����ʱ���ƶ�

	glutMainLoop();

	return 0;
}
