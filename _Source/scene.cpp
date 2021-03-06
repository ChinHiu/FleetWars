//------------------------------------------------------------------------------
//	タイトル：		シーンの関数
//	ファイル名：	scene.cpp
//	作成者：		AT13B284 28 CHIN HIU
//	作成日：		2016/04/19
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	更新履歴:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "scene.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	グローバル変数
//------------------------------------------------------------------------------
CScene *CScene::m_Top[nPriorityMax] = { NULL,NULL,NULL,NULL,NULL };	//  先頭アドレスを宣言と初期化
CScene *CScene::m_Cur[nPriorityMax] = { NULL,NULL,NULL,NULL,NULL };	//  現在アドレスを宣言と初期化

//------------------------------------------------------------------------------
//	関数名:	CScene::CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CScene::CScene(int nPriority, OBJECT_TYPE Object_Type)
{
	m_Priority = nPriority;
	m_ObjectType = Object_Type;

	if (m_Top[m_Priority] == NULL)
	{
		m_Top[m_Priority]	= this;		//  先頭に今のアドレスを設定
		m_Cur[m_Priority]	= this;		//  現在に今のアドレスを設定
		m_Prev				= NULL;		//  前のポインタにNULLを設定
		m_Next				= NULL;		//  次のポインタにNULLを設定
	}
	else
	{
		m_Cur[m_Priority]->m_Next	= this;					//  現在の次のポインタに今のアドレスを設定
		m_Prev						= m_Cur[m_Priority];	//  前のポインタに現在を設定
		m_Cur[m_Priority]			= this;					//  現在に今のアドレスを設定
		m_Next						= NULL;					//  次のポインタにNULLを設定
	}
}

//------------------------------------------------------------------------------
//	関数名:	CScene::~CScene
//	引数:	なし
//	戻り値:	なし
//	説明:	コンストラクタ
//------------------------------------------------------------------------------
CScene::~CScene()
{
}

//------------------------------------------------------------------------------
//	関数名:	void CScene::UpdateAll
//	引数:	なし
//	戻り値:	なし
//	説明:	プロジェクトオール更新
//------------------------------------------------------------------------------
void CScene::UpdateAll(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		CScene *scene = m_Top[i];				//  先頭アドレスを指定
		CScene *next;							//  次のポインタを格納するワーク

		while (scene != NULL)
		{//  NULLではなければ、繰り返す
			next = scene->m_Next;	//  次のポインタを保存する
			scene->Update();			//  更新処理
			scene = next;				//  次のポインタをsceneに代入する
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CScene::DrawAll
//	引数:	なし
//	戻り値:	なし
//	説明:	プロジェクトオール描画
//------------------------------------------------------------------------------
void CScene::DrawAll(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		CScene *scene = m_Top[i];			//  先頭アドレスを指定

		while (scene != NULL)
		{//  NULLではなければ、繰り返す
			scene->Draw();				//  描画処理
			scene = scene->m_Next;		//  次のポインタをsceneに代入する
		}
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CScene::UninitAll
//	引数:	なし
//	戻り値:	なし
//	説明:	プロジェクトオール終了
//------------------------------------------------------------------------------
void CScene::UninitAll(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		CScene *scene = m_Top[i];			//  先頭アドレスを指定
		CScene *next;						//  次のポインタを格納するワーク

		while (scene != NULL)
		{//  NULLではなければ、繰り返す
			next = scene->m_Next;			//  次のポインタを保存する
			scene->Uninit();				//  更新処理
			delete scene;					//  インスタンス削除
			scene = next;					//  次のポインタをsceneに代入する
		}

		m_Top[i] = NULL;
	}
}

//------------------------------------------------------------------------------
//	関数名:	void CScene::Delete
//	引数:	なし
//	戻り値:	なし
//	説明:	リスト構造削除
//------------------------------------------------------------------------------
void CScene::Delete(void)
{
	for (int i = 0; i < nPriorityMax; i++)
	{
		if (this == m_Top[i])	m_Top[i]		= m_Next;	//  先頭アドレスに次のポインタを指定
		else					m_Prev->m_Next	= m_Next;	//  前のアドレスの次のポインタに次のポインタを指定

		if (this == m_Cur[i])	m_Cur[i]		= m_Prev;	//  現在アドレスに前のポインタを指定
		else					m_Next->m_Prev	= m_Prev;	//  次のアドレスの前のポインタに前のポインタを指定
	}
	delete this;
}