#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameEnergyUIPanel.hpp"
#include "UnityEngine/Color.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(EnergyUI_RefreshEnergyUI, &GlobalNamespace::GameEnergyUIPanel::RefreshEnergyUI, void, GlobalNamespace::GameEnergyUIPanel* self, float energy)
    {
        EnergyUI_RefreshEnergyUI(self, energy);

        if (!getReBeatConfig().Enabled.GetValue())
        {
            return;
        }

        if (EnergyCounter->Health < 1) {
            for (auto image : self->____batteryLifeSegments->ToArray()) {
                image->enabled = false;
                self->____energyBar->gameObject->SetActive(false);
            }
        }

        UnityEngine::Color healthColor;
        if (EnergyCounter->MaxHealth == 1) healthColor = UnityEngine::Color::get_green();
        else healthColor = EnergyCounter->Health > 3 ? UnityEngine::Color::get_green() :
            EnergyCounter->Health > 1 ? UnityEngine::Color::get_yellow() :
            UnityEngine::Color::get_red();

        // 0 145 255
        UnityEngine::Color bruhColor = UnityEngine::Color(getReBeatConfig().ColorRed.GetValue()/255.0f, getReBeatConfig().ColorGreen.GetValue()/255.0f, getReBeatConfig().ColorBlue.GetValue()/255.0f, 1.0f);
        UnityEngine::Color shieldColor = EnergyCounter->Shield < EnergyCounter->MaxShield ? bruhColor : UnityEngine::Color::get_cyan();

        for (int i = 0; i < self->____batteryLifeSegments->get_Count(); i++) {
            if (i < EnergyCounter->Health) {
                self->____batteryLifeSegments->get_Item(i)->enabled = true;
                self->____batteryLifeSegments->get_Item(i)->color = healthColor;
            }
            else if (i < EnergyCounter->Health + EnergyCounter->Shield) {
                self->____batteryLifeSegments->get_Item(i)->enabled = true;
                self->____batteryLifeSegments->get_Item(i)->color = shieldColor;
            }
            else {
                self->____batteryLifeSegments->get_Item(i)->enabled = false;
            }
        }


            //recharge bar
        self->____energyBar->gameObject->SetActive(EnergyCounter->Shield < EnergyCounter->MaxShield);
        self->____energyBarRectTransform->anchorMax = UnityEngine::Vector2((float)EnergyCounter->ShieldProgress / (EnergyCounter->ShieldRegen-1.0f), 1.0f);
    }

    MAKE_HOOK_MATCH(EnergyUI_Start, &GlobalNamespace::GameEnergyUIPanel::Start, void, GlobalNamespace::GameEnergyUIPanel* self)
    {
        EnergyUI_Start(self);
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return;
        }

        self->____energyBar->gameObject->transform->position = UnityEngine::Vector3(-0.9539997f, -0.86f, 7.75f);
    }

    void EnergyUIHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, EnergyUI_RefreshEnergyUI);
        INSTALL_HOOK(ReBeat::Logger, EnergyUI_Start);
    }
}