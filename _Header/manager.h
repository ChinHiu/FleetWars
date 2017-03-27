//------------------------------------------------------------------------------
//	�^�C�g���F		�}�l�[�W���[�̃w�b�_�[
//	�t�@�C�����F	manager.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/19
//------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "renderer.h"
#include "game.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CInput;
class CDebugProc;
class COpenAL;
class CMode;
class CFade;
class CFunc;
class CCamera_Data;
class CPlayer;
class CMeshField;
class CUI;
class CBullet;
class CWater;
class CEffect;
class CEnemy_Hamina;
class CMissile;
class CUserMap;
class CSprayBehide;

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------

//  ���[�f�B���O���Ԃ�Z�k���邽�ߊeTexture�Ax�t�@�C���̍ő吔��`
const int nLoadUI = 33;						//  UI�e�N�X�`���̐�
const int nLoadSkybox = 6;					//  Skybox�e�N�X�`���̐�
const int nLoadEffectTex = 9;				//  effect�e�N�X�`���̐�
const int nLoadModel = 4;					//  ���f���̐�
const int nLoadModelTexPattern = 2;			//  ���f���e�N�X�`���^�C�v�̐��i�m�[�}���Ɣj���j

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  ���f���p�[�c
typedef enum
{
	MODEL_PARTS_FAST = 0,
	MODEL_PARTS_HAMINA_BODY,
	MODEL_PARTS_HAMINA_BATTERY,
	MODEL_PARTS_HAMINA_GUN,

	MODEL_PARTS_GORSHKOV_BODY,
	MODEL_PARTS_GORSHKOV_BATTERY,
	MODEL_PARTS_GORSHKOV_GUN,

	MODEL_PARTS_MISSILE,
	MODEL_MAX
}MODEL_PARTS;

//  ���f���^�C�v
typedef enum
{
	MODEL_NONE = -1,
	MODEL_FAST,
	MODEL_GORSHKOV,
	MODEL_HAMINA,
	MODEL_MISSILE
}MODEL_TYPE;

//  �G�t�F�N�g�^�C�v
typedef enum
{
	EFFECT_NONE = -1,
	EFFECT_WATER_FALL_000,
	EFFECT_WATER_FALL_001,
	EFFECT_WATER_FALL_002,
	EFFECT_WATER_IMPACT,
	EFFECT_SPRAY_BEFORE,
	EFFECT_SPRAY_BEHIDE,
	EFFECT_SHOT_FIRE,
	EFFECT_EXPLOSION_000,
	EFFECT_EXPLOSION_001
}EFFECT_TYPE;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  ���f���f�[�^�N���X
class CModel_Data
{
public:
	LPD3DXMESH			Mesh;			//  ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		BufferMat;		//  �}�e���A�����ւ̃|�C���^
	DWORD				NumMat;			//  �}�e���A����

	CModel_Data()
		: Mesh(NULL)
		, BufferMat(NULL)
		, NumMat(NULL)
	{};
};

//  �}�l�[�W���[�N���X
class CManager
{
public:
	CManager();
	~CManager();
	static void					Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	static void					Uninit(void);
	static void					Update(void);
	static void					Draw(void);
	static void					LoadingReduction(void);

	//  �擾�֐�
	static CRenderer			*GetRenderer(void);												//  �����_�����擾
	static CInput				*GetInput(void);												//  DirectInput���擾
	static CMode				*GetMode(void);													//  �V�[�����[�h���擾
	static CFade				*GetFade(void);													//  �t�F�[�h���擾
	static CFunc				*GetFunc(void);													//  �֐����擾
	static CCamera_Data			*GetCameraData(void);											//  �J�����f�[�^���擾
	static CPlayer				*GetPlayer(void);												//  �v���C���[���擾
	static CMeshField			*GetSea(void);													//  �C���擾
	static CUI					*GetUI(void);													//  UI���擾
	static CBullet				*GetBullet(void);												//  �e���擾
	static COpenAL				*GetOpenAL(void);												//  OpenAL���擾
	static CWater				*GetWater(void);												//  Water���擾
	static CEffect				*GetEffect(void);												//  �G�t�F�N�g���擾
	static CEnemy_Hamina		*GetHamina(void);												//  Hamina�G���擾
	static CMissile				*GetMissile(void);												//  �~�T�C�����擾
	static CUserMap				*GetUserMap(void);												//  ���[�U�[�}�b�v���擾
	static CSprayBehide			*GetSprayBehide(void);											//  ���򖗁i���j���擾

	static int					*GetClearTime(void) { return &m_ClearTime; };
	static int					*GetKillsNum(void) { return &m_KillsNum; };
	static int					*GetPlayerDamage(void) { return &m_Damage; };
	static bool					*GetMissionResult(void) { return &m_bMissionResult; };

	static LPDIRECT3DTEXTURE9	GetUITextureBuffer(int nType);									//  UI�e�N�X�`���o�b�t�@���擾
	static LPDIRECT3DTEXTURE9	GetSkyboxTextureBuffer(int nID);								//  �X�J�C�{�b�N�X�e�N�X�`���o�b�t�@���擾
	static LPDIRECT3DTEXTURE9	GetModelTextureBuffer(MODEL_TYPE Model_Type, bool bBroken);		//  ���f���e�N�X�`���o�b�t�@���擾
	static LPDIRECT3DTEXTURE9	GetEffectTextureBuffer(EFFECT_TYPE Effect_Type);				//  //  �G�t�F�N�g�e�N�X�`���o�b�t�@���擾
	static CModel_Data			*GetModeData(MODEL_PARTS Model_Parts);							//  ���f���f�[�^���擾

	//  �Z�b�g�֐�
	static void					SetMode(CMode *pMode);											//  �V�[�����[�h��ݒ�
	static void					SetCameraData(CCamera_Data *pCamera_Data);						//  �J�����f�[�^��ݒ�
	static void					SetPlayer(CPlayer *pPlayer);									//  �v���C���[��ݒ�
	static void					SetSea(CMeshField *pSea);										//  �C��ݒ�
	static void					SetUI(CUI *pUI);												//  UI��ݒ�
	static void					SetBullet(CBullet *pBullet);									//  �e��ݒ�
	static void					SetOpenAL(COpenAL *pOpenAL);									//  OpenAL��ݒ�
	static void					SetWater(CWater *pWater);										//  Water��ݒ�
	static void					SetEffect(CEffect *pEffect);									//  �G�t�F�N�g��ݒ�
	static void					SetHamina(CEnemy_Hamina *pEnemyHamina);							//  Hamina�G��ݒ�
	static void					SetMissile(CMissile *pMissile);									//  �~�T�C����ݒ�
	static void					SetUserMap(CUserMap *pUserMap);									//  ���[�U�[�}�b�v��ݒ�
	static void					SetSprayBehide(CSprayBehide *pSprayBehide);						//  ���򖗁i���j��ݒ�

	static void					AddKillsNum(int nNum) { m_KillsNum += nNum; };
	static void					SetKillsNum(int nNum) { m_KillsNum = nNum; };
	static void					SetClearTime(int nTime) { m_ClearTime = nGameTime - nTime; };
	static void					SetPlayerDamage(int nLife) { m_Damage = 100 - nLife; };
	static void					SetMissionResult(bool bFlag) { m_bMissionResult = bFlag; };

private:				
	static CRenderer			*m_Renderer;													//  �����_��
	static CInput				*m_Input;														//  DirectInput
	static CDebugProc			*m_DebugProc;													//  �f�o�b�O�v���V�[�W��
	static COpenAL				*m_OpenAL;														//  OpenAL
	static CMode				*m_Mode;														//  �V�[�����[�h
	static CFade				*m_Fade;														//  �t�F�[�h
	static CFunc				*m_Func;														//  �֐�
	static CUI					*m_UI;															//  UI
	static CBullet				*m_Bullet;														//  �e
	static CCamera_Data			*m_CameraData;													//  �J�����f�[�^
	static CPlayer				*m_Player;														//  �v���C���[
	static CMeshField			*m_Sea;															//  �C
	static CWater				*m_Water;														//  ��
	static CEffect				*m_Effect;														//  �G�t�F�N�g
	static CEnemy_Hamina		*m_Hamina;														//  Hamina�G
	static CMissile				*m_Missile;														//  �~�T�C��
	static CUserMap				*m_UserMap;														//  ���[�U�[�}�b�v
	static CSprayBehide			*m_SprayBehide;													//  ���򖗁i���j

	static int					m_ClearTime;
	static int					m_KillsNum;
	static int					m_Damage;
	static bool					m_bMissionResult;

	//  ���[�f�B���O���Ԃ�Z�k���邽�߂̕ϐ�
	static LPDIRECT3DTEXTURE9	m_UITextureBuffer[nLoadUI];										//  �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_SkyboxTextureBuffer[nLoadSkybox];								//  �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_EffectTextureBuffer[nLoadEffectTex];							//  �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_ModelTextureBuffer[nLoadModel][nLoadModelTexPattern];			//  �e�N�X�`���ւ̃|�C���^
	static CModel_Data			*m_ModelData;													//  ���f���f�[�^
};

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
#endif