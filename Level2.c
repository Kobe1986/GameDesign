/* Project:		GSMPre
   File Name:	Level2.c
   Author:		Kobe
   Date:		2017-4-9
   Purpose:		LEVEL */

#include "Level2.h"
#include "stdio.h"
#include "System.h"
#include "Input.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "lib/AEEngine.h"
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
extern int Lives;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static AEGfxVertexList*	pMesh_Back;				// 对象1的网格(mesh)模型
static AEGfxVertexList*	pMesh_obj1;
static AEGfxTexture *Back_Texture;
static AEGfxTexture *obj1_Texture;
static int CurrentFrame = 0;
static int ObjFrame = 0;
static int v_obj1 = 2;
static float obj1X, obj1Y;		// 对象1的位置
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void Load2(void){
	FILE *fpRead1 = fopen("Level2_Lives.txt", "r");
	if (fpRead1 == NULL)
	{
		return;
	}
	fscanf(fpRead1, "%d ", &Lives);
	// 开始添加对象1
	AEGfxMeshStart();
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_Back = AEGfxMeshEnd();


	AEGfxMeshStart();
	AEGfxTriAdd(
		-64.0f, -64.0f, 0xFFFF0000, 0.0f, 1.0f,
		64.0f, -64.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		-64.0f, 64.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		64.0f, -64.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		64.0f, 64.0f, 0xFFFF0000, 0.0714285f, 0.0f,
		-64.0f, 64.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_obj1 = AEGfxMeshEnd();


	AE_ASSERT_MESG(pMesh_Back, "Failed to create mesh 1!!");
	Back_Texture = AEGfxTextureLoad("res\\back1.png");
	obj1_Texture = AEGfxTextureLoad("res\\bread.png");
    fprintf(fp, "Level2:Load\n");
}
void Ini2(void){
	// 对象1的初始位置
	obj1X = -400.0f;
	obj1Y = 0.0f;

	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // 背景色RGB
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    fprintf(fp, "Level2:Ini\n");
}
void Update2(void)
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
		v_obj1++;
	}

	if (KeyPressed[KeyDown]) {
		v_obj1--;
	}
	// 输入重置
	Input_Initialize();

	// 签到
	fprintf(fp, "Level2:Update\n");
}
void Draw2(void){
	
    // 画对象1
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxTextureSet(Back_Texture, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh_Back, AE_GFX_MDM_TRIANGLES);
	if (CurrentFrame % 3 == 0) {
		ObjFrame++;
		ObjFrame = ObjFrame % 14;
		if (obj1X < 400.0f) {
			obj1X = obj1X + v_obj1;
		}
		else obj1X = -400.0f;
		
	}
	// 画对象2
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(obj1X, obj1Y);
	AEGfxTextureSet(obj1_Texture, 0.0714285f*ObjFrame, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh_obj1, AE_GFX_MDM_TRIANGLES);
	CurrentFrame++;
	CurrentFrame = CurrentFrame % 60;
    fprintf(fp, "Level2:Draw\n");
}
void Free2(void){
    fprintf(fp, "Level2:Free\n");
}
void Unload2(void){
    AEGfxMeshFree(pMesh_Back);          // 注销创建的对象
    fprintf(fp, "Level2:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
