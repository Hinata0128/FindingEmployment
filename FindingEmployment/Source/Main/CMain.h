#pragma once
#include <Windows.h>

//クラスの前方宣言.
class CDirectX9;
class CDirectX11;
class CGame;

/**************************************************
*	メインクラス.
**/
class CMain
{
public:
	CMain();	//コンストラクタ.
	~CMain();	//デストラクタ.

	void Update();		//更新処理.
	// void Draw(); // この関数はCMain.cppでコメントアウトされているため、不要であればここからも削除できます
	HRESULT Create();	//構築処理.
	HRESULT LoadData();	//データロード処理.
	void Release();		//解放処理.
	void Loop();		//メインループ.

	//ウィンドウ初期化関数.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y,
		INT width, INT height);

private:
	//ウィンドウ関数（メッセージ毎の処理）.
	static LRESULT CALLBACK MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

private:
	HWND			m_hWnd;	//ウィンドウハンドル.
	//CDirectX9* m_pDx9;	//DirectX9セットアップクラス
	//CDirectX11* m_pDx11;//DirectX11セットアップクラス.
	CGame* m_pGame;

#ifdef _DEBUG
	// ImGuiウィジェット用の変数を宣言
	float m_SomeFloatValue;
	bool m_bFeatureEnabled;
#endif // _DEBUG
};

// FPS (Frames Per Second) の定義がCMain.cppで使われているため、
// もし未定義であれば、ここに定義を追加するか、適切な共通ヘッダファイルに移動してください。
// 例:
// #define FPS 60
