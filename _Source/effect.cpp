//------------------------------------------------------------------------------
//	タイトル：		バレット関連の関数
//	ファイル名：	bullet.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/09/15
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "effect.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"

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
//	関数名:	CEffect::CEffect
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CEffect::CEffect(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  頂点バッファへのポイント

}

//------------------------------------------------------------------------------
//	関数名:	CEffect::~CEffect
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CEffect::~CEffect()
{
}

//------------------------------------------------------------------------------
//	関数名:	CEffect *CEffect::Create
//	引数:	なし
//	戻り値:	pEffect
//	説明:	エフェクトの生成
//------------------------------------------------------------------------------
CEffect *CEffect::Create(void)
{
	CEffect *pEffect;

	//  インスタンス生成
	pEffect = new CEffect;

	for (int i = EFFECT_SHOT_FIRE, j = 0; i <= EFFECT_EXPLOSION_001; i++, j++)
	{
		switch (i)
		{
		case EFFECT_EXPLOSION_000:
			pEffect->m_Anim[j].PatternX = 8;
			pEffect->m_Anim[j].PatternY = 6;
			pEffect->m_Anim[j].Frame = 1;
			break;
		case EFFECT_EXPLOSION_001:
			pEffect->m_Anim[j].PatternX = 8;
			pEffect->m_Anim[j].PatternY = 4;
			pEffect->m_Anim[j].Frame = 2;
			break;
		case EFFECT_SHOT_FIRE:
			pEffect->m_Anim[j].PatternX = 2;
			pEffect->m_Anim[j].PatternY = 2;
			pEffect->m_Anim[j].Frame = 1;
			break;
		default:
			break;
		}
	}

	//  初期化
	pEffect->Init();

	return pEffect;
}

