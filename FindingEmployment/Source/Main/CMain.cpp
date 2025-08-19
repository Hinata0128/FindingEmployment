#include "CMain.h"
#include "DirectX//CDirectX9.h"
#include "DirectX//CDirectX11.h"
#include "Game//CGame.h"

#ifdef _DEBUG
#include <crtdbg.h>
#include "ImGui//CImGuiManager.h"
#include "ImGui/Library/imgui.h"
#endif


#ifdef _DEBUG
#define DEBUG_WINDOWS_POSTING		// ウィンドウをデバッグ用の表示位置にする.
#else
#define ENABLE_WINDOWS_CENTERING	//ウィンドウを画面中央で起動を有効にする.
#endif

//ウィンドウを画面中央で起動を有効にする.
//#define ENABLE_WINDOWS_CENTERING

//=================================================
//	定数.
//=================================================
const TCHAR WND_TITLE[] = _T("ブロックスライダー");
const TCHAR APP_NAME[] = _T("Block Slider");


/********************************************************************************
*	メインクラス.
**/
//=================================================
//	コンストラクタ.
//=================================================
CMain::CMain()
//初期化リスト.
	: m_hWnd(nullptr)
	//, m_pDx9(nullptr)
	//, m_pDx11(nullptr)
	, m_pGame(nullptr)
#ifdef _DEBUG
	// ImGuiウィジェット用の変数を初期化 (CMain.hに宣言が必要です)
	, m_SomeFloatValue(0.0f)
	, m_bFeatureEnabled(false)
#endif // _DEBUG
{
}


//=================================================
//	デストラクタ.
//=================================================
CMain::~CMain()
{
	SAFE_DELETE(m_pGame);
	// m_hWnd は MsgProc で DestroyWindow されるか、
	// アプリケーション終了時にシステムが解放するため、
	// ここでの DeleteObject(m_hWnd) は不要か、あるいは問題を引き起こす可能性があります。
	// 通常、ウィンドウハンドルはDestroyWindowで解放されます。
	// DeleteObjectはGDIオブジェクト用です。
#ifdef _DEBUG
	CImGuiManager::Relese(); // ImGuiの終了処理
#endif // _DEBUG

}


//更新処理.
void CMain::Update()
{
	// バックバッファをクリアにする (描画の最初に)
	CDirectX11::GetInstance()->ClearBackBuffer();

#ifdef _DEBUG
	// ImGuiの新しいフレームを開始する (描画の前に)
	CImGuiManager::NewFrameSetting();
#endif // _DEBUG

	//更新処理.
	m_pGame->Update();

	//描画処理.
	m_pGame->Draw();

	// ImGuiの描画. (ゲームの描画の後に、Presentの前に)
#ifdef _DEBUG
	CImGuiManager::Render();
#endif // _DEBUG

	//画面に表示.
	CDirectX11::GetInstance()->Present();
}

// CMain::Draw() 関数は不要になりました。
// void CMain::Draw()
// {
// 	// ImGuiの描画.
// #ifdef _DEBUG
// 	CImGuiManager::Render();
// #endif // _DEBUG
// }

//構築処理.
HRESULT CMain::Create()
{
	//DirectX9構築.
	if (FAILED(CDirectX9::GetInstance()->Create(m_hWnd)))
	{
		return E_FAIL;
	}

	//DirectX11構築.
	// シングルトンインスタンスのCreateを呼び出す
	if (FAILED(CDirectX11::GetInstance()->Create(m_hWnd)))
	{
		return E_FAIL;
	}

#ifdef _DEBUG
	// ImGuiの初期化 (DirectX11のデバイスが作成された後に)
	// CImGuiManager::Init の内部で ImGui_ImplDX11_Init に
	// ID3D11Device* と ID3D11DeviceContext* を渡しているか確認してください。
	CImGuiManager::Init(m_hWnd);

#endif // _DEBUG

	//ゲームクラスのインスタンス生成.
	m_pGame = new CGame(m_hWnd);

	//ゲームクラスの構築（Loadも含める）.
	m_pGame->Create();

	return S_OK;
}

//データロード処理.
HRESULT CMain::LoadData()
{

	//データロード処理.
	m_pGame->LoadData();

	return S_OK;
}


//解放処理.
void CMain::Release()
{
	// ImGuiの終了処理はデストラクタで行われるため、ここではDxの解放のみ。
	// ただし、ImGuiの解放がDxの解放に依存する場合は、ここでImGuiの解放を先に呼ぶべきです。
	// 一般的には、ImGuiの解放 -> Dxの解放 の順が安全です。
	// CMain::~CMain() で CImGuiManager::Relese() が呼ばれるため、
	// Dxの解放はCMain::Release()で、ImGuiの解放はデストラクタで、という分担は可能です。
	CDirectX11::GetInstance()->Release();
	CDirectX9::GetInstance()->Release();
}


