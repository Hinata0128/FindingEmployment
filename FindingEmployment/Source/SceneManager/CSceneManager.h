#pragma once
#include "Scene/CSceneBase.h"
#include "Scene/CTitle/CTitle.h"      // コメントアウトされているが前方宣言は維持
#include "Scene/CGameMain/CGameMain.h"
#include "Scene/CGameOver/CGameOver.h" // コメントアウトされているが前方宣言は維持
#include "Scene/CEnding/CEnding.h"    // コメントアウトされているが前方宣言は維持
#include <memory>                     // std::unique_ptr に必要

//前方宣言 (CDirectX9, CDirectX11はGetInstace()経由でアクセスするため、直接のヘッダは不要)
class CDirectX9;
class CDirectX11;

/********************************************
*	シーンマネージャークラス.
**/

class CSceneManager
{
public:
	//シーンリストの列挙型.
	enum List
	{
		//Title,
		GameMain,
		//GameOver,
		//Ending,

		max,
	};

public:
	//シングルトンパターン
	static CSceneManager* GetInstance()
	{
		static CSceneManager s_Instance;
		return &s_Instance;
	}
	~CSceneManager();

	HRESULT Create(HWND hWnd);

	void Update();
	void Drae(); // Typo: Draw() かもしれません

	//シーン読み込み.
	void LoadScene(List Scene);

	//HWNDを取得.
	HWND GetHWND() const;
public:
	// DirectXはシングルトンなので、これらのセッターは不要になります
	// void SetDx11(CDirectX11* Dx11) { m_pDx11 = Dx11; }
	// void SetDx9(CDirectX9* pDx9) { m_pDx9 = pDx9; }
private:
	//シーン作成.
	void MakeScene(List Scene);
private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;

private:
	std::unique_ptr<CSceneBase> m_pScene;
	HWND m_hWnd;

	// DirectXはシングルトンなので、ここでのポインタは不要です
	// CDirectX11* m_pDx11;
	// CDirectX9*	m_pDx9;
};
