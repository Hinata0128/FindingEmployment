#pragma once

#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"


/**************************************************
*	プレイヤークラス.
**/
class CPlayer
	: public CCharacter	//キャラクタークラスを継承.
{
public:
	//移動状態列挙型
	enum enMoveState
	{
		Stop = 0,	//停止
		Forward,	//前進
		Backward,	//後退
		TurnLeft,	//左回転
		TurnRight,	//右回転
	};
public:
	CPlayer();
	virtual ~CPlayer() override;

	virtual void Update() override;
	virtual void Draw(
		D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	void HandleGroundCollision(CStaticMeshObject* pGroundObject);

	void SetVelocity(const D3DXVECTOR3& velocity) { m_vVelocity = velocity; }
	D3DXVECTOR3 GetVelocity() const { return m_vVelocity; } // 速度取得関数も便利
	void SetVelocityY(float y) { m_vVelocity.y = y; } // Y速度のみ設定

	void SetIsJumping(bool jumping) { m_JumpFrag = jumping; }
	bool IsJumping() const { return m_JumpFrag; }

	void SetIsGrounded(bool grounded) { m_GroundedFrag = grounded; }
	bool IsGrounded() const { return m_GroundedFrag; }

protected:
	float		m_TurnSpeed;	//回転速度.
	float		m_MoveSpeed;	//移動速度.
	enMoveState m_MoveState;	//移動状態.

	D3DXVECTOR3 m_vVelocity;
	float       m_JumpPower;    // ジャンプの初速度.
	float       m_Gravity;      // 重力加速度
	bool        m_JumpFrag;    // ジャンプ中フラグ
	bool        m_GroundedFrag;   // 接地中フラグ (HandleGroundCollisionで設定)
};