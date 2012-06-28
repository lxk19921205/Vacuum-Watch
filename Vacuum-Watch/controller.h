#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "module_interfaces.h"
#include <gl/freeglut.h>
#include <list>

using std::list;

/************************************************************************/
/* �ܿ����࣬������һ������                                             */
/************************************************************************/
class CController : public IController
{
public:
	virtual void StartGame();

	virtual void Init(int* pargc, char** argv);

	virtual IGameData* GetGameData();

	virtual void OnFireKeyClicked();
	virtual void OnMouseMoved(int from_x, int from_y, int to_x, int to_y);
	virtual void OnLeftClicked(int pos_x, int pos_y);

	virtual bool OnTimerClick();

	virtual int GetState();

	virtual void OnStartButton();
	virtual void OnSettingButton();
	virtual void OnAboutButton();
	virtual void OnQuitButton();

	virtual void OnLeftPushed();
	virtual void OnRightPushed();
	virtual void OnUpPushed();
	virtual void OnDownPushed();

	virtual int NextWallType();

	//for Singleton
	static inline CController& Instance()
	{
		static CController _controller;
		return _controller;
	}

protected:
	//for Singleton
	CController();
	virtual ~CController();
	CController(const CController& rhs);			//��ʵ��
	CController& operator=(const CController& rhs);	//��ʵ��


	//��ʼ�����ͼ��̵ļ���
	void InitKeyboardMouseListening();
	
	//����С�ɻ����ٶȡ�����˵�ǵ�ͼ���ٶȣ����ݵ�ǰ�Ѿ����˶�����
	void AdjustSpeed();

	//������Ļ�ϵ�����(window_x, window_y)������ά�������zֵ������������ά�������x��y
	//���ǿ���̫���ˣ������ò���
	void Unproject(int window_x, int window_y, GLdouble* pworld_x, GLdouble* pworld_y, GLdouble* pworld_z);

	//�ƶ��ɻ�������е�λ�ã��ƶ��ɹ�����true
	bool MovePlaneX(int offset);
	bool MovePlaneY(int offset);

	//ȥ��ͷһ������һ���ڵ������͡�
	void PopNextWallType();

	bool Collision(int wall_state, int plane_x, int plane_y, int radius);

	IGameData* m_pGameData;
	IViewEngine* m_pViewEngine;
	int m_state;	//��ǰ��Ϸ���߼�״̬: VW_STATE_*
	list<int> m_NextWallTypes;	//���������ڵ��������
};

#endif
