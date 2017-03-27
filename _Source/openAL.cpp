
/*------------------------------------------------------------------------------
|	�^�C�g���F		OpenAL�̊֐�
|	�t�@�C�����F	openAL.cpp
|	�쐬�ҁF		AT13B284 28 CHIN HIU
|	�쐬���F		2016/06/20
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�X�V����:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "openAL.h"
#include "manager.h"
#include "title.h"
#include "game.h"

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�O���[�o���ϐ�
------------------------------------------------------------------------------*/
typedef struct
{
	char *pFilename;	//  �t�@�C����
	bool bLoop;
	float fVol;
}SOUNDPARAM;

// �e���f�ނ̃p�����[�^
SOUNDPARAM g_Param[SOUND_LABEL_MAX] =
{
	{ "./data/BGM/bgm_Title.wav", true , 1.0f },			// BGMbgm_Title
	{ "./data/BGM/bgm_Tutorial.wav", true , 0.75f },		// BGM
	{ "./data/BGM/bgm_Game.wav", true , 0.75f },
	{ "./data/BGM/bgm_Result.wav", false , 0.4f },
	{ "./data/SE/Title_Falls.wav", true, 0.1f },
	{ "./data/SE/Wave.wav", true, 0.35f },
	{ "./data/SE/Water_Explosion.wav", false, 0.45f },
	{ "./data/SE/Cannon.wav", false, 0.75f },
	{ "./data/SE/Cannon_Explosion.wav", false, 0.3f },
	{ "./data/SE/Missile.wav", false, 0.3f },
	{ "./data/SE/Cannon_Explosion.wav", false, 0.4f },
	{ "./data/SE/Player_Engine.wav", true, 0.15f },
	{ "./data/SE/Cannon_Explosion.wav", false, 0.5f },
};

ALfloat g_ListenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat g_ListenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat g_ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

/*------------------------------------------------------------------------------
|	�֐���:	COpenAL::COpenAL
|	����:	�Ȃ�
|	�߂�l:	�Ȃ�
|	����:	�R���X�g���N�^
------------------------------------------------------------------------------*/
COpenAL::COpenAL()
{
}

/*------------------------------------------------------------------------------
|	�֐���:	COpenAL::~COpenAL
|	����:	�Ȃ�
|	�߂�l:	�Ȃ�
|	����:	�f�X�g���N�^
------------------------------------------------------------------------------*/
COpenAL::~COpenAL()
{
}

/*------------------------------------------------------------------------------
|	�֐���:	void COpenAL::Load
|	����:	�Ȃ�
|	�߂�l:	�Ȃ�
|	����:	�I�[���X�V
------------------------------------------------------------------------------*/
void COpenAL::Init(int argc, char **argv)
{
	alutInit(NULL, NULL);
	alGenSources(32, m_Source);

	SetListenervalues(0.0f, 0.0f, 0.0f);

	//m_Buffer[0] = alutCreateBufferHelloWorld();
	for (int nCnt = 0; nCnt < SOUND_LABEL_MAX; nCnt++)
	{
		m_Buffer[nCnt] = alutCreateBufferFromFile(g_Param[nCnt].pFilename);
	}
}

/*------------------------------------------------------------------------------
|	�֐���:	void COpenAL::Load
|	����:	�Ȃ�
|	�߂�l:	�Ȃ�
|	����:	�I�[���X�V
------------------------------------------------------------------------------*/
int COpenAL::Play(SOUND_LABEL lable, ALfloat volRate, ALfloat posX, ALfloat posY, ALfloat posZ)
{
	int nSoundID = -1;

	for (int i = 0; i < 32; i++)
	{
		int state;
		alGetSourcei(m_Source[i], AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
		{
			m_SourceData[i].m_Loop = g_Param[lable].bLoop;					//  ���[�v
			m_SourceData[i].m_Vol = g_Param[lable].fVol * volRate;
			m_SourceData[i].m_Pos[0] = posX;
			m_SourceData[i].m_Pos[1] = posY;
			m_SourceData[i].m_Pos[2] = posZ;
			m_SourceData[i].m_Vel[0] =
			m_SourceData[i].m_Vel[1] =
			m_SourceData[i].m_Vel[2] = 0.0f;
			alSourcei(m_Source[i], AL_BUFFER, m_Buffer[lable]);				//  ���f�[�^�̃o�b�t�@���w��
			alSourcef(m_Source[i], AL_PITCH, 1.0);
			alSourcef(m_Source[i], AL_GAIN, m_SourceData[i].m_Vol);			//  ����
			alSourcefv(m_Source[i], AL_POSITION, m_SourceData[i].m_Pos);	//  �ʒu
			alSourcefv(m_Source[i], AL_VELOCITY, m_SourceData[i].m_Vel);	//  ���x
			alSourcei(m_Source[i], AL_LOOPING, m_SourceData[i].m_Loop);		//  ���[�v�̐ݒ�
			alSourcePlay(m_Source[i]);
			nSoundID = i;
			break;
		}
	}
	return nSoundID;
}

/*------------------------------------------------------------------------------
|	�֐���:	void CSceneGL::DrawAll
|	����:	�Ȃ�
|	�߂�l:	�Ȃ�
|	����:	�I�[���`��
------------------------------------------------------------------------------*/
void COpenAL::Uninit(void)
{
	alutExit();
}

void COpenAL::Pause(void)
{
	for (int i = 0; i < 32; i++)
	{
		int state;
		alGetSourcei(m_Source[i], AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING)
		{
			alSourcePause(m_Source[i]);
		}
	}
}

void  COpenAL::SetListenervalues(ALfloat posX, ALfloat posY, ALfloat posZ)
{
	g_ListenerPos[0] = posX;
	g_ListenerPos[1] = posY;
	g_ListenerPos[2] = posZ;
	alListenerfv(AL_POSITION, g_ListenerPos);
	alListenerfv(AL_VELOCITY, g_ListenerVel);
	alListenerfv(AL_ORIENTATION, g_ListenerOri);
}

void COpenAL::SetSourceVolume(ALuint nID, ALfloat volRate)
{
	ALfloat vol;
	vol = m_SourceData[nID].m_Vol * volRate;
	alSourcef(m_Source[nID], AL_GAIN, vol);			//  ����
}

//void COpenAL::SetSourceVelocity(ALuint nID, ALfloat vel)
//{
//	m_SourceData[nID].m_Vel[2] = vel;
//
//	alSourcefv(m_Source[nID], AL_VELOCITY, m_SourceData[nID].m_Vel);	//  ���x
//}

void COpenAL::SetSourcePos(ALuint nID, ALfloat posX, ALfloat posY, ALfloat posZ)
{
	m_SourceData[nID].m_Pos[0] = posX;
	m_SourceData[nID].m_Pos[1] = posY;
	m_SourceData[nID].m_Pos[2] = posZ;
	alSourcefv(m_Source[nID], AL_POSITION, m_SourceData[nID].m_Pos);	//  �ʒu
}