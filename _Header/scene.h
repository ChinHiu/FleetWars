//------------------------------------------------------------------------------
//	�^�C�g���F		�V�[���̃w�b�_�[
//	�t�@�C�����F	scene.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/19
//------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
//  �O���錾
class CTitle;
class CTutorial;
class CGame;
class CResult;

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------
const int nPriorityMax = 6;			//  �v���C�I���e�B�ő吔

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  �I�u�W�F�N�g�^�C�v
typedef enum
{
	OBJTYPE_NONE = 0,
	OBJTYPE_PLAYER,
	OBJTYPE_ENEMY,
	OBJTYPE_EFFECT,
	OBJTYPE_MAX,
}OBJECT_TYPE;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------
class CScene	//  �V�[���N���X
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
	static			CScene *m_Top[nPriorityMax];			//  �擪
	static			CScene *m_Cur[nPriorityMax];			//  ����
	CScene			*m_Prev;								//  �O�̃|�C���^
	CScene			*m_Next;								//  ���̃|�C���^
	int				m_Priority;								//  �v���C�I���e�B
	OBJECT_TYPE		m_ObjectType;							//  �I�u�W�F�N�g�^�C�v
	/*CTitle			*m_Title;
	CTutorial		*m_Tutorial;
	CGame			*m_Game;
	CResult			*m_Result;*/

};

#endif