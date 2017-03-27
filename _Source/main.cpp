//------------------------------------------------------------------------------
//	�^�C�g���F		���C���֐�
//	�t�@�C�����F	main.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/18
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include <stdio.h>
#include "manager.h"
#include "input.h"
#include "mouse.h"
#include <tchar.h>			// �ėp�e�L�X�g �}�b�s���O
#include "resource.h"

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
#define CLASS_NAME		"Win32API"		//  �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Fleet Wars"	//  �E�C���h�E�̃L���v�V������

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
LRESULT	CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT	Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void	Uninit(void);
void	Update(void);
void	Draw(void);
void	DisplayInit(HWND hDialog);

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------
int					g_nCountFPS;				//  FPS�J�E���^
HWND				g_hWnd;
HWND				g_hDialog;
DISPLAY				g_Display;
HICON				g_hIcon;

//  �L�[�{�[�h�̃L�[���X�g
LPCTSTR Keyboard_Key_Name[] = {
	TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT("E"), TEXT("F"), TEXT("G"),
	TEXT("H"), TEXT("I"), TEXT("J"), TEXT("K"), TEXT("L"), TEXT("M"), TEXT("N"),
	TEXT("O"), TEXT("P"), TEXT("Q"), TEXT("R"), TEXT("S"), TEXT("T"),
	TEXT("U"), TEXT("V"), TEXT("W"), TEXT("X"), TEXT("Y"), TEXT("Z")
};

//  �L�[�{�[�h�̃L�[
int Keyboard_Key[] = {
	DIK_A, DIK_B, DIK_C, DIK_D, DIK_E, DIK_F, DIK_G,
	DIK_H, DIK_I, DIK_J, DIK_K, DIK_L, DIK_M, DIK_N,
	DIK_O, DIK_P, DIK_Q, DIK_R, DIK_S, DIK_T,
	DIK_U, DIK_V, DIK_W, DIK_X, DIK_Y, DIK_Z,
};

//  �}�E�X�̃L�[���X�g
LPCTSTR Mouse_Key_Name[] = {
	TEXT("LEFT"), TEXT("RIGHT"), TEXT("CENTER"),
};

//  �}�E�X�̃L�[
int Mouse_Key[] = {
	DIM_LEFT, DIM_RIGHT, DIM_CENTER
};

//------------------------------------------------------------------------------
//	�֐���:	int WINAPI WinMain
//	����:	HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpCmdLine, int nCmdShow
//	�߂�l:	(int)msg.wParam
//	����:	���C���֐�
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG  msg;
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	g_hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_SHARED);

	//  �_�C�A���O���Ăяo��
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_OPTION), NULL, (DLGPROC)DialogProc);

	//  �E�B���h�E�g�̐ݒ�
	RECT rect = { 0, 0, (int)g_Display.ScreenSize.x, (int)g_Display.ScreenSize.y };

	//  ��ʊ������Z�o
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

	//  �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	if (g_Display.bWindow) {
		// �E�C���h�E���쐬
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
		// �E�C���h�E���쐬
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

	//  ����������
	if (FAILED(Init(hInstance, g_hWnd, g_Display.bWindow)))
	{
		return -1;
	}

	//  �E�C���h�E�̕\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	
	//  �t���[���J�E���g������
	timeBeginPeriod(1);			//  ����\��ݒ�
	dwFrameCount	=
	dwCurrentTime	= 0;
	dwExecLastTime	=
	dwFPSLastTime	= timeGetTime();

	//  ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{//  PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{//  ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	//  0.5�b���ƂɎ��s
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//  �X�V����
				Update();

				//  �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	//  �E�B���h�E�N���X�̓o�^������
	UnregisterClass("Window", wcex.hInstance);

	//  �I������
	Uninit();

	//  ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//------------------------------------------------------------------------------
