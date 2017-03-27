//------------------------------------------------------------------------------
//	タイトル：		モデルの関数
//	ファイル名：	model.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/12/13
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "model.h"
#include "manager.h"

//------------------------------------------------------------------------------
//	関数名:	CModel::CModel
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CModel::CModel()
{
	m_ModelData	= NULL;
	m_Parent	= NULL;
	m_SizeFVF	=
	m_NumVertex = 0;
	m_Pos		=
	m_Rot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bBroken	= false;
}

//------------------------------------------------------------------------------
//	関数名:	CModel::~CModel
//	引数:	なし
//	戻り値:	なし
//	説明:	デストラクタ
//------------------------------------------------------------------------------
CModel::~CModel()
{
}

//------------------------------------------------------------------------------
//	関数名:	CModel *CModel::Create
//	引数:	MODEL_TYPE	Model_Type	//  モデルタイプ
//			MODEL_PARTS Model_Parts	//  モデルパーツ
//			D3DXVECTOR3 pos			//  位置
//			D3DXVECTOR3 rot			//  回転
//	戻り値:	*pModel
//	説明:	モデルを生成
//------------------------------------------------------------------------------
CModel *CModel::Create(MODEL_TYPE Model_Type, MODEL_PARTS Model_Parts, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel;
	pModel = new CModel;

	pModel->m_Pos			= pos;					//  位置情報
	pModel->m_Rot			= rot;					//  回転
	pModel->m_ModelType		= Model_Type;			//  モデルタイプ
	pModel->m_ModelParts	= Model_Parts;			//  モデルパーツ

	//  初期化
	pModel->Init();

	return pModel;
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CModel::Init(void)
{
	//  パーツごとにモデルデータを取得
	m_ModelData = CManager::GetModeData(m_ModelParts);
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CModel::Uninit(void)
{
	m_ModelData = NULL;		//  モデルデータ
	m_Parent	= NULL;		//  親情報
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CModel::Update(void)
{
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CModel::Draw(void)
{
	D3DXMATERIAL	*pMat;
	D3DMATERIAL9	matDef;
	D3DXMATRIX		pParentMatrix;

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Matrix.World);

	//  親マトリックスの初期化
	D3DXMatrixIdentity(&pParentMatrix);

	//  親の設定
	if (m_Parent != NULL)	pParentMatrix = m_Parent->GetWorldMatrix();
	else					pDevice->GetTransform(D3DTS_WORLD, &pParentMatrix);

	//  スケールを反映
	D3DXMatrixScaling( &m_Matrix.Scl, m_Scl.x, m_Scl.y, m_Scl.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Scl );

	//  回転を反映
	D3DXMatrixRotationYawPitchRoll( &m_Matrix.Rot, m_Rot.y, m_Rot.x, m_Rot.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Rot );

	//  位置を反映
	D3DXMatrixTranslation( &m_Matrix.Trans, m_Pos.x, m_Pos.y, m_Pos.z );
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &m_Matrix.Trans );

	//  親のマトリックスを反映
	D3DXMatrixMultiply( &m_Matrix.World, &m_Matrix.World, &pParentMatrix );
	
	//  ワールドマトリックスを設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Matrix.World);

	//  現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL *)m_ModelData->BufferMat->GetBufferPointer();

	for (int i = 0; i < (int)m_ModelData->NumMat; i++)
	{
		//  マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//  テクスチャの設定
		pDevice->SetTexture(0, CManager::GetModelTextureBuffer(m_ModelType, m_bBroken));

		//  メッシュの描画
		m_ModelData->Mesh->DrawSubset(i);
	}

	//  マテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//------------------------------------------------------------------------------
//	関数名:	D3DXMATRIX CModel::GetWorldMatrix(void)
//	引数:	なし
//	戻り値:	m_Matrix.World
//	説明:	ワールドマトリックスを取得
//------------------------------------------------------------------------------
D3DXMATRIX CModel::GetWorldMatrix(void)
{
	return m_Matrix.World;
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::SetParent
//	引数:	CModel *model
//	戻り値:	なし
//	説明:	親を設定
//------------------------------------------------------------------------------
void CModel::SetParent(CModel *model)
{
	m_Parent = model;
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::SetPosition
//	引数:	D3DXVECTOR3 m_Pos
//	戻り値:	なし
//	説明:	位置を設定
//------------------------------------------------------------------------------
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//------------------------------------------------------------------------------
//	関数名:	void CModel::SetRotation
//	引数:	D3DXVECTOR3 m_Rot
//	戻り値:	なし
//	説明:	回転を設定
//------------------------------------------------------------------------------
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_Rot = rot;
}

void CModel::SetBroken(bool bFlag)
{
	m_bBroken = bFlag;
}