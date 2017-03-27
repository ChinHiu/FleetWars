//------------------------------------------------------------------------------
//	タイトル：		シーンのヘッダー
//	ファイル名：	scene.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/19
//------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
//  前方宣言
class CTitle;
class CTutorial;
class CGame;
class CResult;

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------
const int nPriorityMax = 6;			//  プライオリティ最大数

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  オブジェクトタイプ
typedef enum
{
	OBJTYPE_NONE = 0,
	OBJTYPE_PLAYER,
	OBJTYPE_ENEMY,
	OBJTYPE_EFFECT,
	OBJTYPE_MAX,
}OBJECT_TYPE;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------
class CScene	//  シーンクラス
{
public:
	CScene(int nPriority, OBJECT_TYPE Object_Type);
	~CScene();
	static	void	UpdateAll(void);
	static	void	DrawAll(void);
	static	void	UninitAll(void);

	virtual	void	Init(void) = 0;
	virtual	void	Uninit(void) = 0;
	virtual	void	Update(void) = 0;
	virtual	void	Draw(void) = 0;

	void			Delete(void);

protected:
	static			CScene *m_Top[nPriorityMax];			//  先頭
	static			CScene *m_Cur[nPriorityMax];			//  現在
	CScene			*m_Prev;								//  前のポインタ
	CScene			*m_Next;								//  次のポインタ
	int				m_Priority;								//  プライオリティ
	OBJECT_TYPE		m_ObjectType;							//  オブジェクトタイプ
	/*CTitle			*m_Title;
	CTutorial		*m_Tutorial;
	CGame			*m_Game;
	CResult			*m_Result;*/

};

#endif