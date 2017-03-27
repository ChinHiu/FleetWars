/*------------------------------------------------------------------------------
|	�^�C�g���F		openAL(�T�E���h)�̃w�b�_�[
|	�t�@�C�����F	oopenAL.h
|	�쐬�ҁF		AT13B284 28 CHIN HIU
|	�쐬���F		2016/06/17
------------------------------------------------------------------------------*/
#ifndef _OPENAL_H_
#define _OPENAL_H_

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <alut.h>	
#include "renderer.h"

/*------------------------------------------------------------------------------
|	���C�u�����̃����N
------------------------------------------------------------------------------*/
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

/*------------------------------------------------------------------------------
|	const��`
------------------------------------------------------------------------------*/

const float fVoice_Distance = 7500.0f;
const float fVoice_Water_Distance = 4500.0f;

/*------------------------------------------------------------------------------
|	enum��`
------------------------------------------------------------------------------*/

typedef enum
{
	SOUND_LABEL_BGM_TITLE = 0,			//  �^�C�g��BGM
	SOUND_LABEL_BGM_TUTORIAL,			//  �`���[�g���A��BGM
	SOUND_LABEL_BGM_GAME,				//  �Q�[��BGM
	SOUND_LABEL_BGM_RESULT,				//  ���U���gBGM
	SOUND_LABEL_SE_TITLE_FALLS,			//  �^�C�g����SE
	SOUND_LABEL_SE_WAVE,				//  �CSE
	SOUND_LABEL_SE_WATER_EXPLOSION,		//  �e����SE
	SOUND_LABEL_SE_CANNON,				//  �v���C���[�J�m��SE
	SOUND_LABEL_SE_CANNON_EXPLOSION,	//  �v���C���[�J�m������SE
	SOUND_LABEL_SE_MISSILE,				//  �~�T�C������SE
	SOUND_LABEL_SE_MISSILE_EXPLOSION,	//  �~�T�C������SE
	SOUND_LABEL_SE_PLAYER_ENGINE,		//  �v���C���[�D�G���W��SE
	SOUND_LABEL_SE_SHIP_EXPLOSION,		//  �D����SE
	SOUND_LABEL_MAX
}SOUND_LABEL;

//ALfloat m_ListenerPos[] = { 0.0, 0.0, 0.0 };

/*------------------------------------------------------------------------------
|	�N���X��`
------------------------------------------------------------------------------*/

//  �\�[�X�f�[�^�N���X
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

//  openAL�N���X
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
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
#endif