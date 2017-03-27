//------------------------------------------------------------------------------
//	タイトル：		コリジョン関数のヘッダー
//	ファイル名：	collisionFunc.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2017/01/06
//------------------------------------------------------------------------------
#ifndef _FUNC_H_
#define _FUNC_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "renderer.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
//  前方宣言
class CObb;

//  関数のクラス
class CFunc
{
public:
	float GetDistance(const D3DXVECTOR3 &TargetPos, const D3DXVECTOR3 &OwnPos);
	float GetXZRot(const D3DXVECTOR3 &TargetPos, const D3DXVECTOR3 &OwnPos);
	float GetYZRot(const D3DXVECTOR3 &TargetPos, const D3DXVECTOR3 &OwnPos);
	int Powi(const int &x, const int &y);
	FLOAT LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);
	bool OBBs(CObb &obb1, CObb &obb2);
	FLOAT LenOBBToPoint(CObb &obb, D3DXVECTOR3 &pos);
};

#endif