//------------------------------------------------------------------------------
//	�^�C�g���F		�`���[�g���A���̊֐�
//	�t�@�C�����F	tutorial.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2017/02/11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "tutorial.h"
#include "game.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "meshField.h"
#include "skybox.h"
#include "UI.h"
#include "openAL.h"
#include "fade.h"
#include "bullet.h"
#include "water.h"
#include "bullet.h"
#include "missile.h"
#include "userMap.h"
#include "sprayBehide.h"
#include "numUI.h"

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------
const D3DXVECTOR3 TutorialCameraRot = D3DXVECTOR3(D3DX_PI * 0.43f, D3DX_PI, 0.0f);
#define TUTORIAL_SECOND (60)

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CTutorial::CTutorial()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CTutorial::CTutorial()
{
	m_Camera = NULL;
	m_Light = NULL;
	m_UI = NULL;
	m_TutorialState = TUTORIAL_0;
	m_TutorialPoint = 0;
	m_SkipSelect.Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_SkipSelect.nChangeTime = 60;
}

//------------------------------------------------------------------------------
//	�֐���:	CTutorial::~CTutorial()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CTutorial::~CTutorial()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CTutorial::Init
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CTutorial::Init(void)
{
	//  ��ʃT�C�Y���擾
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  ��ʊ������擾
	float *pScreenRate = GetScreenRate();

	//	�C���X�^���X�ϐ��̐����Ə���������
	m_Camera = new CCamera;			//  �J����
	m_Light = new CLight;			//	���C�g

	//  �J�����̏�����
	m_Camera->Init(TutorialCameraRot, false);

	//  �J�����f�[�^�����}�l�[�W���[�ɓn��
	CManager::SetCameraData(m_Camera->GetCameraData());

	//  ���C�g�̏�����
	m_Light->Init();

	//  �X�J�C�{�b�N�X�̐���
	CSkybox::Create(
		10000.0f						//  �K�́i���A�����A���s���j
	);

	//  �C�̐���
	CManager::SetSea(
		CMeshField::Create(
			MESH_SEA,
			SEAMLESSSEA_TEXTURE_FILE,
			D3DXVECTOR3(0.0f, -15.0f, 0.0f),
			D3DXVECTOR3(400.0f, 0.0f, 400.0f),
			80,
			80,
			true,
			10.0f
		)
	);

	//  ���̐���
	CManager::SetWater(
		CWater::Create()
	);

	//  UI�̐���
	CManager::SetUI(
		m_UI = CUI::Create()
	);

	//  �e�̐���
	CManager::SetBullet(
		CBullet::Create()
	);

	//  �~�T�C���̐���
	CManager::SetMissile(
		CMissile::Create()
	);

	//  ���򖗁i���j�̐���
	CManager::SetSprayBehide(
		CSprayBehide::Create()
	);

	//  �v���C���[�̐���
	CManager::SetPlayer(
		m_Player = CPlayer::Create(
			MODEL_GORSHKOV,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f)
		)
	);

	//  �����nUI�̐���
	m_NumUI = CNumUI::Create();

	//  ���[�U�[�}�b�v�̐���
	CManager::SetUserMap(
		CUserMap::Create()
	);

	//  OpenAL�̏�����
	CManager::GetOpenAL()->Init(0, 0);

	m_BGMSource = CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_TUTORIAL, 1.0f, 0.0f, 0.0f, 0.0f);
	m_WaveSource = CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WAVE, 1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
//	�֐���:	void CTutorial::Uninit
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CTutorial::Uninit(void)
{
	m_Camera->Uninit();
	//  �V�[���I�[���I��
	CScene::UninitAll();

	CManager::GetOpenAL()->Uninit();

	m_NumUI->Uninit();

	//	�C���X�^���X�ϐ��̍폜
	delete m_Camera;
	delete m_Light;

	m_UI = NULL;
}

