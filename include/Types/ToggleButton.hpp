#pragma once
#include "System/IDisposable.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/EventSystems/PointerEventData.hpp"
#include "Zenject/IInitializable.hpp"

#include "bsml/shared/BSML/Components/ClickableImage.hpp"
#include "lapiz/shared/macros.hpp"
#include "custom-types/shared/macros.hpp"

#include "bsml/shared/macros.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN(ReBeat, ToggleButton, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Click);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_DEFAULT_CTOR();
    public:
    BSML::ClickableImage* image;
)