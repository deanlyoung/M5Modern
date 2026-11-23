#include <unity.h>
#include "framework/AppSwitcher.h"
namespace paperos { class ModernDisplay {}; }
using namespace paperos;
static int entered = 0, left = 0, destroyed = 0;
class DemoApp : public IApp {
public:
    explicit DemoApp(const char* name) : name_(name) {}
    ~DemoApp() override { ++destroyed; }
    const char* id() const override { return name_; }
    const char* title() const override { return name_; }
    void enter(AppContext&) override { ++entered; }
    void leave(AppContext&) override { ++left; }
private:
    const char* name_;
};
void setUp() { entered = left = destroyed = 0; }
void tearDown() {}
void test_deferred_switch_calls_lifecycle_in_order() {
    ModernDisplay display;
    AppSwitcher s;
    AppContext ctx{display, s};
    s.setContext(&ctx);
    s.registerApp("a", [] { return new DemoApp("a"); });
    s.registerApp("b", [] { return new DemoApp("b"); });
    s.switchTo("a");
    TEST_ASSERT_EQUAL(1, entered);
    s.requestSwitch("b");
    TEST_ASSERT_EQUAL_STRING("a", s.current()->id());
    TEST_ASSERT_EQUAL(0, left);
    s.applyPending();
    TEST_ASSERT_EQUAL_STRING("b", s.current()->id());
    TEST_ASSERT_EQUAL(2, entered);
    TEST_ASSERT_EQUAL(1, left);
    TEST_ASSERT_EQUAL(1, destroyed);
}
void test_unknown_app_does_not_replace_active_app() {
    ModernDisplay display;
    AppSwitcher s; AppContext ctx{display, s}; s.setContext(&ctx);
    s.registerApp("a", [] { return new DemoApp("a"); });
    s.switchTo("a"); s.switchTo("missing");
    TEST_ASSERT_EQUAL_STRING("a", s.current()->id());
    TEST_ASSERT_EQUAL(0, left);
}
int main() {
    UNITY_BEGIN();
    RUN_TEST(test_deferred_switch_calls_lifecycle_in_order);
    RUN_TEST(test_unknown_app_does_not_replace_active_app);
    return UNITY_END();
}
