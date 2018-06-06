#include "ObjectButtonClass.h"

bool ObjectButtonClass :: Initialize()
{
	ButtonPosition[0] = D3DXVECTOR3(600.0f, 270.0f, 0.0f);
	ButtonPosition[1] = D3DXVECTOR3(130.0f, 270.0f, 0.0f);
	ButtonPosition[2] = D3DXVECTOR3(510.0f, 450.0f, 0.0f);
	ButtonPosition[3] = D3DXVECTOR3(230.0f, 80.0f, 0.0f);
	ButtonPosition[4] = D3DXVECTOR3(230.0f, 450.0f, 0.0f);
	ButtonPosition[5] = D3DXVECTOR3(510.0f, 80.0f, 0.0f);

	ButtonRect[0].left = 595;	ButtonRect[0].right = 658;
	ButtonRect[0].top = 257;	ButtonRect[0].bottom = 318;

	ButtonRect[1].left = 129;	ButtonRect[1].right = 192;
	ButtonRect[1].top = 257;	ButtonRect[1].bottom = 318;

	ButtonRect[2].left = 506;	ButtonRect[2].right = 569;
	ButtonRect[2].top = 429;	ButtonRect[2].bottom = 490;

	ButtonRect[3].left = 228;	ButtonRect[3].right = 291;
	ButtonRect[3].top = 76;		ButtonRect[3].bottom = 137;

	ButtonRect[4].left = 228;	ButtonRect[4].right = 291;
	ButtonRect[4].top = 429;	ButtonRect[4].bottom = 490;

	ButtonRect[5].left = 506;	ButtonRect[5].right = 569;
	ButtonRect[5].top = 76;		ButtonRect[5].bottom = 137;

	for(int i = 0; i < 6; i++)
		ButtonSelected[i] = false;

	D3DXMATRIX t;
	D3DXMatrixIdentity(&OtherPosition[0]);
	D3DXMatrixScaling(&t, 0.75f, 0.75f, 1.0f);
	OtherPosition[0] *= t;
	D3DXMatrixTranslation(&t, 10.0f, 570.0f, 0.0f);
	OtherPosition[0] *= t;
	D3DXMatrixIdentity(&OtherPosition[1]);
	D3DXMatrixScaling(&t, 0.7f, 0.5f, 1.0f);
	OtherPosition[1] *= t;
	D3DXMatrixTranslation(&t, 10.0f, 10.0f, 0.0f);
	OtherPosition[1] *= t;

	D3DXMatrixIdentity(&MixButtonPosition);
	D3DXMatrixScaling(&t, 0.5f, 0.75f, 1.0f);
	MixButtonPosition *= t;
	D3DXMatrixTranslation(&t, 660.0f, 420.0f, 0.0f);
	MixButtonPosition *= t;

	MixButtonRect.left = 655;	MixButtonRect.right = 781;
	MixButtonRect.top = 400;	MixButtonRect.bottom = 445;

	D3DXMatrixIdentity(&ResetButtonPosition);
	D3DXMatrixScaling(&t, 0.5f, 0.75f, 1.0f);
	ResetButtonPosition *= t;
	D3DXMatrixTranslation(&t, 660.0f, 540.0f, 0.0f);
	ResetButtonPosition *= t;

	ResetButtonRect.left = 655;	ResetButtonRect.right = 781;
	ResetButtonRect.top = 515;	ResetButtonRect.bottom = 560;

	D3DXMatrixIdentity(&TimeAttackButtonPosition);
	D3DXMatrixScaling(&t, 0.5f, 0.75f, 1.0f);
	TimeAttackButtonPosition *= t;
	D3DXMatrixTranslation(&t, 660.0f, 480.0f, 0.0f);
	TimeAttackButtonPosition *= t;

	TimeAttackButtonRect.left = 655;	TimeAttackButtonRect.right = 781;
	TimeAttackButtonRect.top = 458;		TimeAttackButtonRect.bottom = 503;

	MixButtonSelected = false;
	ResetButtonSelected = false;
	TimeAttackButtonSelected = false;

	D3DXMatrixScaling(&t, 1.0f, 0.75f, 1.0f);
	for(int i = 0; i < 9; i++)
	{
		D3DXMatrixIdentity(&NumberPosition[i]);
		NumberPosition[i] *= t;
	}
	D3DXMatrixTranslation(&t, 620.0f, 10.0f, 0.0f);
	NumberPosition[0] *= t;
	D3DXMatrixTranslation(&t, 640.0f, 10.0f, 0.0f);
	NumberPosition[1] *= t;
	D3DXMatrixTranslation(&t, 670.0f, 10.0f, 0.0f);
	NumberPosition[2] *= t;
	D3DXMatrixTranslation(&t, 690.0f, 10.0f, 0.0f);
	NumberPosition[3] *= t;
	D3DXMatrixTranslation(&t, 720.0f, 10.0f, 0.0f);
	NumberPosition[4] *= t;
	D3DXMatrixTranslation(&t, 740.0f, 10.0f, 0.0f);
	NumberPosition[5] *= t;
	D3DXMatrixTranslation(&t, 760.0f, 10.0f, 0.0f);
	NumberPosition[6] *= t;
	D3DXMatrixTranslation(&t, 655.0f, 10.0f, 0.0f);
	NumberPosition[7] *= t;
	D3DXMatrixTranslation(&t, 705.0f, 10.0f, 0.0f);
	NumberPosition[8] *= t;

	Alpha = 1.0f;

	return true;
}

