//------------------------------------------------------------------------------
//	タイトル：		ライトの関数
//	ファイル名：	Light.cpp
//	作成者：		AT12A244 33 CHIN HIU
//	作成日：		2015/10/21
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "light.h"
#include "title.h"
#include <typeinfo.h>

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	関数名:	CLight::CLight()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CLight::CLight()
{
}

//------------------------------------------------------------------------------
//	関数名:	CLight::~CLight()
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CLight::~CLight()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CLight::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CLight::Init(void)
{
	CMode *pMode = CManager::GetMode();

	//  タイトルモードの更新処理
	if (typeid(*pMode).name() == typeid(CTitle).name())
	{
		m_LightData[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_LightData[0].ambient = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		m_LightData[0].vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

		m_LightData[1].diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		m_LightData[1].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[1].vecDir = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);

		m_LightData[2].diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		m_LightData[2].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[2].vecDir = D3DXVECTOR3(0.0f, -1.0f, -2.0f);
		m_Adjust = 1;
	}
	else
	{
		m_LightData[0].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[0].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[0].vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

		m_LightData[1].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[1].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[1].vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);

		m_LightData[2].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[2].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[2].vecDir = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

		m_LightData[3].diffuse = D3DXCOLOR(0.32f, 0.32f, 0.32f, 1.0f);
		m_LightData[3].ambient = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
		m_LightData[3].vecDir = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
		m_Adjust = 0;
	}
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int i = 0; i < nLightMax - m_Adjust; i++)
	{
		ZeroMemory(&m_Light[i], sizeof(D3DLIGHT9));

		//平行光源
		m_Light[i].Type = D3DLIGHT_DIRECTIONAL;

		//拡散光
		m_Light[i].Diffuse = m_LightData[i].diffuse;

		////光の方向
		//m_Light[nCntLight].vecDir = m_Light[nCntLight].vecDir;

		//正規化
		D3DXVec3Normalize((D3DXVECTOR3 *)&m_Light[i].Direction, &m_LightData[i].vecDir);

		//ライトの設定
		pDevice->SetLight(i, &m_Light[i]);

		//ライトを有効する
		pDevice->LightEnable(i, TRUE);
	}
}