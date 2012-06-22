#include "game_data.h"
#include "constants.h"



CGameData::CGameData()
	:m_iCurrentStage(VW_DATA_DEF_STAGE),
	m_lCurrentScore(VW_DATA_DEF_SCORE)
{
}

CGameData::~CGameData()
{
}


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ��ǰ�ؿ�����                                                         */
/************************************************************************/

int CGameData::GetCurrentStage()
{
	return this->m_iCurrentStage;
}

void CGameData::NextStage()
{
	++this->m_iCurrentStage;
	if (this->m_iCurrentStage > VW_DATA_MAX_STAGE)
	{
		this->m_iCurrentStage = VW_DATA_MAX_STAGE;
	}
}

void CGameData::ResetStage()
{
	this->m_iCurrentStage = VW_DATA_DEF_STAGE;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ��ǰ���ֲ���                                                         */
/************************************************************************/

long CGameData::GetCurrentScore()
{
	return this->m_lCurrentScore;
}

void CGameData::AddScore( long score )
{
	this->m_lCurrentScore += score;
}

void CGameData::ResetScore()
{
	this->m_lCurrentScore = VW_DATA_DEF_SCORE;
}
//////////////////////////////////////////////////////////////////////////
