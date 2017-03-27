//------------------------------------------------------------------------------
//	タイトル：		タイトルの関数
//	ファイル名：	title.cpp
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
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "camera.h"
#include "light.h"
#include "skybox.h"
#include "UI.h"
#include "meshField.h"
#include "player.h"
#include "openAL.h"
#include "water.h"
#include "missile.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
const D3DXVECTOR3 TitleCameraRot = D3DXVECTOR3(1.44f, -0.63f, 0.0f);

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CTitle::CTitle()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CTitle::CTitle()
{
	m_Camera = NULL;		//  カメラ
	m_Light = NULL;			//	ライト
	m_UI = NULL;
	m_Sea = NULL;
	m_KeyID = START_KEY;
	m_SelectID[START_KEY] =
	m_SelectID[EXIT_KEY] = 0;
}

//------------------------------------------------------------------------------
//	関数名:	CTitle::~CTitle()
//	引数:	なし
//	戻り値:	なし
//	説明:	デストラクタ
//------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Init
//	引数:	なし
//	戻り値: なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CTitle::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();

	//	インスタンス変数の生成と初期化処理
	m_Camera = new CCamera;			//  カメラ
	m_Light = new CLight;			//	ライト

	//  カメラの初期化
	m_Camera->Init(TitleCameraRot, true);

	//  ライトの初期化
	m_Light->Init();

	//  スカイボックスの生成
	CSkybox::Create(
		10000.0f						//  規模（幅、高さ、奥行き）
	);

	//  島の生成
	CMeshField::LoadMap(
		MESH_ISLAND,
		ISLAND_MAP_FILE,
		SEAMLESSMESHFIELD_TEXTURE_FILE,
		true,
		8.0f
	);

	//  海の生成
	CManager::SetSea(
		CMeshField::Create(
			MESH_SEA,
			SEAMLESSSEA_TEXTURE_FILE,
			D3DXVECTOR3(0.0f, -50.0f, 0.0f),
			D3DXVECTOR3(400.0f, 0.0f, 400.0f),
			15,
			15,
			true,
			10.0f
		)
	);

	//  ミサイルの生成
	CManager::SetMissile(
		CMissile::Create()
	);

	//  プレイヤーの生成
	CManager::SetPlayer(
		CPlayer::Create(
			MODEL_GORSHKOV,
			D3DXVECTOR3(160.0f, 0.0f, 100.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		)
	);

	//  水エフェクトの生成
	m_Water = CWater::Create();

	//  滝の生成
	m_Water->Set(
		D3DXVECTOR3(-930.0f, 270.0f, 2290.0f),
		D3DXVECTOR3(0.30f, 0.2f, 0.0f),
		D3DXVECTOR3(350.0f, 740.0f, 0.0f),
		EFFECT_WATER_FALL_000,
		true,
		true,
		false
	);

	m_Water->Set(
		D3DXVECTOR3(-1100.0f, 275.0f, 2395.0f),
		D3DXVECTOR3(0.30f, 0.75f, 0.0f),
		D3DXVECTOR3(420.0f, 810.0f, 0.0f),
		EFFECT_WATER_FALL_000,
		true,
		true,
		false
	);

	m_Water->Set(
		D3DXVECTOR3(-900.0f, 250.0f, 2280.0f),
		D3DXVECTOR3(0.30f, -0.1f, 0.0f),
		D3DXVECTOR3(325.0f, 750.0f, 0.0f),
		EFFECT_WATER_FALL_000,
		true,
		true,
		false
	);

	//  UIの生成
	m_UI = CUI::Create();

	//  タイトルマークを設定
	m_UI->Set(
		UI_TITLE,
		UI_TYPE_NONE,
		D3DXVECTOR2(40.0f * *pScreenRate + pScreenSize->x * 0.3f, 60.0f * *pScreenRate + pScreenSize->y * 0.25f),
		D3DXVECTOR2(pScreenSize->x * 0.6f, pScreenSize->x * 0.3f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//  スタートマークを設定
	m_SelectID[START_KEY] = m_UI->Set(
		UI_START,
		UI_TYPE_NONE,
		D3DXVECTOR2(5.0f * *pScreenRate + pScreenSize->x * 0.3f, 185.0f * *pScreenRate + pScreenSize->y * 0.5f),
		D3DXVECTOR2(pScreenSize->x * 0.14f, pScreenSize->y * 0.06f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//  終了マークを設定
	m_SelectID[EXIT_KEY] = m_UI->Set(
		UI_EXIT,
		UI_TYPE_NONE,
		D3DXVECTOR2(5.0f * *pScreenRate + pScreenSize->x * 0.3f, 210.0f * *pScreenRate + pScreenSize->y * 0.6f),
		D3DXVECTOR2(pScreenSize->x * 0.14f, pScreenSize->y * 0.06f),
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)
	);

	//  OpenALの初期化
	CManager::GetOpenAL()->Init(0, 0);

	CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_TITLE, 1.0f, 160.0f, 0.0f, 30.0f);
	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_TITLE_FALLS, 1.0f, 160.0f, 0.0f, 30.0f);
	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WAVE, 1.0f, 160.0f, 0.0f, 30.0f);
}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Uninit
//	引数:	なし
//	戻り値: なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CTitle::Uninit(void)
{
	//  シーンオール終了
	CScene::UninitAll();

	CManager::GetOpenAL()->Uninit();

	//	インスタンス変数の削除
	delete m_Camera;
	delete m_Light;
}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Update
//	引数:	なし
//	戻り値: なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CTitle::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	//  シーンオール更新
	CScene::UpdateAll();
	
	if (pKeyboard->GetTrigger(DIK_W))
	{
		m_KeyID--;

		if (m_KeyID < START_KEY)	m_KeyID = TITLE_KEY_MAX - 1;
	}
	else if (pKeyboard->GetTrigger(DIK_S))
	{
		m_KeyID++;

		if (m_KeyID > EXIT_KEY)	m_KeyID = START_KEY;
	}

	//  選択した武器マークの色を設定
	for (int i = 0; i < TITLE_KEY_MAX; i++)
	{
		if (m_KeyID == i)	m_UI->SetColor(m_SelectID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		else				m_UI->SetColor(m_SelectID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.5f);
	}

	switch (m_KeyID)
	{
	case START_KEY:
		if (pKeyboard->GetTrigger(DIK_RETURN))	CManager::GetFade()->Set(new CTutorial);
		break;
	case EXIT_KEY:
		if (pKeyboard->GetTrigger(DIK_RETURN))	exit(0);
		break;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CTitle::Draw
//	引数:	なし
//	戻り値: なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CTitle::Draw(void)
{
	//  カメラの設定
	m_Camera->SetCamera();

	//  シーンオール描画
	CScene::DrawAll();
}