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



GLfloat g_x1 = 0.0f;
GLfloat g_y1 = 0.0f;
GLfloat g_rsize = 25;

GLfloat g_xstep = 1.0f;
GLfloat g_ystep = 1.0f;

GLfloat g_window_width = 800;
GLfloat g_window_height = 600;



static void RenderScene()
{
	//用当前清除颜色清除窗口
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 10.0f);  

	glPushMatrix(); 
	glRotatef(g_x1,0.0f,0.0f,1.0f); // 绕z轴旋转
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//创建空心圆柱
	gluDeleteQuadric(pObj); 
	glPopMatrix();  

	//	glRectf(g_x1, g_y1, g_x1+g_rsize, g_y1+g_rsize);

	//用三角形检验旋转
/*	//glLoadIdentity(); // 重置模型观察矩阵
	//glTranslatef(-1.5f,0.0f,-6.0f); // 左移 1.5 单位，并移入屏幕 6.0
	glPushMatrix();
	glRotatef( g_x1, 0.0f, 0.0f,1.0f);
	glBegin(GL_TRIANGLES); // 绘制三角形
	glColor3f(1.0f,0.0f,0.0f); //设置当前色为红色
	glVertex3f( 0.0f, 10.0f, 0.0f); // 上顶点
	glColor3f(0.0f,1.0f,0.0f);//设置当前色为绿色
	glVertex3f(-10.0f,-10.0f, 0.0f); // 左下
	glColor3f(0.0f,0.0f,1.0f);//设置当前色为蓝色
	glVertex3f( 10.0f,-10.0f, 0.0f); // 右下
	glEnd(); // 三角形绘制结束
	glPopMatrix();*/

	//刷新绘图命令并进行交换
	glutSwapBuffers();
}

void CViewEngine::SetupRC()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

//当窗口改变大小时由GLUT函数库调用
static void ChangeSize(GLsizei width, GLsizei height)
{
	//防止被0除
	if (height == 0)
	{
		height = 1;
	}

	//将视口设置为窗口的大小
	glViewport(0, 0, width, height);

	//重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//建立裁剪区域（left, right, bottom, top, front, back）
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	if (width < height)
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
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(33, TimerFunction, 1);

	this->SetupRC();
}
