//------------------------------------------------------------------------------
//	タイトル：		弾の関数
//	ファイル名：	bullet.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/11/29
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "bullet.h"
#include "manager.h"
#include "Func.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "tutorial.h"
#include "player.h"
#include "meshField.h"
#include "openAL.h"
#include "time.h"
#include <typeinfo.h>
#include "water.h"
#include "effect.h"
#include "enemy.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------

const float fCheck_Sea = -15.0f;		//  弾と海の当たり判定を調整する係数
const int	nBullet_Life = 120;			//  弾の飛行寿命
const float	fBullet_Y_Max = 50.0f;		//  弾のY座標最大値
const D3DXVECTOR2 Bullet_Size_Player = D3DXVECTOR2(2.0f, 2.0f);
const D3DXVECTOR2 Bullet_Size_Enemy = D3DXVECTOR2(4.0f, 4.0f);
const float fBullet_Effective_Fire = 6000.0f;
const float fBullet_Check = 5.0f;
const D3DXVECTOR3 Water_Impact_Size = D3DXVECTOR3(50.0f, 100.0f, 0.0f);

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CBullet::CBullet
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBullet::CBullet(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;			//  頂点バッファへのポイント
	m_TextureBuffer	= NULL;			//  テクスチャバッファへのポイント
	m_TextureFile	= NULL;			//  テクスチャファイル
	m_ShotFrame	= 0;				//  シュートフレイム
	m_Gravity =						//  重力
	m_Distance = 0.0f;				//  距離
	m_Player = NULL;
}

//------------------------------------------------------------------------------
//	関数名:	CBullet::~CBullet
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CBullet::~CBullet()
{
}

//------------------------------------------------------------------------------
//	関数名:	CBullet *CBullet::Create
//	引数:	なし
//	戻り値:	pBullet
//	説明:	ガトリングの生成
//------------------------------------------------------------------------------
CBullet *CBullet::Create(void)
{
	CBullet *pBullet;

	//  インスタンス生成
	pBullet = new CBullet;

	pBullet->m_TextureFile = PLAYER_SHOT_TEXTURE_FILE;

	//  テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		pBullet->m_TextureFile,				//  テクスチャファイル位置
		&pBullet->m_TextureBuffer				//  テクスチャバッファへのポインタ
	);

	//  初期化
	pBullet->Init();

	return pBullet;
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CBullet::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点情報の作成
	MakeVertex(pDevice);

	m_Player = CManager::GetPlayer();
	m_Water = CManager::GetWater();
	m_Effect = CManager::GetEffect();
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CBullet::Uninit(void)
{
	//テクスチャバッファの開放
	SAFE_RELEASE(m_TextureBuffer);

	//頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);

	m_TextureFile = NULL;

	m_Player = NULL;
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CBullet::Update(void)
{
	for (int i = 0; i < nBullet_Max; i++)
	{
		if (m_Bullet[i].Flag)
		{
			switch (m_Bullet[i].UserType)
			{
			//  プレイヤー使用者
			case USER_PLAYER:
				PlayerBulletUpdate(i);
				break;
			//  敵使用者
			case USER_ENEMY:
				EnemyBulletUpdate(i);
				break;
			}
		}
	}

	SetVertex();
}

void CBullet::PlayerBulletUpdate(int nID)
{
	float fHeight;
	float fDistance;
	CMode			*pMode = CManager::GetMode();
	CHamina_Data *pHaminaData = CManager::GetHamina()->GetHaminaData();

	if (m_Bullet[nID].Life > 0)
	{
		m_Bullet[nID].Pos += m_Bullet[nID].Vector * m_Bullet[nID].Speed;

		if (typeid(*pMode).name() == typeid(CGame).name())
		{
			//  船に当たった処理
			for (int i = 0; i < nHamina_Max; i++)
			{
				for (int j = 0; j < nHamina_Obb_Max; j++)
				{
					fDistance = CManager::GetFunc()->LenOBBToPoint((pHaminaData + i)->Obb[j], m_Bullet[nID].Pos);
					if (fDistance <= 5.0f)
					{
						m_Bullet[i].Flag = false;

						//  爆発エフェクトと音声の処理
						ExplosionUpdate(nID);

						(pHaminaData + i)->AddLife((int)(-12 * j * 0.3f));
						break;
					}
				}
			}
		}
		//  落水処理
		if (m_Bullet[nID].Flag)
		{
			fHeight = CManager::GetSea()->GetHeight(m_Bullet[nID].Pos);

			if (m_Bullet[nID].Pos.y <= fHeight - fBullet_Check)
			{
				m_Bullet[nID].Pos.y = fHeight;
				m_Bullet[nID].Flag = false;

				//  落水エフェクトと音声の処理
				WaterImpactUpdate(nID);
			}
		}
		m_Bullet[nID].Life--;
	}
	else
	{
		m_Bullet[nID].Flag = false;
	}
}

void CBullet::EnemyBulletUpdate(int nID)
{
	float fDistance;
	float fHeight;

	m_Bullet[nID].FlyTime--;

	//  移動処理
	m_Bullet[nID].Pos.x += m_Bullet[nID].Vector.x * m_Bullet[nID].Speed;
	m_Bullet[nID].Pos.z += m_Bullet[nID].Vector.z * m_Bullet[nID].Speed;
	m_Bullet[nID].Pos.y += m_Bullet[nID].Gravity;

	//  重力反転の処理
	if (!m_Bullet[nID].bGravityInvert)
	{
		//  弾が最高点に到達すれば（総飛行時間以下であれば）、重力反転
		m_Bullet[nID].Gravity = m_Bullet[nID].FlyTime <= m_Bullet[nID].FlyTimeHalf ? -m_Bullet[nID].Gravity : m_Bullet[nID].Gravity;
		m_Bullet[nID].bGravityInvert = true;
	}

	//  船に当たった処理
	for (int i = 0; i < nObbMax_P; i++)
	{
		//  弾とプレイヤー各OBBの距離を算出
		fDistance = CManager::GetFunc()->LenOBBToPoint(*m_Player->GetObb(i), m_Bullet[nID].Pos);
		if (fDistance <= fBullet_Check)
		{
			m_Bullet[nID].Flag = false;

			//  爆発エフェクトと音声処理
			ExplosionUpdate(nID);

			//  プレイヤーにダメージを設定
			m_Player->AddLife(-1);
			break;
		}
	}

	//  落水処理
	if (m_Bullet[nID].Flag)
	{
		//  海との距離（Y）を算出
		fHeight = CManager::GetSea()->GetHeight(m_Bullet[nID].Pos);

		if (m_Bullet[nID].Pos.y <= fHeight - fBullet_Check)
		{
			m_Bullet[nID].Pos.y = fHeight;
			m_Bullet[nID].Flag = false;

			//  落水エフェクトと音声処理
			WaterImpactUpdate(nID);
		}
	}
}

void CBullet::WaterImpactUpdate(int nID)
{
	float fVoiceDistance;
	float fVoiceRate;

	//  落水エフェクト
	m_Water->Set(
		m_Bullet[nID].Pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		Water_Impact_Size,
		EFFECT_WATER_IMPACT,
		false,
		true,
		true
	);

	//  音声源からプレイヤーまでの距離を算出
	fVoiceDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Bullet[nID].Pos);

	//  音声割合を算出（距離が聞こえる範囲内であれば、距離により算出　否:0.0fに設定）
	fVoiceRate = fVoiceDistance <= fVoice_Water_Distance ? 1.0f - fVoiceDistance / fVoice_Water_Distance : 0.0f;

	if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WATER_EXPLOSION, fVoiceRate, m_Bullet[nID].Pos.x, m_Bullet[nID].Pos.y, m_Bullet[nID].Pos.z);
}

