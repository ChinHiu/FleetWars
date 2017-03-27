//------------------------------------------------------------------------------
//	タイトル：		メイン関数
//	ファイル名：	main.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/18
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include <stdio.h>
#include "manager.h"
#include "input.h"
#include "mouse.h"
#include <tchar.h>			// 汎用テキスト マッピング
#include "resource.h"

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
#define CLASS_NAME		"Win32API"		//  ウインドウのクラス名
#define WINDOW_NAME		"Fleet Wars"	//  ウインドウのキャプション名

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
LRESULT	CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT	Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void	Uninit(void);
void	Update(void);
void	Draw(void);
void	DisplayInit(HWND hDialog);

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------
int					g_nCountFPS;				//  FPSカウンタ
HWND				g_hWnd;
HWND				g_hDialog;
DISPLAY				g_Display;
HICON				g_hIcon;

//  キーボードのキーリスト
LPCTSTR Keyboard_Key_Name[] = {
	TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT("E"), TEXT("F"), TEXT("G"),
	TEXT("H"), TEXT("I"), TEXT("J"), TEXT("K"), TEXT("L"), TEXT("M"), TEXT("N"),
	TEXT("O"), TEXT("P"), TEXT("Q"), TEXT("R"), TEXT("S"), TEXT("T"),
	TEXT("U"), TEXT("V"), TEXT("W"), TEXT("X"), TEXT("Y"), TEXT("Z")
};

//  キーボードのキー
int Keyboard_Key[] = {
	DIK_A, DIK_B, DIK_C, DIK_D, DIK_E, DIK_F, DIK_G,
	DIK_H, DIK_I, DIK_J, DIK_K, DIK_L, DIK_M, DIK_N,
	DIK_O, DIK_P, DIK_Q, DIK_R, DIK_S, DIK_T,
	DIK_U, DIK_V, DIK_W, DIK_X, DIK_Y, DIK_Z,
};

//  マウスのキーリスト
LPCTSTR Mouse_Key_Name[] = {
	TEXT("LEFT"), TEXT("RIGHT"), TEXT("CENTER"),
};

//  マウスのキー
int Mouse_Key[] = {
	DIM_LEFT, DIM_RIGHT, DIM_CENTER
};

//------------------------------------------------------------------------------
//	関数名:	int WINAPI WinMain
//	引数:	HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpCmdLine, int nCmdShow
//	戻り値:	(int)msg.wParam
//	説明:	メイン関数
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG  msg;
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	g_hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_SHARED);

	//  ダイアログを呼び出す
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_OPTION), NULL, (DLGPROC)DialogProc);

	//  ウィンドウ枠の設定
	RECT rect = { 0, 0, (int)g_Display.ScreenSize.x, (int)g_Display.ScreenSize.y };

	//  画面割合を算出
	g_Display.ScreenRate = g_Display.ScreenSize.x / fScreenSizeWidthMax;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		g_hIcon,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL,
	};

	//  ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	if (g_Display.bWindow) {
		// ウインドウを作成
		g_hWnd = CreateWindow
		(
			CLASS_NAME,
			WINDOW_NAME,
			WS_POPUPWINDOW,//WS_OVERLAPPEDWINDOW,//WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
			0,//CW_USEDEFAULT,
			0,//CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			hInstance,
			NULL
		);
	}
	else
	{
		// ウインドウを作成
		g_hWnd = CreateWindow
		(
			CLASS_NAME,
			WINDOW_NAME,
			WS_POPUPWINDOW,//WS_OVERLAPPEDWINDOW,//WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
			0,
			0,
			rect.right - rect.left + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
			rect.bottom - rect.top + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			NULL,
			NULL,
			hInstance,
			NULL
		);
	}

	//  初期化処理
	if (FAILED(Init(hInstance, g_hWnd, g_Display.bWindow)))
	{
		return -1;
	}

	//  ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	
	//  フレームカウント初期化
	timeBeginPeriod(1);			//  分解能を設定
	dwFrameCount	=
	dwCurrentTime	= 0;
	dwExecLastTime	=
	dwFPSLastTime	= timeGetTime();

	//  メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{//  PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{//  メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	//  0.5秒ごとに実行
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//  更新処理
				Update();

				//  描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	//  ウィンドウクラスの登録を解除
	UnregisterClass("Window", wcex.hInstance);

	//  終了処理
	Uninit();

	//  分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//------------------------------------------------------------------------------
