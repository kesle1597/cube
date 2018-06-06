#include "WindowClass.h"
#include "RenderClass.h"
#include "CameraClass.h"
#include "InputClass.h"
#include "TextureClass.h"
#include "ObjectCubeClass.h"
#include "ObjectButtonClass.h"
#include "PickingClass.h"
#include "LogicClass.h"
#include "GameClass.h"

WindowClass* WindowManager;
InputClass* InputManager;
RenderClass* RenderManager;
CameraClass* CameraManager;
TextureClass* TextureManager;
ObjectCubeClass* ObjectCubeManager;
ObjectButtonClass* ObjectButtonManager;
PickingClass* PickingManager;
LogicClass* LogicManager;
GameClass* GameManager;

void Setup();
bool Initialize(HINSTANCE, int);
void Cleanup();
void ButtonSelectProcess();
void MixButtonSelectProcess();
void ResetButtonSelectProcess();
void TimeAttackButtonSelectProcess();
void CubeRotateProcess();
void CubeSurfacePointProcess();
void CubeSurfaceSelectProcess();
void CubeSurfaceRotateDirectionProcess();
void CubeDrawProcess();
void CubeMixing();

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevInstance, LPSTR lpszcmdparam, int ncmdshow)
{
	timeBeginPeriod(1);

	Setup();
	if(!Initialize(hinstance, ncmdshow))
	{
		Cleanup();

		return 0;
	}

	RenderManager -> SetRenderState();
	RenderManager -> SetViewMatrix(CameraManager -> GetViewMatrix());
	RenderManager -> SetProjectionMatrix(CameraManager -> GetProjectionMatrix());

	ObjectCubeManager -> SetPositionInitialize();
	ObjectCubeManager -> SetWorldInitialize();
	ObjectCubeManager -> SetColorInitialize();

	float currtime, lasttime, timedelta;
	lasttime = (float)timeGetTime();

	MSG message;
	ZeroMemory(&message, sizeof(message));

	while(message.message != WM_QUIT)
	{
		if(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		currtime = (float)timeGetTime();
		timedelta = (currtime - lasttime) * 0.001f;
		lasttime = currtime;

		InputManager -> Update(WindowManager -> GetWindowHandle(), timedelta);
		if(LogicManager -> GetCubeMixing() == false)
		{
			if(ObjectCubeManager -> GetObjectAlphaChange() == false)
			{
				ButtonSelectProcess();
				MixButtonSelectProcess();
				ResetButtonSelectProcess();
				TimeAttackButtonSelectProcess();
				CubeSurfacePointProcess();
				CubeSurfaceSelectProcess();
				CubeSurfaceRotateDirectionProcess();
			}
		}
		else
			CubeMixing();

		if(GameManager -> GetTimeAttackIsReady() == true)
		{
			if(InputManager -> IsKeyUp(DIK_SPACE))
			{
				GameManager -> SetTimeAttackIsReady(false);
				GameManager -> SetTimeAttackPlaying(true);
			}
		}
		
		if(GameManager -> GetTimeAttackPlaying() == true)
		{
			if(LogicManager -> GetCubeIsCorrect() == true)
			{
				GameManager -> SetTimeAttackPlaying(false);
				MessageBox(0, L"축하합니다. 다 맞추셨습니다.", L"확인 메세지", 0);
			}
			else
				GameManager -> SetTimeRecord(GameManager -> GetTimeRecord() + timedelta);
		}

		CubeRotateProcess();
		ObjectCubeManager -> ObjectRotate(timedelta);
		if(LogicManager -> GetCubeMixing() == false)
			LogicManager -> SetCubeRotateValue(ObjectCubeManager -> ObjectSurfaceRotate(LogicManager -> GetCubePositionArray(ObjectCubeManager -> GetObjectSurfaceRotateState()), 1.0f, timedelta));
		else
			LogicManager -> SetCubeRotateValue(ObjectCubeManager -> ObjectSurfaceRotate(LogicManager -> GetCubePositionArray(ObjectCubeManager -> GetObjectSurfaceRotateState()), 1.5f, timedelta));
		
		LogicManager -> CubeRotate();

		if(ObjectCubeManager -> GetObjectAlphaChange() == true)
		{
			if(ObjectCubeManager -> GetObjectAlphaIncrease() == true)
			{
				ObjectCubeManager -> SetMaterialAlpha(ObjectCubeManager -> GetMaterialAlpha() + (timedelta * 2.0f));
				if(ObjectCubeManager -> GetMaterialAlpha() > 1.0f)
				{
					ObjectCubeManager -> SetMaterialAlpha(1.0f);
					ObjectCubeManager -> SetObjectAlphaChange(false);
					RenderManager -> GetD3DDevice() -> SetRenderState(D3DRS_LIGHTING, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetMaterialAlpha(ObjectCubeManager -> GetMaterialAlpha() - (timedelta * 2.0f));
				if(ObjectCubeManager -> GetMaterialAlpha() < 0.0f)
				{
					ObjectCubeManager -> SetMaterialAlpha(0.0f);
					ObjectCubeManager -> SetObjectAlphaIncrease(true);
					ObjectCubeManager -> SetWorldInitialize();
					LogicManager -> Initialize();
				}
			}
		}

		RenderManager -> GetD3DDevice() -> Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xeeeeeee, 1.0f, 0);
		RenderManager -> GetD3DDevice() -> BeginScene();

		CubeDrawProcess();

		RenderManager -> GetSprite() -> Begin(D3DXSPRITE_ALPHABLEND);

		RenderManager -> GetSprite() -> SetTransform(&RenderManager -> GetMatrixIdentity());
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetArrowTexture(0, ObjectButtonManager -> GetButtonSelected(0)), 0, 0, &ObjectButtonManager -> GetButtonPosition(0), 0xffffffff);
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetArrowTexture(1, ObjectButtonManager -> GetButtonSelected(1)), 0, 0, &ObjectButtonManager -> GetButtonPosition(1), 0xffffffff);
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetArrowTexture(2, ObjectButtonManager -> GetButtonSelected(2)), 0, 0, &ObjectButtonManager -> GetButtonPosition(2), 0xffffffff);
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetArrowTexture(3, ObjectButtonManager -> GetButtonSelected(3)), 0, 0, &ObjectButtonManager -> GetButtonPosition(3), 0xffffffff);
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetArrowTexture(4, ObjectButtonManager -> GetButtonSelected(4)), 0, 0, &ObjectButtonManager -> GetButtonPosition(4), 0xffffffff);
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetArrowTexture(5, ObjectButtonManager -> GetButtonSelected(5)), 0, 0, &ObjectButtonManager -> GetButtonPosition(5), 0xffffffff);

		if(GameManager -> GetTimeAttackMode() == true)
		{
			if(GameManager -> GetTimeAttackMixing() == true && ObjectButtonManager -> GetMaterialAlpha() > 0.0f)
			{
				ObjectButtonManager -> SetMaterialAlpha(ObjectButtonManager -> GetMaterialAlpha() - (timedelta * 2.0f));
				if(ObjectButtonManager -> GetMaterialAlpha() < 0.0f)
					ObjectButtonManager -> SetMaterialAlpha(0.0f);
			}
			else if(GameManager -> GetTimeAttackMixing() == false && GameManager -> GetTimeAttackIsReady() == false && GameManager -> GetTimeAttackPlaying() == false)
			{
				ObjectButtonManager -> SetMaterialAlpha(ObjectButtonManager -> GetMaterialAlpha() + (timedelta * 2.0f));
				if(ObjectButtonManager -> GetMaterialAlpha() > 1.0f)
				{
					ObjectButtonManager -> SetMaterialAlpha(1.0f);
					GameManager -> SetTimeAttackMode(false);
				}
			}
			
			RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetMixButtonPosition());
			RenderManager -> GetSprite() -> Draw(TextureManager -> GetMixButtonTexture(ObjectButtonManager -> GetMixButtonSelected()), 0, 0, 0, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, ObjectButtonManager -> GetMaterialAlpha()));
			RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetTimeAttackButtonPosition());
			RenderManager -> GetSprite() -> Draw(TextureManager -> GetTimeAttackButtonTexture(ObjectButtonManager -> GetTimeAttackButtonSelected()), 0, 0, 0, D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, ObjectButtonManager -> GetMaterialAlpha()));

		}
		else
		{
			RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetMixButtonPosition());
			RenderManager -> GetSprite() -> Draw(TextureManager -> GetMixButtonTexture(ObjectButtonManager -> GetMixButtonSelected()), 0, 0, 0, 0xffffffff);
			RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetTimeAttackButtonPosition());
			RenderManager -> GetSprite() -> Draw(TextureManager -> GetTimeAttackButtonTexture(ObjectButtonManager -> GetTimeAttackButtonSelected()), 0, 0, 0, 0xffffffff);
		}
		RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetResetButtonPosition());
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetResetButtonTexture(ObjectButtonManager -> GetResetButtonSelected()), 0, 0, 0, 0xffffffff);
		
		RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetOtherPosition(0));
		RenderManager -> GetSprite() -> Draw(TextureManager -> GetOtherTexture(0), 0, 0, 0, 0xffffffff);
		
		if(GameManager -> GetTimeAttackIsReady() == true)
		{
			RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetOtherPosition(1));
			RenderManager -> GetSprite() -> Draw(TextureManager -> GetOtherTexture(1), 0, 0, 0, 0xffffffff);
		}

		for(int i = 0; i < 9; i++)
		{
			RenderManager -> GetSprite() -> SetTransform(&ObjectButtonManager -> GetNumberPosition(i));
			switch(i)
			{
			case 0:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture((((int)(GameManager -> GetTimeRecord() / 60.0f)) % 60) / 10), 0, 0, 0, 0xffffffff);
				break;
			case 1:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture((((int)(GameManager -> GetTimeRecord() / 60.0f)) % 60) % 10), 0, 0, 0, 0xffffffff);
				break;
			case 2:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture((((int)GameManager -> GetTimeRecord()) % 60) / 10), 0, 0, 0, 0xffffffff);
				break;
			case 3:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture((((int)GameManager -> GetTimeRecord()) % 60) % 10), 0, 0, 0, 0xffffffff);
				break;
			case 4:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture(((int)(GameManager -> GetTimeRecord() * 10.0f)) % 10), 0, 0, 0, 0xffffffff);
				break;
			case 5:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture(((int)(GameManager -> GetTimeRecord() * 100.0f)) % 10), 0, 0, 0, 0xffffffff);
				break;
			case 6:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture(((int)(GameManager -> GetTimeRecord() * 1000.0f)) % 10), 0, 0, 0, 0xffffffff);
				break;
			default:
				RenderManager -> GetSprite() -> Draw(TextureManager -> GetNumberTexture(10), 0, 0, 0, 0xffffffff);
				break;
			}	
		}

		RenderManager -> GetSprite() -> End();

		RenderManager -> GetD3DDevice() -> EndScene();
		RenderManager -> GetD3DDevice() -> Present(0, 0, 0, 0);

		if(InputManager -> IsKeyUp(DIK_ESCAPE))
		{
			PostQuitMessage(0);
		}

		Sleep(16);
	}

	Cleanup();

	timeEndPeriod(1);

	return 0;
}

