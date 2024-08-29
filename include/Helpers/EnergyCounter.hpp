#pragma once

namespace ReBeat::Helpers
{
    class EnergyCounter
    {
        public:
            EnergyCounter(int maxHealth, int maxShield);
            ~EnergyCounter();

            int MaxShield;
            int MaxHealth;
            
            int Health;
            int Shield;
            int ShieldProgress;
            int ShieldRegen;
            float LastMiss;
            float TimeToNextWallDamage = 0.5f;
            bool WasInWallLastFrame;

            int Misses;
            int TotalMisses;

            int Combo;
            int MaxCombo;
    };
}