#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/MainSystemInit.hpp"
#include "UnityEngine/BoxCollider.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(RegisterCharacteristics_MainSystemInit, &GlobalNamespace::MainSystemInit::InstallBindings, void, GlobalNamespace::MainSystemInit* self, Zenject::DiContainer* container, bool isRunningFromTests)
    {
        RegisterCharacteristics_MainSystemInit(self, container, isRunningFromTests);
    }

    void RegisterCharacteristicsHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, RegisterCharacteristics_MainSystemInit);
    }
}