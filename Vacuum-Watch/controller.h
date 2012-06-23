#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "module_interfaces.h"

/************************************************************************/
/* �ܿ����࣬������һ������                                             */
/************************************************************************/
class CController : public IController
{
public:
	virtual void StartGame();

	virtual void Init();

	virtual void OnFireKeyClicked();
	virtual void OnMouseMoved(int from_x, int from_y, int to_x, int to_y);


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


	IGameData* m_pGameData;
	IViewEngine* m_pViewEngine;
};

#endif
