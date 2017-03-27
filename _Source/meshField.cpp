//------------------------------------------------------------------------------
//	タイトル：		メッシュフィールドの関数
//	ファイル名：	meshField.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/24
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "meshField.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------
const int nNum_Null_Vertex = 2;		//  縮退ポリゴンの頂点数

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CMeshField::CMeshField
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CMeshField::CMeshField(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	m_TextureBuffer = NULL;
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;
	m_PositionBuffer = NULL;

	m_VertexPos = NULL;
	m_Nor = NULL;

	m_Pos =
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//------------------------------------------------------------------------------
//	関数名:	CMeshField::~CMeshField
//	引数:	なし
//	戻り値:	CMeshField
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CMeshField::~CMeshField()
{
}

//------------------------------------------------------------------------------
//	関数名:	CMeshField *CMeshField::LoadMap
//	引数:	int nPriority, OBJECT_TYPE Object_Type		//  プライオリティ番号、オブジェクトタイプ
//			MESH_TYPE Mesh_Type							//  メッシュタイプ
//			LPCSTR MAP_FILE, LPCSTR TEXTURE_FILE		//	マップファイルパス、テクスチャファイルパス
//			bool SeamlessTex, float SeamlessScl			//  シムレーステクスチャ使用かどうか、シムレース規模
//	戻り値:	pField
//	説明:	フィールドの生成
//------------------------------------------------------------------------------
CMeshField *CMeshField::LoadMap(MESH_TYPE Mesh_Type, LPCSTR MAP_FILE, LPCSTR TEXTURE_FILE, bool SeamlessTex, float SeamlessScl)
{
	CMeshField	*pField;
	FILE		*fp;

	char		str[256];
	int			nCntPos;

	pField = new CMeshField();

	nCntPos = 0;

	//  データのエクスポート
	fp = fopen(MAP_FILE, "r");

	while (true)
	{
		fscanf(fp, "%s", str);
		if (feof(fp) != 0)	break;

		//  頂点数
		if (strcmp(str, "VtxNum") == 0)
		{
			fscanf(
				fp,
				"%d %d %d",
				&pField->m_Mesh.WidthNum,
				&pField->m_Mesh.HeightNum,
				&pField->m_Mesh.VertexNum
			);
		}

		if (strcmp(str, "Size") == 0)
		{
			fscanf(
				fp,
				"%f %f",
				&pField->m_Size.x,
				&pField->m_Size.z
			);
		}
	}

	pField->m_VertexPos = new D3DXVECTOR3[pField->m_Mesh.VertexNum];
	pField->m_Nor		= new D3DXVECTOR3[pField->m_Mesh.VertexNum];
	pField->m_NorType	= new NORMAL_TYPE[pField->m_Mesh.VertexNum];

	fseek(fp, 0, SEEK_SET);

	while (true)
	{
		fscanf(fp, "%s", str);
		if (feof(fp) != 0)	break;

		if (strcmp(str, "Pos") == 0)
		{
			fscanf(
				fp,
				"%f %f %f",
				&pField->m_VertexPos[nCntPos].x,
				&pField->m_VertexPos[nCntPos].y,
				&pField->m_VertexPos[nCntPos].z
			);
			nCntPos++;
		}
	}

	//  Mesh情報
	pField->m_Mesh.IndexNum = pField->m_Mesh.VertexNum + (pField->m_Mesh.WidthNum + 2) * (pField->m_Mesh.HeightNum - 2);
	pField->m_Mesh.SeamlessTex = SeamlessTex;
	pField->m_Mesh.SeamlessScl = SeamlessScl;
	pField->m_Mesh.Type = Mesh_Type;

	//  テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		TEXTURE_FILE,										//  テクスチャファイル位置
		&pField->m_TextureBuffer							//  テクスチャバッファへのポインタ
	);

	//  メッシュの初期化
	pField->Init();

	return pField;

	fclose(fp);
}

