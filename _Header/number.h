//------------------------------------------------------------------------------
//	タイトル：		ナンバーのヘッダー
//	ファイル名：	number.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/06/24
//------------------------------------------------------------------------------
#ifndef _NUMBER_H_
#define _NUMBER_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define NUMBER_TEXTURE_FILE "./data/TEXTURE/UI/GAME/Other/Number.png" 

//  前方宣言
typedef enum {
	NUMBER_TYPE_NONE = -1,
	NUMBER_TYPE_POWER,
	NUMBER_TYPE_SPEED,
	NUMBER_TYPE_TIME,
	NUMBER_TYPE_VALUE,
	NUMBER_TYPE_DAMAGE,
	NUMBER_TYPE_MAX
}NUMBER_TYPE;

typedef struct
{
	D3DXVECTOR3 pos0;
	D3DXVECTOR3 pos1;
	D3DXVECTOR3 pos2;
	D3DXVECTOR3 pos3;
}VERTEX_POS;

class CNumber_Data
{
public:
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	int			*value;		//  値
	int			sigFigs;	//  有効桁数
	int			*digit;		//  桁数
	NUMBER_TYPE Type;
	D3DXCOLOR	Col;
	bool		Flag;
	bool		*digitFlag;
};

//  ナンバー構造体
typedef struct
{
	int value;		//  値
	int sigFigs;	//  有効桁数
	int *digit;		//  桁数
}NUMBER;

typedef enum
{
	DIGIT_SYMBOL_PERCENT = 10,
	DIGIT_SYMBOL_KNOT,
	DIGIT_SYMBOL_COLON,
	DIGIT_SYMBOL_DOT
}DIGHIT_SYMBOL_TYPE;

//  シーンクラス
class CNumber : CScene
{
public:
	CNumber(int nPriority = 4, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CNumber();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	void	CalculateVertex(void);
	VERTEX_POS *GetVertexPos(void);

	void	PowerDigitUpdate(void);
	void	SpeedDigitUpdate(void);
	void	TimeDigitUpdate(void);
	void	ValueDigitUpdate(void);
	void	DamageDigitUpdate(void);

	void	SetTexture(void);
	void	SetNumberFlag(bool bFlag);

	int		Powi(int x, int y);

	static	CNumber *Create(int *value, int sigFigs, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, NUMBER_TYPE Number_Type, bool bFlag);

private:
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;						//  頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_TextureBuffer;					//  テクスチャへのポインタ
	CNumber_Data			m_Number;
	VERTEX_POS				*m_VertexPos;
	int						m_MinuteCnt;
	int						m_SecondCnt;
	int						m_SpeedCnt;
};

#endif