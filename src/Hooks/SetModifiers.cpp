#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/PracticeSettings.hpp"
#include "GlobalNamespace/BeatmapKey.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(
    SetModifiers_StartStandardLevel,
    static_cast<
        void (GlobalNamespace::MenuTransitionsHelper::*)(StringW, ByRef<GlobalNamespace::BeatmapKey>, GlobalNamespace::BeatmapLevel*, GlobalNamespace::OverrideEnvironmentSettings*, GlobalNamespace::ColorScheme*, GlobalNamespace::ColorScheme*, GlobalNamespace::GameplayModifiers*, GlobalNamespace::PlayerSpecificSettings*, GlobalNamespace::PracticeSettings*, GlobalNamespace::EnvironmentsListModel*, StringW, bool, bool, System::Action*, System::Action_1<Zenject::DiContainer*>*, System::Action_2<UnityW<GlobalNamespace::StandardLevelScenesTransitionSetupDataSO>, GlobalNamespace::LevelCompletionResults*>*, System::Action_2<UnityW<GlobalNamespace::LevelScenesTransitionSetupDataSO>, GlobalNamespace::LevelCompletionResults*>*, System::Nullable_1<GlobalNamespace::RecordingToolManager::SetupData>)>(
        &GlobalNamespace::MenuTransitionsHelper::StartStandardLevel
    ),
    void,
    GlobalNamespace::MenuTransitionsHelper* self,
    StringW gameMode,
    ByRef<GlobalNamespace::BeatmapKey> beatmapKey,
    GlobalNamespace::BeatmapLevel* beatmapLevel,
    GlobalNamespace::OverrideEnvironmentSettings* overrideEnvironmentSettings,
    GlobalNamespace::ColorScheme* overrideColorScheme,
    GlobalNamespace::ColorScheme* beatmapOverrideColorScheme,
    GlobalNamespace::GameplayModifiers* gameplayModifiers,
    GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings,
    GlobalNamespace::PracticeSettings* practiceSettings,
    GlobalNamespace::EnvironmentsListModel* environmentsListModel,
    StringW backButtonText,
    bool useTestNoteCutSoundEffects,
    bool startPaused,
    System::Action* beforeSceneSwitchCallback,
    System::Action_1<Zenject::DiContainer*>* afterSceneSwitchCallback,
    System::Action_2<UnityW<GlobalNamespace::StandardLevelScenesTransitionSetupDataSO>, GlobalNamespace::LevelCompletionResults*>* levelFinishedCallback,
    System::Action_2<UnityW<GlobalNamespace::LevelScenesTransitionSetupDataSO>, GlobalNamespace::LevelCompletionResults*>* levelRestartedCallback,
    System::Nullable_1<GlobalNamespace::RecordingToolManager::SetupData> recordingToolData) 
{
    if (getReBeatConfig().Enabled.GetValue())
    {
        gameplayModifiers->____energyType = GlobalNamespace::GameplayModifiers::EnergyType::Battery;
        gameplayModifiers->____noFailOn0Energy = Helpers::ModifierHelper::NoFail;
        gameplayModifiers->____instaFail = Helpers::ModifierHelper::OneLife;
        gameplayModifiers->____failOnSaberClash = false;
        gameplayModifiers->____enabledObstacleType = Helpers::ModifierHelper::GetEnabledObstacleType();
        gameplayModifiers->____noBombs = Helpers::ModifierHelper::NoBombs;
        gameplayModifiers->____fastNotes = false;
        gameplayModifiers->____strictAngles = false;
        gameplayModifiers->____disappearingArrows = Helpers::ModifierHelper::DisappearingArrows;
        gameplayModifiers->____songSpeed = Helpers::ModifierHelper::GetSongSpeed();
        gameplayModifiers->____noArrows = Helpers::ModifierHelper::NoArrows;
        gameplayModifiers->____ghostNotes = Helpers::ModifierHelper::GhostNotes || Helpers::ModifierHelper::Hidden;
        gameplayModifiers->____proMode = Helpers::ModifierHelper::ProMode;
        gameplayModifiers->____zenMode = false;
        gameplayModifiers->____smallCubes = Helpers::ModifierHelper::SmallNotes;
    }

    return SetModifiers_StartStandardLevel(
        self,
        gameMode,
        beatmapKey,
        beatmapLevel,
        overrideEnvironmentSettings,
        overrideColorScheme,
        beatmapOverrideColorScheme,
        gameplayModifiers,
        playerSpecificSettings,
        practiceSettings,
        environmentsListModel,
        backButtonText,
        useTestNoteCutSoundEffects,
        startPaused,
        beforeSceneSwitchCallback,
        afterSceneSwitchCallback,
        levelFinishedCallback,
        levelRestartedCallback,
        recordingToolData
    );
}

    void SetModifiersHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, SetModifiers_StartStandardLevel);
    }
}