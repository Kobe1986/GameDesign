/* Project:		GSMPre
   File Name:	GameStateManager.c
   Author:		Xinrea
   Date:		2017-4-11
   Purpose:		GSM */

#include "GameStateManager.h"
#include "GameStateList.h"
#include "LevelChoose.h"
#include "Level1.h"
#include "stdio.h"
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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void GSM_Initialize(){
	State.Previous = State_LevelC;
	State.Current = State_LevelC;
    State.Next= State_LevelC;
	GS = GS_M;
    fprintf(fp,"GSM:Initialize\n");
}

void GSM_Update(){
    State.Current();
    fprintf(fp,"GSM:Update\n");
}

void State_LevelC(void){//状态为关卡选择
	GS = GS_L1;
    Load=LoadC;
    Init=IniC;
    Update=UpdateC;
    Draw=DrawC;
    Free=FreeC;
    Unload=UnloadC;
}

void State_Level1(void){//状态为第1关
	GS = GS_L2;
    Load=Load1;
    Init=Ini1;
    Update=Update1;
    Draw=Draw1;
    Free=Free1;
    Unload=Unload1;
}

void State_Restart(void) {//状态为重新开始
}

void State_Quit(void){//状态为退出
    Free();
    Unload();
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
