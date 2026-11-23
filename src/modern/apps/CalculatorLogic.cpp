#include "CalculatorLogic.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
namespace paperos {
void CalculatorLogic::press(char key) {
    if (key == 'C') { display_ = "0"; left_ = 0; op_ = 0; replace_ = false; return; }
    if ((key >= '0' && key <= '9') || key == '.') {
        if (replace_ || display_ == "Error") { display_ = "0"; replace_ = false; }
        if (key == '.') { if (display_.find('.') == std::string::npos) display_ += '.'; }
        else if (display_ == "0") display_ = std::string(1, key);
        else if (display_.size() < 12) display_ += key;
        return;
    }
    if (display_ == "Error") return;
    if (key == '+' || key == '-' || key == '*' || key == '/') {
        if (op_ && !replace_ && !calculate()) return;
        left_ = strtod(display_.c_str(), nullptr); op_ = key; replace_ = true;
    } else if (key == '=' && op_) { if (calculate()) { op_ = 0; replace_ = true; } }
}
bool CalculatorLogic::calculate() {
    double right = strtod(display_.c_str(), nullptr), result = 0;
    switch (op_) {
        case '+': result = left_ + right; break;
        case '-': result = left_ - right; break;
        case '*': result = left_ * right; break;
        case '/': if (right == 0) { display_ = "Error"; op_ = 0; return false; } result = left_ / right; break;
        default: return false;
    }
    if (!std::isfinite(result)) { display_ = "Error"; op_ = 0; return false; }
    char text[32]; snprintf(text, sizeof(text), "%.9g", result); display_ = text;
    return true;
}
}
