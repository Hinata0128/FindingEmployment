#include "CGame.h"
#include "Sound/CSoundManager.h"
#include <algorithm>    // std::min, std::max のために必要 (衝突応答のoverlap計算で使用)
#include "StaticMash/CStaticMeshManager.h"
#include "DirectX/CDirectX9.h"  // GetInstance() に必要
#include "DirectX/CDirectX11.h" // GetInstance() に必要
#include "SceneManager/CSceneManager.h" // CSceneManager::GetInstance() に必要


//コンストラクタ.
// 引数にDirectXインスタンスの参照を追加
CGame::CGame(HWND hWnd) // ここを修正
	: m_hWnd(hWnd)
	, m_mView()
	, m_mProj()

	, m_Camera()
	, m_Light()

	, m_pSpriteGround(nullptr)
{
	//スタティックメッシュマネージャーの構築
	// シングルトンインスタンスへの参照を直接渡す
	// dx9とdx11はコンストラクタ引数として渡されているので、そのまま使用します。
	CStaticMeshManager::GetInstance()->Create(); // ここを修正
}


//デストラクタ.
CGame::~CGame()
{
	// ここで何かオブジェクトを解放する場合は SAFE_DELETE を使用
}

//構築.
void CGame::Create()
{
}

//ロードデータ関数.
HRESULT CGame::LoadData()
{
	//サウンドデータの読み込み
	if (CSoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}
	// CSceneManagerのCreateにHWNDを渡す
	CSceneManager::GetInstance()->Create(m_hWnd);

	return S_OK;
}

//解放関数.
void CGame::Release()
{
	// CGame::~CGame() で一括して行われるため、
	// 明示的な Release 関数は通常不要ですが、残す場合は他のオブジェクトの解放をここに記述します。
}


//更新処理.
void CGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

void CGame::Draw()
{
	CSceneManager::GetInstance()->Drae(); // Typo: Draw() かもしれません
}

//カメラ関数.
void CGame::Camera()
{
	// 必要に応じてカメラロジックを実装
}
//プロジェクション関数.
void CGame::Projection()
{
	// 必要に応じてプロジェクションロジックを実装
}
//三人称カメラ.
void CGame::ThirdPersonCamera(
	CAMERA* pCamera, const D3DXVECTOR3& TagetPos, float TagetRotY)
{
	// 必要に応じて三人称カメラロジックを実装
}
