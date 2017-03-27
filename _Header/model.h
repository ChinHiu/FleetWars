//------------------------------------------------------------------------------
//	�^�C�g���F		���f���̃w�b�_�[
//	�t�@�C�����F	model.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/12/13
//------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  ���f���N���X
class CModel
{
public:
	CModel();
	~CModel();

	static CModel *Create(MODEL_TYPE Model_Type, MODEL_PARTS Model_Parts, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//  �擾�֐�
	D3DXMATRIX	GetWorldMatrix(void);

	//  �Z�b�g�֐�
	void SetParent(CModel *model);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetBroken(bool bFlag);

private:
	CMatrix						m_Matrix;			//  �}�g���b�N�X
	CModel_Data					*m_ModelData;		//  ���f���f�[�^
	CModel						*m_Parent;			//  �e
	DWORD						m_SizeFVF;			//  ���_�t�H�[�}�b�g
	int							m_NumVertex;		//  ���_��

	D3DXVECTOR3					m_Pos;				//  �ʒu
	D3DXVECTOR3					m_Rot;				//  ����
	D3DXVECTOR3					m_Scl;				//  �g��k��

	MODEL_TYPE					m_ModelType;		//  ���f���^�C�v
	MODEL_PARTS					m_ModelParts;		//  ���f���p�[�c

	bool						m_bBroken;			//  �j�󂵂����ǂ���
};

#endif