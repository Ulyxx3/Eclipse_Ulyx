#include <modules/config/config.hpp>
#include <modules/gui/gui.hpp>
#include <modules/gui/components/toggle.hpp>
#include <modules/hack/hack.hpp>

#include <Geode/modify/LevelEditorLayer.hpp>

namespace eclipse::hacks::Creator {
    class $hack(ResetPercentOnSave) {
        void init() override {
            auto tab = gui::MenuTab::find("tab.creator");
            tab->addToggle("creator.resetpercentonsave")->handleKeybinds()->setDescription();
        }

        [[nodiscard]] const char* getId() const override { return "Reset Percent on Save"; }
    };

    REGISTER_HACK(ResetPercentOnSave)

    class $modify(ResetPercentLELHook, LevelEditorLayer) {
        ADD_HOOKS_DELEGATE("creator.resetpercentonsave")
        bool saveLevel() {
            if (m_level && m_level->m_levelType == GJLevelType::Editor) m_level->m_normalPercent = 0;
            return LevelEditorLayer::saveLevel();
        }
    };
}
