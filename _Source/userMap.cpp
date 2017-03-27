//------------------------------------------------------------------------------
//	タイトル：		ユーザーマップの関数
//	ファイル名：	userMap.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/06
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "userMap.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "tutorial.h"
#include "enemy.h"
#include "camera.h"
#include <typeinfo.h>
#include "enemy.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

// マップ素材のパラメータ
const LPCSTR g_UserMap[USERMAP_TYPE_MAX] =
{
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Background.png" },	
	{ "./data/TEXTURE/UI/GAME/Radar/Bullet_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Missile_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Jamming_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Sensor.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Limits.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Ship_Mark.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Target.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Target.png" },
	{ "./data/TEXTURE/UI/GAME/Radar/Radar_Frame.png" }
};

//------------------------------------------------------------------------------
//	関数名:	CUserMap::CUserMap
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CUserMap::CUserMap(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer	= NULL;		//  頂点バッファへのポイン
	for (int i = 0; i < USERMAP_TYPE_MAX; i++)
	{
		m_TextureBuffer[i] = NULL;		//  テクスチャへのポインタ
	}
}

//------------------------------------------------------------------------------
//	関数名:	CUserMap::~CUserMap
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CUserMap::~CUserMap()
{
}

//------------------------------------------------------------------------------
//	関数名:	CUserMap *CUserMap::Create
//	引数:	なし
//	戻り値:	pUserMap
//	説明:	ユーザーマップの生成
//------------------------------------------------------------------------------
CUserMap *CUserMap::Create(void)
{
	CUserMap *pUserMap;
	pUserMap = new CUserMap;

	for (int i = 0; i < USERMAP_TYPE_MAX; i++)
	{
		//  テクスチャの設定
		D3DXCreateTextureFromFile
		(
			CManager::GetRenderer()->GetDevice(),
			g_UserMap[i],										//  テクスチャファイル位置
			&pUserMap->m_TextureBuffer[i]						//  テクスチャバッファへのポインタ
		);
	}

	pUserMap->Init();

	return pUserMap;
}

