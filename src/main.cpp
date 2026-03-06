#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

std::string floatToRoman(float num) {
    std::string res;
    float remaining = num;
    if (remaining <= 0.f) { res = "N"; return res; }
    if (remaining > 100.f) { return "C"; }
    const int vals[] = {100, 90, 50, 40, 10, 9, 5, 4, 1};
    const std::string syms[] = {"C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    res.clear();
    int whole = static_cast<int>(std::floor(remaining));
    for (int i = 0; i < 9; ++i) {
        while (whole >= vals[i]) {
            whole -= vals[i];
            res += syms[i];
        }
    }
    float frac = remaining - static_cast<float>(whole);
    if (Mod::get()->getSettingValue<bool>("useFractions")) {
	    if (frac > 0.f) {
	        int unciae = static_cast<int>(std::round(frac * 12.f));
	        if (unciae == 12)
	            whole += 1;
	            res += "I";
	            unciae = 0;
	        }
	        if (unciae > 0) {
	            std::string dots = "";
	            if (unciae == 6) {
	                res += "S";
	            } else if (unciae > 6) {
	                res += "S";
	                unciae -= 6;
	            }
	            for (int d = 0; d < unciae; ++d) {
	                dots += "•";
	            }
	            res += dots;
	        }
	    }
	}    
    return res;
}
// burgers taste good
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