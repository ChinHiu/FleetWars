//------------------------------------------------------------------------------
//	�^�C�g���F		�^�C�g���̊֐�
//	�t�@�C�����F	title.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/07/11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "camera.h"
#include "light.h"
#include "skybox.h"
#include "UI.h"
#include "meshField.h"
#include "player.h"
#include "openAL.h"
#include "water.h"
#include "missile.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
const D3DXVECTOR3 TitleCameraRot = D3DXVECTOR3(1.44f, -0.63f, 0.0f);

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CTitle::CTitle()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CTitle::CTitle()
{
	m_Camera = NULL;		//  �J����
	m_Light = NULL;			//	���C�g
	m_UI = NULL;
	m_Sea = NULL;
	m_KeyID = START_KEY;
	m_SelectID[START_KEY] =
	m_SelectID[EXIT_KEY] = 0;
}

//------------------------------------------------------------------------------
//	�֐���:	CTitle::~CTitle()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�f�X�g���N�^
//------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CTitle::Init
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CTitle::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();

	//	�C���X�^���X�ϐ��̐����Ə���������
	m_Camera = new CCamera;			//  �J����
	m_Light = new CLight;			//	���C�g

	//  �J�����̏�����
	m_Camera->Init(TitleCameraRot, true);

	//  ���C�g�̏�����
	m_Light->Init();

	//  �X�J�C�{�b�N�X�̐���
	CSkybox::Create(
		10000.0f						//  �K�́i���A�����A���s���j
	);

	//  ���̐���
	CMeshField::LoadMap(
		MESH_ISLAND,
		ISLAND_MAP_FILE,
		SEAMLESSMESHFIELD_TEXTURE_FILE,
		true,
		8.0f
	);

	//  �C�̐���
	CManager::SetSea(
		CMeshField::Create(
			MESH_SEA,
			SEAMLESSSEA_TEXTURE_FILE,
			D3DXVECTOR3(0.0f, -50.0f, 0.0f),
			D3DXVECTOR3(400.0f, 0.0f, 400.0f),
			15,
			15,
			true,
			10.0f
		)
	);

	//  �~�T�C���̐���
	CManager::SetMissile(
		CMissile::Create()
	);

	//  �v���C���[�̐���
	CManager::SetPlayer(
		CPlayer::Create(
			MODEL_GORSHKOV,
			D3DXVECTOR3(160.0f, 0.0f, 100.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f)
		)
	);

	//  ���G�t�F�N�g�̐���
	m_Water = CWater::Create();

	//  ��̐���
	m_Water->Set(
		D3DXVECTOR3(-930.0f, 270.0f, 2290.0f),
		D3DXVECTOR3(0.30f, 0.2f, 0.0f),
		D3DXVECTOR3(350.0f, 740.0f, 0.0f),
		EFFECT_WATER_FALL_000,
		true,
		true,
		false
	);

	m_Water->Set(
		D3DXVECTOR3(-1100.0f, 275.0f, 2395.0f),
		D3DXVECTOR3(0.30f, 0.75f, 0.0f),
		D3DXVECTOR3(420.0f, 810.0f, 0.0f),
		EFFECT_WATER_FALL_000,
		true,
		true,
		false
	);

	m_Water->Set(
		D3DXVECTOR3(-900.0f, 250.0f, 2280.0f),
		D3DXVECTOR3(0.30f, -0.1f, 0.0f),
		D3DXVECTOR3(325.0f, 750.0f, 0.0f),
		EFFECT_WATER_FALL_000,
		true,
		true,
		false
	);

	//  UI�̐���
	m_UI = CUI::Create();

	//  �^�C�g���}�[�N��ݒ�
	m_UI->Set(
		UI_TITLE,
		UI_TYPE_NONE,
		D3DXVECTOR2(40.0f * *pScreenRate + pScreenSize->x * 0.3f, 60.0f * *pScreenRate + pScreenSize->y * 0.25f),
		D3DXVECTOR2(pScreenSize->x * 0.6f, pScreenSize->x * 0.3f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//  �X�^�[�g�}�[�N��ݒ�
	m_SelectID[START_KEY] = m_UI->Set(
		UI_START,
		UI_TYPE_NONE,
		D3DXVECTOR2(5.0f * *pScreenRate + pScreenSize->x * 0.3f, 185.0f * *pScreenRate + pScreenSize->y * 0.5f),
		D3DXVECTOR2(pScreenSize->x * 0.14f, pScreenSize->y * 0.06f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);

	//  �I���}�[�N��ݒ�
	m_SelectID[EXIT_KEY] = m_UI->Set(
		UI_EXIT,
		UI_TYPE_NONE,
		D3DXVECTOR2(5.0f * *pScreenRate + pScreenSize->x * 0.3f, 210.0f * *pScreenRate + pScreenSize->y * 0.6f),
		D3DXVECTOR2(pScreenSize->x * 0.14f, pScreenSize->y * 0.06f),
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)
	);

	//  OpenAL�̏�����
	CManager::GetOpenAL()->Init(0, 0);

	CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_TITLE, 1.0f, 160.0f, 0.0f, 30.0f);
	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_TITLE_FALLS, 1.0f, 160.0f, 0.0f, 30.0f);
	CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WAVE, 1.0f, 160.0f, 0.0f, 30.0f);
}

//------------------------------------------------------------------------------
//	�֐���:	void CTitle::Uninit
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CTitle::Uninit(void)
{
	//  �V�[���I�[���I��
	CScene::UninitAll();

	CManager::GetOpenAL()->Uninit();

	//	�C���X�^���X�ϐ��̍폜
	delete m_Camera;
	delete m_Light;
}

//------------------------------------------------------------------------------
//	�֐���:	void CTitle::Update
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CTitle::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();

	//  �V�[���I�[���X�V
	CScene::UpdateAll();
	
	if (pKeyboard->GetTrigger(DIK_W))
	{
		m_KeyID--;

		if (m_KeyID < START_KEY)	m_KeyID = TITLE_KEY_MAX - 1;
	}
	else if (pKeyboard->GetTrigger(DIK_S))
	{
		m_KeyID++;

		if (m_KeyID > EXIT_KEY)	m_KeyID = START_KEY;
	}

	//  �I����������}�[�N�̐F��ݒ�
	for (int i = 0; i < TITLE_KEY_MAX; i++)
	{
		if (m_KeyID == i)	m_UI->SetColor(m_SelectID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		else				m_UI->SetColor(m_SelectID[i], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) * 0.5f);
	}

	switch (m_KeyID)
	{
	case START_KEY:
		if (pKeyboard->GetTrigger(DIK_RETURN))	CManager::GetFade()->Set(new CTutorial);
		break;
	case EXIT_KEY:
		if (pKeyboard->GetTrigger(DIK_RETURN))	exit(0);
		break;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CTitle::Draw
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CTitle::Draw(void)
{
	//  �J�����̐ݒ�
	m_Camera->SetCamera();

	//  �V�[���I�[���`��
	CScene::DrawAll();
}