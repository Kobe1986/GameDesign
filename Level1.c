/* Project:		GSMPre
   File Name:	Level1.c
   Author:		Kobe
   Date:		2017-4-9
   Purpose:		LEVEL */

#include "Level1.h"
#include "stdio.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "System.h"
#include "lib/AEEngine.h"
#include "Input.h"
#pragma comment (lib, "lib/Alpha_Engine.lib")
extern FILE* fp;
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static AEGfxVertexList*	pMesh1;
static float obj1X, obj1Y;
AEGfxTexture *P1;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------ ------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void Load1(void){
	AEGfxMeshStart();
	AEGfxTriAdd(
		-30.0f, -30.0f, 0xFFFF0000, 0.0f, 1.0f,
		30.0f, -30.0f, 0xFFFF0000, 0.125f, 1.0f,
		-30.0f, 30.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		30.0f, -30.0f, 0xFFFF0000, 0.125f, 1.0f,
		30.0f, 30.0f, 0xFFFF0000, 0.125f, 0.0f,
		-30.0f, 30.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");
	P1 = AEGfxTextureLoad("PlanetTexture.png");
    fprintf(fp, "Level1:Load\n");
}
void Ini1(void){

	obj1X = 0.0f;
	obj1Y = 0.0f;

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    fprintf(fp, "Level1:Ini\n");
}
void Update1(void)
{
	// 状态切换
	if (KeyPressed[KeyR]) {
		State.Next = State_Restart;
		GS = GS_Restart;
	}
		
	if (KeyPressed[KeyESC]) {
		State.Next = State_Quit;
		GS = GS_Quit;
	}
		
	if (KeyPressed[Key2]) {
		State.Next = State_Level2;
		GS = GS_L2;
	}

	// 对象移动
	if (KeyPressed[KeyUp])
		obj1Y += 1.5f;
	else
		if (KeyPressed[KeyDown])
			obj1Y -= 1.5f;
	if (KeyPressed[KeyLeft])
		obj1X -= 1.5f;
	else
		if (KeyPressed[KeyRight])
			obj1X += 1.5f;

	// 输入重置
	Input_Initialize();

	// 签到
	fprintf(fp, "Level1:Update\n");
}
void Draw1(void){
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(obj1X, obj1Y);
	AEGfxTextureSet(P1, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
    fprintf(fp, "Level1:Draw\n");
}
void Free1(void){
    fprintf(fp, "Level1:Free\n");
}
void Unload1(void){
    AEGfxMeshFree(pMesh1);

    fprintf(fp, "Level1:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