void Setup()
{
	WindowManager = new WindowClass();
	InputManager = new InputClass();
	RenderManager = new RenderClass();
	CameraManager = new CameraClass();
	TextureManager = new TextureClass();
	ObjectCubeManager = new ObjectCubeClass();
	ObjectButtonManager = new ObjectButtonClass();
	PickingManager = new PickingClass();
	LogicManager = new LogicClass();
	GameManager = new GameClass();
}

bool Initialize(HINSTANCE hinstance, int ncmdshow)
{
	if(!WindowManager -> Initialize(hinstance, ncmdshow))
	{
		MessageBox(0, L"Main.cpp - WindowManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!InputManager -> Initialize(WindowManager -> GetWindowHandle(), hinstance))
	{
		MessageBox(0, L"Main.cpp - InputManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!RenderManager -> Initialize(WindowManager -> GetWindowHandle(), hinstance))
	{
		MessageBox(0, L"Main.cpp - RenderManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!CameraManager -> Initialize())
	{
		MessageBox(0, L"Main.cpp - CameraManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!TextureManager -> Initialize(RenderManager -> GetD3DDevice()))
	{
		MessageBox(0, L"Main.cpp - TextureManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!ObjectCubeManager -> Initialize(RenderManager -> GetD3DDevice()))
	{
		MessageBox(0, L"Main.cpp - ObjectCubeManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!ObjectButtonManager -> Initialize())
	{
		MessageBox(0, L"Main.cpp - ObjectButtonManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!LogicManager -> Initialize())
	{
		MessageBox(0, L"Main.cpp - LogicManager -> Initialize() Failed", 0, 0);

		return false;
	}

	if(!GameManager -> Initialize())
	{
		MessageBox(0, L"Main.cpp - GameManager -> Initialize() Failed", 0, 0);

		return false;
	}

	return true;
}

void Cleanup()
{
	delete WindowManager;
	delete InputManager;
	delete RenderManager;
	delete CameraManager;
	delete TextureManager;
	delete ObjectCubeManager;
	delete ObjectButtonManager;
	delete PickingManager;
	delete LogicManager;
	delete GameManager;
}

void ButtonSelectProcess()
{
	if(ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1)
	{
		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetButtonRect(0).left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetButtonRect(0).right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetButtonRect(0).top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetButtonRect(0).bottom)
				ObjectButtonManager -> SetButtonSelected(0, true);
			else
				ObjectButtonManager -> SetButtonSelected(0, false);
		}
		else
			ObjectButtonManager -> SetButtonSelected(0, false);

		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetButtonRect(1).left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetButtonRect(1).right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetButtonRect(1).top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetButtonRect(1).bottom)
				ObjectButtonManager -> SetButtonSelected(1, true);
			else
				ObjectButtonManager -> SetButtonSelected(1, false);
		}
		else
			ObjectButtonManager -> SetButtonSelected(1, false);

		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetButtonRect(2).left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetButtonRect(2).right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetButtonRect(2).top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetButtonRect(2).bottom)
				ObjectButtonManager -> SetButtonSelected(2, true);
			else
				ObjectButtonManager -> SetButtonSelected(2, false);
		}
		else
			ObjectButtonManager -> SetButtonSelected(2, false);

		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetButtonRect(3).left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetButtonRect(3).right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetButtonRect(3).top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetButtonRect(3).bottom)
				ObjectButtonManager -> SetButtonSelected(3, true);
			else
				ObjectButtonManager -> SetButtonSelected(3, false);
		}
		else
			ObjectButtonManager -> SetButtonSelected(3, false);

		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetButtonRect(4).left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetButtonRect(4).right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetButtonRect(4).top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetButtonRect(4).bottom)
				ObjectButtonManager -> SetButtonSelected(4, true);
			else
				ObjectButtonManager -> SetButtonSelected(4, false);
		}
		else
			ObjectButtonManager -> SetButtonSelected(4, false);

		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetButtonRect(5).left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetButtonRect(5).right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetButtonRect(5).top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetButtonRect(5).bottom)
				ObjectButtonManager -> SetButtonSelected(5, true);
			else
				ObjectButtonManager -> SetButtonSelected(5, false);
		}
		else
			ObjectButtonManager -> SetButtonSelected(5, false);
	}
	else
	{
		ObjectButtonManager -> SetButtonSelected(0, false);
		ObjectButtonManager -> SetButtonSelected(1, false);
		ObjectButtonManager -> SetButtonSelected(2, false);
		ObjectButtonManager -> SetButtonSelected(3, false);
		ObjectButtonManager -> SetButtonSelected(4, false);
		ObjectButtonManager -> SetButtonSelected(5, false);
	}
}

void MixButtonSelectProcess()
{
	if(ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1 && GameManager -> GetTimeAttackMode() == false)
	{
		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetMixButtonRect().left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetMixButtonRect().right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetMixButtonRect().top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetMixButtonRect().bottom)
				ObjectButtonManager -> SetMixButtonSelected(true);
			else
				ObjectButtonManager -> SetMixButtonSelected(false);
		}
		else
			ObjectButtonManager -> SetMixButtonSelected(false);

		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetMixButtonSelected())
		{
			LogicManager -> SetCubeMixing(true);
			ObjectButtonManager -> SetMixButtonSelected(false);
		}
	}
}

