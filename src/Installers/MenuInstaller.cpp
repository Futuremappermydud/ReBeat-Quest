#include "Installers/MenuInstaller.hpp"

#include "Types/MenuView.hpp"
#include "Types/ModifiersView.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(ReBeat, MenuInstaller);

namespace ReBeat
{
    void MenuInstaller::InstallBindings()
    {
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<MenuView*>()->AsSingle();
        container->BindInterfacesAndSelfTo<ModifiersView*>()->AsSingle();
    }
}