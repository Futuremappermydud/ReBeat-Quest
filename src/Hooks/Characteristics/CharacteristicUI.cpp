#include "HMUI/ImageView.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "assets.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils-classes.hpp"
#include "bsml/shared/BSML-Lite/Creation/Image.hpp"
#include "bsml/shared/Helpers/utilities.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/BeatmapCharacteristicSegmentedControlController.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
#include "System/Linq/Enumerable.hpp"
#include "Types/ToggleButton.hpp"

#include "System/Collections/Generic/HashSet_1.hpp"

namespace ReBeat::Hooks
{
    bool isCustomLevel;

    MAKE_HOOK_MATCH(CharacteristicUI_Awake, &GlobalNamespace::BeatmapCharacteristicSegmentedControlController::Awake, void, GlobalNamespace::BeatmapCharacteristicSegmentedControlController* self)
    {
        CharacteristicUI_Awake(self);
        auto transform = il2cpp_utils::cast<UnityEngine::RectTransform>(self->transform->parent.ptr());
        transform->anchorMax = UnityEngine::Vector2(0.9f, 1.0f);

        auto parent = transform->parent;

        auto button = BSML::Lite::CreateClickableImage(parent, BSML::Utilities::LoadSpriteRaw(IncludedAssets::icon_png));
        button->gameObject->AddComponent<ReBeat::ToggleButton*>();
        button->transform->SetParent(parent->transform, false);

        auto buttonTransform = il2cpp_utils::cast<UnityEngine::RectTransform>(button->transform.ptr());
        buttonTransform->anchorMin = UnityEngine::Vector2(0.92f, 0.47f);
        buttonTransform->anchorMax = UnityEngine::Vector2(0.92f, 0.47f);
        buttonTransform->sizeDelta = UnityEngine::Vector2(5.0f, 5.0f);
    }


    MAKE_HOOK_MATCH(CharacteristicUI_SetData, &GlobalNamespace::BeatmapCharacteristicSegmentedControlController::SetData, void, GlobalNamespace::BeatmapCharacteristicSegmentedControlController* self,
        System::Collections::Generic::IEnumerable_1<UnityW<GlobalNamespace::BeatmapCharacteristicSO>>* beatmapCharacteristics,
        GlobalNamespace::BeatmapCharacteristicSO* selectedBeatmapCharacteristic,
        System::Collections::Generic::HashSet_1<UnityW<GlobalNamespace::BeatmapCharacteristicSO>>* notAllowedCharacteristics)
    {
        if(isCustomLevel)
        {
            ReBeat::Logger.info("hi!!!");
            auto rebeatData = System::Collections::Generic::List_1<UnityW<GlobalNamespace::BeatmapCharacteristicSO>>::New_ctor();
            auto* k2 = *reinterpret_cast<Il2CppClass**>(beatmapCharacteristics);
            ReBeat::Logger.info("adof {}", il2cpp_utils::ClassStandardName(k2, true));

            auto baseDataIter = il2cpp_utils::cast<System::Linq::Enumerable::_DistinctIterator_d__68_1<GlobalNamespace::BeatmapCharacteristicSO*>>(beatmapCharacteristics);
            ReBeat::Logger.info("hi1 {}", fmt::ptr(baseDataIter));
            ReBeat::Logger.info("source {}", fmt::ptr(baseDataIter->source));
            ReBeat::Logger.info("___source {}", fmt::ptr(baseDataIter->___source));
            ReBeat::Logger.info("_____3__source {}", fmt::ptr(baseDataIter->_____3__source));
            ReBeat::Logger.info("__3__source {}", fmt::ptr(baseDataIter->__3__source));
            ReBeat::Logger.info("___comparer {}", fmt::ptr(baseDataIter->___comparer));
            ReBeat::Logger.info("_____3__comparer {}", fmt::ptr(baseDataIter->_____3__comparer));
            ReBeat::Logger.info("comparer {}", fmt::ptr(baseDataIter->comparer));
            ReBeat::Logger.info("__3__comparer {}", fmt::ptr(baseDataIter->__3__comparer));

            auto hashSet = System::Collections::Generic::HashSet_1<GlobalNamespace::BeatmapCharacteristicSO*>::New_ctor(baseDataIter->__3__source, baseDataIter->comparer);  
            
            auto baseData = ArrayW<GlobalNamespace::BeatmapCharacteristicSO*>(hashSet->Count);
            hashSet->CopyTo(baseData);
            
            ReBeat::Logger.info("hi4 {}", baseData.size());

            for (auto item : baseData) {
                ReBeat::Logger.info("BRUH {}", fmt::ptr(item));
                ReBeat::Logger.info("BRUH2 {}", item->serializedName);
                if (item->serializedName.starts_with("ReBeat_") && getReBeatConfig().Enabled.GetValue()) {
                    ReBeat::Logger.info("hi5");
                    rebeatData->Add(item);
                }

                if (!item->serializedName.starts_with("ReBeat_") && !getReBeatConfig().Enabled.GetValue()) {
                    ReBeat::Logger.info("hi6");
                    rebeatData->Add(item);
                }
            }

            beatmapCharacteristics = rebeatData->i___System__Collections__Generic__IEnumerable_1_T_();
        }
        CharacteristicUI_SetData(self, beatmapCharacteristics, selectedBeatmapCharacteristic, notAllowedCharacteristics);
        if(isCustomLevel)
        {
            auto children = self->GetComponentsInChildren<HMUI::ImageView*>();
            for (auto child : children) {
                child->rectTransform->sizeDelta = UnityEngine::Vector2(10.0f, 4.0f);
            }
        }
    }

    void CharacteristicUIHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, CharacteristicUI_Awake);
        INSTALL_HOOK(ReBeat::Logger, CharacteristicUI_SetData);
    }
}