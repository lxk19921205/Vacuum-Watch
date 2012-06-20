#include <iostream>
#include <gl/glut.h>

#include "constants.h"
#include "module_interfaces.h"
#include "factory.h"

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


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();

	ILog* log = CFactory::getLog();
	log->GetFileName();

	return 0;
}