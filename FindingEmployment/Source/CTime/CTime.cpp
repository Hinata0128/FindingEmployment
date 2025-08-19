#include "CTime.h"

CTime::CTime()
	: m_TimeLimit	(0.f)
	, m_StartTime	()
{
	//コンストラクタにタイムリミットを宣言する.
	//ゲームクリア時間は30秒にセット.
	m_TimeLimit = 15.f;
	//開始時間を入手？
	m_StartTime = std::chrono::steady_clock::now();
}

CTime::~CTime()
{
	//破棄は今のとろしない.
}

void CTime::Update()
{
	//毎フレームでする場合はここに変数を書く.
}

float CTime::GetRemainingTime() const
{
	auto now = std::chrono::steady_clock::now();
	//時間を計算する.
	std::chrono::duration<float> elapsed = now - m_StartTime;
	float remaining = m_TimeLimit - elapsed.count();

	return (remaining > 0.f) ? remaining : 0.f;	//マイナスにはしない.
}

//時間切れかどうか.
bool CTime::IsTimeUp() const
{
	return GetRemainingTime() <= 0.f;
}

//タイムリミットを外部から設定.
void CTime::SetTimeLimit(float time)
{
	m_TimeLimit = time;
	//再スタート.
	m_StartTime = std::chrono::steady_clock::now();
}

float CTime::GetTimeLimit() const
{
	return m_TimeLimit;
}
