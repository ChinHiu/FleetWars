//------------------------------------------------------------------------------
//	タイトル：		デバッグ処理
//	ファイル名：	debugProc.cpp
//	作成者：		AT13B284 33 CHIN HIU
//	作成日：		2015/12/03
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include <stdio.h>
#include <varargs.h>
#include <stdarg.h>
#include "debugProc.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "mouse.h"
#include "player.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CScene::CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CDebugProc::CDebugProc()
{
	m_pFont = NULL;				//  フォントへのポインタ
}

//------------------------------------------------------------------------------
//	関数名:	CScene::~CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CDebugProc::~CDebugProc()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CDebugProc::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CDebugProc::Init(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  デバッグプロシージャ表示用フォントを設定
	D3DXCreateFont
	(
		pDevice,									
		15,
		0,
		FW_NORMAL,
		NULL,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pFont
	);

	//  ゼロクリアする
	memset(m_StrDebug, 0, sizeof m_StrDebug);
}

//------------------------------------------------------------------------------
//	関数名:	void CDebugProc::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CDebugProc::Uninit(void)
{
	//  デバッグプロシージャ表示用フォントを設定
	SAFE_RELEASE(m_pFont);
}

//------------------------------------------------------------------------------
//	関数名:	void CDebugProc::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CDebugProc::Update(void)
{
//	CGame *Game = ((CGame*)CManager::GetMode());
//
//	//  カメラを取得
//	CCamera_Data *pCamera = Game->GetCamera()->GetCamera();
///*
//	D3DXVECTOR2 *pUserMap = CGame::GetUserMap()->GetUserMapPos();*/
//
//	/*CEnemy *pEnemy = CGame::GetEnemy();
//	CHamina_Data *pHamina = Game->GetEnemyHamina()->GetHaminaData();
//*/
//
	CCamera_Data *pCamera = CManager::GetCameraData();

	if (pCamera != NULL)
	{
		CPlayer *pPlayer = CManager::GetPlayer();
		//  プレイヤーを取得
		D3DXVECTOR3 *pPlayerPos = pPlayer->GetPosition();
		D3DXVECTOR3 *pPlayerRot = pPlayer->GetRotation();
		CMouse *pMouse = CManager::GetInput()->GetMouse();

		PrintDebugProc("*** カメラ情報 ***\n");
		PrintDebugProc("[ 視点					( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
		PrintDebugProc("[ 注視点				( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
		PrintDebugProc("[ 向き					( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);
		PrintDebugProc("[ 視点と注視点の距離	( %.2f )]\n\n", pCamera->fDistance);

		PrintDebugProc("*** プレイヤー情報 ***\n");
		PrintDebugProc("[ 座標					( X:%.2f Y:%.2f Z:%.2f )]\n", pPlayerPos->x, pPlayerPos->y, pPlayerPos->z);
		PrintDebugProc("[ 向き					( X:%.2f Y:%.2f Z:%.2f )]\n\n", pPlayerRot->x, pPlayerRot->y, pPlayerRot->z);

		PrintDebugProc("*** マウス情報 ***\n");
		PrintDebugProc("[ IX:%d IY:%d IZ:%d ]\n", pMouse->GetMouseState()->lX, pMouse->GetMouseState()->lY, pMouse->GetMouseState()->lZ);
		PrintDebugProc("[ 画面の位置			(x:%d y:%d ) ]\n", pMouse->GetMousePoint()->x, pMouse->GetMousePoint()->y);
		PrintDebugProc("[ ワールド座標			(x:%.2f y:%.2f z:%.2f ) ]\n", pMouse->GetWorldPos()->x, pMouse->GetWorldPos()->y, pMouse->GetWorldPos()->z);
	}
//		/*PrintDebugProc("*** HAMINA砲台回転情報 ***\n");
//		for (int i = 0; i < HAMINA_MAX; i++) {
//			if ((pHamina + i)->Flag) {
//				PrintDebugProc("[ 砲台向き        ( X:%.2f Y:%.2f Z:%.2f )]\n", (pHamina + i)->BatteryRot.x, (pHamina + i)->BatteryRot.y, (pHamina + i)->BatteryRot.z);
//			}
//		}
//		PrintDebugProc("*** プレイヤーID情報 ***\n");
//		PrintDebugProc("[ 1[%d] 2[%d] 3[%d] 4[%d] ]\n", pPlayer->GetLockShipID(0), pPlayer->GetLockShipID(1), pPlayer->GetLockShipID(2), pPlayer->GetLockShipID(3));*/
//	}
}

//------------------------------------------------------------------------------
//	関数名:	void CDebugProc::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CDebugProc::Draw(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	RECT rect = { 0, 0, (int)pScreenSize->x, (int)pScreenSize->y };

	//  テキスト描画
	m_pFont->DrawText(NULL, &m_StrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(250, 0, 50, 255));

	//  ゼロクリアする
	memset(m_StrDebug, 0, sizeof m_StrDebug);
}

//------------------------------------------------------------------------------
//	関数名:	void CDebugProc::PrintDebugProc
//	引数:	char *fmt, ...
//	戻り値:	なし
//	説明:	デバッグプロシージャ用偽Printf
//------------------------------------------------------------------------------
void CDebugProc::PrintDebugProc(char *fmt, ...)
{
	int len;

	//  文字数チェック
	len = strlen(m_StrDebug);

	va_list	list;
	va_start(list, fmt);
	vsprintf(&m_StrDebug[len], fmt, list);
	va_end(list);
}
