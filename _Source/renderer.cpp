//------------------------------------------------------------------------------
//	タイトル：		DirectX関連の関数
//	ファイル名：	renderer.cpp
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
#include "renderer.h"
#include "debugProc.h"
#include "camera.h"
#include "light.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include <typeinfo.h>
#include "title.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CRenderer::CRenderer
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CRenderer::CRenderer()
{
	m_D3D			= NULL;			//  Direct3Dオブジェクトへのポインタ
	m_D3DDevice		= NULL;			//  Direct3Dデバイスへのポインタ
#ifdef _DEBUG
	m_D3DXFont		= NULL;			//  フォントへのポインタ
#endif

	m_bFog = true;
}

//------------------------------------------------------------------------------
//	関数名:	CRenderer::~CRenderer
//	引数:	なし
//	戻り値:	なし
//	説明:	デストラクタ
//------------------------------------------------------------------------------
CRenderer::~CRenderer()
{
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CRenderer::Init
//	引数:	HINSTANCE hInstance, HWND hWnd, BOOL bWindow
//	戻り値:	E_FAILだと初期化失敗、S_OKだと初期化成功
//	説明:	初期化処理
//------------------------------------------------------------------------------
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	D3DXVECTOR2 *Screen = GetScreenSize();
	
	//  Direct3Dオブジェクトの生成
	m_D3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_D3D == NULL)
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));							//  ワークをゼロクリア

	//  デバイスのプレゼンテーションパラメータの設定
	if (bWindow == TRUE)
	{
		//  ウィンドウモード
		//  現在ディスプレイモードを取得
		if (FAILED(m_D3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			return E_FAIL;
		}
		d3dpp.BackBufferWidth = (UINT)Screen->x;				//  画面の幅を指定
		d3dpp.BackBufferHeight = (UINT)Screen->y;				//  画面の高さを指定
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				//  32Bit Color
		d3dpp.Windowed = TRUE;									//  ウィンドウモード
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				//  映像信号に同期してフリップする
		d3dpp.BackBufferCount = 1;								//  バックバッファの数
		d3dpp.EnableAutoDepthStencil = TRUE;					//  デプスバッファ(Zバッファ)とステンツルバッファを作成
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;			//  デプスバッファとして32ビットを使う
	}
	else
	{
		//  フルスクリーンモード
		d3dpp.BackBufferWidth = (UINT)Screen->x;				//  画面の幅を指定
		d3dpp.BackBufferHeight = (UINT)Screen->y;				//  画面の高さを指定
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				//  32Bit Color
		d3dpp.Windowed = FALSE;									//  ウィンドウモード
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;				//  映像信号に同期してフリップする
		d3dpp.BackBufferCount = 1;								//  バックバッファの数
		d3dpp.FullScreen_RefreshRateInHz = 75;					//  リフレッシュレート
		d3dpp.EnableAutoDepthStencil = TRUE;					//  デプスバッファ(Zバッファ)とステンツルバッファを作成
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;			//  デプスバッファとして32ビットを使う
	}


	//  デバイスの生成
	//  ディスプレイアダプタを表すためのデバイスを作成
	//  描画と頂点処理をハードウェアで行なう
	if (FAILED(
		m_D3D->CreateDevice
		(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_D3DDevice
		)))
	{
		//  上記の設定が失敗したら
		//  描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(
			m_D3D->CreateDevice
			(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_D3DDevice
			)))
		{
			//  上記の設定が失敗したら
			//  描画と頂点処理をCPUで行なう
			if (FAILED(
				m_D3D->CreateDevice
				(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_D3DDevice
				)))
			{
				//  初期化失敗
				return E_FAIL;
			}
		}
	}

	//テクスチャーステージパラメータのの設定
	//m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//m_D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_D3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
	m_D3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); //D3DTA_DIFFUSE

	 //  レンダーステートの設定
	m_D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					//  カリングを行う
	//m_D3DDevice -> SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				//  カリングを行わない
	//m_D3DDevice -> SetRenderState( D3DRS_ZENABLE, TRUE );						//  Zバッファを使用
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					//  αブレンドを行う
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);				//  αソースカラーの指定
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			//  αデスティネーションカラーの指定

	//サンプラーステートの設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		//テクスチャ( U値 )繰り返す設定
	m_D3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		//テクスチャ( V値 )繰り返す設定

	//  フォグの設定
	FLOAT StartPos = 0;																	//  開始位置
	FLOAT EndPos = 8000;																//  終了位置
	m_D3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.90f, 0.90f, 0.90f, 0.1f));	//  白色で不透明
	m_D3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos));					//  開始位置
	m_D3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));						//  終了位置
	m_D3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);						//  頂点モード
	m_D3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);						//  テーブルモード

