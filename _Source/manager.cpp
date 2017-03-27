//------------------------------------------------------------------------------
//	タイトル：		マネージャの関数
//	ファイル名：	manager.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/09
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "Func.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "debugProc.h"
#include "openAL.h"
#include "mode.h"
#include "camera.h"
#include "fade.h"
#include "player.h"
#include "meshField.h"
#include "water.h"
#include "effect.h"
#include "enemy.h"
#include "missile.h"
#include "userMap.h"
#include "sprayBehide.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------

//  UIテクスチャファイルパス
const LPCSTR g_UITexture[] =
{
	{ "./data/TEXTURE/UI/TITLE/Title_Mark.png" },
	{ "./data/TEXTURE/UI/TITLE/Start_Mark.png" },
	{ "./data/TEXTURE/UI/TITLE/Exit_Mark.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Scope.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/UserMapEX.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Frame.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Keyboard.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Skip.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_0.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_1.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_2.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_3.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_4.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_5.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_6.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_7.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_8.png" },
	{ "./data/TEXTURE/UI/TUTORIAL/Tutorial_Description_9.png" },
	{ "./data/TEXTURE/UI/GAME/Weapon_Mark/Weapon_Bullet.png" },
	{ "./data/TEXTURE/UI/GAME/Weapon_Mark/Weapon_Missile.png" },
	{ "./data/TEXTURE/UI/GAME/Weapon_Mark/Weapon_Repair.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Heat.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Infinity.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Overheat.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Power.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Speed.png" },
	{ "./data/TEXTURE/UI/GAME/Other/HP_Frame.png" },
	{ "./data/TEXTURE/UI/GAME/Other/HP.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Mission_Complete.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Mission_Failed.png" },
	{ "./data/TEXTURE/UI/GAME/Other/Mission_Start.png" },
	{ "./data/TEXTURE/UI/RESULT/Result_Frame.png" },
	{ "./data/TEXTURE/UI/RESULT/Result_Rank.png" },
	{ "./data/TEXTURE/UI/RESULT/Result_Thanks.png" },
	{ "./data/TEXTURE/UI/RESULT/Clear_Failed.png" },
};

//  スカイボックステクスチャファイルパス
const LPCSTR g_SkyTexture[] =
{
	{ "./data/TEXTURE/SkyBox/Up.png" },
	{ "./data/TEXTURE/SkyBox/Left.png" },
	{ "./data/TEXTURE/SkyBox/Front.png" },
	{ "./data/TEXTURE/SkyBox/Right.png" },
	{ "./data/TEXTURE/SkyBox/Back.png" },
	{ "./data/TEXTURE/SkyBox/Down.png" },
};

// エフェクトテクスチャファイルパス
const LPCSTR g_EffectTexture[] =
{
	{ "./data/TEXTURE/EffectAnimation/WaterFall_00_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/WaterFall_01_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/WaterFall_02_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/Water_Impact_8_4.png" },
	{ "./data/TEXTURE/EffectAnimation/Spray_Before_4_8.png" },
	{ "./data/TEXTURE/EffectAnimation/Spray_Behide_8_2.png" },
	{ "./data/TEXTURE/EffectAnimation/Shot_Fire_2_2.png" },
	{ "./data/TEXTURE/EffectAnimation/Explosion_8_6.png" },
	{ "./data/TEXTURE/EffectAnimation/Explosion_8_4.png" },
};

//  モデルテクスチャファイルパス
const LPCSTR g_ModelTexture[nLoadModel][nLoadModelTexPattern] =
{
	{
		{ "./data/TEXTURE/SHIP/Fast_Normal.tga" },
		{ "./data/TEXTURE/SHIP/Fast_Broken.tga" },
	},

	{
		{ "./data/TEXTURE/SHIP/Gorshkov_Normal.tga" },
		{ "./data/TEXTURE/SHIP/Gorshkov_Broken.tga" },
	},

	{
		{ "./data/TEXTURE/SHIP/Hamina_Normal.tga" },
		{ "./data/TEXTURE/SHIP/Hamina_Broken.tga" },
	},

	{
		{ "./data/TEXTURE/WEAPON/Missile.tga" },
		{ NULL },
	}

};

