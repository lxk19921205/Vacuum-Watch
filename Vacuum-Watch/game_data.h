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

	virtual bool Step();

	virtual int GetTunnelRadius();

	virtual int GetCurrentLength();
	virtual void ResetCurrentLength();

	virtual int GetTotalLength();
	virtual void SetTotalLength(int length);

private:
	int m_iCurrentStage;	//当前关数
	long m_lCurrentScore;	//当前分数

	int m_iTunnelRadius;	//隧道的半径
	int m_iTotalLength;		//隧道的总长度
	int m_iTunnelStep;		//在隧道中每次走多远
	int m_iCurrentLength;	//在隧道中当前已经经历了多少距离
};

#endif