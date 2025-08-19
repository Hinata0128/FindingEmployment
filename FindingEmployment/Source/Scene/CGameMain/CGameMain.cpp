#include "CGameMain.h"
#include "Sound/CSoundManager.h"
#include "StaticMash/CStaticMeshManager.h" // CStaticMeshManager::GetInstance() に必要
#include "Collision/BoundingBox/BoundingBox.h"
#include "Collision/CBoundingSphere/CBoundingSphere.h"
#include "DirectX/CDirectX9.h"  // シングルトンのGetInstace()に必要
#include "DirectX/CDirectX11.h" // シングルトンのGetInstace()に必要
#include <algorithm>
#include <cfloat>
#include <cmath>

// SAFE_DELETE マクロの定義 (もし外部で定義されていない場合)
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if(x) { delete (x); (x)=nullptr; } }
#endif


// 日本語ImGui表示用のダミーマクロ (実際のImGuiには日本語フォント設定が必要)
#ifndef JAPANESE
#define JAPANESE(text) text
#endif


// コンストラクタ.
// CSceneBaseのコンストラクタにシングルトンインスタンスの参照を渡す
CGameMain::CGameMain()
	: CSceneBase(*CDirectX9::GetInstance(), *CDirectX11::GetInstance()) // ここを修正
	, m_pStcMeshObj(nullptr)
	, m_pStaticMeshGround(nullptr)
	, m_pSp3D(nullptr)
	, m_pSpriteGround(nullptr)
	, m_pSpriteExplosion(nullptr)
	, m_pStaticMeshRoboA(nullptr)
	, m_pStaticMeshRoboB(nullptr)
	, m_pStaticMeshBullet(nullptr)
	, m_pStaticMeshBSphere(nullptr)
	, m_pStaticMeshBBox(nullptr)
	, m_pStaticMeshWall(nullptr)

	, m_pGameMain(nullptr)
	, m_pSpriteTitle(nullptr)
	, m_pPlayer(nullptr)
	, m_pGround(nullptr)
	, m_pDbgText(nullptr)
	, m_pGameMainTime(nullptr)

	, m_debugLightPosition(0.f, 1.f, -1.f)
	, m_debugCameraPosition(0.0f, 5.0f, -5.0f)
	, m_debugCameraLook(0.0f, 2.0f, 5.0f)

	, m_useFirstPersonCamera(true)

	, m_IsBlockActive(false)
{
	// m_pDx11 と m_pDx9 はメンバー変数から削除されたため、ここでの代入は不要
	// m_pDx11 = pDx11;
	// m_pDx9 = pDx9;

	// CSceneBase::m_hWnd の初期化はCMainから行われるか、別途設定が必要
	// 現時点ではCSceneBaseはm_hWndをコンストラクタで受け取っていないため、
	// CGameMainでCSceneBaseのm_hWndを設定する必要があるかもしれません。
	// もし必要であれば、CGameMainのコンストラクタでhWndを受け取り、
	// CSceneBaseのコンストラクタに渡すか、SetHwnd()のような関数をCSceneBaseに追加してください。
	// このコードではCGameMainのコンストラクタからhWnd引数を削除しました。

	CStaticMeshManager::GetInstance()->Create(); // 引数なしで呼び出し

	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	m_Light.vDirection = D3DXVECTOR3(0.f, 1.f, -1.f); //ライト方向.

	Initialize();
}

// デストラクタ.
CGameMain::~CGameMain()
{
	SAFE_DELETE(m_pGround);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pStcMeshObj);

	SAFE_DELETE(m_pStaticMeshGround);
	SAFE_DELETE(m_pStaticMeshBullet);
	SAFE_DELETE(m_pStaticMeshBSphere);
	SAFE_DELETE(m_pStaticMeshBBox);
	SAFE_DELETE(m_pStaticMeshWall);
	SAFE_DELETE(m_pStaticMeshRoboA);
	SAFE_DELETE(m_pStaticMeshRoboB);

	SAFE_DELETE(m_pSp3D);
	SAFE_DELETE(m_pSpriteGround);
	SAFE_DELETE(m_pSpriteExplosion);
	SAFE_DELETE(m_pGameMain);
	SAFE_DELETE(m_pSpriteTitle);

	SAFE_DELETE(m_pDbgText);
	SAFE_DELETE(m_pGameMainTime);

	// Dxポインタはメンバーから削除されたため、nullptr初期化も不要
	// m_pDx11 = nullptr;
	// m_pDx9 = nullptr;
}

