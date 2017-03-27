//------------------------------------------------------------------------------
//	タイトル：		マウス関連の関数
//	ファイル名：	mouse.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/31
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "input.h"
#include "mouse.h"
#include "camera.h"
#include "cursor.h"
//#include "game.h"
#include "title.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CMouse::CMouse
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CMouse::CMouse()
{
	m_Dev			= NULL;
	//m_Cursor		= NULL;
	m_MouseState.lX =
	m_MouseState.lY =
	m_MouseState.lZ = 0;
	ZeroMemory(m_StateTrigger, sizeof(m_StateTrigger));		//  トリガー状態を受け取るワーク
	ZeroMemory(m_StateRelease, sizeof(m_StateRelease));		//  リリス状態を受け取るワーク
	ZeroMemory(m_StateRepeat, sizeof(m_StateRepeat));		//  リピート状態を受け取るワーク
	ZeroMemory(m_StateRepeatCnt, sizeof(m_StateRepeatCnt));	//  リピートカウンタを受け取るワーク
}

//------------------------------------------------------------------------------
//	関数名:	CScene::~CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CMouse::~CMouse()
{
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CMouse::Init
//	引数:	HINSTANCE hInstance, HWND hWnd
//	戻り値:	E_FAILだと初期化失敗、S_OKだと初期化成功
//	説明:	初期化処理
//------------------------------------------------------------------------------
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  インスタンス生成
	m_Cursor = new CCursor;

	//  IDirectInput8インターフェースへのポインタを取得
	LPDIRECTINPUT8 pInput = Input;
	

	if (FAILED(pInput->CreateDevice(GUID_SysMouse, &m_Dev, NULL)))
	{//  デバイスオブジェクトを作成
		MessageBox(hWnd, "マウスがありません！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	if (m_Dev != NULL)
	{
		if (FAILED(m_Dev->SetDataFormat(&c_dfDIMouse)))											//  データフォーマットの設定
		{//  データフォーマットを設定
			MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//  (DISCL_EXCLUSIVE | DISCL_FOREGROUND（フォアグラウンド＆非排他モード
		//  (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
		//  協調モードを設定）
		if (FAILED(m_Dev->SetCooperativeLevel(hWnd, (DISCL_EXCLUSIVE | DISCL_FOREGROUND))))		//  協調モードの設定
		{
			MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//  軸モードを設定（相対値モードに設定）
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_REL;															//  相対値モードで設定（絶対モードはDIPROPAXISMODE_ABS）

		if (FAILED(m_Dev->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			MessageBox(hWnd, "軸モードの設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//  マウス構造体の初期化
		SetRect(&m_Mouse.moveRect, 0, 0, (int)pScreenSize->x, (int)pScreenSize->y);	//  マウスカーソルの動く範囲
		m_Mouse.x		= (int)(pScreenSize->x * 0.5f);									//  マウスカーソルのＸ座標を初期化
		m_Mouse.y		= (int)(pScreenSize->y * 0.5f);									//  マウスカーソルのＹ座標を初期化
		m_Mouse.moveAdd	= 2;															//  マウスカーソルの移動量を設定

		//入力制御開始
		m_Dev->Acquire();

		//カーソルの初期化処理
		m_Cursor->Init();
	}

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CMouse::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CMouse::Uninit(void)
{
	if (m_Dev != NULL)
	{//  アクセス権を開放
		m_Dev->Unacquire();
		m_Dev->Release();
		m_Dev = NULL;
	}

	//  カーソルの終了処理
	m_Cursor->Uninit();
}

//------------------------------------------------------------------------------
//	関数名:	void CMouse::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CMouse::Update(void)
{
	HWND hWnd = GetWnd();
	POINT tempPos;
	GetCursorPos(&tempPos);
	ScreenToClient(hWnd, &tempPos);

	CMode *pMode = CManager::GetMode();
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		CTitle *pTitle = ((CTitle*)CManager::GetMode());
		m_Mouse.x = (int)tempPos.x;
		m_Mouse.y = (int)tempPos.y;

		MouseUpdate();
	}
	else
	{
		CGame *pGame = ((CGame*)CManager::GetMode());
		CCamera_Data *pCameraData = CManager::GetCameraData();
/*
		D3DXVECTOR3 *pScopePos = CGame::GetScope()->GetPosition();*/

		m_Mouse.x = (int)(pScreenSize->x * 0.5f);
		m_Mouse.y = (int)(pScreenSize->y * 0.5f);

	/*	m_Mouse.x = (int)tempPos.x;
		m_Mouse.y = (int)tempPos.y;*/

		MouseUpdate();

		//  ワールド座標へ変換
		CalcScreenToXZ(
			&m_Pos,
			m_Mouse.x,
			m_Mouse.y,
			pScreenSize->x,
			pScreenSize->y,
			&pCameraData->mtxView,
			&pCameraData->mtxProjection
		);

		m_Cursor->Update();

		//  カーソルの設定
		m_Cursor->SetPosition(m_Pos);
	}
}

//------------------------------------------------------------------------------
//	関数名:	bool CMouse::GetPress
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	マウスのプレス状態を取得
//------------------------------------------------------------------------------
bool CMouse::GetPress(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	関数名:	bool CMouse::GetTrigger
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	マウスのトリガー状態を取得
//------------------------------------------------------------------------------
bool CMouse::GetTrigger(int nKey)
{
	return (m_MouseState.rgbButtons[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	関数名:	bool CKeyboard::GetRelease
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	マウスのリリース状態を取得
//------------------------------------------------------------------------------
bool CMouse::GetRelease(int nKey)
{
	return (m_StateTrigger[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	関数名:	bool CMouse::GetRepeat
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	マウスのリピート状態を取得
//------------------------------------------------------------------------------
bool CMouse::GetRepeat(int nKey)
{
	return (m_StateRepeat[nKey] & 0x80) ? true : false;
}

//------------------------------------------------------------------------------
//	関数名:	bool CMouse::GetRepeat
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	マウスのリピート状態を取得
//------------------------------------------------------------------------------
MSTATE *CMouse::GetMousePoint(void)
{
	return &m_Mouse;
}

//------------------------------------------------------------------------------
//	関数名:	bool CMouse::GetRepeat
//	引数:	int nKey
//	戻り値:	trueだと押している, falseだと押していない
//	説明:	マウスのリピート状態を取得
//------------------------------------------------------------------------------
DIMOUSESTATE *CMouse::GetMouseState(void)
{
	return &m_MouseState;
}

//------------------------------------------------------------------------------
//	関数名:	D3DXVECTOR3 *CMouse::GetWorldPos
//	引数:	なし
//	戻り値:	m_Pos
//	説明:	マウスのワールド座標を取得
//------------------------------------------------------------------------------
D3DXVECTOR3 *CMouse::GetWorldPos(void)
{
	return &m_Pos;
}

////------------------------------------------------------------------------------
////	関数名:	PRIMITIVE_TYPE *CMouse::GetPrimitiveType
////	引数:	なし
////	戻り値:	m_Type
////	説明:	選択したプリミティブタイプを取得
////------------------------------------------------------------------------------
//PRIMITIVE_TYPE *CMouse::GetPrimitiveType(void)
//{
//	return &m_Type;
//}

//------------------------------------------------------------------------------
//	関数名:	int	*CMouse::GetInBlockNum
//	引数:	なし
//	戻り値:	m_nInBlockNum
//	説明:	マウスのいるブロックを取得
//------------------------------------------------------------------------------
int	*CMouse::GetInBlockNum(void)
{
	return &m_nInBlockNum;
}

//------------------------------------------------------------------------------
//	関数名:	CCursor *CMouse::GetCursor
//	引数:	なし
//	戻り値:	m_Cursor
//	説明:	カーソルを取得
//------------------------------------------------------------------------------
CCursor *CMouse::GetCursor(void)
{
	return m_Cursor;
}

//------------------------------------------------------------------------------
//	関数名:	D3DXVECTOR3 *CMouse::CalcScreenToWorld
//	引数:	D3DXVECTOR3* pout,
//			int Sx,							//  スクリーンX座標
//			int Sy,							//  スクリーンY座標
//			float fZ,						//  射影空間でのZ値（0～1）
//			int Screen_w,
//			int Screen_h,
//			D3DXMATRIX* View,
//			D3DXMATRIX* Prj
//	戻り値:	m_Cursor
//	説明:	スクリーン座標をワールド座標に変換
//------------------------------------------------------------------------------
D3DXVECTOR3 *CMouse::CalcScreenToWorld(
	D3DXVECTOR3* pout,
	int Sx,							//  スクリーンX座標
	int Sy,							//  スクリーンY座標
	float fZ,						//  射影空間でのZ値（0～1）
	float Screen_w,
	float Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	//  各行列の逆行列を算出
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse(&InvView, NULL, View);
	D3DXMatrixInverse(&InvPrj, NULL, Prj);
	D3DXMatrixIdentity(&VP);
	VP._11 = Screen_w * 0.5f;
	VP._22 = -Screen_h * 0.5f;
	VP._41 = Screen_w * 0.5f;
	VP._42 = Screen_h * 0.5f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	//  逆変換
	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(
		pout,
		&D3DXVECTOR3((float)Sx, (float)Sy, fZ),
		&tmp
	);

	return pout;
}

//------------------------------------------------------------------------------
//	関数名:	D3DXVECTOR3 *CMouse::CalcScreenToXZ
//	引数:	D3DXVECTOR3* pout,
//			int Sx,
//			int Sy,
//			int Screen_w,
//			int Screen_h,
//			D3DXMATRIX* View,
//			D3DXMATRIX* Prj		
//	戻り値:	m_Cursor
//	説明:	XZ平面とスクリーン座標の交点算出関数
//------------------------------------------------------------------------------
D3DXVECTOR3 *CMouse::CalcScreenToXZ(
	D3DXVECTOR3* pout,
	int Sx,
	int Sy,
	float Screen_w,
	float Screen_h,
	D3DXMATRIX* View,
	D3DXMATRIX* Prj
)
{
	D3DXVECTOR3 nearpos;
	D3DXVECTOR3 farpos;
	D3DXVECTOR3 ray;
	CalcScreenToWorld(&nearpos, Sx, Sy, 0.0f, Screen_w, Screen_h, View, Prj);
	CalcScreenToWorld(&farpos, Sx, Sy, 1.0f, Screen_w, Screen_h, View, Prj);
	ray = farpos - nearpos;
	D3DXVec3Normalize(&ray, &ray);

	//  床との交差が起きている場合は交点を出力
	//  起きていない場合は遠くの壁との交点を出力
	if (ray.y <= 0) {
		//  床交点
		float Lray = D3DXVec3Dot(&ray, &D3DXVECTOR3(0, 1, 0));
		float LP0 = D3DXVec3Dot(&(-nearpos), &D3DXVECTOR3(0, 1, 0));
		*pout = nearpos + (LP0 / Lray)*ray;
	}
	else {
		*pout = farpos;
	}

	return pout;
}

void CMouse::MouseUpdate(void)
{
	if (m_Dev != NULL)
	{
		BYTE MouseStateOld[nKeyMax];

		//  前回のデータを保存
		memcpy(MouseStateOld, m_MouseState.rgbButtons, nKeyMax);

		if (SUCCEEDED(m_Dev->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
		{//  デバイスからデータを取得
		 //  画面外チェック
			if (m_Mouse.x < m_Mouse.moveRect.left)
			{
				m_Mouse.x = m_Mouse.moveRect.left;
			}
			if (m_Mouse.x > m_Mouse.moveRect.right)
			{
				m_Mouse.x = m_Mouse.moveRect.right;
			}
			if (m_Mouse.y < m_Mouse.moveRect.top)
			{
				m_Mouse.y = m_Mouse.moveRect.top;
			}
			if (m_Mouse.y > m_Mouse.moveRect.bottom)
			{
				m_Mouse.y = m_Mouse.moveRect.bottom;
			}

			for (int i = 0; i < nKeyMax; i++)
			{//  デバイスからデータを取得
				m_StateTrigger[i] = (MouseStateOld[i] ^ m_MouseState.rgbButtons[i]) & m_MouseState.rgbButtons[i];
				m_StateRelease[i] = (MouseStateOld[i] ^ m_MouseState.rgbButtons[i]) & ~m_MouseState.rgbButtons[i];
				m_StateRepeat[i] = m_StateTrigger[i];

				if (m_MouseState.rgbButtons[i])
				{
					m_StateRepeatCnt[i]++;
					if (m_StateRepeatCnt[i] >= nRepeatCnt)
					{
						m_StateRepeat[i] = m_MouseState.rgbButtons[i];
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
			//  マウスへのアクセス権を取得
			m_Dev->Acquire();
		}
	}
}