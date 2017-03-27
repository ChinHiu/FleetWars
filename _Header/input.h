//------------------------------------------------------------------------------
//	タイトル：		inputのヘッダー
//	ファイル名：	input.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/10
//------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CKeyboard;
class CMouse;

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------
const int nKeyMax = 256;				//  キーの最大数
const int nRepeatCnt = 20;				//  リピート開始までの待ち時間

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  DirectInputクラス
class CInput
{
public:
	CInput();
	~CInput();
	HRESULT			Init(HINSTANCE hInstance, HWND hWnd);
	void			Uninit(void);
	void			Update(void);

	//  取得関数
	CKeyboard		*GetKeyboard(void);
	CMouse			*GetMouse(void);

private:
	LPDIRECTINPUT8	m_Input;		//  IDirectInput8インターフェースへのポインタ
	CKeyboard		*m_Keyboard;
	CMouse			*m_Mouse;
};
#endif