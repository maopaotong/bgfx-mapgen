#include "mapgen.h"
#include <string>

#if BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

static void glfw_errorCallback(int error, const char *description)
{
    // fprintf(stderr, "GLFW error %d: %s\n", error, description);
    std::cout << "GLFW error:" << description << std::endl;
}
void log(std::string msg)
{
    std::cout << msg << std::endl;
}

#define WNDW_WIDTH 1600
#define WNDW_HEIGHT 900

int main(int argc, char **argv)
{
    glfwSwapInterval(1); // Enable vsync
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Hello.bgfx", nullptr, nullptr);    


    bgfx::PlatformData pd;
    pd.nwh = glfwGetWin32Window(window);
    bgfx::setPlatformData(pd);

    bgfx::renderFrame();

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count; // Automatically choose a renderer.
    bgfxInit.platformData.nwh = glfwGetWin32Window(window);
    bgfxInit.resolution.width = WNDW_WIDTH;
    bgfxInit.resolution.height = WNDW_HEIGHT;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

    bgfx::init(bgfxInit);
    
    //bgfx::setViewRect(0, 0, 0, WNDW_WIDTH, WNDW_HEIGHT);
    const bgfx::ViewId kClearView = 0;
	//bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
    bgfx::touch(0); 
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
    unsigned int counter = 0;
	while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        bgfx::frame();
        glfwWaitEventsTimeout(0.01); // 16ms ≈ 60Hz
        counter++;
    }
   
    bgfx::shutdown();
    glfwTerminate();
    log("Done.");
    return 0;
}