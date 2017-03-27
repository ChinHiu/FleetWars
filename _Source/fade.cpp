//------------------------------------------------------------------------------
//	タイトル：		フェードの関数
//	ファイル名：	fade.cpp
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
#include "fade.h"
#include "title.h"
#include "openAL.h"

//------------------------------------------------------------------------------
//	関数名:	CFade::CFade()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CFade::CFade()
{
}

//------------------------------------------------------------------------------
//	関数名:	CFade::~CFade()
//	引数:	なし
//	戻り値:	なし
//	説明:	デストラクタ
//------------------------------------------------------------------------------
CFade::~CFade()
{
}

//------------------------------------------------------------------------------
//	関数名:	CFade *CFade::Create
//	引数:	CMode *NextMode
//	戻り値:	なし
//	説明:	フェードの生成
//------------------------------------------------------------------------------
CFade *CFade::Create(CMode *NextMode)
{
	CFade *pFade;

	//  インスタンス生成
	pFade = new CFade;

	//  初期化
	pFade->Init();

	pFade->m_NextMode = NextMode;

	return pFade;
}

//------------------------------------------------------------------------------
//	関数名:	void CFade::Init
//	引数:	なし
//	戻り値: なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CFade::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_Pos = D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f);

	m_Size = D3DXVECTOR2(pScreenSize->x, pScreenSize->y);

	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_Fade = FADE_IN;

	//  テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		FADE_TEXTURE_FILE,								//  テクスチャファイル位置
		&m_TextureBuffer							//  テクスチャバッファへのポインタ
	);

	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	関数名:	void CFade::Uninit
//	引数:	なし
//	戻り値: なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CFade::Uninit(void)
{
	//  テクスチャバッファの開放
	SAFE_RELEASE(m_TextureBuffer);

	//  頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CFade::Update
//	引数:	なし
//	戻り値: なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_Fade)
	{
	case FADE_IN:
		m_Col.a -= 0.02f;
		if (m_Col.a <= 0.0f)
		{
			m_Fade = FADE_NONE;
		}
		break;
	case FADE_OUT:
		m_Col.a += 0.02f;
		if (m_Col.a >= 1.0f)
		{
			m_Fade = FADE_IN;

			//  画面切替
			CManager::SetMode(m_NextMode);
		}
	default:
		break;
	}

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//  頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Col;

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CFade::Draw
//	引数:	なし
//	戻り値: なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CFade::Draw(void)
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();;

	//頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  ライト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////  フォグ無効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//テクスチャの設定
	pDevice->SetTexture(0, m_TextureBuffer);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * nNumVertex, nNumPolygon);

	//  ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////  フォグ有効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	関数名:	void CFade::SetFade
//	引数:	FADE fade, bool PressButtonUse
//	戻り値: なし
//	説明:	セットフェード
//------------------------------------------------------------------------------
void CFade::Set(CMode *NextMode)
{
	//フェードの状態を設定
	m_Fade = FADE_OUT;

	//次のモードを設定
	m_NextMode = NextMode;
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CFade::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CFade::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * nNumVertex,			//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						//  頂点バッファの使用法
		FVF_VERTEX_2D,							//  使用する頂点フォーマット
		D3DPOOL_MANAGED,						//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,						//  頂点バッファインターフェースへのポインタ
		NULL									//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//  頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_Col;

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexBuffer->Unlock();
	return S_OK;
}