#include "Types/MenuView.hpp"

#include "assets.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSMLDataCache.hpp"
#include "rebeatConfig.hpp"

DEFINE_TYPE(ReBeat, MenuView);

namespace ReBeat
{
    void MenuView::Initialize() {
        BSML::Register::RegisterGameplaySetupTab("ReBeat", MOD_ID "_MenuView", this);
    }

    void MenuView::Dispose() {
        BSML::Register::UnRegisterGameplaySetupTab("ReBeat");
    }

    void MenuView::PostParse() {

    }
}