//------------------------------------------------------------------------------
//	�֐���:	void CTutorial::Update
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CTutorial::Update(void)
{
	CKeyboard *pKeyboard = CManager::GetInput()->GetKeyboard();
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float *pScreenRate = GetScreenRate();

	//  �J�����̍X�V
	m_Camera->Update();

	//  �V�[���I�[���X�V
	CScene::UpdateAll();

	m_NumUI->Update();

	CManager::GetOpenAL()->SetListenervalues(m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_BGMSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_WaveSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);

	switch (m_TutorialState)
	{
	case TUTORIAL_0:
		if (m_TutorialPoint == 0)
		{
			m_UI->Set(
				UI_TUTORIAL_CONTROLLER,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x * 0.5f, 212.11f * *pScreenRate),
				D3DXVECTOR2(830.34f * *pScreenRate, 374.22f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_UI->Set(
				UI_USERMAP_EX,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 200.0f * *pScreenRate, pScreenSize->y - 445.0f * *pScreenRate),
				D3DXVECTOR2(227.0f * *pScreenRate, 151.0f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_UI->Set(
				UI_TUTORIAL_FRAME,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_SkipUIid = m_UI->Set(
				UI_TUTORIAL_SKIP,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y - 100.0f * *pScreenRate),
				D3DXVECTOR2(201.1f * *pScreenRate, 69.3f * *pScreenRate),
				m_SkipSelect.Col
			);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION0,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
		}

		m_TutorialPoint++;

		if (m_TutorialPoint >= TUTORIAL_SECOND * 4)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION1,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_TutorialState = TUTORIAL_1;
		}
		break;
	case TUTORIAL_1:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 8)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION2,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);

			m_TutorialState = TUTORIAL_2;
		}
		break;
	case TUTORIAL_2:
		m_Player->SetMoveFlag(true);
		if (*m_Player->GetPowerNum() >= 100)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION3,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_3;
		}
		break;
	case TUTORIAL_3:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 12)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION4,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_4;
		}
		break;
	case TUTORIAL_4:
		m_Player->SetRotFlag(true);
		if (m_TutorialPoint >= TUTORIAL_SECOND * 14)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION5,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_5;
		}
		break;
	case TUTORIAL_5:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 18)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION6,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_6;
		}
		break;
	case TUTORIAL_6:
		m_Player->SetWeaponFlag(true);
		if (*m_Player->GetWeponType() == WEAPON_BULLET)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION7,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_7;
		}
		break;
	case TUTORIAL_7:
		if (m_TutorialPoint >= TUTORIAL_SECOND * 20)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION8,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_8;
		}
		break;
	case TUTORIAL_8:
		m_TutorialPoint++;
		if (m_TutorialPoint >= TUTORIAL_SECOND * 24)
		{
			m_UI->SetFlag(m_TutorialUIid, false);

			m_TutorialUIid = m_UI->Set(
				UI_TUTORIAL_DESCRIPTION9,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x - 295.0f * *pScreenRate, 150.0f * *pScreenRate),
				D3DXVECTOR2(506.4f * *pScreenRate, 219.6f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_TutorialState = TUTORIAL_9;
		}
		break;
	case TUTORIAL_9:
		break;
	}

	if (m_TutorialState == TUTORIAL_9)
	{
		m_UI->SetFlag(m_SkipUIid, false);

		if (pKeyboard->GetTrigger(DIK_RETURN) /*|| pJoysticks->GetTrigger(DIJ_BUTTON_A)*/)
		{
			CManager::GetFade()->Set(new CGame);
		}
	}
	else
	{
		if (m_SkipSelect.bSelect)
		{
			m_SkipSelect.nChangeTime--;
			m_SkipSelect.nFrameCnt++;
			if (m_SkipSelect.nFrameCnt >= 5)
			{
				m_SkipSelect.nFrameCnt = 0;
				m_SkipSelect.nPattern++;

				if (m_SkipSelect.nPattern >= 2)
				{
					m_SkipSelect.nPattern = 0;
				}

				switch (m_SkipSelect.nPattern)
				{
				case 0:
					m_SkipSelect.Col.a = 0.0f;
					break;
				case 1:
					m_SkipSelect.Col.a = 1.0f;
					break;
				}
			}

			if (m_SkipSelect.nChangeTime < 0)
			{
				m_SkipSelect.Col.a = 0.0f;
				CManager::GetFade()->Set(new CGame);
			}
		}
		else
		{
			if (pKeyboard->GetPress(DIK_RETURN) /*|| pJoysticks->GetPress(DIJ_BUTTON_A)*/)
			{
				m_SkipSelect.Col.a += 2.0f / (float)(TUTORIAL_SECOND * 2);
			}
			else
			{
				if (m_SkipSelect.Col.a < 1.0f)
				{
					m_SkipSelect.Col.a -= 1.0f / (float)(TUTORIAL_SECOND * 2);
				}
			}

			if (m_SkipSelect.Col.a > 1.0f)
			{
				m_SkipSelect.Col.a = 1.0f;
				m_SkipSelect.bSelect = true;
			}
			else if (m_SkipSelect.Col.a < 0.0f)
			{
				m_SkipSelect.Col.a = 0.0f;
			}
		}

		m_UI->SetColor(m_SkipUIid, m_SkipSelect.Col);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CTutorial::Draw
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CTutorial::Draw(void)
{
	//  �J�����̐ݒ�
	m_Camera->SetCamera();

	//  �V�[���I�[���`��
	CScene::DrawAll();
}