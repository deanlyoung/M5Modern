#pragma once
#include <M5Unified.h>

namespace paperos {
// One sprite per screen prevents visible widget-by-widget painting on e-paper.
class ModernDisplay {
public:
    ModernDisplay() : canvas_(&M5.Display) {}
    bool begin();
    M5Canvas& canvas() { return canvas_; }
    void present();
    void presentRegion(int x, int y, int w, int h, bool quality = false);
    void heading(const char* title, bool showBack = true);
    void button(int x, int y, int w, int h, const char* label, bool filled = false);
private:
    M5Canvas canvas_;
    unsigned refreshes_ = 0;
};
}
