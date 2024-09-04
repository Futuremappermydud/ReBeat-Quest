#include "Types/ToggleButton.hpp"
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
    }

    void ToggleButton::Click() {
        if(!ReBeat::Hooks::isCustomLevel) return;
        
        auto view = transform->parent->parent->GetComponent<GlobalNamespace::StandardLevelDetailViewController*>();
        getReBeatConfig().Enabled.SetValue(!getReBeatConfig().Enabled.GetValue());

        view->____standardLevelDetailView->SetContent(view->_beatmapLevel, view->_allowedBeatmapDifficultyMask,
				view->_notAllowedCharacteristics, view->_playerDataModel->playerData->lastSelectedBeatmapDifficulty,
				view->_playerDataModel->playerData->lastSelectedBeatmapCharacteristic, view->_playerDataModel->playerData);

        auto charController = view->_standardLevelDetailView->_beatmapCharacteristicSegmentedControlController;
		view->_standardLevelDetailView->HandleBeatmapCharacteristicSegmentedControlControllerDidSelectBeatmapCharacteristic(charController, charController->selectedBeatmapCharacteristic);
    }

    void ToggleButton::Update() {
        image->enabled = ReBeat::Hooks::isCustomLevel;
        image->defaultColor = getReBeatConfig().Enabled.GetValue() ? image->highlightColor : UnityEngine::Color::get_white();
    }
}