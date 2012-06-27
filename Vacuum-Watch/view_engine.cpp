#include <gl/freeglut.h>
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

static float rotate = 0;//旋转参数

//函数外的static变量表示只在这个.c里用
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

//在显示菜单时，使用这里的RenderScene
static void RenderSceneMenu()
{
	cout << "IN RENDER_SCENE_MENU()" << endl;

	//用当前清除颜色清除窗口
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//要这2行，否则按钮出不来
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	//显示
//	glColor3f(1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_window_width, 0, g_window_height, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	background_picture.Rotate(-rotate);

//	background_picture.Render();
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
	glRotatef(g_x1,0.0f,0.0f,1.0f); // 绕z轴旋转
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//创建空心圆柱
	gluDeleteQuadric(pObj); 
	glPopMatrix();  
*/

	//刷新绘图命令并进行交换
	glutSwapBuffers();
	return;
}

static void RenderSceneSetting()
{
	cout << "IN RENDER_SCENE_SETTING()" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

static void RenderSceneAbout()
{
	cout << "IN RENDER_SCENE_ABOUT()" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	return;
}


static void RenderSceneOngoing()
{
	cout << "IN RENDER_SCENE_ONGOING()" << endl;

	glDisable(GL_DEPTH_TEST);

	//用黑色清除窗口
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	IGameData* data = CFactory::getController()->GetGameData();
	int current_length = data->GetCurrentLength();
	int total_length = data->GetTotalLength();

// 	glMatrixMode(GL_MODELVIEW);
// 	glPushMatrix();
// 	glTranslatef(0.0f, 0.0f, -300.0f);
// 	glPopMatrix();


	glOrtho(-100, 500, -100, 500, -100, 500);
	glRectd(0, 0, 100, 100);
// 	glOrtho(0.0f, 1.0, 0.0, 1.0, -1.0, 1.0);
// 	glColor3f(1.0f, 1.0f, 1.0f);
// 	glBegin(GL_POLYGON);
// 	glVertex3f(0.25f, 0.25f, 0.0f);
// 	glVertex3f(0.75f, 0.25f, 0.0f);
// 	glVertex3f(0.75f, 0.75f, 0.0f);
// 	glVertex3f(0.25f, 0.75f, 0.0f);
// 	glEnd();

//	glFlush();
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
	cout << "IN RENDER_SCENE()" << endl;
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

//当窗口改变大小时由GLUT函数库调用
static void ChangeSize(GLsizei width, GLsizei height)
{
	cout << "IN CHANGE_SIZE()" << endl;

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
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	gluPerspective(45.0f, aspect_ratio, 1.0, 425.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//每VW_REFRESH_INTERVAL毫秒的时间执行一次，用来刷新，Controller只要改状态标识就好了，刷新界面的调令从这里走
void TimerFunction(int value)
{
	IController* controller = CFactory::getController();

	bool need_redraw = controller->OnTimerClick();
	if (need_redraw)
	{
		glutPostRedisplay();
	}

	rotate += 0.1f;
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 1);
}

void CViewEngine::SetupRC()
{
	//TODO 所有一次性设定好、不再改的东西都在这里
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

// 	glShadeModel(GL_SMOOTH);
// 
// 	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
// 	glClearDepth(1.0);
// 	glDepthFunc(GL_LEQUAL);
// 
// 	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
// 
// 	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
// 	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
}

void CViewEngine::Init(int* pargc, char** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize((int)g_window_width, (int)g_window_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 0);

	this->SetupRC();
	this->InitMenuButtons();

	background_picture.LoadPic("../Resource/picture/space.bmp");
	background_picture.AdjustPic(g_window_width, g_window_height, 0, 0);
}

void CViewEngine::OnLeftClicked( int pos_x, int pos_y )
{
	IController* controller = CFactory::getController();
	//先检查当前状态，是不是在显示开始界面的地方！
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
	start_picture.AdjustPic(100, 60, 350, 440);

	setting_button.InitPos(350.0f, 340.0f);
	setting_picture.LoadPic("../Resource/picture/setting.bmp");
	setting_picture.AdjustPic(100, 60, 350, 340);

	about_button.InitPos(350.0f, 240.0f);
	about_picture.LoadPic("../Resource/picture/about.bmp");
	about_picture.AdjustPic(100, 60, 350, 240);

	quit_button.InitPos(350.0f, 140.0f);
	quit_picture.LoadPic("../Resource/picture/quit.bmp");
	quit_picture.AdjustPic(100, 60, 350, 140);
}
