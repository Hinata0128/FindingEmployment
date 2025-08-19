#pragma once
#include <chrono>

/*********************************************
*	�^�C�}�[�N���X(���삾��)
**/

class CTime
{
public:
	CTime();
	~CTime();

	//�����ɍ���̎��Ԍv�����쐬����.
	void Update();

	//�c�莞�Ԃ̎擾.
	float GetRemainingTime() const;
	//�c�莞�Ԃ�0���H
	bool IsTimeUp() const;

public:
	//�Z�b�^�[�E�Q�b�^�[
	void SetTimeLimit(float time);
	float GetTimeLimit() const;
	
private:
	//�����o�ϐ�.
	float m_TimeLimit;	//��������.
	//�J�n����.
	std::chrono::steady_clock::time_point m_StartTime;
};