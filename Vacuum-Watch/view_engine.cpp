#include <gl/glut.h>
#include <iostream>

#include "view_engine.h"
#include "constants.h"
#include "button.h"
#include "factory.h"

using std::cout;
using std::endl;

GLfloat g_window_width = VW_WINDOW_WIDTH;
GLfloat g_window_height = VW_WINDOW_HEIGHT;

int rotate = 0;//旋转参数

//函数外的static变量表示只在这个.c里用
static CButton start_button;
static CButton setting_button;
static CButton about_button;
static CButton quit_button;

static GLint wide, height;//要读的bmp文件的像素的宽度和高度
static GLubyte * pixelDate = NULL;
static GLint pixelLength;


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

bool LoadPic(const char* load)
{
	//打开文件并读取像素
	FILE * readf;
	readf = fopen(load, "rb" );
	if ( readf == NULL )
	{
		printf( "打开文件失败\n \a" );
		system( "PAUSE" );
		exit( 0 );
	}
	fseek( readf, 0x0012, SEEK_SET );
	fread( &wide, sizeof( wide ), 1, readf );
	fread( &height, sizeof( height ), 1, readf );

	//计算像素数据大小(+填补)
	pixelLength = wide * 3;
	while((pixelLength % 4) != 0 )
	{
		//pixelLength = pixelLength + 4 - ( pixelLength % 4 );
		pixelLength++;
	}
	pixelLength = pixelLength * height;
	pixelDate = ( GLubyte * )malloc( pixelLength );
	if ( pixelDate == NULL )
	{
		printf( "\a为像素申请内存空间失败" );
	}
	fseek( readf, 54, SEEK_SET );
	fread( pixelDate, pixelLength, 1, readf );
	fclose( readf );
}

//在显示菜单时，使用这里的RenderScene
static void RenderSceneMenu()
{
	//用当前清除颜色清除窗口
	glClear(GL_COLOR_BUFFER_BIT);

	//显示按钮
	glColor3f(1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, g_window_width, 0, g_window_height, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	start_button.Render();
	setting_button.Render();
	about_button.Render();
	quit_button.Render();

/*	glLoadIdentity();
	glPushMatrix();  
	glTranslatef(-1.5,0.0,-6.0);  
	glRotatef(rotate,0.0f,0.0f,1.0f);  
	glRasterPos2i(0, 0);
	LoadPic("space.bmp");
	glDrawPixels( wide, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelDate );
	glPopMatrix();  
*/

	//导入图片，并调整图片、位置大小
	LoadPic("start.bmp");
	glRasterPos2i(40, 280);
	glPixelZoom(1.38f, 1.35f);//试数试出来的，不会算，用100/wide得到的大小不对
	glDrawPixels( wide, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelDate );

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

static void RenderSceneSetting()
{

}

static void RenderSceneAbout()
{

}

static void RenderSceneOngoing()
{

}

static void RenderScenePaused()
{

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

//每VW_REFRESH_INTERVAL毫秒的时间执行一次，用来刷新，Controller只要改状态标识就好了，刷新界面的调令从这里走
void TimerFunction(int value)
{
	IController* controller = CFactory::getController();
	controller->OnTimerClick();
	rotate += 100;

	glutPostRedisplay();
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

	this->SetupRC();
	this->InitMenuButtons();
	free(pixelDate);
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

//为什么注释呢：见module_interfaces.h
// void CViewEngine::Redraw()
// {
// 	glutPostRedisplay();
// }

void CViewEngine::InitMenuButtons()
{
	//TODO 此函数已经在Init()里调用了

	start_button.InitPos(40.0f, 40.0f);
	setting_button.InitPos(40.0f, 120.0f);
	about_button.InitPos(40.0f, 200.0f);
	quit_button.InitPos(40.0f, 280.0f);

}
