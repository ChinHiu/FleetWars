//------------------------------------------------------------------------------
//	�^�C�g���F		�}�l�[�W���̊֐�
//	�t�@�C�����F	manager.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/09
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "Func.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "debugProc.h"
#include "openAL.h"
#include "mode.h"
#include "camera.h"
#include "fade.h"
#include "player.h"
#include "meshField.h"
#include "water.h"
#include "effect.h"
#include "enemy.h"
#include "missile.h"
#include "userMap.h"
#include "sprayBehide.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------

//  UI�e�N�X�`���t�@�C���p�X
const LPCSTR g_UITexture[] =
{
	{ "./data/TEXTURE/UI/TITLE/Title_Mark.png" },
	{ "./data/TEXTURE/UI/TITLE/Start_Mark.png" },
	{ "./data/TEXTURE/UI/TITLE/Exit_Mark.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Scope.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/UserMapEX.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Frame.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Keyboard.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Skip.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_0.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_1.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_2.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_3.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_4.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_5.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_6.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_7.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_8.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_9.png" },
	{ "./data/TEXTURE/UI/GAME/Weapon_Mark/Weapon_Bullet.png" },
	{ "./data/TEXTURE/UI/GAME/Weapon_Mark/Weapon_Missile.png" },
	{ "./data/TEXTURE/UI/GAME/Weapon_Mark/Weapon_Repair.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Heat.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Infinity.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Overheat.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Power.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Speed.png" },
	{ "./data/TEXTURE/UI/GAME/Other/HP_Frame.png" },
	{ "./data/TEXTURE/UI/GAME/Other/HP.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Mission_Complete.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Mission_Failed.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Mission_Start.png" },
	{ "./data/TEXTURE/UI/RESULT/Result_Frame.png" },
	{ "./data/TEXTURE/UI/RESULT/Result_Rank.png" },
	{ "./data/TEXTURE/UI/RESULT/Result_Thanks.png" },
	{ "./data/TEXTURE/UI/RESULT/Clear_Failed.png" },
};

//  �X�J�C�{�b�N�X�e�N�X�`���t�@�C���p�X
const LPCSTR g_SkyTexture[] =
{
	{ "./data/TEXTURE/SkyBox/Up.png" },
	{ "./data/TEXTURE/SkyBox/Left.png" },
	{ "./data/TEXTURE/SkyBox/Front.png" },
	{ "./data/TEXTURE/SkyBox/Right.png" },
	{ "./data/TEXTURE/SkyBox/Back.png" },
	{ "./data/TEXTURE/SkyBox/Down.png" },
};

// �G�t�F�N�g�e�N�X�`���t�@�C���p�X
const LPCSTR g_EffectTexture[] =
{
	{ "./data/TEXTURE/EffectAnimation/WaterFall_00_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/WaterFall_01_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/WaterFall_02_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/Water_Impact_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/Spray_Before_4_8.png" },
	{ "./data/TEXTURE/EffectAnimation/Spray_Behide_8_2.png" },
	{ "./data/TEXTURE/EffectAnimation/Shot_Fire_2_2.png" },
	{ "./data/TEXTURE/EffectAnimation/Explosion_8_6.png" },
	{ "./data/TEXTURE/EffectAnimation/Explosion_8_4.png" },
};

//  ���f���e�N�X�`���t�@�C���p�X
const LPCSTR g_ModelTexture[nLoadModel][nLoadModelTexPattern] =
{
	{
		{ "./data/TEXTURE/SHIP/Fast_Normal.tga" },
		{ "./data/TEXTURE/SHIP/Fast_Broken.tga" },
	},

	{
		{ "./data/TEXTURE/SHIP/Gorshkov_Normal.tga" },
		{ "./data/TEXTURE/SHIP/Gorshkov_Broken.tga" },
	},

	{
		{ "./data/TEXTURE/SHIP/Hamina_Normal.tga" },
		{ "./data/TEXTURE/SHIP/Hamina_Broken.tga" },
	},

	{
		{ "./data/TEXTURE/WEAPON/Missile.tga" },
		{ NULL },
	}

};

