#pragma once
#include "framework/App.h"
#include <vector>
#include <string>
namespace paperos {
class WifiAnalyzer : public IApp {
public:
    const char* id() const override { return "wifi"; }
    const char* title() const override { return "Wi-Fi scan"; }
    void enter(AppContext&) override;
    void leave(AppContext&) override;
    void tick(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    struct Network { std::string name; int rssi; int channel; bool secured; };
    std::vector<Network> networks_;
    bool scanning_ = false, failed_ = false;
    void scan(AppContext&);
    void draw(AppContext&);
};
}
