//------------------------------------------------------------------------------
//	タイトル：		プレイヤーの関数
//	ファイル名：	player.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/12/13
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "model.h"
#include "player.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include <typeinfo.h>
#include "meshField.h"
#include "title.h"
#include "tutorial.h"
#include "stencilShadow.h"
#include "ObbTest.h"
#include "UI.h"
#include "bullet.h"
#include "openAL.h"
#include "Func.h"
#include "enemy.h"
#include "missile.h"
#include "sprayBehide.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define POSY_ADJUST (18.0f)
#define SPEED_MAX	(40)

#define MISSILE_REPAIR_TIME (12)
#define BULLET_SHOT_COUNT (20)

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//  各Obb相対位置
const D3DXVECTOR3 g_ObbRelativePos[] =
{
	D3DXVECTOR3(0.0f, -23.0f, 0.0f),
	D3DXVECTOR3(0.0f, 12.0f, 38.0f),
	D3DXVECTOR3(0.0f, 44.0f, -26.0f),
	D3DXVECTOR3(0.0f, 28.0f, 170.0f)
};

//  各Obb三軸の長さ
const D3DXVECTOR3 g_ObbLength[] =
{
	D3DXVECTOR3(36.0f, 25.0f, 235.0f),
	D3DXVECTOR3(36.0f, 10.0f, 120.0f),
	D3DXVECTOR3(16.0f, 22.0f, 16.0f),
	D3DXVECTOR3(12.0f, 28.0f, 12.0f)
};

//  ミサイルの偏移量
const D3DXVECTOR3 g_MissileDeviationPos[] =
{
	D3DXVECTOR3(5.5f, 34.0f, 164.2f),
	D3DXVECTOR3(-5.5f, 34.0f, 164.2f),
	D3DXVECTOR3(5.5f, 34.0f, 176.0f),
	D3DXVECTOR3(-5.5f, 34.0f, 176.0f)
};

//  水飛沫（前）の変位量
const D3DXVECTOR3 g_SprayBeforeDeviationPos[] =
{
	D3DXVECTOR3(-2.0f, -40.0f, -192.0f),
	D3DXVECTOR3(2.0f, -40.0f, -192.0f)
};

//  水飛沫（前）のサイズ
const D3DXVECTOR3 g_SprayBeforeSize = D3DXVECTOR3(150.0f, 50.0f, 0.0f);

//  水飛沫（後ろ）の変位量
const D3DXVECTOR3 g_SprayBehideDeviationPos = D3DXVECTOR3(0.0f, -30.0f, 170.0f);

//  水飛沫（後ろ）のサイズ
const D3DXVECTOR3 g_SprayBehideSize = D3DXVECTOR3(100.0f, 0.0f, 300.0f);

//------------------------------------------------------------------------------
//	関数名:	CPlayer::CPlayer
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CPlayer::CPlayer(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		m_Model[i] = NULL;
	}

	m_Weapon = WEAPON_NONE;
	m_WeaponID = WEAPON_NONE;	
	m_PowerNum =
	m_SpeedNum =
	m_BulletCnt =
	m_MissileCnt = 0;
	m_OverHitRate = 0.0f;
	m_bFire = false;
	m_BatteryRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bCollision = false;
	m_HeatCol = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	m_bMoveFlag =
	m_bRotFlag =
	m_WeaponFlag = false;
}

//------------------------------------------------------------------------------
//	関数名:	CPlayer::~CPlayer
//	引数:	なし
//	戻り値:	なし
//	説明:	デストラクタ
//------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//------------------------------------------------------------------------------
//	関数名:	CPlayer *CPlayer::Create
//	引数:	MODEL_TYPE	Model_Type
//			D3DXVECTOR3 pos
//			D3DXVECTOR3 rot
//	戻り値:	pPlayer
//	説明:	プレイヤーの生成
//------------------------------------------------------------------------------
CPlayer *CPlayer::Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer	*pPlayer;
	pPlayer = new CPlayer();

	pPlayer->m_CharData.Pos = pos;
	pPlayer->m_CharData.Rot = rot;
	pPlayer->m_Type = Model_Type;
	pPlayer->m_CharData.bFlag = true;
	pPlayer->Init();
	return pPlayer;
}

