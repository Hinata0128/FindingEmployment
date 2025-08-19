#pragma once
#include <crtdbg.h>//_ASSERT_EXPR()で必要.

//===========================================================
//	マクロ.
//===========================================================

//解放.
#define SAFE_RELEASE(p)	if(p!=nullptr){(p)->Release();(p)=nullptr;}
//破棄.
#define SAFE_DELETE(p) if(p!=nullptr){delete (p);(p)=nullptr;}
#define SAFE_DELETE_ARRAY(p)	\
{								\
	if(p!=nullptr){				\
		delete[] (p);			\
		(p) = nullptr;			\
	}							\
}

// SAFE_DELETE マクロの定義 (もし定義されていない場合)
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=nullptr; } }
#endif

//ImGui　日本語対応.
#define JAPANESE(str) reinterpret_cast<const char*>(u8##str)