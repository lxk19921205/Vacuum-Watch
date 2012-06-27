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

//int rotate = 0;//旋转参数

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

bool LoadPic(const char* load, GLint new_wide, GLint new_height)
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
	//转换图片大小
	pixelLength = new_wide * 3;
	while((pixelLength % 4) != 0 )
	{
		//pixelLength = pixelLength + 4 - ( pixelLength % 4 );
		pixelLength++;
	}
	pixelLength = pixelLength * new_height;
	GLubyte *new_pixelDate = ( GLubyte * )malloc( pixelLength );
	if ( pixelDate == NULL )
	{
		printf( "\a为像素申请内存空间失败" );
	}
	gluScaleImage(GL_RGB, wide, height, GL_UNSIGNED_BYTE, pixelDate, new_wide, new_height, GL_UNSIGNED_BYTE, new_pixelDate);
	free(pixelDate);
	pixelDate = new_pixelDate;
	wide = new_wide;
    height = new_height;
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

/*	glPushMatrix();
	glRotatef(rotate, 0.0f, 0.0f,1.0f);
	glPushMatrix();

//	glRasterPos2i(0, 0);
	LoadPic("space.bmp");
	glDrawPixels( wide, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelDate );
*/

	//导入图片，并调整图片、位置大小
	LoadPic("../Resource/picture/start.bmp",100,60);
	glRasterPos2i(40, 40);
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
	//用黑色清除窗口
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	IGameData* data = CFactory::getController()->GetGameData();
	int current_length = data->GetCurrentLength();
	int total_length = data->GetTotalLength();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0);

	glColor3f(1.0f, 1.0f, 0.0f);
	GLfloat radius = 100;
	GLfloat center_x = 300;
	GLfloat center_y = 300;
	glLineWidth(10);
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_QUADS);
	for (int angle=0; angle<360; angle+=30)
	{
		double radian = angle * VW_PI / 180;
		double next_radian = (angle + 1) * VW_PI / 180;

		glVertex3f(center_x + radius * sin(radian), center_y + radius * cos(radian), 50);
		glVertex3f(center_x + radius * sin(next_radian), center_y + radius * cos(next_radian), 50);
		glVertex3f(center_x + radius * sin(next_radian), center_y + radius * cos(next_radian), -50);
		glVertex3f(center_x + radius * sin(radian), center_y + radius * cos(radian), -50);
	}
	glEnd();

//	glBegin(GL_TRIANGLES);
// 	for (int angle=0; angle<360; angle+=30)
// 	{
// 		double radian = angle * VW_PI / 180;
// 		GLfloat x = radius * sin(radian);
// 		GLfloat y = radius * cos(radian);
// // 		cout << "from (" << center_x+x << ", " << center_y+y << ", " << 50 << endl;
// // 		cout << "to   (" << center_x+x << ", " << center_y+y << ", " << -50 << endl;
// 		glVertex3f(center_x + x, center_y + y, 50);
// 		glVertex3f(center_x + x, center_y + y, -50);
// 	}
// 	glEnd();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//	glFrustum(-100, 100, -100, 100, 50, -50);
	gluPerspective(2, g_window_width/g_window_height, 50, -50);


	

	glutSwapBuffers();
	return;







//	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);


// 	glColor3f(1.0f, 1.0f, 1.0f);
// 	GLfloat inner_angle = 1;
// 	GLfloat outer_angle = 60;
// 	GLfloat radius = 200;
// 
// 	GLfloat center_x = 300;
// 	GLfloat center_y = 300;
// 
// 	static GLfloat the_angle = 0;
// 	the_angle += 1;
// 	if (the_angle > 360)
// 	{
// 		the_angle = 0;
// 	}
// 	GLfloat angle = the_angle;
// 	glBegin(GL_TRIANGLES);
// 		for (int i=0;i<=360;i+=outer_angle)
// 		{
// 			glVertex3f(center_x, center_y, 0.0f);
// 			glVertex3f(center_x + radius * sin(angle * VW_PI / 180), center_y + radius * cos(angle * VW_PI / 180), 0.0f);
// 			GLfloat a_little_more = angle + inner_angle;
// 			glVertex3f(center_x + radius * sin(a_little_more * VW_PI / 180), center_y + radius * cos(a_little_more * VW_PI / 180), 0.0f);
// 			angle += outer_angle;
// 		}
// 	glEnd();
// 
// 	glutSwapBuffers();
// 	return;





// 	glPushMatrix();
// 	glRotatef(30, 1.0f, 0.0f, 0.0f);
// 	glRotatef(30, 0.0f, 1.0f, 0.0f);
// 
// 	static GLfloat offset_x = 0;
// 	static GLfloat offset_y = 0;
// 
// 	offset_x++;
// 	offset_y++;
// 
// 	glBegin(GL_LINE_STRIP);
// 	GLfloat z = -50.0f;
// 	for (GLfloat angle = 0.0f; angle < 2.0f*VW_PI*3.0f; angle += 0.1)
// 	{
// 		GLfloat x = 50.0f * sin(angle);
// 		GLfloat y = 50.0f * cos(angle);
// 
// 		glVertex3f(x + offset_x, y + offset_y, z);
// 		z += 0.5f;
// 	}
// 	glEnd();
// 	glPopMatrix();

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
	glRotatef(g_x1,0.0f,0.0f,1.0f); // 绕z轴旋转
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//创建空心圆柱
	gluDeleteQuadric(pObj); 
	glPopMatrix();  
*/


//	glutSwapBuffers();
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