//  ���f���`���t�@�C���p�X
const LPCSTR g_ModelFile[] =
{
	{ "./data/MODEL/SHIP/Hamina_Fast.x" },

	{ "./data/MODEL/SHIP/Hamina_Body.x" },
	{ "./data/MODEL/SHIP/Hamina_Battery.x" },
	{ "./data/MODEL/SHIP/Hamina_Gun.x" },

	{ "./data/MODEL/SHIP/Gorshkov_Body.x" },
	{ "./data/MODEL/SHIP/Gorshkov_Battery.x" },
	{ "./data/MODEL/SHIP/Gorshkov_Gun.x" },

	{ "./data/MODEL/WEAPON/Missile.x" }
};

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------
CRenderer			*CManager::m_Renderer;
CInput				*CManager::m_Input;
CDebugProc			*CManager::m_DebugProc;
COpenAL				*CManager::m_OpenAL;
CMode				*CManager::m_Mode;
CFunc				*CManager::m_Func;
CCamera_Data		*CManager::m_CameraData;
CFade				*CManager::m_Fade;
CPlayer				*CManager::m_Player;
CMeshField			*CManager::m_Sea;
CUI					*CManager::m_UI;
CBullet				*CManager::m_Bullet;
CWater				*CManager::m_Water;
CEffect				*CManager::m_Effect;
CEnemy_Hamina		*CManager::m_Hamina;
CMissile			*CManager::m_Missile;
CUserMap			*CManager::m_UserMap;
CSprayBehide		*CManager::m_SprayBehide;

int					CManager::m_ClearTime;
int					CManager::m_KillsNum;
int					CManager::m_Damage;
bool				CManager::m_bMissionResult;

//  ���[�f�B���O�y�ʉ��̂��߁A�e�N�X�`���o�b�t�@���}�l�[�W���[�ŊǗ�
LPDIRECT3DTEXTURE9	CManager::m_UITextureBuffer[nLoadUI];
LPDIRECT3DTEXTURE9	CManager::m_SkyboxTextureBuffer[nLoadSkybox];
LPDIRECT3DTEXTURE9	CManager::m_EffectTextureBuffer[nLoadEffectTex];
LPDIRECT3DTEXTURE9	CManager::m_ModelTextureBuffer[nLoadModel][nLoadModelTexPattern];
CModel_Data			*CManager::m_ModelData;

//------------------------------------------------------------------------------
//	�֐���:	CManager::CManager()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CManager::CManager()
{
	m_Renderer		= NULL;
	m_Input			= NULL;
	m_DebugProc		= NULL;
	m_OpenAL		= NULL;
	m_Mode			= NULL;
	m_Func			= NULL;
	m_Bullet		= NULL;

	memset(m_UITextureBuffer, NULL, sizeof(m_UITextureBuffer));		
	memset(m_SkyboxTextureBuffer, NULL, sizeof(m_SkyboxTextureBuffer));
	memset(m_EffectTextureBuffer, NULL, sizeof(m_EffectTextureBuffer));
	memset(m_ModelTextureBuffer, NULL, sizeof(m_ModelTextureBuffer));

	m_ClearTime = 0;
	m_KillsNum = 0;
	m_Damage = 0;
}

//------------------------------------------------------------------------------
//	�֐���:	CManager::~CManager()
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CManager::~CManager()
{
}

//------------------------------------------------------------------------------
//	�֐���:	void CManager::Init
//	����:	HINSTANCE hInstance, HWND hWnd, BOOL bWindow
//	�߂�l: �Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
//  �C���X�^���X����
	m_Renderer			= new CRenderer;				//  �����_��
	m_Input				= new CInput;					//  DirectInput
#ifdef _DEBUG
	m_DebugProc			= new CDebugProc;				//  �f�o�b�O�v���V�[�W��
#endif
	m_OpenAL			= new COpenAL;					//  OPenAL
	m_Mode				= new CTitle;					//  �V�[�����[�h
	m_ModelData			= new CModel_Data[MODEL_MAX];	//  ���f���f�[�^
	m_Fade				= new CFade;					//  �t�F�[�h
	m_Func				= new CFunc;					//  �֐�

	//  �����_���̏�����
	m_Renderer->Init(hInstance, hWnd, bWindow);

	//	���͂̏�����
	m_Input->Init(hInstance, hWnd);

	//  �t�F�[�h�̏�����
	m_Fade->Init();

	//  �Q�[���I�[��������
	m_Mode->Init();

#ifdef _DEBUG
	//  �f�o�b�O�v���V�[�W���̏���������
	m_DebugProc->Init();
