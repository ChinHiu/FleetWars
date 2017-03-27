//------------------------------------------------------------------------------
//	タイトル：		メッシュフィールド処理のヘッダー
//	ファイル名：	meshField.h
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/05/24
//------------------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	Const定義
//------------------------------------------------------------------------------

const int nWaveMax = 4;			//  波の最大数

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
//  テクスチャファイルパス
#define SEAMLESSMESHFIELD_TEXTURE_FILE	"./data/TEXTURE/Seamless_Field.jpg"	//  シムレースフィールド
#define SEAMLESSSEA_TEXTURE_FILE		"./data/TEXTURE/Seamless_Sea.jpg"	//  シムレース海
#define FIELD_TEXTURE_FILE				"./data/TEXTURE/Field.jpg"			//  フィールド
#define SEA_TEXTURE_FILE				"./data/TEXTURE/Sea.jpg"			//  海
#define ISLAND_MAP_FILE					"./data/MAP/MapData.txt"			//  マップデータ

//------------------------------------------------------------------------------
//	enum定義
//------------------------------------------------------------------------------

//  法線タイプ
typedef enum
{
	NONE = 0,
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_DOWN,
	RIGHT_DOWN,
	TOP_SIDE,
	DOWN_SIDE,
	LEFT_SIDE,
	RIGHT_SIDE,
	MIDDLE
}NORMAL_TYPE;

//  メッシュタイプ
typedef enum
{
	MESH_NONE = -1,
	MESH_ISLAND,
	MESH_SEA,
	MESH_TYPE_MAX
}MESH_TYPE;

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------

//  波データクラス
class CWave_Data
{
public:
	D3DXVECTOR2 K;
	float		A;
	float		Omega;
	float		t;
	float		OmegaT;
	float		WaveLength;
	float		k;
	float		testAk;

	CWave_Data()
		: K(D3DXVECTOR2(0, 0))
		, A(0.0f)
		, Omega(0.0f)
		, t(0.0f)
		, OmegaT(0.0f)
		, WaveLength(0.0f)
		, k(0.0f)
		, testAk(0.0f)
	{}
};

//  メッシュデータクラス
class CMesh_Data
{
public:
	int			WidthNum;		//  横の頂点数
	int			HeightNum;		//  縦の頂点数
	int			VertexNum;		//  総頂点数
	int			IndexNum;		//  インデックス数
	//int			PrimitiveNum;	//  ポリゴン数
	int			VertexId;		//  頂点番号
	float		SeamlessScl;	//  シームレス規模
	bool		SeamlessTex;	//  シームレステクスチャを使用するかどうか
	MESH_TYPE	Type;			//  メッシュタイプ

	CMesh_Data()
		: WidthNum(0)
		, HeightNum(0)
		, VertexNum(0)
		, IndexNum(0)
		//, PrimitiveNum(0)
		, VertexId(0)
		, SeamlessTex(false)
		, SeamlessScl(1.0f)
		, Type(MESH_NONE)
	{}
};

//  メッシュフィールドクラス
class CMeshField : public CScene
{
public:
	CMeshField(int nPriority = 0, OBJECT_TYPE Object_Type = OBJTYPE_NONE);
	~CMeshField();

	static			CMeshField *LoadMap(MESH_TYPE Mesh_Type, LPCSTR MAP_FILE, LPCSTR TEXTURE_FILE, bool SeamlessTex, float SeamlessScl);
	static			CMeshField *Create(MESH_TYPE Mesh_Type, LPCSTR TEXTURE_FILE, D3DXVECTOR3 pos, D3DXVECTOR3 size, int WidthNum, int HeightNum, bool SeamlessTex, float SeamlessScl);

	void			Init(void);
	void			Uninit(void);
	void			Update(void);
	void			Draw(void);

	void			CalculateVertex(void);
	void			CalculateNormal(void);
	void			CalculateNormalType(void);

	void			SetVertex(void);
	HRESULT			MakeIndex(LPDIRECT3DDEVICE9 pDevice);
	HRESULT			MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	int				CheckVertex(D3DXVECTOR3 pos);
	void			WaveInit(void);
	void			WaveUpdate(void);

	//  取得関数
	float			GetHeight(D3DXVECTOR3 pos);

private:
	LPDIRECT3DTEXTURE9			m_TextureBuffer;		//  テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;			//  頂点バッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_PositionBuffer;		//  元の頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;			//  インデックスバッファへのポインター

	D3DXVECTOR3					*m_VertexPos;			//  頂点座標
	D3DXVECTOR3					*m_Nor;					//  法線
	NORMAL_TYPE					*m_NorType;				//  法線のタイプ

#ifdef _DEBUG
	int							m_WaveID;				//  波番号
#endif

	CWave_Data					m_Wave[nWaveMax];		//  波データ
	CMesh_Data					m_Mesh;					//  メッシュデータ

	CMatrix						m_Matrix;				//  マトリクス情報
	D3DXVECTOR3					m_Pos;					//  位置
	D3DXVECTOR3					m_Rot;					//  回転
	D3DXVECTOR3					m_Scl;					//  拡大縮小
	D3DXVECTOR3					m_Size;					//  サイズ
};

#endif