void CGameMain::Initialize()
{
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

void CGameMain::Create()
{
	m_pDbgText = new CDebugText();

	m_pStaticMeshGround = new CStaticMesh();
	m_pStaticMeshBullet = new CStaticMesh();
	m_pStaticMeshBSphere = new CStaticMesh();
	m_pStaticMeshBBox = new CStaticMesh();
	m_pStaticMeshWall = new CStaticMesh();

	m_pStcMeshObj = new CStaticMeshObject();

	m_pPlayer = new CPlayer();

	m_pGround = new CGround();

	m_pGameMainTime = new CGameMainTime();
	if (m_pGameMainTime)
	{
		m_pGameMainTime->SetTimeLimit(30.0f);
	}

	// CDebugText::Initにシングルトンインスタンスの参照を渡す
	if (FAILED(m_pDbgText->Init(*CDirectX11::GetInstance()))) // ここを修正
	{
		return;
	}

	// CStaticMesh::Initにシングルトンインスタンスの参照を渡す
	m_pStaticMeshGround->Init(*CDirectX9::GetInstance(), *CDirectX11::GetInstance(), _T("Data\\Mesh\\Static\\Ground\\box.x")); // ここを修正
	m_pStaticMeshBSphere->Init(*CDirectX9::GetInstance(), *CDirectX11::GetInstance(), _T("Data\\Collision\\Sphere.x"));    // ここを修正
	m_pStaticMeshBBox->Init(*CDirectX9::GetInstance(), *CDirectX11::GetInstance(), _T("Data\\Collision\\Box.x"));       // ここを修正
	m_pStaticMeshWall->Init(*CDirectX9::GetInstance(), *CDirectX11::GetInstance(), _T("Data\\Collision\\Box.x"));      // ここを修正


	const float STAGE_HALF_SIZE_X = 10.0f;
	const float STAGE_HALF_SIZE_Z = 100.0f;
	const float WALL_HEIGHT = 10.0f;
	const float WALL_THICKNESS = 0.5f;

	m_pGround->AttachMesh(*m_pStaticMeshGround);


	const float STAGE_FULL_SIZE_X = STAGE_HALF_SIZE_X * 2.0f;
	const float STAGE_FULL_SIZE_Z = STAGE_HALF_SIZE_Z * 2.0f;
	const float GROUND_THICKNESS = 0.5f;
	m_pGround->SetScale(STAGE_FULL_SIZE_X, GROUND_THICKNESS, STAGE_FULL_SIZE_Z);
	m_pGround->SetPosition(0.0f, -GROUND_THICKNESS / 2.0f, 0.0f);
	m_pGround->CreateBBoxForMesh(*m_pStaticMeshGround);

	m_pPlayer->SetPosition(0.f, 0.f, 13.f);
}

void CGameMain::Update()
{
	float delta_time = 1.0f / 60.0f;


	m_pGround->Update();
	m_pPlayer->Update();


	if (m_pGameMainTime)
	{
		m_pGameMainTime->Update();
	}

	m_pPlayer->UpdateBBox();
	m_pPlayer->UpdateBSpherePos();

	BoundingBox* playerBBox = m_pPlayer->GetBBox();
	BoundingBox* groundBBox = m_pGround->GetBBox();

	if (playerBBox && groundBBox)
	{
		float targetPlayerY = groundBBox->GetMaxPosition().y + (playerBBox->GetSize().y / 2.0f);
		CPlayer* playerInstance = dynamic_cast<CPlayer*>(m_pPlayer);

		if (playerInstance && playerInstance->GetPosition().y <= targetPlayerY + 0.01f && playerInstance->GetVelocity().y < 0)
		{
			D3DXVECTOR3 playerPos = playerInstance->GetPosition();
			playerPos.y = targetPlayerY;
			playerInstance->SetPosition(playerPos.x, playerPos.y, playerPos.z);
			playerInstance->SetVelocityY(0.0f);
			playerInstance->SetIsGrounded(true);
			playerInstance->SetIsJumping(false);
		}
	}



	if (m_useFirstPersonCamera)
	{
		D3DXVECTOR3 playerPos = m_pPlayer->GetPosition();
		float playerRotY = m_pPlayer->GetRotation().y;

		const float EYE_HEIGHT_OFFSET = 0.5f;

		m_Camera.vPosition = playerPos + D3DXVECTOR3(0.0f, EYE_HEIGHT_OFFSET, 0.0f);

		D3DXMATRIX mRotationY;
		D3DXMatrixRotationY(&mRotationY, playerRotY);

		D3DXVECTOR3 forwardVec(0.0f, 0.0f, 1.0f);
		D3DXVec3TransformCoord(&forwardVec, &forwardVec, &mRotationY);

		const float LOOK_DISTANCE = 1.0f;
		m_Camera.vLook = m_Camera.vPosition + forwardVec * LOOK_DISTANCE;

		m_Camera.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}


#ifdef _DEBUG
	RightImGuiPos();
	CameraImGuiPos();

	ImGui::Begin("Editor");

	static bool saved = false;
	static float save_message_timer = 0.0f; // メッセージ表示用のタイマー

	ImGui::End();
#endif //DEBUG
}

void CGameMain::Draw()
{
	Camera();
	Projection();

	m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
	m_pPlayer->Draw(m_mView, m_mProj, m_Light, m_Camera);

}

HRESULT CGameMain::LoadData()
{
	return S_OK;
}

void CGameMain::Camera()
{
	D3DXVECTOR3 cam_pos = m_Camera.vPosition;
	D3DXVECTOR3 cam_look = m_Camera.vLook;
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(
		&m_mView,
		&cam_pos, &cam_look, &vUpVec);
}

void CGameMain::Projection()
{
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;
	float far_z = 100.0f;

	D3DXMatrixPerspectiveFovLH(
		&m_mProj,
		fov_y,
		aspect,
		near_z,
		far_z);
}

void CGameMain::ThirdPersonCamera(CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY)
{
	D3DXVECTOR3 vecAxisZ(0.f, 0.f, 1.f);
	D3DXMATRIX mRotationY;
	D3DXMatrixRotationY(&mRotationY, TargetRotY);
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &mRotationY);

	pCamera->vPosition = TargetPos;
	pCamera->vLook = TargetPos;

	pCamera->vPosition -= vecAxisZ * 4.f;
	pCamera->vLook += vecAxisZ * 3.f;

	pCamera->vPosition.y += 1.f;
	pCamera->vLook.y += 0.5f;
}

