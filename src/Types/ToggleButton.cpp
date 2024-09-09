#include "Types/ToggleButton.hpp"
#include "bsml/shared/BSML-Lite/Creation/Misc.hpp"
#include "bsml/shared/BSML/Components/ClickableImage.hpp"
#include "rebeatConfig.hpp"

#include "hooks.hpp"

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSegmentedControlController.hpp"

DEFINE_TYPE(ReBeat, ToggleButton);

namespace ReBeat
{
    void ToggleButton::Awake() {
        image = GetComponent<BSML::ClickableImage*>();
        image->onClick.addCallback(&ToggleButton::Click, this);

        hoverHint = BSML::Lite::AddHoverHint(this, "Toggle ReBeat! On/Off");
    }

    void ToggleButton::Click() {
        if(!ReBeat::Hooks::isCustomLevel) return;
        
        auto view = transform->parent->parent->GetComponent<GlobalNamespace::StandardLevelDetailViewController*>();
        getReBeatConfig().Enabled.SetValue(!getReBeatConfig().Enabled.GetValue());
        ReBeat::Hooks::loadMods = !getReBeatConfig().Enabled.GetValue();
        ReBeat::Hooks::gsvcInstance->RefreshContent();

        view->____standardLevelDetailView->SetContent(view->_beatmapLevel, view->_allowedBeatmapDifficultyMask,
				view->_notAllowedCharacteristics, view->_playerDataModel->playerData->lastSelectedBeatmapDifficulty,
				view->_playerDataModel->playerData->lastSelectedBeatmapCharacteristic, view->_playerDataModel->playerData);

        auto charController = view->_standardLevelDetailView->_beatmapCharacteristicSegmentedControlController;
		view->_standardLevelDetailView->HandleBeatmapCharacteristicSegmentedControlControllerDidSelectBeatmapCharacteristic(charController, charController->selectedBeatmapCharacteristic);
    }

    void ToggleButton::Update() {
        if (ReBeat::Hooks::isCustomLevel)
        {
            image->highlightColor = UnityEngine::Color(0.60f, 0.80f, 1.0f, 1.0f);
            image->defaultColor = getReBeatConfig().Enabled.GetValue() ? image->highlightColor : UnityEngine::Color::get_white();
            hoverHint->text = "Toggle ReBeat! On/Off";
            image->UpdateHighlight();
        }
        else {
            image->highlightColor = UnityEngine::Color(0.4f, 0.4f, 0.4f, 0.8f);
            image->defaultColor = UnityEngine::Color(0.4f, 0.4f, 0.4f, 0.8f);
            hoverHint->text = "ReBeat is only available on custom levels!";
            image->UpdateHighlight();
        }
    }
}