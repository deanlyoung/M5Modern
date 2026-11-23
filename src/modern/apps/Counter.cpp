#include "Counter.h"
#include "modern/ModernDisplay.h"
#include "framework/AppSwitcher.h"
#include <Preferences.h>
#include <cstdio>
namespace paperos {
void Counter::enter(AppContext& ctx) {
    Preferences p;
    if (p.begin("m5counter", true)) { count_ = p.getUInt("count", 0); p.end(); }
    draw(ctx);
}
void Counter::save() {
    Preferences p;
    if (p.begin("m5counter", false)) { p.putUInt("count", count_); p.end(); }
}
void Counter::draw(AppContext& ctx) {
    auto& d = ctx.display; d.heading("Counter");
    auto& c = d.canvas(); c.setTextSize(6);
    char number[16]; snprintf(number, sizeof(number), "%lu", static_cast<unsigned long>(count_));
    c.drawString(number, 40, 200);
    d.button(24, 500, 492, 120, "TAP TO COUNT", true);
    d.button(24, 650, 492, 100, "RESET");
    c.setTextSize(2); c.drawString("Saved on device", 24, 810);
    d.present();
}
void Counter::onInput(const InputEvent& e, AppContext& ctx) {
    if (e.kind != InputEvent::Kind::TouchDown || e.x < 24 || e.x >= 516) return;
    if (e.y >= 500 && e.y < 620) { if (count_ != UINT32_MAX) ++count_; }
    else if (e.y >= 650 && e.y < 750) count_ = 0;
    else return;
    save(); draw(ctx);
}
}
