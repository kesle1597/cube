#ifndef __OBJECTCUBECLASS_H__
#define __OBJECTCUBECLASS_H__

#include <d3dx9.h>

#define NONE 0
#define YAW 1
#define PITCH 2
#define ROLL 3

#pragma comment (lib, "d3dx9")

struct Vertex
{
	float x, y, z, nx, ny, nz, u, v;

	Vertex(float, float, float, float, float, float, float ,float);
};

class ObjectCubeClass
{
public:
	ObjectCubeClass();
	~ObjectCubeClass();

	bool Initialize(IDirect3DDevice9*);
	ID3DXMesh* GetMesh(int);
	void SetPosition(int, float, float, float);
	void SetPositionInitialize();
	void SetWorldMatrix(int);
	void SetWorldInitialize();
	void SetColorInitialize();
	D3DXMATRIX GetWorldMatrix(int);
	int GetColor(int, int);

	void SetObjectRotateData(int, bool);
	int GetObjectRotateState();
	void ObjectRotate(float);
	void ObjectVectorChange();
	void SetObjectSurfaceRotateData(int, bool);
	int GetObjectSurfaceRotateState();
	int ObjectSurfaceRotate(int*, float, float);
	D3DXVECTOR3 GetObjectRight();
	D3DXVECTOR3 GetObjectUp();
	D3DXVECTOR3 GetObjectFront();

	D3DMATERIAL9 GetMaterial();
	float GetMaterialAlpha();
	void SetMaterialAlpha(float);

	void SetCubeSurfacePointed(int, bool);
	bool GetCubeSurfacePointed();
	bool GetCubeSurfacePointed(int);
	void SetCubeSurfaceSelected(int, bool);
	bool GetCubeSurfaceSelected();
	bool GetCubeSurfaceSelected(int);

	void SetObjectAlphaChange(bool);
	void SetObjectAlphaIncrease(bool);
	bool GetObjectAlphaChange();
	bool GetObjectAlphaIncrease();
	
private:
	ID3DXMesh* Mesh[26];

	D3DXMATRIX World[26];
	D3DXMATRIX PrevWorld[26];
	D3DXMATRIX SurfaceWorld[26];

	D3DXVECTOR3 ObjectRight;
	D3DXVECTOR3 ObjectUp;
	D3DXVECTOR3 ObjectFront;
	D3DXVECTOR3 SurfaceVector[6];

	D3DXVECTOR3 ObjectPosition[26];
	D3DMATERIAL9 Material;

	bool ObjectAlphaChange;
	bool ObjectAlphaIncrease;

	int Color[26][6];

	int ObjectRotateState;
	bool ObjectRotateDirectionForward;
	int ObjectSurfaceRotateState;
	bool ObjectSurfaceRotateTimeDirection;
	float RotateAngle;

	bool CubeSurfacePointed[6];
	bool CubeSurfaceSelected[6];
};

#endif