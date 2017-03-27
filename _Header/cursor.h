//------------------------------------------------------------------------------
//	タイトル：		マウスのヘッダー
//	ファイル名：	keyboard.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/10
//------------------------------------------------------------------------------
#ifndef _CURSOR_H_
#define _CURSOR_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define	CURSOR_TEXTURE_FILE	"./data/TEXTURE/cursor000.png"				//  2Dカーソルのテクスチャファイルパス
#define CURSOR3D_TEXTURE_FILE "./data/TEXTURE/EffectAnim/Cursor3D.png"	//  3Dカーソルのテクスチャファイルパス

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  カーソルクラス
class CCursor
{
public:
	CCursor();
	~CCursor();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	//  取得関数
	D3DXVECTOR3 *GetPosition(void);

	//  セット関数
	void	SetVertex(void);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY);
	void	SetPosition(D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;		//  頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_TextureBuffer;	//  テクスチャへのポインタ
	D3DXVECTOR3				m_Pos;
	D3DXVECTOR3				m_Rot;
	D3DXVECTOR3				m_Scl;
	bool					m_Flag;
	D3DXVECTOR3				m_Size;
	//CAnimation			m_Anim;
	CMatrix					m_Matrix;
};

#endif