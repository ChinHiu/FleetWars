/*------------------------------------------------------------------------------
|	タイトル：		カーソルの処理
|	ファイル名：	cursor.cpp
|	作成者：		AT12A244 33 CHIN HIU
|	作成日：		2015/11/21
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	更新履歴:
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "input.h"
#include "cursor.h"

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CCursor::CCursor
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CCursor::CCursor()
{
	m_VertexBuffer = NULL;			//  頂点バッファへのポイン 
	m_TextureBuffer = NULL;					//  テクスチャへのポインタ
}

//------------------------------------------------------------------------------
//	関数名:	CScene::~CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CCursor::~CCursor()
{
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CCursor::Init
//	引数:	なし
//	戻り値:	E_FAILだと初期化失敗、S_OKだと初期化成功
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CCursor::Init( void )
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  カーソルを使用設定
	m_Flag = true;
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(30.0f, 0.0f, 30.0f);
	/*m_Anim.PatternX = 8;
	m_Anim.PatternY = 4;
	m_Anim.Pattern = 0;
	m_Anim.Frame = 2;
	m_Anim.Cnt = 0;*/

	//  テクスチャの読み込み
	D3DXCreateTextureFromFile(
								pDevice,
								CURSOR3D_TEXTURE_FILE,	//  テクスチャファイル位置
								&m_TextureBuffer				//  テクスチャバッファへのポインタ
	);

	//  頂点情報の作成
	MakeVertex( pDevice );
}

//------------------------------------------------------------------------------
//	関数名:	void CCursor::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CCursor::Uninit(void)
{
	//  テクスチャバッファの開放
	SAFE_RELEASE(m_VertexBuffer);

	//  頂点バッファの開放
	SAFE_RELEASE(m_TextureBuffer);
}

void CCursor::Update(void)
{
	//if (m_Flag == true)
	//{
	//	if (m_Anim.PatternX != 1 && m_Anim.PatternY != 1)
	//	{//  横パターンと縦パターンが１ではなければ、テクスチャアニメーション処理を行う
	//		m_Anim.Cnt++;									//  アニメーションカウント

	//		if (m_Anim.Cnt == m_Anim.Frame)
	//		{//  何フレームごとに更新
	//			m_Anim.Cnt = 0;									//  アニメーションカウントの初期化
	//			m_Anim.Pattern++;								//  アニメーション現在パターンを更新

	//			//  テクスチャ座標の設定
	//			SetTexture(m_Anim.Pattern, m_Anim.PatternX, m_Anim.PatternY);

	//			if (m_Anim.Pattern == m_Anim.PatternX * m_Anim.PatternY)
	//			{//  全パターンを回したならば
	//				m_Anim.Pattern = 0;							//  アニメーションパターン数の初期化
	//			}
	//		}
	//	}
	//}
}

//------------------------------------------------------------------------------
//	関数名:	void CCursor::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CCursor::Draw(void)
{
	//if (m_Flag == true)
	//{

	//	//  デバイスを取得
	//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//	//  頂点バッファをデータストリームにバインドする
	//	pDevice->SetStreamSource(0, m_VtxBuffer, 0, sizeof(VERTEX_3D));

	//	//  頂点フォーマットの設定
	//	pDevice->SetFVF(FVF_VERTEX_3D);

	//	//ワールドマトリックスの初期化
	//	D3DXMatrixIdentity(&m_Matrix.World);

	//	//スケールを反映
	//	D3DXMatrixScaling
	//	(
	//		&m_Matrix.Scl,
	//		m_Scl.x,
	//		m_Scl.y,
	//		m_Scl.z
	//	);
	//	D3DXMatrixMultiply
	//	(
	//		&m_Matrix.World,
	//		&m_Matrix.World,
	//		&m_Matrix.Scl
	//	);

	//	//回転を反映
	//	D3DXMatrixRotationYawPitchRoll
	//	(
	//		&m_Matrix.Rot,
	//		m_Rot.y,
	//		m_Rot.x,
	//		m_Rot.z
	//	);
	//	D3DXMatrixMultiply
	//	(
	//		&m_Matrix.World,
	//		&m_Matrix.World,
	//		&m_Matrix.Rot
	//	);

	//	//位置を反映
	//	D3DXMatrixTranslation
	//	(
	//		&m_Matrix.Trans,
	//		m_Pos.x,
	//		m_Pos.y,
	//		m_Pos.z
	//	);
	//	D3DXMatrixMultiply
	//	(
	//		&m_Matrix.World,
	//		&m_Matrix.World,
	//		&m_Matrix.Trans
	//	);

	//	//ワールドマトリックスを設定
	//	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//	//頂点バッファをデータストリームにバインドする
	//	pDevice->SetStreamSource(0, m_VtxBuffer, 0, sizeof(VERTEX_3D));

	//	//頂点フォーマットの設定
	//	pDevice->SetFVF(FVF_VERTEX_3D);

	//	//テクスチャの設定
	//	pDevice->SetTexture(0, m_TexBuffer);

	//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	////  加算合成（アルファブレンド）
	//	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);				//  SRC(これから描画する側)＋DEST(既に描画されてる側)
	//	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//  SRCを半透明合成する
	//	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				//  DESTをそのまま描画する

	//	//  αテストを行う
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  αテストの有効化
	//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  αテスト合格基準
	//	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  α参照値

	//	//  Ｚバッファ禁止
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	//	//  ポリゴンの描画
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4, 2);

	//	
	//	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//	pDevice->SetRenderState(D3DRS_ZENABLE, true);

	//	//  通常ブレンド
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//αソースカラーの指定
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//αデスティネーションカラーの指定

	//	//  αテストを行わない
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  αテスト無効化

	//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//}
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CCursor::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報の作成
//------------------------------------------------------------------------------
HRESULT CCursor::MakeVertex( LPDIRECT3DDEVICE9 pDevice )
{
	//頂点バッファを確保
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					//  頂点バッファの使用法
		FVF_VERTEX_3D,						//  使用する頂点フォーマット
		D3DPOOL_MANAGED,					//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,						//  頂点バッファインターフェースへのポインタ
		NULL								//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);

	//  法線の設定
	pVtx[0].nor =
	pVtx[1].nor =
	pVtx[2].nor =
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//  頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CCursor::SetVertex
//	引数:	なし
//	戻り値:	なし
//	説明:	頂点座標設定
//------------------------------------------------------------------------------/
void CCursor::SetVertex(void)
{
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x * 0.5f, m_Size.y * 0.5f, m_Size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x * 0.5f, -m_Size.y * 0.5f, -m_Size.z * 0.5f);

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CCursor::Set
//	引数:	なし
//	戻り値:	なし
//	説明:	カーソルの設定
//------------------------------------------------------------------------------/
void CCursor::SetPosition(D3DXVECTOR3 pos)
{
	if( m_Flag == true )
	{
		//  位置を設定
		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Pos.z = pos.z;
	}
}

D3DXVECTOR3 *CCursor::GetPosition(void)
{
	return &m_Pos;
}


//------------------------------------------------------------------------------
//	関数名:	void CScene3D::SetTexture
//	引数:	int nPatternAnim, int nPatternX, int nPatternY 
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CCursor::SetTexture(int nPatternAnim, int nPatternX, int nPatternY)
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

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[1].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y));
	pVtx[2].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));
	pVtx[3].tex = D3DXVECTOR2(float(nPatternAnimX % nPatternX * TexAdjust.x + TexAdjust.x), float(nPatternAnimY / nPatternX * TexAdjust.y + TexAdjust.y));

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}