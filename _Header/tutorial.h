//------------------------------------------------------------------------------
//	タイトル：		チュートリアルのヘッダー
//	ファイル名：	tutorial.h
//	作成者：		AT12A244 33 CHIN HIU
//	作成日：		2017/02/11
//------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "mode.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CCamera;
class CLight;
class CUI;
class CPlayer;
class CNumUI;

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------
typedef enum
{
	TUTORIAL_0 = 0,
	TUTORIAL_1,
	TUTORIAL_2,
	TUTORIAL_3,
	TUTORIAL_4,
	TUTORIAL_5,
	TUTORIAL_6,
	TUTORIAL_7,
	TUTORIAL_8,
	TUTORIAL_9,
	TUTORIAL_MAX
}TUTORIAL_STATE;

// カメラクラス
class CTutorial : public CMode
{
private:
	CCamera				*m_Camera;			//  カメラ
	CLight				*m_Light;			//  ライト
	CUI					*m_UI;				//  UI
	CPlayer				*m_Player;			//  プレイヤー
	CNumUI				*m_NumUI;

	TUTORIAL_STATE		m_TutorialState;	//  チュートリアル状態
	int					m_TutorialPoint;	//  チュートリアルポイント
	int					m_TutorialUIid;		//  チュートリアルUIid

	CSelect_Data		m_SkipSelect;		//  スキップキー情報
	int					m_SkipUIid;			//  スキップUIid

	int					m_BGMSource;
	int					m_WaveSource;

	//D3DXCOLOR			m_SkipCol;
	//int					m_SkipFrameCnt;
	//int					m_SkipPattern;
	//bool				m_bSkipSelect;
	//int					m_SkipTime;

public:
	CTutorial();
	~CTutorial();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	KeyUpdate(void);
	void	AppTutorialPoint(int nNum)		{ m_TutorialPoint += nNum; };
	TUTORIAL_STATE *GetTutorialState(void)	{ return &m_TutorialState; };
};

#endif