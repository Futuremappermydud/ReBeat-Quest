/*#include "Types/ModifiersView.hpp"

#include "Helpers/ModifierHelper.hpp"
#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

DEFINE_TYPE(ReBeat, ModifiersView);

namespace ReBeat
{
    void ModifiersView::Initialize() {
        BSML::Register::RegisterGameplaySetupTab("ReBeat", MOD_ID "_ModifiersView", this);
    }

    void ModifiersView::Dispose() {
        BSML::Register::UnRegisterGameplaySetupTab("ReBeat");
    }

    void ModifiersView::PostParse() {

    }

    bool ModifiersView::get_NoFail() {
        return Helpers::ModifierHelper::NoFail;
    }

    void ModifiersView::set_NoFail(bool value) {
        Helpers::ModifierHelper::NoFail = value;
        Helpers::ModifierHelper::Save();
    }

    bool ModifiersView::get_SlowerSong() {
        return Helpers::ModifierHelper::SlowerSong;
    }

    void ModifiersView::set_SlowerSong(bool value) {
        Helpers::ModifierHelper::SlowerSong = value;
        Helpers::ModifierHelper::Save();
    }

    bool ModifiersView::get_EasyMode() {
        return Helpers::ModifierHelper::EasyMode;
    }

    void ModifiersView::set_EasyMode(bool value) {
        Helpers::ModifierHelper::EasyMode = value;
        Helpers::ModifierHelper::Save();
    }

    bool ModifiersView::get_SameColor() {
        return Helpers::ModifierHelper::SameColor;
    }

    void ModifiersView::set_SameColor(bool value) {
        Helpers::ModifierHelper::SameColor = value;
        Helpers::ModifierHelper::Save();
    }
}

BSML_DATACACHE(ModifiersView) {
    return Assets::Modifiers_bsml;
}*/