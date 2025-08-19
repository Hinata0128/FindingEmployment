#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/CSpriteObject/CSpriteObject.h"
#include "SceneManager/CSceneManager.h" // CSceneManager�̒�`�ɕK�v

#include "GameObject/StaticMeshObject/CCharacter/Ground/CGround.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"
#include "DebugText/CDebugText.h" // CDebugText�̒�`�ɕK�v
#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"
#include "StaticMash/CStaticMesh.h" // CStaticMesh�̒�`�ɕK�v

#include "CGameMainTime/CGameMainTime.h"

#include <vector>

#include "ImGui/CImGuiManager.h" // CImGuiManager�̒�`�ɕK�v


/*********************************************
*	�Q�[�����C���摜�N���X.
**/

class CGameMain
	: public CSceneBase
{
public:
	// �R���X�g���N�^�̈�������DirectX�|�C���^���폜
	CGameMain();
	~CGameMain() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

	HRESULT LoadData(); // ����͂��������Ŏg��Ȃ��̂ŁA�����O������Ă΂�Ȃ��Ȃ�폜���Ă��ǂ�

	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Projection();

	//�O�l�̃J����
	void ThirdPersonCamera(
		CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY);


	// ImGui�`��̊֐���
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
