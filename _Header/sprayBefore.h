//------------------------------------------------------------------------------
//	タイトル：		水しぶきのヘッダー
//	ファイル名：	spray.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/02/02
//------------------------------------------------------------------------------
#ifndef _SPRAYBEFORE_H_
#define _SPRAYBEFORE_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define SPRAY_BEFORE_TEXTURE_FILE		"./data/TEXTURE/EffectAnim/Spray_Before_4_8.png"
#define SPRAY_BEHIDE_TEXTURE_FILE		"./data/TEXTURE/EffectAnim/Spray_Behide_8_2.png"

//  水しぶきタイプ
typedef enum
{
	SPRAY_NONE = -1,
	SPRAY_BEFORE_LEFT,
	SPRAY_BEFORE_RIGHT,
	SPRAY_TYPE_MAX
}SPRAY_TYPE;

class CSpray_Data
{
public:
	D3DXVECTOR3 *Pos;			//  現在の位置
	D3DXVECTOR3	*Rot;			//  回転
	D3DXVECTOR3	*Size;			//  サイズ
	D3DXVECTOR3	Scl;			//  拡大縮小
	SPRAY_TYPE	SprayType;		//  バレットタイプ
	CMatrix		Matrix;			//  マトリックス
	CAnimation	Anim;			//  アニメーション
	bool		Flag;			//  trueは使用する
	bool		AnimLoop;		//  trueはループする
	bool		AlphaTest;		//  trueはアルファテストする
	bool		AlphaBlend;		//  trueはアルファブレンドする
	D3DXVECTOR2 AdjustRot;

	CSpray_Data()
		: Pos(NULL)
		, Rot(NULL)
		, Size(NULL)
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, SprayType(SPRAY_NONE)
		, Flag(false)
		, AnimLoop(false)
		, AlphaTest(false)
		, AlphaBlend(false)
		, AdjustRot(D3DXVECTOR2(0.0f, 0.0f))
	{}
};

//  エフェクトクラス
class CSpray
{
private:
	CSpray_Data				m_Spray[SPRAY_TYPE_MAX];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;				//  頂点バッファへのポインタ
	CAnimation				m_Anim[SPRAY_TYPE_MAX];
	MODEL_TYPE				m_Type;

public:
	CSpray();
	~CSpray();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(int nID);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetVertex(int nID);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY, int nID);
	static	CSpray *Create(void);
	void	Set(MODEL_TYPE Model_Type, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot, D3DXVECTOR3 *size, SPRAY_TYPE Spray_Type, bool bAnimLoop);
};

#endif