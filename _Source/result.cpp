//------------------------------------------------------------------------------
//	タイトル：		リザルトの関数
//	ファイル名：	result.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/07/11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "UI.h"
#include "openAL.h"
#include "fade.h"
#include "numUI.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------
RANK	CResult::m_Rank;

//------------------------------------------------------------------------------
//	関数名:	CResult::CResult()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CResult::CResult()
{
	m_UI = NULL;
	m_GamePoint = 0.0f;
}

//------------------------------------------------------------------------------
//	関数名:	CResult::~CResult()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CResult::~CResult()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CResult::Init
//	引数:	なし
//	戻り値: なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CResult::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  画面割合を取得
	float *pScreenRate = GetScreenRate();

	m_UI = CUI::Create();

	m_UI->Set(
		UI_RESULT_FRAME,
		UI_TYPE_NONE,
		D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
		D3DXVECTOR2(pScreenSize->x, pScreenSize->y),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//m_UI->Set(
	//	UI_RESULT_THANKS,
	//	UI_TYPE_NONE,
	//	D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y - 140.25f * *pScreenRate),
	//	D3DXVECTOR2(1459.5f * *pScreenRate, 100.5f * *pScreenRate),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	//);

	m_NumUI = CNumUI::Create();

	CManager::GetOpenAL()->Init(0, 0);

	m_Time = 45;
	m_FrameCnt = 60;

	m_ClearTime = CManager::GetClearTime();
	m_KillsNum = CManager::GetKillsNum();
	m_PlayerDamage = CManager::GetPlayerDamage();

	CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_RESULT, 1.0f, 0.0f, 0.0f, 0.0f);

	if (*m_ClearTime == -1)
	{
	}
	else
	{
		//  50 - 60.0
		if (*m_ClearTime < 90)
		{
			m_GamePoint += 60.0f;
		}
		else
		{
			m_GamePoint += 50.0f;
		}

		if (*m_KillsNum < 6)
		{
			m_GamePoint += (float)*m_KillsNum;
		}
		else
		{
			m_GamePoint += (float)(*m_KillsNum) * 1.25f;
		}

		if (*m_PlayerDamage < 25)
		{
			m_GamePoint += 20.0f;
		}
		else if(*m_PlayerDamage >= 25 && *m_PlayerDamage < 75) // 5 - 16
		{
			m_GamePoint += (float)(1.0f - *m_PlayerDamage / 100) * 15.0f;
		}
	}

	if (m_GamePoint >= 95.0f)
	{
		m_Rank = RANK_S;
	}
	else if (m_GamePoint >= 85.0f && m_GamePoint < 95.0f)
	{
		m_Rank = RANK_A;
	}
	else if (m_GamePoint >= 70.0f && m_GamePoint < 85.0f)
	{
		m_Rank = RANK_B;
	}
	else if (m_GamePoint >= 50.0f && m_GamePoint < 70.0f)
	{
		m_Rank = RANK_C;
	}
	else if (m_GamePoint < 50.0f)
	{
		m_Rank = RANK_D;
	}

	m_RankMarkID = m_UI->Set(
		UI_RESULT_RANK,
		UI_RESULT,
		D3DXVECTOR2(pScreenSize->x * 0.73f, pScreenSize->y * 0.55f),
		D3DXVECTOR2(325.0f * *pScreenRate, 400.0f * *pScreenRate),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	m_UI->SetTexRate(m_RankMarkID, m_Rank * 0.2f);
}

//------------------------------------------------------------------------------
//	関数名:	void CResult::Uninit
//	引数:	なし
//	戻り値: なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CResult::Uninit(void)
{
	//  シーンオール終了
	CScene::UninitAll();

	CManager::GetOpenAL()->Uninit();

	m_UI = NULL;

	CManager::SetKillsNum(0);
}

//------------------------------------------------------------------------------
//	関数名:	void CResult::Update
//	引数:	なし
//	戻り値: なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CResult::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	if (m_FrameCnt <= 0) {
		m_Time--;
		m_FrameCnt = 60;
	}
	else {
		m_FrameCnt--;
	}

	//  シーンオール更新
	CScene::UpdateAll();

	if (pKeyboard->GetTrigger(DIK_RETURN) || m_Time <= 0)
	{
		CManager::GetFade()->Set(new CTitle);
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CResult::Draw
//	引数:	なし
//	戻り値: なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CResult::Draw(void)
{
	//  シーンオール描画
	CScene::DrawAll();
}