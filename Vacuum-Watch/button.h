#include <cstdio>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

extern GLfloat g_window_height;

struct Button{
	float m_fPosX;		//��ʾ������ͶӰ����ϵ(���½�Ϊ����ԭ��)�����꣬
	float m_fPosY;
	float m_fWidth;
	float m_fHeight;

	bool m_bPressed;

//	GLuint	base;			// �����������ʾ�б�Ŀ�ʼλ��

	void init(void) 
	{
		m_bPressed = false;
		m_fPosX = 40;
		m_fPosY = 40;
		m_fWidth = 60;
		m_fHeight = 20;
//		base = glGenLists(96);
		cout<<"button pos: 40 40"<<endl;
	}


	void Render()
	{
		glPushMatrix();
		{
			//������λ��ԭ���cube�ƶ���ʹcube���½�����Ϊm_fPosX,m_fPosY��λ��
			//���뿼��cube��������
			glTranslatef(m_fPosX+m_fWidth/2, m_fPosY+m_fHeight/2, -2.0);		//-2.0ֻ��Ϊ�˰�ť�ɼ�
			if( m_bPressed )
			{
				//double scaleAmt = 10.0 * sin( (double)rand() );
				//double scaleAmt = sin( (double)rand() );
				glScalef(0.9, 0.9, 1.0);
			}
			//cube����λ��ԭ��
			glScalef (m_fWidth, m_fHeight, 5.0);      
			glutSolidCube(1.0);
//			DrawGLScene();
		}
	}
	bool OnMouseDown(int mousex, int mousey)
	{
		//����λ�ã�mousex��mousey����ϵ��ԭ��λ�����Ͻ�
		//���뽫mousey�任��ԭ��λ�����½ǵ�����ϵ��
		mousey = g_window_height-mousey;
		if( mousex > m_fPosX && mousex < m_fPosX+m_fWidth &&
			mousey > m_fPosY && mousey < m_fPosY+m_fHeight )
		{
			cout<<"button is pressed ...."<<endl;
			m_bPressed = true;
			
			return true;
		}
		return false;
	}
	void OnMouseUp()
	{
		m_bPressed = false;
	}

/*	GLvoid glPrint(const char *fmt) // �Զ���GL������庯��
	{
		char text[256]; // �������ִ�
		va_list ap; // ָ��һ�������б��ָ��
		if (fmt == NULL) // ����������򷵻�
			return; 
		va_start(ap, fmt); // �����ɱ����
		vsprintf(text, fmt, ap); // �Ѳ���ֵд���ַ���
		va_end(ap); // ��������
		glPushAttrib(GL_LIST_BIT); // ����ʾ�б�����ѹ�����Զ�ջ
		glListBase(base - 32); // ������ʾ�б�Ļ���ֵ
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // ������ʾ�б�����ַ���
		glPopAttrib(); // �������Զ�ջ
	}

	int DrawGLScene(GLvoid) // �����￪ʼ�������еĻ���
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����Ļ����Ȼ���
		glLoadIdentity(); // ���õ�ǰ��ģ�͹۲����
		glTranslatef(0.0f,0.0f,0.0f); // ������Ļһ����λ
		// ��������λ��������ɫ
		glColor3f(1.0f,1.0f,1.0f);
		// ���ù�դ��λ�ã��������λ��
		glRasterPos2f(40, 40);
		glPrint("Siming Guo "); // ������ֵ���Ļ
		return TRUE; // һ�� OK
	}
*/
};