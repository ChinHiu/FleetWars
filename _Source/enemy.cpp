//------------------------------------------------------------------------------
//	タイトル：		Hamina敵の関数
//	ファイル名：	enemy_Hamina.cpp
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
#include "enemy.h"
#include "game.h"
#include "manager.h"
#include "title.h"
#include "game.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include <typeinfo.h>
#include "meshField.h"
#include "missile.h"
#include "obbTest.h"
#include "bullet.h"
#include "stencilShadow.h"
#include "effect.h"
#include "openAL.h"
#include "time.h"
#include "Func.h"
#include "userMap.h"
#include "sprayBehide.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const float fHamina_PosY_Adjust = 25.0f;
const float fHamina_Speed_Max = 3.0f;

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define POSY_ADJUST (25.0f)
#define SPEED_MAX	(2.5f)
#define HAMINA_BATTERY_ROT_ZONE (0.5f)

#define HAMINA_SHIP_GUN_NUM				(50)
#define HAMINA_MISSILE_NUM				(1)

#define HAMINA_SHIP_GUN_REPAIRTIME		(15)
#define HAMINA_MISSILE_REPAIRTIME		(60)

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------
//  各Obb相対位置
const D3DXVECTOR3 g_ObbRelativePos[] =
{
	D3DXVECTOR3(0.0f, -38.0f, 0.0f),
	D3DXVECTOR3(0.0f, -10.0f, 36.0f),
	D3DXVECTOR3(0.0f, 10.0f, 20.0f),
	D3DXVECTOR3(0.0f, 40.0f, 20.0f),
	D3DXVECTOR3(0.0f, 0.0f, 192.0f)
};

//  各Obb三軸の長さ
const D3DXVECTOR3 g_ObbLength[] =
{
	D3DXVECTOR3(34.0f, 18.0f, 220.0f),
	D3DXVECTOR3(32.0f, 10.0f, 114.0f),
	D3DXVECTOR3(26.0f, 10.0f, 63.0f),
	D3DXVECTOR3(20.0f, 20.0f, 20.0f),
	D3DXVECTOR3(7.0f, 18.0f, 7.0f)
};

const int nHamina_Life = 30;

//  水飛沫（前）の変位量
const D3DXVECTOR3 g_SprayBeforeDeviationPos[] =
{
	D3DXVECTOR3(-4.0f, -40.0f, -210.0f),
	D3DXVECTOR3(4.0f, -40.0f, -210.0f)
};

//  水飛沫（前）のサイズ
const D3DXVECTOR3 g_SprayBeforeSize = D3DXVECTOR3(150.0f, 50.0f, 0.0f);

//  水飛沫（後ろ）の変位量
const D3DXVECTOR3 g_SprayBehideDeviationPos = D3DXVECTOR3(0.0f, -30.0f, 170.0f);

//  水飛沫（後ろ）のサイズ
const D3DXVECTOR3 g_SprayBehideSize = D3DXVECTOR3(100.0f, 0.0f, 300.0f);

//------------------------------------------------------------------------------
//	関数名:	CEnemy_Hamina::CEnemy_Hamina
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CEnemy_Hamina::CEnemy_Hamina(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_Type = MODEL_HAMINA;
}

//------------------------------------------------------------------------------
//	関数名:	CEnemy_Hamina::~CEnemy_Hamina
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CEnemy_Hamina::~CEnemy_Hamina()
{
}

//------------------------------------------------------------------------------
//	関数名:	CEnemy_Hamina *CEnemy_Hamina::Create
//	引数:	なし
//	戻り値:	pHamina
//	説明:	Hamina敵の生成
//------------------------------------------------------------------------------
CEnemy_Hamina *CEnemy_Hamina::Create(void)
{
	CEnemy_Hamina *pHamina;
	pHamina = new CEnemy_Hamina;

	pHamina->Init();

	return pHamina;
}

