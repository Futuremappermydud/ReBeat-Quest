#include "Helpers/ModifierHelper.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/ColorType.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "UnityEngine/Color.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(SameColor_ColorForType, static_cast<UnityEngine::Color(GlobalNamespace::ColorManager::*)(GlobalNamespace::ColorType)>(&GlobalNamespace::ColorManager::ColorForType), UnityEngine::Color, GlobalNamespace::ColorManager* self, GlobalNamespace::ColorType colorType)
    {
        if (!getReBeatConfig().Enabled.GetValue() || !Helpers::ModifierHelper::SameColor)
        {
            return SameColor_ColorForType(self, colorType);
        }

        UnityEngine::Color result = UnityEngine::Color::get_black();

        if (colorType != GlobalNamespace::ColorType::None)
        {
            result = getReBeatConfig().UseLeftColor.GetValue() ? self->_colorScheme->saberAColor : self->_colorScheme->saberBColor;
        }
        return result;
    }

    MAKE_HOOK_MATCH(SameColor_ColorForSaberType, &GlobalNamespace::ColorManager::ColorForSaberType, UnityEngine::Color, GlobalNamespace::ColorManager* self, GlobalNamespace::SaberType saberType)
    {
        if (!getReBeatConfig().Enabled.GetValue() || !Helpers::ModifierHelper::SameColor)
        {
            return SameColor_ColorForSaberType(self, saberType);
        }

        return getReBeatConfig().UseLeftColor.GetValue() ? self->_colorScheme->saberAColor : self->_colorScheme->saberBColor;
    }

    MAKE_HOOK_MATCH(SameColor_EffectsColorForSaberType, &GlobalNamespace::ColorManager::EffectsColorForSaberType, UnityEngine::Color, GlobalNamespace::ColorManager* self, GlobalNamespace::SaberType saberType)
    {
        if (!getReBeatConfig().Enabled.GetValue() || !Helpers::ModifierHelper::SameColor)
        {
            return SameColor_EffectsColorForSaberType(self, saberType);
        }

        float h, s, v;

        if (getReBeatConfig().UseLeftColor.GetValue())
        {
            UnityEngine::Color::RGBToHSV(self->_colorScheme->saberAColor, h, s, v);
        }
        else
        {
            UnityEngine::Color::RGBToHSV(self->_colorScheme->saberBColor, h, s, v);
        }

        return UnityEngine::Color::HSVToRGB(h, s, 1);
    }

    void SameColorHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, SameColor_ColorForType);
        INSTALL_HOOK(ReBeat::Logger, SameColor_ColorForSaberType);
        INSTALL_HOOK(ReBeat::Logger, SameColor_EffectsColorForSaberType);
    }
}