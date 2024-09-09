#include "GlobalNamespace/zzzz__LevelScenesTransitionSetupDataSO_def.hpp"
#include "hooks.hpp"
#include "logger.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "System/Threading/Tasks/Task_1.hpp"

namespace ReBeat::Hooks
{
    float songLength = 0.0f;
    int noteCount = 0;

    MAKE_HOOK_MATCH(AudioLength, &GlobalNamespace::AudioTimeSyncController::InitData::_ctor, void, GlobalNamespace::AudioTimeSyncController::InitData* self, UnityEngine::AudioClip* audioClip, float_t startSongTime, float_t songTimeOffset, float_t timeScale)
    {
        songLength = audioClip->get_length();
        AudioLength(self, audioClip, startSongTime, songTimeOffset, timeScale);
    }

    MAKE_HOOK_MATCH(NoteCount, &GlobalNamespace::GameplayCoreSceneSetupData::TransformBeatmapData, GlobalNamespace::IReadonlyBeatmapData*, GlobalNamespace::GameplayCoreSceneSetupData* self, 
                                GlobalNamespace::IReadonlyBeatmapData* beatmapData)
    {
        auto result = NoteCount(self, beatmapData);
        noteCount = result->get_cuttableNotesCount();
        ReBeat::Logger.info("Note count: {}", noteCount);
        return result;
    }

    void BeatmapDataHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, AudioLength);
        INSTALL_HOOK(ReBeat::Logger, NoteCount);
    }
}