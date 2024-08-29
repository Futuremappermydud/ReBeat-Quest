#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberTypeExtensions.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(DisableWrongColorBadCut_HandleCut, &GlobalNamespace::GameNoteController::HandleCut, void, GlobalNamespace::GameNoteController* self, 
                                                        GlobalNamespace::Saber* saber, UnityEngine::Vector3 cutPoint, UnityEngine::Quaternion orientation, 
                                                        UnityEngine::Vector3 cutDir, bool allowBadCut)
    {
        if (!getReBeatConfig().Enabled.GetValue() || GlobalNamespace::SaberTypeExtensions::MatchesColorType(saber->get_saberType(), self->noteData->colorType))
        {
            return DisableWrongColorBadCut_HandleCut(self, saber, cutPoint, orientation, cutDir, allowBadCut);
        }
    }

    void DisableWrongColorBadCutHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, DisableWrongColorBadCut_HandleCut);
    }
}