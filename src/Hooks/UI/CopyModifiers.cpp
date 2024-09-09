#include "custom-types/shared/delegate.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/GameplayModifiersPanelController.hpp"
#include "System/Action.hpp"
#include "System/Nullable_1.hpp"

namespace ReBeat::Hooks
{
    SafePtr<GlobalNamespace::GameplayModifiers> modifiers;

    MAKE_HOOK_MATCH(CopyModifiers_Awake, &GlobalNamespace::GameplayModifiersPanelController::Awake, void, GlobalNamespace::GameplayModifiersPanelController* self)
    {
        CopyModifiers_Awake(self);
        self->add_didChangeGameplayModifiersEvent(custom_types::MakeDelegate<System::Action*>(std::function<void()>([self]() {
            modifiers = self->gameplayModifiers->CopyWith(System::Nullable_1<GlobalNamespace::GameplayModifiers::EnergyType>(false, GlobalNamespace::GameplayModifiers::EnergyType::Bar), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<GlobalNamespace::GameplayModifiers::EnabledObstacleType>(false, GlobalNamespace::GameplayModifiers::EnabledObstacleType::All), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<GlobalNamespace::GameplayModifiers::SongSpeed>(false, GlobalNamespace::GameplayModifiers::SongSpeed::Normal), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false), System::Nullable_1<bool>(false, false));
        })));
    }

    void CopyModifiersHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, CopyModifiers_Awake);
    }
}