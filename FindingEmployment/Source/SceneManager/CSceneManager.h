#pragma once
#include "Scene/CSceneBase.h"
#include "Scene/CTitle/CTitle.h"      // �R�����g�A�E�g����Ă��邪�O���錾�͈ێ�
#include "Scene/CGameMain/CGameMain.h"
#include "Scene/CGameOver/CGameOver.h" // �R�����g�A�E�g����Ă��邪�O���錾�͈ێ�
#include "Scene/CEnding/CEnding.h"    // �R�����g�A�E�g����Ă��邪�O���錾�͈ێ�
#include <memory>                     // std::unique_ptr �ɕK�v

//�O���錾 (CDirectX9, CDirectX11��GetInstace()�o�R�ŃA�N�Z�X���邽�߁A���ڂ̃w�b�_�͕s�v)
class CDirectX9;
class CDirectX11;

/********************************************
*	�V�[���}�l�[�W���[�N���X.
**/

class CSceneManager
{
public:
	//�V�[�����X�g�̗񋓌^.
	enum List
	{
		//Title,
		GameMain,
		//GameOver,
		//Ending,

		max,
	};

public:
	//�V���O���g���p�^�[��
	static CSceneManager* GetInstance()
	{
		static CSceneManager s_Instance;
		return &s_Instance;
	}
	~CSceneManager();

	HRESULT Create(HWND hWnd);

	void Update();
	void Drae(); // Typo: Draw() ��������܂���

	//�V�[���ǂݍ���.
	void LoadScene(List Scene);

	//HWND���擾.
	HWND GetHWND() const;
public:
	// DirectX�̓V���O���g���Ȃ̂ŁA�����̃Z�b�^�[�͕s�v�ɂȂ�܂�
	// void SetDx11(CDirectX11* Dx11) { m_pDx11 = Dx11; }
	// void SetDx9(CDirectX9* pDx9) { m_pDx9 = pDx9; }
private:
	//�V�[���쐬.
	void MakeScene(List Scene);
private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;

private:
	std::unique_ptr<CSceneBase> m_pScene;
	HWND m_hWnd;

	// DirectX�̓V���O���g���Ȃ̂ŁA�����ł̃|�C���^�͕s�v�ł�
	// CDirectX11* m_pDx11;
	// CDirectX9*	m_pDx9;
};
