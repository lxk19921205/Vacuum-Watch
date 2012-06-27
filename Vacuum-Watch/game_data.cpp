#include "game_data.h"
#include "constants.h"

#include <iostream>
using std::cout;
using std::endl;


CGameData::CGameData()
	:m_iCurrentStage(VW_DATA_DEF_STAGE),
	m_lCurrentScore(VW_DATA_DEF_SCORE),
	m_iTunnelRadius(VW_DATA_DEF_TUNNEL_RADIUS),
	m_iTotalLength(VW_DATA_DEF_TUNNEL_LENGTH),
	m_iTunnelStep(VW_DATA_DEF_TUNNEL_STEP),
	m_iCurrentLength(0)
{
}

CGameData::~CGameData()
{
}


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 当前关卡操作                                                         */
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
/* 当前积分操作                                                         */
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

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 隧道之相关数据                                                        */
/************************************************************************/
bool CGameData::Step()
{
	m_iCurrentLength += m_iTunnelStep;
	if (m_iCurrentLength < m_iTotalLength)
	{
		return true;
	}
	else
	{
		m_iCurrentLength = m_iTotalLength;
		return false;
	}
}

int CGameData::GetStep()
{
	return this->m_iTunnelStep;
}

void CGameData::SetStep(int step)
{
	m_iTunnelStep = step;
}


int CGameData::GetCurrentLength()
{
	return this->m_iCurrentLength;
}

void CGameData::ResetCurrentLength()
{
	this->m_iCurrentLength = 0;
}

int CGameData::GetTotalLength()
{
	return this->m_iTotalLength;
}

void CGameData::SetTotalLength( int length )
{
	this->m_iTotalLength = length;
}

int CGameData::GetTunnelRadius()
{
	return this->m_iTunnelRadius;
}

int CGameData::GetPositionX()
{
	return this->m_PlanePosition.x;
}

void CGameData::SetPositionX( int x )
{
	this->m_PlanePosition.x = x;
}

int CGameData::GetPositionY()
{
	return this->m_PlanePosition.y;
}

void CGameData::SetPositionY( int y )
{
	this->m_PlanePosition.y = y;
}

bool CGameData::IsPlaneInside()
{
	return (m_PlanePosition.x * m_PlanePosition.x + m_PlanePosition.y * m_PlanePosition.y) < m_iTunnelRadius * m_iTunnelRadius;
}
