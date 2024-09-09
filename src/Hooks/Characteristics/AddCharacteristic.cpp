#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
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
#include "songcore/shared/CustomJSONData.hpp"
#include "songcore/shared/SongCore.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/HashSet_1.hpp"
#include "songcore/shared/SongLoader/CustomBeatmapLevel.hpp"
#include <string>

namespace ReBeat::Hooks
{
    //Copy Original characteristic custom data to rebeat characteristic in json document
    void CopyCustomDataV3(SongCore::CustomJSONData::ValueUTF16& root, rapidjson::Document::AllocatorType& allocator) {
        if (root.HasMember(u"_difficultyBeatmapSets") && root[u"_difficultyBeatmapSets"].IsArray()) {
            auto& beatmapSets = root[u"_difficultyBeatmapSets"];

            int size = beatmapSets.Size();
            // Loop over the array of difficulty beatmap sets
            for (rapidjson::SizeType i = 0; i < size; i++) {
                // Create a copy of the current set
                SongCore::CustomJSONData::ValueUTF16 newSet(beatmapSets[i], allocator);

                // Modify the _beatmapCharacteristicName by prepending "ReBeat_"
                if (newSet.HasMember(u"_beatmapCharacteristicName") && newSet[u"_beatmapCharacteristicName"].IsString()) {
                    std::u16string originalName = newSet[u"_beatmapCharacteristicName"].GetString();
                    std::u16string newName = u"ReBeat_" + originalName;
                    newSet[u"_beatmapCharacteristicName"].SetString(newName.c_str(), allocator);
                }

                // Add the modified set to the array
                beatmapSets.PushBack(newSet, allocator);
            }
        }
    }

    void CopyCustomDataV4(SongCore::CustomJSONData::ValueUTF16& root, rapidjson::Document::AllocatorType& allocator) {
        if (root.HasMember(u"difficultyBeatmaps") && root[u"difficultyBeatmaps"].IsArray()) {
            auto& beatmaps = root[u"difficultyBeatmaps"];

            int size = beatmaps.Size();
            // Loop over the array of difficulty beatmap sets
            for (rapidjson::SizeType i = 0; i < size; i++) {
                // Create a copy of the current set
                SongCore::CustomJSONData::ValueUTF16 newSet(beatmaps[i], allocator);

                // Modify the _beatmapCharacteristicName by prepending "ReBeat_"
                if (newSet.HasMember(u"characteristic") && newSet[u"characteristic"].IsString()) {
                    std::u16string originalName = newSet[u"characteristic"].GetString();
                    std::u16string newName = u"ReBeat_" + originalName;
                    newSet[u"characteristic"].SetString(newName.c_str(), allocator);
                }

                // Add the modified set to the array
                beatmaps.PushBack(newSet, allocator);
            }
        }

        if (root.HasMember(u"characteristicData") && root[u"characteristicData"].IsObject())
        {
            if (root.HasMember(u"characteristicData") && root[u"characteristicData"].IsArray()) {
                auto& charData = root[u"characteristicData"];
                int size = charData.Size();
                // Loop over the array of difficulty beatmap sets
                for (rapidjson::SizeType i = 0; i < size; i++) {
                    // Create a copy of the current set
                    SongCore::CustomJSONData::ValueUTF16 newSet(charData[i], allocator);

                    // Modify the characteristic field by prepending "ReBeat_"
                    if (newSet.HasMember(u"characteristic") && newSet[u"characteristic"].IsString()) {
                        std::u16string originalName = newSet[u"characteristic"].GetString();
                        std::u16string newName = u"ReBeat_" + originalName;
                        newSet[u"characteristic"].SetString(newName.c_str(), allocator);
                    }

                    // Add the modified set to the array
                    charData.PushBack(newSet, allocator);
                }
            }
        }
    }

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
            return AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);
        }

        isCustomLevel = true;

        auto customBeatmapLevel = reinterpret_cast<SongCore::SongLoader::CustomBeatmapLevel*>(level);
        const auto& saveDataInfo = customBeatmapLevel->get_CustomSaveDataInfo().value().get();
        auto& document = saveDataInfo.doc;

        auto beatmapBasicData = level->beatmapBasicData;
        auto rebeatCharData = System::Collections::Generic::Dictionary_2<System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>, GlobalNamespace::BeatmapBasicData*>::New_ctor();
        auto baseCharData = il2cpp_utils::cast<System::Collections::Generic::Dictionary_2<System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>, GlobalNamespace::BeatmapBasicData*>>(beatmapBasicData);
        
        for (int i = 0; i < baseCharData->get_Count(); i++) {
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

            if (charSO->serializedName->StartsWith("ReBeat_")) continue;   

            std::string name = "ReBeat_" + charSO->serializedName;
            auto rebeatChar = SongCore::API::Characteristics::GetCharacteristicBySerializedName(name);

            rebeatCharData->Add(System::ValueTuple_2<UnityW<GlobalNamespace::BeatmapCharacteristicSO>, GlobalNamespace::BeatmapDifficulty>(rebeatChar, diff), value);
        }

        switch(saveDataInfo.saveDataVersion) {
			case SongCore::CustomJSONData::CustomSaveDataInfo::SaveDataVersion::Unknown: 
                break;
			case SongCore::CustomJSONData::CustomSaveDataInfo::SaveDataVersion::V3: 
                CopyCustomDataV3(document->GetObject(), document->GetAllocator());
                break;
			case SongCore::CustomJSONData::CustomSaveDataInfo::SaveDataVersion::V4:
                CopyCustomDataV4(document->GetObject(), document->GetAllocator()); 
                break;
		};

        CopyCustomDataV3(document->GetObject(), document->GetAllocator());
        
        level->beatmapBasicData = rebeatCharData->i___System__Collections__Generic__IReadOnlyDictionary_2_TKey_TValue_();
        level->_beatmapKeysCache = nullptr;
        level->_characteristicsCache = nullptr;
        AddCharacteristic_SetContent(self, level, allowedBeatmapDifficultyMask, notAllowedCharacteristics, defaultDifficulty, defaultBeatmapCharacteristic, playerData);
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
        loadMods = !getReBeatConfig().Enabled.GetValue();
        modifiers = GlobalNamespace::GameplayModifiers::New_ctor();

        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_SetContent);
        INSTALL_HOOK(ReBeat::Logger, AddCharacteristic_GetDifficultyBeatmap);
    }
}