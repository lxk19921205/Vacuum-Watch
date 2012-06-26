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

int rotate = 0;//��ת����

//�������static������ʾֻ�����.c����
static CButton start_button;
static CButton setting_button;
static CButton about_button;
static CButton quit_button;

static GLint wide, height;//Ҫ����bmp�ļ������صĿ�Ⱥ͸߶�
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
	//���ļ�����ȡ����
	FILE * readf;
	readf = fopen(load, "rb" );
	if ( readf == NULL )
	{
		printf( "���ļ�ʧ��\n \a" );
		system( "PAUSE" );
		exit( 0 );
	}
	fseek( readf, 0x0012, SEEK_SET );
	fread( &wide, sizeof( wide ), 1, readf );
	fread( &height, sizeof( height ), 1, readf );

	//�����������ݴ�С(+�)
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
		printf( "\aΪ���������ڴ�ռ�ʧ��" );
	}
	fseek( readf, 54, SEEK_SET );
	fread( pixelDate, pixelLength, 1, readf );
	fclose( readf );
}

//����ʾ�˵�ʱ��ʹ�������RenderScene
static void RenderSceneMenu()
{
	//�õ�ǰ�����ɫ�������
	glClear(GL_COLOR_BUFFER_BIT);

	//��ʾ��ť
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

	//����ͼƬ��������ͼƬ��λ�ô�С
	LoadPic("start.bmp");
	glRasterPos2i(40, 280);
	glPixelZoom(1.38f, 1.35f);//�����Գ����ģ������㣬��100/wide�õ��Ĵ�С����
	glDrawPixels( wide, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelDate );

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
	setting_button.InitPos(40.0f, 120.0f);
	about_button.InitPos(40.0f, 200.0f);
	quit_button.InitPos(40.0f, 280.0f);

}
