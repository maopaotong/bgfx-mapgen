#include <bgfx/bgfx.h>
int main()
{
    int a = 1;
    int b = a + 1;
    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::OpenGL;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfxInit.debug = true;
    return 0;
}