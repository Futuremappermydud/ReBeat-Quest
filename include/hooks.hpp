#pragma once

#include "GlobalNamespace/GameplayModifiers.hpp"
#include "Helpers/EnergyCounter.hpp"
#include "beatsaber-hook/shared/utils/typedefs-wrappers.hpp"

#include "GlobalNamespace/GameplaySetupViewController.hpp"

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

    //Statics set by Characteristic hooks
    extern bool isCustomLevel;

    //Statics set by CopyModifiers hooks
    extern SafePtr<GlobalNamespace::GameplayModifiers> modifiers;

    //Statics set by ResetModifiers hooks
    extern SafePtrUnity<GlobalNamespace::GameplaySetupViewController> gsvcInstance;
    extern bool loadMods;

    extern Helpers::EnergyCounter* EnergyCounter;

    void AddCharacteristicHooks();
    void CharacteristicUIHooks();
    void RegisterCharacteristicsHooks();
    void AngleCutScoreHooks();
    void BeatmapDataHooks();
    void CenterCutScoreHooks();
    void DisableComboMultiplierHooks();
    void DisableWrongColorBadCutHooks();
    void DisplayRankHooks();
    void EnergyControllerHooks();
    void CopyModifiersHooks();
    void EnergyUIHooks();
    void ResetModifiersHooks();
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