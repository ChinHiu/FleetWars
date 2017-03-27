//------------------------------------------------------------------------------
//	タイトル：		弾のヘッダー
//	ファイル名：	bullet.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/19
//------------------------------------------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CPlayer;
class CWater;
class CEffect;

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------
const int	nBullet_Max = 50;
const float	fBullet_Speed_Player = 50.0f;
const float	fBullet_Speed_Enemy = 30.0f;

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define PLAYER_SHOT_TEXTURE_FILE	"./data/TEXTURE/Bullet/Shot.png"

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  バレットデータクラス
class CBullet_Data
{
public:
	D3DXVECTOR3 Pos;			//  現在の位置
	D3DXVECTOR3	OriginalPos;	//  元の位置
	D3DXVECTOR3	TargetPos;		//  ターゲットの位置
	D3DXVECTOR3	Rot;			//  回転
	D3DXVECTOR2	Size;			//  サイズ
	D3DXVECTOR3	Vector;			//  原点から目的地までのベクトル
	D3DXVECTOR3	Scl;			//  拡大縮小
	CMatrix		Matrix;			//  マトリックス
	D3DXMATRIX	ViewMatrix;		//  ビューマトリックス
	int			Life;			//  ライフ
	float		Speed;			//  移動速度
	bool		Flag;			//  trueは使用、falseは未使用
	bool		CheckSea;		//  trueだと海と当たり
	USER_TYPE	UserType;		//  使用者
	float		Gravity;		//  重力
	int			FlyTime;		//  飛ぶ時間
	int			FlyTimeHalf;	//  飛ぶ時間 / 2 
	bool		bGravityInvert; //  重力反転フラグ
	float		Distance;		//	ターゲットまでの距離

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

//  バレットクラス
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
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffer;			//  頂点バッファへのポインタ
	LPCSTR					m_TextureFile;			//  テクスチャファイル
	LPDIRECT3DTEXTURE9		m_TextureBuffer;		//  テクスチャへのポインタ
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