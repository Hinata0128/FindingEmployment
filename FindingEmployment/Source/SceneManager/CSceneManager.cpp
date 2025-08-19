#include "CSceneManager.h"
#include "Sound/CSoundManager.h" // CSoundManager::Stop/PlayLoop に必要
#include "DirectX/CDirectX9.h"   // CDirectX9::GetInstance() に必要
#include "DirectX/CDirectX11.h"  // CDirectX11::GetInstance() に必要

// コンストラクタ.
CSceneManager::CSceneManager()
	: m_pScene(nullptr)
	, m_hWnd()
	// m_pDx11 と m_pDx9 はメンバーから削除されたため、ここでの初期化は不要
	//, m_pDx11	()
	//, m_pDx9	()
{

}

// デストラクタ.
CSceneManager::~CSceneManager()
{
	// unique_ptr が自動的に m_pScene を解放します
}

HRESULT CSceneManager::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	LoadScene(List::GameMain);
	return S_OK;
}

void CSceneManager::Update()
{
	if (m_pScene) // m_pSceneが有効な場合のみ更新
	{
		m_pScene->Update();
	}
}

void CSceneManager::Drae() // Typo: Draw() かもしれませんが、元のまま維持
{
	if (m_pScene) // m_pSceneが有効な場合のみ描画
	{
		m_pScene->Draw();
	}
}

void CSceneManager::LoadScene(List Scene)
{
	m_pScene.reset(); // 現在のシーンを解放

	//シーン作成.
	MakeScene(Scene);
	if (m_pScene) // 新しいシーンが作成された場合のみ初期化と構築
	{
		m_pScene->Create();
	}
}

HWND CSceneManager::GetHWND() const
{
	return m_hWnd;
}

//シーン作成.
void CSceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
		//case CSceneManager::Title:
		// CTitleのコンストラクタがCDirectX9&とCDirectX11&を受け取るように修正されていることを前提とします
		//	m_pScene = std::make_unique<CTitle>(*CDirectX9::GetInstance(), *CDirectX11::GetInstance());
		//	//BGMを止める.
		//	CSoundManager::Stop(CSoundManager::BGM_Over);
		//	CSoundManager::Stop(CSoundManager::BGM_Ending);
		//	//BGMのループ再生.
		//	CSoundManager::PlayLoop(CSoundManager::BGM_Title);
		//	break;
	case CSceneManager::GameMain:
		// CGameMainのコンストラクタはDirectXインスタンスを直接受け取らないように修正済み
		m_pScene = std::make_unique<CGameMain>(); // 引数なしで呼び出し
		//SEを止める.
		//BGMを止める.
		CSoundManager::Stop(CSoundManager::BGM_Title);
		//BGMのループ再生.
		CSoundManager::PlayLoop(CSoundManager::BGM_Main);
		break;
		//case CSceneManager::GameOver:
		// CGameOverのコンストラクタがCDirectX9&とCDirectX11&を受け取るように修正されていることを前提とします
		//	m_pScene = std::make_unique<CGameOver>(*CDirectX9::GetInstance(), *CDirectX11::GetInstance());
		//	//BGMを止める.
		//	CSoundManager::Stop(CSoundManager::BGM_Main);
		//	//BGMループ.
		//	CSoundManager::PlayLoop(CSoundManager::BGM_Over);
		//	break;
		//case CSceneManager::Ending:
		// CEndingのコンストラクタがCDirectX9&とCDirectX11&を受け取るように修正されていることを前提とします
		//	m_pScene = std::make_unique<CEnding>(*CDirectX9::GetInstance(), *CDirectX11::GetInstance());
		//	//BGMを止める.
		//	CSoundManager::Stop(CSoundManager::BGM_Main);
		//	//BGMループ.
		//	CSoundManager::PlayLoop(CSoundManager::BGM_Ending);
		//	break;
	default:
		break;
	}
}
