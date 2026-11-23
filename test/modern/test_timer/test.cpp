#include <unity.h>
#include "modern/apps/TimerMath.h"
using paperos::remainingTimerSeconds;
void setUp() {} void tearDown() {}
void test_counts_down_on_second_boundaries() {
    TEST_ASSERT_EQUAL_UINT32(300, remainingTimerSeconds(300, 1000, 1000));
    TEST_ASSERT_EQUAL_UINT32(300, remainingTimerSeconds(300, 1000, 1999));
    TEST_ASSERT_EQUAL_UINT32(299, remainingTimerSeconds(300, 1000, 2000));
    TEST_ASSERT_EQUAL_UINT32(1, remainingTimerSeconds(300, 1000, 300999));
    TEST_ASSERT_EQUAL_UINT32(0, remainingTimerSeconds(300, 1000, 301000));
    TEST_ASSERT_EQUAL_UINT32(0, remainingTimerSeconds(300, 1000, 310000));
}
void test_millis_wrap() {
    TEST_ASSERT_EQUAL_UINT32(4, remainingTimerSeconds(5, 0xffffff00U, 0x000002e8U));
}
int main() { UNITY_BEGIN(); RUN_TEST(test_counts_down_on_second_boundaries); RUN_TEST(test_millis_wrap); return UNITY_END(); }
