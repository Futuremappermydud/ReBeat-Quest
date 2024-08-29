
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/NoteData.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(AngleCutScore_GetNoteScoreDefinition, &GlobalNamespace::ScoreModel::GetNoteScoreDefinition, GlobalNamespace::ScoreModel::NoteScoreDefinition*, GlobalNamespace::NoteData::ScoringType scoringType)
    {
        static std::map<GlobalNamespace::NoteData::ScoringType, GlobalNamespace::ScoreModel::NoteScoreDefinition*> noteScoreDefinitions = {
            {GlobalNamespace::NoteData::ScoringType::Ignore, nullptr},
            {GlobalNamespace::NoteData::ScoringType::NoScore, GlobalNamespace::ScoreModel::NoteScoreDefinition::New_ctor(0,  0,  0,  0,  0,  0)},
            {GlobalNamespace::NoteData::ScoringType::Normal, GlobalNamespace::ScoreModel::NoteScoreDefinition::New_ctor(50, 0,  30, 0,  20, 0)},
            {GlobalNamespace::NoteData::ScoringType::SliderHead, GlobalNamespace::ScoreModel::NoteScoreDefinition::New_ctor(50, 0,  30, 20, 20, 0)},
            {GlobalNamespace::NoteData::ScoringType::SliderTail, GlobalNamespace::ScoreModel::NoteScoreDefinition::New_ctor(50, 30, 30, 0,  20, 0)},
            {GlobalNamespace::NoteData::ScoringType::BurstSliderHead, GlobalNamespace::ScoreModel::NoteScoreDefinition::New_ctor(50, 0,  50, 0,  0,  0)}, // hopefully these last two don't cause problems later lohl
            {GlobalNamespace::NoteData::ScoringType::BurstSliderElement, GlobalNamespace::ScoreModel::NoteScoreDefinition::New_ctor(0,  0,  0,  0,  0,  100)}
        };
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return AngleCutScore_GetNoteScoreDefinition(scoringType);
        }

        return noteScoreDefinitions[scoringType];
    }

    void AngleCutScoreHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, AngleCutScore_GetNoteScoreDefinition);
    }
}