void ResetButtonSelectProcess()
{
	if(ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1)
	{
		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetResetButtonRect().left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetResetButtonRect().right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetResetButtonRect().top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetResetButtonRect().bottom)
				ObjectButtonManager -> SetResetButtonSelected(true);
			else
				ObjectButtonManager -> SetResetButtonSelected(false);
		}
		else
			ObjectButtonManager -> SetResetButtonSelected(false);

		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetResetButtonSelected())
		{
			if(GameManager -> GetTimeAttackMode() == true)
			{
				GameManager -> SetTimeAttackIsReady(false);
				GameManager -> SetTimeAttackPlaying(false);
			}
			ObjectButtonManager -> SetResetButtonSelected(false);
			ObjectCubeManager -> SetObjectAlphaChange(true);
			ObjectCubeManager -> SetObjectAlphaIncrease(false);
			RenderManager -> GetD3DDevice() -> SetRenderState(D3DRS_LIGHTING, true);
		}
	}
}

void TimeAttackButtonSelectProcess()
{
	if(ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1 && GameManager -> GetTimeAttackMode() == false)
	{
		if(InputManager -> GetMouseCursorPos().x >= ObjectButtonManager -> GetTimeAttackButtonRect().left && InputManager -> GetMouseCursorPos().x <= ObjectButtonManager -> GetTimeAttackButtonRect().right)
		{
			if(InputManager -> GetMouseCursorPos().y >= ObjectButtonManager -> GetTimeAttackButtonRect().top && InputManager -> GetMouseCursorPos().y <= ObjectButtonManager -> GetTimeAttackButtonRect().bottom)
				ObjectButtonManager -> SetTimeAttackButtonSelected(true);
			else
				ObjectButtonManager -> SetTimeAttackButtonSelected(false);
		}
		else
			ObjectButtonManager -> SetTimeAttackButtonSelected(false);

		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetTimeAttackButtonSelected())
		{
			LogicManager -> SetCubeMixing(true);
			ObjectButtonManager -> SetTimeAttackButtonSelected(false);
			GameManager -> SetTimeAttackMode(true);
			GameManager -> SetTimeAttackMixing(true);
			GameManager -> SetTimeRecord(0.0f);
		}
	}
}

