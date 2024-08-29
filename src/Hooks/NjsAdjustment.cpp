#include "Helpers/ModifierHelper.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnController.hpp"
#include "GlobalNamespace/Saber.hpp"

namespace ReBeat::Hooks
{
    float Multiplier(float speed) {
        switch ((int)(speed*10)) {
            case 12: return 1.1f;
            case 15: return 1.3f;
            default: return 1.0f;
        }
    }

    MAKE_HOOK_MATCH(NjsAdjustment_ctor, &GlobalNamespace::BeatmapObjectSpawnController::InitData::_ctor, void, GlobalNamespace::BeatmapObjectSpawnController::InitData* self,
                                        float beatsPerMinute, int noteLinesCount, float noteJumpMovementSpeed, 
                                        GlobalNamespace::BeatmapObjectSpawnMovementData::NoteJumpValueType noteJumpValueType, 
                                        float noteJumpValue)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return NjsAdjustment_ctor(self, beatsPerMinute, noteLinesCount, noteJumpMovementSpeed, noteJumpValueType, noteJumpValue);
        }
        
        NjsAdjustment_ctor(self, beatsPerMinute, noteLinesCount, noteJumpMovementSpeed, noteJumpValueType, noteJumpValue);

        float baseNjs = self->___noteJumpMovementSpeed;
        if (Helpers::ModifierHelper::ProMode) self->___noteJumpMovementSpeed = ((float)std::pow(self->___noteJumpMovementSpeed, 2) + 5.0f*self->___noteJumpMovementSpeed + 15.0f) / (self->___noteJumpMovementSpeed + 18.0f) + 11.0f;
        if (SongSpeedMultiplier <= 1) return;
        self->___noteJumpMovementSpeed *= Multiplier(SongSpeedMultiplier) / SongSpeedMultiplier;
    }

    void NjsAdjustmentHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, NjsAdjustment_ctor);
    }
}