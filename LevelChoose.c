/* Project:		GSMPre
   File Name:	Level1.c
   Author:		Kobe
   Date:		2017-4-9
   Purpose:		LEVEL */

#include "LevelChoose.h"
#include "stdio.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "System.h"
#include "inc/AEEngine.h"
#include "Input.h"
#include "inc/fmod.h"
#include "inc/fmod_codec.h"
#pragma comment (lib, "lib/fmod_vc.lib")
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
static AEGfxVertexList*	pBackground;
static AEGfxTexture *MainBackground;
static AEGfxVertexList* pMenue1;
static AEGfxVertexList* pMenue2;
static AEGfxTexture* MenueTexture;
static float Tsp_Menue1 = 0.0f;
static float Tsp_Menue2 = 0.0f;
static int currentframe = 0;
static FMOD_SYSTEM* mbgm;
static FMOD_RESULT result;
static void* extradriverdata = 0;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------ ------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void LoadC(void){
	AEGfxMeshStart();//添加背景图片
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pBackground = AEGfxMeshEnd();

	AEGfxMeshStart();//添加菜单效果1
	AEGfxTriAdd(
		-620.0f, -65.0f, 0xFFFF0000, 0.0f, 0.5f,
		620.0f, -65.0f, 0xFFFF0000, 1.0f, 0.5f,
		-620.0f, 65.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		620.0f, -65.0f, 0xFFFF0000, 1.0f, 0.5f,
		620.0f, 65.0f, 0xFFFF0000, 1.0f, 0.0f,
		-620.0f, 65.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMenue1 = AEGfxMeshEnd();

	AEGfxMeshStart();//添加菜单效果2
	AEGfxTriAdd(
		-620.0f, -70.0f, 0xFFFF0000, 0.0f, 1.0f,
		620.0f, -70.0f, 0xFFFF0000, 1.0f, 1.0f,
		-620.0f, 70.0f, 0xFFFF0000, 0.0f, 0.5f);
	AEGfxTriAdd(
		620.0f, -70.0f, 0xFFFF0000, 1.0f, 1.0f,
		620.0f, 70.0f, 0xFFFF0000, 1.0f, 0.5f,
		-620.0f, 70.0f, 0xFFFF0000, 0.0f, 0.5f);
	pMenue2 = AEGfxMeshEnd();
	MainBackground = AEGfxTextureLoad("res\\main.png");
	MenueTexture = AEGfxTextureLoad("res\\highlight.png");
	result = FMOD_System_Create(&mbgm);
	ERRCHECK(result);
	result = mbgm->init(32, FMOD_INIT_NORMAL, extradriverdata);
    fprintf(fp, "Choose:Load\n");
}
void IniC(void){
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    fprintf(fp, "Choose:Ini\n");
}
void UpdateC(void)
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
		
	if (KeyPressed[Key1]) {
		State.Next = State_Level1;
		GS = GS_L1;
	}

	if (KeyPressed[KeyUp]) {
		Tsp_Menue1 = 1.0f;
		Tsp_Menue2 = 0.0f;
	}
	
	if (KeyPressed[KeyDown]) {
		Tsp_Menue1 = 0.0f;
		Tsp_Menue2 = 1.0f;
	}

	if(KeyPressed[KeyReturn]){
		if (Tsp_Menue1 == 1.0f) {
			State.Next = State_Level1;
			GS = GS_L1;
		}
		if (Tsp_Menue2 == 1.0f) {
			State.Next = State_Quit;
			GS = GS_Quit;
		}
	}
	// 输入重置
	Input_Initialize();

	// 签到
	fprintf(fp, "Choose:Update\n");
}
void DrawC(void){
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxTextureSet(MainBackground, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pBackground, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(100.0f, -148.0f);
	AEGfxTextureSet(MenueTexture, 0.0f, 0.0f);
	AEGfxSetTransparency(Tsp_Menue1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMenue1, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(10.0f, -320.0f);
	AEGfxTextureSet(MenueTexture, 0.0f, 0.0f);
	AEGfxSetTransparency(Tsp_Menue2);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMenue2, AE_GFX_MDM_TRIANGLES);

	currentframe++;
	currentframe = currentframe % 60;

    fprintf(fp, "Choose:Draw\n");
}
void FreeC(void){
    fprintf(fp, "Choose:Free\n");
}
void UnloadC(void){
    AEGfxMeshFree(pBackground);
	AEGfxMeshFree(pMenue1);
	AEGfxMeshFree(pMenue2);
	AEGfxTextureUnload(MainBackground);
	AEGfxTextureUnload(MenueTexture);
    fprintf(fp, "Choose:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
