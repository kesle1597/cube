#ifndef __TEXTURECLASS_H__
#define __TEXTURECLASS_H__

#include <d3dx9.h>

#define WHITE 0
#define RED 1
#define BLUE 2
#define GREEN 3
#define PURPLE 4
#define YELLOW 5
#define BLACK 6

#pragma comment (lib, "d3dx9")

class TextureClass
{
public:
	TextureClass();
	~TextureClass();

	bool Initialize(IDirect3DDevice9*);
	IDirect3DTexture9* GetCubeTexture(int, bool);
	IDirect3DTexture9* GetArrowTexture(int, bool);
	IDirect3DTexture9* GetOtherTexture(int);
	IDirect3DTexture9* GetMixButtonTexture(bool);
	IDirect3DTexture9* GetResetButtonTexture(bool);
	IDirect3DTexture9* GetTimeAttackButtonTexture(bool);
	IDirect3DTexture9* GetNumberTexture(int);

private:
	IDirect3DTexture9* CubeTexture[7][2];
	IDirect3DTexture9* ArrowTexture[6][2];
	IDirect3DTexture9* OtherTexture[2];
	IDirect3DTexture9* MixButtonTexture[2];
	IDirect3DTexture9* ResetButtonTexture[2];
	IDirect3DTexture9* TimeAttackButtonTexture[2];
	IDirect3DTexture9* NumberTexture[11];
};

#endif