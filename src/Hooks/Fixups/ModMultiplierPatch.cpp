#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameplayModifiersModelSO.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(ModMultiplierPatch_GetTotalMultiplier, &GlobalNamespace::GameplayModifiersModelSO::GetTotalMultiplier, float, GlobalNamespace::GameplayModifiersModelSO* self, System::Collections::Generic::List_1<::UnityW<::GlobalNamespace::GameplayModifierParamsSO>>* modifierParams, float_t energy)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return ModMultiplierPatch_GetTotalMultiplier(self, modifierParams, energy);
        }

        float mul = Helpers::ModifierHelper::GetMultiplier();
        if (Helpers::ModifierHelper::NoFail && energy <= 1E-05) mul -= 0.5f;
        return mul < 0.0f ? 0.0f : mul;
    }

    void ModMultiplierPatchHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, ModMultiplierPatch_GetTotalMultiplier);
    }
}