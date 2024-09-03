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

 UnityEngine::Sprite* TextureToSprite(UnityEngine::Texture2D* tex) {
        return (tex && tex->m_CachedPtr.m_value) ? UnityEngine::Sprite::Create(tex, UnityEngine::Rect(0.0f, 0.0f, (float)tex->get_width(), (float)tex->get_height()), UnityEngine::Vector2(0.5f,0.5f), 100.0f, 1u, UnityEngine::SpriteMeshType::FullRect, UnityEngine::Vector4(0.0f, 0.0f, 0.0f, 0.0f), false) : nullptr;
    }

UnityEngine::Sprite* ArrayToSprite(ArrayW<uint8_t> bytes) {
        UnityEngine::Texture2D* texture = UnityEngine::Texture2D::New_ctor(0, 0, UnityEngine::TextureFormat::RGBA32, true, false);
        if (UnityEngine::ImageConversion::LoadImage(texture, bytes, false)) {
            return TextureToSprite(texture);
        }
        UnityEngine::Object::DestroyImmediate(texture);
        return nullptr;
    }


MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    getReBeatConfig().Init(modInfo);

    ReBeat::Hooks::AddCharacteristicHooks();
    ReBeat::Hooks::AngleCutScoreHooks();
    ReBeat::Hooks::BeatmapDataHooks();
    ReBeat::Hooks::CenterCutScoreHooks();
    ReBeat::Hooks::DisableComboMultiplierHooks();
    ReBeat::Hooks::DisableWrongColorBadCutHooks();
    ReBeat::Hooks::DisplayRankHooks();
    ReBeat::Hooks::EnergyControllerHooks();
    ReBeat::Hooks::EnergyUIHooks();
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

    static SafePtrUnity<GlobalNamespace::BeatmapCharacteristicSO> rebeat = SongCore::API::Characteristics::CreateCharacteristic(
        BSML::Lite::ArrayToSprite(IncludedAssets::icon_png),
        "ReBeat",
        "ReBeat",
        "ReBeat_Standard",
        "ReBeat_Standard",
        false,
        false,
        0
    );

    SongCore::API::Characteristics::RegisterCustomCharacteristic(rebeat.ptr());
}

BSML_DATACACHE(MenuView) {
    return IncludedAssets::Menu_bsml;
}

BSML_DATACACHE(ModifiersView) {
    return IncludedAssets::Modifiers_bsml;
}