#include "CGameMainTime.h"

CGameMainTime::CGameMainTime()
{
	m_Timer.SetTimeLimit(15.f);
}

CGameMainTime::~CGameMainTime()
{
}

void CGameMainTime::Update()
{
	m_Timer.Update();
}

void CGameMainTime::Draw()
{
}

bool CGameMainTime::IsTimeUp() const
{
	return m_Timer.IsTimeUp();
}

float CGameMainTime::GetRemainingTime()
{
	return m_Timer.GetRemainingTime();
}

void CGameMainTime::SetTimeLimit(float time)
{
}
