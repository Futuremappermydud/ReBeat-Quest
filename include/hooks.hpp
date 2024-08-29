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

    void BeatmapDataHooks();
    void EnergyControllerHooks();
    void ModifierHooks();
    void SameColorHooks();
    void DisableWrongColorBadCutHooks();
    void GameplayModifiersPatcherHooks();
    void NjsAdjustmentHooks();
    void NoteColliderSizeHooks();
    void SetModifiersHooks();
    void AngleCutScoreHooks();
    void CenterCutScoreHooks();
    void DisableComboMultiplierHooks();
    void ModMultiplierPatchHooks();
    void SwingRatingHooks();
    void ScoreControllerHooks();
    void EnergyUIHooks();
}