//------------------------------------------------------------------------------
//	タイトル：		ミサイルの関数
//	ファイル名：	missile.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/03
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "model.h"
#include "missile.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "meshField.h"
#include <time.h>
#include "openAL.h"
#include "effect.h"
#include "Func.h"
#include "userMap.h"
#include "enemy.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
const D3DXVECTOR3 AxisYVectorUP = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CMissile::CMissile
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CMissile::CMissile(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_Model	= NULL;			//  モデルへのポイント
}

//------------------------------------------------------------------------------
//	関数名:	CMissile::~CMissile
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CMissile::~CMissile()
{
}

//------------------------------------------------------------------------------
//	関数名:	CMissile *CMissile::Create
//	引数:	なし
//	戻り値:	pBullet
//	説明:	ガトリングの生成
//------------------------------------------------------------------------------
CMissile *CMissile::Create(void)
{
	CMissile *pMissile;

	//  インスタンス生成
	pMissile = new CMissile;

	//  初期化
	pMissile->Init();

	return pMissile;
}

//------------------------------------------------------------------------------
//	関数名:	void CMissile::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CMissile::Init(void)
{
	m_Model = CModel::Create(
		MODEL_MISSILE,
		MODEL_PARTS_MISSILE,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);

	m_Model->SetParent(NULL);
}

//------------------------------------------------------------------------------
//	関数名:	void CMissile::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CMissile::Uninit(void)
{
	m_Model->Uninit();
}

