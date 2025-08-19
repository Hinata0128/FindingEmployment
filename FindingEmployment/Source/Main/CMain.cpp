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
#define DEBUG_WINDOWS_POSTING		// �E�B���h�E���f�o�b�O�p�̕\���ʒu�ɂ���.
#else
#define ENABLE_WINDOWS_CENTERING	//�E�B���h�E����ʒ����ŋN����L���ɂ���.
#endif

//�E�B���h�E����ʒ����ŋN����L���ɂ���.
//#define ENABLE_WINDOWS_CENTERING

//=================================================
//	�萔.
//=================================================
const TCHAR WND_TITLE[] = _T("�u���b�N�X���C�_�[");
const TCHAR APP_NAME[] = _T("Block Slider");


/********************************************************************************
*	���C���N���X.
**/
//=================================================
//	�R���X�g���N�^.
//=================================================
CMain::CMain()
//���������X�g.
	: m_hWnd(nullptr)
	//, m_pDx9(nullptr)
	//, m_pDx11(nullptr)
	, m_pGame(nullptr)
#ifdef _DEBUG
	// ImGui�E�B�W�F�b�g�p�̕ϐ��������� (CMain.h�ɐ錾���K�v�ł�)
	, m_SomeFloatValue(0.0f)
	, m_bFeatureEnabled(false)
#endif // _DEBUG
{
}


//=================================================
//	�f�X�g���N�^.
//=================================================
CMain::~CMain()
{
	SAFE_DELETE(m_pGame);
	// m_hWnd �� MsgProc �� DestroyWindow ����邩�A
	// �A�v���P�[�V�����I�����ɃV�X�e����������邽�߁A
	// �����ł� DeleteObject(m_hWnd) �͕s�v���A���邢�͖��������N�����\��������܂��B
	// �ʏ�A�E�B���h�E�n���h����DestroyWindow�ŉ������܂��B
	// DeleteObject��GDI�I�u�W�F�N�g�p�ł��B
#ifdef _DEBUG
	CImGuiManager::Relese(); // ImGui�̏I������
#endif // _DEBUG

}


//�X�V����.
void CMain::Update()
{
	// �o�b�N�o�b�t�@���N���A�ɂ��� (�`��̍ŏ���)
	CDirectX11::GetInstance()->ClearBackBuffer();

#ifdef _DEBUG
	// ImGui�̐V�����t���[�����J�n���� (�`��̑O��)
	CImGuiManager::NewFrameSetting();
#endif // _DEBUG

	//�X�V����.
	m_pGame->Update();

	//�`�揈��.
	m_pGame->Draw();

	// ImGui�̕`��. (�Q�[���̕`��̌�ɁAPresent�̑O��)
#ifdef _DEBUG
	CImGuiManager::Render();
#endif // _DEBUG

	//��ʂɕ\��.
	CDirectX11::GetInstance()->Present();
}

// CMain::Draw() �֐��͕s�v�ɂȂ�܂����B
// void CMain::Draw()
// {
// 	// ImGui�̕`��.
// #ifdef _DEBUG
// 	CImGuiManager::Render();
// #endif // _DEBUG
// }

//�\�z����.
HRESULT CMain::Create()
{
	//DirectX9�\�z.
	if (FAILED(CDirectX9::GetInstance()->Create(m_hWnd)))
	{
		return E_FAIL;
	}

	//DirectX11�\�z.
	// �V���O���g���C���X�^���X��Create���Ăяo��
	if (FAILED(CDirectX11::GetInstance()->Create(m_hWnd)))
	{
		return E_FAIL;
	}

#ifdef _DEBUG
	// ImGui�̏����� (DirectX11�̃f�o�C�X���쐬���ꂽ���)
	// CImGuiManager::Init �̓����� ImGui_ImplDX11_Init ��
	// ID3D11Device* �� ID3D11DeviceContext* ��n���Ă��邩�m�F���Ă��������B
	CImGuiManager::Init(m_hWnd);

#endif // _DEBUG

	//�Q�[���N���X�̃C���X�^���X����.
	m_pGame = new CGame(m_hWnd);

	//�Q�[���N���X�̍\�z�iLoad���܂߂�j.
	m_pGame->Create();

	return S_OK;
}

//�f�[�^���[�h����.
HRESULT CMain::LoadData()
{

	//�f�[�^���[�h����.
	m_pGame->LoadData();

	return S_OK;
}


//�������.
void CMain::Release()
{
	// ImGui�̏I�������̓f�X�g���N�^�ōs���邽�߁A�����ł�Dx�̉���̂݁B
	// �������AImGui�̉����Dx�̉���Ɉˑ�����ꍇ�́A������ImGui�̉�����ɌĂԂׂ��ł��B
	// ��ʓI�ɂ́AImGui�̉�� -> Dx�̉�� �̏������S�ł��B
	// CMain::~CMain() �� CImGuiManager::Relese() ���Ă΂�邽�߁A
	// Dx�̉����CMain::Release()�ŁAImGui�̉���̓f�X�g���N�^�ŁA�Ƃ������S�͉\�ł��B
	CDirectX11::GetInstance()->Release();
	CDirectX9::GetInstance()->Release();
}


