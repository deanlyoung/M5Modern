#pragma once
#include "framework/App.h"
namespace paperos {
class Clock : public IApp {
public:
    const char* id() const override { return "clock"; }
    const char* title() const override { return "Clock"; }
    void enter(AppContext&) override;
    void tick(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    int last_minute_ = -1;
    uint32_t last_check_ = 0;
    void draw(AppContext&);
};
}
