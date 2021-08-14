#ifndef OBJ_UIREPLAYCAROUSEL_H
#define OBJ_UIREPLAYCAROUSEL_H

#include "SonicMania.h"

#if RETRO_USE_PLUS
// Object Class
typedef struct {
    RSDK_OBJECT
    ushort aniFrames;
    EntityUIButtonPrompt *prompt;
} ObjectUIReplayCarousel;

// Entity Class
typedef struct {
    MANIA_UI_ITEM_BASE
    TextInfo zoneNameText[4];
    TextInfo createdAtText[4];
    TextInfo loadingText;
    TextInfo noReplaysText;
    int sprX;
    byte field_158;
    int field_15C;
    void (*stateDraw)(void);
    short field_164;
    ushort dbUnknownCount;
    int field_168;
    int field_16C;
    int field_170;
    byte field_174;
    byte dbUnknownID;
    int field_178;
    int field_17C;
    byte prevDBUnknownID;
    int field_184;
    int field_188;
    int field_18C;
    int field_190;
    int field_194;
    int field_198;
    Animator animator1;
    Animator animator2;
    Animator animator3;
    Animator animator4;
    Animator animators[4];
    Animator animator5;
    Animator animator6;
    Animator animator7;
    Animator animator8;
    Animator animator9;
    int language;
} EntityUIReplayCarousel;

// Object Struct
extern ObjectUIReplayCarousel *UIReplayCarousel;

// Standard Entity Events
void UIReplayCarousel_Update(void);
void UIReplayCarousel_LateUpdate(void);
void UIReplayCarousel_StaticUpdate(void);
void UIReplayCarousel_Draw(void);
void UIReplayCarousel_Create(void* data);
void UIReplayCarousel_StageLoad(void);
void UIReplayCarousel_EditorDraw(void);
void UIReplayCarousel_EditorLoad(void);
void UIReplayCarousel_Serialize(void);

// Extra Entity Functions
void UIReplayCarousel_ProcessButtonCB(void);
void UIReplayCarousel_Unknown2(void);
void UIReplayCarousel_SetupButtonCallbacks(void);
void UIReplayCarousel_HandleTouchPositions(void);
void UIReplayCarousel_TouchedCB(void);
void UIReplayCarousel_Unknown6(void);
void UIReplayCarousel_Unknown7(int a1, short a2, int a3, int a4);
void UIReplayCarousel_Unknown8(byte a1, byte a2, int a3, int a4, int arg10, int a6, int a7);
void UIReplayCarousel_Unknown9(byte a1, short a2, int a4, int a5);
void UIReplayCarousel_Unknown10(byte zoneID, int a2, byte a3, byte a4, int a5, int a6, int drawX, int drawY);
void UIReplayCarousel_Unknown11(void);
void UIReplayCarousel_Unknown12(void);
void UIReplayCarousel_StateDraw_Unknown1(void);
void UIReplayCarousel_StateDraw_Unknown2(void);
void UIReplayCarousel_StateDraw_Unknown3(void);
void UIReplayCarousel_Unknown16(void);
void UIReplayCarousel_Unknown17(void);
void UIReplayCarousel_Unknown18(void);
void UIReplayCarousel_Unknown19(void);

#endif

#endif //!OBJ_UIREPLAYCAROUSEL_H
