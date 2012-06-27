#ifndef _VW_LOAD_PICTURE_H_
#define _VW_LOAD_PICTURE_H_

#include <gl/glut.h>
#include <iostream>

class CLoadPic{

private:
	GLint m_wide, m_height;//Ҫ����bmp�ļ������صĿ�Ⱥ͸߶�
	GLubyte * m_pixelDate;//ָ��ͼƬ��Ϣ
	GLint m_pixelLength;//�����ͼƬ�ռ�
	GLint m_posx, m_posy;//ͼƬ��ʾ��λ��
	GLuint m_texName;//���������

	void Init();

public:
	CLoadPic();
	~CLoadPic();

	bool LoadPic(const char* load);
	bool AdjustPic(GLint new_wide, GLint new_height, GLint new_posx, GLint new_posy);
	void Render();
	void InitRotate();
	void Rotate(float rotate);//ͼƬ��������������ת��rotateΪ��ת����
};

#endif