//------------------------------------------------------------------------------
//	関数名:	CMeshField *CMeshField::Create
//	引数:	int nPriority, OBJECT_TYPE Object_Type		//  プライオリティ番号、オブジェクトタイプ
//			MESH_TYPE Mesh_Type, LPCSTR TEXTURE_FILE	//  メッシュタイプ、テクスチャファイルパス
//			D3DXVECTOR3 pos, D3DXVECTOR3 size			//  位置、サイズ
//			int WidthNum, int HeightNum					//  横の頂点数、縦の頂点数
//			bool SeamlessTex, float SeamlessScl			//  シムレーステクスチャ使用かどうか、シムレース規模
//	戻り値:	pField
//	説明:	フィールドの生成
//------------------------------------------------------------------------------
CMeshField *CMeshField::Create(MESH_TYPE Mesh_Type, LPCSTR TEXTURE_FILE, D3DXVECTOR3 pos, D3DXVECTOR3 size, int WidthNum, int HeightNum, bool SeamlessTex, float SeamlessScl)
{
	int nVertexNum = WidthNum * HeightNum;

	CMeshField	*pField;

	pField = new CMeshField();

	pField->m_VertexPos = new D3DXVECTOR3[nVertexNum];
	pField->m_Nor		= new D3DXVECTOR3[nVertexNum];
	pField->m_NorType	= new NORMAL_TYPE[nVertexNum];

	//  Mesh情報
	pField->m_Mesh.WidthNum		= WidthNum;
	pField->m_Mesh.HeightNum	= HeightNum;
	pField->m_Mesh.VertexNum	= nVertexNum;
	pField->m_Mesh.IndexNum		= nVertexNum + (WidthNum + 2) * (HeightNum - 2);
	pField->m_Mesh.SeamlessTex	= SeamlessTex;
	pField->m_Mesh.SeamlessScl	= SeamlessScl;
	pField->m_Mesh.Type			= Mesh_Type;

	pField->m_Pos	= pos;
	pField->m_Size	= size;

	D3DXCreateTextureFromFile
	(
		CManager::GetRenderer()->GetDevice(),
		TEXTURE_FILE,								//  テクスチャファイル位置
		&pField->m_TextureBuffer					//  テクスチャバッファへのポインタ
	);

	//  頂点座標を算出
	pField->CalculateVertex();

	//  メッシュの初期化
	pField->Init();

	return pField;
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CMeshField::Init(void)
{
	//  デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  法線タイプを算出
	CalculateNormalType();

	//  法線情報を算出
	CalculateNormal();

	//  頂点情報の作成
	MakeVertex(pDevice);

	//  インデックス情報の作成
	MakeIndex(pDevice);

	//  波浪の初期化
	if (m_Mesh.Type == MESH_SEA)	WaveInit();
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CMeshField::Uninit(void)
{
	//  テクスチャバッファを開放
	SAFE_RELEASE(m_TextureBuffer);

	//  元の頂点バッファへを開放
	SAFE_RELEASE(m_PositionBuffer);

	//  頂点バッファを開放
	SAFE_RELEASE(m_VertexBuffer);

	//  インデックスバッファを開放
	SAFE_RELEASE(m_IndexBuffer);

	delete[] m_VertexPos;
	delete[] m_NorType;
	delete[] m_Nor;
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CMeshField::Update(void)
{
	//  デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  キーボードの取得
	CKeyboard	*pKeyboard = CManager::GetInput()->GetKeyboard();

	//  マウスの取得
	CMouse		*pMouse = CManager::GetInput()->GetMouse();

	if (m_Mesh.Type == MESH_SEA)	WaveUpdate();
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CMeshField::Draw(void)
{
	//  デバイスのゲッター
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

	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);				//  ワールドマトリックスを設定
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_3D));	//  頂点バッファをデータストリームにバインドする
	pDevice->SetIndices(m_IndexBuffer);									//  インデックスバッファをバインドする
	pDevice->SetFVF(FVF_VERTEX_3D);										//  頂点フォーマットの設定
	pDevice->SetTexture(0, m_TextureBuffer);							//  テクスチャの設定

	//  描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_Mesh.VertexNum,		//  総頂点数
		0,
		m_Mesh.IndexNum - 2		//  プリミティブ数
	);
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::CalculateVertex
//	引数:	なし
//	戻り値:	なし
//	説明:	頂点座標を計算
//------------------------------------------------------------------------------
void CMeshField::CalculateVertex(void)
{
	int		nHeightNumHalf;					//  縦頂点数の半分
	float	fAdjustX, fAdjustZ;				//  中心座標X、中心座標Zを調整の係数

	nHeightNumHalf = m_Mesh.HeightNum / 2;

	//  フィールド中心を原点座標にする係数の設定
	fAdjustX = m_Mesh.WidthNum % 2 == 0 ? 0.5f : 0.0f;	//  横頂点数が偶数なら0.5f、奇数は0.0f
	fAdjustZ = m_Mesh.HeightNum % 2 == 0 ? 0.5f : 0.0f; //  縦頂点数が偶数なら0.5f、奇数は0.0f

	//  フィールドの座標を計算
	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		int nCntVertex = i % m_Mesh.WidthNum;

		//  頂点座標の設定
		m_VertexPos[i].x = (nCntVertex - m_Mesh.WidthNum / 2 + fAdjustX) * m_Size.x;
		m_VertexPos[i].y = 0.0f;
		m_VertexPos[i].z = (nHeightNumHalf - fAdjustZ) * m_Size.z;

		if (nCntVertex == m_Mesh.WidthNum - 1)
		{
			nHeightNumHalf--;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::CalculateNormalType
//	引数:	なし
//	戻り値:	なし
//	説明:	法線タイプ情報の作成
//------------------------------------------------------------------------------
void CMeshField::CalculateNormalType(void)
{
	int nNumLeftTop, nNumRightTop, nNumLeftDown, nNumRightDown;

	nNumLeftTop = 0;
	nNumRightTop = m_Mesh.WidthNum - 1;
	nNumLeftDown = m_Mesh.VertexNum - m_Mesh.WidthNum;
	nNumRightDown = m_Mesh.VertexNum - 1;

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		m_NorType[i] = NONE;		//  法線タイプの初期化
	}

	m_NorType[nNumLeftTop] = LEFT_TOP;
	m_NorType[nNumRightTop] = RIGHT_TOP;
	m_NorType[nNumLeftDown] = LEFT_DOWN;
	m_NorType[nNumRightDown] = RIGHT_DOWN;

	if (m_Mesh.WidthNum > 2)
	{//  横頂点数２以上の場合
	 //  法線タイプを上辺タイプに設定
		for (int i = 1; i < nNumRightTop; i++)
		{
			m_NorType[i] = TOP_SIDE;
		}

		//  法線タイプを下辺タイプに設定
		for (int i = nNumLeftDown + 1; i < nNumRightDown; i++)
		{
			m_NorType[i] = DOWN_SIDE;
		}

		if (m_Mesh.HeightNum > 2)
		{//  横と縦頂点数２以上の場合
		 //  法線タイプ未設定のを中央タイプに設定
			for (int i = 0; i < m_Mesh.VertexNum; i++)
			{
				m_NorType[i] = m_NorType[i] == NONE ? MIDDLE : m_NorType[i];
			}
		}
	}

	if (m_Mesh.HeightNum > 2)
	{//  縦頂点数２以上の場合
	 //  法線タイプを左辺タイプに設定
		for (int i = m_Mesh.WidthNum; i < nNumLeftDown; i += m_Mesh.WidthNum)
		{
			m_NorType[i] = LEFT_SIDE;
		}

		//  法線タイプを右辺タイプに設定
		for (int i = m_Mesh.WidthNum * 2 - 1; i < nNumRightDown; i += m_Mesh.WidthNum)
		{
			m_NorType[i] = RIGHT_SIDE;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CMeshField::MakeNormal
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	法線情報の作成
//------------------------------------------------------------------------------
void CMeshField::CalculateNormal(void)
{
	D3DXVECTOR3	Vector[6], Normal[6];

	//  法線を求める
	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		switch (m_NorType[i])
		{
		case LEFT_TOP:
			Vector[0] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];

			//  ２面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1]));
			break;

		case RIGHT_TOP:
			Vector[0] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - 1] - m_VertexPos[i];

			//  １面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &Normal[0]);
			break;

		case LEFT_DOWN:
			Vector[0] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + 1] - m_VertexPos[i];

			//  １面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &Normal[0]);
			break;

		case RIGHT_DOWN:
			Vector[0] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];

			//  ２面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1]));
			break;

		case TOP_SIDE:
			Vector[0] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i - 1] - m_VertexPos[i];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;

		case DOWN_SIDE:
			Vector[0] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i + 1] - m_VertexPos[i];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case LEFT_SIDE:
			Vector[0] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case RIGHT_SIDE:
			Vector[0] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];

			//  ３面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);

			//  法線を求める
			D3DXVec3Normalize(&m_Nor[i], &(Normal[0] + Normal[1] + Normal[2]));
			break;
		case MIDDLE:
			Vector[0] = m_VertexPos[i - m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[1] = m_VertexPos[i + 1] - m_VertexPos[i];
			Vector[2] = m_VertexPos[i + m_Mesh.WidthNum + 1] - m_VertexPos[i];
			Vector[3] = m_VertexPos[i + m_Mesh.WidthNum] - m_VertexPos[i];
			Vector[4] = m_VertexPos[i - 1] - m_VertexPos[i];
			Vector[5] = m_VertexPos[i - m_Mesh.WidthNum - 1] - m_VertexPos[i];

			//  ６面の法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[1], &Vector[2]);
			D3DXVec3Cross(&Normal[2], &Vector[2], &Vector[3]);
			D3DXVec3Cross(&Normal[3], &Vector[3], &Vector[4]);
			D3DXVec3Cross(&Normal[4], &Vector[4], &Vector[5]);
			D3DXVec3Cross(&Normal[5], &Vector[5], &Vector[0]);

			//  法線を求める
			D3DXVec3Normalize(
				&m_Nor[i],
				&(Normal[0] + Normal[1] + Normal[2] + Normal[3] + Normal[4] + Normal[5])
			);
			break;
		default:
			break;
		}

		//  正規化
		D3DXVec3Normalize(&m_Nor[i], &m_Nor[i]);
	}
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CMeshField::MakeIndex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	インデックス情報の作成
//------------------------------------------------------------------------------
HRESULT CMeshField::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	int nAdjust = 2;						//  インデックスバッファ用係数
	int nDegTriNum = 0;						//  縮退三角形頂点の数
	int	nIdxEvenNum = 0;					//  インデックス頂点番号が偶数の数(縮退三角形頂点を除く)

	//  インデックスバッファを確保
	if (FAILED(pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * m_Mesh.IndexNum,		//  インデックスデータ用に確保するバッファサイズ(ワード単位)
		D3DUSAGE_WRITEONLY,					//  インデックスバッファの使用法
		D3DFMT_INDEX16,						//  使用するインデックスフォーマット
		D3DPOOL_MANAGED,					//  リソースのバッファを保持するメモリクラスを指定
		&m_IndexBuffer,						//  インデックスバッファインターフェースへのポインタ
		NULL								//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  インデックスバッファの中身を埋める
	WORD *pIdx;

	//  インデックスデータの範囲をロックし、インデックスバッファへのポインタを取得
	m_IndexBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//  頂点番号を取得(N型描画用)
	for (int i = 0; i < m_Mesh.IndexNum; i++)
	{
		//  縮退ポリゴン頂点番号を設定(毎行2個)
		if (i == m_Mesh.WidthNum * nAdjust + nDegTriNum)
		{
			if (i % 2 == 0)
			{//  1個目
				pIdx[i] = pIdx[i - 1];
				nDegTriNum++;
			}
			else
			{//  2個目
				pIdx[i] = m_Mesh.WidthNum + nIdxEvenNum;
				nAdjust += 2;				//  次の行の縮退ポリゴン頂点番号の計算用係数を設定
				nDegTriNum++;				//  縮退ポリゴン頂点数が1を加算する
			}
		}

		else if (i % 2 == 0)
		{//  頂点番号が偶数なら
			pIdx[i] = m_Mesh.WidthNum + nIdxEvenNum;
			nIdxEvenNum++;
		}

		else
		{//  頂点番号が奇数なら
			pIdx[i] = i - nIdxEvenNum - nDegTriNum;
		}
	}

	//  インデックスデータをアンロックする
	m_IndexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CMeshField::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点情報の作成
//------------------------------------------------------------------------------
HRESULT CMeshField::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	float fAdjustTexY = 0.0f;					//  テクスチャY座標ずらす係数									

	//  頂点バッファを確保
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_Mesh.VertexNum,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						//  頂点バッファの使用法　
		FVF_VERTEX_3D,							//  使用する頂点フォーマット
		D3DPOOL_MANAGED,						//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,						//  頂点バッファインターフェースへのポインタ
		NULL									//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点バッファを確保
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(D3DXVECTOR3) * m_Mesh.VertexNum,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						//  頂点バッファの使用法　
		FVF_VERTEX_3D,							//  使用する頂点フォーマット
		D3DPOOL_MANAGED,						//  リソースのバッファを保持するメモリクラスを指定
		&m_PositionBuffer,						//  頂点バッファインターフェースへのポインタ
		NULL									//  NULLに設定
	)))
	{
		return E_FAIL;
	}

	D3DXVECTOR3 *pPos;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);
	m_PositionBuffer->Lock(0, 0, (void**)&pPos, 0);

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		int nCntVertex = i % m_Mesh.HeightNum;

		//  頂点座標の設定
		pVtx[i].pos =
		pPos[i] = m_VertexPos[i];

		//  法線の設定
		pVtx[i].nor = m_Nor[i];

		//  砂色	D3DXCOLOR(0.94f, 0.9f, 0.55f, 1.0f)
		//  草色	D3DXCOLOR(0.345f, 0.75f, 0.25f, 1.0f)
		//  岩石色	D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		//  頂点カラーの設定
		if (m_Mesh.Type == MESH_ISLAND)	pVtx[i].col = D3DXCOLOR(0.345f, 0.75f, 0.25f, 1.0f);
		else							pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//  テクスチャ座標の設定
		if (m_Mesh.SeamlessTex)	pVtx[i].tex = D3DXVECTOR2(m_Mesh.SeamlessScl / m_Mesh.WidthNum * (float)nCntVertex, m_Mesh.SeamlessScl / m_Mesh.WidthNum * fAdjustTexY);
		else					pVtx[i].tex = D3DXVECTOR2((float)nCntVertex, fAdjustTexY);

		//  今は毎行最後の頂点の場合
		if (nCntVertex == m_Mesh.WidthNum - 1)	fAdjustTexY++;
	}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
	m_PositionBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::SetVertex(void)
