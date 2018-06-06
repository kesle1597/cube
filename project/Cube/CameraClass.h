#ifndef __CAMERACLASS_H__
#define __CAMERACLASS_H__

#include <d3dx9.h>

#pragma comment (lib, "d3dx9")

class CameraClass
{
public:
	bool Initialize();

	D3DXMATRIX GetViewMatrix();
	D3DXMATRIX GetProjectionMatrix();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetTarget();
	D3DXVECTOR3 GetUp();

private:
	D3DXMATRIX View;
	D3DXMATRIX Projection;

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Target;
	D3DXVECTOR3 Up;
};

#endif