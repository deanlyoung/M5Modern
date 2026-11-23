#include "WifiAnalyzer.h"
#include "modern/ModernDisplay.h"
#include <WiFi.h>
#include <cstdio>
namespace paperos {
void WifiAnalyzer::enter(AppContext& ctx) { WiFi.mode(WIFI_STA); scan(ctx); }
void WifiAnalyzer::leave(AppContext&) { WiFi.scanDelete(); WiFi.mode(WIFI_OFF); }
void WifiAnalyzer::scan(AppContext& ctx) {
    networks_.clear(); failed_ = false; WiFi.scanDelete();
    scanning_ = WiFi.scanNetworks(true, true) == WIFI_SCAN_RUNNING;
    if (!scanning_) failed_ = true;
    draw(ctx);
}
void WifiAnalyzer::tick(AppContext& ctx) {
    if (!scanning_) return;
    int count = WiFi.scanComplete();
    if (count == WIFI_SCAN_RUNNING) return;
    scanning_ = false;
    if (count < 0) failed_ = true;
    else {
        for (int i=0; i<count && i<8; ++i) {
            String name = WiFi.SSID(i); if (name.length() > 24) name = name.substring(0,24);
            networks_.push_back({name.length() ? std::string(name.c_str()) : std::string("(hidden)"), WiFi.RSSI(i), WiFi.channel(i), WiFi.encryptionType(i) != WIFI_AUTH_OPEN});
        }
    }
    WiFi.scanDelete(); draw(ctx);
}
void WifiAnalyzer::draw(AppContext& ctx) {
    auto& d=ctx.display; d.heading("Wi-Fi scan"); auto& c=d.canvas(); c.setTextSize(2);
    if (scanning_) c.drawString("Scanning...",24,120);
    else if (failed_) c.drawString("Scan failed",24,120);
    else if (networks_.empty()) c.drawString("No networks found",24,120);
    else {
        int y=115;
        for (const auto& n : networks_) {
            c.drawString(n.name.c_str(),24,y); char info[64];
            snprintf(info,sizeof(info),"%d dBm   ch %d   %s",n.rssi,n.channel,n.secured?"secured":"open");
            c.drawString(info,24,y+28); y+=75;
        }
    }
    if (!scanning_) d.button(24,800,492,80,"SCAN AGAIN");
    d.present();
}
void WifiAnalyzer::onInput(const InputEvent& e, AppContext& ctx) {
    if (!scanning_ && e.kind==InputEvent::Kind::TouchDown && Rect{24,800,492,80}.contains({e.x,e.y})) scan(ctx);
}
}
