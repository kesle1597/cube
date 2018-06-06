#include "LogicClass.h"

#define WHITE 0
#define RED 1
#define BLUE 2
#define GREEN 3
#define PURPLE 4
#define YELLOW 5
#define BLACK 6

bool LogicClass :: Initialize()
{
	//앞
	CubePositionArray[0][0] = 0;
	CubePositionArray[0][1] = 1;
	CubePositionArray[0][2] = 2;
	CubePositionArray[0][3] = 3;
	CubePositionArray[0][4] = 4;
	CubePositionArray[0][5] = 5;
	CubePositionArray[0][6] = 6;
	CubePositionArray[0][7] = 7;
	CubePositionArray[0][8] = 8;

	//뒤
	CubePositionArray[1][0] = 17;
	CubePositionArray[1][1] = 18;
	CubePositionArray[1][2] = 19;
	CubePositionArray[1][3] = 20;
	CubePositionArray[1][4] = 21;
	CubePositionArray[1][5] = 22;
	CubePositionArray[1][6] = 23;
	CubePositionArray[1][7] = 24;
	CubePositionArray[1][8] = 25;

	//상
	CubePositionArray[2][0] = 17;
	CubePositionArray[2][1] = 18;
	CubePositionArray[2][2] = 19;
	CubePositionArray[2][3] = 9;
	CubePositionArray[2][4] = 10;
	CubePositionArray[2][5] = 11;
	CubePositionArray[2][6] = 0;
	CubePositionArray[2][7] = 1;
	CubePositionArray[2][8] = 2;

	//하
	CubePositionArray[3][0] = 23;
	CubePositionArray[3][1] = 24;
	CubePositionArray[3][2] = 25;
	CubePositionArray[3][3] = 14;
	CubePositionArray[3][4] = 15;
	CubePositionArray[3][5] = 16;
	CubePositionArray[3][6] = 6;
	CubePositionArray[3][7] = 7;
	CubePositionArray[3][8] = 8;

	//좌
	CubePositionArray[4][0] = 0;
	CubePositionArray[4][1] = 9;
	CubePositionArray[4][2] = 17;
	CubePositionArray[4][3] = 3;
	CubePositionArray[4][4] = 12;
	CubePositionArray[4][5] = 20;
	CubePositionArray[4][6] = 6;
	CubePositionArray[4][7] = 14;
	CubePositionArray[4][8] = 23;

	//우
	CubePositionArray[5][0] = 2;
	CubePositionArray[5][1] = 11;
	CubePositionArray[5][2] = 19;
	CubePositionArray[5][3] = 5;
	CubePositionArray[5][4] = 13;
	CubePositionArray[5][5] = 22;
	CubePositionArray[5][6] = 8;
	CubePositionArray[5][7] = 16;
	CubePositionArray[5][8] = 25;

	for(int i = 0; i < 9; i++)
	{
		ColorArray[0][i] = RED;
		ColorArray[1][i] = PURPLE;
		ColorArray[2][i] = WHITE;
		ColorArray[3][i] = YELLOW;
		ColorArray[4][i] = GREEN;
		ColorArray[5][i] = BLUE;
	}

	for(int i = 0; i < 26; i++)
		ColorReverseArray[i] = false;

	CubeRotateValue = 0;
	CubeMixing = false;
	MixCount = 0;

	return true;
}

int* LogicClass :: GetCubePositionArray(int index)
{
	if(index < 0)
		return 0;
	else
		return CubePositionArray[index];
}

void LogicClass :: SetColorReverseArray(int index, bool reverse)
{
	ColorReverseArray[index] = reverse;
}

bool LogicClass :: GetColorReverseArray(int index)
{
	return ColorReverseArray[index];
}

void LogicClass :: SetColorAtCubeSelected(int surface)
{
	for(int i = 0; i < 26; i++)
		ColorReverseArray[i] = false;

	if(surface != -1)
	{
		for(int i = 0; i < 9; i++)
			ColorReverseArray[CubePositionArray[surface][i]] = true;
	}
}

void LogicClass :: SetCubeRotateValue(int value)
{
	CubeRotateValue = value;
}

