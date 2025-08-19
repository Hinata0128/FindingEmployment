#include "CTime.h"

CTime::CTime()
	: m_TimeLimit	(0.f)
	, m_StartTime	()
{
	//�R���X�g���N�^�Ƀ^�C�����~�b�g��錾����.
	//�Q�[���N���A���Ԃ�30�b�ɃZ�b�g.
	m_TimeLimit = 15.f;
	//�J�n���Ԃ����H
	m_StartTime = std::chrono::steady_clock::now();
}

CTime::~CTime()
{
	//�j���͍��̂Ƃ낵�Ȃ�.
}

void CTime::Update()
{
	//���t���[���ł���ꍇ�͂����ɕϐ�������.
}

float CTime::GetRemainingTime() const
{
	auto now = std::chrono::steady_clock::now();
	//���Ԃ��v�Z����.
	std::chrono::duration<float> elapsed = now - m_StartTime;
	float remaining = m_TimeLimit - elapsed.count();

	return (remaining > 0.f) ? remaining : 0.f;	//�}�C�i�X�ɂ͂��Ȃ�.
}

//���Ԑ؂ꂩ�ǂ���.
bool CTime::IsTimeUp() const
{
	return GetRemainingTime() <= 0.f;
}

//�^�C�����~�b�g���O������ݒ�.
void CTime::SetTimeLimit(float time)
{
	m_TimeLimit = time;
	//�ăX�^�[�g.
	m_StartTime = std::chrono::steady_clock::now();
}

float CTime::GetTimeLimit() const
{
	return m_TimeLimit;
}
