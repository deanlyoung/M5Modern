#include "ModernDisplay.h"

namespace paperos {
bool ModernDisplay::begin() {
    M5.Display.setRotation(0);
    M5.Display.setAutoDisplay(false);
    canvas_.setColorDepth(4);
    return canvas_.createSprite(M5.Display.width(), M5.Display.height()) != nullptr;
}
void ModernDisplay::present() {
    // A periodic quality refresh helps clear e-paper ghosting.
    M5.Display.setEpdMode((refreshes_++ % 20 == 0) ? m5gfx::epd_quality : m5gfx::epd_text);
    canvas_.pushSprite(0, 0);
    M5.Display.display();
    M5.Display.waitDisplay();
}
void ModernDisplay::heading(const char* title, bool showBack) {
    canvas_.fillSprite(TFT_WHITE);
    canvas_.setTextDatum(top_left);
    canvas_.setTextColor(TFT_BLACK, TFT_WHITE);
    canvas_.setTextSize(3);
    canvas_.drawString(title, 24, 30);
    if (showBack) {
        canvas_.setTextSize(2);
        canvas_.drawString("< HOME", 415, 36);
    }
    canvas_.drawLine(24, 80, 516, 80, TFT_BLACK);
}
void ModernDisplay::button(int x, int y, int w, int h, const char* label, bool filled) {
    if (filled) canvas_.fillRoundRect(x, y, w, h, 10, TFT_BLACK);
    else canvas_.drawRoundRect(x, y, w, h, 10, TFT_BLACK);
    canvas_.setTextDatum(middle_center);
    canvas_.setTextSize(2);
    canvas_.setTextColor(filled ? TFT_WHITE : TFT_BLACK, filled ? TFT_BLACK : TFT_WHITE);
    canvas_.drawString(label, x + w / 2, y + h / 2);
    canvas_.setTextDatum(top_left);
    canvas_.setTextColor(TFT_BLACK, TFT_WHITE);
}
}
