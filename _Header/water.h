//------------------------------------------------------------------------------
//	タイトル：		水エフェクトのヘッダー
//	ファイル名：	water.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/09/27
//------------------------------------------------------------------------------
#ifndef _WATER_H_
#define _WATER_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"
#include "manager.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const int nWater_Anim_Max = 50;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  水データクラス
class CWater_Data
{
public:
	D3DXVECTOR3 Pos;			//  現在の位置
	D3DXVECTOR3	Rot;			//  回転
	D3DXVECTOR3	Size;			//  サイズ
	D3DXVECTOR3	Scl;			//  拡大縮小
	EFFECT_TYPE	WaterType;		//  水タイプ
	CMatrix		Matrix;			//  マトリックス
	CAnimation	Anim;			//  アニメーション
	bool		Flag;			//  trueは使用する
	bool		AnimLoop;		//  trueはループする
	bool		AlphaTest;		//  trueはアルファテストする
	bool		AlphaBlend;		//  trueはアルファブレンドする

	CWater_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, WaterType(EFFECT_NONE)
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
	{}
};

//  エフェクトクラス
class CWater : public CScene
{
public:
	CWater(int nPriority = 3, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CWater();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CWater *Create(void);
	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, EFFECT_TYPE WaterType, bool bAnimLoop, bool AlphaTest, bool AlphaBlend);

private:
	CWater_Data				m_Water[nWater_Anim_Max];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;					//  頂点バッファへのポインタ
	CAnimation				m_InitAnim[EFFECT_WATER_IMPACT + 1];
};

#endif