#include "Helpers/ModifierHelper.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp" 

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/DisappearingArrowControllerBase_1.hpp"
#include "GlobalNamespace/DisappearingArrowController.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/NoteMovement.hpp"
#include "GlobalNamespace/CutoutAnimateEffect.hpp"
#include "GlobalNamespace/CutoutEffect.hpp"
#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "UnityEngine/Renderer.hpp"
#include <algorithm>

template <>
struct ::il2cpp_utils::il2cpp_type_check::MetadataGetter<
    &GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>::HandleCubeNoteControllerDidInit> {
  static MethodInfo const* get() {
    return il2cpp_utils::FindMethodUnsafe(classof(GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>*),
                                          "HandleCubeNoteControllerDidInit", 1);
  }
};

template <>
struct ::il2cpp_utils::il2cpp_type_check::MetadataGetter<
    &GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>::HandleNoteMovementNoteDidMoveInJumpPhase> {
  static MethodInfo const* get() {
    return il2cpp_utils::FindMethodUnsafe(classof(GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>*),
                                          "HandleNoteMovementNoteDidMoveInJumpPhase", 0);
  }
};

namespace ReBeat::Hooks
{
    MAKE_HOOK(Modifier_HandleCubeNoteControllerDidInit, nullptr, void, GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>* self,
          MethodInfo* methodInfo, Il2CppObject* gameNoteController) 
    {
        if (!getReBeatConfig().Enabled.GetValue() || Helpers::ModifierHelper::GhostNotes)
        {
            Modifier_HandleCubeNoteControllerDidInit(self, methodInfo, gameNoteController);
            return;
        }

        Modifier_HandleCubeNoteControllerDidInit(self, methodInfo, gameNoteController);

        self->____cubeMeshRenderer->enabled = true;
    }

    MAKE_HOOK(Modifier_HandleNoteMovementNoteDidMoveInJumpPhase, nullptr, void, GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>* self,
          MethodInfo* methodInfo) 
    {
        Modifier_HandleNoteMovementNoteDidMoveInJumpPhase(self, methodInfo);

        auto cast = il2cpp_utils::try_cast<GlobalNamespace::DisappearingArrowController>(self);
        if (!getReBeatConfig().Enabled.GetValue() || Helpers::ModifierHelper::GhostNotes || Helpers::ModifierHelper::DisappearingArrows || !cast.has_value())
        {
            return;
        }

        GlobalNamespace::DisappearingArrowController* dac = cast.value();

        float dist = dac->get_gameNoteController()->get_noteMovement()->distanceToPlayer;

         if (dist < 2.0f) return;

        auto cutoutAnimateEffect = self->gameObject->GetComponent<GlobalNamespace::CutoutAnimateEffect*>();
        if (cutoutAnimateEffect == nullptr) return;

        auto cutoutEffects = cutoutAnimateEffect->____cuttoutEffects;

        for (auto cutoutEffect : cutoutEffects) {
            if (!cutoutEffect->name->Equals("NoteCube")) continue;

            float val = std::clamp((dist - 2.0f) / 7.0f, 0.0f, 1.0f);
            val = val < 0.25 ? 0 : val; // the notes don't fully disappear without this
            cutoutEffect->SetCutout(1.0f - val);

            break;
        }
    }

    MAKE_HOOK_MATCH(Modifier_ConditionalMaterialSwitcher, &GlobalNamespace::ConditionalMaterialSwitcher::Awake, void, GlobalNamespace::ConditionalMaterialSwitcher* self) {
        Modifier_ConditionalMaterialSwitcher(self);
        auto name = self->get_gameObject()->get_name();
        ReBeat::Logger.info("ConditionalMaterialSwitcher: {}", name);
        if (name->Equals("NoteCube")) {
            self->_renderer->sharedMaterial = self->_material1;
        }
    }

    void ModifierHooks()
    {
        auto mInfo = il2cpp_utils::il2cpp_type_check::MetadataGetter<
            &GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>::HandleCubeNoteControllerDidInit>::get();

        auto mInfo2 = il2cpp_utils::il2cpp_type_check::MetadataGetter<
            &GlobalNamespace::DisappearingArrowControllerBase_1<Il2CppObject*>::HandleNoteMovementNoteDidMoveInJumpPhase>::get();

        INSTALL_HOOK_DIRECT(ReBeat::Logger, Modifier_HandleCubeNoteControllerDidInit, (void*)(mInfo->methodPointer));
        INSTALL_HOOK_DIRECT(ReBeat::Logger, Modifier_HandleNoteMovementNoteDidMoveInJumpPhase, (void*)(mInfo2->methodPointer));
        INSTALL_HOOK(ReBeat::Logger, Modifier_ConditionalMaterialSwitcher);
    }
}