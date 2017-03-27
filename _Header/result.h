//------------------------------------------------------------------------------
//	タイトル：		リザルト処理のヘッダー
//	ファイル名：	result.h
//	作成者：		AT12A244 33 CHIN HIU
//	作成日：		2016/07/11
//------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "mode.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define	RESULT_TEXTURE_FILE	"./data/TEXTURE/result.png"	//  テクスチャファイル位置

//  前方宣言
class CUI;
class COpenAL;
class CNumUI;

typedef enum
{
	RANK_S = 0,
	RANK_A,
	RANK_B,
	RANK_C,
	RANK_D
}RANK;

// カメラクラス
class CResult : public CMode
{
private:
	CUI		*m_UI;
	CNumUI	*m_NumUI;
	int m_Time;
	int m_FrameCnt;

	int *m_ClearTime;
	int *m_KillsNum;
	int *m_PlayerDamage;

	int m_RankMarkID;

	float m_GamePoint;
	static	RANK m_Rank;

public:
	CResult();
	~CResult();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	static	RANK	*GetRank(void) { return &m_Rank; };
};

#endif