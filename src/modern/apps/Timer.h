#pragma once
#include "framework/App.h"
#include <stdint.h>
namespace paperos {
class Timer : public IApp {
public:
    const char* id() const override { return "timer"; }
    const char* title() const override { return "Timer"; }
    void enter(AppContext&) override;
    void tick(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    uint32_t duration_min_ = 5;
    uint32_t started_ms_ = 0;
    uint32_t displayed_seconds_ = UINT32_MAX;
    bool running_ = false, finished_ = false;
    void draw(AppContext&);
};
}
