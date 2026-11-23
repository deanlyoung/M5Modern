#pragma once
#include "framework/App.h"
#include "CalculatorLogic.h"
namespace paperos {
class Calculator : public IApp {
public:
    const char* id() const override { return "calculator"; }
    const char* title() const override { return "Calculator"; }
    void enter(AppContext&) override;
    void onInput(const InputEvent&, AppContext&) override;
private:
    CalculatorLogic logic_;
    void draw(AppContext&);
};
}
