#include "SystemMonitor.h"
#include "modern/ModernDisplay.h"
#include <Arduino.h>
#include <cstdio>
namespace paperos {
void SystemMonitor::enter(AppContext& ctx) { draw(ctx); }
void SystemMonitor::draw(AppContext& ctx) {
    auto& d = ctx.display; d.heading("System monitor");
    auto& c = d.canvas(); c.setTextSize(2);
    char line[64];
    snprintf(line, sizeof(line), "Battery: %d%%", M5.Power.getBatteryLevel()); c.drawString(line, 24, 130);
    snprintf(line, sizeof(line), "Free heap: %lu KB", static_cast<unsigned long>(ESP.getFreeHeap()/1024)); c.drawString(line, 24, 190);
    snprintf(line, sizeof(line), "Free PSRAM: %lu KB", static_cast<unsigned long>(ESP.getFreePsram()/1024)); c.drawString(line, 24, 250);
    snprintf(line, sizeof(line), "Uptime: %lu min", static_cast<unsigned long>(millis()/60000)); c.drawString(line, 24, 310);
    d.button(24, 500, 492, 90, "REFRESH"); d.present();
}
void SystemMonitor::onInput(const InputEvent& e, AppContext& ctx) {
    if (e.kind == InputEvent::Kind::TouchDown && Rect{24,500,492,90}.contains({e.x,e.y})) draw(ctx);
}
}