#endif

	//  ���[�f�B���O���Ԃ��팸
	LoadingReduction();
}

//------------------------------------------------------------------------------
//	�֐���:	void CManager::Uninit
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CManager::Uninit(void)
{
	//  �����_���̏I��
	m_Renderer->Uninit();

#ifdef _DEBUG
	//  �f�o�b�O�v���V�[�W���̏I��
	m_DebugProc->Uninit();
#endif

	//  �Q�[���I�[���̏I��
	m_Mode->Uninit();

	//  �t�F�[�h�̏I��
	m_Fade->Uninit();

	//  ���͂̏I��
	m_Input->Uninit();

	//  OpenAL�̏I��
	m_OpenAL->Uninit();

	//  UI�e�N�X�`���o�b�t�@�����
	for (int i = 0; i < nLoadUI; i++)
	{
		SAFE_RELEASE(m_UITextureBuffer[i]);
	}

	//  Skybox�e�N�X�`���o�b�t�@�����
	for (int i = 0; i < nLoadSkybox; i++)
	{
		SAFE_RELEASE(m_SkyboxTextureBuffer[i]);
	}

	//  Effect�e�N�X�`���o�b�t�@�����
	for (int i = 0; i < nLoadEffectTex; i++)
	{
		SAFE_RELEASE(m_EffectTextureBuffer[i]);
	}

	//  Model�e�N�X�`���o�b�t�@�����
	for (int x = 0; x < nLoadModel; x++)
	{
		SAFE_RELEASE(m_ModelData[x].BufferMat);
		SAFE_RELEASE(m_ModelData[x].Mesh);
		m_ModelData[x].NumMat = NULL;
		for (int y = 0; y < nLoadModelTexPattern; y++)
		{
			SAFE_RELEASE(m_ModelTextureBuffer[x][y]);
		}
	}

	//  �C���X�^���X�폜
	delete m_Renderer;
	delete m_Mode;
	delete m_Input;
	delete m_OpenAL;
	delete[] m_ModelData;
	delete m_Func;
#ifdef _DEBUG
	delete m_DebugProc;
#endif
}

//------------------------------------------------------------------------------
//	�֐���:	void CManager::Update
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CManager::Update()
{
	CKeyboard	*keyboard	= CManager::GetInput()->GetKeyboard();
	CMouse		*mouse = CManager::GetInput()->GetMouse();

	//  �����_���̍X�V
	m_Renderer->Update();

	//  ���͂̍X�V
	m_Input->Update();

	//  �Q�[���I�[���̍X�V
	m_Mode->Update();

	//  �t�F�[�h�̍X�V
	m_Fade->Update();

#ifdef _DEBUG
	//  �f�o�b�O�v���V�[�W���̍X�V����
	m_DebugProc->Update();
#endif
}

//------------------------------------------------------------------------------
//	�֐���:	void CManager::Draw
//	����:	�Ȃ�
//	�߂�l: �Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CManager::Draw(void)
{
	//  �f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

//  �����_���̊J�n
	m_Renderer->Begin();

	//  �Q�[���I�[���̕`��
	m_Mode->Draw();

	//  �t�F�[�h�̕`��
	m_Fade->Draw();
#ifdef _DEBUG
	//  �f�o�b�O�v���V�[�W���̕`��
	m_DebugProc->Draw();
#endif

//  �����_���̏I��
	m_Renderer->End();
}

