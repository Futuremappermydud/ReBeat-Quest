#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/CutScoreBuffer.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(CenterCutScoreHooks_Init, &GlobalNamespace::CutScoreBuffer::Init, bool, GlobalNamespace::CutScoreBuffer* self, ByRef<GlobalNamespace::NoteCutInfo> noteCutInfo)
    {
        auto result = CenterCutScoreHooks_Init(self, noteCutInfo);
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return result;
        }

        float sectorSize = 0.6f / 29.0f;
        float cutDistanceToCenter = noteCutInfo->cutDistanceToCenter;

        std::vector<float> sectors = Helpers::ModifierHelper::ProMode ? std::vector<float>({ 4.5f, 8.5f, 11.5f, 13.5f, 14.5f }) : 
                                     Helpers::ModifierHelper::EasyMode ? std::vector<float>({ 7.5f, 10.5f, 12.5f, 13.5f, 14.5f }) : 
                                     std::vector<float>({ 6.5f, 9.5f, 11.5f, 13.5f, 14.5f });

        self->____centerDistanceCutScore = cutDistanceToCenter < sectorSize * sectors[0] ? 50 :
                  cutDistanceToCenter < sectorSize * sectors[1] ? 44 :
                  cutDistanceToCenter < sectorSize * sectors[2] ? 36 :
                  cutDistanceToCenter < sectorSize * sectors[3] ? 22 :
                  cutDistanceToCenter < sectorSize * sectors[4] ? 10 : 0;

        return result;
    }

    void CenterCutScoreHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, CenterCutScoreHooks_Init);
    }
}