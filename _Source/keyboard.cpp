//------------------------------------------------------------------------------
//	タイトル：		ditectInput関連の関数
//	ファイル名：	directInput.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/10
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "input.h"
#include "keyboard.h"

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CKeyboard::CKeyboard
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CKeyboard::CKeyboard()
{
	m_Dev = NULL;

	ZeroMemory(m_KeyboardState,sizeof(m_KeyboardState));		//  キーボードの状態を受け取るワーク
	ZeroMemory(m_StateTrigger, sizeof(m_StateTrigger));			//  トリガー状態を受け取るワーク
	ZeroMemory(m_StateRelease, sizeof(m_StateRelease));			//  リリス状態を受け取るワーク
	ZeroMemory(m_StateRepeat, sizeof(m_StateRepeat));			//  リピート状態を受け取るワーク
	ZeroMemory(m_StateRepeatCnt, sizeof(m_StateRepeatCnt));		//  リピートカウンタを受け取るワーク
}

//------------------------------------------------------------------------------
//	関数名:	CScene::~CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CKeyboard::~CKeyboard()
{
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CKeyboard::Init
//	引数:	HINSTANCE hInstance, HWND hWnd
//	戻り値:	E_FAILだと初期化失敗、S_OKだと初期化成功
//	説明:	初期化処理
//------------------------------------------------------------------------------
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input)
{
	//  IDirectInput8インターフェースへのポインタを取得
	LPDIRECTINPUT8 pInput = Input;

	if (FAILED(pInput->CreateDevice(GUID_SysKeyboard, &m_Dev, NULL)))
	{//  デバイスオブジェクトを作成
		MessageBox(hWnd, "キーボードがありません！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	if (m_Dev != NULL)
	{
		if (FAILED(m_Dev->SetDataFormat(&c_dfDIKeyboard)))											//データフォーマットの設定
		{//  データフォーマットを設定
			MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//  協調モードを設定（フォアグラウンド＆非排他モード）
		if (FAILED(m_Dev->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))	//協調モードの設定
		{
			MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//  入力制御開始
		m_Dev->Acquire();
	}

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CKeyboard::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CKeyboard::Uninit(void)
{
	if (m_Dev != NULL)
	{//  アクセス権を開放
		m_Dev->Unacquire();
		m_Dev->Release();
		m_Dev = NULL;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CKeyboard::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CKeyboard::Update(void)
{
	if (m_Dev != NULL)
	{
		BYTE KeyStateOld[nKeyMax];

		//  前回のデータを保存
		memcpy(KeyStateOld, m_KeyboardState, nKeyMax);

		if (SUCCEEDED(m_Dev->GetDeviceState(sizeof(m_KeyboardState), m_KeyboardState)))
		{//  デバイスからデータを取得
			for (int i = 0; i < nKeyMax; i++)
			{
				m_StateTrigger[i]	= (KeyStateOld[i] ^ m_KeyboardState[i]) & m_KeyboardState[i];
				m_StateRelease[i]	= (KeyStateOld[i] ^ m_KeyboardState[i]) & ~m_KeyboardState[i];
				m_StateRepeat[i]	= m_StateTrigger[i];

				if (m_KeyboardState[i])
				{
					m_StateRepeatCnt[i]++;
					if (m_StateRepeatCnt[i] >= nRepeatCnt)
					{
						m_StateRepeat[i] = m_KeyboardState[i];
					}
				}
				else
				{
					m_StateRepeatCnt[i] = 0;
					m_StateRepeat[i] = 0;
				}
			}
		}
		else
		{
			//  キーボードへのアクセス権を取得
			m_Dev->Acquire();
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	bool CKeyboard::GetPress
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	キーボードのプレス状態を取得
//------------------------------------------------------------------------------
bool CKeyboard::GetPress(int nKey)
{
	return (m_KeyboardState[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	関数名:	bool CKeyboard::GetTrigger
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	キーボードのトリガー状態を取得
//------------------------------------------------------------------------------
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_StateTrigger[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	関数名:	bool CKeyboard::GetRelease
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	キーボードのリリース状態を取得
//------------------------------------------------------------------------------
bool CKeyboard::GetRelease (int nKey)
{
	return (m_StateRelease[nKey] & 0x80) ? true : false;
}


//------------------------------------------------------------------------------
//	関数名:	bool CKeyboard::GetRepeat
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	キーボードのリピート状態を取得
//------------------------------------------------------------------------------
bool CKeyboard::GetRepeat(int nKey)
{
	return (m_StateRepeat[nKey] & 0x80) ? true : false;
}