void CBullet::ExplosionUpdate(int nID)
{
	float fVoiceDistance;
	float fVoiceRate;
	float fExplosionRate;

	srand((unsigned)time(NULL));

	//  ランダムに爆破規模を決める
	switch ((rand() % 5))
	{
	case 0:
		fExplosionRate = 0.9f;
		break;
	case 1:
		fExplosionRate = 1.0f;
		break;
	case 2:
		fExplosionRate = 0.75f;
		break;
	case 3:
		fExplosionRate = 1.2f;
		break;
	case 4:
		fExplosionRate = 0.6f;
		break;
	}

	//  爆発エフェクト
	m_Effect->SetEffect(
		m_Bullet[nID].Pos,
		D3DXVECTOR3(60.0f * fExplosionRate, 60.0f * fExplosionRate, 0.0f),
		EFFECT_EXPLOSION_000,
		false,
		true,
		true,
		true
	);

	//  音声源からプレイヤーまでの距離を算出
	fVoiceDistance = CManager::GetFunc()->GetDistance(*m_Player->GetPosition(), m_Bullet[nID].Pos);

	//  音声割合を算出（距離が聞こえる範囲内であれば、距離により算出　否:0.0fに設定）
	fVoiceRate = fVoiceDistance <= fVoice_Distance ? 1.0f - fVoiceDistance / fVoice_Distance : 0.0f;

	if (fVoiceRate > 0.0f)	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_CANNON_EXPLOSION, fVoiceRate, m_Bullet[nID].Pos.x, m_Bullet[nID].Pos.y, m_Bullet[nID].Pos.z);
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CBullet::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//  ライトを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  αテストを行う
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  αテスト合格基準
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  α参照値

	for (int i = 0; i < nBullet_Max; i++)
	{
		if (m_Bullet[i].Flag)
		{
			//  ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Bullet[i].Matrix.World);

			//  ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &m_Bullet[i].ViewMatrix);

			//  逆行列を求める
			D3DXMatrixInverse(&m_Bullet[i].Matrix.World, NULL, &m_Bullet[i].ViewMatrix);

			m_Bullet[i].Matrix.World._41 = 0.0f;
			m_Bullet[i].Matrix.World._42 = 0.0f;
			m_Bullet[i].Matrix.World._43 = 0.0f;

			//  スケールを反映
			D3DXMatrixScaling( &m_Bullet[i].Matrix.Scl, m_Bullet[i].Scl.x, m_Bullet[i].Scl.y, m_Bullet[i].Scl.z );
			D3DXMatrixMultiply( &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.Scl );

			//  回転を反映
			D3DXMatrixRotationYawPitchRoll( &m_Bullet[i].Matrix.Rot, m_Bullet[i].Rot.y, m_Bullet[i].Rot.x, m_Bullet[i].Rot.z );
			D3DXMatrixMultiply( &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.Rot );

			//  位置を反映
			D3DXMatrixTranslation( &m_Bullet[i].Matrix.Trans, m_Bullet[i].Pos.x, m_Bullet[i].Pos.y, m_Bullet[i].Pos.z );
			D3DXMatrixMultiply( &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.World, &m_Bullet[i].Matrix.Trans );

			//  ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &m_Bullet[i].Matrix.World);

			//  頂点バッファをデータストリームにバインドする
			pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

			//  頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//  テクスチャの設定
			pDevice->SetTexture(0, m_TextureBuffer);

			//  ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  ライトを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  αテストを行わない
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CBullet::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CBullet::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nBullet_Max,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								//  頂点バッファの使用法
		FVF_VERTEX_3D,									//  使用する頂点フォーマット
		D3DPOOL_MANAGED,								//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,								//  頂点バッファインターフェースへのポインタ
		NULL											//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nBullet_Max; i++, pVtx += nNumVertex )
	{
		//  頂点座標の設定
		pVtx[0].pos = 
		pVtx[1].pos = 
		pVtx[2].pos = 
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線の設定
		pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}
	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::Set
//	引数:	USER_TYPE User_Type, D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos
//	戻り値:	なし
//	説明:	弾の設定
//------------------------------------------------------------------------------
void CBullet::Set(USER_TYPE User_Type, D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	for (int i = 0; i < nBullet_Max; i++)
	{
		if (!m_Bullet[i].Flag)
		{
			m_Bullet[i].UserType = User_Type;
			m_Bullet[i].Pos = pos;
			m_Bullet[i].TargetPos = TargetPos;
			m_Bullet[i].Vector = TargetPos - pos;
			D3DXVec3Normalize(&m_Bullet[i].Vector, &m_Bullet[i].Vector);
			m_Bullet[i].CheckSea = false;
			m_Bullet[i].Flag = true;
			m_Bullet[i].Speed = User_Type == USER_PLAYER ? fBullet_Speed_Player : fBullet_Speed_Enemy;
			m_Bullet[i].Size = User_Type == USER_PLAYER ? Bullet_Size_Player : Bullet_Size_Enemy;
			m_Bullet[i].Life = nBullet_Life;

			if (User_Type == USER_ENEMY)
			{
				//  プレイヤーとの距離を算出
				m_Bullet[i].Distance = CManager::GetFunc()->GetDistance(TargetPos, pos);
				m_Bullet[i].Distance = m_Bullet[i].Distance > fBullet_Effective_Fire ? fBullet_Effective_Fire : m_Bullet[i].Distance;

				//  飛行時間を算出
				m_Bullet[i].FlyTime = (int)(m_Bullet[i].Distance / m_Bullet[i].Speed);
				m_Bullet[i].FlyTimeHalf = m_Bullet[i].FlyTime / 2;
				m_Bullet[i].bGravityInvert = false;

				//  Δ重力を算出
				m_Bullet[i].Gravity = (pos.y + fBullet_Y_Max * m_Bullet[i].Distance / fBullet_Effective_Fire) / m_Bullet[i].FlyTime;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::SetVertex
//	引数:	なし
//	戻り値:	なし
//	説明:	頂点情報の更新
//------------------------------------------------------------------------------
void CBullet::SetVertex(void)
{
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nBullet_Max; i++, pVtx += nNumVertex)
	{
		if (m_Bullet[i].Flag)
		{
			//  頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-m_Bullet[i].Size.x * 0.5f, m_Bullet[i].Size.y * 0.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_Bullet[i].Size.x * 0.5f, m_Bullet[i].Size.y * 0.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-m_Bullet[i].Size.x * 0.5f, -m_Bullet[i].Size.y * 0.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_Bullet[i].Size.x * 0.5f, -m_Bullet[i].Size.y * 0.5f, 0.0f);
		}
	}
	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}