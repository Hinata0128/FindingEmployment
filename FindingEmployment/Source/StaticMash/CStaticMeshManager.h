#pragma once

//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning(disable:4005)

//_declspec()	:DLLから(関数、クラス、クラスのメンバ関数を)エクスポートする
//align()		:(強制的に)16byteで使用する
#define ALIGN16 _declspec( align(16) )

//前方宣言.
class CDirectX9;  // CDirectX9 シングルトンへのアクセスに必要
class CDirectX11; // CDirectX11 シングルトンへのアクセスに必要
class CStaticMesh; // CStaticMeshの定義に必要


/**********************************************
*	スタティックメッシュマネージャークラス.
**/

class CStaticMeshManager
{
public:
	//モデルの種類の列挙型.
	enum CMeshList
	{
		Player,
		Collision,
		Block,

		max,
	};
public:
	~CStaticMeshManager();

	// Create関数の引数からDirectXインスタンスの参照を削除
	void Create();
	void Init();

	//スタティッククラスのゲットインスタンスを書く
	CStaticMesh* GetMeshInstance(CMeshList MeshNo)
	{
		return m_pMesh[MeshNo];
	};

	//インスタンス取得(唯一のアクセス経路).
	//※関数の前にstaticを付けることでインスタンス生成しなくても使用できる.
	static CStaticMeshManager* GetInstance()
	{
		//唯一のインスタンスを作成する.
		//※staticで作成されたので2回目以降は、下の1行は無視される.
		static CStaticMeshManager s_Instance;	//s_:staticの意味.
		return &s_Instance;
	}


private:
	//外部からコンストラクタへのアクセスを禁止する.
	CStaticMeshManager();
	//コピーコンストラクタによるコピーを禁止する.
	//「=delete」で関数の定義を削除できる.
	CStaticMeshManager(const CStaticMeshManager& rhs) = delete;
	//代入演算子によるコピーを禁止する.
	//operator(オペレータ):演算子のオーバーロードで、演算の中身を拡張できる.
	CStaticMeshManager& operator = (const CStaticMeshManager& rhs) = delete;

	CStaticMesh* m_pMesh[CMeshList::max];

};
