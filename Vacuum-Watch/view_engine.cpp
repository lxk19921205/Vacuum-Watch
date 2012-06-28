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
}

/************************************************************************/
/* 用来画隧道中的遮挡板                                                  */
/* @type: 遮挡板的类型，见constants.h  @radius: 隧道的半径  @z: 板所在的z值*/
/************************************************************************/
static void DrawWall(int type, int radius, int z)
{
	switch (type)
	{
	case VW_WALL_ONE:
		{
			glPushMatrix();
// 			glBegin(GL_QUAD_STRIP);
// 			int inner_radius = radius / 3;	//里头可通过的圆半径是大圆的1/3
// 			for (int angle=0; angle<360; ++angle)
// 			{
// 				double sin_value = sin(angle * VW_PI / 180);
// 				double cos_value = cos(angle * VW_PI / 180);
// 
// 				glVertex3d(inner_radius*sin_value, inner_radius*cos_value, z);
// 				glVertex3d(radius*sin_value, radius*cos_value, z);
// 			}
// 			glEnd();

//			glCullFace(GL_CCW);
			glBegin(GL_QUADS);
			int inner_radius = radius / 3;	//里头可通过的圆半径是大圆的1/3
			for (int angle=0; angle<360; ++angle)
			{
				double sin_value = sin(angle * VW_PI / 180);
				double cos_value = cos(angle * VW_PI / 180);
				double next_sin_value = sin((angle+1) * VW_PI / 180);
				double next_cos_value = cos((angle+1) * VW_PI / 180);

				glVertex3d(inner_radius*sin_value, inner_radius*cos_value, z);
				glVertex3d(radius*sin_value, radius*cos_value, z);
				glVertex3d(radius*next_sin_value, radius*next_cos_value, z);
				glVertex3d(inner_radius*next_sin_value, inner_radius*next_cos_value, z);
			}
			glEnd();

			glPopMatrix();
// 			glBegin(GL_TRIANGLE_FAN);
// 			radius /= 2;
// 			glColor3f(0.0f, 0.0f, 0.0f);
// 			for(int i=0; i<1000; ++i)
// 			{
// 				glVertex3f(radius*cos(2*VW_PI/1000*i), radius*sin(2*VW_PI/1000*i), z-999.0f);
// 			}
// 			glEnd();
			break;
		}

	case VW_WALL_TWO:
		{
			glPushMatrix();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(0.1f, 0.1f, 0.1f);
			for(int i=0; i<1000; ++i)
			{
				glVertex3f(radius*cos(2* VW_PI/1000*i), radius*sin(2*VW_PI/1000*i), z-800.0f);
			}
			glEnd();

			glColor3f(0.0f, 0.0f, 0.0f);
			glPolygonMode(GL_FRONT,GL_FILL);
			glBegin(GL_POLYGON);
			glVertex3f(radius*0.3f,-radius*0.4f,z-799.0f);
			glVertex3f(radius*0.3f,radius*0.4f,z-799.0f);
			glVertex3f(-radius*0.3f,radius*0.4f,z-799.0f);
			glVertex3f(-radius*0.3f,-radius*0.4f,z-799.0f);
			glEnd();

			glPopMatrix();
			break;
		}
	case VW_WALL_THREE:
		{
			glPushMatrix();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(0.1f, 0.1f, 0.1f);
			for(int i=0; i<1000; ++i)
			{
				glVertex3f(radius*cos(2* VW_PI/1000*i), radius*sin(2*VW_PI/1000*i), z-800.0f);
			}
			glEnd();

			glColor3f(0.0f, 0.0f, 0.0f);
			glPolygonMode(GL_FRONT,GL_FILL);
			glBegin(GL_POLYGON);
			glVertex3f(-radius*0.2f,-radius*0.4f,z-799.0f);
			glVertex3f(-radius*0.2f,radius*0.4f,z-799.0f);
			glVertex3f(-radius*0.5f,radius*0.4f,z-799.0f);
			glVertex3f(-radius*0.5f,-radius*0.4f,z-799.0f);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(radius*0.5f,-radius*0.4f,z-799.0f);
			glVertex3f(radius*0.5f,radius*0.4f,z-799.0f);
			glVertex3f(radius*0.2f,radius*0.4f,z-799.0f);
			glVertex3f(radius*0.2f,-radius*0.4f,z-799.0f);
			glEnd();

			glPopMatrix();
			break;
		}
	default:
		break;
	}
}