void CGameMain::RightImGuiPos()
{
	ImGui::Begin("Light Settings");
	ImGui::Text(JAPANESE("ライト位置調整:"));
	ImGui::SliderFloat3(JAPANESE("位置"), (float*)&m_debugLightPosition, -10.0f, 10.0f, "X:%.1f Y:%.1f Z:%.1f");
	ImGui::End();

	m_Light.vDirection = m_debugLightPosition;
}

void CGameMain::CameraImGuiPos()
{
	ImGui::Begin("Camera Settings");
	ImGui::Text(JAPANESE("カメラモード:"));
	if (ImGui::Checkbox(JAPANESE("一人称カメラを有効にする"), &m_useFirstPersonCamera))
	{
		if (!m_useFirstPersonCamera) {
			m_debugCameraPosition = m_Camera.vPosition;
			m_debugCameraLook = m_Camera.vLook;
		}
	}

	if (!m_useFirstPersonCamera) {
		ImGui::Text(JAPANESE("カメラ位置調整 (デバッグモード):"));
		if (ImGui::SliderFloat3(JAPANESE("カメラ位置"), (float*)&m_debugCameraPosition, -30.f, 30.f, "X:%.1f Y:%.1f Z:%.1f"))
		{
			m_Camera.vPosition = m_debugCameraPosition;
		}

		ImGui::Text(JAPANESE("カメラ視点調整 (デバッグモード):"));
		if (ImGui::SliderFloat3(JAPANESE("カメラ視点"), (float*)&m_debugCameraLook, -30.f, 30.f, "X:%.1f Y:%.1f Z:%.1f"))
		{
			m_Camera.vLook = m_debugCameraLook;
		}
	}
	ImGui::End();
}