//------------------------------------------------------------------------------
//	関数名:	void CSceneX::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CPlayer::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();
	CMode	*pMode	= CManager::GetMode();
	CUI		*pUI	= CManager::GetUI();

	//  モデルの設定
	m_Model[PLAYER_BODY] = CModel::Create(
		m_Type,
		MODEL_PARTS_GORSHKOV_BODY,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	m_Model[PLAYER_BATTERY] = CModel::Create(
		m_Type,
		MODEL_PARTS_GORSHKOV_BATTERY,
		D3DXVECTOR3(0.0f, 60.5f, -26.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	m_Model[PLAYER_GUN] = CModel::Create(
		m_Type,
		MODEL_PARTS_GORSHKOV_GUN,
		D3DXVECTOR3(0.0f, 3.5f, -3.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	//  モデル親の設定
	m_Model[PLAYER_BODY]->SetParent(NULL);
	m_Model[PLAYER_BATTERY]->SetParent(m_Model[PLAYER_BODY]);
	m_Model[PLAYER_GUN]->SetParent(m_Model[PLAYER_BATTERY]);

	//  タイトルモードの初期化処理
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		//  シャドウを設定
		m_Shadow = CStencilShadow::Create(m_Type, D3DXVECTOR3(173.0f, -30.0f, 100.0f) );

		//  マトリクスの更新
		MatrixUpdate();

		//  ミサイルを設定
		for (int i = 0; i < nMissileMax_P; i++)
		{
			m_MissileID[i] = CManager::GetMissile()->Reset(&m_Matrix.World, USER_PLAYER, &m_CharData.Pos, &m_CharData.Rot, &m_CharData.bFlag, g_MissileDeviationPos[i]);
		}
	}

	//  タイトルモード以外の初期化処理（チュートリアル、ゲーム）
	else
	{
		D3DXVECTOR3	ObbPos;

		if (typeid(*pMode).name() == typeid(CGame).name())
		{
			m_bMoveFlag =
			m_bRotFlag =
			m_WeaponFlag = true;
		}

		//  武器データを初期化
		m_WeaponData[WEAPON_BULLET].nNum = 0;
		m_WeaponData[WEAPON_BULLET].fCoolDown = 0.0f;
		m_WeaponData[WEAPON_BULLET].bFlag = true;

		m_WeaponData[WEAPON_MISSILE].nNum = 4;
		m_WeaponData[WEAPON_MISSILE].nCoolDown = MISSILE_REPAIR_TIME;
		m_WeaponData[WEAPON_MISSILE].bFlag = true;

		m_WeaponData[WEAPON_REPAIR].nNum = 1;
		m_WeaponData[WEAPON_REPAIR].nCoolDown = 0;
		m_WeaponData[WEAPON_REPAIR].bFlag = true;

		//  マトリクスの更新
		MatrixUpdate();

		//  ミサイルを設定
		for (int i = 0; i < nMissileMax_P; i++)
		{
			m_MissileID[i] = CManager::GetMissile()->Reset(&m_Matrix.World, USER_PLAYER, &m_CharData.Pos, &m_CharData.Rot, &m_CharData.bFlag, g_MissileDeviationPos[i]);
		}

		//  Obbの設定
		for (int i = 0; i < nObbMax_P; i++)
		{
			D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[i], &m_Matrix.World);							//  Obb位置を算出
			m_Obb[i].SetPos(ObbPos);																		//  Obb位置を設定
			m_Obb[i].SetLength(g_ObbLength[i]);																//  Obb各軸長さを設定
			m_Obb[i].SetDirect(X_AXIS, D3DXVECTOR3(m_Matrix.Rot._11, m_Matrix.Rot._12, m_Matrix.Rot._13));	//  ObbのX軸方向ベクトルを設定
			m_Obb[i].SetDirect(Y_AXIS, D3DXVECTOR3(m_Matrix.Rot._21, m_Matrix.Rot._22, m_Matrix.Rot._23));	//  ObbのY軸方向ベクトルを設定
			m_Obb[i].SetDirect(Z_AXIS, D3DXVECTOR3(m_Matrix.Rot._31, m_Matrix.Rot._32, m_Matrix.Rot._33));	//  ObbのZ軸方向ベクトルを設定
			m_ObbTest[i] = CObbTest::Create(m_Obb[i].GetPos(), m_CharData.Rot, g_ObbLength[i]);				//  Obbテスト立方体の設定
		}

		//  シャドウを設定
		m_Shadow = CStencilShadow::Create(m_Type, m_CharData.Pos);

		//  水飛沫の設定（前）
		m_SprayBefore = CSpray::Create();

		for (int i = 0; i < SPRAY_TYPE_MAX; i++)
		{
			//  水しぶき
			m_SprayBefore->Set(
				MODEL_GORSHKOV,
				&m_SprayBeforePos[i],
				&m_CharData.Rot,
				&m_SprayBeforeSize,
				(SPRAY_TYPE)i,
				true
			);
		}

		//  水飛沫の設定（後ろ）
		CManager::GetSprayBehide()->Set(
			&m_SprayBehidePos,
			&m_CharData.Rot,
			&m_SprayBehideSize,
			true
		);

		m_PowerNum = 50;
		m_SpeedNum = 2500;
		m_OldLife = 
		m_CharData.nLife = 100;


		//  UIの設定
		//  武器マークを設定
		for (int i = UI_WEAPON_GATLING, j = 0; i <= UI_WEAPON_REPAIR; i++, j++)
		{
			m_WeaponMarkID[j] = pUI->Set(
				(UI_LABLE)i,
				UI_TYPE_NONE,
				D3DXVECTOR2(65.0f * *pScreenRate, pScreenSize->y - 85.0f * *pScreenRate * (UI_WEAPON_REPAIR - i) - 65.0f * *pScreenRate),
				D3DXVECTOR2(80.0f * *pScreenRate, 80.0f * *pScreenRate),
				D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f)
			);
		}

		//  HP枠
		pUI->Set(
			UI_LIFE_FRAME,
			UI_TYPE_NONE,
			D3DXVECTOR2((25.0f + 460.0f * 0.5f) * *pScreenRate, 50.0f * *pScreenRate),
			D3DXVECTOR2(460.0f * *pScreenRate, 50.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		//  HP
		m_LifeMarkID = pUI->Set(
			UI_LIFE,
			UI_WIDTH_SCROLL,
			D3DXVECTOR2(112.0f * *pScreenRate, 50.0f * *pScreenRate),
			D3DXVECTOR2(358.0f * *pScreenRate, 28.5f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		pUI->SetTexRate(m_LifeMarkID, 1.0f);

		//  スコープ
		m_ScopeMarkID = pUI->Set(
			UI_SCOPE,
			UI_TYPE_NONE,
			D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
			D3DXVECTOR2(1920.0f * *pScreenRate, 1080.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		//  戦艦砲熱情報
		m_HeatMarkID = pUI->Set(
			UI_HEAT,
			UI_HEIGHT_SCROLL,
			D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
			D3DXVECTOR2(450.0f * *pScreenRate, 441.6f * *pScreenRate),
			m_HeatCol
		);

		//  過熱マーク
		m_OverHeatMarkID = pUI->Set(
			UI_OVERHEAT,
			UI_TYPE_NONE,
			D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
			D3DXVECTOR2(200.0f * *pScreenRate, 109.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
		);

		//  無限マーク
		pUI->Set(
			UI_INFINITY,
			UI_TYPE_NONE,
			D3DXVECTOR2(156.84f * *pScreenRate, pScreenSize->y - 85.0f * *pScreenRate * 2 - 65.0f * *pScreenRate),
			D3DXVECTOR2(73.68f * *pScreenRate, 40.0f * *pScreenRate),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
		);

		//  パワーマーク
		pUI->Set(
			UI_POWER_MARK,
			UI_TYPE_NONE,
			D3DXVECTOR2(75.0f * *pScreenRate, 103.0f * *pScreenRate),
			D3DXVECTOR2(100 * *pScreenRate, 30 * *pScreenRate),
			D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f)
		);

		//  スピードマーク
		pUI->Set(
			UI_SPEED_MARK,
			UI_TYPE_NONE,
			D3DXVECTOR2(75.0f * *pScreenRate, 135.5f * *pScreenRate),
			D3DXVECTOR2(100 * *pScreenRate, 30 * *pScreenRate),
			D3DXCOLOR(0.1f, 1.0f, 0.5f, 1.0f)
		);
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
	CMode *pMode = CManager::GetMode();

	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		m_Model[i]->Uninit();
	}

	m_Shadow->Uninit();
	m_Shadow = NULL;

	for (int i = 0; i < nObbMax_P; i++)
	{
		m_ObbTest[i] = NULL;
	}

	//	タイトル以外
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		m_SprayBefore->Uninit();
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CPlayer::Update(void)
{
	CMode			*pMode			= CManager::GetMode();
	CKeyboard		*pKeyboard		= CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse			= CManager::GetInput()->GetMouse();
	CCamera_Data	*pCameraData	= CManager::GetCameraData();
	CMeshField		*pSea			= CManager::GetSea();
	CUI				*pUI			= CManager::GetUI();
	CMissile		*pMissile		= CManager::GetMissile();

//  タイトルの更新
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		m_CharData.Pos.y = pSea->GetHeight(m_CharData.Pos) - 10.0f;

		MatrixUpdate();
	}
	else
	{
		if (typeid(*pMode).name() == typeid(CTutorial).name())
		{
			CTutorial	*pTutorial = ((CTutorial*)CManager::GetMode());
		}

		CHamina_Data *pHaminaData = CManager::GetHamina()->GetHaminaData();
		D3DXVECTOR3	ObbPos;

		if (m_WeaponFlag)
		{
			//  武器処理
					//  武器昇順選択
			if (pKeyboard->GetTrigger(DIK_Q))
			{
				m_WeaponID--;
				m_WeaponID = m_WeaponID <= WEAPON_NONE - 1 ? WEAPON_REPAIR : m_WeaponID;
			}
			//  武器降順選択
			else if (pKeyboard->GetTrigger(DIK_E))
			{
				m_WeaponID++;
				m_WeaponID = m_WeaponID >= WEAPON_REPAIR + 1 ? WEAPON_NONE : m_WeaponID;
			}

			//  武器直接選択
			if (pKeyboard->GetTrigger(DIK_1)) m_WeaponID = WEAPON_BULLET;
			if (pKeyboard->GetTrigger(DIK_2)) m_WeaponID = WEAPON_MISSILE;
			if (pKeyboard->GetTrigger(DIK_3)) m_WeaponID = WEAPON_REPAIR;

		}

		//  選択した武器を設定
		m_Weapon = (WEAPON_TYPE)m_WeaponID;

		//  選択した武器マークの色を設定
		for (int i = 0; i < WEAPON_TYPE_MAX; i++)
		{
			if (m_Weapon == i)	pUI->SetColor(m_WeaponMarkID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			else				pUI->SetColor(m_WeaponMarkID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.5f);
		}

		//  戦艦砲のcoolDownタイムをカウント（過熱状態）
		if (!m_WeaponData[WEAPON_BULLET].bFlag)
		{
			m_WeaponData[WEAPON_BULLET].fCoolDown -= 0.005f;

			//  CDが終われば、発射可能
			if (m_WeaponData[WEAPON_BULLET].fCoolDown <= 0.0f)
			{
				m_WeaponData[WEAPON_BULLET].bFlag = TRUE;
				m_WeaponData[WEAPON_BULLET].fCoolDown = 0.0f;
			}
		}
		else
		{	//  連射ではなければ、少しずつ回復
			if (!m_bFire)
			{
				if (m_WeaponData[WEAPON_BULLET].fCoolDown > 0.0f)
				{
					m_WeaponData[WEAPON_BULLET].fCoolDown -= 0.0075f;

					//  CD時間のチェック
					m_WeaponData[WEAPON_BULLET].fCoolDown = m_WeaponData[WEAPON_BULLET].fCoolDown <= 0.0f ? 0.0f : m_WeaponData[WEAPON_BULLET].fCoolDown;
				}
			}

			m_bFire = false;
		}

		//  ミサイルクールダウン
		if (!m_WeaponData[WEAPON_MISSILE].bFlag)
		{
			//  ミサイルCoolDownタイムは秒単位で計算
			m_MissileCnt--;

			if (m_MissileCnt <= 0)
			{
				m_WeaponData[WEAPON_MISSILE].nCoolDown--;
				m_MissileCnt = 60;
			}

			if (m_WeaponData[WEAPON_MISSILE].nCoolDown <= 0)
			{
				for (int i = 0; i < nMissileMax_P; i++)
				{
					//  ミサイルリセット
					m_MissileID[i] = pMissile->Reset(&m_Matrix.World, USER_PLAYER, &m_CharData.Pos, &m_CharData.Rot, &m_CharData.bFlag, g_MissileDeviationPos[i]);
				}
				m_WeaponData[WEAPON_MISSILE].bFlag = true;
				m_WeaponData[WEAPON_MISSILE].nCoolDown = MISSILE_REPAIR_TIME;
				m_WeaponData[WEAPON_MISSILE].nNum = nMissileMax_P;
			}
		}

		switch (m_Weapon)
		{
		case WEAPON_BULLET:		//  戦艦砲
			WeaponBulletUpdate();

			if (typeid(*pMode).name() == typeid(CTutorial).name())
			{
				CTutorial	*pTutorial = ((CTutorial*)CManager::GetMode());

				if (*pTutorial->GetTutorialState() == TUTORIAL_7)
				{
					if(m_bFire)	pTutorial->AppTutorialPoint(15);
				}
			}
			break;
		case WEAPON_MISSILE:	//  ミサイル
			if (typeid(*pMode).name() == typeid(CGame).name())
			{
				WeaponMissileUpdate();
			}
			break;
		case WEAPON_REPAIR:		//  緊急修理
			if (typeid(*pMode).name() == typeid(CGame).name())
			{
				WeaponRepairUpdate();
			}
			break;
		default:
			break;
		}

		if (m_Weapon == WEAPON_BULLET)
		{
			CManager::GetUI()->SetFlag(m_ScopeMarkID, true);
			//  過熱マーク
			CManager::GetUI()->SetFlag(m_OverHeatMarkID, !m_WeaponData[m_Weapon].bFlag);

			//  熱
			CManager::GetUI()->SetFlag(m_HeatMarkID, true);
			m_HeatCol.g = 1.0f - m_WeaponData[WEAPON_BULLET].fCoolDown;
			CManager::GetUI()->SetColor(m_HeatMarkID, m_HeatCol);
			CManager::GetUI()->SetTexRate(m_HeatMarkID, m_WeaponData[WEAPON_BULLET].fCoolDown);
		}
		else
		{
			CManager::GetUI()->SetFlag(m_ScopeMarkID, false);
			CManager::GetUI()->SetFlag(m_OverHeatMarkID, false);
			CManager::GetUI()->SetFlag(m_HeatMarkID, false);
		}

		if (m_OldLife > m_CharData.nLife) m_OldLife--;
		if (m_OldLife < m_CharData.nLife) m_OldLife++;

		m_fLifeRate = (float)(m_OldLife / 100.0f);

		pUI->SetTexRate(m_LifeMarkID, m_fLifeRate);

//  武器処理はここまで

//  回転処理
		//  砲台は常にカメラと同じ向き
		m_BatteryRot.y = pCameraData->rot.y - D3DX_PI;

		//  砲台の向きチェック
		SAFE_ROTCHECK(m_BatteryRot.y);

		//  砲台の向きを更新
		m_Model[PLAYER_BATTERY]->SetRot(m_BatteryRot);

		if (m_bRotFlag)
		{
			if (pKeyboard->GetPress(DIK_A))			m_CharData.Rot.y -= 0.005f;
			else if (pKeyboard->GetPress(DIK_D))	m_CharData.Rot.y += 0.005f;

			SAFE_ROTCHECK(m_CharData.Rot.y);

			if (typeid(*pMode).name() == typeid(CTutorial).name())
			{
				CTutorial	*pTutorial = ((CTutorial*)CManager::GetMode());

				if (*pTutorial->GetTutorialState() == TUTORIAL_4)
				{
					if (pKeyboard->GetPress(DIK_A) || pKeyboard->GetPress(DIK_D))	pTutorial->AppTutorialPoint(1);
				}
			}
		}
//  回転処理はここまで

//  移動処理
		if (m_bMoveFlag)
		{
			//  エンジンパワーの加速、減速しょり
			if (pKeyboard->GetPress(DIK_W))			m_PowerNum += 1;
			else if (pKeyboard->GetPress(DIK_S))	m_PowerNum -= 1;

			//  パワー値のチェック
			if (m_PowerNum > 100)					m_PowerNum = 100;
			else if (m_PowerNum < 0)				m_PowerNum = 0;
		}
		//  目標スピードナンバーを算出（Speedの千倍）
		m_AimSpeedNum = SPEED_MAX * m_PowerNum;

		//  現在スピードナンバーを更新（Speedの千倍）
		if (m_SpeedNum > m_AimSpeedNum)			m_SpeedNum -= 4;
		else if (m_SpeedNum < m_AimSpeedNum)	m_SpeedNum += 3;

		//  スピードを算出
		m_CharData.fSpeed = (float)m_SpeedNum * 0.001f;

		//  位置更新
		m_CharData.Pos.x -= m_Obb[0].GetDirect(2).x * m_CharData.fSpeed;
		m_CharData.Pos.z -= m_Obb[0].GetDirect(2).z * m_CharData.fSpeed;
		m_CharData.Pos.y = pSea->GetHeight(m_CharData.Pos) + 20.0f;

//  移動処理はここまで

		if (typeid(*pMode).name() == typeid(CGame).name())
		{
			//  当たり判定
			m_bCollision = false;

			for (int i = 0; i < nHamina_Max; i++, pHaminaData++)
			{
				if (pHaminaData->CharData.bFlag)
				{
					if (pHaminaData->fDistance > 0.0f && pHaminaData->fDistance < 700.0f)
					{
						m_bCollision = CManager::GetFunc()->OBBs(pHaminaData->Obb[0], m_Obb[0]);
						break;
					}
				}
			}

			if (m_bCollision)
			{
				m_CharData.Pos.x = m_CharData.OldPos.x;
				m_CharData.Pos.z = m_CharData.OldPos.z;
				m_CharData.Rot = m_CharData.OldRot;
				m_SpeedNum -= m_SpeedNum <= 0 ? 0 : 5;
			}
		}

		//  水飛沫（前）の更新
		for (int i = 0; i < SPRAY_TYPE_MAX; i++)
		{
			D3DXVec3TransformCoord(&m_SprayBeforePos[i], &g_SprayBeforeDeviationPos[i], &m_Matrix.World);
			m_SprayBeforePos[i].y = pSea->GetHeight(m_SprayBeforePos[i]) - 20.0f;
		}
		m_SprayBeforeSize = g_SprayBeforeSize * (m_CharData.fSpeed / 4.0f);
		m_SprayBefore->Update();

		//  水飛沫（後ろ）の更新
		D3DXVec3TransformCoord(&m_SprayBehidePos, &g_SprayBehideDeviationPos, &m_Matrix.World);
		m_SprayBehideSize = g_SprayBehideSize * (m_CharData.fSpeed / 4.0f);

		//  マトリクスの更新
		MatrixUpdate();

		//  Obb情報の更新
		ObbUpdate();

		//  シャドウ位置、回転の更新
		m_Shadow->SetRot(m_CharData.Rot);
		m_Shadow->SetPos(m_CharData.Pos);

		//  座標と回転を保存
		m_CharData.OldPos = m_CharData.Pos;
		m_CharData.OldRot = m_CharData.Rot;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	CMode *pMode = CManager::GetMode();

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  シャドウの描画
	m_Shadow->Draw();

	//  ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//  パーツの描画
	if (m_Weapon == WEAPON_BULLET)
	{
		m_Model[PLAYER_BODY]->Draw();
	}
	else
	{
		for (int i = 0; i < PLAYER_PARTS_MAX; i++)
		{
			m_Model[i]->Draw();
		}
	}

	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		//  船前の水飛沫を描画
		for (int i = 0; i < SPRAY_TYPE_MAX; i++)
		{
			m_SprayBefore->Draw(i);
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::MatrixUpdate
//	引数:	なし
//	戻り値:	なし
//	説明:	ワールドマトリックスの更新
//------------------------------------------------------------------------------
void CPlayer::MatrixUpdate(void)
{
	//  ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Matrix.World);

	//  スケールを反映
	D3DXMatrixScaling(&m_Matrix.Scl, m_CharData.Scl.x, m_CharData.Scl.y, m_CharData.Scl.z);
	D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl);

	//  回転を反映
	D3DXMatrixRotationYawPitchRoll(&m_Matrix.Rot, m_CharData.Rot.y, m_CharData.Rot.x, m_CharData.Rot.z);
	D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot);

	//  位置を反映
	D3DXMatrixTranslation(&m_Matrix.Trans, m_CharData.Pos.x, m_CharData.Pos.y, m_CharData.Pos.z);
	D3DXMatrixMultiply(&m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans);
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::ObbUpdate(void)
//	引数:	なし
//	戻り値:	なし
//	説明:	OBB情報の更新
//------------------------------------------------------------------------------
void CPlayer::ObbUpdate(void)
{
	D3DXVECTOR3 ObbPos;

	for (int i = 0; i < nObbMax_P; i++)
	{
		D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[i], &m_Matrix.World);							//  Obb位置を算出
		m_Obb[i].SetPos(ObbPos);																		//  Obb位置を設定
		m_Obb[i].SetDirect(X_AXIS, D3DXVECTOR3(m_Matrix.Rot._11, m_Matrix.Rot._12, m_Matrix.Rot._13));	//  ObbのX軸方向ベクトルを設定
		m_Obb[i].SetDirect(Y_AXIS, D3DXVECTOR3(m_Matrix.Rot._21, m_Matrix.Rot._22, m_Matrix.Rot._23));	//  ObbのY軸方向ベクトルを設定
		m_Obb[i].SetDirect(Z_AXIS, D3DXVECTOR3(m_Matrix.Rot._31, m_Matrix.Rot._32, m_Matrix.Rot._33));	//  ObbのZ軸方向ベクトルを設定
		m_ObbTest[i]->SetPos(m_Obb[i].GetPos());														//  Obbテスト立方体の位置を設定
		m_ObbTest[i]->SetRot(m_CharData.Rot);															//  Obbテスト立方体の回転を設定
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::WeaponBulletUpdate(void)
//	引数:	なし
//	戻り値:	なし
//	説明:	戦艦砲の更新
//------------------------------------------------------------------------------
void CPlayer::WeaponBulletUpdate(void)
{
	CKeyboard		*pKeyboard = CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse = CManager::GetInput()->GetMouse();
	CBullet			*pBullet = CManager::GetBullet();
	CCamera_Data	*pCameraData = CManager::GetCameraData();

	if (m_WeaponData[m_Weapon].bFlag)
	{
		//  戦艦砲発射処理
		if (pMouse->GetPress(DIM_LEFT))
		{
			m_BulletCnt--;

			if (m_BulletCnt <= 0)
			{
				//  弾の設定
				pBullet->Set(
					USER_PLAYER,
					pCameraData->posV,
					*pMouse->GetWorldPos()
				);

				//  音声の設定
				CManager::GetOpenAL()->Play(SOUND_LABEL_SE_CANNON, 1.0f, m_CharData.Pos.x, m_CharData.Pos.y, m_CharData.Pos.z);

				//  弾発射カウントをリセット
				m_BulletCnt = BULLET_SHOT_COUNT;
			}

			//  連射中
			m_bFire = true;

			m_WeaponData[m_Weapon].fCoolDown += 0.0015f;

			//  オーバーヒットすれば、発射不可
			if (m_WeaponData[m_Weapon].fCoolDown > 1.0f)
			{
				m_WeaponData[m_Weapon].fCoolDown = 1.0f;
				m_WeaponData[m_Weapon].bFlag = FALSE;
			}
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::WeaponMissileUpdate(void)
//	引数:	なし
//	戻り値:	なし
//	説明:	ミサイルの更新
//------------------------------------------------------------------------------
void CPlayer::WeaponMissileUpdate(void)
{
	CKeyboard		*pKeyboard = CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse = CManager::GetInput()->GetMouse();
	CMissile		*pMissile = CManager::GetMissile();
	CHamina_Data	*pHaminaData = CManager::GetHamina()->GetHaminaData();
	CMissile_Data	*pMissileData = CManager::GetMissile()->GetMissileData();

	float			fDistance[nHamina_Max];
	int				nEnemyNum = 0;
	int				nEnemyID[nHamina_Max];

	if (m_WeaponData[m_Weapon].bFlag)
	{
		if (pMouse->GetRelease(DIM_LEFT))
		{
			//  ミサイル発射処理
			//  射程範囲内の敵を洗い出す
			for (int i = 0; i < nHamina_Max; i++)
			{
				if ((pHaminaData + i)->CharData.bFlag)
				{
					if ((pHaminaData + i)->AIType != HAMINA_DEAD)
					{
						if ((pHaminaData + i)->fDistance >= 2000.0f && (pHaminaData + i)->fDistance <= 7500.0f)
						{
							fDistance[nEnemyNum] = (pHaminaData + i)->fDistance;
							nEnemyID[nEnemyNum] = i;
							nEnemyNum++;
						}
					}
				}
			}

			if (nEnemyNum > 0)
			{
				//  一番遠い敵を洗い出す
				for (int i = 0; i < nEnemyNum - 1; i++)
				{
					if (fDistance[i] > fDistance[i + 1])
					{
						float tmp = fDistance[i + 1];
						int tmpID = nEnemyID[i + 1];

						fDistance[i + 1] = fDistance[i];
						fDistance[i] = tmp;

						nEnemyID[i + 1] = nEnemyID[i];
						nEnemyID[i] = tmpID;
					}
				}

			//  一番遠い敵艦をロック
				pMissile->Set(&(pHaminaData + nEnemyID[nEnemyNum - 1])->CharData.Pos, m_MissileID[4 - m_WeaponData[WEAPON_MISSILE].nNum]);
				(pMissile->GetMissileData() + m_MissileID[4 - m_WeaponData[WEAPON_MISSILE].nNum])->SetLockShipID(nEnemyID[nEnemyNum - 1]);
				CManager::GetOpenAL()->Play(SOUND_LABEL_SE_MISSILE, 1.0f, m_CharData.Pos.x, m_CharData.Pos.y, m_CharData.Pos.z);

				m_WeaponData[m_Weapon].nNum -= 1;
			}

			//  ミサイル残弾0ならば、使用不可能
			m_WeaponData[m_Weapon].bFlag = m_WeaponData[m_Weapon].nNum == 0 ? false : true;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CPlayer::WeaponRepairUpdate(void)
//	引数:	なし
//	戻り値:	なし
//	説明:	緊急修理の更新
//------------------------------------------------------------------------------
void CPlayer::WeaponRepairUpdate(void)
{
	CKeyboard		*pKeyboard = CManager::GetInput()->GetKeyboard();
	CMouse			*pMouse = CManager::GetInput()->GetMouse();

	if (m_WeaponData[WEAPON_REPAIR].bFlag)
	{
		if (pMouse->GetTrigger(DIM_LEFT))
		{
			m_WeaponData[WEAPON_REPAIR].nNum--;
			m_WeaponData[WEAPON_REPAIR].bFlag = false;

			//  ライフ50回復
			m_CharData.nLife += 50;
			m_CharData.nLife = m_CharData.nLife > 100 ? 100 : m_CharData.nLife;
		}
	}
}