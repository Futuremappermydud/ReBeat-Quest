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
        if (EnergyCounter->MaxHealth == 1) healthColor = getReBeatConfig().HealthColor.GetValue();
        else healthColor = EnergyCounter->Health > 3 ? getReBeatConfig().HealthColor.GetValue() :
            EnergyCounter->Health > 1 ? getReBeatConfig().LowHealthColor.GetValue() :
            getReBeatConfig().MinHealthColor.GetValue();

        UnityEngine::Color shieldColor = EnergyCounter->Shield < EnergyCounter->MaxShield
            ? getReBeatConfig().LowShieldColor.GetValue()
            : getReBeatConfig().ShieldColor.GetValue();

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

        static float _prevEnergyBarY = 0.0f;

        if (std::abs(std::abs(self->____energyBar->transform->position.y - _prevEnergyBarY) - 0.22) < 0.01) return;
        _prevEnergyBarY = self->____energyBar->transform->position.y;
        auto vector3 = self->____energyBar->transform->position;
        vector3.y -= 0.22f;
        self->____energyBar->transform->position = vector3;
    }

    void EnergyUIHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, EnergyUI_RefreshEnergyUI);
        INSTALL_HOOK(ReBeat::Logger, EnergyUI_Start);
    }
}