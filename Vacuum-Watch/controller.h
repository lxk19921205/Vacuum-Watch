#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "module_interfaces.h"

/************************************************************************/
/* �ܿ����࣬������һ������                                             */
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
