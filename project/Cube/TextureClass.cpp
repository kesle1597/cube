#include "TextureClass.h"

TextureClass :: TextureClass()
{
	for(int i = 0; i < 7; i++)
	{
		CubeTexture[i][0] = 0;
		CubeTexture[i][1] = 0;
	}

	for(int i = 0; i < 6; i++)
	{
		ArrowTexture[i][0] = 0;
		ArrowTexture[i][1] = 0;
	}

	for(int i = 0; i < 2; i++)
	{
		MixButtonTexture[i] = 0;
		ResetButtonTexture[i] = 0;
		TimeAttackButtonTexture[i] = 0;
		OtherTexture[i] = 0;
	}

	for(int i = 0; i < 11; i++)
		NumberTexture[i] = 0;
}

TextureClass :: ~TextureClass()
{
	for(int i = 0; i < 7; i++)
	{
		if(CubeTexture[i][0] != 0)
		{
			CubeTexture[i][0] -> Release();
			CubeTexture[i][0] = 0;
		}
		if(CubeTexture[i][1] != 0)
		{
			CubeTexture[i][1] -> Release();
			CubeTexture[i][1] = 0;
		}
	}

	for(int i = 0; i < 6; i++)
	{
		if(ArrowTexture[i][0] != 0)
		{
			ArrowTexture[i][0] -> Release();
			ArrowTexture[i][0] = 0;
		}
		if(ArrowTexture[i][1] != 0)
		{
			ArrowTexture[i][1] -> Release();
			ArrowTexture[i][1] = 0;
		}
	}

	for(int i = 0; i < 2; i++)
	{
		if(MixButtonTexture[i] != 0)
		{
			MixButtonTexture[i] -> Release();
			MixButtonTexture[i] = 0;
		}
		if(ResetButtonTexture[i] != 0)
		{
			ResetButtonTexture[i] -> Release();
			ResetButtonTexture[i] = 0;
		}
		if(TimeAttackButtonTexture[i] != 0)
		{
			TimeAttackButtonTexture[i] -> Release();
			TimeAttackButtonTexture[i] = 0;
		}
		if(OtherTexture[i] != 0)
		{
			OtherTexture[i] -> Release();
			OtherTexture[i] = 0;
		}
	}

	for(int i = 0; i < 11; i++)
	{
		if(NumberTexture[i] != 0)
		{
			NumberTexture[i] -> Release();
			NumberTexture[i] = 0;
		}
	}
}

bool TextureClass :: Initialize(IDirect3DDevice9* d3ddevice)
{
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\White.png", &CubeTexture[WHITE][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\WhiteReverse.png", &CubeTexture[WHITE][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\Red.png", &CubeTexture[RED][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\RedReverse.png", &CubeTexture[RED][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\Blue.png", &CubeTexture[BLUE][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\BlueReverse.png", &CubeTexture[BLUE][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\Green.png", &CubeTexture[GREEN][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\GreenReverse.png", &CubeTexture[GREEN][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\Purple.png", &CubeTexture[PURPLE][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\PurpleReverse.png", &CubeTexture[PURPLE][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\Yellow.png", &CubeTexture[YELLOW][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\YellowReverse.png", &CubeTexture[YELLOW][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\Black.png", &CubeTexture[BLACK][0]);

	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowBlackE.png", &ArrowTexture[0][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowWhiteE.png", &ArrowTexture[0][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowBlackW.png", &ArrowTexture[1][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowWhiteW.png", &ArrowTexture[1][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowBlackSE.png", &ArrowTexture[2][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowWhiteSE.png", &ArrowTexture[2][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowBlackNW.png", &ArrowTexture[3][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowWhiteNW.png", &ArrowTexture[3][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowBlackSW.png", &ArrowTexture[4][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowWhiteSW.png", &ArrowTexture[4][1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowBlackNE.png", &ArrowTexture[5][0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ArrowWhiteNE.png", &ArrowTexture[5][1]);

	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\01.png", &MixButtonTexture[0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\02.png", &ResetButtonTexture[0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\03.png", &TimeAttackButtonTexture[0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\04.png", &MixButtonTexture[1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\05.png", &ResetButtonTexture[1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\06.png", &TimeAttackButtonTexture[1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\other01.png", &OtherTexture[0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\other02.png", &OtherTexture[1]);
	
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n0.png", &NumberTexture[0]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n1.png", &NumberTexture[1]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n2.png", &NumberTexture[2]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n3.png", &NumberTexture[3]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n4.png", &NumberTexture[4]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n5.png", &NumberTexture[5]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n6.png", &NumberTexture[6]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n7.png", &NumberTexture[7]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n8.png", &NumberTexture[8]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\n9.png", &NumberTexture[9]);
	D3DXCreateTextureFromFile(d3ddevice, L"Texture\\ncolon.png", &NumberTexture[10]);


	return true;
}

IDirect3DTexture9* TextureClass :: GetCubeTexture(int index, bool reverse)
{
	return CubeTexture[index][reverse];
}

IDirect3DTexture9* TextureClass :: GetArrowTexture(int direction, bool selected)
{
	return ArrowTexture[direction][selected];
}

IDirect3DTexture9* TextureClass :: GetOtherTexture(int index)
{
	return OtherTexture[index];
}

IDirect3DTexture9* TextureClass :: GetMixButtonTexture(bool selected)
{
	return MixButtonTexture[selected];
}

IDirect3DTexture9* TextureClass :: GetResetButtonTexture(bool selected)
{
	return ResetButtonTexture[selected];
}

IDirect3DTexture9* TextureClass :: GetTimeAttackButtonTexture(bool selected)
{
	return TimeAttackButtonTexture[selected];
}

IDirect3DTexture9* TextureClass :: GetNumberTexture(int number)
{
	return NumberTexture[number];
}