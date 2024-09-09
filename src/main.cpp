#include "assets.hpp"
#include "bsml/shared/BSMLDataCache.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "_config.hpp"
#include "rebeatConfig.hpp"

#include "scotland2/shared/modloader.h"

#include "Installers/MenuInstaller.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"

#include "songcore/shared/SongCore.hpp"

#include "UnityEngine/ImageConversion.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    Paper::Logger::RegisterFileContextId(ReBeat::Logger.tag);
}

MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    getReBeatConfig().Init(modInfo);

    ReBeat::Hooks::AddCharacteristicHooks();
    ReBeat::Hooks::CharacteristicUIHooks();
    ReBeat::Hooks::RegisterCharacteristicsHooks();
    ReBeat::Hooks::AngleCutScoreHooks();
    ReBeat::Hooks::BeatmapDataHooks();
    ReBeat::Hooks::CenterCutScoreHooks();
    ReBeat::Hooks::DisableComboMultiplierHooks();
    ReBeat::Hooks::DisableWrongColorBadCutHooks();
    ReBeat::Hooks::DisplayRankHooks();
    ReBeat::Hooks::EnergyControllerHooks();
    ReBeat::Hooks::CopyModifiersHooks();
    ReBeat::Hooks::EnergyUIHooks();
    ReBeat::Hooks::ResetModifiersHooks();
    ReBeat::Hooks::GameplayModifiersPatcherHooks();
    ReBeat::Hooks::ModifierHooks();
    ReBeat::Hooks::ModMultiplierPatchHooks();
    ReBeat::Hooks::NjsAdjustmentHooks();
    ReBeat::Hooks::NoteColliderSizeHooks();
    ReBeat::Hooks::RelativeScoreHooks();
    ReBeat::Hooks::SameColorHooks();
    ReBeat::Hooks::ScoreControllerHooks();
    ReBeat::Hooks::SetModifiersHooks();
    ReBeat::Hooks::SwingRatingHooks();

    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<ReBeat::MenuInstaller*>(::Lapiz::Zenject::Location::Menu);
}

BSML_DATACACHE(MenuView) {
    return IncludedAssets::Menu_bsml;
}

BSML_DATACACHE(ModifiersView) {
    return IncludedAssets::Modifiers_bsml;
}