#pragma once
#include "framework/App.h"
namespace paperos {
class SystemMonitor : public IApp {
public:
    const char* id() const override { return "system"; }
    const char* title() const override { return "System"; }
    void enter(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    void draw(AppContext&);
};
}
