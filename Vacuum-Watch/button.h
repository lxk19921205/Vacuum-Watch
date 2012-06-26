#ifndef _VW_BUTTON_H_
#define _VW_BUTTON_H_


class CButton{

private:
	float m_fPosX;		//��ʾ������ͶӰ����ϵ(���½�Ϊ����ԭ��)�����꣬
	float m_fPosY;
	float m_fWidth;
	float m_fHeight;

	bool m_bPressed;

//	GLuint	base;			// �����������ʾ�б�Ŀ�ʼλ��

	void Init();

public:
	CButton();

	void Render();
	bool OnMouseDown(int mousex, int mousey);
	void OnMouseUp();
	void InitPos(float x, float y);

/*
	GLvoid glPrint(const char *fmt) // �Զ���GL������庯��
	int DrawGLScene(GLvoid) // �����￪ʼ�������еĻ���
*/
};

#endif
