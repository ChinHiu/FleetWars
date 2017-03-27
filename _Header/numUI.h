//------------------------------------------------------------------------------
//	タイトル：		数字系UIのヘッダー
//	ファイル名：	numUI.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/08
//------------------------------------------------------------------------------
#ifndef _NUMUI_H_
#define _NUMUI_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
//  前方宣言
class CNumber;

//  シーンクラス
class CNumUI
{
private:
	CNumber *m_MissileNum;
	CNumber *m_MissileRepairTime;
	bool	*m_MissileFlag;
	CNumber *m_JammingNum;
	CNumber *m_JammingBulletTime;
	bool	*m_JammingFlag;
	CNumber *m_RepairNum;
	CNumber *m_Time;
	D3DXVECTOR2	m_SizeRate;
	CNumber *m_SpeedRate;
	CNumber *m_PowerRate;

public:
	CNumUI();
	~CNumUI();
	static CNumUI *Create(void);
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

#endif