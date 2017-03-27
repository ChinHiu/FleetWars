//------------------------------------------------------------------------------
//	タイトル：		キーボードのヘッダー
//	ファイル名：	keyboard.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/10
//------------------------------------------------------------------------------
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  キーボードクラス
class CKeyboard
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT	Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input);
	void	Uninit(void);
	void	Update(void);

	//  取得関数
	bool	GetPress(int key);
	bool	GetTrigger(int key);
	bool	GetRelease(int key);
	bool	GetRepeat(int key);

private:
	LPDIRECTINPUTDEVICE8	m_Dev;									//  IDirectInputDevice8インターフェースへのポインタ(キーボード)
	BYTE					m_KeyboardState[nKeyMax];			//  キーボードの状態を受け取るワーク
	BYTE					m_StateTrigger[nKeyMax];				//  トリガー状態を受け取るワーク
	BYTE					m_StateRelease[nKeyMax];				//  リリス状態を受け取るワーク
	BYTE					m_StateRepeat[nKeyMax];				//  リピート状態を受け取るワーク
	int						m_StateRepeatCnt[nKeyMax];			//  リピートカウンタを受け取るワーク
};

#endif