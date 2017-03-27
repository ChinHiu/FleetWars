//------------------------------------------------------------------------------
//	タイトル：		ステンシルシャドウのヘッダー
//	ファイル名：	stencil.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/11/15
//------------------------------------------------------------------------------
#ifndef _STENCILSHADOW_H_
#define _STENCILSHADOW_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define TITLE_GORSHKOV_SHADOW_FILE	"./data/MODEL/SHADOW/Title_Gorshkov_Shadow.x"
#define GORSHKOV_SHADOW_FILE		"./data/MODEL/SHADOW/Gorshkov_Shadow.x"
#define HAMINA_SHADOW_FILE			"./data/MODEL/SHADOW/Hamina_Shadow.x"

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  ステンシルシャドウクラス
class CStencilShadow
{
public:
	CStencilShadow();
	~CStencilShadow();

	static CStencilShadow *Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	HRESULT Make2DVertex(LPDIRECT3DDEVICE9 pDevice);

	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; };
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; };
	void SetFlag(bool bFlag) { m_bFlag = bFlag; };

private:
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;				//  頂点バッファへのポインタ
	LPD3DXMESH					m_Mesh;						//  メッシュ情報へのポインタ
	LPD3DXBUFFER				m_BuffMat;					//  マテリアル情報へのポインタ
	DWORD						m_NumMat;					//  マテリアル数
	int							m_NumVertices;				//  頂点数
	DWORD						m_sizeFVF;					//  頂点フォーマット
	CMatrix						m_Matrix;					//  マトリックス
	LPCSTR						m_ModelFile;				//  モデルファイル
	MODEL_TYPE					m_ModelType;				//  モデルタイプ
	D3DXVECTOR3					m_Pos;						//  位置
	D3DXVECTOR3					m_Rot;						//  回転
	D3DXVECTOR3					m_Scl;						//  拡大縮小
	bool						m_bFlag;					//  使用するかどうか
};

#endif