#ifndef _VW_VIEW_ENGINE_H_
#define _VW_VIEW_ENGINE_H_

#include <gl/freeglut.h>
#include "module_interfaces.h"
#include "button.h"

/************************************************************************/
/* 专门用于使用OpenGL，展示游戏界面                                     */
/************************************************************************/
class CViewEngine : public IViewEngine
{
public:
	CViewEngine();
	virtual ~CViewEngine();

	virtual void Init(int* pargc, char** argv);
	virtual void StartDisplaying();
	
	virtual void OnLeftClicked(int pos_x, int pos_y);

	virtual void SetupRCMenu();
	virtual void SetupRCOngoing();
	virtual void SetupRCSetting();
	virtual void SetupRCAbout();
	virtual void SetupRCPaused();

private:
	//通用的SetupRC在此
	void SetupRC();

	//在Menu界面有几个button，初始化他们的位置等信息
	void InitMenuButtons();
};

#endif
