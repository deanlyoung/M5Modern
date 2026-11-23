#include "Clock.h"
#include "modern/ModernDisplay.h"
#include <Arduino.h>
#include <cstdio>
namespace paperos {
void Clock::enter(AppContext& ctx) { draw(ctx); }
void Clock::draw(AppContext& ctx) {
    auto& d=ctx.display; d.heading("Clock"); auto& c=d.canvas();
    m5::rtc_time_t t;
    bool valid=M5.Rtc.getTime(&t) && t.isValid();
    char text[16];
    if (valid) { snprintf(text,sizeof(text),"%02d:%02d",t.hours,t.minutes); last_minute_=t.hours*60+t.minutes; }
    else { snprintf(text,sizeof(text),"--:--"); last_minute_=-1; }
    c.setTextSize(6); c.drawString(text,24,170);
    c.setTextSize(2); c.drawString("Device clock; not network-synced",24,275);
    c.drawString("Tap to set the local time",24,315);
    d.button(24,420,230,90,"HOUR +"); d.button(286,420,230,90,"MINUTE +");
    d.present();
}
void Clock::tick(AppContext& ctx) {
    if (millis()-last_check_<10000) return;
    last_check_=millis(); m5::rtc_time_t t;
    if (M5.Rtc.getTime(&t) && t.isValid() && t.hours*60+t.minutes!=last_minute_) draw(ctx);
}
void Clock::onInput(const InputEvent& e, AppContext& ctx) {
    if (e.kind!=InputEvent::Kind::TouchDown || e.y<420 || e.y>=510) return;
    bool hour=e.x>=24 && e.x<254, minute=e.x>=286 && e.x<516;
    if (!hour && !minute) return;
    m5::rtc_time_t t;
    if (!M5.Rtc.getTime(&t) || !t.isValid()) t=m5::rtc_time_t(12,0,0);
    if (hour) t.hours=(t.hours+1)%24;
    if (minute) t.minutes=(t.minutes+1)%60;
    t.seconds=0;
    if (M5.Rtc.setTime(t)) draw(ctx);
}
}