//------------------------------------------------------------------------------
//	関数名:	void CEnemy_Hamina::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CEnemy_Hamina::Init(void)
{
	CMode *pMode = CManager::GetMode();

	//  船中心点からミサイルの偏移量の初期化
	m_MissileDeviationPos = D3DXVECTOR3(0.0f, 6.0f, 192.8f);

	for (int i = 0; i < nHamina_Max; i++)
	{
		m_Hamina[i].Model[HAMINA_BODY] = CModel::Create(
			MODEL_HAMINA,
			MODEL_PARTS_HAMINA_BODY,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		);

		m_Hamina[i].Model[HAMINA_BATTERY] = CModel::Create(
			MODEL_HAMINA,
			MODEL_PARTS_HAMINA_BATTERY,
			D3DXVECTOR3(0.0f, -10.0f, -125.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		);

		m_Hamina[i].Model[HAMINA_GUN] = CModel::Create(
			MODEL_HAMINA,
			MODEL_PARTS_HAMINA_GUN,
			D3DXVECTOR3(0.0f, 3.5f, -3.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		);

		//  モデル親の設定
		m_Hamina[i].Model[HAMINA_BODY]->SetParent(NULL);
		m_Hamina[i].Model[HAMINA_BATTERY]->SetParent(m_Hamina[i].Model[HAMINA_BODY]);
		m_Hamina[i].Model[HAMINA_GUN]->SetParent(m_Hamina[i].Model[HAMINA_BATTERY]);
	}

	//CMissile *pMissile = CManager::GetMissile();

	for (int i = 0; i < nHamina_Max; i++)
	{
		D3DXVECTOR3	ObbPos;

		//  マトリクスの更新
		MatrixUpdate(i);

		//  Obbの設定
		for (int j = 0; j < nHamina_Obb_Max; j++)
		{
			D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[j], &m_Hamina[i].Matrix.World);														//  Obb位置を算出
			m_Hamina[i].Obb[j].SetPos(ObbPos);																										//  Obb位置を設定
			m_Hamina[i].Obb[j].SetLength(g_ObbLength[j]);																							//  Obb各軸長さを設定
			m_Hamina[i].Obb[j].SetDirect(X_AXIS, D3DXVECTOR3(m_Hamina[i].Matrix.Rot._11, m_Hamina[i].Matrix.Rot._12, m_Hamina[i].Matrix.Rot._13));	//  ObbのX軸方向ベクトルを設定
			m_Hamina[i].Obb[j].SetDirect(Y_AXIS, D3DXVECTOR3(m_Hamina[i].Matrix.Rot._21, m_Hamina[i].Matrix.Rot._22, m_Hamina[i].Matrix.Rot._23));	//  ObbのY軸方向ベクトルを設定
			m_Hamina[i].Obb[j].SetDirect(Z_AXIS, D3DXVECTOR3(m_Hamina[i].Matrix.Rot._31, m_Hamina[i].Matrix.Rot._32, m_Hamina[i].Matrix.Rot._33));	//  ObbのZ軸方向ベクトルを設定
			m_Hamina[i].ObbTest[j] = CObbTest::Create(m_Hamina[i].Obb[j].GetPos(), m_Hamina[i].CharData.Rot, g_ObbLength[j]);						//  Obbテスト立方体の設定
		}

		//  シャドウを設定
		m_Hamina[i].Shadow = CStencilShadow::Create(MODEL_HAMINA, m_Hamina[i].CharData.Pos);

		//  水飛沫の設定（前）
		m_Hamina[i].SprayBefore = CSpray::Create();

		for (int k = 0; k < SPRAY_TYPE_MAX; k++)
		{
			//  水しぶき
			m_Hamina[i].SprayBefore->Set(
				MODEL_GORSHKOV,
				&m_Hamina[i].SprayBeforePos[k],
				&m_Hamina[i].CharData.Rot,
				&m_Hamina[i].SprayBeforeSize,
				(SPRAY_TYPE)k,
				true
			);
		}

		//  水飛沫の設定（後ろ）
		CManager::GetSprayBehide()->Set(
			&m_Hamina[i].SprayBehidePos,
			&m_Hamina[i].CharData.Rot,
			&m_Hamina[i].SprayBehideSize,
			true
		);

		//m_Hamina[i].GunPos.SetDeviation(&m_Hamina[i].Pos, &m_Hamina[i].Rot, D3DXVECTOR3(0.0f, -6.5f, -125.0f));
	}

	m_Player = CManager::GetPlayer();
}

//------------------------------------------------------------------------------
//	関数名:	void CEnemy_Hamina::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CEnemy_Hamina::Uninit(void)
{
	for (int i = 0; i < nHamina_Max; i++)
	{
		for (int j = 0; j < HAMINA_PARTS_MAX; j++)
		{
			m_Hamina[i].Model[j]->Uninit();
		}

		m_Hamina[i].Shadow->Uninit();

		m_Hamina[i].SprayBefore->Uninit();
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CEnemy_Hamina::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CEnemy_Hamina::Update(void)
{
	CMeshField		*pSea = CManager::GetSea();

	for (int i = 0; i < nHamina_Max; i++)
	{
		if (m_Hamina[i].CharData.bFlag)
		{
			float fAimDistance;
			float fAimTime;
			float RotY;

			//  ユーザーマップ
			CManager::GetUserMap()->SensorCheck(&m_Hamina[i].bUserMap, m_Hamina[i].CharData.Pos, ENEMY);

			if (m_Hamina[i].CharData.nLife > 0)
			{
				//  ミサイルをリセット
				if (m_Hamina[i].WeaponData[HAMINA_MISSILE].nCoolDown == 0)
				{
					m_Hamina[i].MissileID = CManager::GetMissile()->Reset(&m_Hamina[i].Matrix.World, USER_ENEMY, &m_Hamina[i].CharData.Pos, &m_Hamina[i].CharData.Rot, &m_Hamina[i].CharData.bFlag, m_MissileDeviationPos);
					m_Hamina[i].WeaponData[HAMINA_MISSILE].bFlag = true;
					m_Hamina[i].WeaponData[HAMINA_MISSILE].nNum = HAMINA_MISSILE_NUM;
					m_Hamina[i].WeaponData[HAMINA_MISSILE].nCoolDown = HAMINA_MISSILE_REPAIRTIME * 60;
				}
				//  ミサイル発射
				if (!m_Hamina[i].WeaponData[HAMINA_MISSILE].bFlag)
				{
					m_Hamina[i].WeaponData[HAMINA_MISSILE].nCoolDown--;
				}
				else
				{
					switch ((rand() % 10))
					{
					case 0:
						if (m_Hamina[i].fDistance >= 3000.0f)
						{
							CManager::GetMissile()->Set(m_Player->GetPosition(), m_Hamina[i].MissileID);
							m_Hamina[i].WeaponData[HAMINA_MISSILE].nNum--;
						}
						break;
					default:
						break;
					}

					if (m_Hamina[i].WeaponData[HAMINA_MISSILE].nNum == 0)	m_Hamina[i].WeaponData[HAMINA_MISSILE].bFlag = false;
				}


				//  戦艦砲をリセット
				if (m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nCoolDown == 0)
				{
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].bFlag = true;
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nNum = HAMINA_SHIP_GUN_NUM;
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nCoolDown = HAMINA_SHIP_GUN_REPAIRTIME * 60;
				}

				if (!m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].bFlag) {
					m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nCoolDown--;
				}
				else
				{
					if (m_Hamina[i].BatteryRot.y > 0.0f && m_Hamina[i].BatteryRot.y <= 0.55f || m_Hamina[i].BatteryRot.y < 0.0f && m_Hamina[i].BatteryRot.y >= -0.55f)
					{
						if (m_Hamina[i].GunCnt == 0)
						{
							CManager::GetBullet()->Set(
								USER_ENEMY,
								//m_Hamina[i].GunPos.GetPos(),
								m_Hamina[i].AimPos,
								*m_Player->GetPosition()
							);
							m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nNum--;
							m_Hamina[i].GunCnt = 240;
						}
						else
						{
							m_Hamina[i].GunCnt--;
						}

						if (m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].nNum == 0)	m_Hamina[i].WeaponData[HAMINA_SHIP_GUN].bFlag = false;
					}
				}

				//  戦艦砲を発射

				//  砲台は常にプレイヤーの進む方向のある程度距離に向いてる
				fAimDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Hamina[i].CharData.Pos);
				fAimTime = fAimDistance / fBullet_Speed_Enemy;
				m_Hamina[i].AimPos.x = m_Player->GetPosition()->x - fAimTime * *m_Player->GetSpeed() * m_Player->GetObb(0)->GetDirect(2).x;
				m_Hamina[i].AimPos.z = m_Player->GetPosition()->z - fAimTime * *m_Player->GetSpeed() * m_Player->GetObb(0)->GetDirect(2).z;
				m_Hamina[i].AimPos.y = m_Player->GetPosition()->y;
				RotY = CManager::GetFunc()->GetXZRot(m_Hamina[i].AimPos, m_Hamina[i].CharData.Pos);

				//  砲台の向きを更新
				m_Hamina[i].BatteryRot.y = RotY + D3DX_PI - m_Hamina[i].CharData.Rot.y;

				//  砲台の向きをチェック
				SAFE_ROTCHECK(m_Hamina[i].BatteryRot.y);

				//  砲台向きを更新
				m_Hamina[i].Model[HAMINA_BATTERY]->SetRot(m_Hamina[i].BatteryRot);

				m_Hamina[i].VectorToPlayer = *m_Player->GetPosition() - m_Hamina[i].CharData.Pos;

				m_Hamina[i].fDistance = D3DXVec3Length(&m_Hamina[i].VectorToPlayer);

				//  AI処理
				switch (m_Hamina[i].AIType)
				{
				case HAMINA_LEFT_LEADER:
					//  プレイヤーとの距離が近いならば、左回転する
					if (m_Hamina[i].fDistance < 3000.0f && m_Hamina[i].State != HAMINA_TURN_LEFT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z) - D3DX_PI);
						m_Hamina[i].State = HAMINA_TURN_LEFT;
					}
					else if (m_Hamina[i].fDistance > 5000.0f && m_Hamina[i].State != HAMINA_TURN_LEFT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z) - D3DX_PI);
						m_Hamina[i].State = HAMINA_TURN_LEFT;
					}

					if (m_Hamina[i].fMoveRot <= 0.0f)	m_Hamina[i].State = HAMINA_MOVE;

					m_LeftLeaderState = m_Hamina[i].State;
					break;
				case HAMINA_LEFT_NORMAL1:
					//  死ぬ以外の行動はリーダーと一緒
					if (m_LeftLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_LeftLeaderState;
					break;
				case HAMINA_LEFT_NORMAL2:
					//  死ぬ以外の行動はリーダーと一緒
					if (m_LeftLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_LeftLeaderState;
					break;
				case HAMINA_RIGHT_LEADER:
					//  プレイヤーとの距離が近いならば、右回転する
					if (m_Hamina[i].fDistance < 1500.0f && m_Hamina[i].State != HAMINA_TURN_RIGHT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(D3DX_PI - atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z));
						m_Hamina[i].State = HAMINA_TURN_RIGHT;
					}
					else if (m_Hamina[i].fDistance > 4500.0f && m_Hamina[i].State != HAMINA_TURN_RIGHT)
					{
						m_Hamina[i].fMoveRot = (float)fabs(D3DX_PI - atan2f(m_Hamina[i].VectorToPlayer.x, m_Hamina[i].VectorToPlayer.z));
						m_Hamina[i].State = HAMINA_TURN_RIGHT;
					}

					if (m_Hamina[i].fMoveRot <= 0.0f)	m_Hamina[i].State = HAMINA_MOVE;
					m_RightLeaderState = m_Hamina[i].State;
					break;
				case HAMINA_RIGHT_NORMAL1:
					//  死ぬ以外の行動はリーダーと一緒
					if (m_RightLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_RightLeaderState;
					break;
				case HAMINA_RIGHT_NORMAL2:
					//  死ぬ以外の行動はリーダーと一緒
					if (m_RightLeaderState != HAMINA_DEAD)	m_Hamina[i].State = m_RightLeaderState;
					break;
				case HAMINA_RAND:
					//  砲台の射撃不可能角度の場合、プレイヤーの方向によって、回転する
					if (m_Hamina[i].BatteryRot.y > -D3DX_PI && m_Hamina[i].BatteryRot.y <= -D3DX_PI * HAMINA_BATTERY_ROT_ZONE)
					{
						m_Hamina[i].State = HAMINA_TURN_LEFT;
					}

					if (m_Hamina[i].BatteryRot.y >= D3DX_PI * HAMINA_BATTERY_ROT_ZONE && m_Hamina[i].BatteryRot.y <= D3DX_PI)
					{
						m_Hamina[i].State = HAMINA_TURN_RIGHT;
					}

					//  他は直線移動
					if (m_Hamina[i].BatteryRot.y > 0.0f && m_Hamina[i].BatteryRot.y <= 0.55f || m_Hamina[i].BatteryRot.y < 0.0f && m_Hamina[i].BatteryRot.y >= -0.55f)
					{
						m_Hamina[i].State = HAMINA_MOVE;
					}
					break;
				default:
					break;
				}
			}
			else if(m_Hamina[i].CharData.nLife <= 0 && m_Hamina[i].State != HAMINA_DEAD)
			{
				float fVoiceDistance;
				float fVoiceRate;

				for (int j = 0; j < HAMINA_PARTS_MAX; j++)
				{
					m_Hamina[i].Model[j]->SetBroken(true);
				}

				CManager::GetEffect()->SetEffect(
					m_Hamina[i].CharData.Pos,
					D3DXVECTOR3(250.0f, 250.0f, 0.0f),
					EFFECT_EXPLOSION_001,
					false,
					true,
					true,
					true
				);

				//  音声源からプレイヤーまでの距離を算出
				fVoiceDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Hamina[i].CharData.Pos);

				//  音声割合を算出（距離が聞こえる範囲内であれば、距離により算出　否:0.0fに設定）
				fVoiceRate = fVoiceDistance <= fVoice_Distance ? 1.0f - fVoiceDistance / fVoice_Distance : 0.0f;

				if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_SHIP_EXPLOSION, fVoiceRate, m_Hamina[i].CharData.Pos.x, m_Hamina[i].CharData.Pos.y, m_Hamina[i].CharData.Pos.z);

				m_Hamina[i].State = HAMINA_DEAD;

				CManager::AddKillsNum(1);
			}

			//  状態ごとの処理
			switch (m_Hamina[i].State)
			{
			case HAMINA_MOVE:
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			case HAMINA_TURN_LEFT:
				m_Hamina[i].CharData.Rot.y -= 0.002f;
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			case HAMINA_TURN_RIGHT:
				m_Hamina[i].CharData.Rot.y += 0.002f;
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			case HAMINA_DEAD:
				m_Hamina[i].CharData.fSpeed -= m_Hamina[i].CharData.fSpeed > 0.0f ? 0.01f : 0.0f;
				m_Hamina[i].CharData.Pos.x -= m_Hamina[i].Obb[0].GetDirect(2).x * m_Hamina[i].CharData.fSpeed;
				m_Hamina[i].CharData.Pos.z -= m_Hamina[i].Obb[0].GetDirect(2).z * m_Hamina[i].CharData.fSpeed;
				break;
			default:
				break;
			}

			SAFE_ROTCHECK(m_Hamina[i].CharData.Rot.y);

			//  Y座標の処理
			if (m_Hamina[i].State != HAMINA_DEAD)
			{
				m_Hamina[i].CharData.Pos.y = pSea->GetHeight(m_Hamina[i].CharData.Pos) + fHamina_PosY_Adjust;
			}
			else
			{
				m_Hamina[i].CharData.Pos.y -= m_Hamina[i].CharData.Pos.y > -50.0f ? 0.2f : 0.0f;
				m_Hamina[i].CharData.bFlag = m_Hamina[i].CharData.Pos.y <= -50.0f ? false : true;
			}

			//  当たり判定
			//  当たり判定
			m_Hamina[i].bCollision = false;

			if (m_Hamina[i].fDistance > 0.0f && m_Hamina[i].fDistance < 700.0f)
			{
				m_Hamina[i].bCollision = CManager::GetFunc()->OBBs(*m_Player->GetObb(0), m_Hamina[i].Obb[0]);
			}

			if (m_Hamina[i].bCollision)
			{
				m_Hamina[i].CharData.Pos.x = m_Hamina[i].CharData.OldPos.x;
				m_Hamina[i].CharData.Pos.z = m_Hamina[i].CharData.OldPos.z;
				m_Hamina[i].CharData.Rot = m_Hamina[i].CharData.OldRot;
				m_Hamina[i].CharData.fSpeed -= m_Hamina[i].CharData.fSpeed <= 0.0f ? 0.0f : 0.005f;
			}

			//  水飛沫の更新
			//  水飛沫（前）の更新
			for (int k = 0; k < SPRAY_TYPE_MAX; k++)
			{
				D3DXVec3TransformCoord(&m_Hamina[i].SprayBeforePos[k], &g_SprayBeforeDeviationPos[k], &m_Hamina[i].Matrix.World);
				m_Hamina[i].SprayBeforePos[k].y = pSea->GetHeight(m_Hamina[i].SprayBeforePos[k]) - 25.0f;
			}
			m_Hamina[i].SprayBeforeSize = g_SprayBeforeSize * (m_Hamina[i].CharData.fSpeed / fHamina_Speed_Max);
			m_Hamina[i].SprayBefore->Update();

			//  水飛沫（後ろ）の更新
			D3DXVec3TransformCoord(&m_Hamina[i].SprayBehidePos, &g_SprayBehideDeviationPos, &m_Hamina[i].Matrix.World);
			m_Hamina[i].SprayBehideSize = g_SprayBehideSize * (m_Hamina[i].CharData.fSpeed / fHamina_Speed_Max);

			//  マトリクスの更新
			MatrixUpdate(i);

			//  Obb情報の更新
			ObbUpdate(i);

			//  シャドウ位置、回転の更新
			m_Hamina[i].Shadow->SetRot(m_Hamina[i].CharData.Rot);
			m_Hamina[i].Shadow->SetPos(m_Hamina[i].CharData.Pos);

			//  座標と回転を保存
			m_Hamina[i].CharData.OldPos = m_Hamina[i].CharData.Pos;
			m_Hamina[i].CharData.OldRot = m_Hamina[i].CharData.Rot;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CEnemy_Hamina::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CEnemy_Hamina::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < nHamina_Max; i++)
	{
		if (m_Hamina[i].CharData.bFlag)
		{
			
			m_Hamina[i].Shadow->Draw();

			//  ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &m_Hamina[i].Matrix.World);

			for (int j = 0; j < HAMINA_PARTS_MAX; j++)
			{
				//  パーツの描画
				m_Hamina[i].Model[j]->Draw();
			}

			//  船前の水飛沫を描画
			for (int k = 0; k < SPRAY_TYPE_MAX; k++)
			{
				m_Hamina[i].SprayBefore->Draw(k);
			}
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CEneny_Hamina::MatrixUpdate
//	引数:	int nID
//	戻り値:	なし
//	説明:	ワールドマトリックスの更新
//------------------------------------------------------------------------------
void CEnemy_Hamina::MatrixUpdate(int nID)
{
	//  ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Hamina[nID].Matrix.World);

	//  スケールを反映
	D3DXMatrixScaling(&m_Hamina[nID].Matrix.Scl, m_Hamina[nID].CharData.Scl.x, m_Hamina[nID].CharData.Scl.y, m_Hamina[nID].CharData.Scl.z);
	D3DXMatrixMultiply(&m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.Scl);

	//  回転を反映
	D3DXMatrixRotationYawPitchRoll(&m_Hamina[nID].Matrix.Rot, m_Hamina[nID].CharData.Rot.y, m_Hamina[nID].CharData.Rot.x, m_Hamina[nID].CharData.Rot.z);
	D3DXMatrixMultiply(&m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.Rot);

	//  位置を反映
	D3DXMatrixTranslation(&m_Hamina[nID].Matrix.Trans, m_Hamina[nID].CharData.Pos.x, m_Hamina[nID].CharData.Pos.y, m_Hamina[nID].CharData.Pos.z);
	D3DXMatrixMultiply(&m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.World, &m_Hamina[nID].Matrix.Trans);

}

//------------------------------------------------------------------------------
//	関数名:	void CEnemy_Hamina::ObbUpdate
//	引数:	int nID
//	戻り値:	なし
//	説明:	OBB情報の更新
//------------------------------------------------------------------------------
void CEnemy_Hamina::ObbUpdate(int nID)
{
	D3DXVECTOR3 ObbPos;

	for (int i = 0; i < nHamina_Obb_Max; i++)
	{
		D3DXVec3TransformCoord(&ObbPos, &g_ObbRelativePos[i], &m_Hamina[nID].Matrix.World);																//  Obb位置を算出
		m_Hamina[nID].Obb[i].SetPos(ObbPos);																											//  Obb位置を設定
		m_Hamina[nID].Obb[i].SetDirect(X_AXIS, D3DXVECTOR3(m_Hamina[nID].Matrix.Rot._11,m_Hamina[nID].Matrix.Rot._12, m_Hamina[nID].Matrix.Rot._13));	//  ObbのX軸方向ベクトルを設定
		m_Hamina[nID].Obb[i].SetDirect(Y_AXIS, D3DXVECTOR3(m_Hamina[nID].Matrix.Rot._21,m_Hamina[nID].Matrix.Rot._22, m_Hamina[nID].Matrix.Rot._23));	//  ObbのY軸方向ベクトルを設定
		m_Hamina[nID].Obb[i].SetDirect(Z_AXIS, D3DXVECTOR3(m_Hamina[nID].Matrix.Rot._31,m_Hamina[nID].Matrix.Rot._32, m_Hamina[nID].Matrix.Rot._33));	//  ObbのZ軸方向ベクトルを設定
		m_Hamina[nID].ObbTest[i]->SetPos(m_Hamina[nID].Obb[i].GetPos());																				//  Obbテスト立方体の位置を設定
		m_Hamina[nID].ObbTest[i]->SetRot(m_Hamina[nID].CharData.Rot);																					//  Obbテスト立方体の回転を設定
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CEnemy_Hamina::Set
//	引数:	D3DXVECTOR3 pos, D3DXVECTOR3 rot
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CEnemy_Hamina::Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, HAMINA_AI_TYPE AI_Type)
{
	for (int i = 0; i < nHamina_Max; i++)
	{
		if (!m_Hamina[i].CharData.bFlag)
		{
			m_Hamina[i].CharData.Pos = Pos;
			m_Hamina[i].CharData.OldPos = Pos;
			m_Hamina[i].CharData.Rot = Rot;
			m_Hamina[i].CharData.OldRot = Rot;
			m_Hamina[i].BatteryRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Hamina[i].CharData.fSpeed = SPEED_MAX;
			m_Hamina[i].CharData.nLife = nHamina_Life;
			m_Hamina[i].AIType = AI_Type;
			m_Hamina[i].CharData.bFlag = true;
			break;
		}
	}
}

CHamina_Data *CEnemy_Hamina::GetHaminaData(void)
{
	return &m_Hamina[0];
}

//void CEnemy_Hamina::SetMissileLock(bool bMissileLock, int nID)
//{ 
//	m_Hamina[nID].SetMissileLockFlag(bMissileLock);
//}