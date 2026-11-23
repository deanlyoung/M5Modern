#pragma once
#include "framework/App.h"
namespace paperos {
class ModernLauncher : public IApp {
public:
    const char* id() const override { return "launcher"; }
    const char* title() const override { return "Home"; }
    void enter(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    unsigned page_ = 0;
    void draw(AppContext&);
};
}
