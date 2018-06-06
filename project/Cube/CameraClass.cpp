#include "CameraClass.h"

bool CameraClass :: Initialize()
{
	Position = D3DXVECTOR3(15.0f, 15.0f, -15.0f);
	Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);

	D3DXMatrixPerspectiveFovLH(&Projection, D3DX_PI * 0.25f, (float)800 / (float)600, 1.0f, 1000.0f);

	return true;
}

D3DXMATRIX CameraClass :: GetViewMatrix()
{
	return View;
}

D3DXMATRIX CameraClass :: GetProjectionMatrix()
{
	return Projection;
}

D3DXVECTOR3 CameraClass :: GetPosition()
{
	return Position;
}

D3DXVECTOR3 CameraClass :: GetTarget()
{
	return Target;
}

D3DXVECTOR3 CameraClass :: GetUp()
{
	return Up;
}