//------------------------------------------------------------------------------
//	�֐���:	void CManager::LoadingReduction
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���[�f�B���O���Ԃ��팸���邽�߁A�S�ĕ`��Ɋւ���f�[�^��ǂݍ��ށB
//			���[�h���ƂɕK�v�ȃf�[�^���ł͂Ȃ��A�������[�̍œK���ł͂Ȃ��B
//------------------------------------------------------------------------------
void CManager::LoadingReduction(void)
{
	//  UI�e�N�X�`��
	for (int i = 0; i < nLoadUI; i++) {
		//  �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile
		(
			m_Renderer->GetDevice(),
			g_UITexture[i],								//  �e�N�X�`���t�@�C���ʒu
			&m_UITextureBuffer[i]						//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
		);
	}

	//  Skybox�e�N�X�`��
	for (int i = 0; i < nLoadSkybox; i++)
	{
		//  �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			m_Renderer->GetDevice(),
			g_SkyTexture[i],							//  �e�N�X�`���t�@�C���ʒu
			&m_SkyboxTextureBuffer[i]					//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
		);
	}

	//  �G�t�F�N�g�A�j���[�V�����e�N�X�`��
	for (int i = 0; i < nLoadEffectTex; i++)
	{
		//  �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			m_Renderer->GetDevice(),
			g_EffectTexture[i],							//  �e�N�X�`���t�@�C���ʒu
			&m_EffectTextureBuffer[i]					//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
		);
	}

	//  ���f���e�N�X�`��
	for (int x = 0; x < nLoadModel; x++)
	{
		for (int y = 0; y < nLoadModelTexPattern; y++)

			//  �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(
				m_Renderer->GetDevice(),
				g_ModelTexture[x][y],					//  �e�N�X�`���t�@�C���ʒu
				&m_ModelTextureBuffer[x][y]				//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
			);
	}

	//  ���f���̏��
	for (int i = 0; i < MODEL_MAX; i++)
	{
		//  X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			g_ModelFile[i],		//  �ǂݍ��ރt�@�C���ʒu
			D3DXMESH_SYSTEMMEM,
			m_Renderer->GetDevice(),
			NULL,
			&m_ModelData[i].BufferMat,		//  �}�e���A�����
			NULL,
			&m_ModelData[i].NumMat,			//  �}�e���A���̐�
			&m_ModelData[i].Mesh				//  ���b�V�����
		);
	}
}

//------------------------------------------------------------------------------
//	�֐���:	CRenderer *CManager::GetRenderer
//	����:	�Ȃ�
//	�߂�l:	m_Renderer
//	����:	�����_�����擾
//------------------------------------------------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	return m_Renderer;
}

//------------------------------------------------------------------------------
//	�֐���:	CInput *CManager::GetInput
//	����:	�Ȃ�
//	�߂�l:	m_Input
//	����:	DirectInput���擾
//------------------------------------------------------------------------------
CInput *CManager::GetInput(void)
{
	return m_Input;
}

//------------------------------------------------------------------------------
//	�֐���:	CMode *CManager::GetMode
//	����:	�Ȃ�
//	�߂�l:	CMode m_Mode
//	����:	���[�h���擾
//------------------------------------------------------------------------------
CMode *CManager::GetMode(void)
{
	return m_Mode;
}

//------------------------------------------------------------------------------
//	�֐���:	CCamera_Data *CManager::GetCameraData
//	����:	�Ȃ�
//	�߂�l:	m_CameraData
//	����:	�J�����f�[�^���擾
//------------------------------------------------------------------------------
CCamera_Data *CManager::GetCameraData(void)
{
	return m_CameraData;
}

//------------------------------------------------------------------------------
//	�֐���:	CFunc *CManager::GetFunc
//	����:	�Ȃ�
//	�߂�l:	CFunc m_CollisionFunc
//	����:	�R���W�����֐����擾
//------------------------------------------------------------------------------
CFunc *CManager::GetFunc(void)
{
	return m_Func;
}

//------------------------------------------------------------------------------
//	�֐���:	LPDIRECT3DTEXTURE9 CManager::GetUITextureBuffer
//	����:	int nType
//	�߂�l:	m_UITextureBuffer[nType]
//	����:	UI�e�N�X�`���o�b�t�@���擾
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetUITextureBuffer(int nType)
{
	return m_UITextureBuffer[nType];
}

//------------------------------------------------------------------------------
//	�֐���:	LPDIRECT3DTEXTURE9 CManager::GetSkyboxTextureBuffer
//	����:	int nID
//	�߂�l:	m_SkyboxTextureBuffer[nID]
//	����:	�X�J�C�{�b�N�X�e�N�X�`���o�b�t�@���擾
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetSkyboxTextureBuffer(int nID)
{
	return m_SkyboxTextureBuffer[nID];
}

//------------------------------------------------------------------------------
//	�֐���:	LPDIRECT3DTEXTURE9 CManager::GetModelTextureBuffer
//	����:	MODEL_TYPE Model_Type, bool bBroken
//	�߂�l:	m_ModelTextureBuffer[Model_Type][bBroken]
//	����:	���f���e�N�X�`���o�b�t�@���擾
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetModelTextureBuffer(MODEL_TYPE Model_Type, bool bBroken)
{
	return m_ModelTextureBuffer[Model_Type][bBroken];
}

