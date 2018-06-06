#include "PickingClass.h"

void PickingClass :: CalcPickingRay(IDirect3DDevice9* d3ddevice, int x, int y)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	D3DXMATRIX proj;

	d3ddevice -> GetViewport(&vp);
	d3ddevice -> GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f * (float)x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f * (float)y) / vp.Height) + 1.0f) / proj(1, 1);

	RayOrigin.x = 0.0f;
	RayOrigin.y = 0.0f;
	RayOrigin.z = 0.0f;

	RayDirection.x = px;
	RayDirection.y = py;
	RayDirection.z = 1.0f;
}

void PickingClass :: TransformRay(D3DXMATRIX* t)
{
	D3DXVec3TransformCoord(&RayOrigin, &RayOrigin, t);
	D3DXVec3TransformNormal(&RayDirection, &RayDirection, t);
	D3DXVec3Normalize(&RayDirection, &RayDirection);
}
/*
bool PickingClass :: RayBoxIntersectionTest1()
{
	D3DXVECTOR3 v = RayOrigin - D3DXVECTOR3(0.0f, 2.0f, -3.0f);

	float b = 2.0f * D3DXVec3Dot(&RayDirection, &v);
	float c = D3DXVec3Dot(&v, &v) - (1.0f);

	float discriminant = (b * b) - (4.0f * c);

	if(discriminant < 0.0f)
		return false;

	discriminant = sqrt(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	if(s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}
*/
bool PickingClass :: RaySurfaceIntersectionTest(IDirect3DDevice9* d3ddevice, ID3DXMesh* mesh, int surface, D3DXMATRIX world, D3DXMATRIX view, int x, int y)
{
	CalcPickingRay(d3ddevice, x, y);

	D3DXMATRIX t, viewinverse;
	t = world * view;
	D3DXMatrixInverse(&viewinverse, 0, &t);

	TransformRay(&viewinverse);

	BOOL IsHit;

	HRESULT hr;

	hr = D3DXIntersectSubset(mesh, surface, &RayOrigin, &RayDirection, &IsHit, 0, 0, 0, 0, 0, 0);
	if(FAILED(hr))
		return false;

	if(IsHit == TRUE)
		return true;
	else
		return false;
}

D3DXVECTOR3 PickingClass :: GetRayOrigin()
{
	return RayOrigin;
}

D3DXVECTOR3 PickingClass :: GetRayDirection()
{
	return RayDirection;
}