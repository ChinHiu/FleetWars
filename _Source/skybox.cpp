//------------------------------------------------------------------------------
//	タイトル：		3D描画関連の関数
//	ファイル名：	scene3D.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/25
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "skybox.h"
#include "input.h"
#include "keyboard.h"
#include <typeinfo.h>
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
//	関数名:	CSkybox::CSkybox
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CSkybox::CSkybox(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer	= NULL;										//  頂点バッファへのポインタ
	m_IndexBuffer	= NULL;										//  インデックスバッファへのポインター

	//  位置、回転、倍率、
	m_Pos =
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Scale = 0.0f;
}

//------------------------------------------------------------------------------
//	関数名:	CSkybox::~CSkybox
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CSkybox::~CSkybox()
{

}

//------------------------------------------------------------------------------
//	関数名:	CSkybox *CSkybox::Create
//	引数:	なし
//	戻り値:	scene3D
//	説明:	3Dの生成
//------------------------------------------------------------------------------
CSkybox *CSkybox::Create(float fScale)
{
	CSkybox *pSky;
	pSky = new CSkybox();

	pSky->m_Scale	= fScale;		//  倍率

	pSky->Init();
	return pSky;
}

//------------------------------------------------------------------------------
//	関数名:	void CSkybox::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CSkybox::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点情報の作成
	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	関数名:	void CScene3D::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CSkybox::Uninit(void)
{
	//  頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);

	//  インデックスバッファを開放
	SAFE_RELEASE(m_IndexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CScene3D::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CSkybox::Update(void)
{
	m_Rot.y += 0.0001f;

	SAFE_ROTCHECK(m_Rot.y);

	m_Pos = *CManager::GetPlayer()->GetPosition();
}

//------------------------------------------------------------------------------
//	関数名:	void CSkybox::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CSkybox::Draw(void)
{
	//  デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Matrix.World);

	//  スケールを反映
	D3DXMatrixScaling(
		&m_Matrix.Scl,
		m_Scl.x,
		m_Scl.y,
		m_Scl.z
		);
	D3DXMatrixMultiply(
		&m_Matrix.World,
		&m_Matrix.World,
		&m_Matrix.Scl
		);

	//  回転を反映
	D3DXMatrixRotationYawPitchRoll(
		&m_Matrix.Rot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z
		);
	D3DXMatrixMultiply(
		&m_Matrix.World,
		&m_Matrix.World,
		&m_Matrix.Rot
		);

	//  位置を反映
	D3DXMatrixTranslation(
		&m_Matrix.Trans,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z
		);
	D3DXMatrixMultiply(
		&m_Matrix.World,
		&m_Matrix.World,
		&m_Matrix.Trans
		);

	//  ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

	//  インデックスバッファをデータストリームにバインドする
	pDevice->SetIndices(m_IndexBuffer);

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//  ライトを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < SKY_TEXTURE_MAX; i++)
	{
		pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

		//  テクスチャの設定
		pDevice->SetTexture(0, CManager::GetSkyboxTextureBuffer(i));

		//  描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
	}

	//  元の設定に戻る
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CScene3D::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice, PLAYER *pPlayer
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CSkybox::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファを確保
	if (FAILED(pDevice->CreateVertexBuffer
		(
		sizeof(VERTEX_3D) * SKY_TEXTURE_MAX * nNumVertex,	//  頂点データ用に確保するバッファサイズ(バイト単位)
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

	for (int i = 0; i < SKY_TEXTURE_MAX * nNumVertex; i += nNumVertex, pVtx += nNumVertex)
	{
		switch (i)
		{
		case 0:
			//  UP
			pVtx[0].pos = D3DXVECTOR3(-m_Scale, m_Scale, -m_Scale);
			pVtx[1].pos = D3DXVECTOR3(m_Scale, m_Scale, -m_Scale);
			pVtx[2].pos = D3DXVECTOR3(-m_Scale, m_Scale, m_Scale);
			pVtx[3].pos = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
			break;
		case 4:
			//  LEFT
			pVtx[0].pos = D3DXVECTOR3(-m_Scale, m_Scale, -m_Scale);
			pVtx[1].pos = D3DXVECTOR3(-m_Scale, m_Scale, m_Scale);
			pVtx[2].pos = D3DXVECTOR3(-m_Scale, -m_Scale, -m_Scale);
			pVtx[3].pos = D3DXVECTOR3(-m_Scale, -m_Scale, m_Scale);
			break;
		case 8:
			//  FRONT
			pVtx[0].pos = D3DXVECTOR3(-m_Scale, m_Scale, m_Scale);
			pVtx[1].pos = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
			pVtx[2].pos = D3DXVECTOR3(-m_Scale, -m_Scale, m_Scale);
			pVtx[3].pos = D3DXVECTOR3(m_Scale, -m_Scale, m_Scale);
			break;
		case 12:
			//  RIGHT
			pVtx[0].pos = D3DXVECTOR3(m_Scale, m_Scale, m_Scale);
			pVtx[1].pos = D3DXVECTOR3(m_Scale, m_Scale, -m_Scale);
			pVtx[2].pos = D3DXVECTOR3(m_Scale, -m_Scale, m_Scale);
			pVtx[3].pos = D3DXVECTOR3(m_Scale, -m_Scale, -m_Scale);
			break;
		case 16:
			//  BACK
			pVtx[0].pos = D3DXVECTOR3(m_Scale, m_Scale, -m_Scale);
			pVtx[1].pos = D3DXVECTOR3(-m_Scale, m_Scale, -m_Scale);
			pVtx[2].pos = D3DXVECTOR3(m_Scale, -m_Scale, -m_Scale);
			pVtx[3].pos = D3DXVECTOR3(-m_Scale, -m_Scale, -m_Scale);
			break;
		case 20:
			// DOWN
			pVtx[0].pos = D3DXVECTOR3(-m_Scale, -m_Scale, m_Scale);
			pVtx[1].pos = D3DXVECTOR3(m_Scale, -m_Scale, m_Scale);
			pVtx[2].pos = D3DXVECTOR3(-m_Scale, -m_Scale, -m_Scale);
			pVtx[3].pos = D3DXVECTOR3(m_Scale, -m_Scale, -m_Scale);
			break;
		default:
			break;
		}

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
	}
	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();

	return S_OK;
}