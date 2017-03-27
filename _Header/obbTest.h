//------------------------------------------------------------------------------
//	タイトル：		Obbテストのヘッダー
//	ファイル名：	ObbTest.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/01
//------------------------------------------------------------------------------
#ifndef _ObbTEST_H_
#define _ObbTEST_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  Obbテストデータクラス
class CObbTest_Data
{
public:
	D3DXVECTOR3 Pos;			//  現在の位置
	D3DXVECTOR3	Rot;			//  回転
	D3DXVECTOR3	Size;			//  サイズ
	D3DXVECTOR3	Scl;			//  拡大縮小
	CMatrix		Matrix;			//  マトリックス
	bool		Flag;

	CObbTest_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Flag(false)
	{}
};

//  ObbTestクラス
class CObbTest : public CScene
{
private:
	CObbTest_Data			m_ObbTest;
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;		//  頂点バッファへのポインタ
	bool					m_bObbTest;
	D3DXCOLOR				m_Col;

public:
	CObbTest(int nPriority = 2, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CObbTest();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(void);
	static	CObbTest *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void	SetCol(D3DXCOLOR col);
	void	SetPos(D3DXVECTOR3 pos);
	void	SetRot(D3DXVECTOR3 rot);
};

#endif