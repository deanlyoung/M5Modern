#include "Launcher.h"
#include "modern/ModernDisplay.h"
#include "framework/AppSwitcher.h"
#include <vector>
namespace paperos {
static std::vector<std::string> apps(AppContext& ctx) {
    std::vector<std::string> result;
    for (const auto& id : ctx.switcher.registeredIds()) if (id != "launcher") result.push_back(id);
    return result;
}
void ModernLauncher::enter(AppContext& ctx) { page_ = 0; draw(ctx); }
void ModernLauncher::draw(AppContext& ctx) {
    auto& d = ctx.display;
    d.heading("M5Modern", false);
    auto ids = apps(ctx);
    for (unsigned i = 0; i < 6 && page_ * 6 + i < ids.size(); ++i) {
        const auto name = ctx.switcher.titleOf(ids[page_ * 6 + i]);
        d.button(24 + (i % 2) * 252, 112 + (i / 2) * 155, 240, 130, name.c_str());
    }
    if (page_ > 0) d.button(24, 850, 230, 65, "PREVIOUS");
    if ((page_ + 1) * 6 < ids.size()) d.button(286, 850, 230, 65, "NEXT");
    d.present();
}
void ModernLauncher::onInput(const InputEvent& e, AppContext& ctx) {
    if (e.kind != InputEvent::Kind::TouchDown) return;
    auto ids = apps(ctx);
    if (e.y >= 850 && e.y < 915) {
        if (e.x < 254 && page_ > 0) { --page_; draw(ctx); }
        else if (e.x >= 286 && (page_ + 1) * 6 < ids.size()) { ++page_; draw(ctx); }
        return;
    }
    for (unsigned i = 0; i < 6 && page_ * 6 + i < ids.size(); ++i) {
        Rect r{static_cast<int16_t>(24 + (i % 2) * 252), static_cast<int16_t>(112 + (i / 2) * 155), 240, 130};
        if (r.contains({e.x, e.y})) { ctx.switcher.requestSwitch(ids[page_ * 6 + i]); return; }
    }
}
}
