#pragma once
#include <Windows.h>

//�N���X�̑O���錾.
class CDirectX9;
class CDirectX11;
class CGame;

/**************************************************
*	���C���N���X.
**/
class CMain
{
public:
	CMain();	//�R���X�g���N�^.
	~CMain();	//�f�X�g���N�^.

	void Update();		//�X�V����.
	// void Draw(); // ���̊֐���CMain.cpp�ŃR�����g�A�E�g����Ă��邽�߁A�s�v�ł���΂���������폜�ł��܂�
	HRESULT Create();	//�\�z����.
	HRESULT LoadData();	//�f�[�^���[�h����.
	void Release();		//�������.
	void Loop();		//���C�����[�v.

	//�E�B���h�E�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y,
		INT width, INT height);

private:
	//�E�B���h�E�֐��i���b�Z�[�W���̏����j.
	static LRESULT CALLBACK MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

private:
	HWND			m_hWnd;	//�E�B���h�E�n���h��.
	//CDirectX9* m_pDx9;	//DirectX9�Z�b�g�A�b�v�N���X
	//CDirectX11* m_pDx11;//DirectX11�Z�b�g�A�b�v�N���X.
	CGame* m_pGame;

#ifdef _DEBUG
	// ImGui�E�B�W�F�b�g�p�̕ϐ���錾
	float m_SomeFloatValue;
	bool m_bFeatureEnabled;
#endif // _DEBUG
};

// FPS (Frames Per Second) �̒�`��CMain.cpp�Ŏg���Ă��邽�߁A
// ��������`�ł���΁A�����ɒ�`��ǉ����邩�A�K�؂ȋ��ʃw�b�_�t�@�C���Ɉړ����Ă��������B
// ��:
// #define FPS 60
