#ifndef __PICKINGCLASS_H__
#define __PICKINGCLASS_H__

#include <d3dx9.h>

class PickingClass
{
public:
	void CalcPickingRay(IDirect3DDevice9*, int, int);
	void TransformRay(D3DXMATRIX*);
	//bool RayBoxIntersectionTest1();
	bool RaySurfaceIntersectionTest(IDirect3DDevice9*, ID3DXMesh*, int, D3DXMATRIX, D3DXMATRIX, int, int);
	D3DXVECTOR3 GetRayOrigin();
	D3DXVECTOR3 GetRayDirection();

private:
	D3DXVECTOR3 RayOrigin;
	D3DXVECTOR3 RayDirection;
};

#endif