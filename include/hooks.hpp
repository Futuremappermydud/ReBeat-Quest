#pragma once

#include "Helpers/EnergyCounter.hpp"

namespace ReBeat::Hooks
{
    //Statics set by BeatmapData hooks
    extern float songLength;
    extern int noteCount;

    //Statics set by GameplayModifiersPatcher hooks
    extern float SongSpeedMultiplier;

    //Statics set by ScoreController hooks
    extern int TotalCutScore;
    extern int TotalNotes;
    extern int CurrentScore;
    extern int CurrentMaxScore;

    extern Helpers::EnergyCounter* EnergyCounter;

    void AddCharacteristicHooks();
    void AngleCutScoreHooks();
    void BeatmapDataHooks();
    void CenterCutScoreHooks();
    void DisableComboMultiplierHooks();
    void DisableWrongColorBadCutHooks();
    void DisplayRankHooks();
    void EnergyControllerHooks();
    void EnergyUIHooks();
    void GameplayModifiersPatcherHooks();
    void ModifierHooks();
    void ModMultiplierPatchHooks();
    void NjsAdjustmentHooks();
    void NoteColliderSizeHooks();
    void RelativeScoreHooks();
    void SameColorHooks();
    void ScoreControllerHooks();
    void SetModifiersHooks();
    void SwingRatingHooks();
}