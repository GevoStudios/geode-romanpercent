#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

std::string floatToRoman(float num) {
    std::string res;
    int n = static_cast<int>(std::floor(num));
    if (n == 0) {
        res = "0";
        return res;
    }
    // i thought over whether id need this or not for a while but its better to be safe ig
    if (n < 0 || n > 100) {
        res.clear();
        return res;
    }
    int vals[] = {100, 90, 50, 40, 10, 9, 5, 4, 1};
    std::string syms[] = {"C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    res.clear();
    for (int i = 0; i < 9; ++i) {
        while (n >= vals[i]) {
            n -= vals[i];
            res += syms[i];
        }
    }
    return res;
}

class $modify(rnPlayLayer, PlayLayer) {
    static void onModify(auto& self) {
        if (!self.setHookPriorityAfterPost("PlayLayer::updateProgressbar", "thesillydoggo.qolmod")) {
            log::warn("roman percent failed to set hook priority for PlayLayer::updateProgressbar. qolmod might break roman percent.");
        }
    }
    
    void updateProgressbar() {
        PlayLayer::updateProgressbar();
        if (Mod::get()->getSettingValue<bool>("enabled")) {
            float ret = this->getCurrentPercent();
            m_percentageLabel->setString((floatToRoman(ret) + std::string("%")).c_str());
        }
    }
};