//------------------------------------------------------------------------------
//	関数名:	void CMissile::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CMissile::Update(void)
{
	CEffect *pEffect = CManager::GetEffect();
	CPlayer *pPlayer = CManager::GetPlayer();

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (m_Missile[i].Flag)
		{
			if (m_Missile[i].UserType == USER_ENEMY && m_Missile[i].State != MISSILE_STATE_NONE)
			{
				CManager::GetUserMap()->SensorCheck(&m_Missile[i].bUserMap, m_Missile[i].Pos, USERMAP_MISSILE);
			}

			if (!m_Missile[i].ShipFlag)
			{
				m_Missile[i].Flag = false;
			}

			switch (m_Missile[i].State)
			{
			case MISSILE_READY:
				m_Missile[i].Speed += m_Missile[i].Speed <= 3.0f ? 0.1f : 0.5f;
				m_Missile[i].Pos.y += m_Missile[i].Speed;

				//  次の状態へ
				if (m_Missile[i].Speed > 15.0f)	m_Missile[i].State = MISSILE_RISE;
				break;
			case MISSILE_RISE:
				m_Missile[i].Speed += 0.5f;
				m_Missile[i].Pos.y += m_Missile[i].Speed;

				//  次の状態へ
				if (m_Missile[i].Pos.y > m_Missile[i].TargetPos->y + 2500.0f)
				{
					//  親マトリックスを切る
					D3DXVec3TransformCoord(&m_Missile[i].Pos, &m_Missile[i].Pos, m_Missile[i].ShipMatrix);
					m_Missile[i].bParent = false;
					m_Missile[i].State = MISSILE_PURSUIT;
				}
				break;
			case MISSILE_PURSUIT:
				m_Missile[i].Speed = 3.0f;
				m_Missile[i].Vector = *m_Missile[i].TargetPos - m_Missile[i].Pos;
				D3DXVec3Normalize(&m_Missile[i].Vector, &m_Missile[i].Vector);
				m_Missile[i].Gravity += m_Missile[i].Gravity >= 15.0f ? 0.0f : 0.2f;

				m_Missile[i].Rot.y = atan2f(m_Missile[i].Vector.x, m_Missile[i].Vector.z) + D3DX_PI;
				m_Missile[i].Rot.x = D3DXVec3Dot(&AxisYVectorUP, &m_Missile[i].Vector);

				m_Missile[i].Pos += m_Missile[i].Vector * (m_Missile[i].Speed + m_Missile[i].Gravity);

				if (m_Missile[i].Pos.y <= m_Missile[i].TargetPos->y + 20.0f)	m_Missile[i].State = MISSILE_EXPLOSION;
				break;
			case MISSILE_EXPLOSION:
				float fVoiceDistance;
				float fVoiceRate;

				m_Missile[i].State = MISSILE_STATE_MAX;
				m_Missile[i].Flag = false;

				if (m_Missile[i].UserType == USER_PLAYER)
				{
					(CManager::GetHamina()->GetHaminaData() + m_Missile[i].LockShipID)->AddLife(-15);
					m_Missile[i].UserType = USER_NONE;
				}

				if (m_Missile[i].UserType == USER_ENEMY)
				{
					m_Missile[i].UserType = USER_NONE;
					pPlayer->AddLife(-5);
				}

				pEffect->SetEffect(
					m_Missile[i].Pos,
					D3DXVECTOR3(150.0f, 150.0f, 0.0f),
					EFFECT_EXPLOSION_001,
					false,
					true,
					true,
					true
				);

				//  音声源からプレイヤーまでの距離を算出
				fVoiceDistance = CManager::GetFunc()->GetDistance(*pPlayer->GetPosition(), m_Missile[i].Pos);
			
				//  音声割合を算出（距離が聞こえる範囲内であれば、距離により算出　否:0.0fに設定）
				fVoiceRate = fVoiceDistance <= fVoice_Distance ? 1.0f - fVoiceDistance / fVoice_Distance : 0.0f;

				if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_MISSILE_EXPLOSION, fVoiceRate, m_Missile[i].Pos.x, m_Missile[i].Pos.y, m_Missile[i].Pos.z);
				break;
			default:
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CMissile::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CMissile::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (m_Missile[i].Flag)
		{
			D3DXMATRIX		pParentMatrix;

			//  ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Missile[i].Matrix.World);

			//  親マトリックスの初期化
			D3DXMatrixIdentity(&pParentMatrix);

			//  親の設定
			if (m_Missile[i].bParent)	pParentMatrix = *m_Missile[i].ShipMatrix;

			//  スケールを反映
			D3DXMatrixScaling( &m_Missile[i].Matrix.Scl, m_Missile[i].Scl.x, m_Missile[i].Scl.y, m_Missile[i].Scl.z );
			D3DXMatrixMultiply( &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.Scl );

			//  回転を反映
			D3DXMatrixRotationYawPitchRoll( &m_Missile[i].Matrix.Rot, m_Missile[i].Rot.y, m_Missile[i].Rot.x, m_Missile[i].Rot.z );
			D3DXMatrixMultiply( &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.Rot );

			//  位置を反映
			D3DXMatrixTranslation( &m_Missile[i].Matrix.Trans, m_Missile[i].Pos.x, m_Missile[i].Pos.y, m_Missile[i].Pos.z );
			D3DXMatrixMultiply( &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &m_Missile[i].Matrix.Trans );

			//  親のマトリックスを反映
			if (m_Missile[i].bParent)	D3DXMatrixMultiply(&m_Missile[i].Matrix.World, &m_Missile[i].Matrix.World, &pParentMatrix);

			//  ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &m_Missile[i].Matrix.World);

			m_Model->Draw();
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CMissile::Set
//	引数:	D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CMissile::Set(D3DXVECTOR3 *TargetPos, int nID)
{
	m_Missile[nID].TargetPos = TargetPos;
	m_Missile[nID].State = MISSILE_READY;
	m_Missile[nID].Speed = 0.0f;
	m_Missile[nID].Gravity = 0.0f;
	m_Missile[nID].Life = 3;
	m_Missile[nID].bUserMap = false;
}

int	CMissile::Reset(D3DXMATRIX *ShipMatrix, USER_TYPE User_Type, D3DXVECTOR3 *ShipPos, D3DXVECTOR3 *ShipRot, bool *bShipFlag, D3DXVECTOR3 DeviationPos)
{
	int nID;

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (!m_Missile[i].Flag)
		{
			m_Missile[i].ShipMatrix = ShipMatrix;
			m_Missile[i].Rot = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);
			m_Missile[i].ShipPos = ShipPos;
			m_Missile[i].ShipRot = ShipRot;
			m_Missile[i].ShipFlag = bShipFlag;
			m_Missile[i].Pos = 
			m_Missile[i].DeviationPos = DeviationPos;
			m_Missile[i].DeviationRot = atan2f(DeviationPos.x, DeviationPos.z);
			m_Missile[i].Radius = sqrtf(DeviationPos.x * DeviationPos.x + DeviationPos.z * DeviationPos.z);
			m_Missile[i].UserType = User_Type;
			m_Missile[i].CheckSea = false;
			m_Missile[i].State = MISSILE_STATE_NONE;
			m_Missile[i].Flag = true;
			m_Missile[i].bParent = true;
			nID = i;
			break;
		}
	}

	return nID;
}

CMissile_Data *CMissile::GetMissileData(void)
{
	return &m_Missile[0];
}