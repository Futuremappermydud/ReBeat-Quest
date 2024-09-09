#include "UnityEngine/Vector3.hpp"
#include "hooks.hpp"
#include "logger.hpp"
#include "rebeatConfig.hpp"
#include "Helpers/ModifierHelper.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "GlobalNamespace/BoxCuttableBySaber.hpp"
#include "UnityEngine/BoxCollider.hpp"

namespace ReBeat::Hooks
{
    MAKE_HOOK_MATCH(NoteColliderSize_Awake, &GlobalNamespace::BoxCuttableBySaber::Awake, void, GlobalNamespace::BoxCuttableBySaber* self)
    {
        if (!getReBeatConfig().Enabled.GetValue())
        {
            return NoteColliderSize_Awake(self);
        }
        UnityEngine::Vector3 size = Helpers::ModifierHelper::ProMode ? UnityEngine::Vector3(0.45f, 0.45f, 0.6f) :
                                    Helpers::ModifierHelper::EasyMode ? UnityEngine::Vector3(0.8f, 0.5f, 0.8f) : 
                                    UnityEngine::Vector3(0.5f, 0.5f, 0.7f);
        self->_collider->set_size(size);
        NoteColliderSize_Awake(self);
    }

    void NoteColliderSizeHooks()
    {
        INSTALL_HOOK(ReBeat::Logger, NoteColliderSize_Awake);
    }
}