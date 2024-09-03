#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
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
        if (!level->levelID->StartsWith("custom_level_")) return AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);

        auto rebeatChar = SongCore::API::Characteristics::GetCharacteristicBySerializedName("ReBeat_Standard");

        bool standardCharset = false;
            
        auto beatmapBasicData = level->beatmapBasicData;
        auto rebeatCharData = System::Collections::Generic::Dictionary_2<System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>, GlobalNamespace::BeatmapBasicData*>::New_ctor();

        auto baseCharData = il2cpp_utils::cast<System::Collections::Generic::Dictionary_2<System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>, GlobalNamespace::BeatmapBasicData*>>(beatmapBasicData);
        
        for (int i = 0; i < baseCharData->get_Count(); i++) {
            auto pair = baseCharData->_entries[i];

            auto key = pair.key;
            auto value = pair.value;

            auto charSO = key.Item1;
            auto diff = key.Item2;  

            rebeatCharData->Add(key, value);

            if (charSO->serializedName == "ReBeat") return AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);

            if (charSO->serializedName == "Standard")
            {
                rebeatCharData->Add(System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>(rebeatChar, diff), value);
            }
        }
        
        level->beatmapBasicData = rebeatCharData->i___System__Collections__Generic__IReadOnlyDictionary_2_TKey_TValue_();
        AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);
    }

    MAKE_HOOK_MATCH(AddCharacteristic_RefreshContent, &GlobalNamespace::StandardLevelDetailView::RefreshContent, void, GlobalNamespace::StandardLevelDetailView* self)
    {
        AddCharacteristic_RefreshContent(self);

        bool ribbit = self->____beatmapCharacteristicSegmentedControlController->selectedBeatmapCharacteristic->serializedName == "ReBeat_Standard";
        if (getReBeatConfig().Enabled.GetValue() == ribbit) return;

        getReBeatConfig().Enabled.SetValue(ribbit);

        //blah;
    }

    MAKE_HOOK_MATCH(AddCharacteristic_GetDifficultyBeatmap, &GlobalNamespace::FileSystemBeatmapLevelData::GetDifficultyBeatmap, GlobalNamespace::FileDifficultyBeatmap*, GlobalNamespace::FileSystemBeatmapLevelData* self, ByRef<GlobalNamespace::BeatmapKey> beatmapKey)
    {
        if (beatmapKey->beatmapCharacteristic->serializedName == "ReBeat_Standard")
        {
            auto standardChar = UnityEngine::Resources::FindObjectsOfTypeAll<GlobalNamespace::BeatmapCharacteristicSO*>()->FirstOrDefault([&](GlobalNamespace::BeatmapCharacteristicSO* x) { return x->serializedName == "Standard"; });
            auto key = GlobalNamespace::BeatmapKey(standardChar, beatmapKey->difficulty, beatmapKey->levelId);
            return AddCharacteristic_GetDifficultyBeatmap(self, key);
        }
        return AddCharacteristic_GetDifficultyBeatmap(self, beatmapKey);
    }

    void AddCharacteristicHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_SetContent);
        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_RefreshContent);
        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_GetDifficultyBeatmap);
    }
}