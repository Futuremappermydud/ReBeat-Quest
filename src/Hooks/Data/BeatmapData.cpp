#include "hooks.hpp"
#include "logger.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/BeatmapDataLoader.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"
#include "UnityEngine/AudioClip.hpp"

namespace ReBeat::Hooks
{
    float songLength = 0.0f;
    int noteCount = 0;

    MAKE_HOOK_MATCH(AudioLength, &GlobalNamespace::AudioTimeSyncController::InitData::_ctor, void, GlobalNamespace::AudioTimeSyncController::InitData* self, UnityEngine::AudioClip* audioClip, float_t startSongTime, float_t songTimeOffset, float_t timeScale)
    {
        songLength = audioClip->get_length();
        AudioLength(self, audioClip, startSongTime, songTimeOffset, timeScale);
    }

    MAKE_HOOK_MATCH(NoteCount, &GlobalNamespace::BeatmapDataLoader::LoadBeatmapData, GlobalNamespace::IReadonlyBeatmapData*, GlobalNamespace::BeatmapDataLoader* self, 
                                ::GlobalNamespace::IBeatmapLevelData* beatmapLevelData, 
                                ::GlobalNamespace::BeatmapKey beatmapKey,
                                ::float_t startBpm, bool loadingForDesignatedEnvironment,
                                ::GlobalNamespace::IEnvironmentInfo* environmentInfo,
                                ::GlobalNamespace::GameplayModifiers* gameplayModifiers,
                                ::GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings)
    {
        auto result = NoteCount(self, beatmapLevelData, beatmapKey, startBpm, loadingForDesignatedEnvironment, environmentInfo, gameplayModifiers, playerSpecificSettings);
        noteCount = result->get_cuttableNotesCount();
        return result;
    }

    void BeatmapDataHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, AudioLength);
        INSTALL_HOOK(ReBeat::Logger, NoteCount);
    }
}