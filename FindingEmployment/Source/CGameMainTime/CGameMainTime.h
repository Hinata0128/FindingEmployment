#pragma once
#include "CTime/CTime.h"	//タイマークラス.

/*******************************************************************
*	ゲームメインで使用する時間の管理.
**/

class CGameMainTime
{
public:
	CGameMainTime();
	~CGameMainTime();

	void Update();	//毎フレーム更新.
	void Draw();	//描画がいるのかわからないがこのままにしておく

	//タイムアップかどうか.
	bool IsTimeUp() const;

	//タイマーを再スタートする.
	float GetRemainingTime();

	void SetTimeLimit(float time);


private:
	CTime m_Timer;	//実際の時間測定用クラス.
};