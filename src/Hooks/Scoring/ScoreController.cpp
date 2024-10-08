#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include <math.h>

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/IGameEnergyCounter.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/GameplayModifiersModelSO.hpp"
#include "GlobalNamespace/ScoreModel.hpp"
#include "GlobalNamespace/ScoringElement.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "System/Action_2.hpp"

namespace ReBeat::Hooks
{
    int TotalCutScore = 0;
    int TotalNotes = 0;
    int CurrentScore = 0;
    int CurrentMaxScore = 0;

    MAKE_HOOK_MATCH(ScoreController_Start, &GlobalNamespace::ScoreController::Start, void, GlobalNamespace::ScoreController* self)
    {
        ScoreController_Start(self);

        if (!getReBeatConfig().Enabled.GetValue())
        {
            return;
        }

        TotalCutScore = 0;
        TotalNotes = 0;
    }

    MAKE_HOOK_MATCH(ScoreController_LateUpdate, &GlobalNamespace::ScoreController::LateUpdate, void, GlobalNamespace::ScoreController* self)
    {
        ScoreController_LateUpdate(self);

        if (!getReBeatConfig().Enabled.GetValue())
        {
            return;
        }

        ReBeat::Logger.info("Hi!");

        double acc = ((double)TotalCutScore / ((double)TotalNotes*100.0f))*100.0f;
        int noteCount = TotalNotes;
        int misses = EnergyCounter->TotalMisses;
        int maxCombo = EnergyCounter->MaxCombo;

        ReBeat::Logger.info("x0 {} {}", TotalCutScore, TotalNotes);
        ReBeat::Logger.info("x1 {} {} {} {}", acc, noteCount, misses, maxCombo);

        double missCountCurve = noteCount / (50 * std::pow(misses, 2) + noteCount) * ((50.0f * noteCount + 1) / (50.0f * noteCount)) - 1 / (50.0f * noteCount);
        double maxComboCurve = std::pow(TotalNotes / ((1 - std::sqrt(0.5)) * maxCombo - TotalNotes), 2) - 1; 
        //const double j = 1d / 1020734678369717893d;
        double accCurve = (19.0444 * std::tan((M_PI / 133.0f) * acc - 4.22) + 35.5) * 0.01; // rip j
        
        ReBeat::Logger.info("x2 {} {} {}", missCountCurve, maxComboCurve, accCurve);

        int score = TotalCutScore == 0 || TotalNotes == 0 ? 0 : (int)(1000000.0f * ((missCountCurve * 0.3) + (maxComboCurve * 0.3) + (accCurve * 0.4)) * ((double)TotalNotes / (double)noteCount));
        self->____multipliedScore = score;
        self->____immediateMaxPossibleMultipliedScore = (int)(1000000.0f * ((double)TotalNotes / (double)noteCount));

        ReBeat::Logger.info("x3 {} {}", score, self->____immediateMaxPossibleMultipliedScore);

        // honestly just gonna leave this in case there's another score issue
        /*string s = $"{acc} {noteCount} {misses} {maxCombo} | {missCountCurve} {maxComboCurve} {accCurve} | {score}";
        if (s != prev) {
            Plugin.Log.Info(s);
            prev = s;
        }*/

        float totalMultiplier = self->____gameplayModifiersModel->GetTotalMultiplier(self->____gameplayModifierParams, self->____gameEnergyCounter->energy);
        if (totalMultiplier <= 0) {
            self->____multipliedScore = 0;
            self->____immediateMaxPossibleMultipliedScore = 0;
        }
        self->____modifiedScore = GlobalNamespace::ScoreModel::GetModifiedScoreForGameplayModifiersScoreMultiplier(self->____multipliedScore, totalMultiplier);
        self->____immediateMaxPossibleModifiedScore = GlobalNamespace::ScoreModel::GetModifiedScoreForGameplayModifiersScoreMultiplier(self->____immediateMaxPossibleMultipliedScore, totalMultiplier);

        ReBeat::Logger.info("x4 {} {}", self->____modifiedScore, self->____immediateMaxPossibleModifiedScore);

        CurrentScore = score;
        CurrentMaxScore = self->____immediateMaxPossibleMultipliedScore;

        System::Action_2<int, int>* action = self->scoreDidChangeEvent;
        if (action == nullptr) return;
        action->Invoke(self->____multipliedScore, self->____modifiedScore);
        ReBeat::Logger.info("x5");
    }

    MAKE_HOOK_MATCH(ScoreController_DespawnScoringElement, &GlobalNamespace::ScoreController::DespawnScoringElement, void, GlobalNamespace::ScoreController* self, GlobalNamespace::ScoringElement* scoringElement)
    {
        ScoreController_DespawnScoringElement(self, scoringElement);

        if (!getReBeatConfig().Enabled.GetValue() || scoringElement->noteData->gameplayType == GlobalNamespace::NoteData::GameplayType::Bomb)
        {
            return;
        }

        ReBeat::Logger.info("x6 {} {}", scoringElement->cutScore, scoringElement->noteData->gameplayType.value__);

        TotalCutScore += scoringElement->cutScore;
        TotalNotes++;
    }

    void ScoreControllerHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, ScoreController_Start);
        INSTALL_HOOK(ReBeat::Logger, ScoreController_LateUpdate);
        INSTALL_HOOK(ReBeat::Logger, ScoreController_DespawnScoringElement);
    }
}