#ifndef OBJ_COMPETITION_H
#define OBJ_COMPETITION_H

#include "SonicMania.h"

// Object Class
struct ObjectCompetition {
    RSDK_OBJECT
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;
    int32 unused5;
    int32 unused6;
    int32 unused7;
    int32 unused8;
    uint16 aniFrames;
    Entity *activeEntity;
    int32 unused9;
};

// Entity Class
struct EntityCompetition {
    RSDK_ENTITY
    StateMachine(state);
    bool32 playerFinished[PLAYER_MAX];
    int32 timer;
    int32 seconds;
    int32 unused1;
    Animator animator;
};

// Object Struct
extern ObjectCompetition *Competition;

// Standard Entity Events
void Competition_Update(void);
void Competition_LateUpdate(void);
void Competition_StaticUpdate(void);
void Competition_Draw(void);
void Competition_Create(void* data);
void Competition_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void Competition_EditorDraw(void);
void Competition_EditorLoad(void);
#endif
void Competition_Serialize(void);

// Extra Entity Functions
void Competition_State_Manager(void);

#if RETRO_USE_PLUS
void Competition_ResetOptions(void);
void Competition_ClearMatchData(void);
void Competition_CalculateScore(int32 playerID, uint8 flags);
#endif

#endif //!OBJ_COMPETITION_H
