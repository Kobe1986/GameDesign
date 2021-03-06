/* Project:		GSMPre
   File Name:	Main.c
   Author:		Xinrea
   Date:		2017-4-11
   Purpose:		主程序模块  */

#include <windows.h>
#include "System.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "inc/AEEngine.h"
#pragma comment (lib, "lib/Alpha_Engine.lib")
FILE *fp;
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
int Counter;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    System_Initialize(hInstance, nCmdShow);
    GSM_Initialize();
    while(GS!=GS_Quit){
        if(GS==GS_Restart){
            State.Current=State.Previous;
			State.Next = State.Current;
        }
		else {
			GSM_Update();
			Load();
		}
		Init();
        while (State.Current==State.Next) {
            AESysFrameStart();
            Update();
            Draw();
            AESysFrameEnd();
            }
        Free();
		if (GS!=GS_Restart)Unload();
		State.Previous = State.Current;
		State.Current = State.Next;
    }
    System_Exit();
    return 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
