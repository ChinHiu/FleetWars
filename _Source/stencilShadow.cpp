//------------------------------------------------------------------------------
//	タイトル：		ステンシルシャドウの関数
//	ファイル名：	stencil.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/10
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "stencilShadow.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "camera.h"
#include "meshField.h"
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
//	関数名:	CStencilShadow::CStencilShadow
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CStencilShadow::CStencilShadow()
{
	m_Pos =
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_bFlag = false;
}

//------------------------------------------------------------------------------
//	関数名:	CStencilShadow::~CStencilShadow
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CStencilShadow::~CStencilShadow()
{
}

//------------------------------------------------------------------------------
//	関数名:	CStencilShadow *CStencilShadow::Create
//	引数:	なし
//	戻り値:	sceneX
//	説明:	Xの生成
//------------------------------------------------------------------------------
CStencilShadow *CStencilShadow::Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos)
{
	CStencilShadow *pStencilShadow;

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pStencilShadow = new CStencilShadow;
	pStencilShadow->m_Pos = pos;	//  位置情報
	pStencilShadow->m_ModelType = Model_Type;

	pStencilShadow->Init();
	return pStencilShadow;
}

//------------------------------------------------------------------------------
//	関数名:	void CStencilShadow::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CStencilShadow::Init(void)
{
	CMode *pMode = CManager::GetMode();

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  タイトルモードの更新処理
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		switch (m_ModelType)
		{
		case MODEL_GORSHKOV:
			m_ModelFile = TITLE_GORSHKOV_SHADOW_FILE;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (m_ModelType)
		{
		case MODEL_GORSHKOV:
			m_ModelFile = GORSHKOV_SHADOW_FILE;
			break;
		case MODEL_HAMINA:
			m_ModelFile = HAMINA_SHADOW_FILE;
		default:
			break;
		}
	}

	//  Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		m_ModelFile,		//  読み込むファイル位置
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMat,			//  マテリアル情報
		NULL,
		&m_NumMat,			//  マテリアルの数
		&m_Mesh				//  メッシュ情報
	);

	Make2DVertex(pDevice);

	m_bFlag = true;
}

//------------------------------------------------------------------------------
//	関数名:	void CStencilShadow::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CStencilShadow::Uninit(void)
{
	//  メッシュ情報の開放
	SAFE_RELEASE(m_Mesh);

	//  マットバッファの開放
	SAFE_RELEASE(m_BuffMat);

	//  頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CStencilShadow::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CStencilShadow::Update(void)
{
}

//------------------------------------------------------------------------------
//	関数名:	void CStencilShadow::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CStencilShadow::Draw(void)
{
	if (m_bFlag)
	{
		D3DXMATERIAL	*pMat;
		D3DMATERIAL9	matDef;

		//  デバイスを取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//  ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_Matrix.World);

		//  スケールを反映
		D3DXMatrixScaling( &m_Matrix.Scl, m_Scl.x, m_Scl.y, m_Scl.z );
		D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl );

		//  回転を反映
		D3DXMatrixRotationYawPitchRoll( &m_Matrix.Rot, m_Rot.y, m_Rot.x, m_Rot.z );
		D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot );

		//  位置を反映
		D3DXMatrixTranslation( &m_Matrix.Trans, m_Pos.x, m_Pos.y, m_Pos.z );
		D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans );

		//  ワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

		//  現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);
		pMat = (D3DXMATERIAL *)m_BuffMat->GetBufferPointer();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_STENCILREF, 1);

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{
			pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//  メッシュの描画
			m_Mesh->DrawSubset(nCntMat);

			pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

			//  メッシュの描画
			m_Mesh->DrawSubset(nCntMat);
		}

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		//  頂点バッファをデータストリームにバインドする
		pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

		//  頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//  テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//  ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * nNumVertex, nNumPolygon);

		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

		//  マテリアルを元に戻す
		pDevice->SetMaterial(&matDef);
	}
}

HRESULT CStencilShadow::Make2DVertex(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * nNumVertex,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				//  頂点バッファの使用法
		FVF_VERTEX_2D,					//  使用する頂点フォーマット
		D3DPOOL_MANAGED,				//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,				//  頂点バッファインターフェースへのポインタ
		NULL							//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pScreenSize->x, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, pScreenSize->y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pScreenSize->x, pScreenSize->y, 0.0f);

	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	//  頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f);

	//  テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();

	return S_OK;
}