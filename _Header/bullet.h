//------------------------------------------------------------------------------
//	�^�C�g���F		�e�̃w�b�_�[
//	�t�@�C�����F	bullet.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/04/19
//------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CPlayer;
class CWater;
class CEffect;

//------------------------------------------------------------------------------
//	Const��`
//------------------------------------------------------------------------------
const int	nBullet_Max = 50;
const float	fBullet_Speed_Player = 50.0f;
const float	fBullet_Speed_Enemy = 30.0f;

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define PLAYER_SHOT_TEXTURE_FILE	"./data/TEXTURE/Bullet/Shot.png"

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �o���b�g�f�[�^�N���X
class CBullet_Data
{
public:
	D3DXVECTOR3 Pos;			//  ���݂̈ʒu
	D3DXVECTOR3	OriginalPos;	//  ���̈ʒu
	D3DXVECTOR3	TargetPos;		//  �^�[�Q�b�g�̈ʒu
	D3DXVECTOR3	Rot;			//  ��]
	D3DXVECTOR2	Size;			//  �T�C�Y
	D3DXVECTOR3	Vector;			//  ���_����ړI�n�܂ł̃x�N�g��
	D3DXVECTOR3	Scl;			//  �g��k��
	CMatrix		Matrix;			//  �}�g���b�N�X
	D3DXMATRIX	ViewMatrix;		//  �r���[�}�g���b�N�X
	int			Life;			//  ���C�t
	float		Speed;			//  �ړ����x
	bool		Flag;			//  true�͎g�p�Afalse�͖��g�p
	bool		CheckSea;		//  true���ƊC�Ɠ�����
	USER_TYPE	UserType;		//  �g�p��
	float		Gravity;		//  �d��
	int			FlyTime;		//  ��Ԏ���
	int			FlyTimeHalf;	//  ��Ԏ��� / 2 
	bool		bGravityInvert; //  �d�͔��]�t���O
	float		Distance;		//	�^�[�Q�b�g�܂ł̋���

	CBullet_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, OriginalPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, TargetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Size(D3DXVECTOR2(0.0f, 0.0f))
		, Vector(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Life(0)
		, Speed(0.0f)
		, Flag(false)
		, CheckSea(false)
		, UserType(USER_NONE)
		, Gravity(0.0f)
		, FlyTime(0)
		, FlyTimeHalf(0)
		, bGravityInvert(false)
		, Distance(0.0f)
	{
		D3DXMatrixIdentity(&ViewMatrix);
	}

	void SetFlag(bool bFlag) { Flag = bFlag; }
};

//  �o���b�g�N���X
class CBullet : public CScene
{
public:
	CBullet(int nPriority = 3, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CBullet();

	static			CBullet *Create(void);
	void			Init(void);
	void			Uninit(void);
	void			Update(void);
	void			Draw(void);

	HRESULT			MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	void			SetVertex(void);
	void			SetTexture(int nPatternAnim, int nPatternX, int nPatternY);

	void			PlayerBulletUpdate(int nID);
	void			EnemyBulletUpdate(int nID);
	void			WaterImpactUpdate(int nID);
	void			ExplosionUpdate(int nID);

	void			Set(USER_TYPE User_Type, D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
	void			ReSet(int nID);
	CBullet_Data	*GetBulletData(void) { return &m_Bullet[0]; };
	bool			*GetFlag(void) { return &m_Bullet[0].Flag; };
	D3DXVECTOR3		*GetPos(void) { return &m_Bullet[0].Pos; };

private:
	CBullet_Data			m_Bullet[nBullet_Max];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;			//  ���_�o�b�t�@�ւ̃|�C���^
	LPCSTR					m_TextureFile;			//  �e�N�X�`���t�@�C��
	LPDIRECT3DTEXTURE9		m_TextureBuffer;		//  �e�N�X�`���ւ̃|�C���^
	int						m_ShotFrame;
	float					m_Gravity;
	float					m_Distance;
	D3DXVECTOR2				m_Size;
	CPlayer					*m_Player;
	CFunc					*m_Func;
	CWater					*m_Water;
	CEffect					*m_Effect;
};

#endif