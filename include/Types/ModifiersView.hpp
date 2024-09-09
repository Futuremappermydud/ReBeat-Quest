#pragma once
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#include "bsml/shared/BSML/Components/Settings/ToggleSetting.hpp"
#include "lapiz/shared/macros.hpp"
#include "custom-types/shared/macros.hpp"

#include "bsml/shared/macros.hpp"

#include "TMPro/TextMeshProUGUI.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(ReBeat, ModifiersView, System::Object, std::vector<Il2CppClass*>({classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}),
                                 DECLARE_INSTANCE_METHOD(void, PostParse);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
                                 DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
                                 DECLARE_DEFAULT_CTOR();

    DECLARE_BSML_PROPERTY(bool, NoFail);
    DECLARE_BSML_PROPERTY(bool, SlowerSong);
    DECLARE_BSML_PROPERTY(bool, EasyMode);
    DECLARE_BSML_PROPERTY(bool, SameColor);

    DECLARE_BSML_PROPERTY(bool, OneLife);
    DECLARE_BSML_PROPERTY(bool, FasterSong);
    DECLARE_BSML_PROPERTY(bool, ProMode);

    DECLARE_BSML_PROPERTY(bool, OneHp);
    DECLARE_BSML_PROPERTY(bool, SuperFastSong);
    DECLARE_BSML_PROPERTY(bool, Hidden);
    
    DECLARE_BSML_PROPERTY(bool, NoArrows);
    DECLARE_BSML_PROPERTY(bool, GhostNotes);

    DECLARE_BSML_PROPERTY(bool, NoBombs);
    DECLARE_BSML_PROPERTY(bool, DisappearingArrows);

    DECLARE_BSML_PROPERTY(bool, NoWalls);
    DECLARE_BSML_PROPERTY(bool, SmallNotes);

    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, MultiplierValue);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, MaxRank);

    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, OneLifeToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, OneHpToggle);

    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, EasyModeToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, ProModeToggle);

    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, HiddenToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, GhostNotesToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, DisappearingArrowsToggle);

    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, SlowerSongToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, FasterSongToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, SuperFastSongToggle);

    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, NoArrowsToggle);


    public:
    void Save(bool config = true);
)