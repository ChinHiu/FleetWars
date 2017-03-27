//------------------------------------------------------------------------------
//	タイトル：		水しぶきの関数
//	ファイル名：	spray.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/02
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "sprayBefore.h"
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
//	関数名:	CSpray::CSpray
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CSpray::CSpray()
{
	m_VertexBuffer = NULL;					//  頂点バッファへのポイント

}

//------------------------------------------------------------------------------
//	関数名:	CSpray::~CSpray
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CSpray::~CSpray()
{
}

//------------------------------------------------------------------------------
//	関数名:	CSpray *CSpray::Create
//	引数:	なし
//	戻り値:	pEffect
//	説明:	エフェクトの生成
//------------------------------------------------------------------------------
CSpray *CSpray::Create(void)
{
	CSpray *pSpray;

	//  インスタンス生成
	pSpray = new CSpray;

	//  初期化
	pSpray->Init();

	return pSpray;
}

//------------------------------------------------------------------------------
//	関数名:	void CSpray::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CSpray::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < SPRAY_TYPE_MAX; i++)
	{
		switch (i)
		{
		case SPRAY_BEFORE_RIGHT:
			m_Anim[i].PatternX = 4;
			m_Anim[i].PatternY = 8;
			m_Anim[i].Frame = 2;
			break;
		case SPRAY_BEFORE_LEFT:
			m_Anim[i].PatternX = 4;
			m_Anim[i].PatternY = 8;
			m_Anim[i].Frame = 2;
			break;
		default:
			break;
		}
	}

	//  頂点情報の作成
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	関数名:	void CSpray::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CSpray::Uninit(void)
{
	//頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CSpray::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CSpray::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	for (int i = 0; i < SPRAY_TYPE_MAX; i++)
	{
		if (m_Spray[i].Flag)
		{
			if (m_Spray[i].Anim.PatternX != 1 && m_Spray[i].Anim.PatternY != 1)
			{//  横パターンと縦パターンが１ではなければ、テクスチャアニメーション処理を行う
			 //  テクスチャ座標の設定
				SetTexture(m_Spray[i].Anim.Pattern, m_Spray[i].Anim.PatternX, m_Spray[i].Anim.PatternY, i);

				//  カウント
				m_Spray[i].Anim.Cnt++;

				if (m_Spray[i].Anim.Cnt == m_Spray[i].Anim.Frame)
				{//  何フレームごとに更新
					m_Spray[i].Anim.Cnt = 0;						//  アニメーションカウントの初期化
					m_Spray[i].Anim.Pattern++;						//  アニメーション現在パターンを更新

					if (m_Spray[i].Anim.Pattern == m_Spray[i].Anim.PatternX * m_Spray[i].Anim.PatternY)
					{//  全パターンを回したならば
						m_Spray[i].Anim.Pattern = 0;				//  アニメーションパターン数の初期化
						if (!m_Spray[i].AnimLoop)
						{//  ループではなければ
							m_Spray[i].Flag = false;
						}
					}
				}
			}

			//  頂点情報の更新
			SetVertex(i);
		}
	}

}