//メッセージループ.
void CMain::Loop()
{
	//データロード.
	if (FAILED(LoadData())) {
		return;
	}

	//------------------------------------------------
	//	フレームレート調整準備.
	//------------------------------------------------
	float Rate = 0.0f;	//レート.
	DWORD sync_old = timeGetTime();			//過去時間.
	DWORD sync_now;							//現在時間.

	//時間処理のため、最小単位を1ミリ秒に変更.
	timeBeginPeriod(1);
	Rate = 1000.0f / static_cast<float>(FPS); //理想時間を算出.

	//メッセージループ.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		sync_now = timeGetTime();	//現在の時間を取得.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;	//現在時間に置き換え.

			//更新処理.
			Update(); // ここでImGuiの描画も行われるように変更
		}
	}
	//アプリケーションの終了.
	Release();
}

//ウィンドウ初期化関数.
HRESULT CMain::InitWindow(
	HINSTANCE hInstance,	//インスタンス.
	INT x, INT y,			//ウィンドウx,y座標.
	INT width, INT height)	//ウィンドウ幅,高さ.
{
	//ウィンドウの定義.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));//初期化(0を設定).

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;//WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = APP_NAME;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	//ウィンドウクラスをWindowsに登録.
	if (!RegisterClassEx(&wc)) {
		_ASSERT_EXPR(false, _T("ウィンドウクラスの登録に失敗"));
		return E_FAIL;
	}

	//--------------------------------------.
	//	ウィンドウ表示位置の調整.
	//--------------------------------------.
	//この関数内でのみ使用する構造体をここで定義.
	struct RECT_WND
	{
		INT x, y, w, h;
		RECT_WND() : x(), y(), w(), h() {}
	} rectWindow;//ここに変数宣言もする.

#ifdef ENABLE_WINDOWS_CENTERING
	//ディスプレイの幅、高さを取得.
	HWND hDeskWnd = nullptr;
	RECT recDisplay;
	hDeskWnd = GetDesktopWindow();
	GetWindowRect(hDeskWnd, &recDisplay);

	//センタリング.
	rectWindow.x = (recDisplay.right - width) / 2;	//表示位置x座標.
	rectWindow.y = (recDisplay.bottom - height) / 2;	//表示位置y座標.
#endif//ENABLE_WINDOWS_CENTERING

	//--------------------------------------.
	//	ウィンドウ領域の調整.
	//--------------------------------------.
	RECT	rect;		//矩形構造体.
	DWORD	dwStyle;	//ウィンドウスタイル.
	rect.top = 0;			//上.
	rect.left = 0;			//左.
	rect.right = width;		//右.
	rect.bottom = height;	//下.
	dwStyle = WS_OVERLAPPEDWINDOW;	//ウィンドウ種別.

	if (AdjustWindowRect(
		&rect,			//(in)画面サイズが入った矩形構造体.(out)計算結果.
		dwStyle,		//ウィンドウスタイル.
		FALSE) == 0)	//メニューを持つかどうかの指定.
	{
		MessageBox(
			nullptr,
			_T("ウィンドウ領域の調整に失敗"),
			_T("エラーメッセージ"),
			MB_OK);
		return 0;
	}

	//ウィンドウの幅高さ調節.
	rectWindow.w = rect.right - rect.left;
	rectWindow.h = rect.bottom - rect.top;

	//ウィンドウの作成.
	m_hWnd = CreateWindow(
		APP_NAME,					//アプリ名.
		WND_TITLE,					//ウィンドウタイトル.
		dwStyle,					//ウィンドウ種別(普通).
		rectWindow.x, rectWindow.y,	//表示位置x,y座標.
		rectWindow.w, rectWindow.h,	//ウィンドウ幅,高さ.
		nullptr,					//親ウィンドウハンドル.
		nullptr,					//メニュー設定.
		hInstance,					//インスタンス番号.
		nullptr);					//ウィンドウ作成時に発生するイベントに渡すデータ.
	if (!m_hWnd) {
		_ASSERT_EXPR(false, _T("ウィンドウ作成失敗"));
		return E_FAIL;
	}

	//ウィンドウの表示.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}



#ifdef _DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // _DEBUG

//ウィンドウ関数（メッセージ毎の処理）.
LRESULT CALLBACK CMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	// ImGuiウィンドウの処理をする(ドラッグやスクロールなど).
	// ImGuiの処理は、DefWindowProcの前に呼び出すのが一般的です。
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		//return true; // ImGuiがメッセージを処理したら、DefWindowProcに渡さない
	}
#endif // _DEBUG
	switch (uMsg) {
	case WM_DESTROY://ウィンドウが破棄されたとき.
		//アプリケーションの終了をWindowsに通知する.
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キーボードが押されたとき.
		//キー別の処理.
		switch (static_cast<char>(wParam)) {
		case VK_ESCAPE:	//ESCｷｰ.
			//ウィンドウを破棄する.
			DestroyWindow(hWnd);
		}
		break;
	}

	//メインに返す情報.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
