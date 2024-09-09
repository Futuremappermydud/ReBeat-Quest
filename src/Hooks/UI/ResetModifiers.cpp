#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameplaySetupViewController.hpp"
#include "GlobalNamespace/GameplayModifiersPanelController.hpp"

namespace ReBeat::Hooks
{
    SafePtrUnity<GlobalNamespace::GameplaySetupViewController> gsvcInstance;
    bool loadMods;

    MAKE_HOOK_MATCH(ResetModifiers_Setup, &GlobalNamespace::GameplaySetupViewController::Setup, void, GlobalNamespace::GameplaySetupViewController* self,
        bool showModifiers, bool showEnvironmentOverrideSettings, bool showColorSchemesSettings, bool showMultiplayer,
        GlobalNamespace::PlayerSettingsPanelController::PlayerSettingsPanelLayout playerSettingsPanelLayout)
    {
        ResetModifiers_Setup(self, showModifiers, showEnvironmentOverrideSettings, showColorSchemesSettings, showMultiplayer, playerSettingsPanelLayout);
        gsvcInstance = self;
    }

    MAKE_HOOK_MATCH(ResetModifiers_RefreshContent, &GlobalNamespace::GameplaySetupViewController::RefreshContent, void, GlobalNamespace::GameplaySetupViewController* self)
    {
        self->____showModifiers = !getReBeatConfig().Enabled.GetValue();
        if (loadMods && modifiers)
        {
            self->____gameplayModifiersPanelController->gameplayModifiers->_energyType = modifiers->energyType;
            self->____gameplayModifiersPanelController->gameplayModifiers->_noFailOn0Energy = modifiers->noFailOn0Energy;
            self->____gameplayModifiersPanelController->gameplayModifiers->_instaFail = modifiers->instaFail;
            self->____gameplayModifiersPanelController->gameplayModifiers->_failOnSaberClash = modifiers->failOnSaberClash;
            self->____gameplayModifiersPanelController->gameplayModifiers->_enabledObstacleType = modifiers->enabledObstacleType;
            self->____gameplayModifiersPanelController->gameplayModifiers->_noBombs = modifiers->noBombs;
            self->____gameplayModifiersPanelController->gameplayModifiers->_fastNotes = modifiers->fastNotes;
            self->____gameplayModifiersPanelController->gameplayModifiers->_strictAngles = modifiers->strictAngles;
            self->____gameplayModifiersPanelController->gameplayModifiers->_disappearingArrows = modifiers->disappearingArrows;
            self->____gameplayModifiersPanelController->gameplayModifiers->_songSpeed = modifiers->songSpeed;
            self->____gameplayModifiersPanelController->gameplayModifiers->_noArrows = modifiers->noArrows;
            self->____gameplayModifiersPanelController->gameplayModifiers->_ghostNotes = modifiers->ghostNotes;
            self->____gameplayModifiersPanelController->gameplayModifiers->_proMode = modifiers->proMode;
            self->____gameplayModifiersPanelController->gameplayModifiers->_zenMode = modifiers->zenMode;
            self->____gameplayModifiersPanelController->gameplayModifiers->_smallCubes = modifiers->smallCubes;

            loadMods = false;
        }
        ResetModifiers_RefreshContent(self);
    }

    void ResetModifiersHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, ResetModifiers_Setup);
        INSTALL_HOOK(ReBeat::Logger, ResetModifiers_RefreshContent);
    }
}