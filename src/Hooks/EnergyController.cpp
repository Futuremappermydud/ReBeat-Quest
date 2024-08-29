#include "Helpers/EnergyCounter.hpp"
#include "Helpers/ModifierHelper.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp" 

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/GameEnergyCounter.hpp"
#include "GlobalNamespace/PlayerHeadAndObstacleInteraction.hpp"
#include "UnityEngine/Time.hpp"

namespace ReBeat::Hooks
{
    Helpers::EnergyCounter* EnergyCounter;

    void HandleCut() {
        if (EnergyCounter->ShieldProgress >= EnergyCounter->ShieldRegen) return;
        if (UnityEngine::Time::get_time() - EnergyCounter->LastMiss < 0.2f) return;
        
        EnergyCounter->ShieldProgress++;

        if (EnergyCounter->ShieldProgress >= EnergyCounter->ShieldRegen && EnergyCounter->Shield < EnergyCounter->MaxShield) {
            EnergyCounter->Shield++;
            EnergyCounter->ShieldProgress = 0;
        }

        EnergyCounter->Combo++;
        if (EnergyCounter->Combo > EnergyCounter->MaxCombo) EnergyCounter->MaxCombo = EnergyCounter->Combo;
    }

    void HandleMiss() {
        EnergyCounter->LastMiss = UnityEngine::Time::get_time();
        EnergyCounter->ShieldProgress = 0;
        EnergyCounter->Misses++;

        EnergyCounter->TotalMisses++;
        EnergyCounter->Combo = 0;
    }

    MAKE_HOOK_MATCH(EnergyController_Start, &GlobalNamespace::GameEnergyCounter::Start, void, GlobalNamespace::GameEnergyCounter* self)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            EnergyController_Start(self);
            return;
        }
        EnergyCounter = Helpers::ModifierHelper::OneLife ? new Helpers::EnergyCounter(1, 0) : Helpers::ModifierHelper::OneHp ? new Helpers::EnergyCounter(1, 4) : new Helpers::EnergyCounter(5, 4);

        self->____batteryLives = EnergyCounter->Health + EnergyCounter->MaxShield;

        EnergyController_Start(self);
    }

    MAKE_HOOK_MATCH(EnergyController_LateUpdate, &GlobalNamespace::GameEnergyCounter::LateUpdate, void, GlobalNamespace::GameEnergyCounter* self)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            EnergyController_LateUpdate(self);
            return;
        }

        if (self->____playerHeadAndObstacleInteraction->get_playerHeadIsInObstacle())
        {
            if (EnergyCounter->WasInWallLastFrame) 
            {
                EnergyCounter->TimeToNextWallDamage -= UnityEngine::Time::get_deltaTime();
                if (EnergyCounter->TimeToNextWallDamage > 0) return;
            }

            EnergyCounter->WasInWallLastFrame = true;
            EnergyCounter->TimeToNextWallDamage = 0.5f;
            EnergyCounter->Misses++;
        }
        else
        {
            EnergyCounter->WasInWallLastFrame = false;
        }

        EnergyController_LateUpdate(self);
    }

    MAKE_HOOK_MATCH(EnergyController_ProcessEnergyChange, &GlobalNamespace::GameEnergyCounter::ProcessEnergyChange, void, GlobalNamespace::GameEnergyCounter* self, float energyChange)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            EnergyController_ProcessEnergyChange(self, energyChange);
            return;
        }

        energyChange = 0;
        self->set_energy(1);

        if (EnergyCounter->Misses == 0)
        {
            EnergyController_ProcessEnergyChange(self, energyChange);
            return;
        }

        if (EnergyCounter->Shield > 0 && EnergyCounter->Shield >= EnergyCounter->Misses) {
            EnergyCounter->Shield -= EnergyCounter->Misses;
            EnergyCounter->Misses = 0;
        }
        else if (EnergyCounter->Shield > 0) {
            EnergyCounter->Misses -= EnergyCounter->Shield;
            EnergyCounter->Shield = 0;
        }

        EnergyCounter->Health -= EnergyCounter->Misses;
        EnergyCounter->Misses = 0;

        if (EnergyCounter->Health < 1) {
            energyChange = -1.0f;
            self->set_energy(0.1f);
        }

        EnergyController_ProcessEnergyChange(self, energyChange);
    }

    MAKE_HOOK_MATCH(EnergyController_HandleNoteWasCut, &GlobalNamespace::GameEnergyCounter::HandleNoteWasCut, void, GlobalNamespace::GameEnergyCounter* self, 
                                                        GlobalNamespace::NoteController* noteController, ByRef<GlobalNamespace::NoteCutInfo> noteCutInfo)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            EnergyController_HandleNoteWasCut(self, noteController, noteCutInfo);
            return;
        }

        switch (noteController->noteData->gameplayType) {
            case GlobalNamespace::NoteData::GameplayType::Normal:
            case GlobalNamespace::NoteData::GameplayType::BurstSliderHead:
            case GlobalNamespace::NoteData::GameplayType::BurstSliderElement:
                if (noteCutInfo->allIsOK) {
                    HandleCut();
                }
                else HandleMiss();
                break;

            case GlobalNamespace::NoteData::GameplayType::Bomb:
                HandleMiss();
                break;
        }
        
        EnergyController_HandleNoteWasCut(self, noteController, noteCutInfo);
    }

    MAKE_HOOK_MATCH(EnergyController_HandleNoteWasMissed, &GlobalNamespace::GameEnergyCounter::HandleNoteWasMissed, void, GlobalNamespace::GameEnergyCounter* self, 
                                                        GlobalNamespace::NoteController* noteController)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            EnergyController_HandleNoteWasMissed(self, noteController);
            return;
        }

        if (noteController->noteData->gameplayType != GlobalNamespace::NoteData::GameplayType::Bomb) 
            HandleMiss();

        EnergyController_HandleNoteWasMissed(self, noteController);
    }

    void EnergyControllerHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, EnergyController_Start);
        INSTALL_HOOK(ReBeat::Logger, EnergyController_LateUpdate);
        INSTALL_HOOK(ReBeat::Logger, EnergyController_ProcessEnergyChange);
        INSTALL_HOOK(ReBeat::Logger, EnergyController_HandleNoteWasCut);
        INSTALL_HOOK(ReBeat::Logger, EnergyController_HandleNoteWasMissed);
    }
}