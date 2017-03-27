//------------------------------------------------------------------------------
//	タイトル：		チュートリアルの関数
//	ファイル名：	tutorial.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "tutorial.h"
#include "game.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "meshField.h"
#include "skybox.h"
#include "UI.h"
#include "openAL.h"
#include "fade.h"
#include "bullet.h"
#include "water.h"
#include "bullet.h"
#include "missile.h"
#include "userMap.h"
#include "sprayBehide.h"
#include "numUI.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const D3DXVECTOR3 TutorialCameraRot = D3DXVECTOR3(D3DX_PI * 0.43f, D3DX_PI, 0.0f);
#define TUTORIAL_SECOND (60)

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CTutorial::CTutorial()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CTutorial::CTutorial()
{
	m_Camera = NULL;
	m_Light = NULL;
	m_UI = NULL;
	m_TutorialState = TUTORIAL_0;
	m_TutorialPoint = 0;
	m_SkipSelect.Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_SkipSelect.nChangeTime = 60;
}

//------------------------------------------------------------------------------
//	関数名:	CTutorial::~CTutorial()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CTutorial::~CTutorial()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CTutorial::Init
//	引数:	なし
//	戻り値: なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CTutorial::Init(void)
{
	//  画面サイズを取得
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  画面割合を取得
	float *pScreenRate = GetScreenRate();

	//	インスタンス変数の生成と初期化処理
	m_Camera = new CCamera;			//  カメラ
	m_Light = new CLight;			//	ライト

	//  カメラの初期化
	m_Camera->Init(TutorialCameraRot, false);

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

	//  水の生成
	CManager::SetWater(
		CWater::Create()
	);

	//  UIの生成
	CManager::SetUI(
		m_UI = CUI::Create()
	);

	//  弾の生成
	CManager::SetBullet(
		CBullet::Create()
	);

	//  ミサイルの生成
	CManager::SetMissile(
		CMissile::Create()
	);

	//  水飛沫（後ろ）の生成
	CManager::SetSprayBehide(
		CSprayBehide::Create()
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

	//  OpenALの初期化
	CManager::GetOpenAL()->Init(0, 0);

	m_BGMSource = CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_TUTORIAL, 1.0f, 0.0f, 0.0f, 0.0f);
	m_WaveSource = CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WAVE, 1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
//	関数名:	void CTutorial::Uninit
//	引数:	なし
//	戻り値: なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CTutorial::Uninit(void)
{
	m_Camera->Uninit();
	//  シーンオール終了
	CScene::UninitAll();

	CManager::GetOpenAL()->Uninit();

	m_NumUI->Uninit();

	//	インスタンス変数の削除
	delete m_Camera;
	delete m_Light;

	m_UI = NULL;
}

//------------------------------------------------------------------------------
//	関数名:	void CTutorial::Update
//	引数:	なし
//	戻り値: なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CTutorial::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float *pScreenRate = GetScreenRate();

	//  カメラの更新
	m_Camera->Update();

	//  シーンオール更新
	CScene::UpdateAll();

	m_NumUI->Update();

	CManager::GetOpenAL()->SetListenervalues(m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_BGMSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_WaveSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);

	switch (m_TutorialState)
	{
	case TUTORIAL_0:
		if (m_TutorialPoint == 0)
		{
			m_UI->Set(
				UI_TUTORIAL_CONTROLLER,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x * 0.5f, 212.11f * *pScreenRate),
				D3DXVECTOR2(830.34f * *pScreenRate, 374.22f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_UI->Set(
				UI_USERMAP_EX,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 200.0f * *pScreenRate, pScreenSize->y - 445.0f * *pScreenRate),
				D3DXVECTOR2(227.0f * *pScreenRate, 151.0f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_UI->Set(
				UI_TUTORIAL_FRAME,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_SkipUIid = m_UI->Set(
				UI_TUTORIAL_SKIP,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y - 100.0f * *pScreenRate),
				D3DXVECTOR2(201.1f * *pScreenRate, 69.3f * *pScreenRate),
				m_SkipSelect.Col
			);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION0,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}

		m_TutorialPoint++;

		if (m_TutorialPoint >= TUTORIAL_SECOND * 4)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION1,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_TutorialState = TUTORIAL_1;
		}
		break;
	case TUTORIAL_1:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 8)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION2,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_TutorialState = TUTORIAL_2;
		}
		break;
	case TUTORIAL_2:
		m_Player->SetMoveFlag(true);
		if (*m_Player->GetPowerNum() >= 100)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION3,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_3;
		}
		break;
	case TUTORIAL_3:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 12)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION4,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_4;
		}
		break;
	case TUTORIAL_4:
		m_Player->SetRotFlag(true);
		if (m_TutorialPoint >= TUTORIAL_SECOND * 14)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION5,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_5;
		}
		break;
	case TUTORIAL_5:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 18)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION6,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_6;
		}
		break;
	case TUTORIAL_6:
		m_Player->SetWeaponFlag(true);
		if (*m_Player->GetWeponType() == WEAPON_BULLET)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION7,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_7;
		}
		break;
	case TUTORIAL_7:
		if (m_TutorialPoint >= TUTORIAL_SECOND * 20)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION8,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_8;
		}
		break;
	case TUTORIAL_8:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 24)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION9,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_9;
		}
		break;
	case TUTORIAL_9:
		break;
	}

	if (m_TutorialState == TUTORIAL_9)
	{
		m_UI->SetFlag(m_SkipUIid, false);

		if (pKeyboard->GetTrigger(DIK_RETURN) /*|| pJoysticks->GetTrigger(DIJ_BUTTON_A)*/)
		{
			CManager::GetFade()->Set(new CGame);
		}
	}
	else
	{
		if (m_SkipSelect.bSelect)
		{
			m_SkipSelect.nChangeTime--;
			m_SkipSelect.nFrameCnt++;
			if (m_SkipSelect.nFrameCnt >= 5)
			{
				m_SkipSelect.nFrameCnt = 0;
				m_SkipSelect.nPattern++;

				if (m_SkipSelect.nPattern >= 2)
				{
					m_SkipSelect.nPattern = 0;
				}

				switch (m_SkipSelect.nPattern)
				{
				case 0:
					m_SkipSelect.Col.a = 0.0f;
					break;
				case 1:
					m_SkipSelect.Col.a = 1.0f;
					break;
				}
			}

			if (m_SkipSelect.nChangeTime < 0)
			{
				m_SkipSelect.Col.a = 0.0f;
				CManager::GetFade()->Set(new CGame);
			}
		}
		else
		{
			if (pKeyboard->GetPress(DIK_RETURN) /*|| pJoysticks->GetPress(DIJ_BUTTON_A)*/)
			{
				m_SkipSelect.Col.a += 2.0f / (float)(TUTORIAL_SECOND * 2);
			}
			else
			{
				if (m_SkipSelect.Col.a < 1.0f)
				{
					m_SkipSelect.Col.a -= 1.0f / (float)(TUTORIAL_SECOND * 2);
				}
			}

			if (m_SkipSelect.Col.a > 1.0f)
			{
				m_SkipSelect.Col.a = 1.0f;
				m_SkipSelect.bSelect = true;
			}
			else if (m_SkipSelect.Col.a < 0.0f)
			{
				m_SkipSelect.Col.a = 0.0f;
			}
		}

		m_UI->SetColor(m_SkipUIid, m_SkipSelect.Col);
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CTutorial::Draw
//	引数:	なし
//	戻り値: なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CTutorial::Draw(void)
{
	//  カメラの設定
	m_Camera->SetCamera();

	//  シーンオール描画
	CScene::DrawAll();
}