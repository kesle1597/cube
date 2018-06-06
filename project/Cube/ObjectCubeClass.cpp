#include "ObjectCubeClass.h"
#include <vector>

#define WHITE 0
#define RED 1
#define BLUE 2
#define GREEN 3
#define PURPLE 4
#define YELLOW 5
#define BLACK 6

using namespace std;

Vertex :: Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _u, float _v)
{
	x = _x; y = _y; z = _z; nx = _nx; ny = _ny; nz = _nz; u = _u; v = _v;
}

ObjectCubeClass :: ObjectCubeClass()
{
	for(int i = 0; i < 26; i++)
		Mesh[i] = 0;
}

ObjectCubeClass :: ~ObjectCubeClass()
{
	for(int i = 0; i < 26; i++)
	{
		if(Mesh[i] != 0)
		{
			Mesh[i] -> Release();
			Mesh[i] = 0;
		}
	}
}

bool ObjectCubeClass :: Initialize(IDirect3DDevice9* d3ddevice)
{
	for(int i = 0; i < 26; i++)
	{
		D3DXMatrixIdentity(&PrevWorld[i]);
		D3DXMatrixIdentity(&SurfaceWorld[i]);

		D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, d3ddevice, &Mesh[i]);

		Vertex* vb;

		Mesh[i] -> LockVertexBuffer(0, (void**)&vb);

		//앞
		vb[0] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		vb[1] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		vb[2] = Vertex( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
		vb[3] = Vertex( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

		//뒤
		vb[4] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		vb[5] = Vertex( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
		vb[6] = Vertex( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		vb[7] = Vertex(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

		//상
		vb[8]  = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
		vb[9]  = Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		vb[10] = Vertex( 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
		vb[11] = Vertex( 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

		//하
		vb[12] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
		vb[13] = Vertex( 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
		vb[14] = Vertex( 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
		vb[15] = Vertex(-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

		//좌
		vb[16] = Vertex(-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vb[17] = Vertex(-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vb[18] = Vertex(-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		vb[19] = Vertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		//우
		vb[20] = Vertex( 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vb[21] = Vertex( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vb[22] = Vertex( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		vb[23] = Vertex( 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		Mesh[i] -> UnlockVertexBuffer();

		WORD* ib;

		Mesh[i] -> LockIndexBuffer(0, (void**)&ib);

		ib[0] = 0; ib[1] = 1; ib[2] = 2;
		ib[3] = 0; ib[4] = 2; ib[5] = 3;

		ib[6] = 4; ib[7]  = 5; ib[8]  = 6;
		ib[9] = 4; ib[10] = 6; ib[11] = 7;

		ib[12] = 8; ib[13] =  9; ib[14] = 10;
		ib[15] = 8; ib[16] = 10; ib[17] = 11;

		ib[18] = 12; ib[19] = 13; ib[20] = 14;
		ib[21] = 12; ib[22] = 14; ib[23] = 15;

		ib[24] = 16; ib[25] = 17; ib[26] = 18;
		ib[27] = 16; ib[28] = 18; ib[29] = 19;

		ib[30] = 20; ib[31] = 21; ib[32] = 22;
		ib[33] = 20; ib[34] = 22; ib[35] = 23;

		Mesh[i] -> UnlockIndexBuffer();

		DWORD* ab;

		Mesh[i] -> LockAttributeBuffer(0, &ab);

		for(int j = 0; j < 2; j++)
			ab[j] = 0;	//앞
		for(int j = 2; j < 4; j++)
			ab[j] = 1;	//뒤
		for(int j = 4; j < 6; j++)
			ab[j] = 2;	//상
		for(int j = 6; j < 8; j++)
			ab[j] = 3;	//하
		for(int j = 8; j < 10; j++)
			ab[j] = 4;	//좌
		for(int j = 10; j < 12; j++)
			ab[j] = 5;	//우

		Mesh[i] -> UnlockAttributeBuffer();

		std :: vector <DWORD> adjacencyBuffer(Mesh[i] -> GetNumFaces() * 3);
		Mesh[i] -> GenerateAdjacency(0.0f, &adjacencyBuffer[0]);
		Mesh[i] -> OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &adjacencyBuffer[0], 0, 0, 0);
	}

	ObjectRotateState = NONE;
	ObjectRotateDirectionForward = true;
	ObjectSurfaceRotateState = -1;
	ObjectSurfaceRotateTimeDirection = true;
	RotateAngle = 0.0f;

	for(int i = 0; i < 6; i++)
	{
		CubeSurfacePointed[i] = false;
		CubeSurfaceSelected[i] = false;
	}

	Material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	Material.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Power = 5.0f;

	ObjectAlphaChange = false;
	ObjectAlphaIncrease = false;

	return true;
}

ID3DXMesh* ObjectCubeClass :: GetMesh(int index)
{
	return Mesh[index];
}

void ObjectCubeClass :: SetPosition(int index, float x, float y, float z)
{
	ObjectPosition[index].x = x;
	ObjectPosition[index].y = y;
	ObjectPosition[index].z = z;
}

void ObjectCubeClass :: SetWorldMatrix(int index)
{
	D3DXMatrixTranslation(&World[index], ObjectPosition[index].x, ObjectPosition[index].y , ObjectPosition[index].z);
}

void ObjectCubeClass :: SetPositionInitialize()
{
	SetPosition(0, -2.0f, 2.0f, -2.0f);
	SetPosition(1, 0.0f, 2.0f, -2.0f);
	SetPosition(2, 2.0f, 2.0f, -2.0f);
	SetPosition(3, -2.0f, 0.0f, -2.0f);
	SetPosition(4, 0.0f, 0.0f, -2.0f);
	SetPosition(5, 2.0f, 0.0f, -2.0f);
	SetPosition(6, -2.0f, -2.0f, -2.0f);
	SetPosition(7, 0.0f, -2.0f, -2.0f);
	SetPosition(8, 2.0f, -2.0f, -2.0f);

	SetPosition(9, -2.0f, 2.0f, 0.0f);
	SetPosition(10, 0.0f, 2.0f, 0.0f);
	SetPosition(11, 2.0f, 2.0f, 0.0f);
	SetPosition(12, -2.0f, 0.0f, 0.0f);
	SetPosition(13, 2.0f, 0.0f, 0.0f);
	SetPosition(14, -2.0f, -2.0f, 0.0f);
	SetPosition(15, 0.0f, -2.0f, 0.0f);
	SetPosition(16, 2.0f, -2.0f, 0.0f);

	SetPosition(17, -2.0f, 2.0f, 2.0f);
	SetPosition(18, 0.0f, 2.0f, 2.0f);
	SetPosition(19, 2.0f, 2.0f, 2.0f);
	SetPosition(20, -2.0f, 0.0f, 2.0f);
	SetPosition(21, 0.0f, 0.0f, 2.0f);
	SetPosition(22, 2.0f, 0.0f, 2.0f);
	SetPosition(23, -2.0f, -2.0f, 2.0f);
	SetPosition(24, 0.0f, -2.0f, 2.0f);
	SetPosition(25, 2.0f, -2.0f, 2.0f);
}

void ObjectCubeClass :: SetWorldInitialize()
{
	for(int i = 0; i < 26; i++)
	{
		SetWorldMatrix(i);
		D3DXMatrixIdentity(&PrevWorld[i]);
		D3DXMatrixIdentity(&SurfaceWorld[i]);
	}

	ObjectRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	ObjectUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	ObjectFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	SurfaceVector[0] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	SurfaceVector[1] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	SurfaceVector[2] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	SurfaceVector[3] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	SurfaceVector[4] = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	SurfaceVector[5] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

void ObjectCubeClass :: SetColorInitialize()
{
	Color[0][0] = RED;		Color[0][1] = BLACK;	Color[0][2] = WHITE;
	Color[0][3] = BLACK;	Color[0][4] = GREEN;	Color[0][5] = BLACK;

	Color[1][0] = RED;		Color[1][1] = BLACK;	Color[1][2] = WHITE;
	Color[1][3] = BLACK;	Color[1][4] = BLACK;	Color[1][5] = BLACK;

	Color[2][0] = RED;		Color[2][1] = BLACK;	Color[2][2] = WHITE;
	Color[2][3] = BLACK;	Color[2][4] = BLACK;	Color[2][5] = BLUE;

	Color[3][0] = RED;		Color[3][1] = BLACK;	Color[3][2] = BLACK;
	Color[3][3] = BLACK;	Color[3][4] = GREEN;	Color[3][5] = BLACK;

	Color[4][0] = RED;		Color[4][1] = BLACK;	Color[4][2] = BLACK;
	Color[4][3] = BLACK;	Color[4][4] = BLACK;	Color[4][5] = BLACK;

	Color[5][0] = RED;		Color[5][1] = BLACK;	Color[5][2] = BLACK;
	Color[5][3] = BLACK;	Color[5][4] = BLACK;	Color[5][5] = BLUE;

	Color[6][0] = RED;		Color[6][1] = BLACK;	Color[6][2] = BLACK;
	Color[6][3] = YELLOW;	Color[6][4] = GREEN;	Color[6][5] = BLACK;

	Color[7][0] = RED;		Color[7][1] = BLACK;	Color[7][2] = BLACK;
	Color[7][3] = YELLOW;	Color[7][4] = BLACK;	Color[7][5] = BLACK;

	Color[8][0] = RED;		Color[8][1] = BLACK;	Color[8][2] = BLACK;
	Color[8][3] = YELLOW;	Color[8][4] = BLACK;	Color[8][5] = BLUE;
	

	Color[9][0] = BLACK;	Color[9][1] = BLACK;	Color[9][2] = WHITE;
	Color[9][3] = BLACK;	Color[9][4] = GREEN;	Color[9][5] = BLACK;

	Color[10][0] = BLACK;	Color[10][1] = BLACK;	Color[10][2] = WHITE;
	Color[10][3] = BLACK;	Color[10][4] = BLACK;	Color[10][5] = BLACK;

	Color[11][0] = BLACK;	Color[11][1] = BLACK;	Color[11][2] = WHITE;
	Color[11][3] = BLACK;	Color[11][4] = BLACK;	Color[11][5] = BLUE;

	Color[12][0] = BLACK;	Color[12][1] = BLACK;	Color[12][2] = BLACK;
	Color[12][3] = BLACK;	Color[12][4] = GREEN;	Color[12][5] = BLACK;

	Color[13][0] = BLACK;	Color[13][1] = BLACK;	Color[13][2] = BLACK;
	Color[13][3] = BLACK;	Color[13][4] = BLACK;	Color[13][5] = BLUE;

	Color[14][0] = BLACK;	Color[14][1] = BLACK;	Color[14][2] = BLACK;
	Color[14][3] = YELLOW;	Color[14][4] = GREEN;	Color[14][5] = BLACK;

	Color[15][0] = BLACK;	Color[15][1]= BLACK;	Color[15][2] = BLACK;
	Color[15][3] = YELLOW;	Color[15][4] = BLACK;	Color[15][5] = BLACK;

	Color[16][0] = BLACK;	Color[16][1] = BLACK;	Color[16][2] = BLACK;
	Color[16][3] = YELLOW;	Color[16][4] = BLACK;	Color[16][5] = BLUE;


	Color[17][0] = BLACK;	Color[17][1] = PURPLE;	Color[17][2] = WHITE;
	Color[17][3] = BLACK;	Color[17][4] = GREEN;	Color[17][5] = BLACK;

	Color[18][0] = BLACK;	Color[18][1] = PURPLE;	Color[18][2] = WHITE;
	Color[18][3] = BLACK;	Color[18][4] = BLACK;	Color[18][5] = BLACK;

	Color[19][0] = BLACK;	Color[19][1] = PURPLE;	Color[19][2] = WHITE;
	Color[19][3] = BLACK;	Color[19][4] = BLACK;	Color[19][5] = BLUE;

	Color[20][0] = BLACK;	Color[20][1] = PURPLE;	Color[20][2] = BLACK;
	Color[20][3] = BLACK;	Color[20][4] = GREEN;	Color[20][5] = BLACK;

	Color[21][0] = BLACK;	Color[21][1] = PURPLE;	Color[21][2] = BLACK;
	Color[21][3] = BLACK;	Color[21][4] = BLACK;	Color[21][5] = BLACK;

	Color[22][0] = BLACK;	Color[22][1] = PURPLE;	Color[22][2] = BLACK;
	Color[22][3] = BLACK;	Color[22][4] = BLACK;	Color[22][5] = BLUE;

	Color[23][0] = BLACK;	Color[23][1] = PURPLE;	Color[23][2] = BLACK;
	Color[23][3] = YELLOW;	Color[23][4] = GREEN;	Color[23][5] = BLACK;

	Color[24][0] = BLACK;	Color[24][1] = PURPLE;	Color[24][2] = BLACK;
	Color[24][3] = YELLOW;	Color[24][4] = BLACK;	Color[24][5] = BLACK;

	Color[25][0] = BLACK;	Color[25][1] = PURPLE;	Color[25][2] = BLACK;
	Color[25][3] = YELLOW;	Color[25][4] = BLACK;	Color[25][5] = BLUE;
}

D3DXMATRIX ObjectCubeClass :: GetWorldMatrix(int index)
{
	return World[index];
}

D3DMATERIAL9 ObjectCubeClass :: GetMaterial()
{
	return Material;
}

float ObjectCubeClass :: GetMaterialAlpha()
{
	return Material.Diffuse.a;
}

void ObjectCubeClass :: SetMaterialAlpha(float alpha)
{
	Material.Diffuse.a = alpha;
}

int ObjectCubeClass :: GetColor(int index, int face)
{
	return Color[index][face];
}

void ObjectCubeClass :: SetObjectRotateData(int rotate, bool direction)
{
	ObjectRotateState = rotate;
	ObjectRotateDirectionForward = direction;
}

int ObjectCubeClass :: GetObjectRotateState()
{
	return ObjectRotateState;
}

void ObjectCubeClass :: ObjectRotate(float timedelta)
{
	if(ObjectRotateState != NONE)
	{
		if(ObjectRotateDirectionForward == true)
		{
			RotateAngle += timedelta * 300.0f;
			if(RotateAngle > 90.0f)
			{
				RotateAngle = 90.0f;
				ObjectVectorChange();
			}
		}
		else
		{
			RotateAngle -= timedelta * 300.0f;
			if(RotateAngle < -90.0f)
			{
				RotateAngle = -90.0f;
				ObjectVectorChange();
			}
		}

		D3DXMATRIX t;
		switch(ObjectRotateState)
		{
		case YAW:
			D3DXMatrixRotationAxis(&t, &ObjectUp, D3DXToRadian(RotateAngle));
			break;
		case PITCH:
			D3DXMatrixRotationAxis(&t, &ObjectRight, D3DXToRadian(RotateAngle));
			break;
		case ROLL:
			D3DXMatrixRotationAxis(&t, &ObjectFront, D3DXToRadian(RotateAngle));
			break;
		}

		for(int i = 0; i < 26; i++)
		{
			D3DXMatrixTranslation(&World[i], ObjectPosition[i].x, ObjectPosition[i].y, ObjectPosition[i].z);

			World[i] = World[i] * SurfaceWorld[i] * t * PrevWorld[i];
		}

		if(RotateAngle == 90.0f || RotateAngle == -90.0f)
		{
			for(int i = 0; i < 26; i++)
				PrevWorld[i] = t * PrevWorld[i];
			RotateAngle = 0.0f;
			ObjectRotateState = NONE;
		}
	}
}

void ObjectCubeClass :: SetObjectSurfaceRotateData(int surface, bool timedirection)
{
	ObjectSurfaceRotateState = surface;
	ObjectSurfaceRotateTimeDirection = timedirection;
}

int ObjectCubeClass :: GetObjectSurfaceRotateState()
{
	return ObjectSurfaceRotateState;
}

int ObjectCubeClass :: ObjectSurfaceRotate(int* cubesurfacearray, float speed, float timedelta)
{
	if(cubesurfacearray != 0)
	{
		if(ObjectSurfaceRotateTimeDirection)
		{
			RotateAngle += timedelta * 300.0f * speed;
			if(RotateAngle > 90.0f)
				RotateAngle = 90.0f;
		}
		else
		{
			RotateAngle -= timedelta * 300.0f * speed;
			if(RotateAngle < -90.0f)
				RotateAngle = -90.0f;
		}

		D3DXMATRIX t;
		switch(ObjectSurfaceRotateState)
		{
		case 0:
			D3DXMatrixRotationAxis(&t, &SurfaceVector[0], D3DXToRadian(RotateAngle));
			break;
		case 1:
			D3DXMatrixRotationAxis(&t, &SurfaceVector[1], D3DXToRadian(RotateAngle));
			break;
		case 2:
			D3DXMatrixRotationAxis(&t, &SurfaceVector[2], D3DXToRadian(RotateAngle));
			break;
		case 3:
			D3DXMatrixRotationAxis(&t, &SurfaceVector[3], D3DXToRadian(RotateAngle));
			break;
		case 4:
			D3DXMatrixRotationAxis(&t, &SurfaceVector[4], D3DXToRadian(RotateAngle));
			break;
		case 5:
			D3DXMatrixRotationAxis(&t, &SurfaceVector[5], D3DXToRadian(RotateAngle));
			break;
		}

		for(int i = 0; i < 9; i++)
		{
			D3DXMatrixTranslation(&World[cubesurfacearray[i]], ObjectPosition[cubesurfacearray[i]].x, ObjectPosition[cubesurfacearray[i]].y, ObjectPosition[cubesurfacearray[i]].z);

			World[cubesurfacearray[i]] = World[cubesurfacearray[i]] * SurfaceWorld[cubesurfacearray[i]] * t * PrevWorld[cubesurfacearray[i]];
		}

		if(RotateAngle == 90.0f || RotateAngle == -90.0f)
		{
			for(int i = 0; i < 9; i++)
				SurfaceWorld[cubesurfacearray[i]] = SurfaceWorld[cubesurfacearray[i]] * t;
			RotateAngle = 0.0f;

			switch(ObjectSurfaceRotateState)
			{
			case 0:
				ObjectSurfaceRotateState = -1;
				if(ObjectSurfaceRotateTimeDirection)
					return 1;
				else
					return 2;
			case 1:
				ObjectSurfaceRotateState = -1;
				if(ObjectSurfaceRotateTimeDirection)
					return 3;
				else
					return 4;
			case 2:
				ObjectSurfaceRotateState = -1;
				if(ObjectSurfaceRotateTimeDirection)
					return 5;
				else
					return 6;
			case 3:
				ObjectSurfaceRotateState = -1;
				if(ObjectSurfaceRotateTimeDirection)
					return 7;
				else
					return 8;
			case 4:
				ObjectSurfaceRotateState = -1;
				if(ObjectSurfaceRotateTimeDirection)
					return 9;
				else
					return 10;
			case 5:
				ObjectSurfaceRotateState = -1;
				if(ObjectSurfaceRotateTimeDirection)
					return 11;
				else
					return 12;
			default:
				return 0;
			}
		}
		else
			return 0;
	}
	else
		return 0;
}

void ObjectCubeClass :: ObjectVectorChange()
{
	D3DXVECTOR3 t;

	switch(ObjectRotateState)
	{
	case YAW:
		if(ObjectRotateDirectionForward == true)
		{
			t = ObjectRight;
			ObjectRight = ObjectFront;
			ObjectFront = -t;
		}
		else
		{
			t = ObjectFront;
			ObjectFront = ObjectRight;
			ObjectRight = -t;
		}
		break;
	case PITCH:
		if(ObjectRotateDirectionForward == true)
		{
			t = ObjectFront;
			ObjectFront = ObjectUp;
			ObjectUp = -t;
		}
		else
		{
			t = ObjectUp;
			ObjectUp = ObjectFront;
			ObjectFront = -t;
		}
		break;
	case ROLL:
		if(ObjectRotateDirectionForward == true)
		{
			t = ObjectUp;
			ObjectUp = ObjectRight;
			ObjectRight = -t;
		}
		else
		{
			t = ObjectRight;
			ObjectRight = ObjectUp;
			ObjectUp = -t;
		}
		break;
	}
}

D3DXVECTOR3 ObjectCubeClass :: GetObjectRight()
{
	return ObjectRight;
}

D3DXVECTOR3 ObjectCubeClass :: GetObjectUp()
{
	return ObjectUp;
}

D3DXVECTOR3 ObjectCubeClass :: GetObjectFront()
{
	return ObjectFront;
}

void ObjectCubeClass :: SetCubeSurfacePointed(int index, bool pointed)
{
	CubeSurfacePointed[index] = pointed;
}

bool ObjectCubeClass :: GetCubeSurfacePointed()
{
	return CubeSurfacePointed[0] || CubeSurfacePointed[1] || CubeSurfacePointed[2] || CubeSurfacePointed[3] || CubeSurfacePointed[4] || CubeSurfacePointed[5];
}

bool ObjectCubeClass :: GetCubeSurfacePointed(int index)
{
	return CubeSurfacePointed[index];
}

void ObjectCubeClass :: SetCubeSurfaceSelected(int index, bool selected)
{
	CubeSurfaceSelected[index] = selected;
}

bool ObjectCubeClass :: GetCubeSurfaceSelected()
{
	return CubeSurfaceSelected[0] || CubeSurfaceSelected[1] || CubeSurfaceSelected[2] || CubeSurfaceSelected[3] || CubeSurfaceSelected[4] || CubeSurfaceSelected[5];
}

bool ObjectCubeClass :: GetCubeSurfaceSelected(int index)
{
	return CubeSurfaceSelected[index];
}

bool ObjectCubeClass :: GetObjectAlphaChange()
{
	return ObjectAlphaChange;
}

void ObjectCubeClass :: SetObjectAlphaChange(bool change)
{
	ObjectAlphaChange = change;
}

bool ObjectCubeClass :: GetObjectAlphaIncrease()
{
	return ObjectAlphaIncrease;
}

void ObjectCubeClass :: SetObjectAlphaIncrease(bool increase)
{
	ObjectAlphaIncrease = increase;
}