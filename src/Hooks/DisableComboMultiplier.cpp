#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/ScoreMultiplierCounter.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(DisableComboMultiplier_ProcessMultiplierEvent, &GlobalNamespace::ScoreMultiplierCounter::ProcessMultiplierEvent, bool, GlobalNamespace::ScoreMultiplierCounter* self, GlobalNamespace::ScoreMultiplierCounter::MultiplierEventType multiplierEventType)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return DisableComboMultiplier_ProcessMultiplierEvent(self, multiplierEventType);
        }

        return false;
    }

    void DisableComboMultiplierHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, DisableComboMultiplier_ProcessMultiplierEvent);
    }
}