//  モデルチャファイルパス
const LPCSTR g_ModelFile[] =
{
	{ "./data/MODEL/SHIP/Hamina_Fast.x" },

	{ "./data/MODEL/SHIP/Hamina_Body.x" },
	{ "./data/MODEL/SHIP/Hamina_Battery.x" },
	{ "./data/MODEL/SHIP/Hamina_Gun.x" },

	{ "./data/MODEL/SHIP/Gorshkov_Body.x" },
	{ "./data/MODEL/SHIP/Gorshkov_Battery.x" },
	{ "./data/MODEL/SHIP/Gorshkov_Gun.x" },

	{ "./data/MODEL/WEAPON/Missile.x" }
};

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------
CRenderer			*CManager::m_Renderer;
CInput				*CManager::m_Input;
CDebugProc			*CManager::m_DebugProc;
COpenAL				*CManager::m_OpenAL;
CMode				*CManager::m_Mode;
CFunc				*CManager::m_Func;
CCamera_Data		*CManager::m_CameraData;
CFade				*CManager::m_Fade;
CPlayer				*CManager::m_Player;
CMeshField			*CManager::m_Sea;
CUI					*CManager::m_UI;
CBullet				*CManager::m_Bullet;
CWater				*CManager::m_Water;
CEffect				*CManager::m_Effect;
CEnemy_Hamina		*CManager::m_Hamina;
CMissile			*CManager::m_Missile;
CUserMap			*CManager::m_UserMap;
CSprayBehide		*CManager::m_SprayBehide;

int					CManager::m_ClearTime;
int					CManager::m_KillsNum;
int					CManager::m_Damage;
bool				CManager::m_bMissionResult;

//  ローディング軽量化のため、テクスチャバッファをマネージャーで管理
LPDIRECT3DTEXTURE9	CManager::m_UITextureBuffer[nLoadUI];
LPDIRECT3DTEXTURE9	CManager::m_SkyboxTextureBuffer[nLoadSkybox];
LPDIRECT3DTEXTURE9	CManager::m_EffectTextureBuffer[nLoadEffectTex];
LPDIRECT3DTEXTURE9	CManager::m_ModelTextureBuffer[nLoadModel][nLoadModelTexPattern];
CModel_Data			*CManager::m_ModelData;

//------------------------------------------------------------------------------
//	関数名:	CManager::CManager()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CManager::CManager()
{
	m_Renderer		= NULL;
	m_Input			= NULL;
	m_DebugProc		= NULL;
	m_OpenAL		= NULL;
	m_Mode			= NULL;
	m_Func			= NULL;
	m_Bullet		= NULL;

	memset(m_UITextureBuffer, NULL, sizeof(m_UITextureBuffer));		
	memset(m_SkyboxTextureBuffer, NULL, sizeof(m_SkyboxTextureBuffer));
	memset(m_EffectTextureBuffer, NULL, sizeof(m_EffectTextureBuffer));
	memset(m_ModelTextureBuffer, NULL, sizeof(m_ModelTextureBuffer));

	m_ClearTime = 0;
	m_KillsNum = 0;
	m_Damage = 0;
}

//------------------------------------------------------------------------------
//	関数名:	CManager::~CManager()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CManager::~CManager()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CManager::Init
//	引数:	HINSTANCE hInstance, HWND hWnd, BOOL bWindow
//	戻り値: なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
//  インスタンス生成
	m_Renderer			= new CRenderer;				//  レンダラ
	m_Input				= new CInput;					//  DirectInput
#ifdef _DEBUG
	m_DebugProc			= new CDebugProc;				//  デバッグプロシージャ
#endif
	m_OpenAL			= new COpenAL;					//  OPenAL
	m_Mode				= new CTitle;					//  シーンモード
	m_ModelData			= new CModel_Data[MODEL_MAX];	//  モデルデータ
	m_Fade				= new CFade;					//  フェード
	m_Func				= new CFunc;					//  関数

	//  レンダラの初期化
	m_Renderer->Init(hInstance, hWnd, bWindow);

	//	入力の初期化
	m_Input->Init(hInstance, hWnd);

	//  フェードの初期化
	m_Fade->Init();

	//  ゲームオール初期化
	m_Mode->Init();

