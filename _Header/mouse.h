//------------------------------------------------------------------------------
//	タイトル：		マウスのヘッダー
//	ファイル名：	keyboard.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/10
//------------------------------------------------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CCursor;

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  マウスボタン
typedef enum
{
	DIM_LEFT = 0,		//  マウス左ボタン
	DIM_RIGHT,			//  マウス右ボタン
	DIM_CENTER,			//  マウス中ボタン
	DIM_MAX
}MOUSE_BUTTONS;

//------------------------------------------------------------------------------
//	構造体定義
//------------------------------------------------------------------------------

//  マウスポインタ情報の構造体
typedef struct
{
	RECT		moveRect;	//  画面上で動ける範囲
	int			x;			//  X座標
	int			y;			//  Y座標
	int			z;
	int			moveAdd;	//  移動量
}MSTATE;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  マウスクラス
class CMouse
{
public:
	CMouse();
	~CMouse();
	HRESULT			Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input);
	void			Uninit(void);
	void			Update(void);
	void			MouseUpdate(void);


	D3DXVECTOR3		*CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ, float Screen_w, float Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
	D3DXVECTOR3		*CalcScreenToXZ(D3DXVECTOR3* pout, int Sx, int Sy, float Screen_w, float Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);

	//  取得関数
	MSTATE			*GetMousePoint(void);
	DIMOUSESTATE	*GetMouseState(void);
	D3DXVECTOR3		*GetWorldPos(void);
	int				*GetInBlockNum(void);
	bool			GetPress(int key);
	bool			GetTrigger(int key);
	bool			GetRelease(int key);
	bool			GetRepeat(int key);
	CCursor			*GetCursor(void);

private:
	LPDIRECTINPUTDEVICE8	m_Dev;									//  IDirectInputDevice8インターフェースへのポインタ(キーボード)
	DIMOUSESTATE			m_MouseState;							//  マウスの状態を受け取るワーク
	BYTE					m_StateTrigger[nKeyMax];			//  トリガー状態を受け取るワーク
	BYTE					m_StateRelease[nKeyMax];			//  リリス状態を受け取るワーク
	BYTE					m_StateRepeat[nKeyMax];			//  リピート状態を受け取るワーク
	int						m_StateRepeatCnt[nKeyMax];			//  リピートカウンタを受け取るワーク
	MSTATE					m_Mouse;								//  マウスのポインタ情報を受け取るワーク
	D3DXVECTOR3				m_Pos;									//  ワールド位置
	int						m_nInBlockNum;							//  いるブロック
	CCursor					*m_Cursor;								//  コンソール
};

#endif