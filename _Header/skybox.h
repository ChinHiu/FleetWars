//------------------------------------------------------------------------------
//	タイトル：		スカイボックスのヘッダー
//	ファイル名：	skybox.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/06/20
//------------------------------------------------------------------------------
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  スカイテクスチャタイプ
typedef enum
{
	UP_TEXTURE = 0,
	LEFT_TEXTURE,
	FRONE_TEXTURE,
	RIGHT_TEXTURE,
	BACK_TEXTURE,
	DOWN_TEXTURE,
	SKY_TEXTURE_MAX
}SKY_TEXTURE;

//  スカイタイプ
typedef enum
{
	TROPICALSUNNYDAY = 0,
	SKY_TYPE_MAX
}SKY_TYPE;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  スカイボックスクラス
class CSkybox : public CScene
{
public:
	CSkybox(int nPriority = 0, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CSkybox();

	static	CSkybox *Create(float fScale);
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	HRESULT MakeIndex(LPDIRECT3DDEVICE9 pDevice);

	//  セット関数
	void	SetPos(const D3DXVECTOR3 pos);

private:
	CMatrix					m_Matrix;									//  マトリックス
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;								//  頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_IndexBuffer;								//  インデックスバッファへのポインター
	float					m_Scale;									//  倍率
	D3DXVECTOR3				m_Pos;										//  位置
	D3DXVECTOR3				m_Rot;										//  回転
	D3DXVECTOR3				m_Scl;										//  拡大縮小

};
#endif