//------------------------------------------------------------------------------
//	タイトル：		フェード処理のヘッダー
//	ファイル名：	fade.h
//	作成者：		AT12A244 33 CHIN HIU
//	作成日：		2016/07/11
//------------------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define FADE_TEXTURE_FILE "./data/TEXTURE/UI/Fade.png"
//  前方宣言
//フェードの状態
typedef enum
{
	FADE_NONE = 0,	//何もしない
	FADE_IN,		//フェードイン
	FADE_OUT,		//フェードアウト
	FADE_MAX
}FADE;

// カメラクラス
class CFade
{
private:
	LPDIRECT3DTEXTURE9 m_TextureBuffer;				//  テクスチャバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;			//  頂点バッファへのポインタ
	D3DXCOLOR m_Col;								//  フェード色
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Size;
	FADE m_Fade;									//  フェードの状態
	bool m_bFlag;									//  フラグ
	CMode *m_NextMode;								//  次のモード

public:
	CFade();
	~CFade();
	static CFade *Create(CMode *NextMode);
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	Set(CMode *NextMode);
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
};
#endif