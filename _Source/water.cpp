//------------------------------------------------------------------------------
//	タイトル：		水エフェクトの関数
//	ファイル名：	water.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/09/27
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "water.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "title.h"
#include "player.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CWater::CWater
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CWater::CWater(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  頂点バッファへのポイント
}

//------------------------------------------------------------------------------
//	関数名:	CWater::~CWater
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CWater::~CWater()
{
}

//------------------------------------------------------------------------------
//	関数名:	CWater *CWater::Create
//	引数:	なし
//	戻り値:	pEffect
//	説明:	エフェクトの生成
//------------------------------------------------------------------------------
CWater *CWater::Create(void)
{
	CWater *pWater;

	//  インスタンス生成
	pWater = new CWater;

	for (int i = 0; i <= EFFECT_WATER_IMPACT; i++)
	{
		switch (i)
		{
		case EFFECT_WATER_FALL_000:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		case EFFECT_WATER_FALL_001:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		case EFFECT_WATER_FALL_002:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		case EFFECT_WATER_IMPACT:
			pWater->m_InitAnim[i].PatternX = 8;
			pWater->m_InitAnim[i].PatternY = 4;
			pWater->m_InitAnim[i].Frame = 2;
			break;
		default:
			break;
		}
	}

	//  初期化
	pWater->Init();

	return pWater;
}

