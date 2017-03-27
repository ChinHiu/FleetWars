//------------------------------------------------------------------------------
//	タイトル：		Obbテストの関数
//	ファイル名：	ObbTest.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/01
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "ObbTest.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
//#include "game.h"
#include "player.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const int nCubeFaceNum = 6;

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CObbTest::CObbTest
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CObbTest::CObbTest(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_VertexBuffer = NULL;					//  頂点バッファへのポイント
#ifdef _DEBUG
	m_bObbTest = true;
#else
	m_bObbTest = false;
#endif
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
}

//------------------------------------------------------------------------------
//	関数名:	CObbTest::~CObbTest
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CObbTest::~CObbTest()
{
}

//------------------------------------------------------------------------------
//	関数名:	CObbTest *CObbTest::Create
//	引数:	なし
//	戻り値:	pEffect
//	説明:	エフェクトの生成
//------------------------------------------------------------------------------
CObbTest *CObbTest::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CObbTest *pObbTest;

	//  インスタンス生成
	pObbTest = new CObbTest;

	//  値を代入
	pObbTest->m_ObbTest.Pos = pos;
	pObbTest->m_ObbTest.Rot = rot;
	pObbTest->m_ObbTest.Size = size;
	pObbTest->m_ObbTest.Flag = true;

	//  初期化
	pObbTest->Init();

	return pObbTest;
}

//------------------------------------------------------------------------------
//	関数名:	void CObbTest::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CObbTest::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点情報の作成
	MakeVertex(pDevice);
}


//------------------------------------------------------------------------------
//	関数名:	void CObbTest::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CObbTest::Uninit(void)
{
	//頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);
}

//------------------------------------------------------------------------------
//	関数名:	void CObbTest::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CObbTest::Update(void)
{
#ifdef _DEBUG

	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F4))	m_bObbTest = m_bObbTest ? false : true;

	SetVertex();
#endif
}

//------------------------------------------------------------------------------
//	関数名:	void CObbTest::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CObbTest::Draw(void)
{
	if (m_bObbTest)
	{
		//  デバイスを取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//  頂点バッファをデータストリームにバインドする
		pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));

		//  頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//  テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//  ライト無効化
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//  フォグ無効化
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

		if (m_bObbTest)
		{
			//  ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_ObbTest.Matrix.World);

			//  スケールを反映
			D3DXMatrixScaling(&m_ObbTest.Matrix.Scl, m_ObbTest.Scl.x, m_ObbTest.Scl.y, m_ObbTest.Scl.z);
			D3DXMatrixMultiply(&m_ObbTest.Matrix.World, &m_ObbTest.Matrix.World, &m_ObbTest.Matrix.Scl);

			//  回転を反映
			D3DXMatrixRotationYawPitchRoll(&m_ObbTest.Matrix.Rot, m_ObbTest.Rot.y, m_ObbTest.Rot.x, m_ObbTest.Rot.z);
			D3DXMatrixMultiply(&m_ObbTest.Matrix.World, &m_ObbTest.Matrix.World, &m_ObbTest.Matrix.Rot);

			//  位置を反映
			D3DXMatrixTranslation(&m_ObbTest.Matrix.Trans, m_ObbTest.Pos.x, m_ObbTest.Pos.y, m_ObbTest.Pos.z);
			D3DXMatrixMultiply(&m_ObbTest.Matrix.World, &m_ObbTest.Matrix.World, &m_ObbTest.Matrix.Trans);

			//  ワールドマトリックスを設定
			pDevice->SetTransform(D3DTS_WORLD, &m_ObbTest.Matrix.World);

			for (int i = 0; i < nCubeFaceNum; i++)
			{
				//  ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
			}

		}

		//  ライト有効化
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		//  フォグ有効化
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CObbTest::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CObbTest::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * nNumVertex * nCubeFaceNum,		//  頂点データ用に確保するバッファサイズ(バイト単位)
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

	//  頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);

	pVtx[4].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[5].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[6].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[7].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);

	pVtx[8].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[9].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[10].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[11].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);

	pVtx[12].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[13].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[14].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[15].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);

	pVtx[16].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[17].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[18].pos = D3DXVECTOR3(-m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[19].pos = D3DXVECTOR3(m_ObbTest.Size.x, m_ObbTest.Size.y, -m_ObbTest.Size.z);

	pVtx[20].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[21].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, -m_ObbTest.Size.z);
	pVtx[22].pos = D3DXVECTOR3(-m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);
	pVtx[23].pos = D3DXVECTOR3(m_ObbTest.Size.x, -m_ObbTest.Size.y, m_ObbTest.Size.z);

	for (int i = 0; i < nNumVertex * nCubeFaceNum; i += nNumVertex, pVtx += nNumVertex)
	{
		//法線の設定
		pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

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

void CObbTest::SetVertex(void)
{
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < nNumVertex * nCubeFaceNum; i += nNumVertex, pVtx += nNumVertex)
	{
		//頂点カラーの設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_Col;
	}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

void CObbTest::SetCol(D3DXCOLOR col)
{
	m_Col = col;
};

void CObbTest::SetPos(D3DXVECTOR3 pos)
{
	m_ObbTest.Pos = pos;
};

void CObbTest::SetRot(D3DXVECTOR3 rot)
{
	m_ObbTest.Rot = rot;
};