#include "CSceneManager.h"
#include "Sound/CSoundManager.h" // CSoundManager::Stop/PlayLoop �ɕK�v
#include "DirectX/CDirectX9.h"   // CDirectX9::GetInstance() �ɕK�v
#include "DirectX/CDirectX11.h"  // CDirectX11::GetInstance() �ɕK�v

// �R���X�g���N�^.
CSceneManager::CSceneManager()
	: m_pScene(nullptr)
	, m_hWnd()
	// m_pDx11 �� m_pDx9 �̓����o�[����폜���ꂽ���߁A�����ł̏������͕s�v
	//, m_pDx11	()
	//, m_pDx9	()
{

}

// �f�X�g���N�^.
CSceneManager::~CSceneManager()
{
	// unique_ptr �������I�� m_pScene ��������܂�
}

HRESULT CSceneManager::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	LoadScene(List::GameMain);
	return S_OK;
}

void CSceneManager::Update()
{
	if (m_pScene) // m_pScene���L���ȏꍇ�̂ݍX�V
	{
		m_pScene->Update();
	}
}

void CSceneManager::Drae() // Typo: Draw() ��������܂��񂪁A���̂܂܈ێ�
{
	if (m_pScene) // m_pScene���L���ȏꍇ�̂ݕ`��
	{
		m_pScene->Draw();
	}
}

void CSceneManager::LoadScene(List Scene)
{
	m_pScene.reset(); // ���݂̃V�[�������

	//�V�[���쐬.
	MakeScene(Scene);
	if (m_pScene) // �V�����V�[�����쐬���ꂽ�ꍇ�̂ݏ������ƍ\�z
	{
		m_pScene->Create();
	}
}

HWND CSceneManager::GetHWND() const
{
	return m_hWnd;
}

//�V�[���쐬.
void CSceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
		//case CSceneManager::Title:
		// CTitle�̃R���X�g���N�^��CDirectX9&��CDirectX11&���󂯎��悤�ɏC������Ă��邱�Ƃ�O��Ƃ��܂�
		//	m_pScene = std::make_unique<CTitle>(*CDirectX9::GetInstance(), *CDirectX11::GetInstance());
		//	//BGM���~�߂�.
		//	CSoundManager::Stop(CSoundManager::BGM_Over);
		//	CSoundManager::Stop(CSoundManager::BGM_Ending);
		//	//BGM�̃��[�v�Đ�.
		//	CSoundManager::PlayLoop(CSoundManager::BGM_Title);
		//	break;
	case CSceneManager::GameMain:
		// CGameMain�̃R���X�g���N�^��DirectX�C���X�^���X�𒼐ڎ󂯎��Ȃ��悤�ɏC���ς�
		m_pScene = std::make_unique<CGameMain>(); // �����Ȃ��ŌĂяo��
		//SE���~�߂�.
		//BGM���~�߂�.
		CSoundManager::Stop(CSoundManager::BGM_Title);
		//BGM�̃��[�v�Đ�.
		CSoundManager::PlayLoop(CSoundManager::BGM_Main);
		break;
		//case CSceneManager::GameOver:
		// CGameOver�̃R���X�g���N�^��CDirectX9&��CDirectX11&���󂯎��悤�ɏC������Ă��邱�Ƃ�O��Ƃ��܂�
		//	m_pScene = std::make_unique<CGameOver>(*CDirectX9::GetInstance(), *CDirectX11::GetInstance());
		//	//BGM���~�߂�.
		//	CSoundManager::Stop(CSoundManager::BGM_Main);
		//	//BGM���[�v.
		//	CSoundManager::PlayLoop(CSoundManager::BGM_Over);
		//	break;
		//case CSceneManager::Ending:
		// CEnding�̃R���X�g���N�^��CDirectX9&��CDirectX11&���󂯎��悤�ɏC������Ă��邱�Ƃ�O��Ƃ��܂�
		//	m_pScene = std::make_unique<CEnding>(*CDirectX9::GetInstance(), *CDirectX11::GetInstance());
		//	//BGM���~�߂�.
		//	CSoundManager::Stop(CSoundManager::BGM_Main);
		//	//BGM���[�v.
		//	CSoundManager::PlayLoop(CSoundManager::BGM_Ending);
		//	break;
	default:
		break;
	}
}