//------------------------------------------------------------------------------
//	関数名:	void CUserMap::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CUserMap::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  画面サイズを取得
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  画面割合を取得
	float *pScreenRate = GetScreenRate();

	CMode *pMode = CManager::GetMode();

	//  ライダー情報の初期化
	m_UserMap[RADAR_BACKGROUNG].Pos =
	m_UserMap[BULLET_LIMITS].Pos =
	m_UserMap[MISSILE_LIMITS].Pos =
	m_UserMap[JAMMING_LIMITS].Pos =
	m_UserMap[RADAR_SENSOR].Pos =
	m_UserMap[RADAR_LIMITS].Pos =
	m_UserMap[PLAYER].Pos =
	m_UserMap[nUserMapMax - 1].Pos = D3DXVECTOR2(pScreenSize->x - 200.0f * *pScreenRate, pScreenSize->y - 200.0f * *pScreenRate);

	m_UserMap[RADAR_BACKGROUNG].Size =
	m_UserMap[BULLET_LIMITS].Size =
	m_UserMap[MISSILE_LIMITS].Size =
	m_UserMap[JAMMING_LIMITS].Size =
	m_UserMap[RADAR_SENSOR].Size =
	m_UserMap[RADAR_LIMITS].Size =
	m_UserMap[PLAYER].Size =
	m_UserMap[nUserMapMax - 1].Size = D3DXVECTOR2(350.0f * *pScreenRate, 350.0f * *pScreenRate);

	m_UserMap[RADAR_BACKGROUNG].Flag =
	m_UserMap[BULLET_LIMITS].Flag =
	m_UserMap[RADAR_SENSOR].Flag =
	m_UserMap[RADAR_LIMITS].Flag =
	m_UserMap[PLAYER].Flag =
	m_UserMap[nUserMapMax - 1].Flag = true;

	m_UserMap[RADAR_BACKGROUNG].Type = RADAR_BACKGROUNG;
	m_UserMap[BULLET_LIMITS].Type = BULLET_LIMITS;
	m_UserMap[MISSILE_LIMITS].Type = MISSILE_LIMITS;
	m_UserMap[JAMMING_LIMITS].Type = JAMMING_LIMITS;
	m_UserMap[RADAR_SENSOR].Type = RADAR_SENSOR;
	m_UserMap[RADAR_LIMITS].Type = RADAR_LIMITS;
	m_UserMap[PLAYER].Type = PLAYER;
	m_UserMap[nUserMapMax - 1].Type = RADAR_FRAME;

	m_TexSensorLength = sqrtf((m_UserMap[RADAR_SENSOR].Size.x * 0.5f ) * (m_UserMap[RADAR_SENSOR].Size.x * 0.5f) + (m_UserMap[RADAR_SENSOR].Size.y * 0.5f) * (m_UserMap[RADAR_SENSOR].Size.y * 0.5f));
	m_TexSensorAngle = atan2f(m_UserMap[RADAR_SENSOR].Size.x * 0.5f, m_UserMap[RADAR_SENSOR].Size.y * 0.5f);

	m_Sensor.Pos[0] = D3DXVECTOR2(pScreenSize->x - 200.0f * *pScreenRate, pScreenSize->y - 200.0f * *pScreenRate);
	m_Sensor.Size = D3DXVECTOR2(20.0f * *pScreenRate, 155.0f * *pScreenRate);
	m_Sensor.Angle = atan2f(m_Sensor.Size.x * 0.5f, m_Sensor.Size.y * 0.5f);

	m_WeaponLimitsAngle = atan2f(m_UserMap[BULLET_LIMITS].Size.x * 0.5f, (m_UserMap[BULLET_LIMITS].Size.y * 0.5f));

	m_CameraRotY = &CManager::GetCameraData()->rot.y;
	m_PlayerRotY = &CManager::GetPlayer()->GetRotation()->y;
	m_WeaponType = CManager::GetPlayer()->GetWeponType();

	//  頂点情報の作成
	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	関数名:	void CUI::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CUserMap::Uninit(void)
{
	//  頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);

	//  テクスチャバッファの開放
	for (int i = 0; i < USERMAP_TYPE_MAX; i++)
	{
		SAFE_RELEASE(m_TextureBuffer[i]);
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CUserMap::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CUserMap::Update(void)
{
	float *pScreenRate = GetScreenRate();

	m_Sensor.Rot -= D3DX_PI / 90.0f;

	SAFE_ROTCHECK(m_Sensor.Rot);

	m_Sensor.Pos[1].x = m_Sensor.Pos[0].x + sinf(m_Sensor.Angle + m_Sensor.Rot) * m_Sensor.Size.y;
	m_Sensor.Pos[1].y = m_Sensor.Pos[0].y + cosf(m_Sensor.Angle + m_Sensor.Rot) * m_Sensor.Size.y;

	m_Sensor.Pos[2].x = m_Sensor.Pos[0].x + sinf(m_Sensor.Rot) * m_Sensor.Size.y;
	m_Sensor.Pos[2].y = m_Sensor.Pos[0].y + cosf(m_Sensor.Rot) * m_Sensor.Size.y;

	for (int i = 0; i < nUserMapMax; i++)
	{
		if (m_UserMap[i].Col.a <= 0.0f)
		{
			m_UserMap[i].Flag = false;
		}

		switch (*m_WeaponType) {
		case WEAPON_BULLET:
			m_UserMap[BULLET_LIMITS].Flag = true;
			m_UserMap[MISSILE_LIMITS].Flag = false;
			m_UserMap[JAMMING_LIMITS].Flag = false;
			break;
		case WEAPON_MISSILE:
			m_UserMap[BULLET_LIMITS].Flag = false;
			m_UserMap[MISSILE_LIMITS].Flag = true;
			m_UserMap[JAMMING_LIMITS].Flag = false;
			break;
		default:
			m_UserMap[BULLET_LIMITS].Flag = false;
			m_UserMap[MISSILE_LIMITS].Flag = false;
			m_UserMap[JAMMING_LIMITS].Flag = false;
			break;
		}

		if (m_UserMap[i].Flag)
		{
			if ( m_UserMap[i].Type == ENEMY || m_UserMap[i].Type == USERMAP_MISSILE)
			{
				m_UserMap[i].Col.a -= 0.01f;
				m_UserMap[i].Size.x += 0.05f * *pScreenRate;
				m_UserMap[i].Size.y += 0.05f * *pScreenRate;
			}

			SetVertex(i);
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CUserMap::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CUserMap::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  ライト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////  フォグ無効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	////  αテストを行う
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  αテストの有効化
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  αテスト合格基準
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  α参照値

	for (int i = 0; i < nUserMapMax; i++)
	{
		if (m_UserMap[i].Flag)
		{
			//  テクスチャの設定
			pDevice->SetTexture(0, m_TextureBuffer[m_UserMap[i].Type]);

			////  Ｚテストを行う
			//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//  Ｚテスト有効化
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					//  Ｚ値の更新を行わないが、Ｚテストを有効化する
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				//  Ｚテスト合格基準

			//if (m_UserMap[i].Type == ENEMY || m_UserMap[i].Type] == FRIENDLY)
			//{

			//  ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);

			////  Ｚテストを行わない
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				//  Ｚテスト合格基準
		}
	}

	//  ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////  フォグ有効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	////  αテストを行わない
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  αテスト無効化
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CUserMap::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice, POLYGON *pPOLYGON
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CUserMap::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * nNumVertex * nUserMapMax,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								//  頂点バッファの使用法
		FVF_VERTEX_2D,									//  使用する頂点フォーマット
		D3DPOOL_MANAGED,								//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,								//  頂点バッファインターフェースへのポインタ
		NULL											//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nUserMapMax; i++, pVtx += nNumVertex)
	{
		pVtx[0].pos = D3DXVECTOR3(m_UserMap[i].Pos.x - m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y - m_UserMap[i].Size.y * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_UserMap[i].Pos.x + m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y - m_UserMap[i].Size.y * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_UserMap[i].Pos.x - m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y + m_UserMap[i].Size.y * 0.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_UserMap[i].Pos.x + m_UserMap[i].Size.x * 0.5f, m_UserMap[i].Pos.y + m_UserMap[i].Size.y * 0.5f, 0.0f);

		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		//  頂点カラーの設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_UserMap[i].Col;

		//  テクスチャ座標の設定
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
//	関数名:	void CUserMap::SetVertex
//	引数:	int nID
//	戻り値:	なし
//	説明:	頂点情報の更新
//------------------------------------------------------------------------------
void CUserMap::SetVertex(int nID)
{
	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//if (nID == RADAR_SENSOR)
	//{
		switch (nID)
		{
		case RADAR_SENSOR:
			pVtx[0].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			pVtx[1].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			pVtx[2].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_TexSensorAngle - m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			pVtx[3].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_TexSensorAngle + m_Sensor.Rot) * m_TexSensorLength,
				0.0f);
			break;
		case BULLET_LIMITS:
			pVtx[0].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			pVtx[1].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			pVtx[2].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle + *m_CameraRotY + *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			pVtx[3].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle - *m_CameraRotY - *m_PlayerRotY) * m_TexSensorLength,
				0.0f);
			break;
		case PLAYER:
			pVtx[0].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			pVtx[1].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y - cosf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			pVtx[2].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x - sinf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle + *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			pVtx[3].pos = D3DXVECTOR3(
				m_UserMap[nID].Pos.x + sinf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				m_UserMap[nID].Pos.y + cosf(m_WeaponLimitsAngle - *m_PlayerRotY + D3DX_PI) * m_TexSensorLength,
				0.0f);
			break;
		default:
			pVtx[0].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x - m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y - m_UserMap[nID].Size.y * 0.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x + m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y - m_UserMap[nID].Size.y * 0.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x - m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y + m_UserMap[nID].Size.y * 0.5f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(m_UserMap[nID].Pos.x + m_UserMap[nID].Size.x * 0.5f, m_UserMap[nID].Pos.y + m_UserMap[nID].Size.y * 0.5f, 0.0f);
			break;
		}
	/*}*/

	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	//  頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_UserMap[nID].Col;

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CBullet::SetBullet
//	引数:	int nPatternAnim, int nPatternX, int nPatternY
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CUserMap::Set(int *nID, D3DXVECTOR2 pos, USERMAP_TYPE type)
{
	//  画面割合を取得
	float *pScreenRate = GetScreenRate();
	//int j = 0;

	//if (type == USERMAP_MISSILE)
	//{
	//	j = HAMINA_MAX;
	//}

	for (int i = 7; i < nUserMapMax -1; i++)
	{
		if (!m_UserMap[i].Flag)
		{
			m_UserMap[i].Pos = pos;
			m_UserMap[i].Type = type;
			m_UserMap[i].Flag = true;
			m_UserMap[i].Size = D3DXVECTOR2(10.0f * *pScreenRate, 10.0f * *pScreenRate);
			switch (type)
			{
			case ENEMY:
				m_UserMap[i].Col = D3DXCOLOR(1.0f, 0.0f, 0.25f, 1.0f);
				m_UserMap[i].Size = D3DXVECTOR2(12.0f * *pScreenRate, 12.0f * *pScreenRate);
				break;
			case USERMAP_MISSILE:
				m_UserMap[i].Col = D3DXCOLOR(0.0f, 1.0f, 1.00f, 1.0f);
				m_UserMap[i].Size = D3DXVECTOR2(6.5f * *pScreenRate, 6.5f * *pScreenRate);
				break;
			}
			*nID = i;
			break;
		}
	}
}

int CUserMap::SensorCheck(bool *check, D3DXVECTOR3 pos, USERMAP_TYPE type)
{
	int nID;
	float length, angle, rot;
	D3DXVECTOR3	VectorVertex[3], VectorTarget[3], VectorResult[3], SensorPos[3], EnemyPos;
	D3DXVECTOR2 EnemyVector, EnenyMapPos, EnemyRotPos;
	CPlayer *pPlayer = CManager::GetPlayer();
	D3DXVECTOR3 *PlayerPos = pPlayer->GetPosition();
	D3DXVECTOR3 *PlayerRot = pPlayer->GetRotation();
	float *fScreenRate = GetScreenRate();

	//  プレイヤーから敵までのベクトルを算出
	EnemyVector.x = -(pos.x - PlayerPos->x) / (75.0f / *fScreenRate);
	EnemyVector.y = (pos.z - PlayerPos->z ) / (75.0f / *fScreenRate);

	length = sqrtf((EnemyVector.x * EnemyVector.x ) + ( EnemyVector.y * EnemyVector.y));
	angle = atan2f(EnemyVector.x, EnemyVector.y);

	rot = -angle - D3DX_PI * 0.5f;

	SAFE_ROTCHECK(rot);

	EnemyRotPos.x = -cosf(rot) * length;
	EnemyRotPos.y = -sinf(rot) * length;

	//  マップの座標を一定割合で算出
	EnenyMapPos = m_UserMap[nUserMapMax - 1].Pos - EnemyRotPos;

	//  あたり判定用敵座標の変換
	EnemyPos.x = EnenyMapPos.x;
	EnemyPos.y = 0.0f;
	EnemyPos.z = EnenyMapPos.y;

	for (int i = 0; i < 3; i++)
	{
		SensorPos[i].x = m_Sensor.Pos[i].x;
		SensorPos[i].y = 0.0f;
		SensorPos[i].z = m_Sensor.Pos[i].y;
	}

	//  プリミティブのベクトルを計算
	VectorVertex[0] = SensorPos[1] - SensorPos[0];
	VectorVertex[1] = SensorPos[2] - SensorPos[1];
	VectorVertex[2] = SensorPos[0] - SensorPos[2];

	//  対象のベクトルを計算
	VectorTarget[0] = EnemyPos - SensorPos[0];
	VectorTarget[1] = EnemyPos - SensorPos[1];
	VectorTarget[2] = EnemyPos - SensorPos[2];

	for (int i = 0; i < 3; i++)
	{
		//  ベクトルＹ座標を０に設定
		VectorVertex[i].y =
		VectorTarget[i].y = 0.0f;

		//  対象がプリミティブ各辺の左右どちらかにいるの計算（外積）
		D3DXVec3Cross(&VectorResult[i], &VectorTarget[i], &VectorVertex[i]);
	}

	//  左右プリミティブどちらにいるチェック
	if (VectorResult[0].y >= 0)
	{//  左プリミティブにいる場合
		if (VectorResult[1].y >= 0)
		{
			if (VectorResult[2].y >= 0)
			{
				*check = true;
				Set(&nID, EnenyMapPos, type);
			}
		}
		else
		{
			*check = false;
		}
		
	}
	else
	{
		*check = false;
	}
	return nID;
}

bool CUserMap::GetUserMapFlag(int nID)
{
	return m_UserMap[nID].Flag;
}

D3DXVECTOR2 *CUserMap::GetUserMapPos(void)
{
	return &m_UserMap[7].Pos;
}