#ifdef _DEBUG
	//  デバッグプロシージャの初期化処理
	m_DebugProc->Init();
#endif

	//  ローディング時間を削減
	LoadingReduction();
}

//------------------------------------------------------------------------------
//	関数名:	void CManager::Uninit
//	引数:	なし
//	戻り値: なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CManager::Uninit(void)
{
	//  レンダラの終了
	m_Renderer->Uninit();

#ifdef _DEBUG
	//  デバッグプロシージャの終了
	m_DebugProc->Uninit();
#endif

	//  ゲームオールの終了
	m_Mode->Uninit();

	//  フェードの終了
	m_Fade->Uninit();

	//  入力の終了
	m_Input->Uninit();

	//  OpenALの終了
	m_OpenAL->Uninit();

	//  UIテクスチャバッファを解放
	for (int i = 0; i < nLoadUI; i++)
	{
		SAFE_RELEASE(m_UITextureBuffer[i]);
	}

	//  Skyboxテクスチャバッファを解放
	for (int i = 0; i < nLoadSkybox; i++)
	{
		SAFE_RELEASE(m_SkyboxTextureBuffer[i]);
	}

	//  Effectテクスチャバッファを解放
	for (int i = 0; i < nLoadEffectTex; i++)
	{
		SAFE_RELEASE(m_EffectTextureBuffer[i]);
	}

	//  Modelテクスチャバッファを解放
	for (int x = 0; x < nLoadModel; x++)
	{
		SAFE_RELEASE(m_ModelData[x].BufferMat);
		SAFE_RELEASE(m_ModelData[x].Mesh);
		m_ModelData[x].NumMat = NULL;
		for (int y = 0; y < nLoadModelTexPattern; y++)
		{
			SAFE_RELEASE(m_ModelTextureBuffer[x][y]);
		}
	}

	//  インスタンス削除
	delete m_Renderer;
	delete m_Mode;
	delete m_Input;
	delete m_OpenAL;
	delete[] m_ModelData;
	delete m_Func;
#ifdef _DEBUG
	delete m_DebugProc;
#endif
}

//------------------------------------------------------------------------------
//	関数名:	void CManager::Update
//	引数:	なし
//	戻り値: なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CManager::Update()
{
	CKeyboard	*keyboard	= CManager::GetInput()->GetKeyboard();
	CMouse		*mouse = CManager::GetInput()->GetMouse();

	//  レンダラの更新
	m_Renderer->Update();

	//  入力の更新
	m_Input->Update();

	//  ゲームオールの更新
	m_Mode->Update();

	//  フェードの更新
	m_Fade->Update();

#ifdef _DEBUG
	//  デバッグプロシージャの更新処理
	m_DebugProc->Update();
#endif
}

//------------------------------------------------------------------------------
//	関数名:	void CManager::Draw
//	引数:	なし
//	戻り値: なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CManager::Draw(void)
{
	//  デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

//  レンダラの開始
	m_Renderer->Begin();

	//  ゲームオールの描画
	m_Mode->Draw();

	//  フェードの描画
	m_Fade->Draw();
#ifdef _DEBUG
	//  デバッグプロシージャの描画
	m_DebugProc->Draw();
#endif

//  レンダラの終了
	m_Renderer->End();
}

