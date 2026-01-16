#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static inline uint8_t floatToByte(float num) {
        int n = static_cast<int>(std::floor(num));
        n = std::clamp(n, 0, 100);
        return static_cast<uint8_t>(n);
}

class $modify(rnPlayLayer, PlayLayer) {
        static void onModify(auto& self) {
                if (!self.setHookPriorityAfterPost(
                        "PlayLayer::updateProgressbar",
                        "thesillydoggo.qolmod"
                )) {
                        log::warn("byte percent failed to set hook priority for PlayLayer::updateProgressbar.");
                }
        }

        void updateProgressbar() {
                PlayLayer::updateProgressbar();
                if (Mod::get()->getSettingValue<bool>("enabled")) {
                        uint8_t b = floatToByte(this->getCurrentPercent());
                        m_percentageLabel->setString(
                                (std::to_string(b) + "%").c_str()
                        );
                }
        }
};
