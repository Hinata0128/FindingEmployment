#include "CSceneBase.h"


// �R���X�g���N�^�̈������Q�ƂɕύX���A�Q�ƃ����o�[�����������܂�
CSceneBase::CSceneBase(CDirectX9& dx9, CDirectX11& dx11)
	: m_pMesh(nullptr)
	, m_dx9_ref(dx9)  // DirectX9�ւ̎Q�Ƃ�������
	, m_dx11_ref(dx11) // DirectX11�ւ̎Q�Ƃ�������
	, m_hWnd() // ���������X�g�Ńf�t�H���g������
	, m_Score(0)
	, m_Count(0)
{
	// �����ŎQ�ƃ����o�[���K�؂ɏ���������邽�߁A
	// �|�C���^�̑���͕s�v�ɂȂ�܂��B
}
