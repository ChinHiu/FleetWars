//------------------------------------------------------------------------------
//	�^�C�g���F		�V�[���̊֐�
//	�t�@�C�����F	scene.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/19
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------
CScene *CScene::m_Top[nPriorityMax] = { NULL,NULL,NULL,NULL,NULL };	//  �擪�A�h���X��錾�Ə�����
CScene *CScene::m_Cur[nPriorityMax] = { NULL,NULL,NULL,NULL,NULL };	//  ���݃A�h���X��錾�Ə�����

//------------------------------------------------------------------------------
//	�֐���:	CScene::CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CScene::CScene(int nPriority, OBJECT_TYPE Object_Type)
{
	m_Priority = nPriority;
	m_ObjectType = Object_Type;

	if (m_Top[m_Priority] == NULL)
	{
		m_Top[m_Priority]	= this;		//  �擪�ɍ��̃A�h���X��ݒ�
		m_Cur[m_Priority]	= this;		//  ���݂ɍ��̃A�h���X��ݒ�
		m_Prev				= NULL;		//  �O�̃|�C���^��NULL��ݒ�
		m_Next				= NULL;		//  ���̃|�C���^��NULL��ݒ�
	}
	else
	{
		m_Cur[m_Priority]->m_Next	= this;					//  ���݂̎��̃|�C���^�ɍ��̃A�h���X��ݒ�
		m_Prev						= m_Cur[m_Priority];	//  �O�̃|�C���^�Ɍ��݂�ݒ�
		m_Cur[m_Priority]			= this;					//  ���݂ɍ��̃A�h���X��ݒ�
		m_Next						= NULL;					//  ���̃|�C���^��NULL��ݒ�
	}
}

//------------------------------------------------------------------------------
//	�֐���:	CScene::~CScene
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CScene::~CScene()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CScene::UpdateAll
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�v���W�F�N�g�I�[���X�V
//------------------------------------------------------------------------------
void CScene::UpdateAll(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		CScene *scene = m_Top[i];				//  �擪�A�h���X���w��
		CScene *next;							//  ���̃|�C���^���i�[���郏�[�N

		while (scene != NULL)
		{//  NULL�ł͂Ȃ���΁A�J��Ԃ�
			next = scene->m_Next;	//  ���̃|�C���^��ۑ�����
			scene->Update();			//  �X�V����
			scene = next;				//  ���̃|�C���^��scene�ɑ������
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CScene::DrawAll
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�v���W�F�N�g�I�[���`��
//------------------------------------------------------------------------------
void CScene::DrawAll(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		CScene *scene = m_Top[i];			//  �擪�A�h���X���w��

		while (scene != NULL)
		{//  NULL�ł͂Ȃ���΁A�J��Ԃ�
			scene->Draw();				//  �`�揈��
			scene = scene->m_Next;		//  ���̃|�C���^��scene�ɑ������
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CScene::UninitAll
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�v���W�F�N�g�I�[���I��
//------------------------------------------------------------------------------
void CScene::UninitAll(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		CScene *scene = m_Top[i];			//  �擪�A�h���X���w��
		CScene *next;						//  ���̃|�C���^���i�[���郏�[�N

		while (scene != NULL)
		{//  NULL�ł͂Ȃ���΁A�J��Ԃ�
			next = scene->m_Next;			//  ���̃|�C���^��ۑ�����
			scene->Uninit();				//  �X�V����
			delete scene;					//  �C���X�^���X�폜
			scene = next;					//  ���̃|�C���^��scene�ɑ������
		}

		m_Top[i] = NULL;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CScene::Delete
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���X�g�\���폜
//------------------------------------------------------------------------------
void CScene::Delete(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		if (this == m_Top[i])	m_Top[i]		= m_Next;	//  �擪�A�h���X�Ɏ��̃|�C���^���w��
		else					m_Prev->m_Next	= m_Next;	//  �O�̃A�h���X�̎��̃|�C���^�Ɏ��̃|�C���^���w��

		if (this == m_Cur[i])	m_Cur[i]		= m_Prev;	//  ���݃A�h���X�ɑO�̃|�C���^���w��
		else					m_Next->m_Prev	= m_Prev;	//  ���̃A�h���X�̑O�̃|�C���^�ɑO�̃|�C���^���w��
	}
	delete this;
}