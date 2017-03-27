//------------------------------------------------------------------------------
//	タイトル：		DirectX関連のヘッダー
//	ファイル名：	renderer.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/18
//------------------------------------------------------------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "d3dx9.h"
#define  DIRECTINPUT_VERSION ( 0x0800 )
#include "dinput.h"							//  DirectInput関連のヘッダー

//------------------------------------------------------------------------------
//	ライブラリのリンク
//------------------------------------------------------------------------------
#pragma comment ( lib, "d3d9.lib" )			//  描画処理に必要
#pragma comment ( lib, "d3dx9.lib" )		//  上記の拡張ライブラリ
#pragma comment ( lib, "dxguid.lib" )		//  DirectXコンポーネント使用に必要
#pragma comment ( lib, "dinput8.lib" )		//  入力処理に必要
#pragma warning ( disable: 4996 )			//  sprintfのウォーミング

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define	FVF_VERTEX_2D	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )				//  頂点座標(3d) | 頂点カラー | テクスチャ座標
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//  頂点座標(3d) | 法線 | 頂点カラー | テクスチャ座標

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CDebugProc;

//------------------------------------------------------------------------------
//	構造体定義
//------------------------------------------------------------------------------

//  2D用構造体
typedef struct
{
	D3DXVECTOR3 pos;	//  頂点座標
	float		rhw;	//  テクスチャのパースペクティブコレクト用
	D3DCOLOR	col;	//  頂点カラー
	D3DXVECTOR2 tex;	//  テクスチャ座標
}VERTEX_2D;

//  3D用構造体	
typedef struct
{
	D3DXVECTOR3	pos;	//  頂点座標
	D3DXVECTOR3	nor;	//  法線ベクトル( 面の向きに設定 )
	D3DCOLOR	col;	//  頂点カラー
	D3DXVECTOR2	tex;	//  テクスチャ座標
}VERTEX_3D;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  レンダラクラス
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT					Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void					Uninit(void);
	void					Update(void);
	void					Begin(void);
	void					End(void);
	LPDIRECT3DDEVICE9		GetDevice(void);
#ifdef _DEBUG
	void					DrawFPS(void);
#endif

private:
	LPDIRECT3D9				m_D3D;				//  Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9		m_D3DDevice;		//  Direct3Dデバイスへのポインタ
	bool					m_bFog;
	bool					m_bFillMode;		//  ワイヤーフレームモードのフラグ
#ifdef _DEBUG
	LPD3DXFONT				m_D3DXFont;			//  フォントへのポインタ
	float					m_Alpha;			//  α値
#endif
};

#endif