//------------------------------------------------------------------------------
//	関数名:	void CManager::LoadingReduction
//	引数:	なし
//	戻り値:	なし
//	説明:	ローディング時間を削減するため、全て描画に関するデータを読み込む。
//			モードごとに必要なデータ分ではなく、メモリーの最適化ではない。
//------------------------------------------------------------------------------
void CManager::LoadingReduction(void)
{
	//  UIテクスチャ
	for (int i = 0; i < nLoadUI; i++) {
		//  テクスチャの読み込み
		D3DXCreateTextureFromFile
		(
			m_Renderer->GetDevice(),
			g_UITexture[i],								//  テクスチャファイル位置
			&m_UITextureBuffer[i]						//  テクスチャバッファへのポインタ
		);
	}

	//  Skyboxテクスチャ
	for (int i = 0; i < nLoadSkybox; i++)
	{
		//  テクスチャの読み込み
		D3DXCreateTextureFromFile(
			m_Renderer->GetDevice(),
			g_SkyTexture[i],							//  テクスチャファイル位置
			&m_SkyboxTextureBuffer[i]					//  テクスチャバッファへのポインタ
		);
	}

	//  エフェクトアニメーションテクスチャ
	for (int i = 0; i < nLoadEffectTex; i++)
	{
		//  テクスチャの読み込み
		D3DXCreateTextureFromFile(
			m_Renderer->GetDevice(),
			g_EffectTexture[i],							//  テクスチャファイル位置
			&m_EffectTextureBuffer[i]					//  テクスチャバッファへのポインタ
		);
	}

	//  モデルテクスチャ
	for (int x = 0; x < nLoadModel; x++)
	{
		for (int y = 0; y < nLoadModelTexPattern; y++)

			//  テクスチャの読み込み
			D3DXCreateTextureFromFile(
				m_Renderer->GetDevice(),
				g_ModelTexture[x][y],					//  テクスチャファイル位置
				&m_ModelTextureBuffer[x][y]				//  テクスチャバッファへのポインタ
			);
	}

	//  モデルの情報
	for (int i = 0; i < MODEL_MAX; i++)
	{
		//  Xファイルの読み込み
		D3DXLoadMeshFromX(
			g_ModelFile[i],		//  読み込むファイル位置
			D3DXMESH_SYSTEMMEM,
			m_Renderer->GetDevice(),
			NULL,
			&m_ModelData[i].BufferMat,		//  マテリアル情報
			NULL,
			&m_ModelData[i].NumMat,			//  マテリアルの数
			&m_ModelData[i].Mesh				//  メッシュ情報
		);
	}
}

//------------------------------------------------------------------------------
//	関数名:	CRenderer *CManager::GetRenderer
//	引数:	なし
//	戻り値:	m_Renderer
//	説明:	レンダラを取得
//------------------------------------------------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	return m_Renderer;
}

//------------------------------------------------------------------------------
//	関数名:	CInput *CManager::GetInput
//	引数:	なし
//	戻り値:	m_Input
//	説明:	DirectInputを取得
//------------------------------------------------------------------------------
CInput *CManager::GetInput(void)
{
	return m_Input;
}

//------------------------------------------------------------------------------
//	関数名:	CMode *CManager::GetMode
//	引数:	なし
//	戻り値:	CMode m_Mode
//	説明:	モードを取得
//------------------------------------------------------------------------------
CMode *CManager::GetMode(void)
{
	return m_Mode;
}

//------------------------------------------------------------------------------
//	関数名:	CCamera_Data *CManager::GetCameraData
//	引数:	なし
//	戻り値:	m_CameraData
//	説明:	カメラデータを取得
//------------------------------------------------------------------------------
CCamera_Data *CManager::GetCameraData(void)
{
	return m_CameraData;
}

//------------------------------------------------------------------------------
//	関数名:	CFunc *CManager::GetFunc
//	引数:	なし
//	戻り値:	CFunc m_CollisionFunc
//	説明:	コリジョン関数を取得
//------------------------------------------------------------------------------
CFunc *CManager::GetFunc(void)
{
	return m_Func;
}

//------------------------------------------------------------------------------
//	関数名:	LPDIRECT3DTEXTURE9 CManager::GetUITextureBuffer
//	引数:	int nType
//	戻り値:	m_UITextureBuffer[nType]
//	説明:	UIテクスチャバッファを取得
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetUITextureBuffer(int nType)
{
	return m_UITextureBuffer[nType];
}

//------------------------------------------------------------------------------
//	関数名:	LPDIRECT3DTEXTURE9 CManager::GetSkyboxTextureBuffer
//	引数:	int nID
//	戻り値:	m_SkyboxTextureBuffer[nID]
//	説明:	スカイボックステクスチャバッファを取得
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetSkyboxTextureBuffer(int nID)
{
	return m_SkyboxTextureBuffer[nID];
}

//------------------------------------------------------------------------------
//	関数名:	LPDIRECT3DTEXTURE9 CManager::GetModelTextureBuffer
//	引数:	MODEL_TYPE Model_Type, bool bBroken
//	戻り値:	m_ModelTextureBuffer[Model_Type][bBroken]
//	説明:	モデルテクスチャバッファを取得
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetModelTextureBuffer(MODEL_TYPE Model_Type, bool bBroken)
{
	return m_ModelTextureBuffer[Model_Type][bBroken];
}

