#include <renderer.hpp>
#include <3ds.h>
#include <globals.hpp>

mutex<std::vector<std::function<void(unsigned char *)>>> renderers;
mutex<std::vector<std::function<void(unsigned char *)>>> runOnce;

void rendererThread() {
    while(running) {
        u16 width, height;
        u8* lfb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, &width, &height);
        renderers++;
        for(auto c : *renderers)
            c(lfb);
        renderers--;

        runOnce++;
        for(auto c : *runOnce)
            c(lfb);
        runOnce->clear();
        runOnce--;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    svcExitThread();
}
