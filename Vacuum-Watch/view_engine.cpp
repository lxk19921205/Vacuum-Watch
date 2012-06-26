#include <gl/glut.h>
#include <iostream>

#include "view_engine.h"
#include "constants.h"
#include "button.h"

using std::cout;
using std::endl;

GLfloat g_window_width = VW_WINDOW_WIDTH;
GLfloat g_window_height = VW_WINDOW_HEIGHT;


//函数外的static变量表示只在这个.c里用
static CButton start_button;
static CButton setting_button;
static CButton about_button;
static CButton quit_button;



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


static void RenderScene()
{
	//用当前清除颜色清除窗口
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	//建立按钮
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_window_width, 0, g_window_height, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	start_button.Render();
	

/*	glTranslatef(0.0f, 0.0f, 10.0f);  

	glPushMatrix(); 
	glRotatef(g_x1,0.0f,0.0f,1.0f); // 绕z轴旋转
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//创建空心圆柱
	gluDeleteQuadric(pObj); 
	glPopMatrix();  
*/

	//	glRectf(g_x1, g_y1, g_x1+g_rsize, g_y1+g_rsize);

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

	g_window_width = width;
	g_window_height = height;

	//将视口设置为窗口的大小
	glViewport(0, 0, width, height);

	//重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//建立裁剪区域（left, right, bottom, top, front, back）
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
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);

	this->SetupRC();
}

void CViewEngine::OnLeftClicked( int pos_x, int pos_y )
{
	//TODO 先检查当前状态，是不是在显示开始界面的地方！
	if (true)
	{
	}

	if (start_button.OnMouseDown(pos_x, pos_y))
	{
		start_button.OnMouseUp();
		//TODO start
		cout << "start" << endl;
		return;
	}

	if (setting_button.OnMouseDown(pos_x, pos_y))
	{
		setting_button.OnMouseUp();
		//TODO setting
		cout << "setting" << endl;
		return;
	}

	if (about_button.OnMouseDown(pos_x, pos_y))
	{
		about_button.OnMouseUp();
		//TODO about
		cout << "about" << endl;
		return;
	}

	if (quit_button.OnMouseDown(pos_x, pos_y))
	{
		quit_button.OnMouseUp();
		//TODO quit
		cout << "quit" << endl;
		return;
	}
}