void LogicClass :: CubeRotate()
{
	if(CubeRotateValue != 0)
	{
		int t1, t2, t3;
		switch(CubeRotateValue)
		{
		case 1:
			t1 = CubePositionArray[0][0];
			t2 = CubePositionArray[0][1];
			CubePositionArray[0][0] = CubePositionArray[0][6];
			CubePositionArray[0][1] = CubePositionArray[0][3];
			CubePositionArray[0][6] = CubePositionArray[0][8];
			CubePositionArray[0][3] = CubePositionArray[0][7];
			CubePositionArray[0][8] = CubePositionArray[0][2];
			CubePositionArray[0][7] = CubePositionArray[0][5];
			CubePositionArray[0][2] = t1;
			CubePositionArray[0][5] = t2;
			t1 = CubePositionArray[2][6];
			t2 = CubePositionArray[2][7];
			t3 = CubePositionArray[2][8];
			CubePositionArray[2][6] = CubePositionArray[4][6];
			CubePositionArray[2][7] = CubePositionArray[4][3];
			CubePositionArray[2][8] = CubePositionArray[4][0];
			CubePositionArray[4][6] = CubePositionArray[3][8];
			CubePositionArray[4][3] = CubePositionArray[3][7];
			CubePositionArray[4][0] = CubePositionArray[3][6];
			CubePositionArray[3][8] = CubePositionArray[5][0];
			CubePositionArray[3][7] = CubePositionArray[5][3];
			CubePositionArray[3][6] = CubePositionArray[5][6];
			CubePositionArray[5][0] = t1;
			CubePositionArray[5][3] = t2;
			CubePositionArray[5][6] = t3;

			t1 = ColorArray[0][0];
			t2 = ColorArray[0][1];
			ColorArray[0][0] = ColorArray[0][6];
			ColorArray[0][1] = ColorArray[0][3];
			ColorArray[0][6] = ColorArray[0][8];
			ColorArray[0][3] = ColorArray[0][7];
			ColorArray[0][8] = ColorArray[0][2];
			ColorArray[0][7] = ColorArray[0][5];
			ColorArray[0][2] = t1;
			ColorArray[0][5] = t2;
			t1 = ColorArray[2][6];
			t2 = ColorArray[2][7];
			t3 = ColorArray[2][8];
			ColorArray[2][6] = ColorArray[4][6];
			ColorArray[2][7] = ColorArray[4][3];
			ColorArray[2][8] = ColorArray[4][0];
			ColorArray[4][6] = ColorArray[3][8];
			ColorArray[4][3] = ColorArray[3][7];
			ColorArray[4][0] = ColorArray[3][6];
			ColorArray[3][8] = ColorArray[5][0];
			ColorArray[3][7] = ColorArray[5][3];
			ColorArray[3][6] = ColorArray[5][6];
			ColorArray[5][0] = t1;
			ColorArray[5][3] = t2;
			ColorArray[5][6] = t3;
			break;
		case 2:
			t1 = CubePositionArray[0][0];
			t2 = CubePositionArray[0][1];
			CubePositionArray[0][0] = CubePositionArray[0][2];
			CubePositionArray[0][1] = CubePositionArray[0][5];
			CubePositionArray[0][2] = CubePositionArray[0][8];
			CubePositionArray[0][5] = CubePositionArray[0][7];
			CubePositionArray[0][8] = CubePositionArray[0][6];
			CubePositionArray[0][7] = CubePositionArray[0][3];
			CubePositionArray[0][6] = t1;
			CubePositionArray[0][3] = t2;
			t1 = CubePositionArray[2][6];
			t2 = CubePositionArray[2][7];
			t3 = CubePositionArray[2][8];
			CubePositionArray[2][6] = CubePositionArray[5][0];
			CubePositionArray[2][7] = CubePositionArray[5][3];
			CubePositionArray[2][8] = CubePositionArray[5][6];
			CubePositionArray[5][0] = CubePositionArray[3][8];
			CubePositionArray[5][3] = CubePositionArray[3][7];
			CubePositionArray[5][6] = CubePositionArray[3][6];
			CubePositionArray[3][8] = CubePositionArray[4][6];
			CubePositionArray[3][7] = CubePositionArray[4][3];
			CubePositionArray[3][6] = CubePositionArray[4][0];
			CubePositionArray[4][6] = t1;
			CubePositionArray[4][3] = t2;
			CubePositionArray[4][0] = t3;

			t1 = ColorArray[0][0];
			t2 = ColorArray[0][1];
			ColorArray[0][0] = ColorArray[0][2];
			ColorArray[0][1] = ColorArray[0][5];
			ColorArray[0][2] = ColorArray[0][8];
			ColorArray[0][5] = ColorArray[0][7];
			ColorArray[0][8] = ColorArray[0][6];
			ColorArray[0][7] = ColorArray[0][3];
			ColorArray[0][6] = t1;
			ColorArray[0][3] = t2;
			t1 = ColorArray[2][6];
			t2 = ColorArray[2][7];
			t3 = ColorArray[2][8];
			ColorArray[2][6] = ColorArray[5][0];
			ColorArray[2][7] = ColorArray[5][3];
			ColorArray[2][8] = ColorArray[5][6];
			ColorArray[5][0] = ColorArray[3][8];
			ColorArray[5][3] = ColorArray[3][7];
			ColorArray[5][6] = ColorArray[3][6];
			ColorArray[3][8] = ColorArray[4][6];
			ColorArray[3][7] = ColorArray[4][3];
			ColorArray[3][6] = ColorArray[4][0];
			ColorArray[4][6] = t1;
			ColorArray[4][3] = t2;
			ColorArray[4][0] = t3;
			break;
		case 3:
			t1 = CubePositionArray[1][0];
			t2 = CubePositionArray[1][1];
			CubePositionArray[1][0] = CubePositionArray[1][2];
			CubePositionArray[1][1] = CubePositionArray[1][5];
			CubePositionArray[1][2] = CubePositionArray[1][8];
			CubePositionArray[1][5] = CubePositionArray[1][7];
			CubePositionArray[1][8] = CubePositionArray[1][6];
			CubePositionArray[1][7] = CubePositionArray[1][3];
			CubePositionArray[1][6] = t1;
			CubePositionArray[1][3] = t2;
			t1 = CubePositionArray[2][0];
			t2 = CubePositionArray[2][1];
			t3 = CubePositionArray[2][2];
			CubePositionArray[2][0] = CubePositionArray[5][2];
			CubePositionArray[2][1] = CubePositionArray[5][5];
			CubePositionArray[2][2] = CubePositionArray[5][8];
			CubePositionArray[5][2] = CubePositionArray[3][2];
			CubePositionArray[5][5] = CubePositionArray[3][1];
			CubePositionArray[5][8] = CubePositionArray[3][0];
			CubePositionArray[3][2] = CubePositionArray[4][8];
			CubePositionArray[3][1] = CubePositionArray[4][5];
			CubePositionArray[3][0] = CubePositionArray[4][2];
			CubePositionArray[4][8] = t1;
			CubePositionArray[4][5] = t2;
			CubePositionArray[4][2] = t3;

			t1 = ColorArray[1][0];
			t2 = ColorArray[1][1];
			ColorArray[1][0] = ColorArray[1][2];
			ColorArray[1][1] = ColorArray[1][5];
			ColorArray[1][2] = ColorArray[1][8];
			ColorArray[1][5] = ColorArray[1][7];
			ColorArray[1][8] = ColorArray[1][6];
			ColorArray[1][7] = ColorArray[1][3];
			ColorArray[1][6] = t1;
			ColorArray[1][3] = t2;
			t1 = ColorArray[2][0];
			t2 = ColorArray[2][1];
			t3 = ColorArray[2][2];
			ColorArray[2][0] = ColorArray[5][2];
			ColorArray[2][1] = ColorArray[5][5];
			ColorArray[2][2] = ColorArray[5][8];
			ColorArray[5][2] = ColorArray[3][2];
			ColorArray[5][5] = ColorArray[3][1];
			ColorArray[5][8] = ColorArray[3][0];
			ColorArray[3][2] = ColorArray[4][8];
			ColorArray[3][1] = ColorArray[4][5];
			ColorArray[3][0] = ColorArray[4][2];
			ColorArray[4][8] = t1;
			ColorArray[4][5] = t2;
			ColorArray[4][2] = t3;
			break;
		case 4:
			t1 = CubePositionArray[1][0];
			t2 = CubePositionArray[1][1];
			CubePositionArray[1][0] = CubePositionArray[1][6];
			CubePositionArray[1][1] = CubePositionArray[1][3];
			CubePositionArray[1][6] = CubePositionArray[1][8];
			CubePositionArray[1][3] = CubePositionArray[1][7];
			CubePositionArray[1][8] = CubePositionArray[1][2];
			CubePositionArray[1][7] = CubePositionArray[1][5];
			CubePositionArray[1][2] = t1;
			CubePositionArray[1][5] = t2;
			t1 = CubePositionArray[2][0];
			t2 = CubePositionArray[2][1];
			t3 = CubePositionArray[2][2];
			CubePositionArray[2][0] = CubePositionArray[4][8];
			CubePositionArray[2][1] = CubePositionArray[4][5];
			CubePositionArray[2][2] = CubePositionArray[4][2];
			CubePositionArray[4][8] = CubePositionArray[3][2];
			CubePositionArray[4][5] = CubePositionArray[3][1];
			CubePositionArray[4][2] = CubePositionArray[3][0];
			CubePositionArray[3][2] = CubePositionArray[5][2];
			CubePositionArray[3][1] = CubePositionArray[5][5];
			CubePositionArray[3][0] = CubePositionArray[5][8];
			CubePositionArray[5][2] = t1;
			CubePositionArray[5][5] = t2;
			CubePositionArray[5][8] = t3;

			t1 = ColorArray[1][0];
			t2 = ColorArray[1][1];
			ColorArray[1][0] = ColorArray[1][6];
			ColorArray[1][1] = ColorArray[1][3];
			ColorArray[1][6] = ColorArray[1][8];
			ColorArray[1][3] = ColorArray[1][7];
			ColorArray[1][8] = ColorArray[1][2];
			ColorArray[1][7] = ColorArray[1][5];
			ColorArray[1][2] = t1;
			ColorArray[1][5] = t2;
			t1 = ColorArray[2][0];
			t2 = ColorArray[2][1];
			t3 = ColorArray[2][2];
			ColorArray[2][0] = ColorArray[4][8];
			ColorArray[2][1] = ColorArray[4][5];
			ColorArray[2][2] = ColorArray[4][2];
			ColorArray[4][8] = ColorArray[3][2];
			ColorArray[4][5] = ColorArray[3][1];
			ColorArray[4][2] = ColorArray[3][0];
			ColorArray[3][2] = ColorArray[5][2];
			ColorArray[3][1] = ColorArray[5][5];
			ColorArray[3][0] = ColorArray[5][8];
			ColorArray[5][2] = t1;
			ColorArray[5][5] = t2;
			ColorArray[5][8] = t3;
			break;
		case 5:
			t1 = CubePositionArray[2][0];
			t2 = CubePositionArray[2][1];
			CubePositionArray[2][0] = CubePositionArray[2][6];
			CubePositionArray[2][1] = CubePositionArray[2][3];
			CubePositionArray[2][6] = CubePositionArray[2][8];
			CubePositionArray[2][3] = CubePositionArray[2][7];
			CubePositionArray[2][8] = CubePositionArray[2][2];
			CubePositionArray[2][7] = CubePositionArray[2][5];
			CubePositionArray[2][2] = t1;
			CubePositionArray[2][5] = t2;
			t1 = CubePositionArray[0][0];
			t2 = CubePositionArray[0][1];
			t3 = CubePositionArray[0][2];
			CubePositionArray[0][0] = CubePositionArray[5][0];
			CubePositionArray[0][1] = CubePositionArray[5][1];
			CubePositionArray[0][2] = CubePositionArray[5][2];
			CubePositionArray[5][0] = CubePositionArray[1][2];
			CubePositionArray[5][1] = CubePositionArray[1][1];
			CubePositionArray[5][2] = CubePositionArray[1][0];
			CubePositionArray[1][2] = CubePositionArray[4][2];
			CubePositionArray[1][1] = CubePositionArray[4][1];
			CubePositionArray[1][0] = CubePositionArray[4][0];
			CubePositionArray[4][2] = t1;
			CubePositionArray[4][1] = t2;
			CubePositionArray[4][0] = t3;

			t1 = ColorArray[2][0];
			t2 = ColorArray[2][1];
			ColorArray[2][0] = ColorArray[2][6];
			ColorArray[2][1] = ColorArray[2][3];
			ColorArray[2][6] = ColorArray[2][8];
			ColorArray[2][3] = ColorArray[2][7];
			ColorArray[2][8] = ColorArray[2][2];
			ColorArray[2][7] = ColorArray[2][5];
			ColorArray[2][2] = t1;
			ColorArray[2][5] = t2;
			t1 = ColorArray[0][0];
			t2 = ColorArray[0][1];
			t3 = ColorArray[0][2];
			ColorArray[0][0] = ColorArray[5][0];
			ColorArray[0][1] = ColorArray[5][1];
			ColorArray[0][2] = ColorArray[5][2];
			ColorArray[5][0] = ColorArray[1][2];
			ColorArray[5][1] = ColorArray[1][1];
			ColorArray[5][2] = ColorArray[1][0];
			ColorArray[1][2] = ColorArray[4][2];
			ColorArray[1][1] = ColorArray[4][1];
			ColorArray[1][0] = ColorArray[4][0];
			ColorArray[4][2] = t1;
			ColorArray[4][1] = t2;
			ColorArray[4][0] = t3;
			break;
		case 6:
			t1 = CubePositionArray[2][0];
			t2 = CubePositionArray[2][1];
			CubePositionArray[2][0] = CubePositionArray[2][2];
			CubePositionArray[2][1] = CubePositionArray[2][5];
			CubePositionArray[2][2] = CubePositionArray[2][8];
			CubePositionArray[2][5] = CubePositionArray[2][7];
			CubePositionArray[2][8] = CubePositionArray[2][6];
			CubePositionArray[2][7] = CubePositionArray[2][3];
			CubePositionArray[2][6] = t1;
			CubePositionArray[2][3] = t2;
			t1 = CubePositionArray[0][0];
			t2 = CubePositionArray[0][1];
			t3 = CubePositionArray[0][2];
			CubePositionArray[0][0] = CubePositionArray[4][2];
			CubePositionArray[0][1] = CubePositionArray[4][1];
			CubePositionArray[0][2] = CubePositionArray[4][0];
			CubePositionArray[4][2] = CubePositionArray[1][2];
			CubePositionArray[4][1] = CubePositionArray[1][1];
			CubePositionArray[4][0] = CubePositionArray[1][0];
			CubePositionArray[1][2] = CubePositionArray[5][0];
			CubePositionArray[1][1] = CubePositionArray[5][1];
			CubePositionArray[1][0] = CubePositionArray[5][2];
			CubePositionArray[5][0] = t1;
			CubePositionArray[5][1] = t2;
			CubePositionArray[5][2] = t3;

			t1 = ColorArray[2][0];
			t2 = ColorArray[2][1];
			ColorArray[2][0] = ColorArray[2][2];
			ColorArray[2][1] = ColorArray[2][5];
			ColorArray[2][2] = ColorArray[2][8];
			ColorArray[2][5] = ColorArray[2][7];
			ColorArray[2][8] = ColorArray[2][6];
			ColorArray[2][7] = ColorArray[2][3];
			ColorArray[2][6] = t1;
			ColorArray[2][3] = t2;
			t1 = ColorArray[0][0];
			t2 = ColorArray[0][1];
			t3 = ColorArray[0][2];
			ColorArray[0][0] = ColorArray[4][2];
			ColorArray[0][1] = ColorArray[4][1];
			ColorArray[0][2] = ColorArray[4][0];
			ColorArray[4][2] = ColorArray[1][2];
			ColorArray[4][1] = ColorArray[1][1];
			ColorArray[4][0] = ColorArray[1][0];
			ColorArray[1][2] = ColorArray[5][0];
			ColorArray[1][1] = ColorArray[5][1];
			ColorArray[1][0] = ColorArray[5][2];
			ColorArray[5][0] = t1;
			ColorArray[5][1] = t2;
			ColorArray[5][2] = t3;
			break;
		case 7:
			t1 = CubePositionArray[3][0];
			t2 = CubePositionArray[3][1];
			CubePositionArray[3][0] = CubePositionArray[3][2];
			CubePositionArray[3][1] = CubePositionArray[3][5];
			CubePositionArray[3][2] = CubePositionArray[3][8];
			CubePositionArray[3][5] = CubePositionArray[3][7];
			CubePositionArray[3][8] = CubePositionArray[3][6];
			CubePositionArray[3][7] = CubePositionArray[3][3];
			CubePositionArray[3][6] = t1;
			CubePositionArray[3][3] = t2;
			t1 = CubePositionArray[0][6];
			t2 = CubePositionArray[0][7];
			t3 = CubePositionArray[0][8];
			CubePositionArray[0][6] = CubePositionArray[4][8];
			CubePositionArray[0][7] = CubePositionArray[4][7];
			CubePositionArray[0][8] = CubePositionArray[4][6];
			CubePositionArray[4][8] = CubePositionArray[1][8];
			CubePositionArray[4][7] = CubePositionArray[1][7];
			CubePositionArray[4][6] = CubePositionArray[1][6];
			CubePositionArray[1][8] = CubePositionArray[5][6];
			CubePositionArray[1][7] = CubePositionArray[5][7];
			CubePositionArray[1][6] = CubePositionArray[5][8];
			CubePositionArray[5][6] = t1;
			CubePositionArray[5][7] = t2;
			CubePositionArray[5][8] = t3;

			t1 = ColorArray[3][0];
			t2 = ColorArray[3][1];
			ColorArray[3][0] = ColorArray[3][2];
			ColorArray[3][1] = ColorArray[3][5];
			ColorArray[3][2] = ColorArray[3][8];
			ColorArray[3][5] = ColorArray[3][7];
			ColorArray[3][8] = ColorArray[3][6];
			ColorArray[3][7] = ColorArray[3][3];
			ColorArray[3][6] = t1;
			ColorArray[3][3] = t2;
			t1 = ColorArray[0][6];
			t2 = ColorArray[0][7];
			t3 = ColorArray[0][8];
			ColorArray[0][6] = ColorArray[4][8];
			ColorArray[0][7] = ColorArray[4][7];
			ColorArray[0][8] = ColorArray[4][6];
			ColorArray[4][8] = ColorArray[1][8];
			ColorArray[4][7] = ColorArray[1][7];
			ColorArray[4][6] = ColorArray[1][6];
			ColorArray[1][8] = ColorArray[5][6];
			ColorArray[1][7] = ColorArray[5][7];
			ColorArray[1][6] = ColorArray[5][8];
			ColorArray[5][6] = t1;
			ColorArray[5][7] = t2;
			ColorArray[5][8] = t3;
			break;
		case 8:
			t1 = CubePositionArray[3][0];
			t2 = CubePositionArray[3][1];
			CubePositionArray[3][0] = CubePositionArray[3][6];
			CubePositionArray[3][1] = CubePositionArray[3][3];
			CubePositionArray[3][6] = CubePositionArray[3][8];
			CubePositionArray[3][3] = CubePositionArray[3][7];
			CubePositionArray[3][8] = CubePositionArray[3][2];
			CubePositionArray[3][7] = CubePositionArray[3][5];
			CubePositionArray[3][2] = t1;
			CubePositionArray[3][5] = t2;
			t1 = CubePositionArray[0][6];
			t2 = CubePositionArray[0][7];
			t3 = CubePositionArray[0][8];
			CubePositionArray[0][6] = CubePositionArray[5][6];
			CubePositionArray[0][7] = CubePositionArray[5][7];
			CubePositionArray[0][8] = CubePositionArray[5][8];
			CubePositionArray[5][6] = CubePositionArray[1][8];
			CubePositionArray[5][7] = CubePositionArray[1][7];
			CubePositionArray[5][8] = CubePositionArray[1][6];
			CubePositionArray[1][8] = CubePositionArray[4][8];
			CubePositionArray[1][7] = CubePositionArray[4][7];
			CubePositionArray[1][6] = CubePositionArray[4][6];
			CubePositionArray[4][8] = t1;
			CubePositionArray[4][7] = t2;
			CubePositionArray[4][6] = t3;

			t1 = ColorArray[3][0];
			t2 = ColorArray[3][1];
			ColorArray[3][0] = ColorArray[3][6];
			ColorArray[3][1] = ColorArray[3][3];
			ColorArray[3][6] = ColorArray[3][8];
			ColorArray[3][3] = ColorArray[3][7];
			ColorArray[3][8] = ColorArray[3][2];
			ColorArray[3][7] = ColorArray[3][5];
			ColorArray[3][2] = t1;
			ColorArray[3][5] = t2;
			t1 = ColorArray[0][6];
			t2 = ColorArray[0][7];
			t3 = ColorArray[0][8];
			ColorArray[0][6] = ColorArray[5][6];
			ColorArray[0][7] = ColorArray[5][7];
			ColorArray[0][8] = ColorArray[5][8];
			ColorArray[5][6] = ColorArray[1][8];
			ColorArray[5][7] = ColorArray[1][7];
			ColorArray[5][8] = ColorArray[1][6];
			ColorArray[1][8] = ColorArray[4][8];
			ColorArray[1][7] = ColorArray[4][7];
			ColorArray[1][6] = ColorArray[4][6];
			ColorArray[4][8] = t1;
			ColorArray[4][7] = t2;
			ColorArray[4][6] = t3;
			break;
		case 9:
			t1 = CubePositionArray[4][0];
			t2 = CubePositionArray[4][1];
			CubePositionArray[4][0] = CubePositionArray[4][2];
			CubePositionArray[4][1] = CubePositionArray[4][5];
			CubePositionArray[4][2] = CubePositionArray[4][8];
			CubePositionArray[4][5] = CubePositionArray[4][7];
			CubePositionArray[4][8] = CubePositionArray[4][6];
			CubePositionArray[4][7] = CubePositionArray[4][3];
			CubePositionArray[4][6] = t1;
			CubePositionArray[4][3] = t2;
			t1 = CubePositionArray[2][0];
			t2 = CubePositionArray[2][3];
			t3 = CubePositionArray[2][6];
			CubePositionArray[2][0] = CubePositionArray[1][6];
			CubePositionArray[2][3] = CubePositionArray[1][3];
			CubePositionArray[2][6] = CubePositionArray[1][0];
			CubePositionArray[1][6] = CubePositionArray[3][6];
			CubePositionArray[1][3] = CubePositionArray[3][3];
			CubePositionArray[1][0] = CubePositionArray[3][0];
			CubePositionArray[3][6] = CubePositionArray[0][0];
			CubePositionArray[3][3] = CubePositionArray[0][3];
			CubePositionArray[3][0] = CubePositionArray[0][6];
			CubePositionArray[0][0] = t1;
			CubePositionArray[0][3] = t2;
			CubePositionArray[0][6] = t3;

			t1 = ColorArray[4][0];
			t2 = ColorArray[4][1];
			ColorArray[4][0] = ColorArray[4][2];
			ColorArray[4][1] = ColorArray[4][5];
			ColorArray[4][2] = ColorArray[4][8];
			ColorArray[4][5] = ColorArray[4][7];
			ColorArray[4][8] = ColorArray[4][6];
			ColorArray[4][7] = ColorArray[4][3];
			ColorArray[4][6] = t1;
			ColorArray[4][3] = t2;
			t1 = ColorArray[2][0];
			t2 = ColorArray[2][3];
			t3 = ColorArray[2][6];
			ColorArray[2][0] = ColorArray[1][6];
			ColorArray[2][3] = ColorArray[1][3];
			ColorArray[2][6] = ColorArray[1][0];
			ColorArray[1][6] = ColorArray[3][6];
			ColorArray[1][3] = ColorArray[3][3];
			ColorArray[1][0] = ColorArray[3][0];
			ColorArray[3][6] = ColorArray[0][0];
			ColorArray[3][3] = ColorArray[0][3];
			ColorArray[3][0] = ColorArray[0][6];
			ColorArray[0][0] = t1;
			ColorArray[0][3] = t2;
			ColorArray[0][6] = t3;
			break;
		case 10:
			t1 = CubePositionArray[4][0];
			t2 = CubePositionArray[4][1];
			CubePositionArray[4][0] = CubePositionArray[4][6];
			CubePositionArray[4][1] = CubePositionArray[4][3];
			CubePositionArray[4][6] = CubePositionArray[4][8];
			CubePositionArray[4][3] = CubePositionArray[4][7];
			CubePositionArray[4][8] = CubePositionArray[4][2];
			CubePositionArray[4][7] = CubePositionArray[4][5];
			CubePositionArray[4][2] = t1;
			CubePositionArray[4][5] = t2;
			t1 = CubePositionArray[2][0];
			t2 = CubePositionArray[2][3];
			t3 = CubePositionArray[2][6];
			CubePositionArray[2][0] = CubePositionArray[0][0];
			CubePositionArray[2][3] = CubePositionArray[0][3];
			CubePositionArray[2][6] = CubePositionArray[0][6];
			CubePositionArray[0][0] = CubePositionArray[3][6];
			CubePositionArray[0][3] = CubePositionArray[3][3];
			CubePositionArray[0][6] = CubePositionArray[3][0];
			CubePositionArray[3][6] = CubePositionArray[1][6];
			CubePositionArray[3][3] = CubePositionArray[1][3];
			CubePositionArray[3][0] = CubePositionArray[1][0];
			CubePositionArray[1][6] = t1;
			CubePositionArray[1][3] = t2;
			CubePositionArray[1][0] = t3;

			t1 = ColorArray[4][0];
			t2 = ColorArray[4][1];
			ColorArray[4][0] = ColorArray[4][6];
			ColorArray[4][1] = ColorArray[4][3];
			ColorArray[4][6] = ColorArray[4][8];
			ColorArray[4][3] = ColorArray[4][7];
			ColorArray[4][8] = ColorArray[4][2];
			ColorArray[4][7] = ColorArray[4][5];
			ColorArray[4][2] = t1;
			ColorArray[4][5] = t2;
			t1 = ColorArray[2][0];
			t2 = ColorArray[2][3];
			t3 = ColorArray[2][6];
			ColorArray[2][0] = ColorArray[0][0];
			ColorArray[2][3] = ColorArray[0][3];
			ColorArray[2][6] = ColorArray[0][6];
			ColorArray[0][0] = ColorArray[3][6];
			ColorArray[0][3] = ColorArray[3][3];
			ColorArray[0][6] = ColorArray[3][0];
			ColorArray[3][6] = ColorArray[1][6];
			ColorArray[3][3] = ColorArray[1][3];
			ColorArray[3][0] = ColorArray[1][0];
			ColorArray[1][6] = t1;
			ColorArray[1][3] = t2;
			ColorArray[1][0] = t3;
			break;
		case 11:
			t1 = CubePositionArray[5][0];
			t2 = CubePositionArray[5][1];
			CubePositionArray[5][0] = CubePositionArray[5][6];
			CubePositionArray[5][1] = CubePositionArray[5][3];
			CubePositionArray[5][6] = CubePositionArray[5][8];
			CubePositionArray[5][3] = CubePositionArray[5][7];
			CubePositionArray[5][8] = CubePositionArray[5][2];
			CubePositionArray[5][7] = CubePositionArray[5][5];
			CubePositionArray[5][2] = t1;
			CubePositionArray[5][5] = t2;
			t1 = CubePositionArray[2][8];
			t2 = CubePositionArray[2][5];
			t3 = CubePositionArray[2][2];
			CubePositionArray[2][8] = CubePositionArray[0][8];
			CubePositionArray[2][5] = CubePositionArray[0][5];
			CubePositionArray[2][2] = CubePositionArray[0][2];
			CubePositionArray[0][8] = CubePositionArray[3][2];
			CubePositionArray[0][5] = CubePositionArray[3][5];
			CubePositionArray[0][2] = CubePositionArray[3][8];
			CubePositionArray[3][2] = CubePositionArray[1][2];
			CubePositionArray[3][5] = CubePositionArray[1][5];
			CubePositionArray[3][8] = CubePositionArray[1][8];
			CubePositionArray[1][2] = t1;
			CubePositionArray[1][5] = t2;
			CubePositionArray[1][8] = t3;

			t1 = ColorArray[5][0];
			t2 = ColorArray[5][1];
			ColorArray[5][0] = ColorArray[5][6];
			ColorArray[5][1] = ColorArray[5][3];
			ColorArray[5][6] = ColorArray[5][8];
			ColorArray[5][3] = ColorArray[5][7];
			ColorArray[5][8] = ColorArray[5][2];
			ColorArray[5][7] = ColorArray[5][5];
			ColorArray[5][2] = t1;
			ColorArray[5][5] = t2;
			t1 = ColorArray[2][8];
			t2 = ColorArray[2][5];
			t3 = ColorArray[2][2];
			ColorArray[2][8] = ColorArray[0][8];
			ColorArray[2][5] = ColorArray[0][5];
			ColorArray[2][2] = ColorArray[0][2];
			ColorArray[0][8] = ColorArray[3][2];
			ColorArray[0][5] = ColorArray[3][5];
			ColorArray[0][2] = ColorArray[3][8];
			ColorArray[3][2] = ColorArray[1][2];
			ColorArray[3][5] = ColorArray[1][5];
			ColorArray[3][8] = ColorArray[1][8];
			ColorArray[1][2] = t1;
			ColorArray[1][5] = t2;
			ColorArray[1][8] = t3;
			break;
		case 12:
			t1 = CubePositionArray[5][0];
			t2 = CubePositionArray[5][1];
			CubePositionArray[5][0] = CubePositionArray[5][2];
			CubePositionArray[5][1] = CubePositionArray[5][5];
			CubePositionArray[5][2] = CubePositionArray[5][8];
			CubePositionArray[5][5] = CubePositionArray[5][7];
			CubePositionArray[5][8] = CubePositionArray[5][6];
			CubePositionArray[5][7] = CubePositionArray[5][3];
			CubePositionArray[5][6] = t1;
			CubePositionArray[5][3] = t2;
			t1 = CubePositionArray[2][8];
			t2 = CubePositionArray[2][5];
			t3 = CubePositionArray[2][2];
			CubePositionArray[2][8] = CubePositionArray[1][2];
			CubePositionArray[2][5] = CubePositionArray[1][5];
			CubePositionArray[2][2] = CubePositionArray[1][8];
			CubePositionArray[1][2] = CubePositionArray[3][2];
			CubePositionArray[1][5] = CubePositionArray[3][5];
			CubePositionArray[1][8] = CubePositionArray[3][8];
			CubePositionArray[3][2] = CubePositionArray[0][8];
			CubePositionArray[3][5] = CubePositionArray[0][5];
			CubePositionArray[3][8] = CubePositionArray[0][2];
			CubePositionArray[0][8] = t1;
			CubePositionArray[0][5] = t2;
			CubePositionArray[0][2] = t3;

			t1 = ColorArray[5][0];
			t2 = ColorArray[5][1];
			ColorArray[5][0] = ColorArray[5][2];
			ColorArray[5][1] = ColorArray[5][5];
			ColorArray[5][2] = ColorArray[5][8];
			ColorArray[5][5] = ColorArray[5][7];
			ColorArray[5][8] = ColorArray[5][6];
			ColorArray[5][7] = ColorArray[5][3];
			ColorArray[5][6] = t1;
			ColorArray[5][3] = t2;
			t1 = ColorArray[2][8];
			t2 = ColorArray[2][5];
			t3 = ColorArray[2][2];
			ColorArray[2][8] = ColorArray[1][2];
			ColorArray[2][5] = ColorArray[1][5];
			ColorArray[2][2] = ColorArray[1][8];
			ColorArray[1][2] = ColorArray[3][2];
			ColorArray[1][5] = ColorArray[3][5];
			ColorArray[1][8] = ColorArray[3][8];
			ColorArray[3][2] = ColorArray[0][8];
			ColorArray[3][5] = ColorArray[0][5];
			ColorArray[3][8] = ColorArray[0][2];
			ColorArray[0][8] = t1;
			ColorArray[0][5] = t2;
			ColorArray[0][2] = t3;
			break;
		}
	}
}

void LogicClass :: SetCubeMixing(bool mixing)
{
	CubeMixing = mixing;
}

bool LogicClass :: GetCubeMixing()
{
	return CubeMixing;
}

void LogicClass :: SetMixCount(int count)
{
	MixCount = count;
}

int LogicClass :: GetMixCount()
{
	return MixCount;
}

bool LogicClass :: GetCubeIsCorrect()
{
	for(int i = 0; i < 9; i++)
	{
		if(ColorArray[0][i] != RED)
			return false;
		if(ColorArray[1][i] != PURPLE)
			return false;
		if(ColorArray[2][i] != WHITE)
			return false;
		if(ColorArray[3][i] != YELLOW)
			return false;
		if(ColorArray[4][i] != GREEN)
			return false;
		if(ColorArray[5][i] != BLUE)
			return false;
	}

	return true;
}