//------------------------------------------------------------------------------
//	�֐���:	LPDIRECT3DTEXTURE9 CManager::GetEffectTextureBuffer
//	����:	EFFECT_TYPE Effect_Type
//	�߂�l:	m_EffectTextureBuffer[Effect_Type]
//	����:	�G�t�F�N�g�e�N�X�`���o�b�t�@���擾
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetEffectTextureBuffer(EFFECT_TYPE Effect_Type)
{
	return m_EffectTextureBuffer[Effect_Type];
}

//------------------------------------------------------------------------------
//	�֐���:	CModel_Data	*CManager::GetModeData
//	����:	MODEL_PARTS Model_Parts
//	�߂�l:	&m_ModelData[Model_Parts]
//	����:	���f���f�[�^���擾
//------------------------------------------------------------------------------
CModel_Data	*CManager::GetModeData(MODEL_PARTS Model_Parts)
{
	return &m_ModelData[Model_Parts];
}

//------------------------------------------------------------------------------
//	�֐���:	CFade *CManager::GetFade
//	����:	�Ȃ�
//	�߂�l:	m_Fade
//	����:	�t�F�[�h���擾
//------------------------------------------------------------------------------
CFade *CManager::GetFade(void)
{
	return m_Fade;
};

//------------------------------------------------------------------------------
//	�֐���:	CPlayer *CManager::GetPlayer
//	����:	�Ȃ�
//	�߂�l:	m_Player
//	����:	�v���C���[���擾
//------------------------------------------------------------------------------
CPlayer *CManager::GetPlayer(void)
{
	return m_Player;
};

//------------------------------------------------------------------------------
//	�֐���:	CMeshField *CManager::GetSea
//	����:	�Ȃ�
//	�߂�l:	m_Sea
//	����:	�C���擾
//------------------------------------------------------------------------------
CMeshField *CManager::GetSea(void)
{
	return m_Sea;
}

//------------------------------------------------------------------------------
//	�֐���:	CUI *CManager::GetUI
//	����:	�Ȃ�
//	�߂�l:	m_UI
//	����:	UI���擾
//------------------------------------------------------------------------------
CUI *CManager::GetUI(void)
{
	return m_UI;
}

//------------------------------------------------------------------------------
//	�֐���:	COpenAL *CManager::GetOpenAL
//	����:	�Ȃ�
//	�߂�l:	m_OpenAL
//	����:	OpenAL���擾
//------------------------------------------------------------------------------
COpenAL *CManager::GetOpenAL(void)
{
	return m_OpenAL;
}

//------------------------------------------------------------------------------
//	�֐���:	CWater *CManager::GetWater
//	����:	�Ȃ�
//	�߂�l:	m_Water
//	����:	�����擾
//------------------------------------------------------------------------------
CWater *CManager::GetWater(void)
{
	return m_Water;
}

//------------------------------------------------------------------------------
//	�֐���: CBullet *CManager::GetBullet
//	����:	�Ȃ�
//	�߂�l:	m_Bullet
//	����:	�e���擾
//------------------------------------------------------------------------------
CBullet *CManager::GetBullet(void)
{
	return m_Bullet;
}

//------------------------------------------------------------------------------
//	�֐���: CEffect *CManager::GetEffect
//	����:	�Ȃ�
//	�߂�l:	m_Effect
//	����:	�G�t�F�N�g���擾
//------------------------------------------------------------------------------
CEffect *CManager::GetEffect(void)
{
	return m_Effect;
}

//------------------------------------------------------------------------------
//	�֐���: CEnemy_Hamina *CManager::GetHamina
//	����:	�Ȃ�
//	�߂�l:	m_Hamina
//	����:	Hamina�G���擾
//------------------------------------------------------------------------------
CEnemy_Hamina *CManager::GetHamina(void)
{
	return m_Hamina;
}

//------------------------------------------------------------------------------
//	�֐���: CMissile *CManager::GetMissile
//	����:	�Ȃ�
//	�߂�l:	m_Missile
//	����:	�~�T�C�����擾
//------------------------------------------------------------------------------
CMissile *CManager::GetMissile(void)
{
	return m_Missile;
}

//------------------------------------------------------------------------------
//	�֐���: CUserMap *CManager::GetUserMap
//	����:	�Ȃ�
//	�߂�l:	m_UserMap
//	����:	���[�U�[�}�b�v���擾
//------------------------------------------------------------------------------
CUserMap *CManager::GetUserMap(void)
{
	return m_UserMap;
}

