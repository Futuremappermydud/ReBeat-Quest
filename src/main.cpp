#include "hooks.hpp"
#include "logger.hpp"
#include "_config.hpp"
#include "rebeatConfig.hpp"

#include "scotland2/shared/modloader.h"

#include "Installers/MenuInstaller.hpp"
#include "Types/MenuView.hpp"
#include "Types/ModifiersView.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    Paper::Logger::RegisterFileContextId(ReBeat::Logger.tag);
}

MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    getReBeatConfig().Init(modInfo);

    ReBeat::Hooks::BeatmapDataHooks();
    ReBeat::Hooks::EnergyControllerHooks();
    ReBeat::Hooks::ModifierHooks();
    ReBeat::Hooks::SameColorHooks();
    ReBeat::Hooks::DisableWrongColorBadCutHooks();
    ReBeat::Hooks::GameplayModifiersPatcherHooks();
    ReBeat::Hooks::NjsAdjustmentHooks();
    ReBeat::Hooks::NoteColliderSizeHooks();
    ReBeat::Hooks::SetModifiersHooks();
    ReBeat::Hooks::AngleCutScoreHooks();
    ReBeat::Hooks::CenterCutScoreHooks();
    ReBeat::Hooks::DisableComboMultiplierHooks();
    ReBeat::Hooks::ModMultiplierPatchHooks();
    ReBeat::Hooks::SwingRatingHooks();
    ReBeat::Hooks::ScoreControllerHooks();

    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    auto zenjector = ::Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<ReBeat::MenuInstaller*>(::Lapiz::Zenject::Location::Menu);

}