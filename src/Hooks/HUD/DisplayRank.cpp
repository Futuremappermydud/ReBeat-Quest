#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/RankModel.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(DisplayRank_GetRankForScore, &GlobalNamespace::RankModel::GetRankForScore, GlobalNamespace::RankModel::Rank, int multipliedScore, int modifiedScore, int maxMultipliedScore, int maxModifiedScore)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return DisplayRank_GetRankForScore(multipliedScore, modifiedScore, maxMultipliedScore, maxModifiedScore);
        }

        float relativeScore = TotalCutScore / (TotalNotes * 100.0f);

        if (relativeScore == 1.0f || TotalNotes == 0) return GlobalNamespace::RankModel::Rank::SSS;
        if (relativeScore > 0.9) { return GlobalNamespace::RankModel::Rank::SS; }
        if (relativeScore > 0.8) { return GlobalNamespace::RankModel::Rank::S; }
        if (relativeScore > 0.65) { return GlobalNamespace::RankModel::Rank::A; }
        if (relativeScore > 0.5) { return GlobalNamespace::RankModel::Rank::B; }
        if (relativeScore > 0.35) { return GlobalNamespace::RankModel::Rank::C; }
        if (relativeScore > 0.2) { return GlobalNamespace::RankModel::Rank::D; }
        return GlobalNamespace::RankModel::Rank::E;
    }

    void DisplayRankHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, DisplayRank_GetRankForScore);
    }
}