void CubeRotateProcess()
{
	if(ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1)
	{
		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetButtonSelected(0))
			ObjectCubeManager -> SetObjectRotateData(YAW, false);
		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetButtonSelected(1))
			ObjectCubeManager -> SetObjectRotateData(YAW, true);
		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetButtonSelected(2))
			ObjectCubeManager -> SetObjectRotateData(ROLL, false);
		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetButtonSelected(3))
			ObjectCubeManager -> SetObjectRotateData(ROLL, true);
		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetButtonSelected(4))
			ObjectCubeManager -> SetObjectRotateData(PITCH, false);
		if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectButtonManager -> GetButtonSelected(5))
			ObjectCubeManager -> SetObjectRotateData(PITCH, true);
	}
}

void CubeSurfacePointProcess()
{
	if(ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1)
	{
		if(GameManager -> GetTimeAttackMode() == false || GameManager -> GetTimeAttackPlaying() == true)
		{
			if(ObjectCubeManager -> GetObjectRight().z == -1.0f || ObjectCubeManager -> GetObjectUp().z == -1.0f || ObjectCubeManager -> GetObjectFront().z == 1.0f)
			{
				if(PickingManager -> RaySurfaceIntersectionTest(RenderManager -> GetD3DDevice(), ObjectCubeManager -> GetMesh(4), 0, ObjectCubeManager -> GetWorldMatrix(4), CameraManager -> GetViewMatrix(), (int)InputManager -> GetMouseCursorPos().x + 3, (int)InputManager -> GetMouseCursorPos().y + 13))
				{
					ObjectCubeManager -> SetCubeSurfacePointed(0, true);
					LogicManager -> SetColorReverseArray(4, true);
				}
				else
				{
					ObjectCubeManager -> SetCubeSurfacePointed(0, false);
					if(!ObjectCubeManager -> GetCubeSurfaceSelected(0))
						LogicManager -> SetColorReverseArray(4, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetCubeSurfacePointed(0, false);
				LogicManager -> SetColorReverseArray(4, false);
			}

			if(ObjectCubeManager -> GetObjectRight().z == 1.0f || ObjectCubeManager -> GetObjectUp().z == 1.0f || ObjectCubeManager -> GetObjectFront().z == -1.0f)
			{
				if(PickingManager -> RaySurfaceIntersectionTest(RenderManager -> GetD3DDevice(), ObjectCubeManager -> GetMesh(21), 1, ObjectCubeManager -> GetWorldMatrix(21), CameraManager -> GetViewMatrix(), (int)InputManager -> GetMouseCursorPos().x + 3, (int)InputManager -> GetMouseCursorPos().y + 13))
				{
					ObjectCubeManager -> SetCubeSurfacePointed(1, true);
					LogicManager -> SetColorReverseArray(21, true);
				}
				else
				{
					ObjectCubeManager -> SetCubeSurfacePointed(1, false);
					if(!ObjectCubeManager -> GetCubeSurfaceSelected(1))
						LogicManager -> SetColorReverseArray(21, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetCubeSurfacePointed(1, false);
				LogicManager -> SetColorReverseArray(21, false);
			}

			if(ObjectCubeManager -> GetObjectRight().y == 1.0f || ObjectCubeManager -> GetObjectUp().y == 1.0f || ObjectCubeManager -> GetObjectFront().y == -1.0f)
			{
				if(PickingManager -> RaySurfaceIntersectionTest(RenderManager -> GetD3DDevice(), ObjectCubeManager -> GetMesh(10), 2, ObjectCubeManager -> GetWorldMatrix(10), CameraManager -> GetViewMatrix(), (int)InputManager -> GetMouseCursorPos().x + 3, (int)InputManager -> GetMouseCursorPos().y + 13))
				{
					ObjectCubeManager -> SetCubeSurfacePointed(2, true);
					LogicManager -> SetColorReverseArray(10, true);
				}
				else
				{
					ObjectCubeManager -> SetCubeSurfacePointed(2, false);
					if(!ObjectCubeManager -> GetCubeSurfaceSelected(2))
						LogicManager -> SetColorReverseArray(10, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetCubeSurfacePointed(2, false);
				LogicManager -> SetColorReverseArray(10, false);
			}

			if(ObjectCubeManager -> GetObjectRight().y == -1.0f || ObjectCubeManager -> GetObjectUp().y == -1.0f || ObjectCubeManager -> GetObjectFront().y == 1.0f)
			{
				if(PickingManager -> RaySurfaceIntersectionTest(RenderManager -> GetD3DDevice(), ObjectCubeManager -> GetMesh(15), 3, ObjectCubeManager -> GetWorldMatrix(15), CameraManager -> GetViewMatrix(), (int)InputManager -> GetMouseCursorPos().x + 3, (int)InputManager -> GetMouseCursorPos().y + 13))
				{
					ObjectCubeManager -> SetCubeSurfacePointed(3, true);
					LogicManager -> SetColorReverseArray(15, true);
				}
				else
				{
					ObjectCubeManager -> SetCubeSurfacePointed(3, false);
					if(!ObjectCubeManager -> GetCubeSurfaceSelected(3))
						LogicManager -> SetColorReverseArray(15, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetCubeSurfacePointed(3, false);
				LogicManager -> SetColorReverseArray(15, false);
			}

			if(ObjectCubeManager -> GetObjectRight().x == -1.0f || ObjectCubeManager -> GetObjectUp().x == -1.0f || ObjectCubeManager -> GetObjectFront().x == 1.0f)
			{
				if(PickingManager -> RaySurfaceIntersectionTest(RenderManager -> GetD3DDevice(), ObjectCubeManager -> GetMesh(12), 4, ObjectCubeManager -> GetWorldMatrix(12), CameraManager -> GetViewMatrix(), (int)InputManager -> GetMouseCursorPos().x + 3, (int)InputManager -> GetMouseCursorPos().y + 13))
				{
					ObjectCubeManager -> SetCubeSurfacePointed(4, true);
					LogicManager -> SetColorReverseArray(12, true);
				}
				else
				{
					ObjectCubeManager -> SetCubeSurfacePointed(4, false);
					if(!ObjectCubeManager -> GetCubeSurfaceSelected(4))
						LogicManager -> SetColorReverseArray(12, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetCubeSurfacePointed(4, false);
				LogicManager -> SetColorReverseArray(12, false);
			}

			if(ObjectCubeManager -> GetObjectRight().x == 1.0f || ObjectCubeManager -> GetObjectUp().x == 1.0f || ObjectCubeManager -> GetObjectFront().x == -1.0f)
			{
				if(PickingManager -> RaySurfaceIntersectionTest(RenderManager -> GetD3DDevice(), ObjectCubeManager -> GetMesh(13), 5, ObjectCubeManager -> GetWorldMatrix(13), CameraManager -> GetViewMatrix(), (int)InputManager -> GetMouseCursorPos().x + 3, (int)InputManager -> GetMouseCursorPos().y + 13))
				{
					ObjectCubeManager -> SetCubeSurfacePointed(5, true);
					LogicManager -> SetColorReverseArray(13, true);
				}
				else
				{
					ObjectCubeManager -> SetCubeSurfacePointed(5, false);
					if(!ObjectCubeManager -> GetCubeSurfaceSelected(5))
						LogicManager -> SetColorReverseArray(13, false);
				}
			}
			else
			{
				ObjectCubeManager -> SetCubeSurfacePointed(5, false);
				LogicManager -> SetColorReverseArray(13, false);
			}
		}
	}
}

void CubeSurfaceSelectProcess()
{
	if(InputManager -> IsMouseButtonUp(MOUSE_LBUTTON) && ObjectCubeManager -> GetObjectRotateState() == NONE && ObjectCubeManager -> GetObjectSurfaceRotateState() == -1)
	{
		if(ObjectCubeManager -> GetCubeSurfacePointed(0))
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, true);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			LogicManager -> SetColorAtCubeSelected(0);
		}
		else if(ObjectCubeManager -> GetCubeSurfacePointed(1))
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, true);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			LogicManager -> SetColorAtCubeSelected(1);
		}
		else if(ObjectCubeManager -> GetCubeSurfacePointed(2))
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, true);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			LogicManager -> SetColorAtCubeSelected(2);
		}
		else if(ObjectCubeManager -> GetCubeSurfacePointed(3))
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, true);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			LogicManager -> SetColorAtCubeSelected(3);
		}
		else if(ObjectCubeManager -> GetCubeSurfacePointed(4))
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, true);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			LogicManager -> SetColorAtCubeSelected(4);
		}
		else if(ObjectCubeManager -> GetCubeSurfacePointed(5))
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, true);
			LogicManager -> SetColorAtCubeSelected(5);
		}
		else
		{
			ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			LogicManager -> SetColorAtCubeSelected(-1);
		}
	}
}

