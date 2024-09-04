#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "System/ValueTuple_2.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/BeatmapKey.hpp"
#include "GlobalNamespace/BeatmapLevel.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSegmentedControlController.hpp"
#include "GlobalNamespace/FileSystemBeatmapLevelData.hpp"
#include "UnityEngine/Resources.hpp"
#include "rebeatConfig.hpp"
#include "songcore/shared/SongCore.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include "songcore/shared/SongLoader/CustomBeatmapLevel.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(AddCharacteristic_SetContent, static_cast<void(GlobalNamespace::StandardLevelDetailView::*)(GlobalNamespace::BeatmapLevel*, GlobalNamespace::BeatmapDifficultyMask, System::Collections::Generic::HashSet_1<UnityW<GlobalNamespace::BeatmapCharacteristicSO>>*, GlobalNamespace::BeatmapDifficulty, GlobalNamespace::BeatmapCharacteristicSO*, GlobalNamespace::PlayerData*)>(&GlobalNamespace::StandardLevelDetailView::SetContent), void, GlobalNamespace::StandardLevelDetailView* self,
        GlobalNamespace::BeatmapLevel* level, ::GlobalNamespace::BeatmapDifficultyMask allowedBeatmapDifficultyMask,
                         ::System::Collections::Generic::HashSet_1<::UnityW<::GlobalNamespace::BeatmapCharacteristicSO>>* notAllowedCharacteristics,
                         ::GlobalNamespace::BeatmapDifficulty defaultDifficulty, ::GlobalNamespace::BeatmapCharacteristicSO* defaultBeatmapCharacteristic, 
                         ::GlobalNamespace::PlayerData* playerData)
    {
        ReBeat::Logger.info("AddCharacteristic_SetContent");
        if (!level->levelID->StartsWith("custom_level_"))
        {
            isCustomLevel = false;
            getReBeatConfig().Enabled.SetValue(false);
            ReBeat::Logger.info("ost level");
            return AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);
        }

        isCustomLevel = true;

        auto beatmapBasicData = level->beatmapBasicData;

        auto rebeatCharData = System::Collections::Generic::Dictionary_2<System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>, GlobalNamespace::BeatmapBasicData*>::New_ctor();

        auto baseCharData = il2cpp_utils::cast<System::Collections::Generic::Dictionary_2<System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>, GlobalNamespace::BeatmapBasicData*>>(beatmapBasicData);
        
        for (int i = 0; i < baseCharData->get_Count(); i++) {
            ReBeat::Logger.info("asdf {} {}", i, baseCharData->_entries[i].key.Item1->serializedName);
            if (baseCharData->_entries[i].key.Item1->serializedName->StartsWith("ReBeat_")) {
                return AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);
            }
        }

        for (int i = 0; i < baseCharData->get_Count(); i++) {
            auto pair = baseCharData->_entries[i];

            auto key = pair.key;
            auto value = pair.value;

            auto charSO = key.Item1;
            auto diff = key.Item2;  

            rebeatCharData->Add(key, value);

            ReBeat::Logger.info("added {}" , charSO->serializedName);

            if (charSO->serializedName->StartsWith("ReBeat_")) continue;   

            std::string name = "ReBeat_" + charSO->serializedName;

            ReBeat::Logger.info("Duplicating {} as {}", charSO->serializedName, name);
            auto rebeatChar = SongCore::API::Characteristics::GetCharacteristicBySerializedName(name);

            rebeatCharData->Add(System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>(rebeatChar, diff), value);
        }

        ReBeat::Logger.info("Total {} keys", rebeatCharData->get_Count());
        
        level->beatmapBasicData = rebeatCharData->i___System__Collections__Generic__IReadOnlyDictionary_2_TKey_TValue_();
        level->_beatmapKeysCache = nullptr;
        level->_characteristicsCache = nullptr;
        AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);
    }

    MAKE_HOOK_MATCH(AddCharacteristic_RefreshContent, &GlobalNamespace::StandardLevelDetailView::RefreshContent, void, GlobalNamespace::StandardLevelDetailView* self)
    {
        AddCharacteristic_RefreshContent(self);

        bool ribbit = self->____beatmapCharacteristicSegmentedControlController->selectedBeatmapCharacteristic->serializedName.starts_with("ReBeat_");
        if (getReBeatConfig().Enabled.GetValue() == ribbit) return;

        getReBeatConfig().Enabled.SetValue(ribbit);

        //blah;
    }

    MAKE_HOOK_MATCH(AddCharacteristic_GetDifficultyBeatmap, &GlobalNamespace::FileSystemBeatmapLevelData::GetDifficultyBeatmap, GlobalNamespace::FileDifficultyBeatmap*, GlobalNamespace::FileSystemBeatmapLevelData* self, ByRef<GlobalNamespace::BeatmapKey> beatmapKey)
    {
        if (beatmapKey->beatmapCharacteristic->serializedName.starts_with("ReBeat_"))
        {
            auto regularChar = beatmapKey->beatmapCharacteristic->serializedName->Substring(7);
            auto standardChar = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::BeatmapCharacteristicSO*>()->FirstOrDefault([&](GlobalNamespace::BeatmapCharacteristicSO* x) { return x->serializedName == regularChar; });
            auto key = GlobalNamespace::BeatmapKey(standardChar, beatmapKey->difficulty, beatmapKey->levelId);
            return AddCharacteristic_GetDifficultyBeatmap(self, key);
        }
        return AddCharacteristic_GetDifficultyBeatmap(self, beatmapKey);
    }

    void AddCharacteristicHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_SetContent);
        //INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_RefreshContent);
        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_GetDifficultyBeatmap);
    }
}