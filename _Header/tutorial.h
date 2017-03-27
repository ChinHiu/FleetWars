//------------------------------------------------------------------------------
//	�^�C�g���F		�`���[�g���A���̃w�b�_�[
//	�t�@�C�����F	tutorial.h
//	�쐬�ҁF		AT12A244 33 CHIN HIU
//	�쐬���F		2017/02/11
//------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "mode.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CCamera;
class CLight;
class CUI;
class CPlayer;
class CNumUI;

//------------------------------------------------------------------------------
//	enum��`
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

// �J�����N���X
class CTutorial : public CMode
{
private:
	CCamera				*m_Camera;			//  �J����
	CLight				*m_Light;			//  ���C�g
	CUI					*m_UI;				//  UI
	CPlayer				*m_Player;			//  �v���C���[
	CNumUI				*m_NumUI;

	TUTORIAL_STATE		m_TutorialState;	//  �`���[�g���A�����
	int					m_TutorialPoint;	//  �`���[�g���A���|�C���g
	int					m_TutorialUIid;		//  �`���[�g���A��UIid

	CSelect_Data		m_SkipSelect;		//  �X�L�b�v�L�[���
	int					m_SkipUIid;			//  �X�L�b�vUIid

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