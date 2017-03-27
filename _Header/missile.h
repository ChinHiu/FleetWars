//------------------------------------------------------------------------------
//	タイトル：		ミサイルのヘッダー
//	ファイル名：	missile.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/03
//------------------------------------------------------------------------------
#ifndef _MISSILE_H_
#define _MISSILE_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define MISSILE_MAX				(256)

typedef enum{
	MISSILE_STATE_NONE = -1,
	MISSILE_READY,
	MISSILE_RISE,
	MISSILE_PURSUIT,
	MISSILE_EXPLOSION,
	MISSILE_STATE_MAX
}MISSILE_STATE;

//  ミサイルデータのクラス
class CMissile_Data
{
public:
	D3DXVECTOR3		Pos;			//  現在の位置
	D3DXVECTOR3		RandPos;
	D3DXVECTOR3		*TargetPos;		//  ターゲットの位置へのポインタ
	D3DXVECTOR3		*ShipPos;		//  船の位置へのポインタ
	D3DXVECTOR3		*ShipRot;		//  船の回転へのポインタ
	bool			*ShipFlag;		//  船のフラグへのポインタ
	D3DXVECTOR3		DeviationPos;	//  位置の偏移量
	float			DeviationRot;	//  偏移量の角度
	float			Radius;
	D3DXVECTOR3		Rot;			//  現在の回転
	D3DXVECTOR3		GoalRot;		//  目標回転
	D3DXVECTOR3		Vector;			//  原点から目的地までのベクトル
	D3DXVECTOR3		Scl;			//  拡大縮小
	CMatrix			Matrix;			//  マトリックス
	int				Life;			//  ライフ
	float			Speed;			//  移動速度
	float			Gravity;		//  重力
	float			Distance;
	bool			Flag;			//  trueは使用、falseは未使用
	bool			CheckSea;		//  trueだと海と当たり
	USER_TYPE		UserType;		//  使用者
	MISSILE_STATE	State;			//  状態
	bool			bUserMap;
	int				LockShipID;
	D3DXMATRIX		*ShipMatrix;
	bool			bParent;

	CMissile_Data()
		: Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, TargetPos(NULL)
		, ShipPos(NULL)
		, ShipRot(NULL)
		, DeviationPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, DeviationRot(0.0f)
		, Radius(0.0f)
		, Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, GoalRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Vector(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		, Scl(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
		, Life(3)
		, Speed(0.0f)
		, Gravity(0.0f)
		, Distance(0.0f)
		, Flag(false)
		, CheckSea(false)
		, UserType(USER_NONE)
		, State(MISSILE_STATE_NONE)
		, bUserMap(false)
	{}

	void SetFlag(bool bFlag) { Flag = bFlag; }
	void SetDamage(int nDamage) { Life -= nDamage; }
	void SetLockShipID(int nID) { LockShipID = nID; };
};

//  ミサイルクラス
class CMissile : public CScene
{
private:
	CMissile_Data			m_Missile[MISSILE_MAX];
	CModel					*m_Model;

public:
	CMissile(int nPriority = 2, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CMissile();
	void	Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	static	CMissile *Create(void);
	void	Set(D3DXVECTOR3 *TargetPos, int nID);
	int		Reset(D3DXMATRIX *ShipMatrix, USER_TYPE User_Type, D3DXVECTOR3 *ShipPos, D3DXVECTOR3 *ShipRot, bool *bShipFlag, D3DXVECTOR3 DeviationPos);
	CMissile_Data *GetMissileData(void);
	void	MissileDataInit(void);
};

#endif