//	引数:	なし
//	戻り値:	なし
//	説明:	頂点情報の更新
//------------------------------------------------------------------------------
void CMeshField::SetVertex(void)
{
	//  頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		//  頂点座標の設定
		pVtx[i].pos = m_VertexPos[i];
		pVtx[i].nor = m_Nor[i];
	}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::WaveInit
//	引数:	なし
//	戻り値:	なし
//	説明:	波の初期化処理
//------------------------------------------------------------------------------
void CMeshField::WaveInit(void)
{
	CMode *pMode = CManager::GetMode();

#ifdef _DEBUG
	m_WaveID = 0;
#endif

	//  タイトルモードの波設定
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		int i = 0;
		m_Wave[i].K = D3DXVECTOR2(1.0f, 1.0f);
		m_Wave[i].A = 3.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.1f;
		m_Wave[i].WaveLength = 1300.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(1.0f, 0.5f);
		m_Wave[i].A = -4.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 1200.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(0.5f, 1.0f);
		m_Wave[i].A = -1.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.3f;
		m_Wave[i].WaveLength = 800.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(0.2f, 1.0f);
		m_Wave[i].A = -0.6f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 600.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;
	}

	//  ゲームモードの波設定
	else
	{
		int i = 0;
		m_Wave[i].K = D3DXVECTOR2(1.0f, 1.0f);
		m_Wave[i].A = -3.5f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.1f;
		m_Wave[i].WaveLength = 1200.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(-1.0f, 0.5f);
		m_Wave[i].A = 8.5f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.1f;
		m_Wave[i].WaveLength = 1500.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(0.2f, 0.8f);
		m_Wave[i].A = -5.0f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 2000.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;

		i++;
		m_Wave[i].K = D3DXVECTOR2(-0.2f, 1.0f);
		m_Wave[i].A = -0.6f;
		m_Wave[i].Omega = 0.1f;
		m_Wave[i].t = 0.0f;
		m_Wave[i].OmegaT = 0.2f;
		m_Wave[i].WaveLength = 500.0f;
		m_Wave[i].k = 2.0f * D3DX_PI / m_Wave[i].WaveLength;
		D3DXVec2Normalize(&m_Wave[i].K, &m_Wave[i].K);
		m_Wave[i].K *= m_Wave[i].k;
		m_Wave[i].testAk = m_Wave[i].A * m_Wave[i].k;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::SeaUpdate
//	引数:	MESH_TYPE MeshType
//	戻り値:	なし
//	説明:	波の更新
//------------------------------------------------------------------------------
void CMeshField::WaveUpdate(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	D3DXVECTOR2 posXZ = D3DXVECTOR2(0, 0);
	float posY = 0;
	D3DXVECTOR2 posXZDif = D3DXVECTOR2(0, 0);
	float posYDif = 0;
	float temp = 0;

	LPDIRECT3DDEVICE9 device = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 *pVec;
	m_PositionBuffer->Lock(0, 0, (void **)&pVec, 0);

#ifdef _DEBUG
//	if (pKeyboard->GetTrigger(DIK_TAB))
//	{
//		m_WaveID++;
//		if (m_WaveID >= nWaveMax)
//		{
//			m_WaveID = 0;
//		}
//	}
//
//	if (pKeyboard->GetTrigger(DIK_LSHIFT))
//	{ 
//		if (pKeyboard->GetTrigger(DIK_1))		m_Wave[m_WaveID].K.x += 0.01f;
//		if (pKeyboard->GetTrigger(DIK_2))		m_Wave[m_WaveID].K.y += 0.01f;
//		if (pKeyboard->GetTrigger(DIK_3))		m_Wave[m_WaveID].Omega += 0.1f;
//		if (pKeyboard->GetTrigger(DIK_4))		m_Wave[m_WaveID].OmegaT += 0.1f;
//	}
//	else 
//	{ 
//		if (pKeyboard->GetTrigger(DIK_1))		m_Wave[m_WaveID].K.x -= 0.01f;  
//		if (pKeyboard->GetTrigger(DIK_2))		m_Wave[m_WaveID].K.y -= 0.01f;  
//		if (pKeyboard->GetTrigger(DIK_3))		m_Wave[m_WaveID].Omega -= 0.1f;  
//		if (pKeyboard->GetTrigger(DIK_4))		m_Wave[m_WaveID].OmegaT -= 0.1f;
//	}   
//
//	if (pKeyboard->GetTrigger(DIK_5))			m_Wave[m_WaveID].A += 0.1f; 
//	if (pKeyboard->GetTrigger(DIK_6))			m_Wave[m_WaveID].A -= 0.1f;
//
//	if (pKeyboard->GetTrigger(DIK_7))			m_Wave[m_WaveID].t = 0.0f;
//
//	if (pKeyboard->GetTrigger(DIK_8))
//	{ 
//		m_Wave[m_WaveID].WaveLength += 1.0f;
//		m_Wave[m_WaveID].k = 2.0f * D3DX_PI / m_Wave[m_WaveID].WaveLength;
//		D3DXVec2Normalize(&m_Wave[m_WaveID].K, &m_Wave[m_WaveID].K);
//		m_Wave[m_WaveID].K *= m_Wave[m_WaveID].k;
//		m_Wave[m_WaveID].testAk = m_Wave[m_WaveID].A * m_Wave[m_WaveID].k;
//	}  
//	if (pKeyboard->GetTrigger(DIK_9))
//	{ 
//		m_Wave[m_WaveID].WaveLength -= 1.0f;
//		m_Wave[m_WaveID].k = 2.0f * D3DX_PI / m_Wave[m_WaveID].WaveLength;
//		D3DXVec2Normalize(&m_Wave[m_WaveID].K, &m_Wave[m_WaveID].K);
//		m_Wave[m_WaveID].K *= m_Wave[m_WaveID].k;
//		m_Wave[m_WaveID].testAk = m_Wave[m_WaveID].A * m_Wave[m_WaveID].k;
//	} 
//	if (pKeyboard->GetTrigger(DIK_0))
//	{ 
//		m_Wave[m_WaveID].k = 2.0f * D3DX_PI / m_Wave[m_WaveID].WaveLength;
//		D3DXVec2Normalize(&m_Wave[m_WaveID].K, &m_Wave[m_WaveID].K);
//		m_Wave[m_WaveID].K *= m_Wave[m_WaveID].k;
//		m_Wave[m_WaveID].testAk = m_Wave[m_WaveID].A * m_Wave[m_WaveID].k;
//	}
#endif

	for (int i = 0; i < m_Mesh.VertexNum; i++)
	{
		posXZ = D3DXVECTOR2(pVec[i].x, pVec[i].z);
		posY = pVec[i].y;

		for (int j = 0; j < nWaveMax; j++)
		{
			// x = x0 - (K / k)*Asin(K*x0 - ωt)
			// y = Acos(K*x0 - ωt)
			temp = D3DXVec2Dot(&m_Wave[j].K, &posXZ) - m_Wave[j].Omega * m_Wave[j].t;

			//  変位量を算出
			posXZDif += (m_Wave[j].K / m_Wave[j].k) * m_Wave[j].A * sinf(temp);
			posYDif += m_Wave[j].A * cosf(temp);
		}

		//  座標を更新
		m_VertexPos[i].x = posXZ.x - posXZDif.x;
		m_VertexPos[i].z = posXZ.y - posXZDif.y;
		m_VertexPos[i].y = posY - posYDif;
	}

	for (int k = 0; k < nWaveMax; k++)
	{
		m_Wave[k].t += m_Wave[k].OmegaT;
	}

	m_PositionBuffer->Unlock();

	//  法線情報を算出
	CalculateNormal();

	SetVertex();
}

//------------------------------------------------------------------------------
//	関数名:	void CMeshField::CheckVertex
//	引数:	D3DXVECTOR3 pos
//	戻り値:	なし
//	説明:	現在いる頂点番号のチェック
//------------------------------------------------------------------------------
int CMeshField::CheckVertex(D3DXVECTOR3 pos)
{
	int		nWidthID;		//  横頂点番号
	int		nHeightID;		//  縦頂点番号
	float	fWidthID;		//  横頂点番号（float型）
	float	fHeightID;		//  縦頂点番号（float型）
	int		nInVertexID;	//  現在いる頂点番号

	//  フィールド範囲内であれば
	if ( pos.x >= m_VertexPos[0].x && pos.x <= m_VertexPos[m_Mesh.HeightNum - 1].x
		&&
		pos.z <= m_VertexPos[0].z && pos.z >= m_VertexPos[m_Mesh.VertexNum - 1].z )
	{
		//  現在いる頂点番号 = フィールド中心頂点 + 対象の座標 / フィールドの長さ
		fWidthID = m_Mesh.WidthNum * 0.5f + pos.x / m_Size.x;
		fHeightID = m_Mesh.HeightNum * 0.5f - pos.z / m_Size.z;

		nWidthID = (int)fWidthID;
		nHeightID = (int)fHeightID;

		// 現在いる頂点番号を算出
		nInVertexID = nHeightID * m_Mesh.WidthNum + nWidthID;
	}
	else
	{
		nInVertexID = -1;
	}

	return nInVertexID;
}

//------------------------------------------------------------------------------
//	関数名:	float CMeshField::GetHeight
//	引数:	D3DXVECTOR3 pos
//	戻り値:	float fHeight
//	説明:	対象とプリミティブの交差点を求める（高さ）
//			ポリゴンチェック：島は１、海は３ｘ３
//------------------------------------------------------------------------------
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3	VectorVtx[6], VectorObject[6], VectorResult[6];
	D3DXVECTOR3	Vector[4], Normal[2];
	int			nNum[4];
	float		fHeight;
	int			nCheckMax;
	int			nInVertexID;
	int			nCheckVertexID[9];

	//  参照物のいる頂点番号をチェック
	nInVertexID = CheckVertex(pos);

	//  メッシュタイプごとにブロック計算数をわける
	switch (m_Mesh.Type)
	{
	case MESH_ISLAND:
		nCheckVertexID[0] = nInVertexID;
		nCheckMax = 1;
		break;
	case MESH_SEA:
		for (int i = 0; i < 3; i++)
		{
			nCheckVertexID[0 + i * 3] = nInVertexID + i - 1 - m_Mesh.WidthNum;
			nCheckVertexID[1 + i * 3] = nInVertexID + i - 1;
			nCheckVertexID[2 + i * 3] = nInVertexID + i - 1 + m_Mesh.WidthNum;
		}
		nCheckMax = 9;
		break;
	}

	for (int i = 0; i < nCheckMax; i++)
	{
		if (nInVertexID != -1)
		{
			//  ブロック頂点番号を算出
			nNum[0] = nCheckVertexID[i];
			nNum[1] = nNum[0] + 1;
			nNum[2] = nNum[0] + m_Mesh.WidthNum;
			nNum[3] = nNum[0] + m_Mesh.WidthNum + 1;

			//  プリミティブのベクトルを計算
			VectorVtx[0] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[2]];
			VectorVtx[1] = m_VertexPos[nNum[3]] - m_VertexPos[nNum[0]];
			VectorVtx[2] = m_VertexPos[nNum[2]] - m_VertexPos[nNum[3]];

			VectorVtx[3] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[1]];
			VectorVtx[4] = m_VertexPos[nNum[1]] - m_VertexPos[nNum[3]];
			VectorVtx[5] = VectorVtx[1];

			//  対象のベクトルを計算
			VectorObject[0] = pos - m_VertexPos[nNum[2]];
			VectorObject[1] = pos - m_VertexPos[nNum[0]];
			VectorObject[2] = pos - m_VertexPos[nNum[3]];

			VectorObject[3] = pos - m_VertexPos[nNum[1]];
			VectorObject[4] = pos - m_VertexPos[nNum[3]];
			VectorObject[5] = pos - m_VertexPos[nNum[0]];

			for (int nCnt = 0; nCnt < 6; nCnt++)
			{
				//  ベクトルＹ座標を０に設定
				VectorVtx[nCnt].y =
				VectorObject[nCnt].y = 0.0f;

				//  対象がプリミティブ各辺の左右どちらかにいるの計算（外積）
				D3DXVec3Cross(&VectorResult[nCnt], &VectorObject[nCnt], &VectorVtx[nCnt]);
			}

			//  左右プリミティブ２辺のベクトルを計算
			Vector[0] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[2]];
			Vector[1] = m_VertexPos[nNum[3]] - m_VertexPos[nNum[2]];
			Vector[2] = m_VertexPos[nNum[3]] - m_VertexPos[nNum[1]];
			Vector[3] = m_VertexPos[nNum[0]] - m_VertexPos[nNum[1]];

			//  プリミティブ法線を求める(時計回り)
			D3DXVec3Cross(&Normal[0], &Vector[0], &Vector[1]);
			D3DXVec3Cross(&Normal[1], &Vector[2], &Vector[3]);

			//  プリミティブ法線の正規化
			D3DXVec3Normalize(&Normal[0], &Normal[0]);
			D3DXVec3Normalize(&Normal[1], &Normal[1]);

			//  左右プリミティブどちらにいるチェック
			if (VectorResult[0].y <= 0)		//  左
			{
				if (VectorResult[1].y <= 0)
				{
					if (VectorResult[2].y <= 0)
					{
						//  高さを求める
						fHeight = m_VertexPos[nNum[2]].y - ((Normal[0].x * (pos.x - m_VertexPos[nNum[2]].x)) + Normal[0].z * (pos.z - m_VertexPos[nNum[2]].z)) / Normal[0].y;
					}
				}
			}

			if (VectorResult[3].y > 0)		//  右
			{
				if (VectorResult[4].y > 0)
				{
					if (VectorResult[5].y > 0)
					{
						//  高さを求める
						fHeight = m_VertexPos[nNum[1]].y - ((Normal[1].x * (pos.x - m_VertexPos[nNum[1]].x)) + Normal[1].z * (pos.z - m_VertexPos[nNum[1]].z)) / Normal[1].y;
					}
				}
			}
		}
	}

	return fHeight;
}
