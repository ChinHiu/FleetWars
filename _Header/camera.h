//------------------------------------------------------------------------------
//	タイトル：		カメラのヘッダー
//	ファイル名：	camera.h
//	作成者：		AT12A244 33 CHIN HIU
//	作成日：		2015/10/21
//------------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "player.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CKeyboard;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  カメラデータクラス
class CCamera_Data
{
public:
	D3DXMATRIX		mtxProjection;	//　プロジェクションマトリックス
	D3DXMATRIX		mtxView;		//  ビューマトリックス
	D3DXVECTOR3		posV;			//  視点座標
	D3DXVECTOR3		posR;			//  注視点座標
	D3DXVECTOR3		vecU;			//  上方向きベクトル
	D3DXVECTOR3		rot;			//  回転角度
	D3DXVECTOR3		posRAim;		//  注視点目標移動座標
	D3DXVECTOR3		rotAim;			//  回転目標角度
	int				nMoveCount;		//  移動カウンタ
	float			fMove;			//  移動量
	float			fDistance;		//  視点と注視点の距離
	bool			bLookAt;
};

// カメラクラス
class CCamera
{
public:
	CCamera();
	~CCamera();
	void			Init(D3DXVECTOR3 rot, bool bLookAt);
	void			Uninit(void);
	void			Update(void);
	void			SetCamera(void);
	CCamera_Data	*GetCameraData(void);

#ifdef _DEBUG
	void	Move(
		CKeyboard *keyboard,
		int UP_KEY,
		int DOWN_KEY,
		int LEFT_KEY,
		int RIGHT_KEY,
		int VIEW_LTURNING_KEY,
		int VIEW_RTURNING_KEY,
		int LOOKAT_LTURNING_KEY,
		int LOOKAT_RTURNING_KEY);
#endif

private:
	CCamera_Data	m_CameraData;
	WEAPON_TYPE		m_OldWeapon;
};

#endif