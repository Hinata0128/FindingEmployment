#pragma once
#include "StaticMash/CStaticMesh.h"
#include "DirectX/CDirectX9.h"  // CDirectX9�̒�`���K�v�ɂȂ邽�߃C���N���[�h
#include "DirectX/CDirectX11.h"
#include "Sprite2D/CSprite2D.h"
#include "GameObject/UIObject/CUIObject.h"


/**********************************************************
*	���N���X.
**/

class CSceneBase
{
public:
	// �R���X�g���N�^�̈�����DirectX�V���O���g���C���X�^���X�ւ̎Q�ƂɕύX
	CSceneBase(CDirectX9& dx9, CDirectX11& dx11);
	virtual ~CSceneBase() {}

	virtual void Initialize() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//���b�V����ڑ�����.
	void AttachMesh(CStaticMesh& pMesh) {
		m_pMesh = &pMesh;
	}

protected:
	CStaticMesh* m_pMesh;
	// DirectX9��DirectX11�̓V���O���g���Ȃ̂ŁA�����ł̃|�C���^�͕s�v�ł��B
	// ����ɁA�ȉ��̂悤�ɃV���O���g���C���X�^���X�ւ̎Q�Ƃ������o�[�Ƃ��ĕێ����A
	// �R���X�g���N�^�ŏ��������܂��B
	CDirectX9& m_dx9_ref;  // DirectX9�ւ̎Q��
	CDirectX11& m_dx11_ref; // DirectX11�ւ̎Q��


	//�E�B���h�E�n���h��.
	HWND				m_hWnd;

	//�J�������.
	CAMERA				m_Camera;
	//���C�g���
	LIGHT				m_Light;

	//�s��.
	D3DXMATRIX			m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX			m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.

	int m_Score;

	int m_Count;


};
