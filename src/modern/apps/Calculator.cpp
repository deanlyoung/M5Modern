#include "Calculator.h"
#include "modern/ModernDisplay.h"
namespace paperos {
static constexpr char keys[4][4] = {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','.','+'}};
void Calculator::enter(AppContext& ctx) { draw(ctx); }
void Calculator::draw(AppContext& ctx) {
    auto& d = ctx.display; d.heading("Calculator");
    auto& c = d.canvas(); c.setTextSize(4); c.drawString(logic_.display().c_str(), 24, 130);
    for (int r=0;r<4;++r) for(int col=0;col<4;++col) {
        char label[] = {keys[r][col], '\0'};
        d.button(24 + col*124, 230 + r*120, 112, 105, label);
    }
    d.button(24, 725, 484, 95, "=", true); d.present();
}
void Calculator::onInput(const InputEvent& e, AppContext& ctx) {
    if (e.kind != InputEvent::Kind::TouchDown) return;
    if (e.x >= 24 && e.x < 520 && e.y >= 230 && e.y < 710) {
        int col=(e.x-24)/124, row=(e.y-230)/120;
        if ((e.x-24)%124 >= 112 || (e.y-230)%120 >= 105) return;
        logic_.press(keys[row][col]); draw(ctx);
    } else if (Rect{24,725,484,95}.contains({e.x,e.y})) { logic_.press('='); draw(ctx); }
}
}
