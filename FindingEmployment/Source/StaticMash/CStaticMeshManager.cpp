#include "CStaticMeshManager.h"
#include "DirectX/CDirectX9.h"  // CDirectX9 の定義が必要
#include "DirectX/CDirectX11.h" // CDirectX11 の定義が必要
#include "CStaticMesh.h"        // CStaticMesh の定義が必要 (もしなければ)

//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning(disable:4005)

CStaticMeshManager::CStaticMeshManager()
	: m_pMesh()
{

}

CStaticMeshManager::~CStaticMeshManager()
{
	// CStaticMeshのインスタンスをここで解放
	for (int i = 0; i < CMeshList::max; ++i)
	{
		if (m_pMesh[i])
		{
			delete m_pMesh[i];
			m_pMesh[i] = nullptr;
		}
	}
}

// Create関数の引数からDirectXインスタンスの参照を削除
void CStaticMeshManager::Create()
{
	for (int i = 0; i < CMeshList::max; ++i)
	{
		m_pMesh[i] = new CStaticMesh();
	}
	struct MeshList
	{
		int listNo;				//CMeshList列挙型を設定.
		const TCHAR path[256];	//ファイルの名前(パス付き).
	};
	MeshList MList[] =
	{
		{CMeshList::Player,		_T("Data\\Mesh\\Static\\Player\\Player.x")},
		{CMeshList::Collision, 	_T("Data\\Collision\\Sphere.x")},
		{CMeshList::Block, 		_T("Data\\Mesh\\Static\\Enemy\\Art.x")},
	};
	int list_max = sizeof(MList) / sizeof(MList[0]);
	for (int i = 0; i < list_max; ++i)
	{
		// CDirectX9とCDirectX11のシングルトンインスタンスを直接取得して使用
		if (FAILED(m_pMesh[i]->Init(
			*CDirectX9::GetInstance(),  // シングルトンインスタンスへの参照を渡す
			*CDirectX11::GetInstance(), // シングルトンインスタンスへの参照を渡す
			MList[i].path))) {

			return;
		};
	}
}

void CStaticMeshManager::Init()
{
}
