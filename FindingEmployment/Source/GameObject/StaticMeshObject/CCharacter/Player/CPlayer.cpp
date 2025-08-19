#include "CPlayer.h"
#include "Sound/CSoundManager.h"
#include "Collision/BoundingBox/BoundingBox.h"
#include "StaticMash/CStaticMeshManager.h"

CPlayer::CPlayer()
	: m_TurnSpeed	(0.1f)	//きっちりやりたい場合はラジアン値を設定すること.
	, m_MoveSpeed	(0.3f)
	, m_MoveState	(enMoveState::Stop)

	, m_vVelocity	(0.f,0.f,0.f)
	, m_JumpPower	(0.42f)
	, m_Gravity		(0.02f)
	, m_JumpFrag	(false)
	, m_GroundedFrag	(true)	//最初は地面にいてるから
{
	AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Player));
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	float delta_time	= 1.0f;
	float add_value		= 0.1f;
	// 左への移動
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
	{
		m_vPosition.x -= add_value;
	}
	// 右への移動
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
	{
		m_vPosition.x += add_value;
	}
#ifdef _DEBUG
	if (GetAsyncKeyState(VK_UP))
	{
		m_vPosition.z += add_value;
	}
if (GetAsyncKeyState(VK_DOWN))
	{
		m_vPosition.z += add_value;
	}
#endif

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_GroundedFrag) // 接地している場合のみジャンプ可能
		{
			CSoundManager::PlaySE(CSoundManager::SE_Jump);

			m_vVelocity.y = m_JumpPower; // Y軸にジャンプ力を与える
			m_JumpFrag = true;          // ジャンプ中フラグを立てる
			m_GroundedFrag = false;        // 地面から離れるので接地フラグを下ろす
		}
	}

	if (!m_GroundedFrag) // 接地していない場合のみ重力の影響を受ける
	{
		m_vVelocity.y -= m_Gravity * delta_time; // Y軸速度から重力を引く (Y軸上が正の場合)
	}
	m_vPosition.y += m_vVelocity.y * delta_time;

#if 0
	float add_value = 0.1f;
	if( GetAsyncKeyState( VK_UP ) & 0x8000 ){
		m_vPosition.y += add_value;
	}
	if( GetAsyncKeyState( VK_DOWN ) & 0x8000 ){
		m_vPosition.y -= add_value;
	}
	if( GetAsyncKeyState( VK_RIGHT ) & 0x8000 ){
		m_vPosition.x += add_value;
	}
	if( GetAsyncKeyState( VK_LEFT ) & 0x8000 ){
		m_vPosition.x -= add_value;
	}
#endif

	//前回のフレームで弾を飛ばしているかも知れないのでfalseにする
	m_Shot = false;

	//弾を飛ばしたい!
	if (GetAsyncKeyState('Z') & 0x8000) {
		m_Shot = true;
	}

	UpdateBBox(); // プレイヤーのAABBを更新
	UpdateBSpherePos(); // プレイヤーのBSphereを更新 (もし使うなら)


	CCharacter::Update();
}

void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CCharacter::Draw( View, Proj, Light, Camera );
}

void CPlayer::HandleGroundCollision(CStaticMeshObject* pGroundObject)
{
	BoundingBox* playerBBox = this->GetBBox();
	BoundingBox* groundBBox = pGroundObject->GetBBox();

	if (playerBBox == nullptr || groundBBox == nullptr) {
		return;
	}

	// プレイヤーのAABBの底が、地面のAABBのトップよりも下にある場合 (衝突している)
	if (playerBBox->GetMinPosition().y < groundBBox->GetMaxPosition().y) {
		float playerHalfHeight = (playerBBox->GetMaxPosition().y - playerBBox->GetMinPosition().y) / 2.0f;

		// プレイヤーの中心Y座標を、地面の最上部にプレイヤーの底が接するように調整
		this->SetPosition(m_vPosition.x, groundBBox->GetMaxPosition().y + playerHalfHeight, m_vPosition.z);

		//接地時の処理を追加
		// プレイヤーが下方向へ移動している（または静止している）場合のみ速度をリセット
		if (m_vVelocity.y < 0 || m_GroundedFrag) { // 下向き速度があるか、既に接地している場合
			m_vVelocity.y = 0.0f; // Y方向の速度をゼロにする
		}
		m_GroundedFrag = true;    // 接地フラグを立てる
		m_JumpFrag = false;    // ジャンプ中フラグを下ろす（着地したため）
	}
}