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

	virtual void Init();

	virtual IGameData* GetGameData();

	virtual void OnFireKeyClicked();
	virtual void OnMouseMoved(int from_x, int from_y, int to_x, int to_y);
	virtual void OnLeftClicked(int pos_x, int pos_y);

	virtual void OnTimerClick();

	virtual int GetState();

	virtual void OnStartButton();
	virtual void OnSettingButton();
	virtual void OnAboutButton();
	virtual void OnQuitButton();

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


	//初始化鼠标和键盘的监听
	void InitKeyboardMouseListening();


	IGameData* m_pGameData;
	IViewEngine* m_pViewEngine;
	int m_state;	//当前游戏的逻辑状态: VW_STATE_*
};

#endif
