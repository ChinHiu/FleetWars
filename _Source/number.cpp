//------------------------------------------------------------------------------
//	タイトル：		ナンバーの関数
//	ファイル名：	number.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/07/14
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "main.h"
#include "number.h"
#include "manager.h"
#include "input.h"
#include "keyboard.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define TIME_SIGFIGS (5)
#define POWER_SIGFIGS (4)
#define SPEED_SIGFIGS (5)
#define FRAME (60)

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//	関数名:	CNumber::CNumber
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CNumber::CNumber(int nPriority, OBJECT_TYPE Object_Type) : CScene(nPriority, Object_Type)
{
	//  頂点バッファへのポイン
	m_VertexBuffer	= NULL;

	//  テクスチャへのポインタ
	m_TextureBuffer = NULL;

}

//------------------------------------------------------------------------------
//	関数名:	CNumber::~CNumber
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CNumber::~CNumber()
{
}

//------------------------------------------------------------------------------
//	関数名:	CNumber *CNumber::Create
//	引数:	int value			//  値
//			int sigFigs			//  有効桁数
//			D3DXVECTOR3 pos		//  位置
//			D3DXVECTOR3 size	//  サイズ（幅、高さん、奥行き）
//			bool bUse			//  使用するかどうか
//	戻り値:	CNumber pNumber
//	説明:	ナンバーの生成
//------------------------------------------------------------------------------
CNumber *CNumber::Create(int *value, int sigFigs, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, NUMBER_TYPE Number_Type, bool bFlag)
{
	CNumber *pNumber;
	pNumber = new CNumber;

	//  情報の設定
	pNumber->m_Number.value		= value;		//  値
	pNumber->m_Number.Pos		= pos;			//  位置
	pNumber->m_Number.Type		= Number_Type;
	pNumber->m_Number.Size		= size;			//  サイズ（幅、高さん、奥行き）
	pNumber->m_Number.Flag		= bFlag;		//  使用するかどうか
	pNumber->m_Number.Col		= col;

	//  有効桁数
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

	//  初期化
	pNumber->Init();

	return pNumber;
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::Init
//	引数:	なし
//	戻り値:	なし
//	説明:	初期化処理
//------------------------------------------------------------------------------
void CNumber::Init(void)
{
	m_Number.digit		= new int[m_Number.sigFigs];
	m_Number.digitFlag	= new bool[m_Number.sigFigs];
	m_VertexPos			= new VERTEX_POS[m_Number.sigFigs];		

	m_MinuteCnt = m_SecondCnt = 2;

	m_SpeedCnt = 4;

	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  テクスチャの読み込み
	D3DXCreateTextureFromFile (
		pDevice,
		NUMBER_TEXTURE_FILE,	//  テクスチャファイル位置
		&m_TextureBuffer		//  テクスチャバッファへのポインタ
	);

	CalculateVertex();

	//  頂点情報の作成
	MakeVertex(pDevice);
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::Uninit
//	引数:	なし
//	戻り値:	なし
//	説明:	終了処理
//------------------------------------------------------------------------------
void CNumber::Uninit(void)
{
	//  テクスチャバッファの開放
	SAFE_RELEASE(m_TextureBuffer);

	//  頂点バッファの開放
	SAFE_RELEASE(m_VertexBuffer);

	delete m_Number.digit;
	delete m_Number.digitFlag;
	delete m_VertexPos;
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::Update
//	引数:	なし
//	戻り値:	なし
//	説明:	更新処理
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

	//  テクスチャの更新
	SetTexture();
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::Draw
//	引数:	なし
//	戻り値:	なし
//	説明:	描画処理
//------------------------------------------------------------------------------
void CNumber::Draw(void)
{
	//  デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//  頂点バッファをデータストリームにバインドする
	pDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VERTEX_2D));

	//  頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//  テクスチャの設定
	pDevice->SetTexture(0, m_TextureBuffer);

	////  Ｚテストを行う
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						//  Ｚテスト有効化
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					//  Ｚ値の更新を行わないが、Ｚテストを有効化する
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				//  Ｚテスト合格基準

	//  αテストを行う
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);				//  αテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);			//  αテスト合格基準
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);						//  α参照値

																		//  ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	////  フォグ有効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (m_Number.Flag)
	{
		for (int i = 0; i < m_Number.sigFigs; i++)
		{
			if (m_Number.digitFlag[i]) {
				//  ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * nNumVertex, nNumPolygon);
			}
		}
	}

	////  Ｚテストを行わない
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				//  Ｚテスト合格基準

	//  αテストを行わない
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);				//  αテスト無効化

	//  ライト有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	////  フォグ有効化
	//pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//------------------------------------------------------------------------------
