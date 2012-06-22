#ifndef _VW_CONTROLLER_H_
#define _VW_CONTROLLER_H_

#include "game_data.h"
#include "view_engine.h"

/************************************************************************/
/* �ܿ����࣬������һ������                                             */
/************************************************************************/
class CController
{
public:
	CController();
	virtual ~CController();

protected:
	CGameData* m_pGameData;
	CViewEngine* m_pViewEngine;
};

#endif