//	関数名:	LRESULT CALLBACK WndProc
//	引数:	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
//	戻り値:	DefWindowProc(hWnd, uMsg, wParam, lParam)
//	説明:	プロシージャ
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか。", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);			//  ウィンドウを破棄するよう指示する
		}
		return 0;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:						//  [ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか。", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);		//  ウィンドウを破棄するよう指示する
			}
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//*------------------------------------------------------------------------------
//	関数名:	HRESULT Init
//	引数:	HINSTANCE hInstance, HWND hWnd, BOOL bWindow
//	戻り値:	E_FAILだと初期化失敗、S_OKだと初期化成功
//	説明:	初期化処理
//-------------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CManager::Init(hInstance, hWnd, bWindow);
	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void Uninit(void)
{
	CManager::Uninit();
}

//------------------------------------------------------------------------------
//	関数名:	void Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void Update(void)
{
	CManager::Update();
}

//------------------------------------------------------------------------------
//	関数名:	void Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void Draw(void)
{
	CManager::Draw();
}

//-------------------------------------------------------------------------------
//	関数名:	LRESULT CALLBACK DialogProc
//	引数:	HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam
//	戻り値:	TRUE か FALSE
//	説明:	プロシージャ
//-------------------------------------------------------------------------------
LRESULT CALLBACK DialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SendMessage(hDialog, WM_SETICON, ICON_SMALL, (LPARAM)g_hIcon);
		DisplayInit(hDialog);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RESOLUTION1:
			g_Display.ScreenSize = D3DXVECTOR2(1280, 720);
			break;
		case IDC_RESOLUTION2:
			g_Display.ScreenSize = D3DXVECTOR2(1366, 768);
			break;
		case IDC_RESOLUTION3:
			g_Display.ScreenSize = D3DXVECTOR2(1600, 900);
			break;
		case IDC_RESOLUTION4:
			g_Display.ScreenSize = D3DXVECTOR2(1920, 1080);
			break;
		case IDC_WINDOW_MODE:
			g_Display.bWindow = g_Display.bWindow ? false : true;
			break;
		case IDC_EASY:
			g_Display.iDifficulty = 0;
			break;
		case IDC_HARD:
			g_Display.iDifficulty = 1;
			break;
		case IDC_DEFAULT:
			DisplayInit(hDialog);
			return TRUE;
		case IDOK:
			EndDialog(hDialog, IDOK);
			break;;
		case IDCANCEL:
			EndDialog(hDialog, IDCANCEL);
			exit(0);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

//-------------------------------------------------------------------------------
//	関数名:	void DisplayInit
//	引数:	HWND hDialog
//	戻り値:	なし
//	説明:	ディスプレイデータの初期化処理
//-------------------------------------------------------------------------------
void DisplayInit(HWND hDialog)
{
	//  ディスプレイクラスの初期化
	g_Display.bWindow = false;
	g_Display.ScreenSize = D3DXVECTOR2(1920, 1080);
	g_Display.iDifficulty = 0;

	//  解像度のデフォルトを設定
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION1), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION2), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION3), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION4), BM_SETCHECK, BST_CHECKED, 0);

	//  難易度のデフォルトを設定
	SendMessage(GetDlgItem(hDialog, IDC_EASY), BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_HARD), BM_SETCHECK, BST_UNCHECKED, 0);

	//  ウィンドウモードのデフォルトを設定
	SendMessage(GetDlgItem(hDialog, IDC_WINDOW_MODE), BM_SETCHECK, BST_UNCHECKED, 0);

	//// コントローラモードのデフォルトを設定
	//SendMessage(GetDlgItem(hDialog, IDC_DIRECTINPUT), BM_SETCHECK, BST_CHECKED, 0);
	//SendMessage(GetDlgItem(hDialog, IDC_XINPUT), BM_SETCHECK, BST_UNCHECKED, 0);
}

//------------------------------------------------------------------------------
//	関数名:	HWND GetWnd
//	引数:	なし
//	戻り値:	g_hWnd
//	説明:	ウィンドウハンドルを取得
//------------------------------------------------------------------------------
HWND GetWnd(void)
{
	return g_hWnd;
}

//------------------------------------------------------------------------------
//	関数名:	int *GetFPS
//	引数:	なし
//	戻り値:	g_nCountFPS
//	説明:	FPSを取得
//------------------------------------------------------------------------------
int *GetFPS(void)
{
	return &g_nCountFPS;
}

//------------------------------------------------------------------------------
//	関数名:	D3DXVECTOR2 *GetScreenSize(void)
//	引数:	なし
//	戻り値:	&g_Display.Screen
//	説明:	ディスプレイの画面サイズを取得
//------------------------------------------------------------------------------
D3DXVECTOR2 *GetScreenSize(void)
{
	return &g_Display.ScreenSize;
}

float *GetScreenRate(void)
{
	return &g_Display.ScreenRate;
}
