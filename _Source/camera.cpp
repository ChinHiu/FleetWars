//------------------------------------------------------------------------------
//	タイトル：		カメラ関数
//	ファイル名：	camera.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/26
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "camera.h"
#include "manager.h"
#include "title.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	マクロ定義とConst定義
//------------------------------------------------------------------------------
const int			nNear_Z			= 5;										//  NearZ値
const int			nFar_Z			= 50000;									//  FarZ値
const float			fView_Angle		= 45.0f;									//  視野角
const float			fDistance		= 650.0f;									//  注視点と視点の距離
const float			fCamera_Move	= 0.005f;									//  デバッグ状態カメラの移動量
const D3DXVECTOR3	View_Pos		= D3DXVECTOR3(291.00f, 107.0f, -400.0f);	//  視点座標初期値
const D3DXVECTOR3	Look_Pos		= D3DXVECTOR3(0.0f, 40.0f, 0.0f);			//  注視点座標初期値
const D3DXVECTOR3	Gun_Pos			= D3DXVECTOR3(32.0f, 64.0f, 32.0f);			//  銃の相対位置

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CCamera::CCamera()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CCamera::CCamera()
{
}

//------------------------------------------------------------------------------
//	関数名:	CCamera::~CCamera()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CCamera::~CCamera()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CCamera::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CCamera::Init(D3DXVECTOR3 rot, bool bLookAt)
{
	//  カメラの視点
	m_CameraData.posV = View_Pos;

	//  カメラの注視点
	m_CameraData.posR = Look_Pos;

	//  カメラの上方向
	m_CameraData.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//  カメラの向き
	m_CameraData.rot = rot;

	//カメラの移動量
	m_CameraData.fMove = fCamera_Move;

	//  視点と注視点の距離
	m_CameraData.fDistance = fDistance;

	//  旋回中心を注視点に設定
	m_CameraData.bLookAt = bLookAt;
}	

//------------------------------------------------------------------------------
//	関数名:	void CCamera::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}