//------------------------------------------------------------------------------
//	関数名:	void CSpray::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CSpray::Draw(int nID)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//  ライト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  フォグ無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//  カリングを行わない
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	if (m_Spray[nID].Flag)
	{
		//  ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_Spray[nID].Matrix.World);

		//  スケールを反映
		D3DXMatrixScaling
		(
			&m_Spray[nID].Matrix.Scl,
			m_Spray[nID].Scl.x,
			m_Spray[nID].Scl.y,
			m_Spray[nID].Scl.z
		);
		D3DXMatrixMultiply
		(
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.Scl
		);

		//  回転を反映
		D3DXMatrixRotationYawPitchRoll
		(
			&m_Spray[nID].Matrix.Rot,
			m_Spray[nID].Rot->y + m_Spray[nID].AdjustRot.y,
			m_Spray[nID].Rot->x + m_Spray[nID].AdjustRot.x,
			m_Spray[nID].Rot->z
		);
		D3DXMatrixMultiply
		(
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.Rot
		);

		//  位置を反映
		D3DXMatrixTranslation
		(
			&m_Spray[nID].Matrix.Trans,
			m_Spray[nID].Pos->x,
			m_Spray[nID].Pos->y,
			m_Spray[nID].Pos->z
		);
		D3DXMatrixMultiply
		(
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.World,
			&m_Spray[nID].Matrix.Trans
		);

		//  ワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &m_Spray[nID].Matrix.World);

		//  テクスチャの設定
		pDevice->SetTexture(0, CManager::GetEffectTextureBuffer(EFFECT_SPRAY_BEFORE));

		//  ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nID * nNumVertex, nNumPolygon);
	}

	//  αテストを行わない
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//  ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  フォグ有効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//  カリングを行う
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CSpray::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CSpray::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * SPRAY_TYPE_MAX,	//  頂点データ用に確保するバッファサイズ(バイト単位)
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

	for (int i = 0; i < SPRAY_TYPE_MAX; i++, pVtx += nNumVertex)
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
//	関数名:	void CSpray::Set
//	引数:	D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, SPRAY_TYPE Spray_Type, bool bAnimLoop
//	戻り値:	なし
//	説明:	水しぶきの使用設定
//------------------------------------------------------------------------------
void CSpray::Set(MODEL_TYPE Model_Type, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, SPRAY_TYPE Spray_Type, bool bAnimLoop)
{
	for (int i = 0; i < SPRAY_TYPE_MAX; i++)
	{
		if (!m_Spray[i].Flag)
		{
			m_Spray[i].Pos = pos;
			m_Spray[i].Rot = rot;
			m_Spray[i].Size = size;
			m_Spray[i].SprayType = Spray_Type;
			m_Spray[i].AnimLoop = bAnimLoop;
			m_Spray[i].Anim.PatternX = m_Anim[m_Spray[i].SprayType].PatternX;
			m_Spray[i].Anim.PatternY = m_Anim[m_Spray[i].SprayType].PatternY;
			m_Spray[i].Anim.Frame = m_Anim[m_Spray[i].SprayType].Frame;
			m_Type = Model_Type;

			switch (Model_Type)
			{
			case MODEL_GORSHKOV:
				switch (Spray_Type)
				{
				case SPRAY_BEFORE_LEFT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(-D3DX_PI * 0.13f, -D3DX_PI * 0.42f);
					break;
				case SPRAY_BEFORE_RIGHT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(D3DX_PI * 0.13f, -D3DX_PI * 0.58f);
					break;
				default:
					break;
				}
				break;
			case MODEL_HAMINA:
				switch (Spray_Type)
				{
				case SPRAY_BEFORE_LEFT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(-D3DX_PI * 0.3f, -D3DX_PI * 0.5f);
					break;
				case SPRAY_BEFORE_RIGHT:
					m_Spray[i].AdjustRot = D3DXVECTOR2(D3DX_PI * 0.3f, -D3DX_PI * 0.5f);
					break;
				default:
					break;
				}
				break;
			}

			m_Spray[i].Flag = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CSpray::SetVertex
//	引数:	int nID
//	戻り値:	なし
//	説明:	頂点情報の設定
//------------------------------------------------------------------------------
void CSpray::SetVertex(int nID)
{
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nNumVertex * nID;

	//if (m_Spray[nID].SprayType == SPRAY_BEHIDE)
	//{
		/*pVtx[0].pos = D3DXVECTOR3(-m_Spray[nID].Size->x * 0.5f, 0.0f, m_Spray[nID].Size->z);
		pVtx[1].pos = D3DXVECTOR3(m_Spray[nID].Size->x * 0.5f, 0.0f, m_Spray[nID].Size->z);
		pVtx[2].pos = D3DXVECTOR3(-m_Spray[nID].Size->x * 0.5f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_Spray[nID].Size->x * 0.5f, 0.0f, 0.0f);*/
	//}
	//else
	//{
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_Spray[nID].Size->y * 0.8f, m_Spray[nID].Size->z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Spray[nID].Size->x, m_Spray[nID].Size->y * 0.8f, m_Spray[nID].Size->z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, -m_Spray[nID].Size->y * 0.2f, -m_Spray[nID].Size->z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Spray[nID].Size->x, -m_Spray[nID].Size->y * 0.2f, -m_Spray[nID].Size->z * 0.5f);

	//}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CSpray::SetTexture
//	引数:	int nPatternAnim, int nPatternX, int nPatternY
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CSpray::SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID)
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