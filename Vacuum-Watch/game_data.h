#ifndef _VW_GAME_DATA_H_
#define _VW_GAME_DATA_H_

#include "module_interfaces.h"

/************************************************************************/
/* ���������Ϸ���� by Andriy                                           */
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
	int m_iCurrentStage;	//��ǰ����
	long m_lCurrentScore;	//��ǰ����

	int m_iTunnelRadius;	//����İ뾶
	int m_iTotalLength;		//������ܳ���
	int m_iTunnelStep;		//�������ÿ���߶�Զ
	int m_iCurrentLength;	//������е�ǰ�Ѿ������˶��پ���
};

#endif