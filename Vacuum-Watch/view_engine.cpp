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

static float background_rotate = 0;	//背景图片旋转参数，弧度
static int tunnel_rotate = 0;		//隧道转动的角度

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;



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



void CViewEngine::StartDisplaying()
{
	glutMainLoop();
	//TODO
}

//在显示菜单时，使用这里的RenderScene
static void RenderSceneMenu()
{
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

	background_picture.Rotate(-background_rotate);

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
	IGameData* data = CFactory::getController()->GetGameData();
	int current_length = data->GetCurrentLength();
	int total_length = data->GetTotalLength();
	int tunnel_radius = data->GetTunnelRadius();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//转动
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, -current_length, 0, 0, -current_length-100, 0, 1, 0);	//减100还是减1不重要，只需要方向
	glRotated(tunnel_rotate, 0, 0, 1);
	tunnel_rotate += 1;
	if (tunnel_rotate >= 360)
	{
		tunnel_rotate = 0;
	}

	//想设置背景图片为那张太空，暂无
//	background_picture.Rotate(-background_rotate, -1000.0f);


	glColor3d(1, 1, 1);
	const GLfloat start_z = -100.0f;
	glLineWidth(10);
	glBegin(GL_LINES);
		for (int angle = 0; angle < 360; angle+=60)
		{
			GLdouble sin_value = sin(angle * VW_PI / 180);
			GLdouble cos_value = cos(angle * VW_PI / 180);

			glNormal3d(sin_value, cos_value, 0);
			glVertex3d(tunnel_radius * sin_value, tunnel_radius * cos_value, start_z);
			glVertex3d(tunnel_radius * sin_value, tunnel_radius * cos_value, start_z - total_length);
		}
	glEnd();

	glutSwapBuffers();
	return;


	float fZ,bZ;
	fZ = 100.0f;
	bZ = -100.0f;

	// Save the matrix state and do the rotations
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -300.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Set material color, Red
	glColor3f(1.0f, 0.0f, 0.0f);

	// Front Face ///////////////////////////////////
	glBegin(GL_QUADS);
	// Pointing straight out Z
	glNormal3f(0.0f, 0.0f, 1.0f);	

	// Left Panel
	glVertex3f(-50.0f, 50.0f, fZ);
	glVertex3f(-50.0f, -50.0f, fZ);
	glVertex3f(-35.0f, -50.0f, fZ);
	glVertex3f(-35.0f,50.0f,fZ);

	// Right Panel
	glVertex3f(50.0f, 50.0f, fZ);
	glVertex3f(35.0f, 50.0f, fZ);
	glVertex3f(35.0f, -50.0f, fZ);
	glVertex3f(50.0f,-50.0f,fZ);

	// Top Panel
	glVertex3f(-35.0f, 50.0f, fZ);
	glVertex3f(-35.0f, 35.0f, fZ);
	glVertex3f(35.0f, 35.0f, fZ);
	glVertex3f(35.0f, 50.0f,fZ);

	// Bottom Panel
	glVertex3f(-35.0f, -35.0f, fZ);
	glVertex3f(-35.0f, -50.0f, fZ);
	glVertex3f(35.0f, -50.0f, fZ);
	glVertex3f(35.0f, -35.0f,fZ);

	// Top length section ////////////////////////////
	// Normal points up Y axis
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-50.0f, 50.0f, fZ);
	glVertex3f(50.0f, 50.0f, fZ);
	glVertex3f(50.0f, 50.0f, bZ);
	glVertex3f(-50.0f,50.0f,bZ);

	// Bottom section
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, fZ);
	glVertex3f(-50.0f, -50.0f, bZ);
	glVertex3f(50.0f, -50.0f, bZ);
	glVertex3f(50.0f, -50.0f, fZ);

	// Left section
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(50.0f, 50.0f, fZ);
	glVertex3f(50.0f, -50.0f, fZ);
	glVertex3f(50.0f, -50.0f, bZ);
	glVertex3f(50.0f, 50.0f, bZ);

	// Right Section
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, 50.0f, fZ);
	glVertex3f(-50.0f, 50.0f, bZ);
	glVertex3f(-50.0f, -50.0f, bZ);
	glVertex3f(-50.0f, -50.0f, fZ);
	glEnd();

	glFrontFace(GL_CW);		// clock-wise polygons face out

	glBegin(GL_QUADS);
	// Back section
	// Pointing straight out Z
	glNormal3f(0.0f, 0.0f, -1.0f);	

	// Left Panel
	glVertex3f(-50.0f, 50.0f, bZ);
	glVertex3f(-50.0f, -50.0f, bZ);
	glVertex3f(-35.0f, -50.0f, bZ);
	glVertex3f(-35.0f,50.0f,bZ);

	// Right Panel
	glVertex3f(50.0f, 50.0f, bZ);
	glVertex3f(35.0f, 50.0f, bZ);
	glVertex3f(35.0f, -50.0f, bZ);
	glVertex3f(50.0f,-50.0f,bZ);

	// Top Panel
	glVertex3f(-35.0f, 50.0f, bZ);
	glVertex3f(-35.0f, 35.0f, bZ);
	glVertex3f(35.0f, 35.0f, bZ);
	glVertex3f(35.0f, 50.0f,bZ);

	// Bottom Panel
	glVertex3f(-35.0f, -35.0f, bZ);
	glVertex3f(-35.0f, -50.0f, bZ);
	glVertex3f(35.0f, -50.0f, bZ);
	glVertex3f(35.0f, -35.0f,bZ);

	// Insides /////////////////////////////
	glColor3f(0.75f, 0.75f, 0.75f);

	// Normal points up Y axis
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-35.0f, 35.0f, fZ);
	glVertex3f(35.0f, 35.0f, fZ);
	glVertex3f(35.0f, 35.0f, bZ);
	glVertex3f(-35.0f,35.0f,bZ);

	// Bottom section
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-35.0f, -35.0f, fZ);
	glVertex3f(-35.0f, -35.0f, bZ);
	glVertex3f(35.0f, -35.0f, bZ);
	glVertex3f(35.0f, -35.0f, fZ);

	// Left section
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-35.0f, 35.0f, fZ);
	glVertex3f(-35.0f, 35.0f, bZ);
	glVertex3f(-35.0f, -35.0f, bZ);
	glVertex3f(-35.0f, -35.0f, fZ);

	// Right Section
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(35.0f, 35.0f, fZ);
	glVertex3f(35.0f, -35.0f, fZ);
	glVertex3f(35.0f, -35.0f, bZ);
	glVertex3f(35.0f, 35.0f, bZ);
	glEnd();

	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

	// Restore the matrix state
	glPopMatrix();

	// Buffer swap
	glutSwapBuffers();
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
		background_picture.InitRotate();
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
	gluPerspective(45, aspect_ratio, 1, 1000);

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

	background_rotate += 0.1f;
	if (background_rotate >= 2 * VW_PI)
	{
		background_rotate = 0;
	}
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 1);
}

// 处理某几个特别按键的，时间紧迫，就乱乱地放在这里了
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
}


void CViewEngine::SetupRC()
{
	//TODO 所有一次性设定好、不再改的东西都在这里
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_FLAT);



	// Light values and coordinates
	GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black blue background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void CViewEngine::Init(int* pargc, char** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(VW_WINDOW_WIDTH, VW_WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	
	glutSpecialFunc(SpecialKeys);

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
