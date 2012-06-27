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

static float rotate = 0;//��ת����

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Ҫ��2�У�����ť������
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	//��ʾ
//	glColor3f(1.0f, 0.0f, 0.0f);
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

	background_picture.Rotate(-rotate);

//	background_picture.Render();
	start_picture.Render();
	setting_picture.Render();
	about_picture.Render();
	quit_picture.Render();

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
	return;
}

static void RenderSceneSetting()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

static void RenderSceneAbout()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	return;
}

static void RenderSceneOngoing()
{
	//�ú�ɫ�������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	IGameData* data = CFactory::getController()->GetGameData();
	int current_length = data->GetCurrentLength();
	int total_length = data->GetTotalLength();

	glutSwapBuffers();
	return;
}

static void RenderScenePaused()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	return;
}

static void RenderScene()
{
	IController* controller = CFactory::getController();
	switch (controller->GetState())
	{
	case VW_STATE_MENU:
		background_picture.InitRotate();
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
	cout << "IN CHANGE_SIZE()" << endl;

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
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	gluPerspective(45.0f, aspect_ratio, 0.1, 400.0);

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
	rotate += 0.1f;
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, value+1);
}

void CViewEngine::SetupRC()
{
	//TODO ����һ�����趨�á����ٸĵĶ�����������
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
}

void CViewEngine::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_window_width, g_window_height);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 0);

	this->SetupRC();
	this->InitMenuButtons();

	background_picture.LoadPic("../Resource/picture/space.bmp");
	background_picture.AdjustPic(g_window_width+200, g_window_height+200, -100.0f, -100.0f);
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

void CViewEngine::InitMenuButtons()
{
	start_button.InitPos(350.0f, 440.0f);
	start_picture.LoadPic("../Resource/picture/start.bmp");
	start_picture.AdjustPic(100.0f, 60.0f, 350.0f, 440.0f);

	setting_button.InitPos(350.0f, 340.0f);
	setting_picture.LoadPic("../Resource/picture/setting.bmp");
	setting_picture.AdjustPic(100.0f, 60.0f, 350.0f, 340.0f);

	about_button.InitPos(350.0f, 240.0f);
	about_picture.LoadPic("../Resource/picture/about.bmp");
	about_picture.AdjustPic(100.0f, 60.0f, 350.0f, 240.0f);

	quit_button.InitPos(350.0f, 140.0f);
	quit_picture.LoadPic("../Resource/picture/quit.bmp");
	quit_picture.AdjustPic(100.0f, 60.0f, 350.0f, 140.0f);
}