//	�֐���:	LRESULT CALLBACK WndProc
//	����:	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
//	�߂�l:	DefWindowProc(hWnd, uMsg, wParam, lParam)
//	����:	�v���V�[�W��
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
		nID = MessageBox(hWnd, "�I�����܂����B", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);			//  �E�B���h�E��j������悤�w������
		}
		return 0;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:						//  [ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����B", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);		//  �E�B���h�E��j������悤�w������
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
//	�֐���:	HRESULT Init
//	����:	HINSTANCE hInstance, HWND hWnd, BOOL bWindow
//	�߂�l:	E_FAIL���Ə��������s�AS_OK���Ə���������
//	����:	����������
//-------------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CManager::Init(hInstance, hWnd, bWindow);
	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void Uninit(void)
{
	CManager::Uninit();
}

//------------------------------------------------------------------------------
//	�֐���:	void Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void Update(void)
{
	CManager::Update();
}

//------------------------------------------------------------------------------
//	�֐���:	void Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void Draw(void)
{
	CManager::Draw();
}

//-------------------------------------------------------------------------------
//	�֐���:	LRESULT CALLBACK DialogProc
//	����:	HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam
//	�߂�l:	TRUE �� FALSE
//	����:	�v���V�[�W��
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
//	�֐���:	void DisplayInit
//	����:	HWND hDialog
//	�߂�l:	�Ȃ�
//	����:	�f�B�X�v���C�f�[�^�̏���������
//-------------------------------------------------------------------------------
void DisplayInit(HWND hDialog)
{
	//  �f�B�X�v���C�N���X�̏�����
	g_Display.bWindow = false;
	g_Display.ScreenSize = D3DXVECTOR2(1920, 1080);
	g_Display.iDifficulty = 0;

	//  �𑜓x�̃f�t�H���g��ݒ�
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION1), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION2), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION3), BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_RESOLUTION4), BM_SETCHECK, BST_CHECKED, 0);

	//  ��Փx�̃f�t�H���g��ݒ�
	SendMessage(GetDlgItem(hDialog, IDC_EASY), BM_SETCHECK, BST_CHECKED, 0);
	SendMessage(GetDlgItem(hDialog, IDC_HARD), BM_SETCHECK, BST_UNCHECKED, 0);

	//  �E�B���h�E���[�h�̃f�t�H���g��ݒ�
	SendMessage(GetDlgItem(hDialog, IDC_WINDOW_MODE), BM_SETCHECK, BST_UNCHECKED, 0);

	//// �R���g���[�����[�h�̃f�t�H���g��ݒ�
	//SendMessage(GetDlgItem(hDialog, IDC_DIRECTINPUT), BM_SETCHECK, BST_CHECKED, 0);
	//SendMessage(GetDlgItem(hDialog, IDC_XINPUT), BM_SETCHECK, BST_UNCHECKED, 0);
}

//------------------------------------------------------------------------------
//	�֐���:	HWND GetWnd
//	����:	�Ȃ�
//	�߂�l:	g_hWnd
//	����:	�E�B���h�E�n���h�����擾
//------------------------------------------------------------------------------
HWND GetWnd(void)
{
	return g_hWnd;
}

//------------------------------------------------------------------------------
//	�֐���:	int *GetFPS
//	����:	�Ȃ�
//	�߂�l:	g_nCountFPS
//	����:	FPS���擾
//------------------------------------------------------------------------------
int *GetFPS(void)
{
	return &g_nCountFPS;
}

//------------------------------------------------------------------------------
//	�֐���:	D3DXVECTOR2 *GetScreenSize(void)
//	����:	�Ȃ�
//	�߂�l:	&g_Display.Screen
//	����:	�f�B�X�v���C�̉�ʃT�C�Y���擾
//------------------------------------------------------------------------------
D3DXVECTOR2 *GetScreenSize(void)
{
	return &g_Display.ScreenSize;
}

float *GetScreenRate(void)
{
	return &g_Display.ScreenRate;
}