//���b�Z�[�W���[�v.
void CMain::Loop()
{
	//�f�[�^���[�h.
	if (FAILED(LoadData())) {
		return;
	}

	//------------------------------------------------
	//	�t���[�����[�g��������.
	//------------------------------------------------
	float Rate = 0.0f;	//���[�g.
	DWORD sync_old = timeGetTime();			//�ߋ�����.
	DWORD sync_now;							//���ݎ���.

	//���ԏ����̂��߁A�ŏ��P�ʂ�1�~���b�ɕύX.
	timeBeginPeriod(1);
	Rate = 1000.0f / static_cast<float>(FPS); //���z���Ԃ��Z�o.

	//���b�Z�[�W���[�v.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		sync_now = timeGetTime();	//���݂̎��Ԃ��擾.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;	//���ݎ��Ԃɒu������.

			//�X�V����.
			Update(); // ������ImGui�̕`����s����悤�ɕύX
		}
	}
	//�A�v���P�[�V�����̏I��.
	Release();
}

//�E�B���h�E�������֐�.
HRESULT CMain::InitWindow(
	HINSTANCE hInstance,	//�C���X�^���X.
	INT x, INT y,			//�E�B���h�Ex,y���W.
	INT width, INT height)	//�E�B���h�E��,����.
{
	//�E�B���h�E�̒�`.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));//������(0��ݒ�).

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;//WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = APP_NAME;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	//�E�B���h�E�N���X��Windows�ɓo�^.
	if (!RegisterClassEx(&wc)) {
		_ASSERT_EXPR(false, _T("�E�B���h�E�N���X�̓o�^�Ɏ��s"));
		return E_FAIL;
	}

	//--------------------------------------.
	//	�E�B���h�E�\���ʒu�̒���.
	//--------------------------------------.
	//���̊֐����ł̂ݎg�p����\���̂������Œ�`.
	struct RECT_WND
	{
		INT x, y, w, h;
		RECT_WND() : x(), y(), w(), h() {}
	} rectWindow;//�����ɕϐ��錾������.

#ifdef ENABLE_WINDOWS_CENTERING
	//�f�B�X�v���C�̕��A�������擾.
	HWND hDeskWnd = nullptr;
	RECT recDisplay;
	hDeskWnd = GetDesktopWindow();
	GetWindowRect(hDeskWnd, &recDisplay);

	//�Z���^�����O.
	rectWindow.x = (recDisplay.right - width) / 2;	//�\���ʒux���W.
	rectWindow.y = (recDisplay.bottom - height) / 2;	//�\���ʒuy���W.
#endif//ENABLE_WINDOWS_CENTERING

	//--------------------------------------.
	//	�E�B���h�E�̈�̒���.
	//--------------------------------------.
	RECT	rect;		//��`�\����.
	DWORD	dwStyle;	//�E�B���h�E�X�^�C��.
	rect.top = 0;			//��.
	rect.left = 0;			//��.
	rect.right = width;		//�E.
	rect.bottom = height;	//��.
	dwStyle = WS_OVERLAPPEDWINDOW;	//�E�B���h�E���.

	if (AdjustWindowRect(
		&rect,			//(in)��ʃT�C�Y����������`�\����.(out)�v�Z����.
		dwStyle,		//�E�B���h�E�X�^�C��.
		FALSE) == 0)	//���j���[�������ǂ����̎w��.
	{
		MessageBox(
			nullptr,
			_T("�E�B���h�E�̈�̒����Ɏ��s"),
			_T("�G���[���b�Z�[�W"),
			MB_OK);
		return 0;
	}

	//�E�B���h�E�̕���������.
	rectWindow.w = rect.right - rect.left;
	rectWindow.h = rect.bottom - rect.top;

	//�E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(
		APP_NAME,					//�A�v����.
		WND_TITLE,					//�E�B���h�E�^�C�g��.
		dwStyle,					//�E�B���h�E���(����).
		rectWindow.x, rectWindow.y,	//�\���ʒux,y���W.
		rectWindow.w, rectWindow.h,	//�E�B���h�E��,����.
		nullptr,					//�e�E�B���h�E�n���h��.
		nullptr,					//���j���[�ݒ�.
		hInstance,					//�C���X�^���X�ԍ�.
		nullptr);					//�E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.
	if (!m_hWnd) {
		_ASSERT_EXPR(false, _T("�E�B���h�E�쐬���s"));
		return E_FAIL;
	}

	//�E�B���h�E�̕\��.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}



#ifdef _DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // _DEBUG

//�E�B���h�E�֐��i���b�Z�[�W���̏����j.
LRESULT CALLBACK CMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	// ImGui�E�B���h�E�̏���������(�h���b�O��X�N���[���Ȃ�).
	// ImGui�̏����́ADefWindowProc�̑O�ɌĂяo���̂���ʓI�ł��B
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		//return true; // ImGui�����b�Z�[�W������������ADefWindowProc�ɓn���Ȃ�
	}
#endif // _DEBUG
	switch (uMsg) {
	case WM_DESTROY://�E�B���h�E���j�����ꂽ�Ƃ�.
		//�A�v���P�[�V�����̏I����Windows�ɒʒm����.
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://�L�[�{�[�h�������ꂽ�Ƃ�.
		//�L�[�ʂ̏���.
		switch (static_cast<char>(wParam)) {
		case VK_ESCAPE:	//ESC��.
			//�E�B���h�E��j������.
			DestroyWindow(hWnd);
		}
		break;
	}

	//���C���ɕԂ����.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
