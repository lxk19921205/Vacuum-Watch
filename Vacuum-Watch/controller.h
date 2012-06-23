#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "module_interfaces.h"

/************************************************************************/
/* 总控制类，决定下一步动作                                             */
/************************************************************************/
class CController : public IController
{
public:
	virtual void StartGame();

	virtual void InitKeyboardMouseListening();
	virtual void OnFireKeyClicked();
	virtual void OnMouseMoved(int from_x, int from_y, int to_x, int to_y);

	virtual void InitViewEngine();

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
	CController(const CController& rhs);			//不实现
	CController& operator=(const CController& rhs);	//不实现


	IGameData* m_pGameData;
	IViewEngine* m_pViewEngine;
};

#endif
