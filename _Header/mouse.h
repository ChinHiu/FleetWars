//------------------------------------------------------------------------------
//	�^�C�g���F		�}�E�X�̃w�b�_�[
//	�t�@�C�����F	keyboard.h
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/05/10
//------------------------------------------------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CCursor;

//------------------------------------------------------------------------------
//	enum��`
//------------------------------------------------------------------------------

//  �}�E�X�{�^��
typedef enum
{
	DIM_LEFT = 0,		//  �}�E�X���{�^��
	DIM_RIGHT,			//  �}�E�X�E�{�^��
	DIM_CENTER,			//  �}�E�X���{�^��
	DIM_MAX
}MOUSE_BUTTONS;

//------------------------------------------------------------------------------
//	�\���̒�`
//------------------------------------------------------------------------------

//  �}�E�X�|�C���^���̍\����
typedef struct
{
	RECT		moveRect;	//  ��ʏ�œ�����͈�
	int			x;			//  X���W
	int			y;			//  Y���W
	int			z;
	int			moveAdd;	//  �ړ���
}MSTATE;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------

//  �}�E�X�N���X
class CMouse
{
public:
	CMouse();
	~CMouse();
	HRESULT			Init(HINSTANCE hInstance, HWND hWnd, LPDIRECTINPUT8 Input);
	void			Uninit(void);
	void			Update(void);
	void			MouseUpdate(void);


	D3DXVECTOR3		*CalcScreenToWorld(D3DXVECTOR3* pout, int Sx, int Sy, float fZ, float Screen_w, float Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);
	D3DXVECTOR3		*CalcScreenToXZ(D3DXVECTOR3* pout, int Sx, int Sy, float Screen_w, float Screen_h, D3DXMATRIX* View, D3DXMATRIX* Prj);

	//  �擾�֐�
	MSTATE			*GetMousePoint(void);
	DIMOUSESTATE	*GetMouseState(void);
	D3DXVECTOR3		*GetWorldPos(void);
	int				*GetInBlockNum(void);
	bool			GetPress(int key);
	bool			GetTrigger(int key);
	bool			GetRelease(int key);
	bool			GetRepeat(int key);
	CCursor			*GetCursor(void);

private:
	LPDIRECTINPUTDEVICE8	m_Dev;									//  IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
	DIMOUSESTATE			m_MouseState;							//  �}�E�X�̏�Ԃ��󂯎�郏�[�N
	BYTE					m_StateTrigger[nKeyMax];			//  �g���K�[��Ԃ��󂯎�郏�[�N
	BYTE					m_StateRelease[nKeyMax];			//  �����X��Ԃ��󂯎�郏�[�N
	BYTE					m_StateRepeat[nKeyMax];			//  ���s�[�g��Ԃ��󂯎�郏�[�N
	int						m_StateRepeatCnt[nKeyMax];			//  ���s�[�g�J�E���^���󂯎�郏�[�N
	MSTATE					m_Mouse;								//  �}�E�X�̃|�C���^�����󂯎�郏�[�N
	D3DXVECTOR3				m_Pos;									//  ���[���h�ʒu
	int						m_nInBlockNum;							//  ����u���b�N
	CCursor					*m_Cursor;								//  �R���\�[��
};

#endif