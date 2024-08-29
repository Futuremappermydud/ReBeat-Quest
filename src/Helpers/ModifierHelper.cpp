#include "Helpers/ModifierHelper.hpp"
#include "rebeatConfig.hpp"

namespace ReBeat::Helpers
{
    bool ModifierHelper::NoFail = false;
    bool ModifierHelper::OneLife = false;
    bool ModifierHelper::OneHp = false;
    bool ModifierHelper::NoBombs = false;
    bool ModifierHelper::NoWalls = false;
    bool ModifierHelper::EasyMode = false;
    bool ModifierHelper::Hidden = false;
    bool ModifierHelper::DisappearingArrows = false;
    bool ModifierHelper::SameColor = false;
    bool ModifierHelper::ProMode = false;
    bool ModifierHelper::GhostNotes = false;
    bool ModifierHelper::SlowerSong = false;
    bool ModifierHelper::FasterSong = false;
    bool ModifierHelper::SuperFastSong = false;
    bool ModifierHelper::NoArrows = false;
    bool ModifierHelper::SmallNotes = false;

    std::vector<int> GetModifiers() 
    {
        return std::vector<int> { 
            ModifierHelper::NoFail, ModifierHelper::OneLife, ModifierHelper::OneHp, ModifierHelper::NoBombs, 
            ModifierHelper::NoWalls, ModifierHelper::EasyMode, ModifierHelper::Hidden, ModifierHelper::DisappearingArrows, 
            ModifierHelper::SameColor, ModifierHelper::ProMode, ModifierHelper::GhostNotes, ModifierHelper::SlowerSong, 
            ModifierHelper::FasterSong, ModifierHelper::SuperFastSong, ModifierHelper::NoArrows, ModifierHelper::SmallNotes 
        };
    }

    void ModifierHelper::Enable()
    {
        Load();
    }

    void ModifierHelper::Load()
    {
        auto modifiers = getReBeatConfig().Modifiers.GetValue();

        if (modifiers.size() != 16) return;

        NoFail = modifiers[0];
        OneLife = modifiers[1];
        OneHp = modifiers[2];
        NoBombs = modifiers[3];
        NoWalls = modifiers[4];
        EasyMode = modifiers[5];
        Hidden = modifiers[6];
        DisappearingArrows = modifiers[7];
        SameColor = modifiers[8];
        ProMode = modifiers[9];
        GhostNotes = modifiers[10];
        SlowerSong = modifiers[11];
        FasterSong = modifiers[12];
        SuperFastSong = modifiers[13];
        NoArrows = modifiers[14];
        SmallNotes = modifiers[15];
    }

    void ModifierHelper::Save()
    {
        getReBeatConfig().Modifiers.SetValue(GetModifiers());
    }

    float ModifierHelper::GetMultiplier()
    {
        static std::vector<float> Multipliers = { 
         //  nf    1l   1hp     nb     nw    easy  hidden  da  sameColor
            0.0f, 0.0f, 0.0f, -0.4f, -0.4f, -0.4f, 0.05f, 0.0f, 0.07f,
         // pro     gn     ss    fs    sfs      na    sn
            0.12f, 0.0f, -0.5f, 0.07f, 0.15f, -1.0f, 0.0f };

        if (NoArrows) return 0;
        auto mods = GetModifiers();
        float multiplier = 1.0f;
        for (int i = 0; i < mods.size(); i++) {
            if (mods[i]) multiplier += Multipliers[i];
        }

        if (multiplier <= 0) return 0;
        return multiplier;
    }

    GlobalNamespace::GameplayModifiers::EnabledObstacleType ModifierHelper::GetEnabledObstacleType()
    {
        return NoWalls ? GlobalNamespace::GameplayModifiers::EnabledObstacleType::NoObstacles : GlobalNamespace::GameplayModifiers::EnabledObstacleType::All;
    }

    GlobalNamespace::GameplayModifiers::SongSpeed ModifierHelper::GetSongSpeed()
    {
        return SuperFastSong ? GlobalNamespace::GameplayModifiers::SongSpeed::SuperFast :
                FasterSong ? GlobalNamespace::GameplayModifiers::SongSpeed::Faster :
                SlowerSong ? GlobalNamespace::GameplayModifiers::SongSpeed::Slower : 
                GlobalNamespace::GameplayModifiers::SongSpeed::Normal;
    }
}