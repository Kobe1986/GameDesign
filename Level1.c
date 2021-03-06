/* Project:		GSMPre
   File Name:	Level1.c
   Author:		Kobe
   Date:		2017-5-28
   Purpose:		LEVEL */

#include "Level1.h"
#include "stdio.h"
#include "System.h"
#include "Input.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "lib/AEEngine.h"
extern FILE *fp;
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
static AEGfxVertexList*	pMesh_obj;
static AEGfxVertexList*	pMesh_Back;				// 对象1的网格(mesh)模型
static AEGfxVertexList*	pMesh_ldoor;            // 左侧障碍物网格模型 
static AEGfxVertexList*	pMesh_rdoor;            // 右侧障碍物网格模型
static AEGfxVertexList*	pMesh_obj1;				// 对象一(red)
static AEGfxVertexList*	pMesh_obj2;				// 对象二(green)
static AEGfxVertexList*	pMesh_obj3;				// 对象三(blue)
static AEGfxVertexList*	pMesh_obj4;            	// 对象四(yellow)  
static AEGfxVertexList* pMesh_Question;
static AEGfxVertexList*pMesh_choice;

static AEGfxTexture *obj_Texture;
static AEGfxTexture *Back_Texture;
static AEGfxTexture *ldoor_Texture;
static AEGfxTexture *rdoor_Texture;
static AEGfxTexture *obj1_Texture;
static AEGfxTexture *obj2_Texture;
static AEGfxTexture *obj3_Texture;
static AEGfxTexture *obj4_Texture;
static AEGfxTexture *Question_Texture;
static AEGfxTexture *choice_Texture;

static int CurrentFrame = 0;    				//记录当前总帧数
static int game_time = 0;       				//记录当前游戏时间 
static int ObjFrame = 0;       					//记录物体运动帧数
static int v_obj1 = 17;       					//物体运动速度