//	関数名:	HRESULT CNumber::MakeVertex
//	引数:	LPDIRECT3DDEVICE9 pDevice
//	戻り値:	E_FAILだと作成失敗、S_OKだと作成成功
//	説明:	頂点バッファ情報作成
//------------------------------------------------------------------------------
HRESULT CNumber::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	//  頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
		(
		sizeof(VERTEX_2D) * nNumVertex * m_Number.sigFigs,	//  頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,									//  頂点バッファの使用法
		FVF_VERTEX_2D,										//  使用する頂点フォーマット
		D3DPOOL_MANAGED,									//  リソースのバッファを保持するメモリクラスを指定
		&m_VertexBuffer,									//  頂点バッファインターフェースへのポインタ
		NULL												//  NULLに設定
		)))
	{
		return E_FAIL;
	}

	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_VertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//  頂点座標の設定
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

		//  頂点カラーの設定
		pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = m_Number.Col;

		//  テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();

	return S_OK;
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::CalculateVertex
//	引数:	なし
//	戻り値:	なし
//	説明:	頂点座標を算出
//------------------------------------------------------------------------------
void CNumber::CalculateVertex(void)
{
	VERTEX_POS *pVertexPos = GetVertexPos();

	for (int i = 0; i < m_Number.sigFigs; i++, pVertexPos++)
	{
		switch (m_Number.Type)
		{
		case NUMBER_TYPE_SPEED: //  スピード
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
		case NUMBER_TYPE_POWER: //  パワー
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
		case NUMBER_TYPE_TIME: //  タイム
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
		case NUMBER_TYPE_DAMAGE: //  タイム
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
		default:				//  数字
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
//	関数名:	VERTEX_POS *CNumber::GetVertexPos
//	引数:	なし
//	戻り値:	m_VertexPos[0]
//	説明:	頂点座標を取得
//------------------------------------------------------------------------------
VERTEX_POS *CNumber::GetVertexPos(void)
{
	return &m_VertexPos[0];
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::PowerDigitUpdate
//	引数:	なし
//	戻り値:	なし
//	説明:	パワータイプ桁の更新
//------------------------------------------------------------------------------
void CNumber::PowerDigitUpdate(void)
{
	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  各桁数字の計算か設定
		if (i != m_Number.sigFigs - 1)
		{
			m_Number.digit[i] = *m_Number.value % Powi(10, m_Number.sigFigs - 1 - i) / Powi(10, m_Number.sigFigs - 2 - i);
		}
		else {
			m_Number.digit[i] = DIGIT_SYMBOL_PERCENT;
		}

		//  描画フラグ更新処理
		switch (i)
		{
		case 0:
			if (m_Number.digit[i] == 0)
			{
				//  百位が０の時描画しない
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
				//  百位と十位も０の時描画しない
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
		default://  ほかの描画する
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
		//  各桁数字の計算か設定
		if (i != m_Number.sigFigs - 1)
		{
			m_Number.digit[i] = *m_Number.value % Powi(10, m_Number.sigFigs - 1 - i) / Powi(10, m_Number.sigFigs - 2 - i);
		}
		else {
			m_Number.digit[i] = DIGIT_SYMBOL_PERCENT;
		}

		//  描画フラグ更新処理
		switch (i)
		{
		case 0:
			if (m_Number.digit[i] == 0)
			{
				//  百位が０の時描画しない
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
				//  百位と十位も０の時描画しない
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
		default://  ほかの描画する
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
//	関数名:	void CNumber::SpeedDigitUpdate
//	引数:	なし
//	戻り値:	なし
//	説明:	スピードタイプ桁の更新
//------------------------------------------------------------------------------
void CNumber::SpeedDigitUpdate(void)
{
	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  各桁数字の計算か設定
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

		//  描画フラグ更新処理
		switch (i)
		{
		case 0:
			if (m_Number.digit[i] == 0)
			{
				//  十位が０であれば、描画しない
				m_Number.digitFlag[i] = false;
			}
			else
			{
				m_Number.digitFlag[i] = true;
			}
			break;
		default://  ほかの描画する
			m_Number.digitFlag[i] = true;
			break;
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::TimeDigitUpdate
//	引数:	なし
//	戻り値:	なし
//	説明:	タイムタイプ桁の更新
//------------------------------------------------------------------------------
void CNumber::TimeDigitUpdate(void)
{
	int nMinute;
	int nSecond;

	nMinute = *m_Number.value / FRAME;
	nSecond = *m_Number.value % FRAME;

	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  各桁数字の計算か設定
		if (i == 2)
		{
			m_Number.digit[i] = DIGIT_SYMBOL_COLON;
		}
		else
		{
			//  分
			if (i < 2)
			{
				m_Number.digit[i] = nMinute % Powi(10, m_MinuteCnt) / Powi(10, m_MinuteCnt - 1);
				m_MinuteCnt--;
				if (m_MinuteCnt == 0)
				{
					m_MinuteCnt = 2;
				}
			}

			//  秒
			else if (i > 2)
			{
				//  各桁数字の計算
				m_Number.digit[i] = nSecond % Powi(10, m_SecondCnt) / Powi(10, m_SecondCnt - 1);
				m_SecondCnt--;
				if (m_SecondCnt == 0)
				{
					m_SecondCnt = 2;
				}
			}
		}

		//  全部描画する
		m_Number.digitFlag[i] = true;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::ValueDigitUpdate
//	引数:	なし
//	戻り値:	なし
//	説明:	値タイプ桁の更新
//------------------------------------------------------------------------------
void CNumber::ValueDigitUpdate(void)
{
	for (int i = 0; i < m_Number.sigFigs; i++)
	{
		//  各桁数字の計算
		m_Number.digit[i] = *m_Number.value % Powi(10, m_Number.sigFigs - i) / Powi(10, m_Number.sigFigs - i - 1);

		if (m_Number.sigFigs == 1)
		{
			//  一桁のみ時描画する
			m_Number.digitFlag[i] = true;
		}
		else
		{
			//  一桁以外の時、フラグの更新処理
			switch (i)
			{
			case 0:	// 最初の桁位が０であれば、描画しない
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
						//  最後の桁ではなければ、前の桁と現在の桁も０の時描画しない
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
					//  最後の桁必ず描画する
					m_Number.digitFlag[i] = true;
				}
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::SetTexture
//	引数:	なし
//	戻り値:	なし
//	説明:	テクスチャ座標の設定
//------------------------------------------------------------------------------
void CNumber::SetTexture(void)
{
	VERTEX_POS *pVertexPos = GetVertexPos();

	//  頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//  頂点データの範囲をロックし、頂点バッファへのポインタを取得
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

	//  頂点データをアンロックする
	m_VertexBuffer->Unlock();
}

//------------------------------------------------------------------------------
//	関数名:	int CNumber::Powi
//	引数:	int x, int y
//	戻り値:	(int)(powf((float)x, (float)y))
//	説明:	int型のpowf
//------------------------------------------------------------------------------
int CNumber::Powi(int x, int y)
{
	return (int)(powf((float)x, (float)y));
}

//------------------------------------------------------------------------------
//	関数名:	void CNumber::SetNumberFlag
//	引数:	bool bFlag
//	戻り値:	なし
//	説明:	ナンバーフラグを設定
//------------------------------------------------------------------------------
void CNumber::SetNumberFlag(bool bFlag)
{
	m_Number.Flag = bFlag;
}