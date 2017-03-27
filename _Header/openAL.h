/*------------------------------------------------------------------------------
|	タイトル：		openAL(サウンド)のヘッダー
|	ファイル名：	oopenAL.h
|	作成者：		AT13B284 28 CHIN HIU
|	作成日：		2016/06/17
------------------------------------------------------------------------------*/
#ifndef _OPENAL_H_
#define _OPENAL_H_

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <alut.h>	
#include "renderer.h"

/*------------------------------------------------------------------------------
|	ライブラリのリンク
------------------------------------------------------------------------------*/
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

/*------------------------------------------------------------------------------
|	const定義
------------------------------------------------------------------------------*/

const float fVoice_Distance = 7500.0f;
const float fVoice_Water_Distance = 4500.0f;

/*------------------------------------------------------------------------------
|	enum定義
------------------------------------------------------------------------------*/

typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			//  タイトルBGM
	SOUND_LABEL_BGM_TUTORIAL,			//  チュートリアルBGM
	SOUND_LABEL_BGM_GAME,				//  ゲームBGM
	SOUND_LABEL_BGM_RESULT,				//  リザルトBGM
	SOUND_LABEL_SE_TITLE_FALLS,			//  タイトル滝SE
	SOUND_LABEL_SE_WAVE,				//  海SE
	SOUND_LABEL_SE_WATER_EXPLOSION,		//  弾落水SE
	SOUND_LABEL_SE_CANNON,				//  プレイヤーカノンSE
	SOUND_LABEL_SE_CANNON_EXPLOSION,	//  プレイヤーカノン爆発SE
	SOUND_LABEL_SE_MISSILE,				//  ミサイル発射SE
	SOUND_LABEL_SE_MISSILE_EXPLOSION,	//  ミサイル爆発SE
	SOUND_LABEL_SE_PLAYER_ENGINE,		//  プレイヤー船エンジンSE
	SOUND_LABEL_SE_SHIP_EXPLOSION,		//  船爆発SE
	SOUND_LABEL_MAX
}SOUND_LABEL;

//ALfloat m_ListenerPos[] = { 0.0, 0.0, 0.0 };

/*------------------------------------------------------------------------------
|	クラス定義
------------------------------------------------------------------------------*/

//  ソースデータクラス
class CSource_Data
{
public:
	ALfloat m_Pos[3];
	ALfloat m_Vel[3];
	ALfloat m_Vol;
	bool	m_Loop;

	CSource_Data()
	{
		m_Pos[0] =
		m_Pos[1] =
		m_Pos[2] =
		m_Vel[0] =
		m_Vel[1] =
		m_Vel[2] = 0.0f;
		m_Vol = 1.0f;
		m_Loop = false;
	};
};

//  openALクラス
class COpenAL
{
private:
	ALuint			m_Buffer[SOUND_LABEL_MAX];
	ALuint			m_Source[32];
	CSource_Data	m_SourceData[32];

public:
	COpenAL();
	~COpenAL();
	void	Init(int argc, char **argv);
	void	Uninit(void);
	int		Play(SOUND_LABEL lable, ALfloat volRate, ALfloat posX, ALfloat posY, ALfloat posZ);

	void	Pause(void);

	void	SetListenervalues(ALfloat posX, ALfloat posY, ALfloat posZ);
	void	SetSourceVolume(ALuint nID, ALfloat volRate);
	void	SetSourcePos(ALuint nID, ALfloat posX, ALfloat posY, ALfloat posZ);
};
/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
#endif