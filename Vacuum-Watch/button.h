#ifndef _VW_BUTTON_H_
#define _VW_BUTTON_H_


class CButton{

private:
	float m_fPosX;		//表示在正交投影坐标系(左下角为坐标原点)的坐标，
	float m_fPosY;
	float m_fWidth;
	float m_fHeight;

	bool m_bPressed;

//	GLuint	base;			// 绘制字体的显示列表的开始位置

	void Init(void);

public:
	CButton();

	void Render();
	bool OnMouseDown(int mousex, int mousey);
	void OnMouseUp();

/*
	GLvoid glPrint(const char *fmt) // 自定义GL输出字体函数
	int DrawGLScene(GLvoid) // 从这里开始进行所有的绘制
*/
};

#endif
