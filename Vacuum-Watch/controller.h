#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "module_interfaces.h"
#include <gl/freeglut.h>
#include <list>

using std::list;

/************************************************************************/
/* 总控制类，决定下一步动作                                             */
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
	CController(const CController& rhs);			//不实现
	CController& operator=(const CController& rhs);	//不实现


	//初始化鼠标和键盘的监听
	void InitKeyboardMouseListening();
	
	//调整小飞机的速度、或者说是地图的速度，根据当前已经进了多少米
	void AdjustSpeed();

	//根据屏幕上的坐标(window_x, window_y)和在三维世界里的z值，来决定在三维世界里的x和y
	//但是开销太大了，现在用不到
	void Unproject(int window_x, int window_y, GLdouble* pworld_x, GLdouble* pworld_y, GLdouble* pworld_z);

	//移动飞机在隧道中的位置，移动成功返回true
	bool MovePlaneX(int offset);
	bool MovePlaneY(int offset);

	//去掉头一个“下一个遮挡板类型”
	void PopNextWallType();

	bool Collision(int wall_state, int plane_x, int plane_y, int radius);

	IGameData* m_pGameData;
	IViewEngine* m_pViewEngine;
	int m_state;	//当前游戏的逻辑状态: VW_STATE_*
	list<int> m_NextWallTypes;	//接下来的遮挡板的类型
};

#endif
