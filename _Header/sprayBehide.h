//------------------------------------------------------------------------------
//	タイトル：		水しぶきのヘッダー
//	ファイル名：	sprayBehide.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/02
//------------------------------------------------------------------------------
#ifndef _SPRAYBEHIDE_H_
#define _SPRAYBEHIDE_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const int nSprayMax = 9;

class CSprayBehide_Data
{
public:
	D3DXVECTOR3 *Pos,			//  現在の位置
				*Rot,			//  回転
				*Size,			//  サイズ
				Scl;			//  拡大縮小
	CMatrix		Matrix;			//  マトリックス
	CAnimation	Anim;			//  アニメーション
	bool		Flag,			//  trueは使用する
				AnimLoop,		//  trueはループする
				AlphaTest,		//  trueはアルファテストする
				AlphaBlend;		//  trueはアルファブレンドする

	CSprayBehide_Data()
		: Pos(NULL)
		, Rot(NULL)
		, Size(NULL)
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
	{}
};

//  エフェクトクラス
class CSprayBehide : public CScene
{
private:
	CSprayBehide_Data		m_SprayBehide[nSprayMax];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;				//  頂点バッファへのポインタ
	CAnimation				m_Anim;

public:
	CSprayBehide(int nPriority = 1, OBJECT_TYPE Object_Type = OBJTYPE_PLAYER);
	~CSprayBehide();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CSprayBehide *Create(void);
	void	Set(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, bool bAnimLoop);
};

#endif