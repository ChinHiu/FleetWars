//------------------------------------------------------------------------------
//	タイトル：		playerのヘッダー
//	ファイル名：	player.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/12/13
//------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"
#include "sprayBefore.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CModel;
class CObb;
class CObbTest;
class CStencilShadow;
class CSpray;
class CSprayBehide;

//------------------------------------------------------------------------------
//	const定義
//------------------------------------------------------------------------------
const int nMissileMax_P = 4;			//  プレイヤーミサイル最大数
const int nObbMax_P = 4;				//  プレイヤーObb最大数
const float fOverHitMax_P = 1.0f;		//  プライヤーオーバーヒット最大数

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  プレイヤーモデルパーツ
typedef enum
{
	PLAYER_BODY = 0,
	PLAYER_BATTERY,
	PLAYER_GUN,
	PLAYER_PARTS_MAX
}PLAYER_PARTS;

//  武器タイプ
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
//	クラス定義
//------------------------------------------------------------------------------
class CPhysics_Data
{
public:
	D3DXVECTOR3		TargetDirectVector;
	D3DXVECTOR3		PosVector;
	float			DirectVectorAngle;			//  targetとownの方向ベクトルなす角
	float			VectorAngle;				//  targetからown座標のベクトルとtarget方向ベクトルのなす角
	D3DXVECTOR3		RelativeBearing;			//	targetを基準に、ownの左右位置(左+、右-)	

	CPhysics_Data()
		: DirectVectorAngle(0)
		, VectorAngle(0)
		, RelativeBearing(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{}
};

//  シーンクラス
class CPlayer : public CScene
{
private:
	CMatrix			m_Matrix;									//  マトリックス
	MODEL_TYPE		m_Type;										//  モデルタイプ
	CModel			*m_Model[PLAYER_PARTS_MAX];					//  モデル（パーツ分）
	CCharacter_Data	m_CharData;									//  基本データ
	CStencilShadow	*m_Shadow;									//  シャドウ
	WEAPON_TYPE		m_Weapon;									//  現在の武器タイプ
	int				m_WeaponID;									//  武器選択用係数
	CWeapon_Data	m_WeaponData[WEAPON_TYPE_MAX];				//  武器データ（武器数分）
	int				m_PowerNum;									//  エンジンパワーナンバー（パワーのUIを描画用）
	int				m_SpeedNum;									//  スピードナンバー（スピードのUIを描画用）
	int				m_AimSpeedNum;								//  目標スピードナンバー（計算用）
	float			m_OverHitRate;								//  オーバーヒット割合
	bool			m_bFire;									//  連射中かどうか？
	int				m_BulletCnt;								//  戦艦砲の射撃カウント（Frame単位）
	int				m_MissileCnt;								//  ミサイルの射撃カウント（Frame単位）
	D3DXVECTOR3		m_BatteryRot;								//  砲台回転
	D3DXVECTOR3		m_ObbRelativePos[nObbMax_P];				//  相対移動量
	D3DXVECTOR3		m_ObbLength[nObbMax_P];						//  Obb各軸の長さ
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