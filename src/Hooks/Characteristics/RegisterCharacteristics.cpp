#include "hooks.hpp"
#include "logger.hpp"
#include "assets.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "BGLib/Polyglot/Localization.hpp"
#include "BGLib/Polyglot/LocalizationModel.hpp"

#include "GlobalNamespace/BeatmapCharacteristicCollection.hpp"
#include "UnityEngine/Resources.hpp"

#include "bsml/shared/Helpers/utilities.hpp"
#include "songcore/shared/SongCore.hpp"

#include "Helpers/TextureHelper.hpp"
namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(RegisterCharacteristics_SetSingletonInstance, &BGLib::Polyglot::Localization::SetSingletonInstance, void, BGLib::Polyglot::LocalizationModel* instance)
    {
        RegisterCharacteristics_SetSingletonInstance(instance);

        ReBeat::Logger.info("Registering ReBeat! Characteristics");

        auto characteristics = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::BeatmapCharacteristicCollectionSO*>()->FirstOrDefault()->____beatmapCharacteristics;
        auto songCoreCharacteristics = SongCore::API::Characteristics::GetRegisteredCharacteristics();
        std::vector<GlobalNamespace::BeatmapCharacteristicSO*> mergeTarget;
        
        std::merge(characteristics.begin(), characteristics.end(), songCoreCharacteristics.begin(), songCoreCharacteristics.end(), 
            std::insert_iterator(mergeTarget, mergeTarget.end())
        );

        auto rebeatIcon = BSML::Utilities::LoadTextureRaw(IncludedAssets::icon_png);
        auto transferIcon = BSML::Utilities::LoadTextureRaw(IncludedAssets::transfer_png);

        for (auto characteristic : mergeTarget)
        {
            auto charIcon = characteristic->icon;
            auto charTex = charIcon->texture->isReadable ? charIcon->texture.ptr() : ReBeat::Helpers::TextureHelper::DuplicateTexture(charIcon);
            auto combined = BSML::Utilities::LoadSpriteFromTexture(
                ReBeat::Helpers::TextureHelper::MergeTextures({ rebeatIcon, transferIcon, charTex }));

            auto newCharacteristic = SongCore::API::Characteristics::CreateCharacteristic(combined, fmt::format("ReBeat! {}", characteristic->name), fmt::format("ReBeat! {}", BGLib::Polyglot::Localization::Get(characteristic->descriptionLocalizationKey)), fmt::format("ReBeat_{}", characteristic->serializedName), fmt::format("ReBeat_{}", characteristic->compoundIdPartName), characteristic->requires360Movement, characteristic->containsRotationEvents, characteristic->sortingOrder);
            SongCore::API::Characteristics::RegisterCustomCharacteristic(newCharacteristic);
        }
    }

    void RegisterCharacteristicsHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, RegisterCharacteristics_SetSingletonInstance);
    }
}