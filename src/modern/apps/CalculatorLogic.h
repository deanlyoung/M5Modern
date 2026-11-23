#pragma once
#include <string>
namespace paperos {
class CalculatorLogic {
public:
    const std::string& display() const { return display_; }
    void press(char key);
private:
    std::string display_ = "0";
    double left_ = 0;
    char op_ = 0;
    bool replace_ = false;
    bool calculate();
};
}
