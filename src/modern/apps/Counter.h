#pragma once
#include "framework/App.h"
#include <stdint.h>
namespace paperos {
class Counter : public IApp {
public:
    const char* id() const override { return "counter"; }
    const char* title() const override { return "Counter"; }
    void enter(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    uint32_t count_ = 0;
    void draw(AppContext&);
    void save();
};
}
