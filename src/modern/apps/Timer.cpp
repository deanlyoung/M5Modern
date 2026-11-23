#include "Timer.h"
#include "modern/ModernDisplay.h"
#include <Arduino.h>
#include <cstdio>
namespace paperos {
void Timer::enter(AppContext& ctx) { draw(ctx); }
void Timer::draw(AppContext& ctx) {
    auto& d = ctx.display; d.heading("Timer");
    auto& c = d.canvas(); c.setTextSize(2);
    const uint32_t elapsed = running_ ? (millis() - started_ms_) / 1000 : 0;
    const uint32_t seconds = finished_ ? 0 : (running_ && elapsed < duration_min_ * 60 ? duration_min_ * 60 - elapsed : duration_min_ * 60);
    char text[32]; snprintf(text, sizeof(text), "%lu min", static_cast<unsigned long>((seconds + 59) / 60));
    c.setTextSize(6); c.drawString(text, 24, 180);
    c.setTextSize(2); c.drawString(finished_ ? "Time is up" : "Runs while this screen is open", 24, 285);
    if (!running_) { d.button(24, 390, 230, 90, "- 1 MIN"); d.button(286, 390, 230, 90, "+ 1 MIN"); }
    d.button(24, 520, 492, 100, running_ ? "STOP" : "START", true);
    d.present();
}
void Timer::tick(AppContext& ctx) {
    if (!running_) return;
    uint32_t elapsed = (millis() - started_ms_) / 1000;
    if (elapsed >= duration_min_ * 60) { running_ = false; finished_ = true; draw(ctx); return; }
    // E-paper needs only a minute-level update while counting down.
    uint32_t minute = (duration_min_ * 60 - elapsed + 59) / 60;
    if (displayed_seconds_ != minute) { displayed_seconds_ = minute; draw(ctx); }
}
void Timer::onInput(const InputEvent& e, AppContext& ctx) {
    if (e.kind != InputEvent::Kind::TouchDown) return;
    if (!running_ && e.y >= 390 && e.y < 480) {
        if (e.x >= 24 && e.x < 254 && duration_min_ > 1) --duration_min_;
        else if (e.x >= 286 && e.x < 516 && duration_min_ < 180) ++duration_min_;
        else return;
        finished_ = false; draw(ctx);
    } else if (e.x >= 24 && e.x < 516 && e.y >= 520 && e.y < 620) {
        running_ = !running_; finished_ = false;
        if (running_) { started_ms_ = millis(); displayed_seconds_ = UINT32_MAX; }
        draw(ctx);
    }
}
}
