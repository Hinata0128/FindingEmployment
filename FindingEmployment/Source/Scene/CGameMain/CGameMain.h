#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/CSpriteObject/CSpriteObject.h"
#include "SceneManager/CSceneManager.h" // CSceneManagerの定義に必要

#include "GameObject/StaticMeshObject/CCharacter/Ground/CGround.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"
#include "DebugText/CDebugText.h" // CDebugTextの定義に必要
#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"
#include "StaticMash/CStaticMesh.h" // CStaticMeshの定義に必要

#include "CGameMainTime/CGameMainTime.h"

#include <vector>

#include "ImGui/CImGuiManager.h" // CImGuiManagerの定義に必要


/*********************************************
*	ゲームメイン画像クラス.
**/

class CGameMain
	: public CSceneBase
{
public:
	// コンストラクタの引数からDirectXポインタを削除
	CGameMain();
	~CGameMain() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

	HRESULT LoadData(); // これはもう内部で使わないので、もし外部から呼ばれないなら削除しても良い

	//カメラ関数.
	void Camera();
	//プロジェクション関数.
	void Projection();

	//三人称カメラ
	void ThirdPersonCamera(
		CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY);


	// ImGui描画の関数化
	void RightImGuiPos();
	void CameraImGuiPos();
private:

	CSprite3D* m_pSp3D;
	CSprite3D* m_pSpriteGround;
	CSprite3D* m_pSpriteExplosion;

	CStaticMesh* m_pStaticMeshGround;
	CStaticMesh* m_pStaticMeshRoboA;
	CStaticMesh* m_pStaticMeshRoboB;
	CStaticMesh* m_pStaticMeshBullet;
	CStaticMesh* m_pStaticMeshBSphere;
	CStaticMesh* m_pStaticMeshBBox;
	CStaticMesh* m_pStaticMeshWall;

	CStaticMesh* m_pGameMain;
	CSprite2D* m_pSpriteTitle;

	CStaticMeshObject* m_pStcMeshObj;

	CCharacter* m_pPlayer;

	CGround* m_pGround;
	CDebugText* m_pDbgText;

	CAMERA m_Camera;
	LIGHT m_Light;
	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;

	std::vector<LIGHT> m_Lights;

	CGameMainTime* m_pGameMainTime;

	CAMERA m_CameraFirstPerson;

	D3DXVECTOR3 m_debugLightPosition;
	D3DXVECTOR3 m_debugCameraPosition;
	D3DXVECTOR3 m_debugCameraLook;

	bool m_useFirstPersonCamera;
	bool m_IsBlockActive;

private:
};
