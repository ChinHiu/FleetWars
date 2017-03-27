//------------------------------------------------------------------------------
//	タイトル：		モデルのヘッダー
//	ファイル名：	model.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/12/13
//------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  モデルクラス
class CModel
{
public:
	CModel();
	~CModel();

	static CModel *Create(MODEL_TYPE Model_Type, MODEL_PARTS Model_Parts, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//  取得関数
	D3DXMATRIX	GetWorldMatrix(void);

	//  セット関数
	void SetParent(CModel *model);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetBroken(bool bFlag);

private:
	CMatrix						m_Matrix;			//  マトリックス
	CModel_Data					*m_ModelData;		//  モデルデータ
	CModel						*m_Parent;			//  親
	DWORD						m_SizeFVF;			//  頂点フォーマット
	int							m_NumVertex;		//  頂点数

	D3DXVECTOR3					m_Pos;				//  位置
	D3DXVECTOR3					m_Rot;				//  向き
	D3DXVECTOR3					m_Scl;				//  拡大縮小

	MODEL_TYPE					m_ModelType;		//  モデルタイプ
	MODEL_PARTS					m_ModelParts;		//  モデルパーツ

	bool						m_bBroken;			//  破壊したかどうか
};

#endif