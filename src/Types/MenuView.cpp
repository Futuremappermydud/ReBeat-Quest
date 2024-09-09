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

    UnityEngine::Color MenuView::get_ShieldColor() {
        return getReBeatConfig().ShieldColor.GetValue();
    }

    void MenuView::set_ShieldColor(UnityEngine::Color value) {
        getReBeatConfig().ShieldColor.SetValue(value);
    }

    UnityEngine::Color MenuView::get_LowShieldColor() {
        return getReBeatConfig().LowShieldColor.GetValue();
    }

    void MenuView::set_LowShieldColor(UnityEngine::Color value) {
        getReBeatConfig().LowShieldColor.SetValue(value);
    }

    UnityEngine::Color MenuView::get_HealthColor() {
        return getReBeatConfig().HealthColor.GetValue();
    }

    void MenuView::set_HealthColor(UnityEngine::Color value) {
        getReBeatConfig().HealthColor.SetValue(value);
    }

    UnityEngine::Color MenuView::get_LowHealthColor() {
        return getReBeatConfig().LowHealthColor.GetValue();
    }

    void MenuView::set_LowHealthColor(UnityEngine::Color value) {
        getReBeatConfig().LowHealthColor.SetValue(value);
    }

    UnityEngine::Color MenuView::get_MinHealthColor() {
        return getReBeatConfig().MinHealthColor.GetValue();
    }

    void MenuView::set_MinHealthColor(UnityEngine::Color value) {
        getReBeatConfig().MinHealthColor.SetValue(value);
    }
}