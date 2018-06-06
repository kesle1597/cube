#include "RenderClass.h"

RenderClass :: RenderClass()
{
	D3DDevice = 0;
	Sprite = 0;
}

RenderClass :: ~RenderClass()
{
	if(D3DDevice != 0)
	{
		D3DDevice -> Release();
		D3DDevice = 0;
	}

	if(Sprite != 0)
	{
		Sprite -> Release();
		Sprite = 0;
	}
}

bool RenderClass :: Initialize(HWND hwnd, HINSTANCE hinstance)
{
	IDirect3D9* d3d9;

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if(!d3d9)
	{
		MessageBox(0, L"RenderClass.cpp - Direct3dCreate9() Failed", 0, 0);

		return false;
	}

	D3DCAPS9 caps;
	d3d9 -> GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;

	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	DWORD level;
	if(SUCCEEDED(d3d9 -> CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_D24S8, false, D3DMULTISAMPLE_8_SAMPLES, &level)))
	{
		d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
		d3dpp.MultiSampleQuality = level - 1;
	}
	else if(SUCCEEDED(d3d9 -> CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_D24S8, false, D3DMULTISAMPLE_6_SAMPLES, &level)))
	{
		d3dpp.MultiSampleType = D3DMULTISAMPLE_6_SAMPLES;
		d3dpp.MultiSampleQuality = level - 1;
	}
	else if(SUCCEEDED(d3d9 -> CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_D24S8, false, D3DMULTISAMPLE_4_SAMPLES, &level)))
	{
		d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
		d3dpp.MultiSampleQuality = level - 1;
	}
	else if(SUCCEEDED(d3d9 -> CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_D24S8, false, D3DMULTISAMPLE_2_SAMPLES, &level)))
	{
		d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
		d3dpp.MultiSampleQuality = level - 1;
	}
	else
	{
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
	}

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true; 
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr;

	hr = d3d9 -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, &D3DDevice);
	if(FAILED(hr))
	{
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9 -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, &d3dpp, &D3DDevice);
		if(FAILED(hr))
		{
			d3d9 -> Release();
			MessageBox(0, L"RenderClass.cpp - CreateDevice() Failed", 0, 0);

			return false;
		}
	}

	d3d9 -> Release();

	hr = D3DXCreateSprite(D3DDevice, &Sprite);
	if(FAILED(hr))
	{
		MessageBox(0, L"RenderClass.cpp - CreateSprite() Failed", 0, 0);

		return false;
	}

	D3DXMatrixIdentity(&Identity);

	return true;
}

IDirect3DDevice9* RenderClass :: GetD3DDevice()
{
	return D3DDevice;
}

ID3DXSprite* RenderClass :: GetSprite()
{
	return Sprite;
}

void RenderClass :: SetRenderState()
{
	D3DLIGHT9 Light;
	Light.Type      = D3DLIGHT_DIRECTIONAL;
	Light.Diffuse   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Light.Specular  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Light.Ambient   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Light.Direction = D3DXVECTOR3(0.707f, 0.0f, 0.707f);

	D3DDevice -> SetLight(0, &Light);
	D3DDevice -> LightEnable(0, true);
	D3DDevice -> SetRenderState(D3DRS_LIGHTING, false);
	D3DDevice -> SetRenderState(D3DRS_NORMALIZENORMALS, true);

	D3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	D3DDevice -> SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	D3DDevice -> SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DDevice -> SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DDevice -> SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	D3DDevice -> SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	D3DDevice -> SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	D3DDevice -> SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	D3DDevice -> SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);
}

void RenderClass :: SetWorldMatrix(D3DXMATRIX world)
{
	D3DDevice -> SetTransform(D3DTS_WORLD, &world);
}

void RenderClass :: SetViewMatrix(D3DXMATRIX view)
{
	D3DDevice -> SetTransform(D3DTS_VIEW, &view);
}

void RenderClass :: SetProjectionMatrix(D3DXMATRIX proj)
{
	D3DDevice -> SetTransform(D3DTS_PROJECTION, &proj);
}

D3DXMATRIX RenderClass :: GetMatrixIdentity()
{
	return Identity;
}