static void RenderSceneOngoing()
{
	IGameData* data = CFactory::getController()->GetGameData();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//转动
	int current_length = data->GetCurrentLength();
	GLfloat plane_x = data->GetPositionX();
	GLfloat plane_y = data->GetPositionY();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(plane_x, plane_y, -current_length, plane_x, plane_y, -current_length-100, 0, 1, 0);	//减100还是减1不重要，只需要方向
	glRotated(tunnel_rotate, 0, 0, 1);
	tunnel_rotate += 1;
	if (tunnel_rotate >= 360)
	{
		tunnel_rotate = 0;
	}

	//想设置背景图片为那张太空，暂无
//	background_picture.Rotate(-background_rotate, -1000.0f);


	const GLfloat start_z = -100.0f;
	int total_length = data->GetTotalLength();
	int tunnel_radius = data->GetTunnelRadius();
	glBegin(GL_LINES);
		for (int angle = 0; angle < 360; angle++)
		{
			if (angle % 60 == 0)
			{
				glLineWidth(10);
				glColor3d(1, 1, 1);
			}
			else
			{
				glLineWidth(1);
				glColor3d(0.1, 0.1, 0.1);
			}

			GLdouble sin_value = sin(angle * VW_PI / 180);
			GLdouble cos_value = cos(angle * VW_PI / 180);

			glNormal3d(sin_value, cos_value, 0);
			glVertex3d(tunnel_radius * sin_value, tunnel_radius * cos_value, start_z);
			glVertex3d(tunnel_radius * sin_value, tunnel_radius * cos_value, start_z - total_length);
		}
	glEnd();

	//已经经过了几个遮挡板
	int past_walls = (current_length-1) / VW_DEF_WALL_DISTANCE;
	IController* controller = CFactory::getController();
	// 从当前将要遇到的遮挡板开始算起，最多画3个
	for (int wall_z=(past_walls+1)*VW_DEF_WALL_DISTANCE, count=0; wall_z<total_length && count<3; wall_z+=VW_DEF_WALL_DISTANCE, count++)
	{
		// 画遮挡板
		DrawWall(controller->NextWallType(), tunnel_radius, wall_z);
	}

	glutSwapBuffers();
}

static void RenderScenePaused()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

static void RenderScene()
{
	IController* controller = CFactory::getController();
	switch (controller->GetState())
	{
	case VW_STATE_MENU:
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

	g_window_width = (GLfloat) width;
	g_window_height = (GLfloat) height;

	//将视口设置为窗口的大小
	glViewport(0, 0, width, height);

	//重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	gluPerspective(30, aspect_ratio, 1, 1000);

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
	//下边必须注释掉，不然图片只能转一个很小的角度
// 	if (background_rotate >= 2 * VW_PI)
// 	{
// 		background_rotate = 0;
// 	}
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 1);
}

// 处理某几个特别按键的，时间紧迫，就乱乱地放在这里了
void SpecialKeys(int key, int x, int y)
{
	IController* controller = CFactory::getController();

	switch (key)
	{
	case GLUT_KEY_UP:
		controller->OnUpPushed();
		break;
	case GLUT_KEY_DOWN:
		controller->OnDownPushed();
		break;
	case GLUT_KEY_LEFT:
		controller->OnLeftPushed();
		break;
	case GLUT_KEY_RIGHT:
		controller->OnRightPushed();
		break;

	default:
		break;
	}
}


void CViewEngine::SetupRC()
{
	//TODO 所有一次性设定好、不再改的东西都在这里
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_FLAT);
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

	this->SetupRCMenu();
	this->InitMenuButtons();
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

void CViewEngine::SetupRCMenu()
{
	this->SetupRC();

	//加载背景图片
	background_picture.LoadPic("../Resource/picture/space.bmp");
	background_picture.AdjustPic(g_window_width, g_window_height, 0, 0);
	background_picture.InitRotate();
}

void CViewEngine::SetupRCOngoing()
{
	ChangeSize(g_window_width, g_window_height);

	this->SetupRC();

	glDisable(GL_TEXTURE_2D);

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

void CViewEngine::SetupRCSetting()
{
	this->SetupRC();
}

void CViewEngine::SetupRCAbout()
{
	this->SetupRC();
}

void CViewEngine::SetupRCPaused()
{
	this->SetupRC();
}
