#include "Types/ModifiersView.hpp"

#include "Helpers/ModifierHelper.hpp"
#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

DEFINE_TYPE(ReBeat, ModifiersView);

namespace ReBeat
{
    void ModifiersView::Initialize() {
        BSML::Register::RegisterGameplaySetupTab("Modifiers", MOD_ID "_ModifiersView", this);
    }

    void ModifiersView::Dispose() {
        BSML::Register::UnRegisterGameplaySetupTab("Modifiers");
    }

    void ModifiersView::PostParse() {
        Save(false);
    }

    StringW MaxRankFunc(float mul) {
        if (mul >= 0.9f) return "SS";
        if (mul >= 0.8f) return "S";
        if (mul >= 0.65f) return "A";
        if (mul >= 0.5f) return "B";
        if (mul >= 0.35f) return "C";
        if (mul >= 0.2f) return "D";
        return "E";
    }

    void ModifiersView::Save(bool config) {
        if (config)
            Helpers::ModifierHelper::Save();

        float multiplier = Helpers::ModifierHelper::GetMultiplier();

        UnityEngine::Color color = multiplier >= 1 ? UnityEngine::Color(0.0f, 0.75f, 1.0f, 1.0f) : UnityEngine::Color(1.0f, 0.37f, 0.0f, 1.0f);
        MultiplierValue->color = color;
        MultiplierValue->text = fmt::format("{:.2f}x", multiplier);
        MaxRank->color = color;
        MaxRank->text = MaxRankFunc(multiplier);
    }

    bool ModifiersView::get_NoFail() {
        return Helpers::ModifierHelper::NoFail;
    }

    void ModifiersView::set_NoFail(bool value) {
        Helpers::ModifierHelper::NoFail = value;
        Save();
    }

    bool ModifiersView::get_SlowerSong() {
        return Helpers::ModifierHelper::SlowerSong;
    }

    void ModifiersView::set_SlowerSong(bool value) {
        Helpers::ModifierHelper::SlowerSong = value;
        if (value)
        {
            Helpers::ModifierHelper::FasterSong = false;
            FasterSongToggle->toggle->set_isOn(false);
            Helpers::ModifierHelper::SuperFastSong = false;
            SuperFastSongToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_EasyMode() {
        return Helpers::ModifierHelper::EasyMode;
    }

    void ModifiersView::set_EasyMode(bool value) {
        Helpers::ModifierHelper::EasyMode = value;
        if (value)
        {
            Helpers::ModifierHelper::ProMode = false;
            ProModeToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_SameColor() {
        return Helpers::ModifierHelper::SameColor;
    }

    void ModifiersView::set_SameColor(bool value) {
        Helpers::ModifierHelper::SameColor = value;
        Save();
    }

    bool ModifiersView::get_OneLife() {
        return Helpers::ModifierHelper::OneLife;
    }

    void ModifiersView::set_OneLife(bool value) {
        Helpers::ModifierHelper::OneLife = value;
        if (value)
        {
            Helpers::ModifierHelper::OneHp = false;
            OneHpToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_FasterSong() {
        return Helpers::ModifierHelper::FasterSong;
    }

    void ModifiersView::set_FasterSong(bool value) {
        Helpers::ModifierHelper::FasterSong = value;
        if (value)
        {
            Helpers::ModifierHelper::SlowerSong = false;
            SlowerSongToggle->toggle->set_isOn(false);
            Helpers::ModifierHelper::SuperFastSong = false;
            SuperFastSongToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_ProMode() {
        return Helpers::ModifierHelper::ProMode;
    }

    void ModifiersView::set_ProMode(bool value) {
        Helpers::ModifierHelper::ProMode = value;
        if (value)
        {
            Helpers::ModifierHelper::EasyMode = false;
            EasyModeToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_OneHp() {
        return Helpers::ModifierHelper::OneHp;
    }

    void ModifiersView::set_OneHp(bool value) {
        Helpers::ModifierHelper::OneHp = value;
        if (value)
        {
            Helpers::ModifierHelper::OneLife = false;
            OneLifeToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_SuperFastSong() {
        return Helpers::ModifierHelper::SuperFastSong;
    }

    void ModifiersView::set_SuperFastSong(bool value) {
        Helpers::ModifierHelper::SuperFastSong = value;
        if (value)
        {
            Helpers::ModifierHelper::SlowerSong = false;
            SlowerSongToggle->toggle->set_isOn(false);
            Helpers::ModifierHelper::FasterSong = false;
            FasterSongToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_Hidden() {
        return Helpers::ModifierHelper::Hidden;
    }

    void ModifiersView::set_Hidden(bool value) {
        Helpers::ModifierHelper::Hidden = value;
        if (value)
        {
            Helpers::ModifierHelper::GhostNotes = false;
            GhostNotesToggle->toggle->set_isOn(false);
            if (Helpers::ModifierHelper::DisappearingArrows)
            {
                Helpers::ModifierHelper::NoArrows = false;
                NoArrowsToggle->toggle->set_isOn(false);
            }
            Helpers::ModifierHelper::DisappearingArrows = false;
            DisappearingArrowsToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_NoArrows() {
        return Helpers::ModifierHelper::NoArrows;
    }

    void ModifiersView::set_NoArrows(bool value) {
        Helpers::ModifierHelper::NoArrows = value;
        if (value)
        {
            Helpers::ModifierHelper::DisappearingArrows = false;
            DisappearingArrowsToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_GhostNotes() {
        return Helpers::ModifierHelper::GhostNotes;
    }

    void ModifiersView::set_GhostNotes(bool value) {
        Helpers::ModifierHelper::GhostNotes = value;
        if (value)
        {
            Helpers::ModifierHelper::Hidden = false;
            HiddenToggle->toggle->set_isOn(false);
            if (Helpers::ModifierHelper::DisappearingArrows)
            {
                Helpers::ModifierHelper::NoArrows = false;
                NoArrowsToggle->toggle->set_isOn(false);
            }
            Helpers::ModifierHelper::DisappearingArrows = false;
            DisappearingArrowsToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_NoBombs() {
        return Helpers::ModifierHelper::NoBombs;
    }

    void ModifiersView::set_NoBombs(bool value) {
        Helpers::ModifierHelper::NoBombs = value;
        Save();
    }

    bool ModifiersView::get_DisappearingArrows() {
        return Helpers::ModifierHelper::DisappearingArrows;
    }

    void ModifiersView::set_DisappearingArrows(bool value) {
        Helpers::ModifierHelper::DisappearingArrows = value;
        if (value)
        {
            Helpers::ModifierHelper::Hidden = false;
            HiddenToggle->toggle->set_isOn(false);
            Helpers::ModifierHelper::GhostNotes = false;
            GhostNotesToggle->toggle->set_isOn(false);
            Helpers::ModifierHelper::NoArrows = false;
            NoArrowsToggle->toggle->set_isOn(false);
        }
        Save();
    }

    bool ModifiersView::get_NoWalls() {
        return Helpers::ModifierHelper::NoWalls;
    }

    void ModifiersView::set_NoWalls(bool value) {
        Helpers::ModifierHelper::NoWalls = value;
        Save();
    }

    bool ModifiersView::get_SmallNotes() {
        return Helpers::ModifierHelper::SmallNotes;
    }

    void ModifiersView::set_SmallNotes(bool value) {
        Helpers::ModifierHelper::SmallNotes = value;
        Save();
    }
}