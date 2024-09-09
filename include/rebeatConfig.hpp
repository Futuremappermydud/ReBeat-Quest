#pragma once

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/Color.hpp"

DECLARE_CONFIG(ReBeatConfig,
    CONFIG_VALUE(Enabled, bool, "Enabled", false);

    CONFIG_VALUE(Modifiers, std::vector<int>, "Modifiers", std::vector<int>({ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false }));

    CONFIG_VALUE(UseLeftColor, bool, "UseLeftColor", false);
    CONFIG_VALUE(ShowComboPercent, bool, "ShowComboPercent", false);

    CONFIG_VALUE(ShieldColor, UnityEngine::Color, "ShieldColor", UnityEngine::Color(0,1,1,1));
    CONFIG_VALUE(LowShieldColor, UnityEngine::Color, "LowShieldColor", UnityEngine::Color(0,0.57f,1,1));
    CONFIG_VALUE(HealthColor, UnityEngine::Color, "HealthColor", UnityEngine::Color(1,0,0,1));
    CONFIG_VALUE(LowHealthColor, UnityEngine::Color, "LowHealthColor", UnityEngine::Color(1,0.92f,0.016f,1));
    CONFIG_VALUE(MinHealthColor, UnityEngine::Color, "MinHealthColor", UnityEngine::Color(1,0,0,1));
)