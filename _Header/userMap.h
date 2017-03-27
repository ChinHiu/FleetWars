//------------------------------------------------------------------------------
//	タイトル：		ユーザーマップ処理のヘッダー
//	ファイル名：	userMap.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/07/19
//------------------------------------------------------------------------------
#ifndef _USERMAP_H_
#define _USERMAP_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"
#include "player.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
const int nUserMapMax = 64;

//  ユーザーマップタイプ
typedef enum {
	USERMAP_NONE = -1,
	RADAR_BACKGROUNG,		//  レーダー背景
	BULLET_LIMITS,			//  ガトリング砲射程
	MISSILE_LIMITS,			//  ミサイル射程
	JAMMING_LIMITS,			//  ジャミング弾射程
	RADAR_SENSOR,			//  レーダーセンサー
	RADAR_LIMITS,			//  レーダー範囲
	PLAYER,					//  プレイヤー
	USERMAP_MISSILE,		//  ボス
	ENEMY,					//  敵軍
	RADAR_FRAME,			//  レーダー枠
	USERMAP_TYPE_MAX
}USERMAP_TYPE;

//  ユーザーマップデータクラス
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

//  センサーデータクラス
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

//  ユーザーマップクラス
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