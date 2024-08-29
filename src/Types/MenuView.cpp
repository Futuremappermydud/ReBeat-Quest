#include "Types/MenuView.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"
#include "rebeatConfig.hpp"

DEFINE_TYPE(ReBeat, MenuView);

namespace ReBeat
{
    void MenuView::Initialize() {
        BSML::Register::RegisterGameplaySetupTab("ReBeat", MOD_ID "_MenuView", this);
    }

    void MenuView::Dispose() {
        BSML::Register::UnRegisterGameplaySetupTab("ReBeat");
    }

    void MenuView::PostParse() {

    }

    bool MenuView::get_ShowComboPercent() {
        return getReBeatConfig().ShowComboPercent.GetValue();
    }

    void MenuView::set_ShowComboPercent(bool value) {
        getReBeatConfig().ShowComboPercent.SetValue(value);
    }

    bool MenuView::get_UseLeftColor() {
        return getReBeatConfig().UseLeftColor.GetValue();
    }

    void MenuView::set_UseLeftColor(bool value) {
        getReBeatConfig().UseLeftColor.SetValue(value);
    }

    float MenuView::get_ColorRed() {
        return getReBeatConfig().ColorRed.GetValue();
    }

    void MenuView::set_ColorRed(float value) {
        getReBeatConfig().ColorRed.SetValue(value);
    }

    float MenuView::get_ColorGreen() {
        return getReBeatConfig().ColorGreen.GetValue();
    }

    void MenuView::set_ColorGreen(float value) {
        getReBeatConfig().ColorGreen.SetValue(value);
    }

    float MenuView::get_ColorBlue() {
        return getReBeatConfig().ColorBlue.GetValue();
    }

    void MenuView::set_ColorBlue(float value) {
        getReBeatConfig().ColorBlue.SetValue(value);
    }
}

BSML_DATACACHE(Menu) {
    return Assets::Menu_bsml;
}