#pragma once
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#include "lapiz/shared/macros.hpp"
#include "custom-types/shared/macros.hpp"

#include "bsml/shared/macros.hpp"

#include "UnityEngine/Color.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(ReBeat, MenuView, System::Object, std::vector<Il2CppClass*>({classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}),
                                 DECLARE_INSTANCE_METHOD(void, PostParse);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
                                 DECLARE_DEFAULT_CTOR();

    DECLARE_BSML_PROPERTY(bool, ShowComboPercent);
    DECLARE_BSML_PROPERTY(bool, UseLeftColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, ShieldColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, LowShieldColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, HealthColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, LowHealthColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, MinHealthColor);

)