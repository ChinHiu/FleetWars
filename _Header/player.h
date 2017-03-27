//------------------------------------------------------------------------------
//	�^�C�g���F		player�̃w�b�_�[
//	�t�@�C�����F	player.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/12/13
//------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"
#include "sprayBefore.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CModel;
class CObb;
class CObbTest;
class CStencilShadow;
class CSpray;
class CSprayBehide;

//------------------------------------------------------------------------------
//	const��`
//------------------------------------------------------------------------------
const int nMissileMax_P = 4;			//  �v���C���[�~�T�C���ő吔
const int nObbMax_P = 4;				//  �v���C���[Obb�ő吔
const float fOverHitMax_P = 1.0f;		//  �v���C���[�I�[�o�[�q�b�g�ő吔

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  �v���C���[���f���p�[�c
typedef enum
{
	PLAYER_BODY = 0,
	PLAYER_BATTERY,
	PLAYER_GUN,
	PLAYER_PARTS_MAX
}PLAYER_PARTS;

//  ����^�C�v
typedef enum
{
	WEAPON_NONE = -1,
	WEAPON_BULLET,
	WEAPON_MISSILE,
	WEAPON_REPAIR,
	WEAPON_TYPE_MAX,
}WEAPON_TYPE;

typedef enum
{
	BEARING_NONE = 0,
	BEARING_LEFT,
	BEARING_RIGHT
}BEARING_STATE;

typedef enum
{
	ENEMY_NONE = -1,
	ENEMY_FAST,
	ENEMY_HAMINA,
	ENEMY_BOSS,
	ENEMY_TYPE_MAX
}ENEMY_TYPE;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------
class CPhysics_Data
{
public:
	D3DXVECTOR3		TargetDirectVector;
	D3DXVECTOR3		PosVector;
	float			DirectVectorAngle;			//  target��own�̕����x�N�g���Ȃ��p
	float			VectorAngle;				//  target����own���W�̃x�N�g����target�����x�N�g���̂Ȃ��p
	D3DXVECTOR3		RelativeBearing;			//	target����ɁAown�̍��E�ʒu(��+�A�E-)	

	CPhysics_Data()
		: DirectVectorAngle(0)
		, VectorAngle(0)
		, RelativeBearing(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{}
};

//  �V�[���N���X
class CPlayer : public CScene
{
private:
	CMatrix			m_Matrix;									//  �}�g���b�N�X
	MODEL_TYPE		m_Type;										//  ���f���^�C�v
	CModel			*m_Model[PLAYER_PARTS_MAX];					//  ���f���i�p�[�c���j
	CCharacter_Data	m_CharData;									//  ��{�f�[�^
	CStencilShadow	*m_Shadow;									//  �V���h�E
	WEAPON_TYPE		m_Weapon;									//  ���݂̕���^�C�v
	int				m_WeaponID;									//  ����I��p�W��
	CWeapon_Data	m_WeaponData[WEAPON_TYPE_MAX];				//  ����f�[�^�i���퐔���j
	int				m_PowerNum;									//  �G���W���p���[�i���o�[�i�p���[��UI��`��p�j
	int				m_SpeedNum;									//  �X�s�[�h�i���o�[�i�X�s�[�h��UI��`��p�j
	int				m_AimSpeedNum;								//  �ڕW�X�s�[�h�i���o�[�i�v�Z�p�j
	float			m_OverHitRate;								//  �I�[�o�[�q�b�g����
	bool			m_bFire;									//  �A�˒����ǂ����H
	int				m_BulletCnt;								//  ��͖C�̎ˌ��J�E���g�iFrame�P�ʁj
	int				m_MissileCnt;								//  �~�T�C���̎ˌ��J�E���g�iFrame�P�ʁj
	D3DXVECTOR3		m_BatteryRot;								//  �C���]
	D3DXVECTOR3		m_ObbRelativePos[nObbMax_P];				//  ���Έړ���
	D3DXVECTOR3		m_ObbLength[nObbMax_P];						//  Obb�e���̒���
	CObb			m_Obb[nObbMax_P];							//  Obb
	CObbTest		*m_ObbTest[nObbMax_P];						//  ObbTest
	bool			m_bCollision;
	CSpray			*m_SprayBefore;
	D3DXVECTOR3		m_SprayBeforeSize;
	D3DXVECTOR3		m_SprayBeforePos[SPRAY_TYPE_MAX];
	D3DXVECTOR3		m_SprayBehideSize;
	D3DXVECTOR3		m_SprayBehidePos;

	bool			m_bMoveFlag;
	bool			m_bRotFlag;
	bool			m_WeaponFlag;

	int				m_WeaponMarkID[WEAPON_TYPE_MAX];
	int				m_LifeMarkID;
	int				m_MissileID[nMissileMax_P];
	int				m_HeatMarkID;
	int				m_OverHeatMarkID;
	int				m_ScopeMarkID;
	D3DXCOLOR		m_HeatCol;

	int				m_OldLife;
	float			m_fLifeRate;

public:
	CPlayer(int nPriority = 2, OBJECT_TYPE Object_Type = OBJTYPE_PLAYER);
	~CPlayer();

	static CPlayer *Create(MODEL_TYPE Model_Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void MatrixUpdate(void);
	void ObbUpdate(void);
	void WeaponBulletUpdate(void);
	void WeaponMissileUpdate(void);
	void WeaponRepairUpdate(void);

	D3DXMATRIX	*GetMatrix(void)	{ return &m_Matrix.World; };
	WEAPON_TYPE	*GetWeponType(void)	{ return &m_Weapon; };
	D3DXVECTOR3	*GetPosition(void)	{ return &m_CharData.Pos; };
	D3DXVECTOR3	*GetRotation(void)	{ return &m_CharData.Rot; };
	CObb		*GetObb(int nID)	{ return &m_Obb[nID]; };
	float		*GetSpeed(void)		{ return &m_CharData.fSpeed; };
	CWeapon_Data *GetWeaponData(WEAPON_TYPE Weapon_Type) { return &m_WeaponData[Weapon_Type]; }
	int *GetPowerNum(void) { return &m_PowerNum; };
	int *GetSpeedNum(void) { return &m_SpeedNum; };
	int	*GetLife(void) { return &m_CharData.nLife; };

	void SetMoveFlag(bool bFlag) { m_bMoveFlag = bFlag; };
	void SetRotFlag(bool bFlag) { m_bRotFlag = bFlag; };
	void SetWeaponFlag(bool bFlag) { m_WeaponFlag = bFlag; };
	void AddLife(int nNum) { m_CharData.nLife += nNum; };
};

#endif