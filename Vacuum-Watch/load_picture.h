#ifndef _VW_LOAD_PICTURE_H_
#define _VW_LOAD_PICTURE_H_

#include <gl/freeglut.h>
#include <gl/GL.h>
#include <iostream>

class CLoadPic{

private:
	GLint m_wide, m_height;//要读的bmp文件的像素的宽度和高度
	GLubyte * m_pixelDate;//指向图片信息
	GLint m_pixelLength;//分配的图片空间
	GLint m_posx, m_posy;//图片显示的位置
	GLuint m_texName;//保存纹理绑定

	void Init();

public:
	CLoadPic();
	~CLoadPic();

	bool LoadPic(const char* load);
	bool AdjustPic(GLint new_wide, GLint new_height, GLint new_posx, GLint new_posy);
	void Render();
	void InitRotate();
	void Rotate(float rotate);//图片按照自身中心旋转，rotate为旋转快慢
	void Rotate(float rotate, GLfloat z);	//增加一个z轴的变量，表示深度
};

#endif
