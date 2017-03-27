//------------------------------------------------------------------------------
//	�^�C�g���F		�����nUI�̃w�b�_�[
//	�t�@�C�����F	numUI.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/01/08
//------------------------------------------------------------------------------
#ifndef _NUMUI_H_
#define _NUMUI_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
//  �O���錾
class CNumber;

//  �V�[���N���X
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