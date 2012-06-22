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


int main(int argc, char** argv)
{
// 	DoTest();
// 	return 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);

	SetupRC();

	CInput input;
	input.InitListener();

	glutMainLoop();

	return 0;
}
