#include "Helpers/ModifierHelper.hpp"
#include "conditional-dependencies/shared/main.hpp"
#include "rebeatConfig.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type-c-linkage"

EXPOSE_API(GetEnabled, bool) {
    return getReBeatConfig().Enabled.GetValue();
}

EXPOSE_API(SetEnabled, void, bool enabled, bool temporary) {
    return getReBeatConfig().Enabled.SetValue(enabled, !temporary);
}

EXPOSE_API(GetHidden, bool) {
    return ReBeat::Helpers::ModifierHelper::Hidden;
}

EXPOSE_API(SetHidden, void, bool enabled) {
    ReBeat::Helpers::ModifierHelper::Hidden = enabled;
}

EXPOSE_API(GetSameColor, bool) {
    return ReBeat::Helpers::ModifierHelper::SameColor;
}

EXPOSE_API(SetSameColor, void, bool enabled) {
    ReBeat::Helpers::ModifierHelper::SameColor = enabled;
}

EXPOSE_API(GetEasyMode, bool) {
    return ReBeat::Helpers::ModifierHelper::EasyMode;
}

EXPOSE_API(SetEasyMode, void, bool enabled) {
    ReBeat::Helpers::ModifierHelper::EasyMode = enabled;
}

EXPOSE_API(GetOneHP, bool) {
    return ReBeat::Helpers::ModifierHelper::OneHp;
}

EXPOSE_API(SetOneHP, void, bool enabled) {
    ReBeat::Helpers::ModifierHelper::OneHp = enabled;
}