//------------------------------------------------------------------------------
//	�^�C�g���F		���C�g�̊֐�
//	�t�@�C�����F	Light.cpp
//	�쐬�ҁF		AT12A244 33 CHIN HIU
//	�쐬���F		2015/10/21
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "light.h"
#include "title.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CLight::CLight()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CLight::CLight()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CLight::~CLight()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CLight::~CLight()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CLight::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CLight::Init(void)
{
	CMode *pMode = CManager::GetMode();

	//  �^�C�g�����[�h�̍X�V����
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		m_LightData[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_LightData[0].ambient = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		m_LightData[0].vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

		m_LightData[1].diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		m_LightData[1].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[1].vecDir = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);

		m_LightData[2].diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		m_LightData[2].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[2].vecDir = D3DXVECTOR3(0.0f, -1.0f, -2.0f);
		m_Adjust = 1;
	}
	else
	{
		m_LightData[0].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[0].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[0].vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

		m_LightData[1].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[1].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[1].vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

		m_LightData[2].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[2].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[2].vecDir = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

		m_LightData[3].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[3].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[3].vecDir = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
		m_Adjust = 0;
	}
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < nLightMax - m_Adjust; i++)
	{
		ZeroMemory(&m_Light[i], sizeof(D3DLIGHT9));

		//���s����
		m_Light[i].Type = D3DLIGHT_DIRECTIONAL;

		//�g�U��
		m_Light[i].Diffuse = m_LightData[i].diffuse;

		////���̕���
		//m_Light[nCntLight].vecDir = m_Light[nCntLight].vecDir;

		//���K��
		D3DXVec3Normalize((D3DXVECTOR3 *)&m_Light[i].Direction, &m_LightData[i].vecDir);

		//���C�g�̐ݒ�
		pDevice->SetLight(i, &m_Light[i]);

		//���C�g��L������
		pDevice->LightEnable(i, TRUE);
	}
}