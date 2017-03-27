//------------------------------------------------------------------------------
//	タイトル：		UIのヘッダー
//	ファイル名：	UI.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/07
//------------------------------------------------------------------------------
#ifndef _UI_H_
#define _UI_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const int nUIMax = 50;		//  UI最大数

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  UIラベル
typedef enum
{
	UI_LABLE_NONE = -1,

	//  タイトルUI
	UI_TITLE,
	UI_START,
	UI_EXIT,

	UI_SCOPE,

	//  チュートリアルUI,
	UI_USERMAP_EX,
	UI_TUTORIAL_FRAME,
	UI_TUTORIAL_CONTROLLER,
	UI_TUTORIAL_SKIP,
	UI_TUTORIAL_DESCRIPTION0,
	UI_TUTORIAL_DESCRIPTION1,
	UI_TUTORIAL_DESCRIPTION2,
	UI_TUTORIAL_DESCRIPTION3,
	UI_TUTORIAL_DESCRIPTION4,
	UI_TUTORIAL_DESCRIPTION5,
	UI_TUTORIAL_DESCRIPTION6,
	UI_TUTORIAL_DESCRIPTION7,
	UI_TUTORIAL_DESCRIPTION8,
	UI_TUTORIAL_DESCRIPTION9,

	//  武器UI
	UI_WEAPON_GATLING,
	UI_WEAPON_MISSILE,
	//UI_WEAPON_JAMMING,
	UI_WEAPON_REPAIR,
	UI_HEAT,

	//  武器数字関係UI
	UI_INFINITY,
	UI_OVERHEAT,
	UI_POWER_MARK,
	UI_SPEED_MARK,
	UI_LIFE_FRAME,
	UI_LIFE,

	//  ゲーム結果
	UI_MISSION_COM,
	UI_MISSION_FAIL,
	UI_MISSION_START,

	//  リザルトUI
	UI_RESULT_FRAME,
	UI_RESULT_RANK,
	UI_RESULT_THANKS,
	UI_RESULT_FAIL,
	UI_LABLE_MAX
}UI_LABLE;

typedef enum
{
	UI_TYPE_NONE = -1,
	UI_WIDTH_SCROLL,
	UI_HEIGHT_SCROLL,
	UI_RESULT,
	UI_TYPE_MAX
}UI_TYPE;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  UIデータクラス
class CUI_Data : public CTex2D_Data
{
public:
	UI_LABLE	Lable;
	UI_TYPE		Type;
	float		TexRate;

	CUI_Data()
		: Lable(UI_LABLE_NONE)
		, Type(UI_TYPE_NONE)
	{}
};

//  UIクラス
class CUI : public CScene
{
public:
	CUI(int nPriority = 4, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CUI();
	static	CUI *Create();

	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	HRESULT	MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void	SetTexture(int nPatternAnim, int nPatternX, int nPatternY);
	void	SetVertex(void);

	//  セット関数
	int		Set(UI_LABLE lable, UI_TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col);
	void	SetColor(int nID, D3DXCOLOR col);
	void	SetFlag(int nID, bool bFlag);
	void	SetTexRate(int nID, float fTexRate);

private:
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;				//  頂点バッファへのポインタ
	CUI_Data				m_UI[nUIMax];
};

#endif

