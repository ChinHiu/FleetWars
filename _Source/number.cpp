//------------------------------------------------------------------------------
//	�^�C�g���F		�i���o�[�̊֐�
//	�t�@�C�����F	number.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/07/14
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "number.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define TIME_SIGFIGS (5)
#define POWER_SIGFIGS (4)
#define SPEED_SIGFIGS (5)
#define FRAME (60)

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//	�֐���:	CNumber::CNumber
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CNumber::CNumber(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	//  ���_�o�b�t�@�ւ̃|�C��
	m_VertexBuffer	= NULL;

	//  �e�N�X�`���ւ̃|�C���^
	m_TextureBuffer = NULL;

}

//------------------------------------------------------------------------------
//	�֐���:	CNumber::~CNumber
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�R���X�g���N�^
//------------------------------------------------------------------------------
CNumber::~CNumber()
{
}

//------------------------------------------------------------------------------
//	�֐���:	CNumber *CNumber::Create
//	����:	int value			//  �l
//			int sigFigs			//  �L������
//			D3DXVECTOR3 pos		//  �ʒu
//			D3DXVECTOR3 size	//  �T�C�Y�i���A������A���s���j
//			bool bUse			//  �g�p���邩�ǂ���
//	�߂�l:	CNumber pNumber
//	����:	�i���o�[�̐���
//------------------------------------------------------------------------------
CNumber *CNumber::Create(int *value, int sigFigs, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, NUMBER_TYPE Number_Type, bool bFlag)
{
	CNumber *pNumber;
	pNumber = new CNumber;

	//  ���̐ݒ�
	pNumber->m_Number.value		= value;		//  �l
	pNumber->m_Number.Pos		= pos;			//  �ʒu
	pNumber->m_Number.Type		= Number_Type;
	pNumber->m_Number.Size		= size;			//  �T�C�Y�i���A������A���s���j
	pNumber->m_Number.Flag		= bFlag;		//  �g�p���邩�ǂ���
	pNumber->m_Number.Col		= col;

	//  �L������
	switch (Number_Type) {
	case NUMBER_TYPE_POWER:
		pNumber->m_Number.sigFigs = POWER_SIGFIGS;
		break;
	case NUMBER_TYPE_SPEED:
		pNumber->m_Number.sigFigs = SPEED_SIGFIGS;
		break;
	case NUMBER_TYPE_TIME:
		pNumber->m_Number.sigFigs = TIME_SIGFIGS;
		break;
	case NUMBER_TYPE_VALUE:
		pNumber->m_Number.sigFigs = sigFigs;
		break;
	case NUMBER_TYPE_DAMAGE:
		pNumber->m_Number.sigFigs = POWER_SIGFIGS;
	default:
		break;
	}

	//  ������
	pNumber->Init();

	return pNumber;
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::Init
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	����������
//------------------------------------------------------------------------------
void CNumber::Init(void)
{
	m_Number.digit		= new int[m_Number.sigFigs];
	m_Number.digitFlag	= new bool[m_Number.sigFigs];
	m_VertexPos			= new VERTEX_POS[m_Number.sigFigs];		

	m_MinuteCnt = m_SecondCnt = 2;

	m_SpeedCnt = 4;

	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile (
		pDevice,
		NUMBER_TEXTURE_FILE,	//  �e�N�X�`���t�@�C���ʒu
		&m_TextureBuffer		//  �e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	CalculateVertex();

	//  ���_���̍쐬
	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::Uninit
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�I������
//------------------------------------------------------------------------------
void CNumber::Uninit(void)
{
	//  �e�N�X�`���o�b�t�@�̊J��
	SAFE_RELEASE(m_TextureBuffer);

	//  ���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_VertexBuffer);

	delete m_Number.digit;
	delete m_Number.digitFlag;
	delete m_VertexPos;
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::Update
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�V����
//------------------------------------------------------------------------------
void CNumber::Update(void)
{
	switch (m_Number.Type) {
	case NUMBER_TYPE_POWER:
		PowerDigitUpdate();
		break;
	case NUMBER_TYPE_SPEED:
		SpeedDigitUpdate();
		break;
	case NUMBER_TYPE_TIME:
		TimeDigitUpdate();
		break;
	case NUMBER_TYPE_VALUE:
		ValueDigitUpdate();
		break;
	case NUMBER_TYPE_DAMAGE:
		DamageDigitUpdate();
		break;
	default:
		break;
	}

	//  �e�N�X�`���̍X�V
	SetTexture();
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::Draw
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�`�揈��
//------------------------------------------------------------------------------
void CNumber::Draw(void)
{
	//  �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//  ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_TextureBuffer);

	////  �y�e�X�g���s��
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//  �y�e�X�g�L����
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					//  �y�l�̍X�V���s��Ȃ����A�y�e�X�g��L��������
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				//  �y�e�X�g���i�

	//  ���e�X�g���s��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  ���e�X�g�̗L����
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  ���e�X�g���i�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  ���Q�ƒl

																		//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////  �t�H�O�L����
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (m_Number.Flag)
	{
		for (int i = 0; i < m_Number.sigFigs; i++)
		{
			if (m_Number.digitFlag[i]) {
				//  �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
			}
		}
	}

	////  �y�e�X�g���s��Ȃ�
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				//  �y�e�X�g���i�

	//  ���e�X�g���s��Ȃ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  ���e�X�g������

	//  ���C�g�L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////  �t�H�O�L����
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	�֐���:	HRESULT CNumber::MakeVertex
//	����:	LPDIRECT3DDEVICE9 pDevice
//	�߂�l:	E_FAIL���ƍ쐬���s�AS_OK���ƍ쐬����
//	����:	���_�o�b�t�@���쐬
//------------------------------------------------------------------------------
HRESULT CNumber::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
		(
		sizeof(VERTEX_2D) * nNumVertex * m_Number.sigFigs,	//  ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,									//  ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,										//  �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,									//  ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_VertexBuffer,									//  ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL												//  NULL�ɐݒ�
		)))
	{
		return E_FAIL;
	}

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  ���_���W�̐ݒ�
	for (int i = 0; i < m_Number.sigFigs; i++, pVtx += 4)
	{
		pVtx[0].pos = (m_VertexPos + i)->pos0;
		pVtx[1].pos = (m_VertexPos + i)->pos1;
		pVtx[2].pos = (m_VertexPos + i)->pos2;
		pVtx[3].pos = (m_VertexPos + i)->pos3;

		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		//  ���_�J���[�̐ݒ�
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_Number.Col;

		//  �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::CalculateVertex
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	���_���W���Z�o
//------------------------------------------------------------------------------
void CNumber::CalculateVertex(void)
{
	VERTEX_POS *pVertexPos = GetVertexPos();

	for (int i = 0; i < m_Number.sigFigs; i++, pVertexPos++)
	{
		switch (m_Number.Type)
		{
		case NUMBER_TYPE_SPEED: //  �X�s�[�h
			switch (i)
			{
			case 0:
				pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			case 2:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 0.5f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 0.5f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			case 4:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			default:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			}
			break;
		case NUMBER_TYPE_POWER: //  �p���[
			switch (i)
			{
			case 0:
				pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			case 3:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			default:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			}
			break;
		case NUMBER_TYPE_TIME: //  �^�C��
			switch (i)
			{
			case 0:
				pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			case 2:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 0.5f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 0.5f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			default:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			}
			break;
		case NUMBER_TYPE_DAMAGE: //  �^�C��
			switch (i)
			{
			case 0:
				pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			case 3:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			default:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			}
			break;
		default:				//  ����
			switch (i)
			{
			case 0:
				pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			default:
				pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				break;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	VERTEX_POS *CNumber::GetVertexPos
//	����:	�Ȃ�
//	�߂�l:	m_VertexPos[0]
//	����:	���_���W���擾
//------------------------------------------------------------------------------
VERTEX_POS *CNumber::GetVertexPos(void)
{
	return &m_VertexPos[0];
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::PowerDigitUpdate
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�p���[�^�C�v���̍X�V
//------------------------------------------------------------------------------
void CNumber::PowerDigitUpdate(void)
{
	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  �e�������̌v�Z���ݒ�
		if (i != m_Number.sigFigs - 1)
		{
			m_Number.digit[i] = *m_Number.value % Powi(10, m_Number.sigFigs - 1 - i) / Powi(10, m_Number.sigFigs - 2 - i);
		}
		else {
			m_Number.digit[i] = DIGIT_SYMBOL_PERCENT;
		}

		//  �`��t���O�X�V����
		switch (i)
		{
		case 0:
			if (m_Number.digit[i] == 0)
			{
				//  �S�ʂ��O�̎��`�悵�Ȃ�
				m_Number.digitFlag[i] = false;
			}
			else
			{
				m_Number.digitFlag[i] = true;
			}
			break;
		case 1:
			if (m_Number.digit[i - 1 ] == 0)
			{
				//  �S�ʂƏ\�ʂ��O�̎��`�悵�Ȃ�
				if (m_Number.digit[i] == 0)
				{
					m_Number.digitFlag[i] = false;
				}
				else
				{
					m_Number.digitFlag[i] = true;
				}
			}
			else
			{
				m_Number.digitFlag[i] = true;
			}
			break;
		default://  �ق��̕`�悷��
			m_Number.digitFlag[i] = true;
			break;
		}
	}
}


void CNumber::DamageDigitUpdate(void)
{
	VERTEX_POS *pVertexPos = GetVertexPos();

	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  �e�������̌v�Z���ݒ�
		if (i != m_Number.sigFigs - 1)
		{
			m_Number.digit[i] = *m_Number.value % Powi(10, m_Number.sigFigs - 1 - i) / Powi(10, m_Number.sigFigs - 2 - i);
		}
		else {
			m_Number.digit[i] = DIGIT_SYMBOL_PERCENT;
		}

		//  �`��t���O�X�V����
		switch (i)
		{
		case 0:
			if (m_Number.digit[i] == 0)
			{
				//  �S�ʂ��O�̎��`�悵�Ȃ�
				m_Number.digitFlag[i] = false;
			}
			else
			{
				m_Number.digitFlag[i] = true;
			}
			break;
		case 1:
			if (m_Number.digit[i] == 0)
			{
				//  �S�ʂƏ\�ʂ��O�̎��`�悵�Ȃ�
				if (m_Number.digit[i - 1] == 0)
				{
					m_Number.digitFlag[i] = false;
				}
			}
			else
			{
				m_Number.digitFlag[i] = true;
			}
			break;
		case 3:
			m_Number.digitFlag[i] = true;
			/*(pVertexPos + 3)->pos0 = D3DXVECTOR3((pVertexPos + 2)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			(pVertexPos + 3)->pos1 = D3DXVECTOR3((pVertexPos + 2)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			(pVertexPos + 3)->pos2 = D3DXVECTOR3((pVertexPos + 2)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			(pVertexPos + 3)->pos3 = D3DXVECTOR3((pVertexPos + 2)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);*/
			break;
		default://  �ق��̕`�悷��
			m_Number.digitFlag[i] = true;
	/*		(pVertexPos + 2)->pos0 = D3DXVECTOR3((pVertexPos + 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			(pVertexPos + 2)->pos1 = D3DXVECTOR3((pVertexPos + 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			(pVertexPos + 2)->pos2 = D3DXVECTOR3((pVertexPos + 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			(pVertexPos + 2)->pos3 = D3DXVECTOR3((pVertexPos + 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);*/
			break;
		}
	}

	for (int i = 0; i < m_Number.sigFigs; i++, pVertexPos++)
	{
		switch (i)
		{
		case 0:
			if (m_Number.digit[0] == 0)
			{
				if (m_Number.digit[1] == 0)
				{
					pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x - m_Number.Size.x * 2.0f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
					pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x - m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
					pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x - m_Number.Size.x * 2.0f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
					pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x - m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				}
				else
				{
					pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x - m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
					pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
					pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x - m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
					pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				}
			}
			else
			{
				pVertexPos->pos0 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos1 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos2 = D3DXVECTOR3(m_Number.Pos.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
				pVertexPos->pos3 = D3DXVECTOR3(m_Number.Pos.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			}
			break;
		case 3:
			pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x * 2.0f, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			break;
		default:
			pVertexPos->pos0 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			pVertexPos->pos1 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y - m_Number.Size.y * 0.5f, 0.0f);
			pVertexPos->pos2 = D3DXVECTOR3((pVertexPos - 1)->pos1.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			pVertexPos->pos3 = D3DXVECTOR3((pVertexPos - 1)->pos1.x + m_Number.Size.x, m_Number.Pos.y + m_Number.Size.y * 0.5f, 0.0f);
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::SpeedDigitUpdate
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�X�s�[�h�^�C�v���̍X�V
//------------------------------------------------------------------------------
void CNumber::SpeedDigitUpdate(void)
{
	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  �e�������̌v�Z���ݒ�
		if (i == 2)
		{
			m_Number.digit[i] = DIGIT_SYMBOL_DOT;
		}
		else if (i == m_Number.sigFigs - 1)
		{
			m_Number.digit[i] = DIGIT_SYMBOL_KNOT;
		}
		else
		{
			m_Number.digit[i] = *m_Number.value % Powi(10, m_SpeedCnt) / Powi(10, m_SpeedCnt - 1);

			m_SpeedCnt--;
			if (m_SpeedCnt == 1)
			{
				m_SpeedCnt = 4;
			}
		}

		//  �`��t���O�X�V����
		switch (i)
		{
		case 0:
			if (m_Number.digit[i] == 0)
			{
				//  �\�ʂ��O�ł���΁A�`�悵�Ȃ�
				m_Number.digitFlag[i] = false;
			}
			else
			{
				m_Number.digitFlag[i] = true;
			}
			break;
		default://  �ق��̕`�悷��
			m_Number.digitFlag[i] = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::TimeDigitUpdate
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�^�C���^�C�v���̍X�V
//------------------------------------------------------------------------------
void CNumber::TimeDigitUpdate(void)
{
	int nMinute;
	int nSecond;

	nMinute = *m_Number.value / FRAME;
	nSecond = *m_Number.value % FRAME;

	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  �e�������̌v�Z���ݒ�
		if (i == 2)
		{
			m_Number.digit[i] = DIGIT_SYMBOL_COLON;
		}
		else
		{
			//  ��
			if (i < 2)
			{
				m_Number.digit[i] = nMinute % Powi(10, m_MinuteCnt) / Powi(10, m_MinuteCnt - 1);
				m_MinuteCnt--;
				if (m_MinuteCnt == 0)
				{
					m_MinuteCnt = 2;
				}
			}

			//  �b
			else if (i > 2)
			{
				//  �e�������̌v�Z
				m_Number.digit[i] = nSecond % Powi(10, m_SecondCnt) / Powi(10, m_SecondCnt - 1);
				m_SecondCnt--;
				if (m_SecondCnt == 0)
				{
					m_SecondCnt = 2;
				}
			}
		}

		//  �S���`�悷��
		m_Number.digitFlag[i] = true;
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::ValueDigitUpdate
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�l�^�C�v���̍X�V
//------------------------------------------------------------------------------
void CNumber::ValueDigitUpdate(void)
{
	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  �e�������̌v�Z
		m_Number.digit[i] = *m_Number.value % Powi(10, m_Number.sigFigs - i) / Powi(10, m_Number.sigFigs - i - 1);

		if (m_Number.sigFigs == 1)
		{
			//  �ꌅ�̂ݎ��`�悷��
			m_Number.digitFlag[i] = true;
		}
		else
		{
			//  �ꌅ�ȊO�̎��A�t���O�̍X�V����
			switch (i)
			{
			case 0:	// �ŏ��̌��ʂ��O�ł���΁A�`�悵�Ȃ�
				if (m_Number.digit[i] == 0)
				{
					m_Number.digitFlag[i] = false;
				}
				else
				{
					m_Number.digitFlag[i] = true;
				}
				break;
			default:
				if (i != m_Number.sigFigs - 1)
				{
					if (m_Number.digit[i - 1] == 0)
					{
						//  �Ō�̌��ł͂Ȃ���΁A�O�̌��ƌ��݂̌����O�̎��`�悵�Ȃ�
						if (m_Number.digit[i] == 0)
						{
							m_Number.digitFlag[i] = false;
						}
						else
						{
							m_Number.digitFlag[i] = true;
						}
					}
				}
				else
				{
					//  �Ō�̌��K���`�悷��
					m_Number.digitFlag[i] = true;
				}
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::SetTexture
//	����:	�Ȃ�
//	�߂�l:	�Ȃ�
//	����:	�e�N�X�`�����W�̐ݒ�
//------------------------------------------------------------------------------
void CNumber::SetTexture(void)
{
	VERTEX_POS *pVertexPos = GetVertexPos();

	//  ���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//  ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < m_Number.sigFigs; i++, pVtx+=4)
	{
		pVtx[0].pos = (pVertexPos + i)->pos0;
		pVtx[1].pos = (pVertexPos + i)->pos1;
		pVtx[2].pos = (pVertexPos + i)->pos2;
		pVtx[3].pos = (pVertexPos + i)->pos3;

		switch (m_Number.digit[i]) {
		case DIGIT_SYMBOL_PERCENT:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.2f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);
			break;
		case DIGIT_SYMBOL_KNOT:
			pVtx[0].tex = D3DXVECTOR2(0.2f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.4f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.2f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.4f, 1.0f);
			break;
		case DIGIT_SYMBOL_COLON:
			pVtx[0].tex = D3DXVECTOR2(0.4f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.45f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.4f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.45f, 1.0f);
			break;
		case DIGIT_SYMBOL_DOT:
			pVtx[0].tex = D3DXVECTOR2(0.45f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.45f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
			break;
		default:
			pVtx[0].tex = D3DXVECTOR2(float(m_Number.digit[i] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(float(m_Number.digit[i] * 0.1f + 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(float(m_Number.digit[i] * 0.1f), 0.5f);
			pVtx[3].tex = D3DXVECTOR2(float(m_Number.digit[i] * 0.1f + 0.1f), 0.5f);
			break;
		}
	}

	//  ���_�f�[�^���A�����b�N����
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	�֐���:	int CNumber::Powi
//	����:	int x, int y
//	�߂�l:	(int)(powf((float)x, (float)y))
//	����:	int�^��powf
//------------------------------------------------------------------------------
int CNumber::Powi(int x, int y)
{
	return (int)(powf((float)x, (float)y));
}

//------------------------------------------------------------------------------
//	�֐���:	void CNumber::SetNumberFlag
//	����:	bool bFlag
//	�߂�l:	�Ȃ�
//	����:	�i���o�[�t���O��ݒ�
//------------------------------------------------------------------------------
void CNumber::SetNumberFlag(bool bFlag)
{
	m_Number.Flag = bFlag;
}