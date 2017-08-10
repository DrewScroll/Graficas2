#include "Application.h"
#include <iostream>

using namespace std;

#define M_PI 3.141592654

void TestApp::InitVars() {
	DtTimer.Init();
	//Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Orientation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//Scaling		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Position = { 0,0,0,0 };
	Orientation = { 0,0,0,0 };
	Scaling = { 1,1,1,0 };
}

void TestApp::CreateAssets() {
	PrimitiveMgr.SetVP(&VP);
	//int indexCube = PrimitiveMgr.CreateCube();
	//Cubes[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexCube), &VP);
	//Cubes[1].CreateInstance(PrimitiveMgr.GetPrimitive(indexCube), &VP);

	//int indexTri = PrimitiveMgr.CreateCube();
	int indexMesh = PrimitiveMgr.CreateMesh("CerdoNuevo.X");
	//Triangle[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexTri), &VP);

	Mesh[0].CreateInstance(PrimitiveMgr.GetPrimitive(indexMesh), &VP);

	/*D3DXMATRIX View;
	D3DXVECTOR3 Pos		= D3DXVECTOR3(0.0f,1.0f,5.0f);
	D3DXVECTOR3 Up		= D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVECTOR3 LookAt	= D3DXVECTOR3(0.0001f, 0.0001f, 0.0001f) - Pos;
	D3DXMatrixLookAtRH(&View,&Pos,&LookAt,&Up);
	D3DXMATRIX Proj;*/

	MATRIX4D View;

	VECTOR4D Pos = { 0,1,5,0 };
	VECTOR4D Up = { 0,1,0,0 };
	VECTOR4D LookAt = { 0.0001,0.0001,0.0001,0 };
	View = LookAtRH(Pos, LookAt, Up);
	MATRIX4D Proj = PerspectiveFOVRH((M_PI / 4), (1280.0f / 720.0f), 0.1, 1000);

	//D3DXMatrixPerspectiveFovRH(&Proj,D3DXToRadian(45.0f),1280.0f/720.0f,0.1f,1000.0f);
	//	D3DXMatrixOrthoRH(&Proj, 1280.0f / 720.0f, 1.0f , 0.1, 100.0f);
	VP = View*Proj;
}

void TestApp::DestroyAssets() {
	PrimitiveMgr.DestroyPrimitives();
}

void TestApp::OnUpdate() {
	DtTimer.Update();

	/*Triangle[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Triangle[0].RotateXAbsolute(Orientation.x);
	Triangle[0].RotateYAbsolute(Orientation.y);
	Triangle[0].RotateZAbsolute(Orientation.z);
	Triangle[0].ScaleAbsolute(Scaling.x);
	Triangle[0].Update();*/
	
	Mesh[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Mesh[0].RotateXAbsolute(Orientation.x);
	Mesh[0].RotateYAbsolute(Orientation.y);
	Mesh[0].RotateZAbsolute(Orientation.z);
	Mesh[0].ScaleAbsolute(Scaling.x);
	Mesh[0].Update();

	OnInput();

	/*
	Cubes[0].TranslateAbsolute(Position.x, Position.y, Position.z);
	Cubes[0].RotateXAbsolute(Orientation.x);
	Cubes[0].RotateYAbsolute(Orientation.y);
	Cubes[0].RotateZAbsolute(Orientation.z);
	Cubes[0].ScaleAbsolute(Scaling.x);
	Cubes[0].Update();

	Cubes[1].TranslateAbsolute(-Position.x,-Position.y, Position.z);
	Cubes[1].RotateXAbsolute(-Orientation.x);
	Cubes[1].RotateYAbsolute(-Orientation.y);
	Cubes[1].RotateZAbsolute(-Orientation.z);
	Cubes[1].ScaleAbsolute(Scaling.x);
	Cubes[1].Update();
	*/
	OnDraw();
}

void TestApp::OnDraw() {
	pFramework->pVideoDriver->Clear();
	//Triangle[0].Draw();
	Mesh[0].Draw();
	pFramework->pVideoDriver->SwapBuffers();
}

void TestApp::OnInput() {
	
	if (IManager.PressedKey(SDLK_UP)) {
		Position.y += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_DOWN)) {
		Position.y -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_LEFT)) {
		Position.x -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_RIGHT)) {
		Position.x += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_z)) {
		Position.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_x)) {
		Position.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PLUS)) {
		Scaling.x += 1.0f*DtTimer.GetDTSecs();
		Scaling.y += 1.0f*DtTimer.GetDTSecs();
		Scaling.z += 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_MINUS)) {
		Scaling.x -= 1.0f*DtTimer.GetDTSecs();
		Scaling.y -= 1.0f*DtTimer.GetDTSecs();
		Scaling.z -= 1.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP5)) {
		Orientation.x -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP6)) {
		Orientation.x += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP2)) {
		Orientation.y -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP3)) {
		Orientation.y += 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP0)) {
		Orientation.z -= 60.0f*DtTimer.GetDTSecs();
	}

	if (IManager.PressedKey(SDLK_KP_PERIOD)) {
		Orientation.z += 60.0f*DtTimer.GetDTSecs();
	}

	
}

void TestApp::OnPause() {

}

void TestApp::OnResume() {

}

void TestApp::OnReset() {

}