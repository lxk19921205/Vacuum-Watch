#include <cstdio>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

extern GLfloat g_window_height;

struct Button{
	float m_fPosX;		//表示在正交投影坐标系(左下角为坐标原点)的坐标，
	float m_fPosY;
	float m_fWidth;
	float m_fHeight;

	bool m_bPressed;

//	GLuint	base;			// 绘制字体的显示列表的开始位置

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
			//将中心位于原点的cube移动到使cube左下角坐标为m_fPosX,m_fPosY的位置
			//必须考虑cube的自身长宽
			glTranslatef(m_fPosX+m_fWidth/2, m_fPosY+m_fHeight/2, -2.0);		//-2.0只是为了按钮可见
			if( m_bPressed )
			{
				//double scaleAmt = 10.0 * sin( (double)rand() );
				//double scaleAmt = sin( (double)rand() );
				glScalef(0.9, 0.9, 1.0);
			}
			//cube中心位于原点
			glScalef (m_fWidth, m_fHeight, 5.0);      
			glutSolidCube(1.0);
//			DrawGLScene();
		}
	}
	bool OnMouseDown(int mousex, int mousey)
	{
		//鼠标的位置：mousex，mousey坐标系是原点位于左上角
		//必须将mousey变换到原点位于左下角的坐标系中
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

/*	GLvoid glPrint(const char *fmt) // 自定义GL输出字体函数
	{
		char text[256]; // 保存文字串
		va_list ap; // 指向一个变量列表的指针
		if (fmt == NULL) // 如果无输入则返回
			return; 
		va_start(ap, fmt); // 分析可变参数
		vsprintf(text, fmt, ap); // 把参数值写入字符串
		va_end(ap); // 结束分析
		glPushAttrib(GL_LIST_BIT); // 把显示列表属性压入属性堆栈
		glListBase(base - 32); // 设置显示列表的基础值
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // 调用显示列表绘制字符串
		glPopAttrib(); // 弹出属性堆栈
	}

	int DrawGLScene(GLvoid) // 从这里开始进行所有的绘制
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
		glLoadIdentity(); // 重置当前的模型观察矩阵
		glTranslatef(0.0f,0.0f,0.0f); // 移入屏幕一个单位
		// 根据字体位置设置颜色
		glColor3f(1.0f,1.0f,1.0f);
		// 设置光栅化位置，即字体的位置
		glRasterPos2f(40, 40);
		glPrint("Siming Guo "); // 输出文字到屏幕
		return TRUE; // 一切 OK
	}
*/
};