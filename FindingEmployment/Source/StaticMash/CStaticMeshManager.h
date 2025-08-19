#pragma once

//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//_declspec()	:DLL����(�֐��A�N���X�A�N���X�̃����o�֐���)�G�N�X�|�[�g����
//align()		:(�����I��)16byte�Ŏg�p����
#define ALIGN16 _declspec( align(16) )

//�O���錾.
class CDirectX9;  // CDirectX9 �V���O���g���ւ̃A�N�Z�X�ɕK�v
class CDirectX11; // CDirectX11 �V���O���g���ւ̃A�N�Z�X�ɕK�v
class CStaticMesh; // CStaticMesh�̒�`�ɕK�v


/**********************************************
*	�X�^�e�B�b�N���b�V���}�l�[�W���[�N���X.
**/

class CStaticMeshManager
{
public:
	//���f���̎�ނ̗񋓌^.
	enum CMeshList
	{
		Player,
		Collision,
		Block,

		max,
	};
public:
	~CStaticMeshManager();

	// Create�֐��̈�������DirectX�C���X�^���X�̎Q�Ƃ��폜
	void Create();
	void Init();

	//�X�^�e�B�b�N�N���X�̃Q�b�g�C���X�^���X������
	CStaticMesh* GetMeshInstance(CMeshList MeshNo)
	{
		return m_pMesh[MeshNo];
	};

	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static CStaticMeshManager* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static CStaticMeshManager s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}


private:
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CStaticMeshManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CStaticMeshManager(const CStaticMeshManager& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CStaticMeshManager& operator = (const CStaticMeshManager& rhs) = delete;

	CStaticMesh* m_pMesh[CMeshList::max];

};
