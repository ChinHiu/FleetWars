//------------------------------------------------------------------------------
//	�^�C�g���F		���[�U�[�}�b�v�����̃w�b�_�[
//	�t�@�C�����F	userMap.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/07/19
//------------------------------------------------------------------------------
#ifndef _USERMAP_H_
#define _USERMAP_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "scene.h"
#include "player.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
const int nUserMapMax = 64;

//  ���[�U�[�}�b�v�^�C�v
typedef enum {
	USERMAP_NONE = -1,
	RADAR_BACKGROUNG,		//  ���[�_�[�w�i
	BULLET_LIMITS,			//  �K�g�����O�C�˒�
	MISSILE_LIMITS,			//  �~�T�C���˒�
	JAMMING_LIMITS,			//  �W���~���O�e�˒�
	RADAR_SENSOR,			//  ���[�_�[�Z���T�[
	RADAR_LIMITS,			//  ���[�_�[�͈�
	PLAYER,					//  �v���C���[
	USERMAP_MISSILE,		//  �{�X
	ENEMY,					//  �G�R
	RADAR_FRAME,			//  ���[�_�[�g
	USERMAP_TYPE_MAX
}USERMAP_TYPE;

//  ���[�U�[�}�b�v�f�[�^�N���X
class CUserMap_Data {
public:
	D3DXVECTOR2		Pos;
	D3DXVECTOR2		Size;
	USERMAP_TYPE	Type;
	D3DXCOLOR		Col;
	bool			Flag;

	CUserMap_Data()
		: Pos(D3DXVECTOR2(0.0f, 0.0f))
		, Size(D3DXVECTOR2(0, 0))
		, Type(USERMAP_NONE)
		, Col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
		, Flag(false)
	{}
};

//  �Z���T�[�f�[�^�N���X
class CSensor_Data {
public:
	D3DXVECTOR2		Pos[3];
	D3DXVECTOR2		Size;
	float			Length;
	float			Angle;
	float			Rot;
	CSensor_Data()
		: Length(0.0f)
		, Angle(0.0f)
		, Rot(0.0f)
	{
		Pos[0] = Pos[1] = Pos[2] = D3DXVECTOR2(0.0f, 0.0f);
	}
};

//  ���[�U�[�}�b�v�N���X
class CUserMap : public CScene
{
private:
	CUserMap_Data			m_UserMap[nUserMapMax];
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;
	LPDIRECT3DTEXTURE9		m_TextureBuffer[USERMAP_TYPE_MAX];
	D3DXVECTOR2				m_SizeRate;
	CSensor_Data			m_Sensor;
	float					m_TexSensorLength;
	float					m_TexSensorAngle;
	float					m_WeaponLimitsAngle;
	float					*m_CameraRotY;
	float					*m_PlayerRotY;
	WEAPON_TYPE				*m_WeaponType;

public:
	CUserMap(int nPriority = 4, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CUserMap();
	void		Init(void);
	void		Uninit(void);
	void		Update(void);
	void		Draw(void);
	HRESULT		MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void		SetVertex(int nID);
	static		CUserMap *Create(void);
	void		Set(int *nID, D3DXVECTOR2 pos, USERMAP_TYPE type);
	int			SensorCheck(bool *check, D3DXVECTOR3 pos, USERMAP_TYPE type);
	bool		GetUserMapFlag(int nID);
	D3DXVECTOR2 *GetUserMapPos(void);
};

#endif