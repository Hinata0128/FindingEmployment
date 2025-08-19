#pragma once
#include <chrono>

/*********************************************
*	タイマークラス(動作だけ)
**/

class CTime
{
public:
	CTime();
	~CTime();

	//ここに今回の時間計測を作成する.
	void Update();

	//残り時間の取得.
	float GetRemainingTime() const;
	//残り時間が0か？
	bool IsTimeUp() const;

public:
	//セッター・ゲッター
	void SetTimeLimit(float time);
	float GetTimeLimit() const;
	
private:
	//メンバ変数.
	float m_TimeLimit;	//制限時間.
	//開始時間.
	std::chrono::steady_clock::time_point m_StartTime;
};