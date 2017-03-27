//------------------------------------------------------------------------------
//	タイトル：		メインのヘッダー
//	ファイル名：	main.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/18
//------------------------------------------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "Windows.h"
#include "manager.h"

//------------------------------------------------------------------------------
//	ライブラリのリンク
//------------------------------------------------------------------------------
#pragma comment ( lib, "winmm.lib" )		//  マルチメディアタイマー使用に必要

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------
const int nNumVertex = 4;						// 頂点数
const int nNumPolygon = 2;						// ポリゴン数
const float fScreenSizeWidthMax = 1920.0f;		//  画面幅最大値

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
//  RELEASE開放
#define SAFE_RELEASE( p )	if( p != NULL )					\
							{								\
								( p ) -> Release();			\
								p = NULL;					\
							}

//  角度のチェック
#define SAFE_ROTCHECK( rot )	if( rot > D3DX_PI )				\
								{								\
									rot -= D3DX_PI * 2.0f;		\
								}								\
								else if( rot < -D3DX_PI )		\
								{								\
									rot += D3DX_PI * 2.0f;		\
								}

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  軸指定用（人為的なミスを避ける）
typedef enum
{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS
}AXIS;

//  ユーザータイプ
typedef enum
{
	USER_NONE = -1,
	USER_PLAYER,
	USER_ENEMY,
	USER_MAX
}USER_TYPE;

//------------------------------------------------------------------------------
//	構造体定義
//------------------------------------------------------------------------------

//  KEY構造体
typedef struct
{
	int UP;
	int DOWN;
	int LEFT;
	int RIGHT;
	int CAMERA;
	int HIT;
	int LOCK;
}KEY;

//  画面情報構造体
typedef struct
{
	D3DXVECTOR2 ScreenSize;
	float		ScreenRate;
	bool		bWindow;
	int			iDifficulty;
	KEY			Key;
}DISPLAY;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  2Dテクスチャデータ
class CTex2D_Data
{
public:
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 Rot;
	D3DXVECTOR2 Size;
	D3DXCOLOR	Col;
	bool		Flag;

	CTex2D_Data()
		: Pos(D3DXVECTOR2(0.0f, 0.0f))
		, Rot(D3DXVECTOR2(0.0f, 0.0f))
		, Size(D3DXVECTOR2(0.0f, 0.0f))
		, Col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
		, Flag(false)
	{}
};

//  選択UI用クラス
class CSelect_Data
{
public:
	D3DXCOLOR	Col;
	int			nFrameCnt;
	int			nPattern;
	bool		bSelect;
	int			nChangeTime;

	CSelect_Data()
		: Col(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
		, nFrameCnt(0)
		, nPattern(0)
		, bSelect(false)
		, nChangeTime(0)
	{}
};

//  マトリックスクラス
class CMatrix
{
public:
	D3DXMATRIX	World;			//  ワールドマトリックス
	D3DXMATRIX	Scl;			//  スケールマトリックス
	D3DXMATRIX	Rot;			//  回転マトリックス
	D3DXMATRIX	Trans;			//  位置マトリックス

	CMatrix()
	{
		D3DXMatrixIdentity(&World);
		D3DXMatrixIdentity(&Scl);
		D3DXMatrixIdentity(&Rot);
		D3DXMatrixIdentity(&Trans);
	}
};

//  キャラクターデータクラス
class CCharacter_Data
{
public:
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 OldPos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 OldRot;
	D3DXVECTOR3 Scl;
	float		fAimSpeed;
	float		fSpeed;
	int			nLife;
	bool		bFlag;

	CCharacter_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, OldPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, OldRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, fAimSpeed(0.0f)
		, fSpeed(0.0f)
		, nLife(0)
		, bFlag(false)
	{}
};

//  武器データクラス
class CWeapon_Data
{
public:
	int nNum;
	float fCoolDown;
	int	nCoolDown;
	bool bFlag;


	CWeapon_Data()
		: nNum(0)
		, fCoolDown(0)
		, nCoolDown(0)
		, bFlag(false)
	{}
};

//  Obbクラス
class CObb
{
private:
	D3DXVECTOR3 Pos;			//  位置
	D3DXVECTOR3 Direct[3];		//  方向ベクトル
	D3DXVECTOR3 Length;			//  各軸方向の長さ

public:
	D3DXVECTOR3 GetDirect(int nID)	{ return Direct[nID]; };		//  指定軸番号の方向ベクトルを取得
	FLOAT		GetLength(int nID)	{ return Length[nID]; };		//  指定軸方向の長さを取得
	D3DXVECTOR3 GetPos(void)		{ return Pos; };				//  位置を取得

	void		SetDirect(int nID, D3DXVECTOR3 direct)	{ Direct[nID] = direct; }
	void		SetPos(D3DXVECTOR3 pos)					{ Pos = pos; };
	void		SetLength(D3DXVECTOR3 length)			{ Length = length; };
};

//  アニメーションクラス
class CAnimation
{
public:
	int PatternX;		//  横総パターン
	int	PatternY;		//  縦総パターン
	int	Pattern;		//  現在のパターン
	int	Cnt;			//  カウント
	int	Frame;			//  更新フレーム

	CAnimation()
	{
		PatternX =
		PatternY =
		Pattern =
		Cnt =
		Frame = 0;
	}
};

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
int				*GetFPS(void);				//  FPSを取得
HWND			GetWnd(void);				//  ウィンドウハンドルを取得
D3DXVECTOR2		*GetScreenSize(void);		//  スクリーンサイズを取得
float			*GetScreenRate(void);
#endif