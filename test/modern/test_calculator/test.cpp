#include <unity.h>
#include "modern/apps/CalculatorLogic.h"
using paperos::CalculatorLogic;
void setUp() {} void tearDown() {}
void test_arithmetic_and_chaining() {
    CalculatorLogic c;
    for (char k : std::string("12+3*2=")) c.press(k);
    TEST_ASSERT_EQUAL_STRING("30", c.display().c_str());
}
void test_decimal_and_zero_division() {
    CalculatorLogic c;
    for (char k : std::string("1.5/0=")) c.press(k);
    TEST_ASSERT_EQUAL_STRING("Error", c.display().c_str());
    c.press('2'); TEST_ASSERT_EQUAL_STRING("2", c.display().c_str());
    c.press('C'); TEST_ASSERT_EQUAL_STRING("0", c.display().c_str());
}
int main() { UNITY_BEGIN(); RUN_TEST(test_arithmetic_and_chaining); RUN_TEST(test_decimal_and_zero_division); return UNITY_END(); }
