#ifndef __OBJECTBUTTONCLASS_H__
#define __OBJECTBUTTONCLASS_H__

#include <windows.h>
#include <d3dx9.h>

class ObjectButtonClass
{
public:
	bool Initialize();
	D3DXVECTOR3 GetButtonPosition(int);
	RECT GetButtonRect(int);
	void SetButtonSelected(int, bool);
	bool GetButtonSelected(int);
	D3DXMATRIX GetMixButtonPosition();
	RECT GetMixButtonRect();
	D3DXMATRIX GetResetButtonPosition();
	RECT GetResetButtonRect();
	D3DXMATRIX GetTimeAttackButtonPosition();
	RECT GetTimeAttackButtonRect();
	void SetMixButtonSelected(bool);
	bool GetMixButtonSelected();
	void SetResetButtonSelected(bool);
	bool GetResetButtonSelected();
	void SetTimeAttackButtonSelected(bool);
	bool GetTimeAttackButtonSelected();
	float GetMaterialAlpha();
	void SetMaterialAlpha(float);

	D3DXMATRIX GetOtherPosition(int);
	D3DXMATRIX GetNumberPosition(int);
private:
	D3DXVECTOR3 ButtonPosition[6];
	RECT ButtonRect[6];
	bool ButtonSelected[6];
	D3DXMATRIX MixButtonPosition;
	RECT MixButtonRect;
	bool MixButtonSelected;
	D3DXMATRIX ResetButtonPosition;
	RECT ResetButtonRect;
	bool ResetButtonSelected;
	D3DXMATRIX TimeAttackButtonPosition;
	RECT TimeAttackButtonRect;
	bool TimeAttackButtonSelected;
	float Alpha;

	D3DXMATRIX OtherPosition[2];
	D3DXMATRIX NumberPosition[9];
};

#endif