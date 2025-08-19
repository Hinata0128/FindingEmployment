#pragma once
#include <crtdbg.h>//_ASSERT_EXPR()�ŕK�v.

//===========================================================
//	�}�N��.
//===========================================================

//���.
#define SAFE_RELEASE(p)	if(p!=nullptr){(p)->Release();(p)=nullptr;}
//�j��.
#define SAFE_DELETE(p) if(p!=nullptr){delete (p);(p)=nullptr;}
#define SAFE_DELETE_ARRAY(p)	\
{								\
	if(p!=nullptr){				\
		delete[] (p);			\
		(p) = nullptr;			\
	}							\
}

// SAFE_DELETE �}�N���̒�` (������`����Ă��Ȃ��ꍇ)
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=nullptr; } }
#endif

//ImGui�@���{��Ή�.
#define JAPANESE(str) reinterpret_cast<const char*>(u8##str)