static float objX, objY;						// 对象1的位置
static float ldoor_X,ldoor_Y;
static float rdoor_X,rdoor_Y;
static float Question_X,Question_Y;
static float choice_X[3],choice_Y[3];  
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void Load1(void){
	// 添加背景
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

	// 添加对象1
	AEGfxMeshStart();
	AEGfxTriAdd(
		-64.0f, -128.0f, 0xFFFF0000, 0.0f, 1.0f,
		64.0f, -128.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		64.0f, -128.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		64.0f, 128.0f, 0xFFFF0000, 0.0714285f, 0.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_obj1 = AEGfxMeshEnd();

	//添加对象2
	AEGfxMeshStart();
	AEGfxTriAdd(
		-64.0f, -128.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		64.0f, -128.0f, 0xFFFF0000, 0.0f, 1.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0714285f, 0.0f);
	AEGfxTriAdd(
		64.0f, -128.0f, 0xFFFF0000, 0.0f, 1.0f,
		64.0f, 128.0f, 0xFFFF0000, 0.0f, 0.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0714285f, 0.0f);
	pMesh_obj2 = AEGfxMeshEnd();

	//添加对象3
	AEGfxMeshStart();
	AEGfxTriAdd(
		-64.0f, -128.0f, 0xFFFF0000, 0.0f, 1.0f,
		64.0f, -128.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		64.0f, -128.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		64.0f, 128.0f, 0xFFFF0000, 0.0714285f, 0.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_obj3 = AEGfxMeshEnd();

	//添加对象4
	AEGfxMeshStart();
	AEGfxTriAdd(
		-64.0f, -128.0f, 0xFFFF0000, 0.0714285f, 1.0f,
		64.0f, -128.0f, 0xFFFF0000, 0.0f, 1.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0714285f, 0.0f);
	AEGfxTriAdd(
		64.0f, -128.0f, 0xFFFF0000, 0.0f, 1.0f,
		64.0f, 128.0f, 0xFFFF0000, 0.0f, 0.0f,
		-64.0f, 128.0f, 0xFFFF0000, 0.0714285f, 0.0f);
	pMesh_obj4 = AEGfxMeshEnd();

	// 添加障碍物（左）
	AEGfxMeshStart();
	AEGfxTriAdd(
		-200.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		200.0f, -450.0f, 0xFFFF0000, 0.25f, 1.0f,
		-200.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		200.0f, -450.0f, 0xFFFF0000, 0.25f, 1.0f,
		200.0f, 450.0f, 0xFFFF0000, 0.25f, 0.0f,
		-200.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_ldoor = AEGfxMeshEnd();

	// 添加障碍物（右）
	AEGfxMeshStart();
	AEGfxTriAdd(
		-200.0f, -450.0f, 0xFFFF0000, 0.75f, 1.0f,
		200.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-200.0f, 450.0f, 0xFFFF0000, 0.75f, 0.0f);
	AEGfxTriAdd(
		200.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		200.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-200.0f, 450.0f, 0xFFFF0000, 0.75f, 0.0f);
	pMesh_rdoor = AEGfxMeshEnd();

	// 添加提问界面
	AEGfxMeshStart();
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_Question = AEGfxMeshEnd();

	// 添加提问框
	AEGfxMeshStart();
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_choice = AEGfxMeshEnd();

	AE_ASSERT_MESG(pMesh_Back, "Failed to create mesh 1!!");

	Back_Texture = AEGfxTextureLoad("res\\back1.png");
	obj1_Texture = AEGfxTextureLoad("res\\RED.png");
	obj2_Texture = AEGfxTextureLoad("res\\GREEN.png");
	obj3_Texture = AEGfxTextureLoad("res\\BULE.png");
	obj4_Texture = AEGfxTextureLoad("res\\YELLOW.png");
	ldoor_Texture = AEGfxTextureLoad("res\\door.png");
	rdoor_Texture = AEGfxTextureLoad("res\\door.png");
	Question_Texture = AEGfxTextureLoad("res\\Question.png");
	choice_Texture = AEGfxTextureLoad("res\\choice.png");

    fprintf(fp, "Level1:Load\n");
}


void Ini1(void){
	// 对象1的初始位置
	objX = -680.0f;
	objY = 0.0f;

	// 对象左侧障碍物的初始位置
	ldoor_X = -600.0f;
	ldoor_Y = 0.0f;

	// 对象右侧障碍物的初始位置
	rdoor_X = 600.0f;
	rdoor_Y = 0.0f;

	// 提问界面的位置
	Question_X = 0.0f;
	Question_Y = 0.0f;

	// 提问框位置
	choice_X[0] = 0;
	choice_Y[0] = 0;
	choice_X[1] = 340;
	choice_Y[1] = 0;
	choice_X[2] = 0;
	choice_Y[2] = -300;
	choice_X[3] = 340;
	choice_Y[3] = -300;

	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);   // 背景色RGB
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

	if (KeyPressed[Key1]) {
		State.Next = State_LevelC;
		GS = GS_M;
	}

	if (KeyPressed[KeyUp]) {
		v_obj1++;
	}

	if (KeyPressed[KeyDown]) {
		v_obj1--;
	}

	if (game_time > 25)





	// 输入重置
	Input_Initialize();

	// 签到
	fprintf(fp, "Level1:Update\n");
}
void Draw1(void){

	if (CurrentFrame >= 20)
	{
		game_time++;
		CurrentFrame = 0;
		
	}
	else  CurrentFrame++;

	if (CurrentFrame % 3 == 0) {
			ObjFrame++;
			ObjFrame = ObjFrame % 14;	
		}

    // 画背景
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0, 0);
	AEGfxTextureSet(Back_Texture, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh_Back, AE_GFX_MDM_TRIANGLES);
	
	if (game_time <= 3)
	{
		obj_Texture = obj1_Texture;
		pMesh_obj = pMesh_obj1;
		objX = objX + v_obj1;
	}
	else if ((game_time >= 5)&& (game_time <= 8))
	{
		obj_Texture = obj2_Texture;
		pMesh_obj = pMesh_obj2;
		objX = objX - v_obj1;
  	}
  	else if ((game_time >= 10)&& (game_time <= 13))
	{
		obj_Texture = obj3_Texture;
		pMesh_obj = pMesh_obj3;
		objX = objX + v_obj1;
  	}
  	else if ((game_time >= 15)&& (game_time <= 18))
	{
		obj_Texture = obj4_Texture;
		pMesh_obj = pMesh_obj4;
		objX = objX - v_obj1;
  	}
  	else if ((game_time >= 20)&& (game_time <= 23))
	{
		obj_Texture = obj1_Texture;
		pMesh_obj = pMesh_obj1;
		objX = objX + v_obj1;
  	}
	// 画对象1
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(objX, objY);
	AEGfxTextureSet(obj_Texture, 0.0714285f*ObjFrame, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh_obj, AE_GFX_MDM_TRIANGLES);
	


    // 画左侧障碍物
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(ldoor_X, ldoor_Y);
	AEGfxTextureSet(ldoor_Texture, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh_ldoor, AE_GFX_MDM_TRIANGLES);

    // 画右侧障碍物
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(rdoor_X, rdoor_Y);
	AEGfxTextureSet(rdoor_Texture, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMesh_rdoor, AE_GFX_MDM_TRIANGLES);
	
	// 画提问界面和选择框
	if (game_time >= 25)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(Question_X, Question_Y);
		AEGfxTextureSet(Question_Texture, 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_Question, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(choice_X[3], choice_Y[3]);
		AEGfxTextureSet(choice_Texture, 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_choice, AE_GFX_MDM_TRIANGLES);
	}
	

}
void Free1(void){
    fprintf(fp, "Level1:Free\n");
}
void Unload1(void){
    AEGfxMeshFree(pMesh_Back);          // 注销创建的对象
    fprintf(fp, "Level1:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