//------------------------------------------------------------------------------
//	関数名:	LPDIRECT3DTEXTURE9 CManager::GetEffectTextureBuffer
//	引数:	EFFECT_TYPE Effect_Type
//	戻り値:	m_EffectTextureBuffer[Effect_Type]
//	説明:	エフェクトテクスチャバッファを取得
//------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CManager::GetEffectTextureBuffer(EFFECT_TYPE Effect_Type)
{
	return m_EffectTextureBuffer[Effect_Type];
}

//------------------------------------------------------------------------------
//	関数名:	CModel_Data	*CManager::GetModeData
//	引数:	MODEL_PARTS Model_Parts
//	戻り値:	&m_ModelData[Model_Parts]
//	説明:	モデルデータを取得
//------------------------------------------------------------------------------
CModel_Data	*CManager::GetModeData(MODEL_PARTS Model_Parts)
{
	return &m_ModelData[Model_Parts];
}

//------------------------------------------------------------------------------
//	関数名:	CFade *CManager::GetFade
//	引数:	なし
//	戻り値:	m_Fade
//	説明:	フェードを取得
//------------------------------------------------------------------------------
CFade *CManager::GetFade(void)
{
	return m_Fade;
};

//------------------------------------------------------------------------------
//	関数名:	CPlayer *CManager::GetPlayer
//	引数:	なし
//	戻り値:	m_Player
//	説明:	プレイヤーを取得
//------------------------------------------------------------------------------
CPlayer *CManager::GetPlayer(void)
{
	return m_Player;
};

//------------------------------------------------------------------------------
//	関数名:	CMeshField *CManager::GetSea
//	引数:	なし
//	戻り値:	m_Sea
//	説明:	海を取得
//------------------------------------------------------------------------------
CMeshField *CManager::GetSea(void)
{
	return m_Sea;
}

//------------------------------------------------------------------------------
//	関数名:	CUI *CManager::GetUI
//	引数:	なし
//	戻り値:	m_UI
//	説明:	UIを取得
//------------------------------------------------------------------------------
CUI *CManager::GetUI(void)
{
	return m_UI;
}

//------------------------------------------------------------------------------
//	関数名:	COpenAL *CManager::GetOpenAL
//	引数:	なし
//	戻り値:	m_OpenAL
//	説明:	OpenALを取得
//------------------------------------------------------------------------------
COpenAL *CManager::GetOpenAL(void)
{
	return m_OpenAL;
}

//------------------------------------------------------------------------------
//	関数名:	CWater *CManager::GetWater
//	引数:	なし
//	戻り値:	m_Water
//	説明:	水を取得
//------------------------------------------------------------------------------
CWater *CManager::GetWater(void)
{
	return m_Water;
}

//------------------------------------------------------------------------------
//	関数名: CBullet *CManager::GetBullet
//	引数:	なし
//	戻り値:	m_Bullet
//	説明:	弾を取得
//------------------------------------------------------------------------------
CBullet *CManager::GetBullet(void)
{
	return m_Bullet;
}

//------------------------------------------------------------------------------
//	関数名: CEffect *CManager::GetEffect
//	引数:	なし
//	戻り値:	m_Effect
//	説明:	エフェクトを取得
//------------------------------------------------------------------------------
CEffect *CManager::GetEffect(void)
{
	return m_Effect;
}

//------------------------------------------------------------------------------
//	関数名: CEnemy_Hamina *CManager::GetHamina
//	引数:	なし
//	戻り値:	m_Hamina
//	説明:	Hamina敵を取得
//------------------------------------------------------------------------------
CEnemy_Hamina *CManager::GetHamina(void)
{
	return m_Hamina;
}

//------------------------------------------------------------------------------
//	関数名: CMissile *CManager::GetMissile
//	引数:	なし
//	戻り値:	m_Missile
//	説明:	ミサイルを取得
//------------------------------------------------------------------------------
CMissile *CManager::GetMissile(void)
{
	return m_Missile;
}

