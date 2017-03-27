//------------------------------------------------------------------------------
//	タイトル：		ユーザーインターフェースの関数
//	ファイル名：	UI.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/07
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "UI.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "title.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define WEAPON_UI_SPACE (5.0f)
#define GLITTER_CNT		(500)

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CUI::CUI
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CUI::CUI(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;						//  頂点バッファへのポイン
}

//------------------------------------------------------------------------------
//	関数名:	CUI::~CUI
//	引数:	なし
//	戻り値:	なし
//	説明:	デストラクタ
//------------------------------------------------------------------------------
CUI::~CUI()
{
}

//------------------------------------------------------------------------------
//	関数名:	CUI *CUI::Create
//	引数:	int			nPriority		//  プライオリティ
//			OBJECT_TYPE Object_Type		//  オブジェクトタイプ
//	戻り値:	pUI
//	説明:	UIの生成
//------------------------------------------------------------------------------
CUI *CUI::Create()
{
	CUI *pUI;

	//  インスタンス生成
	pUI = new CUI();

	//  初期化
	pUI->Init();

	return pUI;
}

//------------------------------------------------------------------------------
//	関数名:	void CUI::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CUI::Init(void)
{
	//  頂点情報の作成
	MakeVertex(CManager::GetRenderer()->GetDevice());
}

//------------------------------------------------------------------------------
//	関数名:	void CUI::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CUI::Uninit(void)
{
	//頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CUI::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CUI::Update(void)
{
	//  頂点情報の設定
	SetVertex();
}

//------------------------------------------------------------------------------
//	関数名:	void CUI::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CUI::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  ライト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//  フォグ無効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	for (int i = 0; i < nUIMax; i++)
	{
		if (m_UI[i].Flag)
		{
			//  テクスチャの設定
			pDevice->SetTexture(0, CManager::GetUITextureBuffer(m_UI[i].Lable));

			//  ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
		}
	}

	//  ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//  フォグ有効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CUI::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CUI::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
		(
		sizeof(VERTEX_2D) * nNumVertex * nUIMax,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,							//  頂点バッファの使用法
		FVF_VERTEX_2D,								//  使用する頂点フォーマット
		D3DPOOL_MANAGED,							//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,							//  頂点バッファインターフェースへのポインタ
		NULL										//  NULLに設定
		)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nUIMax; i++, pVtx += nNumVertex)
	{
		//  頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);

		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		//  頂点カラーの設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_UI[i].Col;

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
//	関数名:	void CUI::SetVertex
//	引数:	int nID
//	戻り値:	なし
//	説明:	頂点情報の更新
//------------------------------------------------------------------------------
void CUI::SetVertex(void)
{
	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nUIMax; i++, pVtx += nNumVertex)
	{
		if (m_UI[i].Flag)
		{
			switch(m_UI[i].Type)
			{
			case UI_HEIGHT_SCROLL:
				pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f - m_UI[i].Size.y * m_UI[i].TexRate,	0.0f);
				pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f - m_UI[i].Size.y * m_UI[i].TexRate,	0.0f);
				pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f,										0.0f);
				pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f,										0.0f);
				break;
			case UI_WIDTH_SCROLL:
				pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x,									m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * m_UI[i].TexRate, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x,									m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * m_UI[i].TexRate, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				break;
			default:
				pVtx[0].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y - m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(m_UI[i].Pos.x - m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(m_UI[i].Pos.x + m_UI[i].Size.x * 0.5f, m_UI[i].Pos.y + m_UI[i].Size.y * 0.5f, 0.0f);
				break;
			}

			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			//  頂点カラーの設定
			pVtx[0].col =
			pVtx[1].col =
			pVtx[2].col =
			pVtx[3].col = m_UI[i].Col;

			//  テクスチャ座標の設定
			switch (m_UI[i].Type)
			{
			case UI_WIDTH_SCROLL:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(m_UI[i].TexRate, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(m_UI[i].TexRate, 1.0f);
				break;
			case UI_HEIGHT_SCROLL:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f - m_UI[i].TexRate);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f - m_UI[i].TexRate);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			case UI_RESULT:
				pVtx[0].tex = D3DXVECTOR2(m_UI[i].TexRate, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(m_UI[i].TexRate + 0.2f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(m_UI[i].TexRate, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(m_UI[i].TexRate + 0.2f, 1.0f);
				break;
			default:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}
		}
	}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

void CUI::SetColor(int nID, D3DXCOLOR col)
{
	m_UI[nID].Col = col;
}

void CUI::SetFlag(int nID, bool bFlag)
{
	m_UI[nID].Flag = bFlag;
}

void CUI::SetTexRate(int nID, float fTexRate)
{
	m_UI[nID].TexRate = fTexRate;
}

//------------------------------------------------------------------------------
//	関数名:	void CUI::Set
//	引数:	UI_TYPE		type		//  UIタイプ
//			D3DXVECTOR2 pos			//  位置
//			D3DXVECTOR2 size		//  サイズ
//			D3DXCOLOR	col			//  色
//			bool		bTypeID		//  タイプ順のIDで生成するかどうか
//	戻り値:	int nID
//	説明:	UIの設定
//------------------------------------------------------------------------------
int CUI::Set(UI_LABLE lable, UI_TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	//int i;

	//for (i = 0; i < nUIMax; i++)
	//{
		if (!m_UI[lable].Flag)
		{
			m_UI[lable].Pos = pos;
			m_UI[lable].Lable = lable;
			m_UI[lable].Type = type;
			m_UI[lable].Flag = true;
			m_UI[lable].Size.x = size.x;
			m_UI[lable].Size.y = size.y;
			m_UI[lable].Col = col;
			//break;
		}
	//}

	return (int)lable;
}