void CubeSurfaceRotateDirectionProcess()
{
	if(ObjectCubeManager -> GetCubeSurfaceSelected())
	{
		if(InputManager -> IsKeyUp(DIK_A))
		{
			if(ObjectCubeManager -> GetCubeSurfaceSelected(0))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(0, false);
				ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(1))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(1, false);
				ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(2))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(2, false);
				ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(3))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(3, false);
				ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(4))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(4, false);
				ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			}
			else
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(5, false);
				ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			}
			LogicManager -> SetColorAtCubeSelected(-1);
		}
		else if(InputManager -> IsKeyUp(DIK_S))
		{
			if(ObjectCubeManager -> GetCubeSurfaceSelected(0))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(0, true);
				ObjectCubeManager -> SetCubeSurfaceSelected(0, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(1))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(1, true);
				ObjectCubeManager -> SetCubeSurfaceSelected(1, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(2))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(2, true);
				ObjectCubeManager -> SetCubeSurfaceSelected(2, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(3))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(3, true);
				ObjectCubeManager -> SetCubeSurfaceSelected(3, false);
			}
			else if(ObjectCubeManager -> GetCubeSurfaceSelected(4))
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(4, true);
				ObjectCubeManager -> SetCubeSurfaceSelected(4, false);
			}
			else
			{
				ObjectCubeManager -> SetObjectSurfaceRotateData(5, true);
				ObjectCubeManager -> SetCubeSurfaceSelected(5, false);
			}
			LogicManager -> SetColorAtCubeSelected(-1);
		}
	}
}

