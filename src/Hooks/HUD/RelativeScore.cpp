#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/ImmediateRankUIPanel.hpp"
#include "GlobalNamespace/RelativeScoreAndImmediateRankCounter.hpp"
#include "GlobalNamespace/RankModel.hpp"
#include "System/Text/StringBuilder.hpp"

#include "BGLib/Polyglot/Localization.hpp"

namespace ReBeat::Hooks
{
    float get_relativeScore()
    {
        float relativeScore = getReBeatConfig().ShowComboPercent.GetValue() ? (float)CurrentScore / (float)CurrentMaxScore : 
                                                                              TotalCutScore / (TotalNotes * 100.0f);
        return TotalNotes == 0 ? 1 : relativeScore;
    }

    MAKE_HOOK_MATCH(RelativeScore_RefreshUI, &GlobalNamespace::ImmediateRankUIPanel::RefreshUI, void, GlobalNamespace::ImmediateRankUIPanel* self)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return RelativeScore_RefreshUI(self);
        }

        auto immediateRank = self->_relativeScoreAndImmediateRankCounter->get_immediateRank();
		if (immediateRank != self->_prevImmediateRank)
		{
			self->_rankText->text = GlobalNamespace::RankModel::GetRankName(immediateRank);
			self->_prevImmediateRank = immediateRank;
		}
		float relativeScore = get_relativeScore();
		if (std::abs(self->_prevRelativeScore - relativeScore) >= 0.001f)
		{
			self->_stringBuilder->Remove(0, self->_stringBuilder->get_Length());
			self->_stringBuilder->Append(fmt::format("{:.2f}%", relativeScore * 100.0f));
			self->_relativeScoreText->text = self->_stringBuilder->ToString();
			self->_prevRelativeScore = relativeScore;
		}
    }

    void RelativeScoreHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, RelativeScore_RefreshUI);
    }
}