//------------------------------------------------------------------------------
//	タイトル：		マネージャーのヘッダー
//	ファイル名：	manager.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/19
//------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "renderer.h"
#include "game.h"

//------------------------------------------------------------------------------
//	前方宣言
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
//	const定義
//------------------------------------------------------------------------------

//  ローディング時間を短縮するため各Texture、xファイルの最大数定義
const int nLoadUI = 33;						//  UIテクスチャの数
const int nLoadSkybox = 6;					//  Skyboxテクスチャの数
const int nLoadEffectTex = 9;				//  effectテクスチャの数
const int nLoadModel = 4;					//  モデルの数
const int nLoadModelTexPattern = 2;			//  モデルテクスチャタイプの数（ノーマルと破損）

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  モデルパーツ
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

//  モデルタイプ
typedef enum
{
	MODEL_NONE = -1,
	MODEL_FAST,
	MODEL_GORSHKOV,
	MODEL_HAMINA,
	MODEL_MISSILE
}MODEL_TYPE;

//  エフェクトタイプ
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
//	クラス定義
//------------------------------------------------------------------------------

//  モデルデータクラス
class CModel_Data
{
public:
	LPD3DXMESH			Mesh;			//  メッシュ情報へのポインタ
	LPD3DXBUFFER		BufferMat;		//  マテリアル情報へのポインタ
	DWORD				NumMat;			//  マテリアル数

	CModel_Data()
		: Mesh(NULL)
		, BufferMat(NULL)
		, NumMat(NULL)
	{};
};

//  マネージャークラス
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

	//  取得関数
	static CRenderer			*GetRenderer(void);												//  レンダラを取得
	static CInput				*GetInput(void);												//  DirectInputを取得
	static CMode				*GetMode(void);													//  シーンモードを取得
	static CFade				*GetFade(void);													//  フェードを取得
	static CFunc				*GetFunc(void);													//  関数を取得
	static CCamera_Data			*GetCameraData(void);											//  カメラデータを取得
	static CPlayer				*GetPlayer(void);												//  プレイヤーを取得
	static CMeshField			*GetSea(void);													//  海を取得
	static CUI					*GetUI(void);													//  UIを取得
	static CBullet				*GetBullet(void);												//  弾を取得
	static COpenAL				*GetOpenAL(void);												//  OpenALを取得
	static CWater				*GetWater(void);												//  Waterを取得
	static CEffect				*GetEffect(void);												//  エフェクトを取得
	static CEnemy_Hamina		*GetHamina(void);												//  Hamina敵を取得
	static CMissile				*GetMissile(void);												//  ミサイルを取得
	static CUserMap				*GetUserMap(void);												//  ユーザーマップを取得
	static CSprayBehide			*GetSprayBehide(void);											//  水飛沫（後ろ）を取得

	static int					*GetClearTime(void) { return &m_ClearTime; };
	static int					*GetKillsNum(void) { return &m_KillsNum; };
	static int					*GetPlayerDamage(void) { return &m_Damage; };
	static bool					*GetMissionResult(void) { return &m_bMissionResult; };

	static LPDIRECT3DTEXTURE9	GetUITextureBuffer(int nType);									//  UIテクスチャバッファを取得
	static LPDIRECT3DTEXTURE9	GetSkyboxTextureBuffer(int nID);								//  スカイボックステクスチャバッファを取得
	static LPDIRECT3DTEXTURE9	GetModelTextureBuffer(MODEL_TYPE Model_Type, bool bBroken);		//  モデルテクスチャバッファを取得
	static LPDIRECT3DTEXTURE9	GetEffectTextureBuffer(EFFECT_TYPE Effect_Type);				//  //  エフェクトテクスチャバッファを取得
	static CModel_Data			*GetModeData(MODEL_PARTS Model_Parts);							//  モデルデータを取得

	//  セット関数
	static void					SetMode(CMode *pMode);											//  シーンモードを設定
	static void					SetCameraData(CCamera_Data *pCamera_Data);						//  カメラデータを設定
	static void					SetPlayer(CPlayer *pPlayer);									//  プレイヤーを設定
	static void					SetSea(CMeshField *pSea);										//  海を設定
	static void					SetUI(CUI *pUI);												//  UIを設定
	static void					SetBullet(CBullet *pBullet);									//  弾を設定
	static void					SetOpenAL(COpenAL *pOpenAL);									//  OpenALを設定
	static void					SetWater(CWater *pWater);										//  Waterを設定
	static void					SetEffect(CEffect *pEffect);									//  エフェクトを設定
	static void					SetHamina(CEnemy_Hamina *pEnemyHamina);							//  Hamina敵を設定
	static void					SetMissile(CMissile *pMissile);									//  ミサイルを設定
	static void					SetUserMap(CUserMap *pUserMap);									//  ユーザーマップを設定
	static void					SetSprayBehide(CSprayBehide *pSprayBehide);						//  水飛沫（後ろ）を設定

	static void					AddKillsNum(int nNum) { m_KillsNum += nNum; };
	static void					SetKillsNum(int nNum) { m_KillsNum = nNum; };
	static void					SetClearTime(int nTime) { m_ClearTime = nGameTime - nTime; };
	static void					SetPlayerDamage(int nLife) { m_Damage = 100 - nLife; };
	static void					SetMissionResult(bool bFlag) { m_bMissionResult = bFlag; };

private:				
	static CRenderer			*m_Renderer;													//  レンダラ
	static CInput				*m_Input;														//  DirectInput
	static CDebugProc			*m_DebugProc;													//  デバッグプロシージャ
	static COpenAL				*m_OpenAL;														//  OpenAL
	static CMode				*m_Mode;														//  シーンモード
	static CFade				*m_Fade;														//  フェード
	static CFunc				*m_Func;														//  関数
	static CUI					*m_UI;															//  UI
	static CBullet				*m_Bullet;														//  弾
	static CCamera_Data			*m_CameraData;													//  カメラデータ
	static CPlayer				*m_Player;														//  プレイヤー
	static CMeshField			*m_Sea;															//  海
	static CWater				*m_Water;														//  水
	static CEffect				*m_Effect;														//  エフェクト
	static CEnemy_Hamina		*m_Hamina;														//  Hamina敵
	static CMissile				*m_Missile;														//  ミサイル
	static CUserMap				*m_UserMap;														//  ユーザーマップ
	static CSprayBehide			*m_SprayBehide;													//  水飛沫（後ろ）

	static int					m_ClearTime;
	static int					m_KillsNum;
	static int					m_Damage;
	static bool					m_bMissionResult;

	//  ローディング時間を短縮するための変数
	static LPDIRECT3DTEXTURE9	m_UITextureBuffer[nLoadUI];										//  テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_SkyboxTextureBuffer[nLoadSkybox];								//  テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_EffectTextureBuffer[nLoadEffectTex];							//  テクスチャへのポインタ
	static LPDIRECT3DTEXTURE9	m_ModelTextureBuffer[nLoadModel][nLoadModelTexPattern];			//  テクスチャへのポインタ
	static CModel_Data			*m_ModelData;													//  モデルデータ
};

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
#endif