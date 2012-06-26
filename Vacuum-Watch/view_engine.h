#ifndef _VW_VIEW_ENGINE_H_
#define _VW_VIEW_ENGINE_H_

#include <gl/GL.h>
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

	virtual void Init();
	virtual void StartDisplaying();
	
	virtual void OnLeftClicked(int pos_x, int pos_y);

	virtual void Redraw();

private:
	//在Init中调用，为OpenGL超级宝典中写的框架
	void SetupRC();

};

#endif
