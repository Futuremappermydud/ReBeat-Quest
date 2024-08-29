/*#pragma once
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#include "lapiz/shared/macros.hpp"
#include "custom-types/shared/macros.hpp"

#include "bsml/shared/macros.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(ReBeat, ModifiersView, System::Object, std::vector<Il2CppClass*>({classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}),
                                 DECLARE_INSTANCE_METHOD(void, PostParse);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
                                 DECLARE_DEFAULT_CTOR();

    DECLARE_BSML_PROPERTY(bool, NoFail);
    DECLARE_BSML_PROPERTY(bool, SlowerSong);
    DECLARE_BSML_PROPERTY(bool, EasyMode);
    DECLARE_BSML_PROPERTY(bool, SameColor);
)*/