//------------------------------------------------------------------------------
//	関数名: CUserMap *CManager::GetUserMap
//	引数:	なし
//	戻り値:	m_UserMap
//	説明:	ユーザーマップを取得
//------------------------------------------------------------------------------
CUserMap *CManager::GetUserMap(void)
{
	return m_UserMap;
}

//------------------------------------------------------------------------------
//	関数名: CSprayBehide *CManager::GetSprayBehide
//	引数:	なし
//	戻り値:	m_SprayBehide
//	説明:	水飛沫（後ろ）を取得
//------------------------------------------------------------------------------
CSprayBehide *CManager::GetSprayBehide(void)
{
	return m_SprayBehide;
}

//------------------------------------------------------------------------------
//	関数名:	void CManager::SetMode
//	引数:	CMode *Mode
//	戻り値:	なし
//	説明:	モードの設定
//------------------------------------------------------------------------------
void CManager::SetMode(CMode *Mode)
{
	m_Mode->Uninit();
	delete m_Mode;

	m_Mode = Mode;
	m_Mode->Init();
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetCameraData
//	引数:	CCamera_Data *pCamera_Data
//	戻り値:	なし
//	説明:	カメラデータを設定
//------------------------------------------------------------------------------
void CManager::SetCameraData(CCamera_Data *pCamera_Data)
{
	m_CameraData = pCamera_Data;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetSea
//	引数:	CMeshField *pSea
//	戻り値:	なし
//	説明:	海を設定
//------------------------------------------------------------------------------
void CManager::SetSea(CMeshField *pSea)
{
	m_Sea = pSea;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetPlayer
//	引数:	CPlayer *pPlayer
//	戻り値:	なし
//	説明:	プレイヤーを設定
//------------------------------------------------------------------------------
void CManager::SetPlayer(CPlayer *pPlayer)
{
	m_Player = pPlayer;
};

//------------------------------------------------------------------------------
//	関数名: void CManager::SetUI
//	引数:	CUI *pUI
//	戻り値:	なし
//	説明:	UIを設定
//------------------------------------------------------------------------------
void CManager::SetUI(CUI *pUI)
{
	m_UI = pUI;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetOpenAL
//	引数:	COpenAL *pOpenAL
//	戻り値:	なし
//	説明:	OpenALを設定
//------------------------------------------------------------------------------
void CManager::SetOpenAL(COpenAL *pOpenAL)
{
	m_OpenAL = pOpenAL;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetWater
//	引数:	CWater *pWater
//	戻り値:	なし
//	説明:	水を設定
//------------------------------------------------------------------------------
void CManager::SetWater(CWater *pWater)
{
	m_Water = pWater;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetBullet
//	引数:	CBullet *pBullet
//	戻り値:	なし
//	説明:	弾を設定
//------------------------------------------------------------------------------
void CManager::SetBullet(CBullet *pBullet)
{
	m_Bullet = pBullet;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetEffect
//	引数:	CEffect *pEffect
//	戻り値:	なし
//	説明:	弾を設定
//------------------------------------------------------------------------------
void CManager::SetEffect(CEffect *pEffect)
{
	m_Effect = pEffect;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetHamina
//	引数:	CEnemy_Hamina *pHaminaEnemy
//	戻り値:	なし
//	説明:	Hamina敵を設定
//------------------------------------------------------------------------------
void CManager::SetHamina(CEnemy_Hamina *pHaminaEnemy)
{
	m_Hamina = pHaminaEnemy;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetHamina
//	引数:	CMissile *pMissile
//	戻り値:	なし
//	説明:	ミサイルを設定
//------------------------------------------------------------------------------
void CManager::SetMissile(CMissile *pMissile)
{
	m_Missile = pMissile;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SetUserMap
//	引数:	CUserMap *pUserMap
//	戻り値:	なし
//	説明:	ユーザーマップを設定
//------------------------------------------------------------------------------
void CManager::SetUserMap(CUserMap *pUserMap)
{
	m_UserMap = pUserMap;
}

//------------------------------------------------------------------------------
//	関数名: void CManager::SerSprayBehide
//	引数:	CUserMap *pUserMap
//	戻り値:	なし
//	説明:	水飛沫（後ろ）を設定
//------------------------------------------------------------------------------
void CManager::SetSprayBehide(CSprayBehide *pSprayBehide)
{
	m_SprayBehide = pSprayBehide;
}