//------------------------------------------------------------------------------
//	�֐���: CSprayBehide *CManager::GetSprayBehide
//	����:	�Ȃ�
//	�߂�l:	m_SprayBehide
//	����:	���򖗁i���j���擾
//------------------------------------------------------------------------------
CSprayBehide *CManager::GetSprayBehide(void)
{
	return m_SprayBehide;
}

//------------------------------------------------------------------------------
//	�֐���:	void CManager::SetMode
//	����:	CMode *Mode
//	�߂�l:	�Ȃ�
//	����:	���[�h�̐ݒ�
//------------------------------------------------------------------------------
void CManager::SetMode(CMode *Mode)
{
	m_Mode->Uninit();
	delete m_Mode;

	m_Mode = Mode;
	m_Mode->Init();
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetCameraData
//	����:	CCamera_Data *pCamera_Data
//	�߂�l:	�Ȃ�
//	����:	�J�����f�[�^��ݒ�
//------------------------------------------------------------------------------
void CManager::SetCameraData(CCamera_Data *pCamera_Data)
{
	m_CameraData = pCamera_Data;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetSea
//	����:	CMeshField *pSea
//	�߂�l:	�Ȃ�
//	����:	�C��ݒ�
//------------------------------------------------------------------------------
void CManager::SetSea(CMeshField *pSea)
{
	m_Sea = pSea;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetPlayer
//	����:	CPlayer *pPlayer
//	�߂�l:	�Ȃ�
//	����:	�v���C���[��ݒ�
//------------------------------------------------------------------------------
void CManager::SetPlayer(CPlayer *pPlayer)
{
	m_Player = pPlayer;
};

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetUI
//	����:	CUI *pUI
//	�߂�l:	�Ȃ�
//	����:	UI��ݒ�
//------------------------------------------------------------------------------
void CManager::SetUI(CUI *pUI)
{
	m_UI = pUI;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetOpenAL
//	����:	COpenAL *pOpenAL
//	�߂�l:	�Ȃ�
//	����:	OpenAL��ݒ�
//------------------------------------------------------------------------------
void CManager::SetOpenAL(COpenAL *pOpenAL)
{
	m_OpenAL = pOpenAL;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetWater
//	����:	CWater *pWater
//	�߂�l:	�Ȃ�
//	����:	����ݒ�
//------------------------------------------------------------------------------
void CManager::SetWater(CWater *pWater)
{
	m_Water = pWater;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetBullet
//	����:	CBullet *pBullet
//	�߂�l:	�Ȃ�
//	����:	�e��ݒ�
//------------------------------------------------------------------------------
void CManager::SetBullet(CBullet *pBullet)
{
	m_Bullet = pBullet;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetEffect
//	����:	CEffect *pEffect
//	�߂�l:	�Ȃ�
//	����:	�e��ݒ�
//------------------------------------------------------------------------------
void CManager::SetEffect(CEffect *pEffect)
{
	m_Effect = pEffect;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetHamina
//	����:	CEnemy_Hamina *pHaminaEnemy
//	�߂�l:	�Ȃ�
//	����:	Hamina�G��ݒ�
//------------------------------------------------------------------------------
void CManager::SetHamina(CEnemy_Hamina *pHaminaEnemy)
{
	m_Hamina = pHaminaEnemy;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetHamina
//	����:	CMissile *pMissile
//	�߂�l:	�Ȃ�
//	����:	�~�T�C����ݒ�
//------------------------------------------------------------------------------
void CManager::SetMissile(CMissile *pMissile)
{
	m_Missile = pMissile;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SetUserMap
//	����:	CUserMap *pUserMap
//	�߂�l:	�Ȃ�
//	����:	���[�U�[�}�b�v��ݒ�
//------------------------------------------------------------------------------
void CManager::SetUserMap(CUserMap *pUserMap)
{
	m_UserMap = pUserMap;
}

//------------------------------------------------------------------------------
//	�֐���: void CManager::SerSprayBehide
//	����:	CUserMap *pUserMap
//	�߂�l:	�Ȃ�
//	����:	���򖗁i���j��ݒ�
//------------------------------------------------------------------------------
void CManager::SetSprayBehide(CSprayBehide *pSprayBehide)
{
	m_SprayBehide = pSprayBehide;
}

