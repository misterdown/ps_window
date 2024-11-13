#include <iostream>
#include "ps_window.hpp"
#include <cstdint>
#include <limits>

void d(ps_window::deafult_window* w, int x, int y) {
    (void)w;
    std::cout << x << ' ' << y << '\n';
    *((int*)w->userPointer) = x;
}
void k(ps_window::deafult_window* w, int k) {
    (void)w;
    if (k == ps_window::KEY_CODES_E)
        std::cout << k << '\n';
    
}
struct rgba_color {
    public:
    union {
        struct {
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
        };
        uint32_t hex;
        uint8_t rgba[4];
        
    };

    public:
    rgba_color() : hex(0) {

    }
    rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = std::numeric_limits<uint8_t>::max()) : r(r), g(g), b(b), a(a) {
        
    }
    rgba_color(uint32_t hex) : r((hex >> 24) & 0xFF), g((hex >> 16) & 0xFF), b((hex >> 8) & 0xFF), a(hex & 0xFF) {

    }

};

int main() {
    rgba_color icon[16 * 16];
    ps_window::deafult_window win("wow");
    int XX;

    win.userRbDownCallback = d;
    win.userLmbDownCallback = d;
    win.userResizeCallback = d;
    win.userMoveCallback = d;
    win.userMouseMoveCallback = d;
    win.userKeyDownCallback = k;
    win.userPointer = &XX;
    win.set_window_name("piss");
    win.show();
    size_t d = 0;
    while (win.is_open()) {
        win.pool_events();
        if (rand() % 5000 == 0) {
            ++d;
            std::cout << d << " ";
            for (size_t i = 0; i < 16 * 16; ++i) {
                icon[i] = rgba_color((i + XX) % 256, (i + XX) % 128, (i + XX) % 64, 255);
            }
            win.set_icon(16, 16, (const char*)icon, false);
        }
    }
    return 0;
}