#include <gl/glut.h>

#include "view_engine.h"
#include "constants.h"
#include "button.h"

extern Button pBtn;


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

GLfloat g_x1 = 0.0f;
GLfloat g_y1 = 0.0f;
GLfloat g_rsize = 25;

GLfloat g_xstep = 1.0f;
GLfloat g_ystep = 1.0f;

GLfloat g_window_width = 800;
GLfloat g_window_height = 600;

static void RenderScene()
{
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	//������ť
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_window_width, 0, g_window_height, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pBtn.Render();

/*	glTranslatef(0.0f, 0.0f, 10.0f);  

	glPushMatrix(); 
	glRotatef(g_x1,0.0f,0.0f,1.0f); // ��z����ת
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//��������Բ��
	gluDeleteQuadric(pObj); 
	glPopMatrix();  
*/

	//	glRectf(g_x1, g_y1, g_x1+g_rsize, g_y1+g_rsize);

	//ˢ�»�ͼ������н���
	glutSwapBuffers();
}

void CViewEngine::SetupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//�����ڸı��Сʱ��GLUT���������
static void ChangeSize(GLsizei width, GLsizei height)
{
	//��ֹ��0��
	if (height == 0)
	{
		height = 1;
	}

	g_window_width = width;
	g_window_height = height;

	//���ӿ�����Ϊ���ڵĴ�С
	glViewport(0, 0, width, height);

	//��������ϵͳ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//�����ü�����left, right, bottom, top, front, back��
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	if (width <= height)
	{
		glOrtho(-100.0, 100.0, -100.0/aspect_ratio, 100.0/aspect_ratio, 1.0, -1.0);
	}
	else
	{
		glOrtho(-100.0*aspect_ratio, 100.0*aspect_ratio, -100.0, 100.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void TimerFunction(int value)
{
	if (g_x1 > g_window_width-g_rsize || g_x1 < -g_window_width)
	{
	g_xstep = -g_xstep;
	}
	if (g_y1 > g_window_height || g_y1 < -g_window_height+g_rsize)
	{
	g_ystep = -g_ystep;
	}

	g_x1 += g_xstep;
	g_y1 += g_ystep;

	if (g_x1 > (g_window_width - g_rsize + g_xstep))
	{
	g_x1 = g_window_width - g_rsize - 1;
	}
	else if (g_x1 < -(g_window_width + g_xstep))
	{
	g_x1 = -g_window_width - 1;
	}

	if (g_y1 > (g_window_height + g_ystep))
	{
	g_y1 = g_window_height - 1;
	}
	else if (g_y1 < -(g_window_height - g_rsize + g_ystep))
	{
	g_y1 = -g_window_height + g_rsize - 1;
	}

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void CViewEngine::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow(VW_WINDOW_TITLE);
	pBtn.init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);

	this->SetupRC();
}
