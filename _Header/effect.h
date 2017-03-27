//------------------------------------------------------------------------------
//	タイトル：		エフェクトのヘッダー
//	ファイル名：	effect.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/12/15
//------------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------

const int nEffect_Anim_Max = 50;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  エフェクトデータクラス
class CEffect_Data
{
public:
	D3DXVECTOR3 Pos;			//  現在の位置
	D3DXVECTOR3	Rot;			//  回転
	D3DXVECTOR3 Size;			//  サイズ
	D3DXVECTOR3 Scl;			//  拡大縮小
	EFFECT_TYPE	EffectType;		//  バレットタイプ
	CMatrix		Matrix;			//  マトリックス
	D3DXMATRIX	ViewMatrix;		//  ビューマトリックス
	CAnimation	Anim;			//  アニメーション
	bool		Flag;			//  trueは使用する
	bool		AnimLoop;		//  trueはループする
	bool		AlphaTest;		//  trueはアルファテストする
	bool		AlphaBlend;		//  trueはアルファブレンドする
	bool		ZBuffer;

	CEffect_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, EffectType(EFFECT_NONE)
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
		, ZBuffer(false)
	{
		D3DXMatrixIdentity(&ViewMatrix);
	}
};

//  エフェクトクラス
class CEffect : public CScene
{
public:
	CEffect(int nPriority = 3, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CEffect();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CEffect *Create(void);
	void	SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, EFFECT_TYPE EffectType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend, bool ZBuffer);

private:
	CEffect_Data			m_Effect[nEffect_Anim_Max];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;											//  頂点バッファへのポインタ
	CAnimation				m_Anim[EFFECT_EXPLOSION_001 - EFFECT_WATER_IMPACT];
};

#endif