// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SSZ1Outro Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "SonicMania.h"

ObjectSSZ1Outro *SSZ1Outro;

void SSZ1Outro_Update(void)
{
    RSDK_THIS(SSZ1Outro);

    if (!self->activated) {
        self->activated = true;

#if RETRO_USE_PLUS
        if (RSDK_GET_ENTITY(SLOT_CUTSCENESEQ, CutsceneSeq)->objectID)
            RSDK_GET_ENTITY(SLOT_CUTSCENESEQ, CutsceneSeq)->skipType = SKIPTYPE_RELOADSCN;
#endif

        CutsceneSeq_StartSequence(self, SSZ1Outro_Cutscene_TimeWarpRunway, SSZ1Outro_Cutscene_TimeWarp, StateMachine_None);
    }
}

void SSZ1Outro_LateUpdate(void) {}

void SSZ1Outro_StaticUpdate(void) {}

void SSZ1Outro_Draw(void) {}

void SSZ1Outro_Create(void *data)
{
    RSDK_THIS(SSZ1Outro);

    INIT_ENTITY(self);
    CutsceneRules_SetupEntity(self, &self->size, &self->hitbox);
    self->active = ACTIVE_NEVER;
}

void SSZ1Outro_StageLoad(void)
{
    foreach_all(RTeleporter, teleporter) { SSZ1Outro->teleporter = teleporter; }
}

bool32 SSZ1Outro_Cutscene_TimeWarpRunway(EntityCutsceneSeq *host)
{
    RSDK_THIS(SSZ1Outro);

    RSDK_GET_PLAYER(player1, player2, camera);
    unused(camera);

    if (!host->timer) {
        foreach_all(FXFade, fxFade)
        {
            if (MathHelpers_PointInHitbox(self->position.x, self->position.y, fxFade->position.x, fxFade->position.y, self->direction,
                                          &self->hitbox)) {
                SSZ1Outro->fxFade = fxFade;
                foreach_break;
            }
        }

        Zone->cameraBoundsR[0]      = self->hitbox.right + (self->position.x >> 16);
        Zone->playerBoundActiveR[0] = false;

        Zone->cameraBoundsR[1]      = self->hitbox.right + (self->position.x >> 16);
        Zone->playerBoundActiveR[1] = false;

        Zone->cameraBoundsR[2]      = self->hitbox.right + (self->position.x >> 16);
        Zone->playerBoundActiveR[2] = false;

        Zone->cameraBoundsR[3]      = self->hitbox.right + (self->position.x >> 16);
        Zone->playerBoundActiveR[3] = false;

        CutsceneSeq_LockAllPlayerControl();

        player1->state      = Player_State_Ground;
        player1->stateInput = StateMachine_None;
        if (player2->objectID == Player->objectID) {
            player2->state      = Player_State_Ground;
            player2->stateInput = StateMachine_None;
        }
    }

    player1->right = true;

    if (player1->position.x < SSZ1Outro->teleporter->position.x || !player1->onGround) {
        player1->nextAirState    = StateMachine_None;
        player1->nextGroundState = StateMachine_None;

        if (player1->groundVel > 0x40000)
            player1->groundVel = 0x40000;

        player1->groundVel = player1->groundVel;

        if (player1->velocity.x > 0x40000)
            player1->velocity.x = 0x40000;

        player1->velocity.x = player1->velocity.x;
    }

    if (player2->objectID == Player->objectID) {
        if (player1->position.x > player2->position.x)
            player2->right = true;

        if (player1->groundVel < player2->groundVel)
            player2->groundVel = player1->groundVel;

        if (player1->groundVel < player1->velocity.x)
            player2->velocity.x = player1->groundVel;
        else
            player2->velocity.x = player1->velocity.x;

        player2->nextAirState    = StateMachine_None;
        player2->nextGroundState = StateMachine_None;
    }

    if (host->values[0]) {
        player1->jumpPress = false;
        if (player1->onGround)
            player1->jumpHold = false;
    }
    else if (player1->position.x >= SSZ1Outro->teleporter->position.x - 0xC80000) {
        player1->jumpPress = true;
        player1->jumpHold  = true;
        host->values[0]    = true;
    }

    return player1->position.x >= self->position.x + (self->hitbox.right << 16);
}
bool32 SSZ1Outro_Cutscene_TimeWarp(EntityCutsceneSeq *host)
{
    if (host->timer == 10)
        SSZ1Outro->fxFade->state = FXFade_State_FadeIn;

    if (SSZ1Outro->fxFade->timer == 512) {
        RSDK.SetScene("Cutscenes", "SSZ Time Warp");
        RSDK.LoadScene();
        return true;
    }

    return false;
}

void SSZ1Outro_DestroyHotaru(EntityHotaruMKII *hotaru)
{
    CREATE_ENTITY(Animals, intToVoid(Animals->animalTypes[RSDK.Rand(0, 32) >> 4] + 1), hotaru->position.x, hotaru->position.y);
    CREATE_ENTITY(Explosion, intToVoid(EXPLOSION_ENEMY), hotaru->position.x, hotaru->position.y)->drawOrder = Zone->objectDrawHigh;

    RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);
    destroyEntity(hotaru);
}

void SSZ1Outro_DestroyLeftoverHotarus(void)
{
    foreach_active(HotaruMKII, hotaru)
    {
        if (!hotaru->type)
            SSZ1Outro_DestroyHotaru(hotaru);
    }
}

#if RETRO_INCLUDE_EDITOR
void SSZ1Outro_EditorDraw(void)
{
    RSDK_THIS(SSZ1Outro);

    CutsceneRules_DrawCutsceneBounds(self, &self->size);
}

void SSZ1Outro_EditorLoad(void) {}
#endif

void SSZ1Outro_Serialize(void) { RSDK_EDITABLE_VAR(SSZ1Outro, VAR_VECTOR2, size); }