void CubeDrawProcess()
{
	if(ObjectCubeManager -> GetObjectAlphaChange() == true)
	{
		RenderManager -> GetD3DDevice() -> SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		RenderManager -> GetD3DDevice() -> SetMaterial(&ObjectCubeManager -> GetMaterial());
		for(int i = 0; i < 26; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				if(ObjectCubeManager -> GetColor(i, j) != BLACK)
				{
					RenderManager -> GetD3DDevice() -> SetTransform(D3DTS_WORLD, &ObjectCubeManager -> GetWorldMatrix(i));
					RenderManager -> GetD3DDevice() -> SetTexture(0, TextureManager -> GetCubeTexture(ObjectCubeManager -> GetColor(i, j), false));
					ObjectCubeManager -> GetMesh(i) -> DrawSubset(j);
				}
			}
		}
		RenderManager -> GetD3DDevice() -> SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
	else
	{
		for(int i = 0; i < 26; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				RenderManager -> GetD3DDevice() -> SetTransform(D3DTS_WORLD, &ObjectCubeManager -> GetWorldMatrix(i));
				RenderManager -> GetD3DDevice() -> SetTexture(0, TextureManager -> GetCubeTexture(ObjectCubeManager -> GetColor(i, j), LogicManager -> GetColorReverseArray(i)));
				ObjectCubeManager -> GetMesh(i) -> DrawSubset(j);
			}
		}
	}
}

void CubeMixing()
{
	srand((unsigned)timeGetTime());

	int surface, direction;
	if(LogicManager -> GetMixCount() == 0)
		LogicManager -> SetMixCount(rand() % 10 + 51);

	if(ObjectCubeManager -> GetObjectSurfaceRotateState() == -1)
	{
		LogicManager -> SetMixCount(LogicManager -> GetMixCount() - 1);

		if(LogicManager -> GetMixCount() == 0)
		{
			LogicManager -> SetCubeMixing(false);
			if(GameManager -> GetTimeAttackMode() == true)
			{
				GameManager -> SetTimeAttackMixing(false);
				GameManager -> SetTimeAttackIsReady(true);
			}
		}
		else
		{
			surface = rand() % 6;
			direction = rand() % 100;
			if(direction < 50)
				ObjectCubeManager -> SetObjectSurfaceRotateData(surface, false);
			else
				ObjectCubeManager -> SetObjectSurfaceRotateData(surface, true);
		}
	}
}