#pragma once
#include "CTime/CTime.h"	//�^�C�}�[�N���X.

/*******************************************************************
*	�Q�[�����C���Ŏg�p���鎞�Ԃ̊Ǘ�.
**/

class CGameMainTime
{
public:
	CGameMainTime();
	~CGameMainTime();

	void Update();	//���t���[���X�V.
	void Draw();	//�`�悪����̂��킩��Ȃ������̂܂܂ɂ��Ă���

	//�^�C���A�b�v���ǂ���.
	bool IsTimeUp() const;

	//�^�C�}�[���ăX�^�[�g����.
	float GetRemainingTime();

	void SetTimeLimit(float time);


private:
	CTime m_Timer;	//���ۂ̎��ԑ���p�N���X.
};