//------------------------------------------------------------------------------
//	�^�C�g���F		�Q�[���̊֐�
//	�t�@�C�����F	game.cpp
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
#include "game.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "skybox.h"
#include "meshField.h"
#include "UI.h"
#include "openAL.h"
#include "fade.h"
#include "bullet.h"
#include "water.h"
#include "enemy.h"
#include "missile.h"
#include "userMap.h"
#include "sprayBehide.h"
#include "numUI.h"
#include "effect.h"
#include "result.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
const D3DXVECTOR3 GameCameraRot = D3DXVECTOR3(D3DX_PI * 0.43f, D3DX_PI, 0.0f);

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�֐���:	CGame::CGame()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CGame::CGame()
{
	m_Camera = NULL;
	m_Light = NULL;
	m_bFail = false;
	m_bOneCreat = false;
	m_GameResultCnt = 180;
}

//------------------------------------------------------------------------------
//	�֐���:	CGame::~CGame()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CGame::~CGame()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CGame::Init
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CGame::Init(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();

	//	�C���X�^���X�ϐ��̐����Ə���������
	m_Camera = new CCamera;			//  �J����
	m_Light = new CLight;			//	���C�g

#ifdef _DEBUG
	m_Time = 1200;
#else
	m_Time = nGameTime;

#endif

	m_FrameCnt = 60;

	//  �J�����̏�����
	m_Camera->Init(GameCameraRot, false);

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

	//  ���G�t�F�N�g�̐���
	CManager::SetWater(
		CWater::Create()
	);

	//  UI�̐���
	CManager::SetUI(
		m_UI = CUI::Create()
	);

	//  �~�T�C���̐���
	CManager::SetMissile(
		CMissile::Create()
	);

	//  ���򖗁i���j�̐���
	CManager::SetSprayBehide(
		CSprayBehide::Create()
	);

	//  �G�t�F�N�g�̐���
	CManager::SetEffect(
		CEffect::Create()
	);

	//  �e�̐���
	CManager::SetBullet(
		CBullet::Create()
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

	//  Hamina�G�̐���
	CManager::SetHamina(
		m_Hamina = CEnemy_Hamina::Create()
	);

	//  �G�̐���
	m_Hamina->Set(
		D3DXVECTOR3(-2000.0f, 0.0f, 4000.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_LEFT_NORMAL1
	);

	m_Hamina->Set(
		D3DXVECTOR3(-2500.0f, 0.0f, 4200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_LEFT_LEADER
	);

	m_Hamina->Set(
		D3DXVECTOR3(-3000.0f, 0.0f, 4400.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_LEFT_NORMAL2
	);

	m_Hamina->Set(
		D3DXVECTOR3(2000.0f, 0.0f, 4000.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RIGHT_NORMAL1
	);

	m_Hamina->Set(
		D3DXVECTOR3(2500.0f, 0.0f, 4200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RIGHT_LEADER
	);

	m_Hamina->Set(
		D3DXVECTOR3(3000.0f, 0.0f, 4400.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RIGHT_NORMAL2
	);

	m_Hamina->Set(
		D3DXVECTOR3(500, 0.0f, 3200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RAND
	);

	m_Hamina->Set(
		D3DXVECTOR3(-500, 0.0f, 3200.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		HAMINA_RAND
	);

	CManager::GetOpenAL()->Init(0, 0);

	m_BGMSource = CManager::GetOpenAL()->Play(SOUND_LABEL_BGM_GAME, 1.0f, 0.0f, 0.0f, 0.0f);
	m_WaveSource = CManager::GetOpenAL()->Play(SOUND_LABEL_SE_WAVE, 1.0f, 0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
//	�֐���:	void CGame::Uninit
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CGame::Uninit(void)
{
	//  �J�����̏I��			
	m_Camera->Uninit();
	CScene::UninitAll();
	CManager::GetOpenAL()->Uninit();

	m_NumUI->Uninit();

	//	�C���X�^���X�ϐ��̍폜
	delete m_Camera;				//  �J����
	delete m_Light;					//  ���C�g
}

//------------------------------------------------------------------------------
//	�֐���:	void CGame::Update
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CGame::Update(void)
{
	CKeyboard	*pKeyboard = CManager::GetInput()->GetKeyboard();
	D3DXVECTOR2 *pScreenSize = GetScreenSize();
	float		*pScreenRate = GetScreenRate();

	//  �J�����̍X�V
	m_Camera->Update();

	m_NumUI->Update();

	//  �V�[���I�[���X�V
	CScene::UpdateAll();

	CManager::GetOpenAL()->SetListenervalues(m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_BGMSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);
	CManager::GetOpenAL()->SetSourcePos(m_WaveSource, m_Player->GetPosition()->x, m_Player->GetPosition()->y, m_Player->GetPosition()->z);

	if (*CManager::GetKillsNum() < nHamina_Max)
	{
		if (m_FrameCnt <= 0)
		{
			m_Time--;
			m_FrameCnt = 60;

			m_Time = m_Time <= 0 ? 0 : m_Time;
		}
		else
		{
			m_FrameCnt--;
		}
	}

	if (*m_Player->GetLife() <= 0 || m_Time == 0)
	{
		m_bFail = true;
		CManager::SetMissionResult(true);
	}

	if (m_bFail)
	{
		m_GameResultCnt--;
		if (!m_bOneCreat)
		{
			m_UI->Set(
				UI_MISSION_FAIL,
				UI_TYPE_NONE,
				D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
				D3DXVECTOR2(1227.2f * *pScreenRate, 107.2f * *pScreenRate),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			);
			m_bOneCreat = true;
		}
	}
	else
	{
		if (*CManager::GetKillsNum() == nHamina_Max)
		{
			m_GameResultCnt--;
			if (!m_bOneCreat)
			{
				m_UI->Set(
					UI_MISSION_COM,
					UI_TYPE_NONE,
					D3DXVECTOR2(pScreenSize->x * 0.5f, pScreenSize->y * 0.5f),
					D3DXVECTOR2(1227.2f * *pScreenRate, 107.2f * *pScreenRate),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
				);
				m_bOneCreat = true;
			}
		}
	}

	if (m_GameResultCnt <= 0)
	{
		CManager::SetClearTime(m_Time);
		CManager::SetPlayerDamage(*m_Player->GetLife());
		CManager::GetFade()->Set(new CResult);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CGame::Draw
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CGame::Draw(void)
{
	//  �J�����̐ݒ�
	m_Camera->SetCamera();

	//  �V�[���I�[���`��
	CScene::DrawAll();

}