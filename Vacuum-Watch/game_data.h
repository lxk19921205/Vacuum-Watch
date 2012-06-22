#ifndef _VW_GAME_DATA_H_
#define _VW_GAME_DATA_H_

#include "module_interfaces.h"

/************************************************************************/
/* 管理各种游戏数据 by Andriy                                           */
/************************************************************************/
class CGameData : public IGameData
{
public:
	CGameData();
	virtual ~CGameData();

	virtual int GetCurrentStage();
	virtual void NextStage();
	virtual void ResetStage();

	virtual long GetCurrentScore();
	virtual void AddScore(long score);
	virtual void ResetScore();

private:
	int m_iCurrentStage;
	long m_lCurrentScore;
};

#endif