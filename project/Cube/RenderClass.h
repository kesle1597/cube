#ifndef __RENDERCLASS_H__
#define __RENDERCLASS_H__

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9")
#pragma comment (lib, "d3dx9")

class RenderClass
{
public:
	RenderClass();
	~RenderClass();

	bool Initialize(HWND, HINSTANCE);
	IDirect3DDevice9* GetD3DDevice();
	ID3DXSprite* GetSprite();

	void SetRenderState();
	void SetWorldMatrix(D3DXMATRIX);
	void SetViewMatrix(D3DXMATRIX);
	void SetProjectionMatrix(D3DXMATRIX);
	D3DXMATRIX GetMatrixIdentity();

private:
	IDirect3DDevice9* D3DDevice;
	ID3DXSprite* Sprite;
	D3DXMATRIX Identity;
};

#endif