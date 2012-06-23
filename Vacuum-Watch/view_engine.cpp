#include <gl/glut.h>

#include "view_engine.h"
#include "constants.h"


CViewEngine::CViewEngine()
{
}

CViewEngine::~CViewEngine()
{
}

void CViewEngine::StartDisplaying()
{
	glutMainLoop();
	//TODO
}

static void RenderScene()
{
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT);
	//ˢ�»�ͼ����
	glFlush();
}

void CViewEngine::SetupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}


void CViewEngine::Init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);
	this->SetupRC();
}
