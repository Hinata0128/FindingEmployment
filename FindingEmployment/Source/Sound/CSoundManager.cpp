#include "CSoundManager.h"
#include "MyMacro.h"

CSoundManager::CSoundManager()
	: m_pSound()
{
	//インスタンス生成.
	for (int i = 0; i < enList::max; i++)
	{
		m_pSound[i] = new CSound();
	}
}

CSoundManager::~CSoundManager()
{
	Release();

	//インスタンス破棄.
	for (int i = enList::max - 1; i >= 0; i--)
	{
		SAFE_DELETE(m_pSound[i]);
	}
}

//サウンドデータ読込関数.
bool CSoundManager::Load(HWND hWnd)
{
	struct SoundList
	{
		int listNo;				//enList列挙型を設定.
		const TCHAR path[256];	//ファイルの名前(パス付き).
		const TCHAR alias[32];	//エイリアス名.
	};
	SoundList SList[] =
	{
		{ enList::BGM_Ending,	_T("Data\\Sound\\BGM\\ending.mp3"),			_T("BGM_End")},
		{ enList::BGM_Over,		_T("Data\\Sound\\BGM\\gameover.mp3"),		_T("BGM_Over")},
		{ enList::BGM_Main,		_T("Data\\Sound\\BGM\\gamemain.mp3"),		_T("BGM_Main")},
		{ enList::BGM_Title,	_T("Data\\Sound\\BGM\\title.mp3"),			_T("BGM_Title")},
		{ enList::SE_Jump,		_T("Data\\Sound\\SE\\Jump.mp3"),			_T("SE_Jump")},
		{ enList::SE_Exp,		_T("Data\\Sound\\SE\\explosion.mp3"),			_T("SE_Exp")},
		{ enList::SE_Click,		_T("Data\\Sound\\SE\\Enter.mp3"),			_T("SE_Click")},
		{ enList::SE_Ending,		_T("Data\\Sound\\SE\\Hanabi.mp3"),			_T("SE_Hanabi")},

	};
	//配列の最大要素数を算出 (配列全体のサイズ/配列1つ分のサイズ).
	int list_max = sizeof(SList) / sizeof(SList[0]);
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSound[SList[i].listNo]->Open(
			SList[i].path,
			SList[i].alias,
			hWnd) == false)
		{
			return false;
		}
	}

	return true;
}

//サウンドデータ解放関数.
void CSoundManager::Release()
{
	//開いた時と逆順で閉じる.
	for (int i = enList::max - 1; i >= 0; i--)
	{
		if (m_pSound[i] != nullptr)
		{
			m_pSound[i]->Close();
		}
	}
}
