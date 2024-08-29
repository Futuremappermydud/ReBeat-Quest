#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ReBeatConfig,
    CONFIG_VALUE(Enabled, bool, "Enabled", false);
    CONFIG_VALUE(UseLeftColor, bool, "UseLeftColor", false);
    CONFIG_VALUE(ShowComboPercent, bool, "ShowComboPercent", false);
    CONFIG_VALUE(ColorRed, float, "ColorRed", 0);
    CONFIG_VALUE(ColorGreen, float, "ColorGreen", 145.0f);
    CONFIG_VALUE(ColorBlue, float, "ColorBlue", 255.0f);
    CONFIG_VALUE(Modifiers, std::vector<int>, "Modifiers", std::vector<int>({ false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false }));
)