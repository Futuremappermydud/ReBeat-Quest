#include "Helpers/EnergyCounter.hpp"
#include "hooks.hpp"
#include <cmath>

namespace ReBeat::Helpers
{
    EnergyCounter::EnergyCounter(int maxHealth, int maxShield)
    {
        MaxShield = maxShield;
        MaxHealth = maxHealth;
        
        Health = maxHealth;
        Shield = maxShield;

        ShieldProgress = 0;
        ShieldRegen = (int)std::round(-20.0f / (1.0f + std::pow(2.71828182845904523536, (ReBeat::Hooks::noteCount / ReBeat::Hooks::songLength - 10.0f) / 2.0f)) + 30.0f);
        LastMiss = 0;
        WasInWallLastFrame = false;

        Misses = 0;
        TotalMisses = 0;

        Combo = 0;
        MaxCombo = 0;
    }

    EnergyCounter::~EnergyCounter()
    {
    }
}