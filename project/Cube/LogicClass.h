#ifndef __LOGICCLASS_H__
#define __LOGICCLASS_H__

class LogicClass
{
public:
	bool Initialize();
	int* GetCubePositionArray(int);
	bool GetCurrCubeIsAnswer();
	void SetColorReverseArray(int, bool);
	bool GetColorReverseArray(int);
	void SetColorAtCubeSelected(int);
	void SetCubeRotateValue(int);
	void CubeRotate();
	void SetCubeMixing(bool);
	bool GetCubeMixing();
	void SetMixCount(int);
	int GetMixCount();
	bool GetCubeIsCorrect();
private:
	int CubePositionArray[6][9];
	int ColorArray[6][9];
	bool ColorReverseArray[26];
	int CubeRotateValue;
	bool CubeMixing;
	int MixCount;
};

#endif