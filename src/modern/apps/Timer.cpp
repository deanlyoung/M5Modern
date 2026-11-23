#include "Timer.h"
#include "modern/ModernDisplay.h"
#include "TimerMath.h"
#include <Arduino.h>
#include <cstdio>
namespace paperos {
void Timer::enter(AppContext& ctx) { draw(ctx); }
void Timer::drawCountdown(AppContext& ctx, uint32_t seconds, bool partial) {
    auto& d = ctx.display;
    auto& c = d.canvas();
    c.fillRect(24, 180, 360, 64, TFT_WHITE);
    c.setTextColor(TFT_BLACK, TFT_WHITE);
    c.setTextDatum(top_left);
    c.setTextSize(6);
    char text[24];
    snprintf(text, sizeof(text), "%02lu:%02lu", static_cast<unsigned long>(seconds / 60), static_cast<unsigned long>(seconds % 60));
    c.drawString(text, 24, 180);
    displayed_seconds_ = seconds;
    if (partial) d.presentRegion(24, 180, 360, 64, seconds % 60 == 0);
}
void Timer::draw(AppContext& ctx) {
    auto& d = ctx.display; d.heading("Timer");
    auto& c = d.canvas(); c.setTextSize(2);
    const uint32_t seconds = finished_ ? 0 : (running_ ? remainingTimerSeconds(duration_min_ * 60, started_ms_, millis()) : duration_min_ * 60);
    drawCountdown(ctx, seconds, false);
    c.setTextSize(2); c.drawString(finished_ ? "Time is up" : "Runs while this screen is open", 24, 285);
    if (!running_) { d.button(24, 390, 230, 90, "- 1 MIN"); d.button(286, 390, 230, 90, "+ 1 MIN"); }
    d.button(24, 520, 492, 100, running_ ? "STOP" : "START", true);
    d.present();
}
void Timer::tick(AppContext& ctx) {
    if (!running_) return;
    uint32_t seconds = remainingTimerSeconds(duration_min_ * 60, started_ms_, millis());
    if (seconds == 0) { running_ = false; finished_ = true; draw(ctx); return; }
    if (displayed_seconds_ != seconds) drawCountdown(ctx, seconds, true);
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
