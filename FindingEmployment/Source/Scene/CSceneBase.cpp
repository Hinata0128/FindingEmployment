#include "CSceneBase.h"


// コンストラクタの引数を参照に変更し、参照メンバーを初期化します
CSceneBase::CSceneBase(CDirectX9& dx9, CDirectX11& dx11)
	: m_pMesh(nullptr)
	, m_dx9_ref(dx9)  // DirectX9への参照を初期化
	, m_dx11_ref(dx11) // DirectX11への参照を初期化
	, m_hWnd() // 初期化リストでデフォルト初期化
	, m_Score(0)
	, m_Count(0)
{
	// ここで参照メンバーが適切に初期化されるため、
	// ポインタの代入は不要になります。
}