//------------------------------------------------------------------------------
//	関数名:	void CCamera::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
//------------------------------------------------------------------------------
void CCamera::Update(void)
{
	CMode		*pMode		= CManager::GetMode();
	CKeyboard	*pKeyboard	= CManager::GetInput()->GetKeyboard();
	CMouse		*pMouse		= CManager::GetInput()->GetMouse();

	//  タイトル以外カメラの更新
	if (typeid(*pMode).name() != typeid(CTitle).name())
	{
		CPlayer	*pPlayer = CManager::GetPlayer();				//  プレイヤーを取得
		WEAPON_TYPE *pPlayerWeapon = pPlayer->GetWeponType();	//  プレイヤー現在の武器を取得
		D3DXVECTOR3 *pPlayerPos = pPlayer->GetPosition();		//  プレイヤー位置を取得
		D3DXVECTOR3 *pPlayerRot = pPlayer->GetRotation();		//  プレイヤー回転を取得

		float RateRot;

		if (*pPlayerWeapon != m_OldWeapon)
		{
			if(*pPlayerWeapon == WEAPON_BULLET) m_CameraData.rot.x = D3DX_PI * 0.57f;
			else								m_CameraData.rot.x = D3DX_PI * 0.43f;
		}

		switch (*pPlayerWeapon)
		{
		case WEAPON_BULLET:
			if (pMouse->GetMouseState()->lX != 0)
			{
				m_CameraData.rot.y += pMouse->GetMouseState()->lX * fCamera_Move;
				SAFE_ROTCHECK(m_CameraData.rot.y);
			}

			RateRot = m_CameraData.rot.y + pPlayerRot->y;
			SAFE_ROTCHECK(RateRot);

			if (pMouse->GetMouseState()->lY != 0)
			{
				m_CameraData.rot.x += pMouse->GetMouseState()->lY * fCamera_Move;
				if (m_CameraData.rot.x >= D3DX_PI * 0.57f)
				{
					m_CameraData.rot.x = D3DX_PI * 0.57f;
				}
				else if (m_CameraData.rot.x <= D3DX_PI * 0.4f)
				{
					m_CameraData.rot.x = D3DX_PI * 0.4f;
				}
			}

			m_CameraData.posV.x = pPlayerPos->x + sinf(-pPlayerRot->y) * Gun_Pos.x;
			m_CameraData.posV.y = pPlayerPos->y + Gun_Pos.y;
			m_CameraData.posV.z = pPlayerPos->z - cosf(-pPlayerRot->y) * Gun_Pos.z;

			//  プレイヤーカメラの追従
			m_CameraData.posR.x = m_CameraData.posV.x - sinf(-RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			m_CameraData.posR.y = m_CameraData.posV.y + cosf(m_CameraData.rot.x) * m_CameraData.fDistance;
			m_CameraData.posR.z = m_CameraData.posV.z + cosf(-RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			break;
		default:
			if (pMouse->GetMouseState()->lX != 0)
			{
				m_CameraData.rot.y += pMouse->GetMouseState()->lX * fCamera_Move;
				SAFE_ROTCHECK(m_CameraData.rot.y);
			}

			RateRot = m_CameraData.rot.y + pPlayerRot->y;
			SAFE_ROTCHECK(RateRot);

			//  注視点座標の更新
			m_CameraData.posR.x = pPlayerPos->x;
			m_CameraData.posR.y = Look_Pos.y;
			m_CameraData.posR.z = pPlayerPos->z;

			//  注視点から視点を求める
			m_CameraData.posV.x = m_CameraData.posR.x - sinf(RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			m_CameraData.posV.z = m_CameraData.posR.z - cosf(RateRot) * m_CameraData.fDistance * sinf(m_CameraData.rot.x);
			m_CameraData.posV.y = m_CameraData.posR.y + cosf(m_CameraData.rot.x) * m_CameraData.fDistance;
			break;
		}

		m_OldWeapon = *pPlayerWeapon;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CCamera::SetCamera
//	引数:	なし
//	戻り値:	なし
//	説明:	カメラの設定
//------------------------------------------------------------------------------
void CCamera::SetCamera(void)
{
	D3DXVECTOR2 *pScreenSize = GetScreenSize();

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_CameraData.mtxProjection);

	//  プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH
	(
		&m_CameraData.mtxProjection,
		D3DXToRadian(fView_Angle),					//  視野角
		(float)pScreenSize->x / pScreenSize->y,		//  アスペクト比
		(float)nNear_Z,								//  NearZ値
		(float)nFar_Z								//  FarZ値
	);

	//  プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_CameraData.mtxProjection);

	//  ビューマトリックスの作成
	D3DXMatrixLookAtLH
	(
		&m_CameraData.mtxView,
		&m_CameraData.posV,
		&m_CameraData.posR,
		&m_CameraData.vecU
	);

	//  ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_CameraData.mtxView);
}

//------------------------------------------------------------------------------
//	関数名:	CCamera_Data *CCamera::GetCamera
//	引数:	なし
//	戻り値:	m_Camera
//	説明:	カメラデータの取得
//------------------------------------------------------------------------------
CCamera_Data *CCamera::GetCameraData(void)
{
	return &m_CameraData;
}
//
////------------------------------------------------------------------------------
////	関数名:	void CCamera::Move
////	引数:	CKeyboard *keyboard
////			int UP_KEY					int DOWN_KEY
////			int LEFT_KEY				int RIGHT_KEY
////			int VIEW_LTURNING_KEY		int VIEW_RTURNING_KEY
////			int LOOKAT_LTURNING_KEY		int LOOKAT_RTURNING_KEY
////	戻り値:	なし
////	説明:	カメラの操作
////------------------------------------------------------------------------------
//void CCamera::Move(CKeyboard *keyboard, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY, int VIEW_LTURNING_KEY, int VIEW_RTURNING_KEY, int LOOKAT_LTURNING_KEY, int LOOKAT_RTURNING_KEY)
//{
//	//  視点旋回
//	if (keyboard->GetPress(VIEW_LTURNING_KEY))			m_Camera.rot.y -= D3DX_PI * 0.01f;		//  左旋回
//	else if (keyboard->GetPress(VIEW_RTURNING_KEY))		m_Camera.rot.y += D3DX_PI * 0.01f;		//  右旋回
//

//	m_Camera.bLookAt = false;
//	//  注視点旋回
//	if (keyboard->GetPress(LOOKAT_LTURNING_KEY))
//	{//  左旋回
//		m_Camera.rot.y += D3DX_PI * 0.01f;
//
//		//  旋回中心を注視点に設定
//		m_Camera.bLookAt = true;
//	}
//	else if (keyboard->GetPress(LOOKAT_RTURNING_KEY))
//	{//  右旋回
//		m_Camera.rot.y -= D3DX_PI * 0.01f;
//
//		//  旋回中心を注視点に設定
//		m_Camera.bLookAt = true;
//	}
//
//	SAFE_ROTCHECK(m_Camera.rot.y);
//
//	if (keyboard->GetPress(UP_KEY))
//	{
//		if (keyboard->GetPress(LEFT_KEY))
//		{//  左上移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(RIGHT_KEY)))
//		{//  右上移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else
//		{//  前移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI) * m_Camera.fMove;
//		}
//	}
//	else if (keyboard->GetPress(DOWN_KEY))
//	{
//		if (keyboard->GetPress(LEFT_KEY))
//		{//  左下移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(RIGHT_KEY)))
//		{//  右下移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else
//		{//  後移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y) * m_Camera.fMove;
//		}
//	}
//	else if (keyboard->GetPress(LEFT_KEY))
//	{
//		if (keyboard->GetPress(UP_KEY))
//		{//  左上移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(DOWN_KEY)))
//		{//  左下移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else
//		{//  左移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y + D3DX_PI * 0.5f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y + D3DX_PI * 0.5f) * m_Camera.fMove;
//		}
//	}
//	else if (keyboard->GetPress(RIGHT_KEY))
//	{
//		if (keyboard->GetPress(UP_KEY))
//		{//  右上移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.75f) * m_Camera.fMove;
//		}
//		else if ((keyboard->GetPress(DOWN_KEY)))
//		{//  右下移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.25f) * m_Camera.fMove;
//		}
//		else
//		{//  右移動
//			m_Camera.posV.x -= sinf(m_Camera.rot.y - D3DX_PI * 0.5f) * m_Camera.fMove;
//			m_Camera.posV.z -= cosf(m_Camera.rot.y - D3DX_PI * 0.5f) * m_Camera.fMove;
//		}
//	}
//}