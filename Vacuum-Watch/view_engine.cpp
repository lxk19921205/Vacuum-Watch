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

static float background_rotate = 0;	//����ͼƬ��ת����������
static int tunnel_rotate = 0;		//���ת���ĽǶ�



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
	glRotatef(g_x1,0.0f,0.0f,1.0f); // ��z����ת
	GLUquadric *pObj; 
	pObj = gluNewQuadric(); 
	gluCylinder(pObj,10.0f,90.0f,10.0f,100,100);//��������Բ��
	gluDeleteQuadric(pObj); 
	glPopMatrix();  
*/

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
	IGameData* data = CFactory::getController()->GetGameData();
	int current_length = data->GetCurrentLength();
	int total_length = data->GetTotalLength();
	int tunnel_radius = data->GetTunnelRadius();
	GLfloat plane_x = data->GetPositionX();
	GLfloat plane_y = data->GetPositionY();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ת��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(plane_x, plane_y, -current_length, plane_x, plane_y, -current_length-100, 0, 1, 0);	//��100���Ǽ�1����Ҫ��ֻ��Ҫ����
	glRotated(tunnel_rotate, 0, 0, 1);
	tunnel_rotate += 1;
	if (tunnel_rotate >= 360)
	{
		tunnel_rotate = 0;
	}

	//�����ñ���ͼƬΪ����̫�գ�����
//	background_picture.Rotate(-background_rotate, -1000.0f);


	const GLfloat start_z = -100.0f;
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

	glBegin(GL_POLYGON);
		for (int i=VW_DATA_DEF_WALL_DISTANCE; i<total_length; i+=VW_DATA_DEF_WALL_DISTANCE)
		{
			//TODO ���ڵ���
			//��֪��λ�õ�z���������radius
			//DrawWall(int type)	type��VW_WALL_XXX
		}
	glEnd();

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
	GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
	gluPerspective(45, aspect_ratio, 1, 1000);

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

	background_rotate += 0.1f;
	if (background_rotate >= 2 * VW_PI)
	{
		background_rotate = 0;
	}
	glutTimerFunc(VW_REFRESH_INTERVAL, TimerFunction, 1);
}

// ����ĳ�����ر𰴼��ģ�ʱ����ȣ������ҵط���������
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
	//TODO ����һ�����趨�á����ٸĵĶ�����������
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
