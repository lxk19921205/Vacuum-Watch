#ifndef _VW_VIEW_ENGINE_H_
#define _VW_VIEW_ENGINE_H_

#include "module_interfaces.h"

/************************************************************************/
/* 专门用于使用OpenGL，展示游戏界面                                     */
/************************************************************************/
class CViewEngine : public IViewEngine
{
public:
	CViewEngine();
	virtual ~CViewEngine();
};

#endif
