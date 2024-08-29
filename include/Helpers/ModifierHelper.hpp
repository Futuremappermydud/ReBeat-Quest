#pragma once

#include "GlobalNamespace/GameplayModifiers.hpp"

namespace ReBeat::Helpers
{
    class ModifierHelper
    {
        public:
            static bool NoFail;
            static bool OneLife;
            static bool OneHp;
            static bool NoBombs;
            static bool NoWalls;
            static bool EasyMode;
            static bool Hidden;
            static bool DisappearingArrows;
            static bool SameColor;
            static bool ProMode;
            static bool GhostNotes;
            static bool SlowerSong;
            static bool FasterSong;
            static bool SuperFastSong;
            static bool NoArrows;
            static bool SmallNotes;

            static void Enable();
            static void Load();
            static void Save();

            static float GetMultiplier();
            static GlobalNamespace::GameplayModifiers::EnabledObstacleType GetEnabledObstacleType();
            static GlobalNamespace::GameplayModifiers::SongSpeed GetSongSpeed();

    };
}