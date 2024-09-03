#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/SaberSwingRating.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(SwingRating_BeforeCutStepRating, &GlobalNamespace::SaberSwingRating::BeforeCutStepRating, float, float angleDiff, float normalDiff)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return SwingRating_BeforeCutStepRating(angleDiff, normalDiff);
        }

        return angleDiff * (1.0f - std::clamp((normalDiff - 75.0f) / 15.0f, 0.0f, 1.0f)) / 95.0f;
    }

    MAKE_HOOK_MATCH(SwingRating_AfterCutStepRating, &GlobalNamespace::SaberSwingRating::AfterCutStepRating, float, float angleDiff, float normalDiff)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return SwingRating_AfterCutStepRating(angleDiff, normalDiff);
        }

        return angleDiff * (1.0f - std::clamp((normalDiff - 75.0f) / 15.0f, 0.0f, 1.0f)) / 55.0f;
    }

    void SwingRatingHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, SwingRating_BeforeCutStepRating);
        INSTALL_HOOK(ReBeat::Logger, SwingRating_AfterCutStepRating);
    }
}