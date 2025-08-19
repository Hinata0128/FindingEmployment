#pragma once
#include "StaticMash/CStaticMesh.h"
#include "DirectX/CDirectX9.h"  // CDirectX9の定義が必要になるためインクルード
#include "DirectX/CDirectX11.h"
#include "Sprite2D/CSprite2D.h"
#include "GameObject/UIObject/CUIObject.h"


/**********************************************************
*	基底クラス.
**/

class CSceneBase
{
public:
	// コンストラクタの引数をDirectXシングルトンインスタンスへの参照に変更
	CSceneBase(CDirectX9& dx9, CDirectX11& dx11);
	virtual ~CSceneBase() {}

	virtual void Initialize() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//メッシュを接続する.
	void AttachMesh(CStaticMesh& pMesh) {
		m_pMesh = &pMesh;
	}

protected:
	CStaticMesh* m_pMesh;
	// DirectX9とDirectX11はシングルトンなので、ここでのポインタは不要です。
	// 代わりに、以下のようにシングルトンインスタンスへの参照をメンバーとして保持し、
	// コンストラクタで初期化します。
	CDirectX9& m_dx9_ref;  // DirectX9への参照
	CDirectX11& m_dx11_ref; // DirectX11への参照


	//ウィンドウハンドル.
	HWND				m_hWnd;

	//カメラ情報.
	CAMERA				m_Camera;
	//ライト情報
	LIGHT				m_Light;

	//行列.
	D3DXMATRIX			m_mView;	//ビュー(カメラ)行列.
	D3DXMATRIX			m_mProj;	//射影（プロジェクション）行列.

	int m_Score;

	int m_Count;


};
