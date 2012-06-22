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
	//用当前清除颜色清除窗口
	glClear(GL_COLOR_BUFFER_BIT);
	//刷新绘图命令
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

//	glutKeyboardFunc(ListenKeyboard);//监听键盘
//	glutMotionFunc(ListenMouseMove);//监听鼠标按下时的移动
//	glutPassiveMotionFunc(ListenMouseMove);//监听鼠标未按下时的移动

	glutMainLoop();

	return 0;
}
