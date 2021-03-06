/* Project:		GSMPre
   File Name:	GameStateManager.h
   Author:		Xinrea
   Date:		2017-4-11
   Purpose:		GSM */

#ifndef _GameStateManager
#define _GameStateManager

//------------------------------------------------------------------------------
// Typedef:
//------------------------------------------------------------------------------
struct State{
    void (* Previous)(void);
    void (* Current)(void);
    void (* Next)(void);
}State;
//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
void (*Load )(void);
void (*Init )(void);
void (*Update )(void);
void (*Draw )(void);
void (*Free )(void);
void (*Unload )(void);
int GS;
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void GSM_Initialize(void);
void GSM_Update(void);
void State_LevelC(void);
void State_Level1(void);
void State_Restart(void);
void State_Quit(void);

#endif