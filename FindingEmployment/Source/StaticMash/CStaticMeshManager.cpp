#include "CStaticMeshManager.h"
#include "DirectX/CDirectX9.h"  // CDirectX9 �̒�`���K�v
#include "DirectX/CDirectX11.h" // CDirectX11 �̒�`���K�v
#include "CStaticMesh.h"        // CStaticMesh �̒�`���K�v (�����Ȃ����)

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

CStaticMeshManager::CStaticMeshManager()
	: m_pMesh()
{

}

CStaticMeshManager::~CStaticMeshManager()
{
	// CStaticMesh�̃C���X�^���X�������ŉ��
	for (int i = 0; i < CMeshList::max; ++i)
	{
		if (m_pMesh[i])
		{
			delete m_pMesh[i];
			m_pMesh[i] = nullptr;
		}
	}
}

// Create�֐��̈�������DirectX�C���X�^���X�̎Q�Ƃ��폜
void CStaticMeshManager::Create()
{
	for (int i = 0; i < CMeshList::max; ++i)
	{
		m_pMesh[i] = new CStaticMesh();
	}
	struct MeshList
	{
		int listNo;				//CMeshList�񋓌^��ݒ�.
		const TCHAR path[256];	//�t�@�C���̖��O(�p�X�t��).
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
		// CDirectX9��CDirectX11�̃V���O���g���C���X�^���X�𒼐ڎ擾���Ďg�p
		if (FAILED(m_pMesh[i]->Init(
			*CDirectX9::GetInstance(),  // �V���O���g���C���X�^���X�ւ̎Q�Ƃ�n��
			*CDirectX11::GetInstance(), // �V���O���g���C���X�^���X�ւ̎Q�Ƃ�n��
			MList[i].path))) {

			return;
		};
	}
}

void CStaticMeshManager::Init()
{
}
