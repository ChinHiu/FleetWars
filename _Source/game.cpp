//------------------------------------------------------------------------------
//	タイトル：		ゲームの関数
//	ファイル名：	game.cpp
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
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "skybox.h"
#include "meshField.h"
#include "UI.h"
#include "openAL.h"
#include "fade.h"
#include "bullet.h"
#include "water.h"
#include "enemy.h"
#include "missile.h"
#include "userMap.h"
#include "sprayBehide.h"
#include "numUI.h"
#include "effect.h"
#include "result.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
const D3DXVECTOR3 GameCameraRot = D3DXVECTOR3(D3DX_PI * 0.43f, D3DX_PI, 0.0f);

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CGame::CGame()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CGame::CGame()
{
	m_Camera = NULL;
	m_Light = NULL;
	m_bFail = false;
	m_bOneCreat = false;
	m_GameResultCnt = 180;
}

//------------------------------------------------------------------------------
//	関数名:	CGame::~CGame()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CGame::~CGame()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Init
//	引数:	なし
//	戻り値: なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CGame::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();

	//	インスタンス変数の生成と初期化処理
	m_Camera = new CCamera;			//  カメラ
	m_Light = new CLight;			//	ライト

#ifdef _DEBUG
	m_Time = 1200;
#else
	m_Time = nGameTime;

#endif

	m_FrameCnt = 60;

	//  カメラの初期化
	m_Camera->Init(GameCameraRot, false);

	//  カメラデータ情報をマネージャーに渡す
	CManager::SetCameraData(m_Camera->GetCameraData());

	//  ライトの初期化
	m_Light->Init();

	//  スカイボックスの生成
	CSkybox::Create(
		10000.0f						//  規模（幅、高さ、奥行き）
	);

	//  海の生成
	CManager::SetSea(
		CMeshField::Create(
			MESH_SEA,
			SEAMLESSSEA_TEXTURE_FILE,
			D3DXVECTOR3(0.0f, -15.0f, 0.0f),
			D3DXVECTOR3(400.0f, 0.0f, 400.0f),
			80,
			80,
			true,
			10.0f
		)
	);

	//  水エフェクトの生成
	CManager::SetWater(
		CWater::Create()
	);

	//  UIの生成
	CManager::SetUI(
		m_UI = CUI::Create()
	);

	//  ミサイルの生成
	CManager::SetMissile(
		CMissile::Create()
	);

	//  水飛沫（後ろ）の生成
	CManager::SetSprayBehide(
		CSprayBehide::Create()
	);

	//  エフェクトの生成
	CManager::SetEffect(
		CEffect::Create()
	);

	//  弾の生成
	CManager::SetBullet(
		CBullet::Create()
	);

	//  プレイヤーの生成
	CManager::SetPlayer(
		m_Player = CPlayer::Create(
			MODEL_GORSHKOV,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f)
		)
	);

	//  数字系UIの生成
	m_NumUI = CNumUI::Create();

	//  ユーザーマップの生成
	CManager::SetUserMap(
		CUserMap::Create()
	);

	//  Hamina敵の生成
	CManager::SetHamina(
		m_Hamina = CEnemy_Hamina::Create()
	);

	//  敵の生成
	m_Hamina->Set(
		D3DXVECTOR3(-2000.0f, 0.0f, 4000.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_LEFT_NORMAL1
	);

	m_Hamina->Set(
		D3DXVECTOR3(-2500.0f, 0.0f, 4200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_LEFT_LEADER
	);

	m_Hamina->Set(
		D3DXVECTOR3(-3000.0f, 0.0f, 4400.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_LEFT_NORMAL2
	);

	m_Hamina->Set(
		D3DXVECTOR3(2000.0f, 0.0f, 4000.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RIGHT_NORMAL1
	);

	m_Hamina->Set(
		D3DXVECTOR3(2500.0f, 0.0f, 4200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RIGHT_LEADER
	);

	m_Hamina->Set(
		D3DXVECTOR3(3000.0f, 0.0f, 4400.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RIGHT_NORMAL2
	);

	m_Hamina->Set(
		D3DXVECTOR3(500, 0.0f, 3200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RAND
	);

	m_Hamina->Set(
		D3DXVECTOR3(-500, 0.0f, 3200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RAND
	);

	CManager::GetOpenAL()->Init(0, 0);

	m_BGMSource = CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_GAME, 1.0f, 0.0f, 0.0f, 0.0f);
	m_WaveSource = CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WAVE, 1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Uninit
//	引数:	なし
//	戻り値: なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CGame::Uninit(void)
{
	//  カメラの終了			
	m_Camera->Uninit();
	CScene::UninitAll();
	CManager::GetOpenAL()->Uninit();

	m_NumUI->Uninit();

	//	インスタンス変数の削除
	delete m_Camera;				//  カメラ
	delete m_Light;					//  ライト
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Update
//	引数:	なし
//	戻り値: なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CGame::Update(void)
{
	CKeyboard	*pKeyboard = CManager::GetInput()->GetKeyboard();
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();

	//  カメラの更新
	m_Camera->Update();

	m_NumUI->Update();

	//  シーンオール更新
	CScene::UpdateAll();

	CManager::GetOpenAL()->SetListenervalues(m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_BGMSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_WaveSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);

	if (*CManager::GetKillsNum() < nHamina_Max)
	{
		if (m_FrameCnt <= 0)
		{
			m_Time--;
			m_FrameCnt = 60;

			m_Time = m_Time <= 0 ? 0 : m_Time;
		}
		else
		{
			m_FrameCnt--;
		}
	}

	if (*m_Player->GetLife() <= 0 || m_Time == 0)
	{
		m_bFail = true;
		CManager::SetMissionResult(true);
	}

	if (m_bFail)
	{
		m_GameResultCnt--;
		if (!m_bOneCreat)
		{
			m_UI->Set(
				UI_MISSION_FAIL,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
				D3DXVECTOR2(1227.2f * *pScreenRate, 107.2f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_bOneCreat = true;
		}
	}
	else
	{
		if (*CManager::GetKillsNum() == nHamina_Max)
		{
			m_GameResultCnt--;
			if (!m_bOneCreat)
			{
				m_UI->Set(
					UI_MISSION_COM,
					UI_TYPE_NONE,
					D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
					D3DXVECTOR2(1227.2f * *pScreenRate, 107.2f * *pScreenRate),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
				);
				m_bOneCreat = true;
			}
		}
	}

	if (m_GameResultCnt <= 0)
	{
		CManager::SetClearTime(m_Time);
		CManager::SetPlayerDamage(*m_Player->GetLife());
		CManager::GetFade()->Set(new CResult);
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CGame::Draw
//	引数:	なし
//	戻り値: なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CGame::Draw(void)
{
	//  カメラの設定
	m_Camera->SetCamera();

	//  シーンオール描画
	CScene::DrawAll();

}