//------------------------------------------------------------------------------
//	関数名:	void CEffect::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CEffect::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点情報の作成
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	関数名:	void CEffect::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CEffect::Uninit(void)
{
	//頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CEffect::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CEffect::Update(void)
{
	for (int i = 0; i < nEffect_Anim_Max; i++)
	{
		if (m_Effect[i].Flag)
		{
			if (m_Effect[i].Anim.PatternX != 1 && m_Effect[i].Anim.PatternY != 1)
			{//  横パターンと縦パターンが１ではなければ、テクスチャアニメーション処理を行う
				//  テクスチャ座標の設定
				SetTexture(m_Effect[i].Anim.Pattern, m_Effect[i].Anim.PatternX, m_Effect[i].Anim.PatternY, i);

				//  カウント
				m_Effect[i].Anim.Cnt++;

				if (m_Effect[i].Anim.Cnt == m_Effect[i].Anim.Frame)
				{//  何フレームごとに更新
					m_Effect[i].Anim.Cnt = 0;						//  アニメーションカウントの初期化
					m_Effect[i].Anim.Pattern++;						//  アニメーション現在パターンを更新

					if (m_Effect[i].Anim.Pattern == m_Effect[i].Anim.PatternX * m_Effect[i].Anim.PatternY)
					{//  全パターンを回したならば
						m_Effect[i].Anim.Pattern = 0;				//  アニメーションパターン数の初期化
						if (!m_Effect[i].AnimLoop)
						{//  ループではなければ
							m_Effect[i].Flag = false;
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
//	関数名:	void CEffect::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CEffect::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  フォグ無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//  αテストを行う
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  αテスト合格基準
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  α参照値

	//  加算合成（アルファブレンド）
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//  SRC(これから描画する側)＋DEST(既に描画されてる側)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//  SRCを半透明合成する
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//  DESTをそのまま描画する

	//  Ｚバッファ禁止
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	for (int i = 0; i < nEffect_Anim_Max; i++)
	{
		if (m_Effect[i].Flag)
		{
			//  ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_Effect[i].Matrix.World);

			//  ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &m_Effect[i].ViewMatrix);

			//  逆行列を求める
			D3DXMatrixInverse(&m_Effect[i].Matrix.World, NULL, &m_Effect[i].ViewMatrix);

			m_Effect[i].Matrix.World._41 = 0.0f;
			m_Effect[i].Matrix.World._42 = 0.0f;
			m_Effect[i].Matrix.World._43 = 0.0f;

			//  スケールを反映
			D3DXMatrixScaling( &m_Effect[i].Matrix.Scl, m_Effect[i].Scl.x, m_Effect[i].Scl.y, m_Effect[i].Scl.z );
			D3DXMatrixMultiply( &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.Scl );

			//  回転を反映
			D3DXMatrixRotationYawPitchRoll( &m_Effect[i].Matrix.Rot, m_Effect[i].Rot.y, m_Effect[i].Rot.x, m_Effect[i].Rot.z );
			D3DXMatrixMultiply( &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.Rot );

			//  位置を反映
			D3DXMatrixTranslation( &m_Effect[i].Matrix.Trans, m_Effect[i].Pos.x, m_Effect[i].Pos.y, m_Effect[i].Pos.z );
			D3DXMatrixMultiply( &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.World, &m_Effect[i].Matrix.Trans );

			//  ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &m_Effect[i].Matrix.World);

			//  テクスチャの設定
			pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(m_Effect[i].EffectType));

			//  ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  αテストを行わない
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  αテスト無効化

	//  通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//αデスティネーションカラーの指定

	//  Ｚバッファ有効
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  フォグ無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CEffect::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CEffect::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nEffect_Anim_Max,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,									//  頂点バッファの使用法
		FVF_VERTEX_3D,										//  使用する頂点フォーマット
		D3DPOOL_MANAGED,									//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,									//  頂点バッファインターフェースへのポインタ
		NULL												//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nEffect_Anim_Max; i++, pVtx += nNumVertex)
	{
		//  頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_Effect[i].Size.x * 0.5f, m_Effect[i].Size.y * 0.5f, m_Effect[i].Size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_Effect[i].Size.x * 0.5f, m_Effect[i].Size.y * 0.5f, m_Effect[i].Size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(-m_Effect[i].Size.x * 0.5f, -m_Effect[i].Size.y * 0.5f, -m_Effect[i].Size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_Effect[i].Size.x * 0.5f, -m_Effect[i].Size.y * 0.5f, -m_Effect[i].Size.z * 0.5f);

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
void CEffect::SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, EFFECT_TYPE EffectType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend, bool ZBuffer)
{
	for (int i = 0; i < nEffect_Anim_Max; i++)
	{
		if (!m_Effect[i].Flag)
		{
			m_Effect[i].Pos = pos;
			m_Effect[i].Size = size;
			m_Effect[i].EffectType = EffectType;
			m_Effect[i].AnimLoop = bAnimLoop;
			m_Effect[i].Anim.PatternX = m_Anim[m_Effect[i].EffectType - EFFECT_SHOT_FIRE].PatternX;
			m_Effect[i].Anim.PatternY = m_Anim[m_Effect[i].EffectType - EFFECT_SHOT_FIRE].PatternY;
			m_Effect[i].Anim.Frame = m_Anim[m_Effect[i].EffectType - EFFECT_SHOT_FIRE].Frame;
			m_Effect[i].AlphaTest = AlphaTest;
			m_Effect[i].AlphaBlend = AlphaBlend;
			m_Effect[i].ZBuffer = ZBuffer;
			m_Effect[i].Flag = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CEffect::SetVertex
//	引数:	int nID
//	戻り値:	なし
//	説明:	頂点情報の設定
//------------------------------------------------------------------------------
void CEffect::SetVertex(int nID)
{
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_Effect[nID].Size.x * 0.5f, m_Effect[nID].Size.y * 0.5f, m_Effect[nID].Size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Effect[nID].Size.x * 0.5f, m_Effect[nID].Size.y * 0.5f, m_Effect[nID].Size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_Effect[nID].Size.x * 0.5f, -m_Effect[nID].Size.y * 0.5f, -m_Effect[nID].Size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Effect[nID].Size.x * 0.5f, -m_Effect[nID].Size.y * 0.5f, -m_Effect[nID].Size.z * 0.5f);

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CEffect::SetTexture
//	引数:	int nPatternAnim, int nPatternX, int nPatternY
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CEffect::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
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