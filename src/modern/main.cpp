#include <M5Unified.h>
#include "modern/ModernDisplay.h"
#include "modern/apps/Launcher.h"
#include "modern/apps/Counter.h"
#include "modern/apps/SystemMonitor.h"
#include "modern/apps/Timer.h"
#include "modern/apps/Calculator.h"
#include "modern/apps/Clock.h"
#include "modern/apps/WifiAnalyzer.h"
#include "framework/AppSwitcher.h"

static paperos::ModernDisplay display;
static paperos::AppSwitcher switcher;
static paperos::AppContext context{display, switcher};
static bool ready = false;
static uint32_t last_touch_ms = 0;

void setup() {
    Serial.begin(115200);
    M5.begin(M5.config());
    if (!display.begin()) { Serial.println("M5Modern: display allocation failed"); return; }
    switcher.registerApp("launcher", [] { return new paperos::ModernLauncher(); });
    switcher.registerApp("counter", [] { return new paperos::Counter(); });
    switcher.registerApp("system", [] { return new paperos::SystemMonitor(); });
    switcher.registerApp("timer", [] { return new paperos::Timer(); });
    switcher.registerApp("calculator", [] { return new paperos::Calculator(); });
    switcher.registerApp("clock", [] { return new paperos::Clock(); });
    switcher.registerApp("wifi", [] { return new paperos::WifiAnalyzer(); });
    switcher.setContext(&context);
    switcher.switchTo("launcher");
    ready = true;
    Serial.printf("M5Modern shell ready: %dx%d\n", M5.Display.width(), M5.Display.height());
}
void loop() {
    M5.update();
    if (!ready) { delay(100); return; }
    auto t = M5.Touch.getDetail();
    const uint32_t now = millis();
    if (t.wasPressed() && (last_touch_ms == 0 || now - last_touch_ms >= 250)) {
        last_touch_ms = now;
        Serial.printf("Touch: %d,%d\n", t.x, t.y);
        if (switcher.current() && switcher.current()->id() != std::string("launcher") && t.x >= 405 && t.y < 80) {
            switcher.requestSwitch("launcher");
        } else if (switcher.current()) {
            paperos::InputEvent e{}; e.kind = paperos::InputEvent::Kind::TouchDown; e.x = t.x; e.y = t.y; e.now_ms = now;
            switcher.current()->onInput(e, context);
        }
    }
    if (switcher.current()) switcher.current()->tick(context);
    if (switcher.hasPending()) switcher.applyPending();
    delay(20);
}
