#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "module_interfaces.h"

/************************************************************************/
/* 总控制类，决定下一步动作                                             */
/************************************************************************/
class CController
{
public:
	CController();
	virtual ~CController();

protected:
	IGameData* m_pGameData;
	IViewEngine* m_pViewEngine;
};

#endif