D3DXVECTOR3 ObjectButtonClass :: GetButtonPosition(int index)
{
	return ButtonPosition[index];
}

RECT ObjectButtonClass :: GetButtonRect(int index)
{
	return ButtonRect[index];
}

void ObjectButtonClass :: SetButtonSelected(int index, bool isselected)
{
	ButtonSelected[index] = isselected;
}

bool ObjectButtonClass :: GetButtonSelected(int index)
{
	return ButtonSelected[index];
}

D3DXMATRIX ObjectButtonClass :: GetOtherPosition(int index)
{
	return OtherPosition[index];
}

D3DXMATRIX ObjectButtonClass :: GetMixButtonPosition()
{
	return MixButtonPosition;
}

RECT ObjectButtonClass :: GetMixButtonRect()
{
	return MixButtonRect;
}

bool ObjectButtonClass :: GetMixButtonSelected()
{
	return MixButtonSelected;
}

void ObjectButtonClass :: SetMixButtonSelected(bool selected)
{
	MixButtonSelected = selected;
}

D3DXMATRIX ObjectButtonClass :: GetResetButtonPosition()
{
	return ResetButtonPosition;
}

RECT ObjectButtonClass :: GetResetButtonRect()
{
	return ResetButtonRect;
}

bool ObjectButtonClass :: GetResetButtonSelected()
{
	return ResetButtonSelected;
}

void ObjectButtonClass :: SetResetButtonSelected(bool selected)
{
	ResetButtonSelected = selected;
}

D3DXMATRIX ObjectButtonClass :: GetTimeAttackButtonPosition()
{
	return TimeAttackButtonPosition;
}

RECT ObjectButtonClass :: GetTimeAttackButtonRect()
{
	return TimeAttackButtonRect;
}

bool ObjectButtonClass :: GetTimeAttackButtonSelected()
{
	return TimeAttackButtonSelected;
}

void ObjectButtonClass :: SetTimeAttackButtonSelected(bool selected)
{
	TimeAttackButtonSelected = selected;
}

D3DXMATRIX ObjectButtonClass :: GetNumberPosition(int index)
{
	return NumberPosition[index];
}

float ObjectButtonClass :: GetMaterialAlpha()
{
	return Alpha;
}

void ObjectButtonClass :: SetMaterialAlpha(float alpha)
{
	Alpha = alpha;
}