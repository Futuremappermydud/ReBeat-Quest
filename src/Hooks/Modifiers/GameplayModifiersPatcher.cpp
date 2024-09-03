#include "Helpers/ModifierHelper.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameplayModifiers.hpp"

namespace ReBeat::Hooks
{
    float SongSpeedMultiplier = 0;

    MAKE_HOOK_MATCH(GameplayModifiersPatcher_get_songSpeedMul, &GlobalNamespace::GameplayModifiers::get_songSpeedMul, float, GlobalNamespace::GameplayModifiers* self)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return GameplayModifiersPatcher_get_songSpeedMul(self);
        }
        auto result = GameplayModifiersPatcher_get_songSpeedMul(self);
        SongSpeedMultiplier = result;
        return result;
    }

    MAKE_HOOK_MATCH(GameplayModifiersPatcher_get_cutAngleTolerance, &GlobalNamespace::GameplayModifiers::get_cutAngleTolerance, float, GlobalNamespace::GameplayModifiers* self)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return GameplayModifiersPatcher_get_cutAngleTolerance(self);
        }
        return Helpers::ModifierHelper::ProMode ? 37.5f : Helpers::ModifierHelper::EasyMode ? 52.5f : 45.0f;
    }

    void GameplayModifiersPatcherHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, GameplayModifiersPatcher_get_songSpeedMul);
        INSTALL_HOOK(ReBeat::Logger, GameplayModifiersPatcher_get_cutAngleTolerance);
    }
}