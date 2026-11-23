// Standalone migration probe. This is not yet the M5Modern application.
#include <M5Unified.h>

static M5Canvas canvas(&M5.Display);

void setup() {
    Serial.begin(115200);
    M5.begin(M5.config());
    M5.Display.setRotation(0);
    M5.Display.setAutoDisplay(false);
    canvas.setColorDepth(4);
    if (!canvas.createSprite(M5.Display.width(), M5.Display.height())) {
        Serial.println("M5Modern probe: framebuffer allocation failed");
        return;
    }
    canvas.fillSprite(TFT_WHITE);
    canvas.setTextColor(TFT_BLACK, TFT_WHITE);
    canvas.setTextSize(3);
    canvas.drawString("M5Modern hardware probe", 24, 50);
    canvas.setTextSize(2);
    canvas.drawString("Touch anywhere to test input.", 24, 120);
    canvas.pushSprite(0, 0);
    M5.Display.display();
    Serial.printf("M5Modern probe: %dx%d battery %d%%\n", M5.Display.width(),
                  M5.Display.height(), M5.Power.getBatteryLevel());
}

void loop() {
    M5.update();
    const auto touch = M5.Touch.getDetail();
    if (touch.wasPressed()) Serial.printf("touch %d,%d\n", touch.x, touch.y);
    delay(20);
}
