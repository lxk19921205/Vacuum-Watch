#include <gl/glut.h>
#include <iostream>

#include "view_engine.h"
#include "constants.h"
#include "button.h"
#include "factory.h"
#include "load_picture.h"

using std::cout;
using std::endl;

GLfloat g_window_width = VW_WINDOW_WIDTH;
GLfloat g_window_height = VW_WINDOW_HEIGHT;

//int rotate = 0;//��ת����

//�������static������ʾֻ�����.c����
static CButton start_button;
static CButton setting_button;
static CButton about_button;
static CButton quit_button;

static CLoadPic start_picture;
static CLoadPic setting_picture;
static CLoadPic about_picture;
static CLoadPic quit_picture;
static CLoadPic background_picture;

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

//����ʾ�˵�ʱ��ʹ�������RenderScene
static void RenderSceneMenu()
{
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT);

	//��ʾ
	glColor3f(1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_window_width, 0, g_window_height, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

/*	start_button.Render();
	setting_button.Render();
	about_button.Render();
	quit_button.Render();
*/
	background_picture.Render();
	start_picture.Render();
	setting_picture.Render();
	about_picture.Render();
	quit_picture.Render();

/*	glPushMatrix();
	glRotatef(rotate, 0.0f, 0.0f,1.0f);
	glPushMatrix();

//	glRasterPos2i(0, 0);
	LoadPic("space.bmp");
	glDrawPixels( wide, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelDate );
*/

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

static void RenderSceneSetting()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

static void RenderSceneAbout()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

static void RenderSceneOngoing()
{
	//�ú�ɫ�������
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	IGameData* data = CFactory::getController()->GetGameData();
	int current_length = data->GetCurrentLength();
	int total_length = data->GetTotalLength();




	GLfloat inner_angle = 1;
	GLfloat outer_angle = 60;
	GLfloat radius = 200;

	GLfloat center_x = 300;
	GLfloat center_y = 300;

	static GLfloat the_angle = 0;
	the_angle += 1;
	if (the_angle > 360)
	{
		the_angle = 0;
	}
	GLfloat angle = the_angle;
	glBegin(GL_TRIANGLES);
		for (int i=0;i<=360;i+=outer_angle)
		{
			glVertex3f(center_x, center_y, 0.0f);
			glVertex3f(center_x + radius * sin(angle * VW_PI / 180), center_y + radius * cos(angle * VW_PI / 180), 0.0f);
			GLfloat a_little_more = angle + inner_angle;
			glVertex3f(center_x + radius * sin(a_little_more * VW_PI / 180), center_y + radius * cos(a_little_more * VW_PI / 180), 0.0f);
			angle += outer_angle;
		}
	glEnd();

	glutSwapBuffers();
	return;





	glPushMatrix();
	glRotatef(30, 1.0f, 0.0f, 0.0f);
	glRotatef(30, 0.0f, 1.0f, 0.0f);

	static GLfloat offset_x = 0;
	static GLfloat offset_y = 0;

	offset_x++;
	offset_y++;

	glBegin(GL_LINE_STRIP);
	GLfloat z = -50.0f;
	for (GLfloat angle = 0.0f; angle < 2.0f*VW_PI*3.0f; angle += 0.1)
	{
		GLfloat x = 50.0f * sin(angle);
		GLfloat y = 50.0f * cos(angle);

		glVertex3f(x + offset_x, y + offset_y, z);
		z += 0.5f;
	}
	glEnd();
	glPopMatrix();

// 	cout << current_length << endl;
// 	int width = (int) g_window_width;
// 	float pos = current_length % width;
// 	glBegin(GL_LINE);
// 	glVertex2f(pos, 100);
// 	glVertex2f(100, pos);
// 	glEnd();
// 
// 	glRectf(pos, 0.0f, 100.0f, 100.0f);


// 
// 
// 	glColor3f(1.0f, 1.0f, 1.0f);
// 	glRectf(0.0f, 0.0f, 100.0f, 100.0f);



/*	glTranslatef(0.0f, 0.0f, 10.0f);  

	glPushMatrix(); 
	glRotatef(g_x1,0.0f,0.0f,1.0f); // ��z����ת
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//��������Բ��
	gluDeleteQuadric(pObj); 
	glPopMatrix();  
*/


	glutSwapBuffers();
}

static void RenderScenePaused()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

static void RenderScene()
{
	IController* controller = CFactory::getController();
	switch (controller->GetState())
	{
	case VW_STATE_MENU:
		background_picture.LoadPic("../Resource/picture/space.bmp");
		background_picture.AdjustPic(g_window_width, g_window_height, 0.0f, 0.0f);
		RenderSceneMenu();
		return;
	case VW_STATE_SETTING:
		RenderSceneSetting();
		return;
	case VW_STATE_ABOUT:
		RenderSceneAbout();
		return;
	case VW_STATE_ONGOING:
		RenderSceneOngoing();
		return;
	case VW_STATE_PAUSED:
		RenderScenePaused();
		return;

	default:
		return;
	}
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

//ÿVW_REFRESH_INTERVAL�����ʱ��ִ��һ�Σ�����ˢ�£�ControllerֻҪ��״̬��ʶ�ͺ��ˣ�ˢ�½���ĵ����������
void TimerFunction(int value)
{
	IController* controller = CFactory::getController();

	bool need_redraw = controller->OnTimerClick();
	if (need_redraw)
	{
		glutPostRedisplay();
	}

	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, value+1);
}


void CViewEngine::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(g_window_width, g_window_height);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 0);

	this->InitMenuButtons();
}

void CViewEngine::OnLeftClicked( int pos_x, int pos_y )
{
	IController* controller = CFactory::getController();
	//�ȼ�鵱ǰ״̬���ǲ�������ʾ��ʼ����ĵط���
	if (controller->GetState() != VW_STATE_MENU)
	{
		return;
	}

	if (start_button.OnMouseDown(pos_x, pos_y))
	{
		start_button.OnMouseUp();
		controller->OnStartButton();
		return;
	}

	if (setting_button.OnMouseDown(pos_x, pos_y))
	{
		setting_button.OnMouseUp();
		controller->OnSettingButton();
		return;
	}

	if (about_button.OnMouseDown(pos_x, pos_y))
	{
		about_button.OnMouseUp();
		controller->OnAboutButton();
		return;
	}

	if (quit_button.OnMouseDown(pos_x, pos_y))
	{
		quit_button.OnMouseUp();
		controller->OnQuitButton();
		return;
	}
}

//Ϊʲôע���أ���module_interfaces.h
// void CViewEngine::Redraw()
// {
// 	glutPostRedisplay();
// }

void CViewEngine::InitMenuButtons()
{
	//TODO �˺����Ѿ���Init()�������

	start_button.InitPos(40.0f, 40.0f);
	start_picture.LoadPic("../Resource/picture/start.bmp");
	start_picture.AdjustPic(100.0f, 60.0f, 40.0f, 40.0f);
	setting_button.InitPos(40.0f, 120.0f);
	setting_picture.LoadPic("../Resource/picture/setting.bmp");
	setting_picture.AdjustPic(100.0f, 60.0f, 40.0f, 120.0f);
	about_button.InitPos(40.0f, 200.0f);
	about_picture.LoadPic("../Resource/picture/about.bmp");
	about_picture.AdjustPic(100.0f, 60.0f, 40.0f, 200.0f);
	quit_button.InitPos(40.0f, 280.0f);
	quit_picture.LoadPic("../Resource/picture/quit.bmp");
	quit_picture.AdjustPic(100.0f, 60.0f, 40.0f, 280.0f);

}
