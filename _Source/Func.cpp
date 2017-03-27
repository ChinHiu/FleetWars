//------------------------------------------------------------------------------
//	�^�C�g���F		�^�C�g���̊֐�
//	�t�@�C�����F	title.cpp
//	�쐬�ҁF		AT13B284 28 CHIN HIU
//	�쐬���F		2016/07/11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�X�V����:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "Func.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//------------------------------------------------------------------------------

float CFunc::GetDistance(const D3DXVECTOR3 &TargetPos, const D3DXVECTOR3 &OwnPos) {
	D3DXVECTOR3 Vector = TargetPos - OwnPos;
	return D3DXVec3Length(&Vector);
}

float CFunc::GetXZRot(const D3DXVECTOR3 & TargetPos, const D3DXVECTOR3 & OwnPos)
{
	return atan2f(TargetPos.x - OwnPos.x, TargetPos.z - OwnPos.z);
}

float CFunc::GetYZRot(const D3DXVECTOR3 &TargetPos, const D3DXVECTOR3 &OwnPos) {
	D3DXVECTOR3 Vector = TargetPos - OwnPos;
	float fLength = sqrtf((Vector.x * Vector.x + Vector.z * Vector.z));
	return atan2f(OwnPos.y - TargetPos.y, fLength);
}

int CFunc::Powi(const int &x, const int &y)
{
	return (int)(powf((float)x, (float)y));
}

// OBB v.s. OBB
bool CFunc::OBBs(CObb &obb1, CObb &obb2)
{
	// �e�����x�N�g���̊m��
	// �iN***:�W���������x�N�g���j
	D3DXVECTOR3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLength(0);
	D3DXVECTOR3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLength(1);
	D3DXVECTOR3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLength(2);
	D3DXVECTOR3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLength(0);
	D3DXVECTOR3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLength(1);
	D3DXVECTOR3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLength(2);
	D3DXVECTOR3 Interval = obb1.GetPos() - obb2.GetPos();

	// ������ : Ae1
	FLOAT rA = D3DXVec3Length(&Ae1);
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	FLOAT L = (float)fabs(D3DXVec3Dot(&Interval, &NAe1));
	if (L > rA + rB)	return false; // �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NAe2));
	if (L > rA + rB)	return false;

	// ������ : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NAe3));
	if (L > rA + rB)	return false;

	// ������ : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe1));
	if (L > rA + rB)	return false;

	// ������ : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe2));
	if (L > rA + rB)	return false;

	// ������ : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &NBe3));
	if (L > rA + rB)	return false;

	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// ������ : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = (float)fabs(D3DXVec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}

// �������ɓ��e���ꂽ���������瓊�e���������Z�o
FLOAT CFunc::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	FLOAT r1 = (float)fabs(D3DXVec3Dot(Sep, e1));
	FLOAT r2 = (float)fabs(D3DXVec3Dot(Sep, e2));
	FLOAT r3 = e3 ? (float)(fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}


FLOAT CFunc::LenOBBToPoint(CObb &obb, D3DXVECTOR3 &pos)
{
	D3DXVECTOR3 Vec(0, 0, 0);   // �ŏI�I�ɒ��������߂�x�N�g��

	// �e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
	for (int i = 0; i < 3; i++)
	{
		FLOAT L = obb.GetLength(i);
		if (L <= 0) continue;  // L=0�͌v�Z�ł��Ȃ�
		FLOAT s = D3DXVec3Dot(&(pos - obb.GetPos()), &obb.GetDirect(i)) / L;

		// s�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
		s = (float)fabs(s);
		if (s > 1)	Vec += (1 - s) * L * obb.GetDirect(i);   // �͂ݏo���������̃x�N�g���Z�o
	}

	return D3DXVec3Length(&Vec);   // �������o��
}