#ifdef _DEBUG
	//  デバッグプロシージャ表示用フォントを設定
	D3DXCreateFont
	(
		m_D3DDevice,					//  デバイス
		30,								//  文字の高さ
		0,								//	文字幅
		FW_NORMAL,						//  フォントの太さ	
		NULL,							//  MIPMAPのレベル
		FALSE,							//  イタリックか？
		SHIFTJIS_CHARSET,				//  文字セット
		OUT_DEFAULT_PRECIS,				//  出力精度
		DRAFT_QUALITY,					//  出力品質							
		DEFAULT_PITCH | FF_DONTCARE,	//  フォントピッチとファミリ  //FIXED_PITCH=固定幅	VARIABLE_PITCH=可変幅							
		"Terminal",						//  フォント名				
		&m_D3DXFont						//  Direct3Dフォントへのポインタへのアドレス
	);
#endif
	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CRenderer::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CRenderer::Uninit(void)
{
	//  デバイスの開放
	SAFE_RELEASE(m_D3DDevice);

	//  オブジェクトの開放
	SAFE_RELEASE(m_D3D);

#ifdef _DEBUG
	//  デバッグプロシージャ表示用フォントを設定
	SAFE_RELEASE(m_D3DXFont);
#endif
}

//------------------------------------------------------------------------------
//	関数名:	void CRenderer::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CRenderer::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_F1)) m_bFillMode = m_bFillMode ? false : true;

	if (pKeyboard->GetTrigger(DIK_F2)) m_bFog = m_bFog ? false : true;
}

//------------------------------------------------------------------------------
//	関数名:	void CRenderer::Begin
//	引数:	なし
//	戻り値:	なし
//	説明:	描画開始
//------------------------------------------------------------------------------
void CRenderer::Begin(void)
{
	CMode *pMode = CManager::GetMode();

	//  バックバッファ＆Ｚバッファのクリア
	m_D3DDevice->Clear
	(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0
	);

	//  ゲームモードの更新処理
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		if (m_bFog)
		{
			m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);									//  フォグ：ON
		}
		else
		{
			m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		}
	}

#ifdef _DEBUG
	switch (m_bFillMode)
	{
	case true:
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	//  ワイヤフレーム4
		break;
	case false:
		m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//  塗りつぶす
		break;
	}
#endif

	//  Direct3Dによる描画の開始
	m_D3DDevice->BeginScene();
#ifdef _DEBUG
	//FPS情報の描画処理
	DrawFPS();
#endif
}

//------------------------------------------------------------------------------
//	関数名:	void CRenderer::End
//	引数:	なし
//	戻り値:	なし
//	説明:	描画終了
//------------------------------------------------------------------------------
void CRenderer::End(void)
{
	//  Direct3Dによる描画の終了
	m_D3DDevice->EndScene();

	//  フォグ無効化
	if (m_bFog)	m_D3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (m_bFillMode) m_D3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//  塗りつぶす

	//  バックバッファとフロントバッファの入れ替え
	m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}

//------------------------------------------------------------------------------
//	関数名:	LPDIRECT3DDEVICE9 CRenderer::GetDevice
//	引数:	なし
//	戻り値:	m_D3DDevice
//	説明:	デバイスを取得
//------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_D3DDevice;
}

#ifdef _DEBUG
//------------------------------------------------------------------------------
//	関数名:	void CRenderer::DrawFPS
//	引数:	なし
//	戻り値:	なし
//	説明:	FPS情報の描画処理
//------------------------------------------------------------------------------
void CRenderer::DrawFPS(void)
{
	D3DXVECTOR2 *pScreen = GetScreenSize();
	int *pCountFPS;

	pCountFPS = GetFPS();
	RECT rect = { 0, 0, (int)pScreen->x, (int)pScreen->y };

	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", *pCountFPS);

	//テキスト描画
	m_D3DXFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT | DT_BOTTOM, D3DCOLOR_RGBA(50, 255, 50, 255));
}
#endif