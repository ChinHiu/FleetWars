//------------------------------------------------------------------------------
//	�^�C�g���F		���U���g�����̃w�b�_�[
//	�t�@�C�����F	result.h
//	�쐬�ҁF		AT12A244 33 CHIN HIU
//	�쐬���F		2016/07/11
//------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "mode.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define	RESULT_TEXTURE_FILE	"./data/TEXTURE/result.png"	//  �e�N�X�`���t�@�C���ʒu

//  �O���錾
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

// �J�����N���X
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