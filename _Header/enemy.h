//------------------------------------------------------------------------------
//	タイトル：		enemyのヘッダー
//	ファイル名：	enemy.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/12/13
//------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"
#include "sprayBefore.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
const int nHamina_Max = 8;
const int nHamina_Obb_Max = 5;
//#define HAMINA_LIFE (100.0f)
//#define HAMINA_OBB_MAX (5)

typedef enum {
	HAMINA_BODY = 0,
	HAMINA_BATTERY,
	HAMINA_GUN,
	HAMINA_PARTS_MAX
}HAMINA_PARTS;

typedef enum {
	HAMINA_SHIP_GUN = 0,
	HAMINA_MISSILE,
	HAMINA_WEAPON_MAX
}HAMINA_WEAPON;

typedef enum {
	HAMINA_AI_NONE = -1,
	HAMINA_LEFT_LEADER,
	HAMINA_LEFT_NORMAL1,
	HAMINA_LEFT_NORMAL2,
	HAMINA_RIGHT_LEADER,
	HAMINA_RIGHT_NORMAL1,
	HAMINA_RIGHT_NORMAL2,
	HAMINA_RAND,
	HAMINA_AI_MAX
}HAMINA_AI_TYPE;

typedef enum {
	HAMINA_STATE_NONE = -1,
	HAMINA_MOVE,
	HAMINA_TURN_LEFT,
	HAMINA_TURN_RIGHT,
	HAMINA_DEAD,
	HAMINA_STATE_MAX
}HAMINA_STATE;

//  前方宣言
class CModel;
class CSpray;
class CStencilShadow;
class CObbTest;
class CPlayer;


class CHamina_Data
{
public:
	CMatrix			Matrix;									//  マトリックス
	CModel			*Model[HAMINA_PARTS_MAX];				//  モデル（パーツ分）
	CCharacter_Data	CharData;								//  基本データ
	CStencilShadow	*Shadow;								//  シャドウ
	CWeapon_Data	WeaponData[HAMINA_WEAPON_MAX];			//  武器データ（武器数分）
	HAMINA_STATE	State;
	D3DXVECTOR3		BatteryRot;								//  砲台回転
	D3DXVECTOR3		ObbRelativePos[nHamina_Obb_Max];		//  相対移動量
	D3DXVECTOR3		ObbLength[nHamina_Obb_Max];				//  Obb各軸の長さ
	CObb			Obb[nHamina_Obb_Max];					//  Obb
	CObbTest		*ObbTest[nHamina_Obb_Max];				//  ObbTest
	HAMINA_AI_TYPE	AIType;
	float			fDistance;
	D3DXVECTOR3		VectorToPlayer;
	float			fMoveRot;
	D3DXVECTOR3		AimPos;
	bool			bUserMap;
	bool			*bLock;

	CSpray			*SprayBefore;
	D3DXVECTOR3		SprayBeforeSize;
	D3DXVECTOR3		SprayBeforePos[SPRAY_TYPE_MAX];
	D3DXVECTOR3		SprayBehideSize;
	D3DXVECTOR3		SprayBehidePos;

	bool			bCollision;

	int				MissileID;

	int				GunCnt;
	bool SetLock(bool *bFlag) { bLock = bFlag; };
	void AddLife(int nNum) { CharData.nLife += nNum; };

	CHamina_Data()
	{
		for (int i = 0; i < HAMINA_PARTS_MAX; i++)
		{
			Model[i] = NULL;
		}
		Shadow = NULL;
		BatteryRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		State = HAMINA_STATE_NONE;
		AIType = HAMINA_AI_NONE;
		fDistance = 0.0f;
		bUserMap = false;
		bLock = false;
		SprayBefore = NULL;
		SprayBeforeSize =
		SprayBeforePos[SPRAY_BEFORE_LEFT] =
		SprayBeforePos[SPRAY_BEFORE_RIGHT] =
		SprayBehideSize =
		SprayBehidePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bCollision = false;
		GunCnt = 0;
	}
};

//  シーンクラス
class CEnemy_Hamina : public CScene
{
private:
	MODEL_TYPE					m_Type;
	LPCSTR						*m_ModelFile;
	CHamina_Data				m_Hamina[nHamina_Max];
	D3DXVECTOR3					m_MissileDeviationPos;

	CPlayer						*m_Player;
	HAMINA_STATE				m_LeftLeaderState;
	HAMINA_STATE				m_RightLeaderState;

public:
	CEnemy_Hamina(int nPriority = 2, OBJECT_TYPE Object_Type = OBJTYPE_PLAYER);
	~CEnemy_Hamina();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetModelFile(MODEL_TYPE Model_Type);
	static CEnemy_Hamina *Create(void);
	void	Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, HAMINA_AI_TYPE AI_Type);
	CHamina_Data *GetHaminaData(void);
	void MatrixUpdate(int nID);
	void ObbUpdate(int nID);

};

#endif