//------------------------------------------------------------------------------
//	関数名:	void CWater::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CWater::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点情報の作成
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	関数名:	void CWater::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CWater::Uninit(void)
{
	//頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CWater::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CWater::Update(void)
{
	for (int i = 0; i < nWater_Anim_Max; i++)
	{
		if (m_Water[i].Flag)
		{
			if (m_Water[i].Anim.PatternX != 1 && m_Water[i].Anim.PatternY != 1)
			{//  横パターンと縦パターンが１ではなければ、テクスチャアニメーション処理を行う
				//  テクスチャ座標の設定
				SetTexture(m_Water[i].Anim.Pattern, m_Water[i].Anim.PatternX, m_Water[i].Anim.PatternY, i);

				//  カウント
				m_Water[i].Anim.Cnt++;

				if (m_Water[i].Anim.Cnt == m_Water[i].Anim.Frame)
				{//  何フレームごとに更新
					m_Water[i].Anim.Cnt = 0;						//  アニメーションカウントの初期化
					m_Water[i].Anim.Pattern++;						//  アニメーション現在パターンを更新

					if (m_Water[i].Anim.Pattern == m_Water[i].Anim.PatternX * m_Water[i].Anim.PatternY)
					{//  全パターンを回したならば
						m_Water[i].Anim.Pattern = 0;				//  アニメーションパターン数の初期化
						if (!m_Water[i].AnimLoop)
						{//  ループではなければ
							m_Water[i].Flag = false;
						}
					}
				}
			}

			//  頂点情報の設定
			SetVertex(i);
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CWater::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CWater::Draw(void)
{
	CMode *pMode = CManager::GetMode();

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//  αテストを行う
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  αテスト合格基準
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  α参照値

	//  ゲームモードの更新処理
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		//  加算合成（アルファブレンド）
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//  SRC(これから描画する側)＋DEST(既に描画されてる側)
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//  SRCを半透明合成する
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//  DESTをそのまま描画する
	}
	////  Ｚバッファ禁止
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int i = 0; i < nWater_Anim_Max; i++)
	{
		if (m_Water[i].Flag)
		{
			//  ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Water[i].Matrix.World);

			//  スケールを反映
			D3DXMatrixScaling( &m_Water[i].Matrix.Scl, m_Water[i].Scl.x, m_Water[i].Scl.y, m_Water[i].Scl.z );
			D3DXMatrixMultiply( &m_Water[i].Matrix.World, &m_Water[i].Matrix.World, &m_Water[i].Matrix.Scl );

			//  回転を反映
			D3DXMatrixRotationYawPitchRoll( &m_Water[i].Matrix.Rot, m_Water[i].Rot.y, m_Water[i].Rot.x, m_Water[i].Rot.z );
			D3DXMatrixMultiply( &m_Water[i].Matrix.World, &m_Water[i].Matrix.World, &m_Water[i].Matrix.Rot );

			//  位置を反映
			D3DXMatrixTranslation( &m_Water[i].Matrix.Trans, m_Water[i].Pos.x, m_Water[i].Pos.y, m_Water[i].Pos.z );
			D3DXMatrixMultiply( &m_Water[i].Matrix.World, &m_Water[i].Matrix.World, &m_Water[i].Matrix.Trans );

			//  ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &m_Water[i].Matrix.World);

			//  テクスチャの設定
			pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(m_Water[i].WaterType));

			if (m_Water[i].Size.z == 0.0f)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}

			//  ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);

			if (m_Water[i].Size.z == 0.0f)	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
	}

	//  αテストを行わない
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//  タイトルモードの更新処理
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		//  通常ブレンド
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//αソースカラーの指定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//αデスティネーションカラーの指定
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CWater::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CWater::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nWater_Anim_Max,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				//  頂点バッファの使用法
		FVF_VERTEX_3D,					//  使用する頂点フォーマット
		D3DPOOL_MANAGED,				//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,					//  頂点バッファインターフェースへのポインタ
		NULL							//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nWater_Anim_Max; i++, pVtx+=nNumVertex)
	{
		//  頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_Water[i].Size.x * 0.5f, m_Water[i].Size.y * 0.5f, m_Water[i].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Water[i].Size.x * 0.5f, m_Water[i].Size.y * 0.5f, m_Water[i].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Water[i].Size.x * 0.5f, -m_Water[i].Size.y * 0.5f, -m_Water[i].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Water[i].Size.x * 0.5f, -m_Water[i].Size.y * 0.5f, -m_Water[i].Size.z * 0.5f);

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
//	関数名:	void CEffect::SetTexture
//	引数:	int nPatternAnim, int nPatternX, int nPatternY
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CWater::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, EFFECT_TYPE WaterType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend)
{
	int nCnt = 3;
	float fRot = D3DX_PI / 3.0f;

	for (int i = 0; i < nWater_Anim_Max; i++)
	{
		if (!m_Water[i].Flag)
		{
			m_Water[i].Pos = pos;
			m_Water[i].Rot = rot;
			m_Water[i].Size = size;
			m_Water[i].WaterType = WaterType;
			m_Water[i].AnimLoop = bAnimLoop;
			m_Water[i].Anim.PatternX = m_InitAnim[m_Water[i].WaterType].PatternX;
			m_Water[i].Anim.PatternY = m_InitAnim[m_Water[i].WaterType].PatternY;
			m_Water[i].Anim.Frame = m_InitAnim[m_Water[i].WaterType].Frame;
			m_Water[i].Flag = true;
			m_Water[i].AlphaTest = AlphaTest;
			m_Water[i].AlphaBlend = AlphaBlend;

			if (WaterType != EFFECT_WATER_IMPACT)
			{
				break;
			}
			else
			{
				nCnt--;
				m_Water[i].Rot.y += fRot * (float)nCnt;
				if (nCnt <= 0)
				{
					break;
				}
			}
			
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CWater::SetVertex
//	引数:	int nID
//	戻り値:	なし
//	説明:	頂点情報の設定
//------------------------------------------------------------------------------
void CWater::SetVertex(int nID)
{
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	if (m_Water[nID].WaterType == EFFECT_WATER_IMPACT)
	{
		//  頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.7f, m_Water[nID].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.7f, m_Water[nID].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.3f, -m_Water[nID].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.3f, -m_Water[nID].Size.z * 0.5f);
	}
	else
	{
		//  頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.5f, m_Water[nID].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, m_Water[nID].Size.y * 0.5f, m_Water[nID].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.5f, -m_Water[nID].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Water[nID].Size.x * 0.5f, -m_Water[nID].Size.y * 0.5f, -m_Water[nID].Size.z * 0.5f);
	}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CWater::SetTexture
//	引数:	int nPatternAnim, int nPatternX, int nPatternY
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CWater::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
{
	D3DXVECTOR2 TexAdjust;				//  テクスチャ調整係数
	int nPatternAnimX, nPatternAnimY;	//  アニメーションパターンを格納する

	TexAdjust.x = 1.0f / float(nPatternX);
	TexAdjust.y = 1.0f / float(nPatternY);

	if (nPatternX == 1)
	{//  もし横総パターンが１ならば、テクスチャX座標変わらずの設定
		nPatternAnimX = 1;
	}
	else
	{
		nPatternAnimX = nPatternAnim;
	}

	if (nPatternY == 1)
	{//  もし縦総パターンが１ならば、テクスチャY座標変わらずの設定
		nPatternAnimY = 0;
	}
	else
	{
		nPatternAnimY = nPatternAnim;
	}
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[1].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[2].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));
	pVtx[3].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}